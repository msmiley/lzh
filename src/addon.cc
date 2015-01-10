#include <node.h>
#include <string>

using namespace v8;

Handle<Value> toUpper(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsString()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  String::Utf8Value str(args[0].As<String>());
  std::string ret(*str);
  std::transform(ret.begin(), ret.end(), ret.begin(), toupper);

  Local<String> strout = String::New(ret.c_str());
  return scope.Close(strout);
}

void Init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "toUpper", toUpper);
}

NODE_MODULE(addon, Init)
