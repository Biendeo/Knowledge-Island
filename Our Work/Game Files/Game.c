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

/// These are the "setters". Basically, when the game starts, these are
/// the values that are used to initialise the data.
/// Each array must be "NUM_REGIONS" long.
/// There's a "#defined" array, that is then stored in an actual array,
/// which then is used to start the game creation function.
// Thomas: I figured it out, it's the default map layout.
/*
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
*/

/// When the game initalises, you store these numbers into variables,
/// and then pass that into the initialise function.
// INCOMPLETE
Game newGame (int discipline[], int dice[]) {
	Game g;
	// From here on out, we initialise every other value in our struct.
	
	return g;
}

/// This frees the game when you're done. THIS IS IMPORTANT.
void disposeGame (Game g) {
	free(g);
}

/// This does an action the user inputs. I guess the AI will jump
/// directy to this step on his turn.
// INCOMPLETE
void makeAction (Game g, action a) {
	
}

/// This advances the game to the next turn. It increases the turn
/// number, and gives a dice roll.
// advance the game to the next turn, 
// assuming that the dice has just been rolled and produced diceScore
// the game starts in turn -1 (we call this state "Terra Nullis") and 
// moves to turn 0 as soon as the first dice is thrown. 
// INCOMPLETE
void throwDice (Game g, int diceScore) {
	
}

/// These are the "getter" functions. They return something based on
/// what you tell them.

/// This asks for a hexagon number, and returns what kind of resource
/// it is.
int getDiscipline (Game g, int regionID) {
	int discipline = g->discipline[regionID];
	return discipline;
}

/// This asks for a hexagon number, and returns the dice number on it.
int getDiceValue (Game g, int regionID) {
	int diceValue = g->dice[regionID];
	return diceValue;	
}

/// This returns who has the most ARCs (I think).
int getMostARCs (Game g) {
	int returnPlayer = VACANT_ARC;
	int p1ARCs = g->p1.ARCs;
	int p2ARCs = g->p2.ARCs;
	int p3ARCs = g->p3.ARCs;
	
	if (p1ARCs > p2ARCs) {
		returnPlayer = ARC_A;
	} else if (p1ARCs < p2ARCs) {
		returnPlayer = ARC_B
	}
	
	if (returnPlayer == ARC_A) {
		if (p1ARCs > p3ARCs) {
			returnPlayer = ARC_A;
		} else if (p1ARCs < p3ARCs) {
			returnPlayer = ARC_C;
		} else {
			returnPlayer = VACANT_ARC;
		}
	} else {
		if (p2ARCs > p3ARCs) {
			returnPlayer = ARC_B;
		} else if (p2ARCs < p3ARCs) {
			returnPlayer = ARC_C;
		} else {
			returnPlayer = VACANT_ARC;
		}
	}
	
	return returnPlayer;
}

/// This returns who has the most publications (papers).
int getMostPublications (Game g) {
	int returnPlayer = VACANT_ARC;
	int p1papers = g->p1.papers;
	int p2papers = g->p2.papers;
	int p3papers = g->p3.papers;
	
	if (p1papers > p2papers) {
		returnPlayer = ARC_A;
	} else if (p1papers < p2papers) {
		returnPlayer = ARC_B
	}
	
	if (returnPlayer == ARC_A) {
		if (p1papers > p3papers) {
			returnPlayer = ARC_A;
		} else if (p1papers < p3papers) {
			returnPlayer = ARC_C;
		} else {
			returnPlayer = VACANT_ARC;
		}
	} else {
		if (p2papers > p3papers) {
			returnPlayer = ARC_B;
		} else if (p2papers < p3papers) {
			returnPlayer = ARC_C;
		} else {
			returnPlayer = VACANT_ARC;
		}
	}
	
	return returnPlayer;	
}

/// This returns the turn number.
int getTurnNumber (Game g) {
	int turnNumber = g->turnNumber;
	return turnNumber;
}

/// This returns whose turn it is.
int getWhoseTurn (Game g) {
	int whoseTurn = g->whoseTurn;
	return whoseTurn;
}

/// This asks for a path to a vertex, and returns what is on it.
// INCOMPLETE
int getCampus(Game g, path pathToVertex) {
	int whatCampus = VACANT_ARC;
	
	return whatCampus;
}

/// This asks for a path to an edge, and returns what is on it.
// INCOMPLETE
int getARC(Game g, path pathToEdge) {
	int whatARC = VACANT_ARC;
	
	return whatARC;
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
// INCOMPLETE
int isLegalAction (Game g, action a) {
	int isLegalAction = FALSE;
	// In here will be a bunch of checks for the action.
	
	return isLegalAction;
}

/// These are getters for specific player data.

/// This asks for a player, and returns how many KPI points they have.
int getKPIpoints (Game g, int player) {
	// If this is calculated rather than stored, then it will need to
	// be expanded.
	int howManyKPIs = 0;
	
	if (player == ARC_A) {
		howManyKPIs = g->p1.KPIs;
	} else if (player == ARC_B) {
		howManyKPIs = g->p2.KPIs;
	} else if (player == ARC_C) {
		howManyKPIs = g->p3.KPIs;
	}
	
	return howManyKPIs;
}

/// This asks for a player, and returns how many ARCs they have.
int getARCs (Game g, int player) {
	int howManyARCs = 0;
	
	if (player == ARC_A) {
		howManyARCs = g->p1.ARCs;
	} else if (player == ARC_B) {
		howManyARCs = g->p2.ARCs;
	} else if (player == ARC_C) {
		howManyARCs = g->p3.ARCs;
	}
	
	return howManyARCs;
}

/// This asks for a player, and returns how many GO8s they have.
int getGO8s (Game g, int player) {
	int howManyG08s = 0;
	
	if (player == ARC_A) {
		howManyG08s = g->p1.G08s;
	} else if (player == ARC_B) {
		howManyG08s = g->p2.G08s;
	} else if (player == ARC_C) {
		howManyG08s = g->p3.G08s;
	}
	
	return howManyG08s;
}

/// This asks for a player, and returns how many campuses they have.
int getCampuses (Game g, int player) {
		int howManyCampuses = 0;
	
	if (player == ARC_A) {
		howManyCampuses = g->p1.campuses;
	} else if (player == ARC_B) {
		howManyCampuses = g->p2.campuses;
	} else if (player == ARC_C) {
		howManyCampuses = g->p3.campuses;
	}
	
	return howManyCampuses;
}

/// This asks for a player, and returns how many IP patents they have.
int getIPs (Game g, int player) {
	int howManyPatents = 0;
	
	if (player == ARC_A) {
		howManyPatents = g->p1.patents;
	} else if (player == ARC_B) {
		howManyPatents = g->p2.patents;
	} else if (player == ARC_C) {
		howManyPatents = g->p3.patents;
	}
	
	return howManyPatents;
}

/// This asks for a player, and returns how many publications they have.
int getPublications (Game g, int player) {
		int howManyPapers = 0;
	
	if (player == ARC_A) {
		howManyPapers = g->p1.papers;
	} else if (player == ARC_B) {
		howManyPapers = g->p2.papers;
	} else if (player == ARC_C) {
		howManyPapers = g->p3.papers;
	}
	
	return howManyPapers;
}

/// This asks for a player and a resource type, and returns how many
/// of that they have.
int getStudents (Game g, int player, int discipline) {
	int howManyStudents = 0;
	
	if (player == ARC_A) {
		if (discipline == STUDENT_THD) {
			howManyStudents = g->p1.THDs;
		} else if (discipline == STUDENT_BPS) {
			howManyStudents = g->p1.BPSs;
		} else if (discipline == STUDENT_BQN) {
			howManyStudents = g->p1.BQNs;
		} else if (discipline == STUDENT_MJ) {
			howManyStudents = g->p1.MJs;
		} else if (discipline == STUDENT_MTV) {
			howManyStudents = g->p1.MTVs;
		} else if (discipline == STUDENT_MMONEY) {
			howManyStudents = g->p1.MMONEYs;
		}
	} else if (player == ARC_B) {
		if (discipline == STUDENT_THD) {
			howManyStudents = g->p2.THDs;
		} else if (discipline == STUDENT_BPS) {
			howManyStudents = g->p2.BPSs;
		} else if (discipline == STUDENT_BQN) {
			howManyStudents = g->p2.BQNs;
		} else if (discipline == STUDENT_MJ) {
			howManyStudents = g->p2.MJs;
		} else if (discipline == STUDENT_MTV) {
			howManyStudents = g->p2.MTVs;
		} else if (discipline == STUDENT_MMONEY) {
			howManyStudents = g->p2.MMONEYs;
		}
	} else if (player == ARC_C) {
		if (discipline == STUDENT_THD) {
			howManyStudents = g->p3.THDs;
		} else if (discipline == STUDENT_BPS) {
			howManyStudents = g->p3.BPSs;
		} else if (discipline == STUDENT_BQN) {
			howManyStudents = g->p3.BQNs;
		} else if (discipline == STUDENT_MJ) {
			howManyStudents = g->p3.MJs;
		} else if (discipline == STUDENT_MTV) {
			howManyStudents = g->p3.MTVs;
		} else if (discipline == STUDENT_MMONEY) {
			howManyStudents = g->p3.MMONEYs;
		}
	}
	
	return howManyStudents;
}

/// This asks for a player, and two types of resources, and returns how
/// many of one type of resource is used to convert to another type.
int getExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo) {
	int exchangeRate = 3;
	// I think this is 3 for everything. We could add a weird formula
	// or something, but for now it'll just be 3. This doesn't use any
	// data yet.
	return exchangeRate;
}
