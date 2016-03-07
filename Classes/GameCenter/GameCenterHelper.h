#ifndef __GAME_CENTER_HELPER__
#define __GAME_CENTER_HELPER__

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

/**
 * C++ -->> Java
 */

namespace helper {
namespace gamecenter {

const char* const CLASS_NAME = "com/jino/wanted/Wanted";

void callStaticVoidMethod(const char* name);
bool callStaticBoolMethod(const char* name);
void callStaticVoidMethodWithString(const char* name, const char* idName);
void callStaticVoidMethodWithStringAndInt(const char* name, const char* idName, const int score);
void callStaticVoidMethodWithInt(const char* name, const int i);
void callStaticVoidMethodWithIntAndInt(const char* name, const int i1 , const int i2);
void callStaticVoidMethodWithDouble(const char* name, const double d);
} // namespace gamecenter
} // namespace helper

#endif 		// __GAME_CENTER_HELPER__
