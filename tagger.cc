#include "node-mecab.h"

namespace node_mecab {

using namespace std;

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::ObjectTemplate;
using v8::String;
using v8::Value;

const char* ToCString(const String::Utf8Value& value) {
    return *value ? *value : "<string conversion failed>";
}

Tagger::Tagger(MeCab::Tagger *tagger) : tagger_(tagger) {
}

Tagger::~Tagger() {
  delete tagger_;
}

void Tagger::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<ObjectTemplate> addon_data_tpl = ObjectTemplate::New(isolate);
  addon_data_tpl->SetInternalFieldCount(1);  // 1 field for the Tagger::New()
  Local<Object> addon_data =
      addon_data_tpl->NewInstance(context).ToLocalChecked();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New, addon_data);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Tagger"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "parse", Parse);

  Local<Function> constructor = tpl->GetFunction(context).ToLocalChecked();
  addon_data->SetInternalField(0, constructor);
  exports->Set(
    context,
    String::NewFromUtf8(isolate, "Tagger"),
    constructor
  ).FromJust();
}

void Tagger::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  v8::String::Utf8Value str(isolate, args[0]);
  std::string cppStr(*str);
  const char *str_char = ToCString(str);

  Tagger* tagger = new Tagger(MeCab::createTagger(str_char));
  tagger->Wrap(args.This());
  args.GetReturnValue().Set(args.This());
}

void Tagger::Parse (const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();
  Tagger* tagger = ObjectWrap::Unwrap<Tagger>(args.Holder());

  v8::String::Utf8Value str(isolate, args[0]);
  std::string cppStr(*str);
  const char *str_char = ToCString(str);
  const char *result = tagger->tagger_->parse(str_char);

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, result));
}

}
