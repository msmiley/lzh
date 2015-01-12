#include <node.h>
#include <node_buffer.h>
#include <string>
#include "nan.h"
#include "cpp-debug.h"

using namespace v8;
using namespace node;

// bring in the prototypes for lzh.c
extern "C" {
  unsigned int DecodedLength(unsigned char *in);
  unsigned int Decode(unsigned char *in, unsigned char *out);
  unsigned int Encode(unsigned char *in, unsigned int inlen, unsigned char *out);
}



// // compress
// static NAN_METHOD(compress) {
//   NanScope();
//
//   if (args.Length() < 0 || !Buffer::HasInstance(args[0])) {
//     return NanThrowTypeError("Argument must be a Buffer");
//   }
//
//   // get input Buffer
//   Local<Object> buf_in = args[0].As<Object>();
//
//   unsigned char *in = (unsigned char *)Buffer::Data(buf_in);
//   size_t inLen = Buffer::Length(buf_in);
//
//   // SlowBuffer
//   Buffer *slowbuf_out = Buffer::New(inLen*2);
//   unsigned char *out = (unsigned char *)Buffer::Data(slowbuf_out);
//
//   unsigned int encodedLen = Encode(in, inLen, out);
//
//   // prepare Buffer for trip back to JS-land
//   Local<Object> globalObj = Context::GetCurrent()->Global();
//   // get the Buffer constructor
//   Local<Function> bufferConstructor = Local<Function>::Cast(globalObj->Get(String::New("Buffer")));
//   // prepare args to Bufer constructor
//   Handle<Value> constructorArgs[3] = { slowbuf_out->handle_, Integer::New(encodedLen), Integer::New(0) };
//   // instantiate Buffer
//   Local<Object> buf_out = bufferConstructor->NewInstance(3, constructorArgs);
//
//   NanReturnValue(buf_out);
// }

// decompress
NAN_METHOD(decompress) {
  NanScope();

  if (args.Length() < 0 || !Buffer::HasInstance(args[0])) {
    return NanThrowTypeError("Argument must be a Buffer");
  }

  // get input Buffer
  Local<Object> buf_in = args[0]->ToObject();
  unsigned char *in = (unsigned char *)Buffer::Data(buf_in);
  size_t encodedLen = Buffer::Length(buf_in);
  printf("%d\n", encodedLen);

  // get the length so we can size the out Buffer
  uint32_t decodedLen = DecodedLength(in);

  unsigned char out[4155]; // maximum block size

  // call Decode in lzh.c
  uint32_t outLen = Decode(in, out);

  // make sure algorithm yielded correct length
  if (outLen != decodedLen) {
    NanThrowError("invalid LZH input bytes");
    NanReturnUndefined();
  }

  Local<Object> buf_out = NanNewBufferHandle((char *)out, outLen);

  NanReturnValue(buf_out);
}


extern "C"
void Initialize(Handle<Object> exports) {
  NanScope();

  exports->Set(String::NewSymbol("decompress"),
    FunctionTemplate::New(decompress)->GetFunction());
  // exports->Set(String::NewSymbol("compress"),
  //   FunctionTemplate::New(compress)->GetFunction());
}

NODE_MODULE(lzh, Initialize)
