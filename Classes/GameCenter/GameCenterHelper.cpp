#include "GameCenterHelper.h"
#include "cocos2d.h"

namespace helper {
namespace gamecenter {


void callStaticVoidMethod(const char* name)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, name, "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

bool callStaticBoolMethod(const char* name)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, name, "()Z")) {
        bool result = (t.env->CallStaticBooleanMethod(t.classID, t.methodID) == JNI_TRUE);
        t.env->DeleteLocalRef(t.classID);
        return result;
    } else {
        return false;
    }
}

void callStaticVoidMethodWithString(const char* name, const char* idName)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, name, "(Ljava/lang/String;)V")) {
        jstring jIdName = t.env->NewStringUTF(idName);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jIdName);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(jIdName);
    }
}

void callStaticVoidMethodWithStringAndInt(const char* name, const char* idName, const int score)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, name, "(Ljava/lang/String;I)V")) {
        jstring jIdName = t.env->NewStringUTF(idName);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jIdName, (jint)score);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(jIdName);
    }
}
void callStaticVoidMethodWithInt(const char* name, const int i)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, name, "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, (jint)i);
        t.env->DeleteLocalRef(t.classID);
    } else {
    	cocos2d::CCLog("helper::gameCenter::callStaticVoidMethodWithInt : method not found [%s]", name);
    }
}

void callStaticVoidMethodWithIntAndInt(const char* name, const int i1 , const int i2)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, name, "(II)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, (jint)i1, (jint)i2);
        t.env->DeleteLocalRef(t.classID);
    } else {
    	cocos2d::CCLog("helper::gameCenter::callStaticVoidMethodWithIntAndInt : method not found [%s]", name);
    }
}

void callStaticVoidMethodWithDouble(const char* name, const double d)
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, name, "(D)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, (jdouble)d);
        t.env->DeleteLocalRef(t.classID);
    }
}

} // namespace gamecenter
} // namespace helper
