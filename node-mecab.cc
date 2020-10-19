// addon.cc
#include <node.h>
#include "node-mecab.h"

namespace node_mecab {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  Tagger::Init(exports);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)

}