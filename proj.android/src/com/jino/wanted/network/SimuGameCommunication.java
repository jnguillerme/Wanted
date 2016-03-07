package com.jino.wanted.network;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.jino.wanted.Wanted;
import com.jino.wanted.WantedHelper;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class SimuGameCommunication implements GameCommunication {

    final static String TAG = "com.jino.wanted.network.simuGameCommunication";

	static Context mContext;
 
    public String getType() { return "simu"; }
	public SimuGameCommunication(Context context) {
		mContext = context;
	}

	public void start() 
	{
		Log.i(TAG, "Start");
		((Wanted)mContext).runOnUiThread(new Runnable() {
            public void run() {
            	((Wanted)mContext).startServer();            		
            	onSignInSucceeded();
            }
        });
	}
	public void stop() {}

	public void onSignInSucceeded() {
		Log.i(TAG, "onSignInSucceeded");
    	((Wanted)mContext).startGame();            
	}
	public void onSignInFailed() {}
    public void onActivityResult(int request, int response, Intent data) {}
    
    public void notifyOpponentOfCharacter(int character) {
    	int[] buf = {WANTED_NOTIFY_CHARACTER, 1}; 
        ((Wanted)mContext).onMessageReceived(buf, buf.length);    		
    }

    public void notifyOpponentOfTargetPos(int x, int y) {
		Log.i(TAG, "notifyOpponentOfTargetPos");

    	int[] buf1 = {WANTED_OPPONENT_IS_COMPUTER}; 
        ((Wanted)mContext).onMessageReceived(buf1, buf1.length);    		

        int[] buf2 = {WANTED_NOTIFY_DUEL_START}; 
        ((Wanted)mContext).onMessageReceived(buf2, buf2.length);    		
    }
    
    public void notifyOpponentOfDuelStart() {}
    public void notifyOpponentOfTimeToHit(int usec) {}
    public void notifyOpponentOfWinner(int winner) {}    

}
