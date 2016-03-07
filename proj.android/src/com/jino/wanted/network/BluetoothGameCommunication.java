package com.jino.wanted.network;

import com.jino.wanted.Wanted;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.util.Log;
import com.jino.wanted.R;

public class BluetoothGameCommunication implements GameCommunication {

    final static String TAG = "com.jino.wanted.network.BluetoothGameCommunication";
	private final static int RC_ENABLE_BLUETOOTH = 3000;

	static Context mContext;
	public BluetoothGameCommunication(Context context) {
		mContext = context;
	}
	public String getType()		{ return "bluetooth";}


	/**
	 * displayError
	 * build error message and notify wanted::GameCenter
	 */
	void displayError(int messageId)
	{
		Resources res = mContext.getResources();
		((Wanted)mContext).displayError(res.getString(messageId));
	}

	public void start() {
		BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		
		if (bluetoothAdapter != null) {
			if (!bluetoothAdapter.isEnabled()) {
				((Wanted)mContext).startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), RC_ENABLE_BLUETOOTH);
			} else {
				connectToOtherDevice();
			}
		} else {
			displayError(R.string.bluetooth_not_supported);
		}
	}
	public void stop() {}
	public void onSignInSucceeded() {}
	public void onSignInFailed() {}
    public void notifyOpponentOfCharacter(int character) {}
    public void notifyOpponentOfTargetPos(int x, int y) {}
    public void notifyOpponentOfDuelStart() {}
    public void notifyOpponentOfTimeToHit(int usec) {}
    public void notifyOpponentOfWinner(int winner) {}

    /**
     * connectToOtherDevice
     * Establish bluetooth connection to another device
     * to start a wanted game
     */
    private void connectToOtherDevice() {
    	// 1 - Prepare device as WANTED server, listening for connection
    	
    	
    	// 2 - look for devices already bonded
    	// 		=> if available, try to connect on service WANTED

    	// 3 - could not connect to devices already bonded
    	//		=> look for new devices and try to connect on service WANTED 
    	

    }

    @Override
    public void onActivityResult(int request, int response, Intent data) {
        Log.d(TAG, "onActivityResult");
        if (request == RC_ENABLE_BLUETOOTH) {
            Log.d(TAG, "onActivityResult RC_ENABLE_BLUETOOTH");
            if (response == Activity.RESULT_OK ) {
            	// user activated Bluetooth            	
            	connectToOtherDevice();
            } else {
            	// user did not activate Bluetooth
    			displayError(R.string.bluetooth_not_enable);
            }
        }
    }
}
