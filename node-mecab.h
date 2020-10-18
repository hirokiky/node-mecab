#ifndef _NODE_MECAB_H_
#define _NODE_MECAB_H_

#include <mecab.h>
#include <node.h>
#include <node_object_wrap.h>

namespace node_mecab {

class Tagger : public node::ObjectWrap {
    public:
        static void Init(v8::Local<v8::Object> exports);
    private:
        explicit Tagger();
        ~Tagger();
        static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
        static void Parse(const v8::FunctionCallbackInfo<v8::Value>& args);
        static v8::Global<v8::Function> constructor;
        MeCab::Tagger *tagger;
};

}  // namespace mecab
#endif
