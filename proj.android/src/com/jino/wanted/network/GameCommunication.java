package com.jino.wanted.network;

import android.content.Intent;

public interface GameCommunication {

	final static int WANTED_STARTGAME			= 0x0000;
	final static int WANTED_GAME_INITIALIZED	= 0x0001;
	final static int WANTED_SCENE_INITIALIZED	= 0x0002;
	final static int WANTED_NOTIFY_CHARACTER	= 0x0003;
	final static int WANTED_NOTIFY_TARGET_POS	= 0x0004;
	final static int WANTED_NOTIFY_DUEL_START	= 0x0005;
	final static int WANTED_NOTIFY_TARGET_HIT	= 0x0006;
	final static int WANTED_NOTIFY_WINNER		= 0x0007;
	final static int WANTED_ERROR				= 0x0008;
	final static int WANTED_OPPONENT_IS_COMPUTER= 0x0009;	
	final static int WANTED_OPPONENT		= 0;
	final static int WANTED_ME				= 1;
	
	public String getType();
	public void start();
	public void stop();
	public void onSignInSucceeded();
	public void onSignInFailed();
    public void onActivityResult(int request, int response, Intent data);
    public void notifyOpponentOfCharacter(int character);
    public void notifyOpponentOfTargetPos(int x, int y);
    public void notifyOpponentOfDuelStart();
    public void notifyOpponentOfTimeToHit(int usec);
    public void notifyOpponentOfWinner(int winner);
    
}
