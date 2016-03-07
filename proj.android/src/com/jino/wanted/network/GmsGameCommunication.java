package com.jino.wanted.network;

import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;
import android.util.SparseIntArray;

import com.google.android.gms.games.GamesActivityResultCodes;
import com.google.android.gms.games.GamesClient;
import com.google.android.gms.games.multiplayer.Invitation;
import com.google.android.gms.games.multiplayer.OnInvitationReceivedListener;
import com.google.android.gms.games.multiplayer.Participant;
import com.google.android.gms.games.multiplayer.realtime.RealTimeMessage;
import com.google.android.gms.games.multiplayer.realtime.RealTimeMessageReceivedListener;
import com.google.android.gms.games.multiplayer.realtime.RealTimeReliableMessageSentListener;
import com.google.android.gms.games.multiplayer.realtime.Room;
import com.google.android.gms.games.multiplayer.realtime.RoomConfig;
import com.google.android.gms.games.multiplayer.realtime.RoomStatusUpdateListener;
import com.google.android.gms.games.multiplayer.realtime.RoomUpdateListener;
import com.jino.wanted.R;
import com.jino.wanted.Wanted;
import com.jino.wanted.WantedUtils;

public class GmsGameCommunication implements 
		RoomUpdateListener, RealTimeMessageReceivedListener, RealTimeReliableMessageSentListener, RoomStatusUpdateListener, OnInvitationReceivedListener, GameCommunication {

    final static String TAG = "com.jino.wanted.network.GmsGameCommunication";

	final static int RC_SELECT_PLAYERS = 20000;
	final static int RC_INVITATION_INBOX = 20001;
	final static int RC_WAITING_ROOM = 20002; 
	
	static Context mContext;
	static String mIncomingInvitationId;
	static String mOpponentId;
	static String mRoomId;
	
	static SparseIntArray mTokenSentArray = new SparseIntArray();
	
	public GmsGameCommunication(Context context) {
		mContext = context;
		mRoomId = "";
		mOpponentId = "";
	}
	
	@Override
	public String getType()		{ return "gms";}
	
	
	@Override
	public void start()  {
		gameServicesSignIn();
	}

	@Override
	public void stop()  {
		if ( !mRoomId.equals("") ) { 
			((Wanted)mContext).getGamesClient().leaveRoom(this, mRoomId);
		}
	//	gameServicesSignOut();
	}

	/////
	// GameCenter Sign in / sign out
	public void gameServicesSignIn() {

		Log.i(TAG, "gameServicesSignIn");
		
		// if returns false, it means it's already connected 
		if (! Wanted.googlePlayServicesSignIn() ) { 
			onSignInSucceeded();
		}
    }
	
	public static void gameServicesSignOut() {
		Log.i(TAG, "gameServicesSignOut");
		((Wanted)mContext).getGamesClient().signOut();
//		mSignedIn = flase;
	}

	@Override
	public void onSignInFailed() {
		Log.i("com.jino.wanted.gmsGameCommunication", "OnSignInFailed");
		
	}
	/// 
	// user successfully signed in
	//@Override
	public void onSignInSucceeded() {
		Log.i("com.jino.wanted.gmsGameCommunication", "onSignInSucceeded");
		
		// register to be notified of incoming invitation
		((Wanted)mContext).getGamesClient().registerInvitationListener(this);

		//startActivityForResult(getGamesClient().getInvitationInboxIntent(), RC_INVITATION_INBOX);
		
		// check if an invitation is available
		if (((Wanted)mContext).getInvitationId() != null) {
			Log.i(TAG, "onSignInSucceeded - getInvitationID <> NULL");			
			RoomConfig.Builder roomConfigBuilder = makeBasicRoomConfigBuilder();
			roomConfigBuilder.setInvitationIdToAccept(((Wanted)mContext).getInvitationId());
			((Wanted)mContext).getGamesClient().joinRoom(roomConfigBuilder.build());
		} else { // go to quick game
			Log.i(TAG, "onSignInSucceeded - getInvitationID = NULL");			

	    	//Intent intent = getGamesClient().getInvitationInboxIntent();
	    	//startActivityForResult(intent, RC_INVITATION_INBOX);

			startQuickGame();
			// launch the player selection screen
			// minimum: 1 other player; maximum: 3 other players
	//		Intent intent = getGamesClient().getSelectPlayersIntent(1, 1);
		//	startActivityForResult(intent, RC_SELECT_PLAYERS);
		}
	}
		
	////
	// startQuickGame
	// 
	void startQuickGame() {
		// automatch criteria to invite 1 random opponent
		Bundle am = RoomConfig.createAutoMatchCriteria(1, 1, 0);
	
		//build the room config
		RoomConfig.Builder roomConfigBuilder = makeBasicRoomConfigBuilder();
		roomConfigBuilder.setAutoMatchCriteria(am);
		RoomConfig roomConfig = roomConfigBuilder.build();
		
		// create a room
		((Wanted)mContext).getGamesClient().createRoom(roomConfig);
		
	}

	
	/**
	 * encodeRealTimeMessage
	 * encode array of int into array of bytes
	 * 
	 * @param msgArray: array of int that needs to be encoded
	 * @return	the encode byte array
	 */
	public byte[] encodeRealTimeMessage(int[] msgArray) 
	{
		return WantedUtils.encodeIntToBytes(msgArray);
	}
	
	/**
	 * decodeRealTimeMessage
	 * decode byte array message into int array
	 * @param msgArray
	 * @return
	 */
	public int[] decodeRealTimeMessage(byte[] msgArray)
	{	
		return WantedUtils.decodeBytesToInt(msgArray);
	}

	// Called when we receive a sent message callback
    @Override
	public void onRealTimeMessageSent(int statusCode, int tokenId, String recipientParticipantId)
    {
        int msgType = mTokenSentArray.get(tokenId);

        Log.d(TAG, "Message sent: " + Integer.toString(statusCode) + "/" + Integer.toString(tokenId) + "/" + Integer.toString(msgType));
	
    	if (msgType > 0 && statusCode == GamesClient.STATUS_OK) {
    		((Wanted)mContext).onMessageSent(msgType);
    	}
    }
    // Called when we receive a real-time message from the network.
    @Override
    public void onRealTimeMessageReceived(RealTimeMessage rtm) {
        int[] buf = decodeRealTimeMessage(rtm.getMessageData());
        
        Log.d(TAG, "Message received: " + buf[0] + "/" + buf.length);
		((Wanted)mContext).onMessageReceived(buf, buf.length);
    }
    

    // 
    // send chosen character to opponent
    //
    public void notifyOpponentOfCharacter(int character)
    {
		int[] msgArray = {WANTED_NOTIFY_CHARACTER, character};
    	
        Log.d(TAG, "notifyOpponentOfCharacter(" + mRoomId + ", " + mOpponentId + ") Character:[" + Integer.toString(character) + "]");
    	((Wanted)mContext).getGamesClient().sendReliableRealTimeMessage(this, encodeRealTimeMessage(msgArray), mRoomId, mOpponentId);    	
    }
    

	///
	// sendTargetPos to Opponent
	@Override
    public void notifyOpponentOfTargetPos(int x, int y)
    {
		int[] msgArray = {WANTED_NOTIFY_TARGET_POS, x, y};
    	    	
        Log.d(TAG, "notifyOpponentOfTargetPos(" + mRoomId + ", " + mOpponentId + ") X:[" + Integer.toString(x) + "] Y:[" + Integer.toString(y) + "]");
    	((Wanted)mContext).getGamesClient().sendReliableRealTimeMessage(this, encodeRealTimeMessage(msgArray), mRoomId, mOpponentId);
    }

	@Override
    public void notifyOpponentOfDuelStart()
	{
		int[] msgArray = {WANTED_NOTIFY_DUEL_START};
    	
    	int startDuelToken = ((Wanted)mContext).getGamesClient().sendReliableRealTimeMessage(this,encodeRealTimeMessage(msgArray), mRoomId, mOpponentId);
    	mTokenSentArray.append(startDuelToken, WANTED_NOTIFY_DUEL_START);

		Log.d(TAG, "StartDuel sent [" + Integer.toString(startDuelToken) + "]");
	}
	
	@Override
	public void notifyOpponentOfTimeToHit(int usec) 
	{
		int[] msgArray = {WANTED_NOTIFY_TARGET_HIT, usec, WANTED_OPPONENT};
    	
        Log.d(TAG, "notifyOpponentOfTimeToHit(" + mRoomId + ", " + mOpponentId + ") USEC:[" + Integer.toString(usec) + "]");
    	((Wanted)mContext).getGamesClient().sendReliableRealTimeMessage(this, encodeRealTimeMessage(msgArray), mRoomId, mOpponentId);		
	}

	@Override
    public void notifyOpponentOfWinner(int winner)
	{
		// change value as I am the opponent of my opponent
		int theWinner = WANTED_ME;

		if (winner == WANTED_ME) {
			theWinner = WANTED_OPPONENT;
		}
		int[] msgArray = {WANTED_NOTIFY_WINNER, theWinner};
    	
        Log.d(TAG, "notifyOpponentOfWinner(" + mRoomId + ", " + mOpponentId + ") theWinner:[" + Integer.toString(theWinner) + "]");
    	((Wanted)mContext).getGamesClient().sendReliableRealTimeMessage(this, encodeRealTimeMessage(msgArray), mRoomId, mOpponentId);

	}


	void displayError(int messageId)
	{
		Resources res = mContext.getResources();
		((Wanted)mContext).displayError(res.getString(messageId));
	}
	
	@Override
	public void onLeftRoom(int statusCode, String roomId) {
        Log.d(TAG, "onLeftRoom(" + statusCode + ", " + roomId + ")");
        // if opponent left room, inform the player and return to main menu
		//displayError(R.string.opponent_left_room);
        //ready to start another game
        mRoomId = "";
	}
	
	private RoomConfig.Builder makeBasicRoomConfigBuilder() {
		return RoomConfig.builder(this)
				.setMessageReceivedListener(this)
				.setRoomStatusUpdateListener(this);
	}
	
	//////////////////
	// RoomUpdateListener implement
	
    // Called when room has been created
    @Override
    public void onRoomCreated(int statusCode, Room room) {
        Log.d(TAG, "onRoomCreated(" + statusCode + ", " + room + ")");
        
        // if room creation failed, inform the player and return to main menu
        if (statusCode != GamesClient.STATUS_OK) {
            Log.e(TAG, "*** Error: onRoomCreated, status " + statusCode);
            displayError(R.string.room_creation_failed);
            
            return;
        }
        
        // get waiting room intent
       Intent i = ((Wanted)mContext).getGamesClient().getRealTimeWaitingRoomIntent(room, Integer.MAX_VALUE);
       ((Wanted)mContext).startActivityForResult(i, RC_WAITING_ROOM);
    }

    // Called when room is fully connected.
    @Override
    public void onRoomConnected(int statusCode, Room room) {
        Log.d(TAG, "onRoomConnected(" + statusCode + ", " + room + ")");

        // if room connection failed, inform the player and return to main menu
        if (statusCode != GamesClient.STATUS_OK) {
            Log.e(TAG, "*** Error: onRoomConnected, status " + statusCode);
            return;
        }
    }

    @Override
    public void onJoinedRoom(int statusCode, Room room) {
        Log.d(TAG, "onJoinedRoom(" + statusCode + ", " + room + ")");
        if (statusCode != GamesClient.STATUS_OK) {
            Log.e(TAG, "*** Error: onRoomConnected, status " + statusCode);
            return;
        }

         // get waiting room intent
         Intent i = ((Wanted)mContext).getGamesClient().getRealTimeWaitingRoomIntent(room, Integer.MAX_VALUE);
         ((Wanted)mContext).startActivityForResult(i, RC_WAITING_ROOM);        
    }


	
	// We treat most of the room update callbacks in the same way: we update our list of
    // participants and update the display. In a real game we would also have to check if that
    // change requires some action like removing the corresponding player avatar from the screen,
    // etc.
    @Override
    public void onConnectedToRoom(Room room) {
        Log.d(TAG, "onConnectedToRoom");
        updateRoom(room);
        
    	boolean bServer = false;
        Wanted w = (Wanted)mContext;
        String myId = room.getParticipantId(w.getGamesClient().getCurrentPlayerId());
        
        mRoomId = room.getRoomId();
        // smallest ID is the server
        for (Participant p : room.getParticipants()) {
        	String pid = p.getParticipantId();
        	if (!pid.equals(myId)) {        		
        		bServer = (myId.compareTo(pid) < 0);
        		mOpponentId = pid;
        	}
        }
        
        if (bServer) {
            Log.d(TAG, "onConnectedToRoom - StartServer (" + myId + "/" + mOpponentId + ")");
            ((Wanted)mContext).startServer();            
        } else {
            Log.d(TAG, "onConnectedToRoom - StartClient (" + myId + "/" + mOpponentId + ")");
            ((Wanted)mContext).startClient();            
        }
    }

    @Override
    public void onDisconnectedFromRoom(Room room) {
        Log.d(TAG, "onDisconnectedToRoom");
        updateRoom(room);
    }
    
    @Override
    public void onPeerDeclined(Room room, List<String> arg1) {
        updateRoom(room);
    }

    @Override
    public void onPeerInvitedToRoom(Room room, List<String> arg1) {
        updateRoom(room);
    }

    @Override
    public void onPeerJoined(Room room, List<String> arg1) {
        updateRoom(room);
    }

    @Override
    public void onPeerLeft(Room room, List<String> peersWhoLeft) {
        updateRoom(room);
    }

    @Override
    public void onRoomAutoMatching(Room room) {
        Log.d(TAG, "onRoomAutoMatching");
        updateRoom(room);
    }

    @Override
    public void onRoomConnecting(Room room) {
        Log.d(TAG, "onRoomConnecting");
        updateRoom(room);
    }

    @Override
    public void onPeersConnected(Room room, List<String> peers) {
        updateRoom(room);
    }

    @Override
    public void onPeersDisconnected(Room room, List<String> peers) {
        updateRoom(room);
    }

    void updateRoom(Room room) {
        
    }	
	
    @Override
    public void onActivityResult(int request, int response, Intent data) {
        Log.d(TAG, "onActivityResult");
        
        if (request == RC_SELECT_PLAYERS) {
            Log.d(TAG, "onActivityResult RC_SELECT_PLAYERS");
            if (response != Activity.RESULT_OK) {
                // user canceled
                return;
            }

            // get the invitee list
            final ArrayList<String> invitees =
                data.getStringArrayListExtra(GamesClient.EXTRA_PLAYERS);

            // get automatch criteria
            Bundle autoMatchCriteria = null;
            int minAutoMatchPlayers =
                data.getIntExtra(GamesClient.EXTRA_MIN_AUTOMATCH_PLAYERS, 0);
            int maxAutoMatchPlayers =
                data.getIntExtra(GamesClient.EXTRA_MAX_AUTOMATCH_PLAYERS, 0);

            if (minAutoMatchPlayers > 0) {
                autoMatchCriteria =
                    RoomConfig.createAutoMatchCriteria(
                        minAutoMatchPlayers, maxAutoMatchPlayers, 0);
            } else {
                autoMatchCriteria = null;
            }

            // create the room and specify a variant if appropriate
            RoomConfig.Builder roomConfigBuilder = makeBasicRoomConfigBuilder();
            roomConfigBuilder.addPlayersToInvite(invitees);
            if (autoMatchCriteria != null) {
                roomConfigBuilder.setAutoMatchCriteria(autoMatchCriteria);
            }
            RoomConfig roomConfig = roomConfigBuilder.build();
            ((Wanted)mContext).getGamesClient().createRoom(roomConfig);

        } else if (request == RC_INVITATION_INBOX) {
            Log.d(TAG, "onActivityResult RC_INVITATION_INBOX");
            if (response != Activity.RESULT_OK) {
                // canceled
                Log.d(TAG, "onActivityResult RC_INVITATION_INBOX  >>> CANCELED");
                return;
            }

            // get the selected invitation
            Bundle extras = data.getExtras();
            Invitation invitation = extras.getParcelable(GamesClient.EXTRA_INVITATION);

            // accept it!
            RoomConfig roomConfig = makeBasicRoomConfigBuilder()
                    .setInvitationIdToAccept(invitation.getInvitationId())
                    .build();
            ((Wanted)mContext).getGamesClient().joinRoom(roomConfig);

            Log.d(TAG, "onActivityResult RC_INVITATION_INBOX  >>> ACCEPTED");

            // go to game screen
        } else if (request == RC_WAITING_ROOM) {
        	Log.d(TAG, "onActivityResult RC_WAITING_ROOM");
            if (response == Activity.RESULT_OK) {
                Log.d(TAG, "onActivityResult RC_WAITING_ROOM  >>> OPPONENT FOUND !");
                // (start game)
                ((Wanted)mContext).startGame();            

                // start multiplayer game logic 
            }
            else if (response == Activity.RESULT_CANCELED) {
                // Waiting room was dismissed with the back button. The meaning of this
                // action is up to the game. You may choose to leave the room and cancel the
                // match, or do something else like minimize the waiting room and
                // continue to connect in the background.

                // in this example, we take the simple approach and just leave the room:
             //   getGamesClient().leaveRoom(this, mRoomId);
                Log.d(TAG, "onActivityResult RC_WAITING_ROOM  >>> CANCELED");

            }
            else if (response == GamesActivityResultCodes.RESULT_LEFT_ROOM) {
                Log.d(TAG, "onActivityResult RC_WAITING_ROOM  >>> LEFT ROOM");
                // player wants to leave the room.
//                getGamesClient().leaveRoom(this, mRoomId);
            }
        }
    }

    
    // Called when we get an invitation to play a game
    //@Override
    public void onInvitationReceived(Invitation invitation) {
    	Log.d(TAG, "Invitation received");
            	
    	mIncomingInvitationId = invitation.getInvitationId();
    	Intent intent = ((Wanted)mContext).getGamesClient().getInvitationInboxIntent();
    	((Wanted)mContext).startActivityForResult(intent, RC_INVITATION_INBOX);
   }
    
}

