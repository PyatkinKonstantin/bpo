#include <node.h>

#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <locale.h>
#include <clocale>
#include <assert.h>
#include <windows.h>
#include <lm.h>
#include <iostream>
#include <string>
#include <atlstr.h>

namespace demo {

using namespace std;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using std::string;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {

    Isolate* isolate = args.GetIsolate();

          string username;

          USER_INFO_0* buffer;
          DWORD entries;
          DWORD total_entries;
          DWORD resume_handle = 0;

          NetUserEnum(NULL,0, 0, (BYTE**)&buffer, 4096, &entries, &total_entries, &resume_handle);

            v8::String::Utf8Value str(isolate, args[0]);
            std::string cppStr(*str);

          int count=0;
          for (unsigned i = 0; i < entries; i++) {

                username = string(CW2A(buffer[i].usri0_name, CP_UTF8));

                if (username==cppStr)
                {
                    args.GetReturnValue().Set(Number::New(isolate, 1));
                    count++;
                }
          }

          if(count==0){
               args.GetReturnValue().Set(Number::New(isolate, 0));
          }

}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "getWindowsUser", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace demo