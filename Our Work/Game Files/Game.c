/*
	WHAT NEEDS TO BE DONE:
	makeAction();
		Compute what the user has input, and do it. 
	throwDice();
		We need to compute paths to buildings, and add resources based
		on them.
	convertPath();
		We need to convert a path to a co-ordinate.
*/

// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 12/05/2015
// This program is the underlying functions of Knowledge Island.

/// This is the co-ordinate storage system. Refer to the co-ordinate
/// diagram to determine where a co-ordinate is on the board.
// Thomas: I will make a function that converts a path to a co-ord.
// Since nothing returns a path, we can use this to store the location
// of objects.

#define NUM_EDGES 72
#define NUM_VERTICES 54

#define NOT_FOUND -1

typedef struct _co-ordinate {
	char x;
	char y;
} Coord;

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
	int GO8s;
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

/// This stores the data of a single ARC grant.
typedef struct _edge {
	/// This stores the start and end positions of the road.
	coord start;
	coord end;
	
	/// This stores what player this building belongs to.
	int type;
} Edge;

/// This stores the data of a single campus.
typedef struct _vertex {
	/// This stores the position of the campus.
	coord start;
	
	/// This stores what player this belongs to (as well as the type).
	int type;
} Vertex;

typedef struct _game {
	/// This stores what turn the game is up to. In game.h, they start
	/// at -1, so this has to be signed.
	int turnNumber;
	
	/// This stores whose turn it is.
	int whoseTurn;
	
	/// This stores the disciplines and dice layout of the board.
	int discipline[NUM_REGIONS];
	int dice[NUM_REGIONS];
	
	/// This stores the exchange rate of resources. It should be stored
	/// somewhere at least.
	int exchangeRate;
	
	/// This stores all the data of the possible buildings on the board.
	// Thomas: Are we cool with sorting them like this? I think it'll be
	// convenient for accessing either campuses or ARCs.
	Edge ARC[NUM_EDGES];
	Vertex campus[NUM_VERTICES];
	
	/// These store specific data about each player. Their info is
	/// above.
	Player p1;
	Player p2;
	Player p3;
} * Game;

/// These are our custom-defined functions. They are at the bottom of
/// the whole file.
Coord convertPath(path path);
short findCampus(Game g, path pathToEdge);
short findARC(Game g, path pathToEdge);
void initialiseVertices(Game g);
void initialiseEdges(Game g);

/// These are the "setters". Basically, when the game starts, these are
/// the values that are used to initialise the data.
/// Each array must be "NUM_REGIONS" long.
/// There's a "#defined" array, that is then stored in an actual array,
/// which then is used to start the game creation function.

/// When the game initalises, you store these numbers into variables,
/// and then pass that into the initialise function.
// MIGHT NEED TWEAKING
Game newGame (int discipline[], int dice[]) {
	Game g = malloc(sizeof(Game));
	/// This is used to fill out the discipline and dice layouts.
	short pos = 0;
	short pathpos = 0;
	
	g->turnNumber = -1;
	g->whoseTurn = 0;
	
	while (pos < 19) {
		g->discipline[pos] = discipline[pos];
		g->dice[pos] = dice[pos];
		pos++;
	}
	
	g->exchangeRate = 3;
	
	/// Now we set all the building data.
	// We need to make a function that assigns the starts and ends, and
	// just return void. While order won't matter, every value needs to
	// be assigned.
	pos = 0;
	while (pos < NUM_EDGES) {
		if (pos < NUM_VERTICES) {
			g->campus[pos].start.x = 0;
			g->campus[pos].start.y = 0;
			g->campus[pos].type = 0;
		}
		g->ARC[pos].start.x = 0;
		g->ARC[pos].start.y = 0;
		g->ARC[pos].end.x = 0;
		g->ARC[pos].end.y = 0;
		g->ARC[pos].type = 0;
		pos++;
	}
	
	/// Now the player data.
	// Some of this we can set right away.
	g->p1.playerID = UNI_A;
	g->p1.KPIs = 0;
	g->p1.ARCs = 0;
	g->p1.campuses = 0;
	g->p1.GO8s = 0;
	g->p1.patents = 0;
	g->p1.papers = 0;
	g->p1.THDs = 0;
	g->p1.BPSs = 0;
	g->p1.BQNs = 0;
	g->p1.MJs = 0;
	g->p1.MTVs = 0;
	g->p1.MMONEYs = 0;
	g->p2.playerID = UNI_A;
	g->p2.KPIs = 0;
	g->p2.ARCs = 0;
	g->p2.campuses = 0;
	g->p2.GO8s = 0;
	g->p2.patents = 0;
	g->p2.papers = 0;
	g->p2.THDs = 0;
	g->p2.BPSs = 0;
	g->p2.BQNs = 0;
	g->p2.MJs = 0;
	g->p2.MTVs = 0;
	g->p2.MMONEYs = 0;
	g->p3.playerID = UNI_C;
	g->p3.KPIs = 0;
	g->p3.ARCs = 0;
	g->p3.campuses = 0;
	g->p3.GO8s = 0;
	g->p3.patents = 0;
	g->p3.papers = 0;
	g->p3.THDs = 0;
	g->p3.BPSs = 0;
	g->p3.BQNs = 0;
	g->p3.MJs = 0;
	g->p3.MTVs = 0;
	g->p3.MMONEYs = 0;
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
/// number, and computes a dice roll given.
// INCOMPLETE
void throwDice (Game g, int diceScore) {
	/// Firstly, we increase the turn.
	g->turnNumber++;
	g->whoseTurn++;
	if (g->whoseTurn > NUM_UNIS) {
		g->whoseTurn = UNI_A;
	}
	
	/// Then we give everyone resources based on the dice roll.
	// ADD 
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
int getCampus(Game g, path pathToVertex) {
	int whatCampus = VACANT_ARC;
	
	short ID = findCampus(g, pathToVertex);
	
	if (ID != NOT_FOUND) {
		whatArc = g->campus[ID].type;
	}
	return whatCampus;
}

/// This asks for a path to an edge, and returns what is on it.int getARC(Game g, path pathToEdge) {
	int whatARC = VACANT_ARC;
	short pathpos = 0;
	short arrayPos = 0;
	
	// findARC returns what member of the array is that specific ARC.
	short ID = findARC(g, pathToEdge);
	
	if (ID != NOT_FOUND) {
		whatArc = g->ARC[ID].type;
	}
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
	int howManyGO8s = 0;
	
	if (player == ARC_A) {
		howManyGO8s = g->p1.GO8s;
	} else if (player == ARC_B) {
		howManyGO8s = g->p2.GO8s;
	} else if (player == ARC_C) {
		howManyGO8s = g->p3.GO8s;
	}
	
	return howManyGO8s;
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

/// This function converts a path from the starting vertex into a
/// triangle co-ordinate. Refer to the diagram to check these values.
// INCOMPLETE
Coord convertPath(path path) {
	Coord coord;
	
	return returnCoord;
}

/// This function compares a coordinate with the campuses stored in
/// memory, and returns the array position of the matching one, or
/// NOT_FOUND if no match was found.
short findCampus(Game g, Coord coord) {
	short ID = NOT_FOUND;
	short pos = 0;
	
	/// Every vertex is checked until the given co-ordinate's x and y
	/// values match that vertex's. Then, it breaks and returns that ID.
	while ((pos < NUM_VERTICES) && (ID == NOT_FOUND)) {
		if ((coord.x == g->campus[pos].start.x) &&
		    (coord.y == g->campus[pos].start.y)) {
			ID = pos;
		}
		pos++;
	}
	
	return ID;
}

/// This is the same as above, just with two coords for edges.
short findARC(Game g, Coord start, Coord end) {
	short ID = NOT_FOUND;
	short pos = 0;
	
	/// Every edge is checked until the given co-ordinate's x and y
	/// values match that edge's. Then, it breaks and returns that ID.
	/// It checks if either of the ends of an edge match
	while ((pos < NUM_EDGES) && (ID == NOT_FOUND)) {
		if ((start.x == g->campus[pos].start.x) &&
		    (start.y == g->campus[pos].start.y)) {
			if ((end.x == g->campus[pos].end.x) &&
		    (end.y == g->campus[pos].end.y)) {
				ID = pos;
			}
		} else if ((start.x == g->campus[pos].end.x) &&
		           (start.y == g->campus[pos].end.y)) {
				if ((end.x == g->campus[pos].start.x) &&
		            (end.y == g->campus[pos].start.y)) {
					ID = pos;	
				}
			}
		pos++;
	}
	
	return ID;
}

void initialiseVertices(Game g) {
	g->ARC[p]
}

void intialiseEdges(Game g) {
	
}