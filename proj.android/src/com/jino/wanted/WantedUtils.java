package com.jino.wanted;

import java.nio.ByteBuffer;
import java.nio.IntBuffer;


public class WantedUtils {

	public static byte[] encodeIntToBytes(int[] intArray) {
		ByteBuffer bb = ByteBuffer.allocate(4 * intArray.length); 
		for (int i = 0; i < intArray.length; i++) {
			bb.putInt(intArray[i]);
		}
		return bb.array();
	}

	public static int[] decodeBytesToInt(byte[] byteArray) {
		ByteBuffer bb = ByteBuffer.wrap(byteArray);
		IntBuffer ib = bb.asIntBuffer();
		int[] out = new int[ib.limit()];
		ib.get(out);

		return out;
	}
}
