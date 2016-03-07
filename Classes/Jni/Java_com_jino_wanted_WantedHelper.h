#ifndef _Java_com_jino_wanted_WantedHelper_H_
#define _Java_com_jino_wanted_WantedHelper_H_

extern "C" {
	JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeEnableGameCenter(JNIEnv *env, jobject thiz, jboolean enable);
	JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeEnableBluetooth(JNIEnv *env, jobject thiz, jboolean enable);
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeStartGame(JNIEnv *env, jobject thiz);
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeStartServer(JNIEnv *env, jobject thiz);
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeStartClient(JNIEnv *env, jobject thiz);
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeOnMessageReceived(JNIEnv *env, jobject thiz, jintArray array, jint arrayLength);
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeOnMessageSent(JNIEnv *env, jobject thiz, jint msgType);
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeDisplayError(JNIEnv *env, jobject thiz, jstring javaMessage);
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeLoadDuelWon(JNIEnv *env, jobject thiz, jint duelWon);
    JNIEXPORT void JNICALL Java_com_jino_wanted_WantedHelper_nativeLoadDuelLost(JNIEnv *env, jobject thiz, jint duelLost);

}
#endif //_Java_com_jino_wanted_WantedHelper_H_
