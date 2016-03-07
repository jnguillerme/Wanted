#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include "cocos2d.h"

#include "Java_com_jino_wanted_WantedHelper.h"
#include "GameCenter/GameCenter.h"

using namespace cocos2d;

extern "C" {
	JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeEnableGameCenter(JNIEnv *env, jobject thiz, jboolean enable) {
    	CCLog("JNI HELPER => Java_com_jino_wanted_wantedHelper_nativeEnableGameCenter");
        wanted::GameCenter::sharedGC().enableGameCenter(enable);
    }
	JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeEnableBluetooth(JNIEnv *env, jobject thiz, jboolean enable) {
		CCLog("JNI HELPER => Java_com_jino_wanted_wantedHelper_nativeEnableBluetooth");
		wanted::GameCenter::sharedGC().enableBluetooth(enable);
	}
	JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeStartGame(JNIEnv *env, jobject thiz) {
    	CCLog("JNI HELPER => Java_com_jino_wanted_wantedHelper_nativeStartGame");
        wanted::GameCenter::sharedGC().startGame();
    }
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeStartServer(JNIEnv *env, jobject thiz) {
        CCLog("JNI HELPER => Java_com_jino_wanted_wantedHelper_nativeStartServer");
        wanted::GameCenter::sharedGC().startServer();
     }
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeStartClient(JNIEnv *env, jobject thiz) {
        CCLog("JNI HELPER => Java_com_jino_wanted_wantedHelper_nativeStartClient");
        wanted::GameCenter::sharedGC().startClient();
    }
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeOnMessageReceived(JNIEnv *env, jobject thiz, jintArray array, jint arrayLength) {
         CCLog("JNI HELPER => Java_com_jino_wanted_wantedHelper_nativeOnMessageReceived");

         jint* content_array = (env)->GetIntArrayElements(array,NULL);
         int* buf = new int[arrayLength];
         //env->GetByteArrayRegion(content_array, 0, arrayLength, reinterpret_cast<jbyte*>(buf));
         for (unsigned int i = 0; i < arrayLength; i++) {
        	 buf[i] = content_array[i];
             CCLog("JNI HELPER => [%d][%d]", content_array[i], buf[i]);
         }

         wanted::GameCenter::sharedGC().onMessageReceived((unsigned int*)buf, arrayLength);
         delete buf;
     }

    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeOnMessageSent(JNIEnv *env, jobject thiz, jint msgType) {
         CCLog("JNI HELPER => Java_com_jino_wanted_wantedHelper_nativeOnMessageSent");
         wanted::GameCenter::sharedGC().onMessageSent(msgType);
     }

    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeDisplayError(JNIEnv *env, jobject thiz, jstring javaMessage) {
        CCLog("JNI HELPER => Java_com_jino_wanted_wantedHelper_nativeDisplayError");

        const char* nativeMessage = env->GetStringUTFChars(javaMessage, 0);
        wanted::GameCenter::sharedGC().onError(nativeMessage, true);
        env->ReleaseStringUTFChars(javaMessage, nativeMessage);
    }

    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeLoadDuelWon(JNIEnv *env, jobject thiz, jint duelWon) {
        CCLog("JNI HELPER => Java_com_jino_wanted_wantedHelper_nativeLoadDuelWon [%d]", duelWon);
        wanted::GameCenter::sharedGC().setDuelWon(duelWon);
    }
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeLoadDuelLost(JNIEnv *env, jobject thiz, jint duelLost) {
        CCLog("JNI HELPER => Java_com_jino_wanted_wantedHelper_nativeLoadDuelLost [%d]", duelLost);
        wanted::GameCenter::sharedGC().setDuelLost(duelLost);
    }

}
