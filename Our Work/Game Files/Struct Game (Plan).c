/*
	For this file, we need to put everything that needs to be stored
	about the game.
	
	Thomas: I think we should give everything player-related (rather
		than overall) its own struct, and pop that inside this struct.
		For my own game, I've done it where there's a struct called
		_player, and it stores their ID, money, and buildingData.
		We'll design that, and then just add three of those structs
		inside _game (as each player will need to store the same thing).
*/

/// This stores specific data about a player. Just have three of them
/// in _game.
typedef struct _player {
	/// This stores the ID of the player.
	int playerID;
	
	/// This counts how many of each building they have. This will
	/// allow us to easily calculate their score, and use other
	/// functions with it.
	int ARCs;
	int campuses;
	int G08s;
	int patents;
	int papers;
	
	/// This stores how many disciplines a person has.
	int THDs;
	int BPSs;
	int BQNs;
	int MJs;
	int MTVs;
	int MMONEYs;
} Player;

typedef struct _game {
	/// This stores what turn the game is up to. In game.h, they start
	/// at -1, so this has to be signed.
	int turnNumber;
	
	/// This stores whose turn it is.
	int whoseTurn;
	
	/// This stores the disciplines and dice layout of the board.
	int discipline[];
	int dice[];
	
	/// This stores the exchange rate of resources. It should be stored
	/// somewhere at least.
	int exchangeRate;
	
	/// These store specific data about each player. Their info is
	/// above.
	Player p1;
	Player p2;
	Player p3;
} * Game;