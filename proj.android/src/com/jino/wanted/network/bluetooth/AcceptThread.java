package com.jino.wanted.network.bluetooth;

import java.io.IOException;
import java.util.UUID;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;

public class AcceptThread extends Thread {
	private final BluetoothServerSocket mmServerSocket;
	private final UUID WANTED_UUID = new UUID(12345L, 12345L);
	
	private BluetoothAdapter mBluetoothAdapter;
	
	public AcceptThread() {
		// use a temporary object that is later assigned to mServerSocket
		// because mServerSocket is final
		BluetoothServerSocket  tmp = null;
		try {
			tmp = mBluetoothAdapter.listenUsingRfcommWithServiceRecord("WANTED", WANTED_UUID);
		} catch(IOException e) {}
		
		mmServerSocket = tmp;
	}

	public void run() {
		BluetoothSocket socket = null;
		
		// keep listening until exception occurs or a socket is returned
		while (true) {
			try { 
				socket = mmServerSocket.accept();
			} catch (IOException e) {
				break;
			}
			if (socket != null) {
				//do work to manage connection in a separate thread
			//	manageConnectedSocket(socket);
				try {
					mmServerSocket.close();
				} catch (IOException e) {}
				break;
			}
		}
		
	}

	/**
	 * cancel
	 * will cancel the listening socket and cause the thread to finish
	 */
	public void cancel() {
		try {
			mmServerSocket.close();
		} catch (IOException e) {}
	}
}
