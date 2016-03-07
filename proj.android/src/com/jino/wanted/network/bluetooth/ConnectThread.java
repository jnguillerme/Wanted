package com.jino.wanted.network.bluetooth;

import java.io.IOException;
import java.util.UUID;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

public class ConnectThread extends Thread {
	private final BluetoothSocket mmSocket;
	private final BluetoothDevice mmDevice;
	private BluetoothAdapter mBluetoothAdapter;

	private final UUID WANTED_UUID = new UUID(12345L, 12345L);

	public ConnectThread(BluetoothDevice device) {
		// use a temporary object later assigned to mmSocket
		// as mmSocket is final
		BluetoothSocket tmp = null;
		mmDevice = device;
		
		// get a BluetoothSocket to connect with the given BluetootDevice
		try {
			tmp= device.createRfcommSocketToServiceRecord(WANTED_UUID);
		} catch (IOException e) {}
		mmSocket = tmp;
	}

	public void run() {
		// cancel discovery because it will slow down the connection
		mBluetoothAdapter.cancelDiscovery();
		
		try {
			// connect the device through the socket. 
			// This will block until it succeeds or throw an exception
			mmSocket.connect();
		} catch (IOException connectException) {
			// unable to connect - close the socket and get out
			try {
				mmSocket.close();
			} catch (IOException closeException) {}
			return;
		}
		// do work to manage the connection in a separate thread
		// manageConnectedSocket(mmSocket);
	}
	
	/**
	 * cancel
	 * will cancel an in-progress connection and close the socket
	 */
	 public void cancel() {
		 try {
			 mmSocket.close();
		 } catch (IOException e) {}
	 }
}
