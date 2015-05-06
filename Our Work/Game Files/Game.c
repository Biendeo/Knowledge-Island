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
	///Should we store this or use a formula to calculate this from the other info?
	int KPIs; 
	
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

typedef struct _building {
	/// This stores what type of building it is.
	int buildingType;
	
	/// This stores the path to that building.
	path path[PATH_LIMIT];
	
	/// This stores what player this building belongs to.
	int player;
} Building;

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
	
	/// This stores all the buildings currently in the game.
	/// 126 is the maximum number of ARCs and corner resources. We'll
	/// turn it into a define later.
	Building b[126];
	
	/// These store specific data about each player. Their info is
	/// above.
	Player p1;
	Player p2;
	Player p3;
} * Game;

Game newGame (int discipline[], int dice[]);

/// This frees the game when you're done. THIS IS IMPORTANT.
void disposeGame (Game g) {
	
}

/// This does an action the user inputs. I guess the AI will jump
/// directy to this step on his turn.
void makeAction (Game g, action a) {
	
}

/// This advances the game to the next turn. It increases the turn
/// number, and gives a dice roll.
// advance the game to the next turn, 
// assuming that the dice has just been rolled and produced diceScore
// the game starts in turn -1 (we call this state "Terra Nullis") and 
// moves to turn 0 as soon as the first dice is thrown. 
void throwDice (Game g, int diceScore) {
	
}

/// These are the "getter" functions. They return something based on
/// what you tell them.

/// This asks for a hexagon number, and returns what kind of resource
/// it is.
int getDiscipline (Game g, int regionID) {
	
}

/// This asks for a hexagon number, and returns the dice number on it.
int getDiceValue (Game g, int regionID) {
	
}

/// This returns who has the most ARCs (I think).
int getMostARCs (Game g) {
	
}

/// This returns who has the most publications (I think).
int getMostPublications (Game g) {
	
}

/// This returns the turn number.
int getTurnNumber (Game g) {
	
}

/// This returns whose turn it is.
int getWhoseTurn (Game g) {
	
}

/// This asks for a path to a vertex, and returns what is on it.
int getCampus(Game g, path pathToVertex) {
	
}

/// This asks for a path to an edge, and returns what is on it.
int getARC(Game g, path pathToEdge) {
	
}

/// This asks for a action, and returns TRUE if you can do it, or FALSE
/// if you can't.
// returns TRUE if it is legal for the current
// player to make the specified action, FALSE otherwise.
//
// "legal" means everything is legal: 
//   * that the action code is a valid action code which is legal to 
//     be made at this time
//   * that any path is well formed and legal ie consisting only of 
//     the legal direction characters and of a legal length, 
//     and which does not leave the island into the sea at any stage.
//   * that disciplines mentioned in any retraining actions are valid 
//     discipline numbers, and that the university has sufficient
//     students of the correct type to perform the retraining
//
// eg when placing a campus consider such things as: 
//   * is the path a well formed legal path 
//   * does it lead to a vacent vertex?
//   * under the rules of the game are they allowed to place a 
//     campus at that vertex?  (eg is it adjacent to one of their ARCs?)
//   * does the player have the 4 specific students required to pay for 
//     that campus?
// It is not legal to make any action during Terra Nullis ie 
// before the game has started.
// It is not legal for a player to make the moves OBTAIN_PUBLICATION 
// or OBTAIN_IP_PATENT (they can make the move START_SPINOFF)
// you can assume that any pths passed in are NULL terminated strings.
int isLegalAction (Game g, action a) {
	
}

/// These are getters for specific player data.

/// This asks for a player, and returns how many KPI points they have.
int getKPIpoints (Game g, int player) {
	
}

/// This asks for a player, and returns how many ARCs they have.
int getARCs (Game g, int player) {
	
}

/// This asks for a player, and returns how many GO8s they have.
int getGO8s (Game g, int player) {
	
}

/// This asks for a player, and returns how many campuses they have.
int getCampuses (Game g, int player) {
	
}

/// This asks for a player, and returns how many IP patents they have.
int getIPs (Game g, int player) {
	
}

/// This asks for a player, and returns how many publications they have.
int getPublications (Game g, int player) {
	
}

/// This asks for a player and a resource type, and returns how many
/// of that they have.
int getStudents (Game g, int player, int discipline) {
	
}

/// This asks for a player, and two types of resources, and returns how
/// many of one type of resource is used to convert to another type.
int getExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo) {
	
}
