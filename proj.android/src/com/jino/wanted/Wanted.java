/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.jino.wanted;

import com.google.android.gms.appstate.AppStateClient;
import com.google.android.gms.appstate.OnStateLoadedListener;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.jino.wanted.network.BluetoothGameCommunication;
import com.jino.wanted.network.GameCommunication;
import com.jino.wanted.network.GmsGameCommunication;
import com.jino.wanted.network.SimuGameCommunication;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;
import com.jino.wanted.R;

public class Wanted extends BaseGameActivity  implements OnStateLoadedListener
{

    // Debug tag
    final static String TAG = "com.jino.wanted.wanted";
	final static int RC_REQUEST_LEADERBOARD = 10000;
	
	// Cloud data keys
	final static int DATA_DUEL_WON	= 1;
	final static int DATA_DUEL_LOST	= 2;
	
	static Context mContext;
	static boolean mSignedIn;
	static String mIncomingInvitationId;
	static GameCommunication mGameCom;
	
	public Wanted() {
		super(BaseGameActivity.CLIENT_APPSTATE | BaseGameActivity.CLIENT_GAMES);
	}
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		mContext = Wanted.this;
		mGameCom = null;
		mSignedIn = false;		
	}
		
	public static void onApplicationDidFinishLaunching() {
		// check if game center and bluetooth are available
		// and notify wanted::GameCenter
		((Wanted)mContext).runOnUiThread(new Runnable() {
			public void run() {
				WantedHelper.nativeEnableGameCenter( (GooglePlayServicesUtil.isGooglePlayServicesAvailable((Wanted)mContext) == ConnectionResult.SUCCESS) );
				WantedHelper.nativeEnableBluetooth( (BluetoothAdapter.getDefaultAdapter() != null) );
			}
		});
		googlePlayServicesSignIn();
	}

	private static GameCommunication getGameCom() {
		if (mGameCom == null) {
			mGameCom = new GmsGameCommunication(mContext);
		}
		
		return mGameCom;
	}
	
	public static void setGameCommunicationGooglePlayGameServices() {
		if (mGameCom == null || !mGameCom.getType().equals("gms") ) {
			mGameCom = new GmsGameCommunication(mContext);		
		}
	}
	
	public static void setGameCommunicationBlueTooth() {
		if (mGameCom == null || !mGameCom.getType().equals("bluetooth") ) {
			mGameCom = new BluetoothGameCommunication(mContext);
		}
	}
	
	public static void setGameCommunicationTest() {
		if (mGameCom == null || !mGameCom.getType().equals("simu") ) {
			mGameCom = new SimuGameCommunication(mContext);
		}
	}
	
	public static boolean googlePlayServicesSignIn() {		
		boolean ret = (!mSignedIn); 
		
		if (!mSignedIn) { 
			((Wanted)mContext).runOnUiThread(new Runnable() {
				public void run() {
					if ( GooglePlayServicesUtil.isGooglePlayServicesAvailable((Wanted)mContext) == ConnectionResult.SUCCESS ) {
						Log.i("com.jino.wanted.wanted", "gameServicesSignIn");		
						((Wanted)mContext).beginUserInitiatedSignIn();
					}
				}
			});
		} 
		
		return ret;
	}
	
	///
	// OnStateLoadedListener implementation
	///
	@Override
	public void onStateLoaded(int statusCode, int stateKey, byte[] data) {
		
		Log.i("com.jino.wanted.wanted", "onStateLoaded [" + Integer.toString(statusCode) + "][" + Integer.toString(stateKey) + "]");		

		if (statusCode == AppStateClient.STATUS_OK) {
			// successfully loaded / saved data
			if (stateKey == DATA_DUEL_WON) {
				WantedHelper.nativeLoadDuelWon(WantedUtils.decodeBytesToInt(data)[0]);
			} else if (stateKey == DATA_DUEL_LOST) {
				WantedHelper.nativeLoadDuelLost(WantedUtils.decodeBytesToInt(data)[0]);			
			}
		} else if (statusCode == AppStateClient.STATUS_NETWORK_ERROR_STALE_DATA) {
			// could not connect to get fresh data
			// but loaded possibly out of sync cached data instead
		} else {
			// handle error
		}
	}
	@Override 
	public void onStateConflict(int stateKey, String versionId, byte[] localData, byte[] serverData) {
		// resolve conflict, then call mAppStateClient.resolveConflict
		
	    byte[] resolvedData = resolveConflict(localData, serverData);
	    getAppStateClient().resolveState(this, stateKey, versionId, resolvedData);
	}

	byte[] resolveConflict(byte[] localData, byte[] serverData) {
	    // consolidate conflicting data here as appropriate to your application
	    //return resolvedState;
		return localData;	
	}
	///
	
	//  Messages sent to Game UI
	// We need to make sure all messages are processed by the UI thread
	///////
	public void startGame() {
		runOnGLThread(new Runnable() {
			public void run() {
				WantedHelper.nativeStartGame();
			}
		});		
	}
	
	public void startServer() {
		runOnGLThread(new Runnable() {
			public void run() {
				WantedHelper.nativeStartServer();
			}
		});		
	}
	public void startClient() {
		runOnGLThread(new Runnable() {
			public void run() {
				WantedHelper.nativeStartClient();
			}
		});		
	}
	public void onMessageSent(final int msgType) {
		runOnGLThread(new Runnable() {
			public void run() {
				WantedHelper.nativeOnMessageSent(msgType);
			}
		});
	}
    
	public void onMessageReceived(final int[] array, final int arrayLength) {
		runOnGLThread(new Runnable() {
			public void run() {
				WantedHelper.nativeOnMessageReceived(array, arrayLength);
			}
		});		
	}

	public void displayError(final String message) {
		runOnGLThread(new Runnable() {
			public void run() {
				WantedHelper.nativeDisplayError(message);
			}
		});		
	}
    

	///
	// Message received from the Game UI
	//
	
	public static void startGameServices() {
		getGameCom().start();
	}
	public static void stopGameServices() {
		getGameCom().stop();
	}

	public static void notifyOpponentOfCharacter(int character) {
		getGameCom().notifyOpponentOfCharacter(character);		
	}

	public static void notifyOpponentOfTargetPos(int x, int y) {
		Log.i(TAG , "notifyOpponentOfTargetPos [" + Integer.toString(x) + "][" + Integer.toString(y) + "]");
		getGameCom().notifyOpponentOfTargetPos(x, y);
	}

	public static void notifyOpponentOfDuelStart() {
		getGameCom().notifyOpponentOfDuelStart();		
	}

	public static void notifyOpponentOfTimeToHit(int usec) {
		getGameCom().notifyOpponentOfTimeToHit(usec);		
	}
	
	public static void notifyOpponentOfWinner(int winner) {
		getGameCom().notifyOpponentOfWinner(winner);		
	}
	
	///
	// update cloud data
	///	
	public static void saveDuelWon(int duelWon) {
		if (mSignedIn) {
			Log.i(TAG , "saveDuelWon [" + Integer.toString(duelWon) + "]");
			int[] data = {duelWon};
			((Wanted)mContext).getAppStateClient().updateState(DATA_DUEL_WON, WantedUtils.encodeIntToBytes(data));
		}
	}

	public static void saveDuelLost(int duelLost) {
		if (mSignedIn) {
			Log.i(TAG , "saveDuelLost [" + Integer.toString(duelLost) + "]");
			int[] data = {duelLost};
			((Wanted)mContext).getAppStateClient().updateState(DATA_DUEL_LOST, WantedUtils.encodeIntToBytes(data));
		}
	}
		
	public static void loadSavedData() {
		((Wanted)mContext).getAppStateClient().loadState(((Wanted)mContext), DATA_DUEL_WON);
		((Wanted)mContext).getAppStateClient().loadState(((Wanted)mContext), DATA_DUEL_LOST);
	}
	

	///
	// update leaderboard
	///
	public static void updateLeaderBoard(int leaderboadID, int score) {
		Resources res = mContext.getResources();
		((Wanted)mContext).getGamesClient().submitScore(res.getString(leaderboadID), score); 
	}
	public static void updateLeaderBoardDuelWon(int duelWon) {
		updateLeaderBoard(R.string.LEADERBOARD_ID_TOTAL_WON, duelWon);
	}
	public static void updateLeaderBoardDuelRatio(int ratio) {
		updateLeaderBoard(R.string.LEADERBOARD_ID_RATIO_WON, ratio);		
	}
	
	public static void displayLeaderboard() {
		Resources res = mContext.getResources();
		((Wanted)mContext).startActivityForResult(((Wanted)mContext).getGamesClient().getLeaderboardIntent(res.getString(R.string.LEADERBOARD_ID_TOTAL_WON)), RC_REQUEST_LEADERBOARD);
	}

	
	@Override
	public void onSignInFailed() {
		Log.i(TAG , "onSignInFailed");
		if (mGameCom != null) {
			mGameCom.onSignInFailed();
		}
		mSignedIn = false;
	}

	/// 
	// user successfully signed in
	@Override
	public void onSignInSucceeded() {
		Log.i(TAG , "onSignInSucceeded");
		mSignedIn = true;	
		loadSavedData();
	}
	
    @Override
    public void onActivityResult(int request, int response, Intent data) {
    	getGameCom().onActivityResult(request, response, data);
    }
    
    static {
         System.loadLibrary("game");
    }
    
}

