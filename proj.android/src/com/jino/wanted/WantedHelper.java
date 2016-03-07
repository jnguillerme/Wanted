package com.jino.wanted;

public class WantedHelper {
	public static native void nativeEnableGameCenter(boolean enable);
	public static native void nativeEnableBluetooth(boolean enable);
	public static native void nativeStartGame();
	public static native void nativeStartServer();
	public static native void nativeStartClient();
	public static native void nativeOnMessageSent(int msgType);
	public static native void nativeOnMessageReceived(int[] array, int arrayLength);
	public static native void nativeDisplayError(String message);
	public static native void nativeLoadDuelWon(int duelWon);
	public static native void nativeLoadDuelLost(int duelLost);
}
