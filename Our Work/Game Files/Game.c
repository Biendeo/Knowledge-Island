/*
	WHAT NEEDS TO BE DONE:
	makeAction();
		Compute what the user has input, and do it.
	throwDice();
		We need to compute paths to buildings, and add resources based
		on them.
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

#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

#define NUM_EDGES 72
#define NUM_VERTICES 54

#define NOT_FOUND -1

#define LEFT 'L'
#define RIGHT 'R'
#define BACK 'B'

typedef struct _coordinate {
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
	Coord start;
	Coord end;

	/// This stores what player this building belongs to.
	int type;
} Edge;

/// This stores the data of a single campus.
typedef struct _vertex {
	/// This stores the position of the campus.
	Coord start;

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
short getCampusID(Game g, path path);
short getARCID(Game g, path path);
short findCampus(Game g, Coord coord);
short findARC(Game g, Coord start, Coord end);
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

	g->turnNumber = -1;
	g->whoseTurn = 0;

	while (pos < 19) {
		g->discipline[pos] = discipline[pos];
		g->dice[pos] = dice[pos];
		pos++;
	}

	g->exchangeRate = 3;

	/// Now we set all the building data.
	/// All the data is initially "flushed".
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

	/// Then, each vertex and edge is assigned a position. These start
	/// from the top-left, and go row-by-row.
	initialiseVertices(g);
	initialiseEdges(g);

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
	if (a.actionCode == PASS) {
		/// We don't do anything.
	} else if (a.actionCode == BUILD_CAMPUS) {
		/// If they build a campus, first we find what vertex ID they
		/// are referring to, then we change it to that player's campus.
		short ID = getCampusID(g, a.destination);
		if (g->whoseTurn == UNI_A) {
			g->campus[ID].type = CAMPUS_A;
		} else if (g->whoseTurn == UNI_B) {
			g->campus[ID].type = CAMPUS_B;
		} else if (g->whoseTurn == UNI_C) {
			g->campus[ID].type = CAMPUS_C;
		}
	} else if (a.actionCode == BUILD_GO8) {
		/// If they build a GO8, first we find what vertex ID they are
		/// referring to, then we change it to that player's GO8.
		short ID = getCampusID(g, a.destination);
		if (g->whoseTurn == UNI_A) {
			g->campus[ID].type = GO8_A;
		} else if (g->whoseTurn == UNI_B) {
			g->campus[ID].type = GO8_B;
		} else if (g->whoseTurn == UNI_C) {
			g->campus[ID].type = GO8_C;
		}
	} else if (a.actionCode == OBTAIN_ARC) {
		/// If they build an ARC, first we find what vertex ID they are
		/// referring to, then we change it to that player's ARC.
		short ID = getARCID(g, a.destination);
		if (g->whoseTurn == UNI_A) {
			g->ARC[ID].type = ARC_A;
		} else if (g->whoseTurn == UNI_B) {
			g->ARC[ID].type = ARC_B;
		} else if (g->whoseTurn == UNI_C) {
			g->ARC[ID].type = ARC_C;
		}
	} else if (a.actionCode == START_SPINOFF) {
		// This doesn't have any other inputs.
	} else if (a.actionCode == OBTAIN_PUBLICATION) {
		// I dunno about this.
	} else if (a.actionCode == OBTAIN_IP_PATENT) {
		// I dunno about this either.
	} else if (a.actionCode == RETRAIN_STUDENTS) {
		// This accepts two discipline types.
	}
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
		returnPlayer = ARC_B;
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
		returnPlayer = ARC_B;
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

	/// We firstly convert the path to a co-ordinate.
	short ID = getCampusID(g, pathToVertex);

	/// If we found a vertex, we return
	if (ID != NOT_FOUND) {
		whatCampus = g->campus[ID].type;
	}

	return whatCampus;
}

/// This asks for a path to an edge, and returns what is on it.
int getARC(Game g, path pathToEdge) {
	int whatARC = VACANT_ARC;
	
	short ID = getARCID(g, pathToEdge);
	
	/// And then get what type is on it.
	if (ID != NOT_FOUND) {
		whatARC = g->ARC[ID].type;
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
	// We need to fill out ALL of these.
	if (a.actionCode == PASS) {
		isLegalAction = TRUE;
	} else if (a.actionCode == BUILD_CAMPUS) {
		// This accepts a path to a vertex.
	} else if (a.actionCode == BUILD_GO8) {
		// This accepts a path to a vertex.
	} else if (a.actionCode == OBTAIN_ARC) {
		// This accepts a path to an edge.
	} else if (a.actionCode == START_SPINOFF) {
		// This doesn't have any other inputs.
	} else if (a.actionCode == OBTAIN_PUBLICATION) {
		// I dunno about this.
	} else if (a.actionCode == OBTAIN_IP_PATENT) {
		// I dunno about this either.
	} else if (a.actionCode == RETRAIN_STUDENTS) {
		// This accepts two discipline types.
	}
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
	
	

	return exchangeRate;
}

/// This function converts a path from the starting vertex into a
/// triangle co-ordinate. Refer to the diagram to check these values.
Coord convertPath(path path) {
	Coord coord;
	/// These are the starting co-ords from the beginning of a path.
	coord.x = 7;
	coord.y = 10;
	/// This is the direction the path is facing.
	/// If the direction value is n then it is facing at (2n+1) o'clock.
	short direction = 2;
	/// This tracks where we are in the path.
	short pos = 0;

	/// When the path ends, we stop moving the co-ordinate.
	while ((path[pos] == LEFT) || (path[pos] == RIGHT) ||
	                              (path[pos] == BACK)) {
		if (direction == 0) {
			if (path[pos] == LEFT) {
				direction = 5;
				coord.y++;
			} else if (path[pos] == RIGHT) {
				direction = 1;
				coord.x++;
			} else if (path[pos] == BACK) {
				direction = 3;
				coord.x--;
				coord.y--;
			}
		} else if (direction == 1) {
			if (path[pos] == LEFT) {
				direction = 0;
				coord.x++;
				coord.y++;
			} else if (path[pos] == RIGHT) {
				direction = 2;
				coord.y--;
			} else if (path[pos] == BACK) {
				direction = 4;
				coord.x--;
			}
		} else if (direction == 2) {
			if (path[pos] == LEFT) {
				direction = 1;
				coord.x++;
			} else if (path[pos] == RIGHT) {
				direction = 3;
				coord.x--;
				coord.y--;
			} else if (path[pos] == BACK) {
				direction = 5;
				coord.y++;
			}
		} else if (direction == 3) {
			if (path[pos] == LEFT) {
				direction = 2;
				coord.y--;
			} else if (path[pos] == RIGHT) {
				direction = 4;
				coord.x--;
			} else if (path[pos] == BACK) {
				direction = 0;
				coord.x++;
				coord.y++;
			}
		} else if (direction == 4) {
			if (path[pos] == LEFT) {
				direction = 3;
				coord.x--;
				coord.y--;
			} else if (path[pos] == RIGHT) {
				direction = 5;
				coord.y++;
			} else if (path[pos] == BACK) {
				direction = 1;
				coord.x++;
			}
		} else if (direction == 5) {
			if (path[pos] == LEFT) {
				direction = 4;
				coord.x--;
			} else if (path[pos] == RIGHT) {
				direction = 0;
				coord.x++;
				coord.y++;
			} else if (path[pos] == BACK) {
				direction = 2;
				coord.y--;
			}
		}
		pos++;
	}

	return coord;
}

short getCampusID(Game g, path path) {
	/// We convert the path to a coord.
	Coord start = convertPath(path);
	/// And then we get its ID.
	short ID = findCampus(g, start);
	
	return ID;
}

short getARCID(Game g, path path) {
	short pathsize = 0;
	/// It's easy to find the end of the ARC.
	Coord end = convertPath(path);

	/// To find the start, we truncate the last term of the path.
	while ((path[pathsize] == 'R') ||
	       (path[pathsize] == 'L') ||
           (path[pathsize] == 'B')) {
		pathsize++;
	}
	pathsize--;
	/// And we replace it with a dummy character.
	path[pathsize] = 0;

	/// That way, the path stops at the beginning.
	Coord start = convertPath(path);

	/// Then, we find which edge is being referred to.
	short ID = findARC(g, start, end);
	
	return ID;
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
		if ((start.x == g->ARC[pos].start.x) &&
		    (start.y == g->ARC[pos].start.y)) {
			if ((end.x == g->ARC[pos].end.x) &&
		    (end.y == g->ARC[pos].end.y)) {
				ID = pos;
			}
		} else if ((start.x == g->ARC[pos].end.x) &&
		           (start.y == g->ARC[pos].end.y)) {
				if ((end.x == g->ARC[pos].start.x) &&
		            (end.y == g->ARC[pos].start.y)) {
					ID = pos;
				}
			}
		pos++;
	}

	return ID;
}

void initialiseVertices(Game g) {
	/// These are arranged by rows.
	g->campus[ 0].start.x = 7;
	g->campus[ 0].start.y = 10;
	g->campus[ 1].start.x = 8;
	g->campus[ 1].start.y = 10;

	g->campus[ 2].start.x = 5;
	g->campus[ 2].start.y = 9;
	g->campus[ 3].start.x = 6;
	g->campus[ 3].start.y = 9;
	g->campus[ 4].start.x = 8;
	g->campus[ 4].start.y = 9;
	g->campus[ 5].start.x = 9;
	g->campus[ 5].start.y = 9;

	g->campus[ 6].start.x = 3;
	g->campus[ 6].start.y = 8;
	g->campus[ 7].start.x = 4;
	g->campus[ 7].start.y = 8;
	g->campus[ 8].start.x = 6;
	g->campus[ 8].start.y = 8;
	g->campus[ 9].start.x = 7;
	g->campus[ 9].start.y = 8;
	g->campus[10].start.x = 9;
	g->campus[10].start.y = 8;
	g->campus[11].start.x = 10;
	g->campus[11].start.y = 8;

	g->campus[12].start.x = 2;
	g->campus[12].start.y = 7;
	g->campus[13].start.x = 4;
	g->campus[13].start.y = 7;
	g->campus[14].start.x = 5;
	g->campus[14].start.y = 7;
	g->campus[15].start.x = 7;
	g->campus[15].start.y = 7;
	g->campus[16].start.x = 8;
	g->campus[16].start.y = 7;
	g->campus[17].start.x = 10;
	g->campus[17].start.y = 7;

	g->campus[18].start.x = 2;
	g->campus[18].start.y = 6;
	g->campus[19].start.x = 3;
	g->campus[19].start.y = 6;
	g->campus[20].start.x = 5;
	g->campus[20].start.y = 6;
	g->campus[21].start.x = 6;
	g->campus[21].start.y = 6;
	g->campus[22].start.x = 8;
	g->campus[22].start.y = 6;
	g->campus[23].start.x = 9;
	g->campus[23].start.y = 6;

	g->campus[24].start.x = 1;
	g->campus[24].start.y = 5;
	g->campus[25].start.x = 3;
	g->campus[25].start.y = 5;
	g->campus[26].start.x = 4;
	g->campus[26].start.y = 5;
	g->campus[27].start.x = 6;
	g->campus[27].start.y = 5;
	g->campus[28].start.x = 7;
	g->campus[28].start.y = 5;
	g->campus[29].start.x = 9;
	g->campus[29].start.y = 5;

	g->campus[30].start.x = 1;
	g->campus[30].start.y = 4;
	g->campus[31].start.x = 2;
	g->campus[31].start.y = 4;
	g->campus[32].start.x = 4;
	g->campus[32].start.y = 4;
	g->campus[33].start.x = 5;
	g->campus[33].start.y = 4;
	g->campus[34].start.x = 7;
	g->campus[34].start.y = 4;
	g->campus[35].start.x = 8;
	g->campus[35].start.y = 4;

	g->campus[36].start.x = 0;
	g->campus[36].start.y = 3;
	g->campus[37].start.x = 2;
	g->campus[37].start.y = 3;
	g->campus[38].start.x = 3;
	g->campus[38].start.y = 3;
	g->campus[39].start.x = 5;
	g->campus[39].start.y = 3;
	g->campus[40].start.x = 6;
	g->campus[40].start.y = 3;
	g->campus[41].start.x = 8;
	g->campus[41].start.y = 3;

	g->campus[42].start.x = 0;
	g->campus[42].start.y = 2;
	g->campus[43].start.x = 1;
	g->campus[43].start.y = 2;
	g->campus[44].start.x = 3;
	g->campus[44].start.y = 2;
	g->campus[45].start.x = 4;
	g->campus[45].start.y = 2;
	g->campus[46].start.x = 6;
	g->campus[46].start.y = 2;
	g->campus[47].start.x = 7;
	g->campus[47].start.y = 2;

	g->campus[46].start.x = 1;
	g->campus[46].start.y = 1;
	g->campus[47].start.x = 2;
	g->campus[47].start.y = 1;
	g->campus[48].start.x = 4;
	g->campus[48].start.y = 1;
	g->campus[49].start.x = 5;
	g->campus[49].start.y = 1;

	g->campus[50].start.x = 2;
	g->campus[50].start.y = 0;
	g->campus[51].start.x = 3;
	g->campus[51].start.y = 0;
}

void initialiseEdges(Game g) {
	/// These are arranged by rows.
	/// Firstly, horizontal edges.
	g->ARC[ 0].start.x = 7;
	g->ARC[ 0].start.y = 10;
	g->ARC[ 0].end.x   = 8;
	g->ARC[ 0].end.y   = 10;

	g->ARC[ 1].start.x = 5;
	g->ARC[ 1].start.y = 9;
	g->ARC[ 1].end.x   = 6;
	g->ARC[ 1].end.y   = 9;
	g->ARC[ 2].start.x = 8;
	g->ARC[ 2].start.y = 9;
	g->ARC[ 2].end.x   = 9;
	g->ARC[ 2].end.y   = 9;

	g->ARC[ 3].start.x = 3;
	g->ARC[ 3].start.y = 8;
	g->ARC[ 3].end.x   = 4;
	g->ARC[ 3].end.y   = 8;
	g->ARC[ 4].start.x = 6;
	g->ARC[ 4].start.y = 8;
	g->ARC[ 4].end.x   = 7;
	g->ARC[ 4].end.y   = 8;
	g->ARC[ 5].start.x = 9;
	g->ARC[ 5].start.y = 8;
	g->ARC[ 5].end.x   = 10;
	g->ARC[ 5].end.y   = 8;

	g->ARC[ 6].start.x = 4;
	g->ARC[ 6].start.y = 7;
	g->ARC[ 6].end.x   = 5;
	g->ARC[ 6].end.y   = 7;
	g->ARC[ 7].start.x = 7;
	g->ARC[ 7].start.y = 7;
	g->ARC[ 7].end.x   = 8;
	g->ARC[ 7].end.y   = 7;

	g->ARC[ 8].start.x = 2;
	g->ARC[ 8].start.y = 6;
	g->ARC[ 8].end.x   = 3;
	g->ARC[ 8].end.y   = 6;
	g->ARC[ 9].start.x = 5;
	g->ARC[ 9].start.y = 6;
	g->ARC[ 9].end.x   = 6;
	g->ARC[ 9].end.y   = 6;
	g->ARC[10].start.x = 8;
	g->ARC[10].start.y = 6;
	g->ARC[10].end.x   = 9;
	g->ARC[10].end.y   = 6;

	g->ARC[11].start.x = 3;
	g->ARC[11].start.y = 5;
	g->ARC[11].end.x   = 4;
	g->ARC[11].end.y   = 5;
	g->ARC[12].start.x = 6;
	g->ARC[12].start.y = 5;
	g->ARC[12].end.x   = 7;
	g->ARC[12].end.y   = 5;

	g->ARC[13].start.x = 1;
	g->ARC[13].start.y = 4;
	g->ARC[13].end.x   = 2;
	g->ARC[13].end.y   = 4;
	g->ARC[14].start.x = 4;
	g->ARC[14].start.y = 4;
	g->ARC[14].end.x   = 5;
	g->ARC[14].end.y   = 4;
	g->ARC[15].start.x = 7;
	g->ARC[15].start.y = 4;
	g->ARC[15].end.x   = 8;
	g->ARC[15].end.y   = 4;

	g->ARC[16].start.x = 2;
	g->ARC[16].start.y = 3;
	g->ARC[16].end.x   = 3;
	g->ARC[16].end.y   = 3;
	g->ARC[17].start.x = 5;
	g->ARC[17].start.y = 3;
	g->ARC[17].end.x   = 6;
	g->ARC[17].end.y   = 3;

	g->ARC[18].start.x = 0;
	g->ARC[18].start.y = 2;
	g->ARC[18].end.x   = 1;
	g->ARC[18].end.y   = 2;
	g->ARC[19].start.x = 3;
	g->ARC[19].start.y = 2;
	g->ARC[19].end.x   = 4;
	g->ARC[19].end.y   = 2;
	g->ARC[20].start.x = 6;
	g->ARC[20].start.y = 2;
	g->ARC[20].end.x   = 7;
	g->ARC[20].end.y   = 2;

	g->ARC[21].start.x = 1;
	g->ARC[21].start.y = 1;
	g->ARC[21].end.x   = 2;
	g->ARC[21].end.y   = 1;
	g->ARC[22].start.x = 4;
	g->ARC[22].start.y = 1;
	g->ARC[22].end.x   = 5;
	g->ARC[22].end.y   = 1;

	g->ARC[23].start.x = 2;
	g->ARC[23].start.y = 0;
	g->ARC[23].end.x   = 3;
	g->ARC[23].end.y   = 0;

	/// Secondly, edges that go up-right.
	g->ARC[24].start.x = 6;
	g->ARC[24].start.y = 9;
	g->ARC[24].end.x   = 7;
	g->ARC[24].end.y   = 10;

	g->ARC[25].start.x = 4;
	g->ARC[25].start.y = 8;
	g->ARC[25].end.x   = 5;
	g->ARC[25].end.y   = 9;
	g->ARC[26].start.x = 7;
	g->ARC[26].start.y = 8;
	g->ARC[26].end.x   = 8;
	g->ARC[26].end.y   = 9;

	g->ARC[27].start.x = 2;
	g->ARC[27].start.y = 7;
	g->ARC[27].end.x   = 3;
	g->ARC[27].end.y   = 8;
	g->ARC[28].start.x = 5;
	g->ARC[28].start.y = 7;
	g->ARC[28].end.x   = 6;
	g->ARC[28].end.y   = 8;
	g->ARC[29].start.x = 8;
	g->ARC[29].start.y = 7;
	g->ARC[29].end.x   = 9;
	g->ARC[29].end.y   = 8;

	g->ARC[30].start.x = 3;
	g->ARC[30].start.y = 6;
	g->ARC[30].end.x   = 4;
	g->ARC[30].end.y   = 7;
	g->ARC[31].start.x = 6;
	g->ARC[31].start.y = 6;
	g->ARC[31].end.x   = 7;
	g->ARC[31].end.y   = 7;
	g->ARC[32].start.x = 9;
	g->ARC[32].start.y = 6;
	g->ARC[32].end.x   = 10;
	g->ARC[32].end.y   = 7;

	g->ARC[33].start.x = 1;
	g->ARC[33].start.y = 5;
	g->ARC[33].end.x   = 2;
	g->ARC[33].end.y   = 6;
	g->ARC[34].start.x = 4;
	g->ARC[34].start.y = 5;
	g->ARC[34].end.x   = 5;
	g->ARC[34].end.y   = 6;
	g->ARC[35].start.x = 7;
	g->ARC[35].start.y = 5;
	g->ARC[35].end.x   = 8;
	g->ARC[35].end.y   = 6;

	g->ARC[36].start.x = 2;
	g->ARC[36].start.y = 4;
	g->ARC[36].end.x   = 3;
	g->ARC[36].end.y   = 5;
	g->ARC[37].start.x = 5;
	g->ARC[37].start.y = 4;
	g->ARC[37].end.x   = 6;
	g->ARC[37].end.y   = 5;
	g->ARC[38].start.x = 8;
	g->ARC[38].start.y = 4;
	g->ARC[38].end.x   = 9;
	g->ARC[38].end.y   = 5;

	g->ARC[39].start.x = 0;
	g->ARC[39].start.y = 3;
	g->ARC[39].end.x   = 1;
	g->ARC[39].end.y   = 4;
	g->ARC[40].start.x = 3;
	g->ARC[40].start.y = 3;
	g->ARC[40].end.x   = 4;
	g->ARC[40].end.y   = 4;
	g->ARC[41].start.x = 6;
	g->ARC[41].start.y = 3;
	g->ARC[41].end.x   = 7;
	g->ARC[41].end.y   = 4;

	g->ARC[42].start.x = 1;
	g->ARC[42].start.y = 2;
	g->ARC[42].end.x   = 2;
	g->ARC[42].end.y   = 3;
	g->ARC[43].start.x = 4;
	g->ARC[43].start.y = 2;
	g->ARC[43].end.x   = 5;
	g->ARC[43].end.y   = 3;
	g->ARC[44].start.x = 7;
	g->ARC[44].start.y = 2;
	g->ARC[44].end.x   = 8;
	g->ARC[44].end.y   = 3;

	g->ARC[45].start.x = 2;
	g->ARC[45].start.y = 1;
	g->ARC[45].end.x   = 3;
	g->ARC[45].end.y   = 2;
	g->ARC[46].start.x = 5;
	g->ARC[46].start.y = 1;
	g->ARC[46].end.x   = 6;
	g->ARC[46].end.y   = 2;

	g->ARC[47].start.x = 3;
	g->ARC[47].start.y = 0;
	g->ARC[47].end.x   = 4;
	g->ARC[47].end.y   = 1;

	/// Finally, edges that go down-right.
	g->ARC[48].start.x = 8;
	g->ARC[48].start.y = 10;
	g->ARC[48].end.x   = 8;
	g->ARC[48].end.y   = 9;

	g->ARC[49].start.x = 6;
	g->ARC[49].start.y = 9;
	g->ARC[49].end.x   = 6;
	g->ARC[49].end.y   = 8;
	g->ARC[50].start.x = 9;
	g->ARC[50].start.y = 9;
	g->ARC[50].end.x   = 9;
	g->ARC[50].end.y   = 8;

	g->ARC[51].start.x = 4;
	g->ARC[51].start.y = 8;
	g->ARC[51].end.x   = 4;
	g->ARC[51].end.y   = 7;
	g->ARC[52].start.x = 7;
	g->ARC[52].start.y = 8;
	g->ARC[52].end.x   = 7;
	g->ARC[52].end.y   = 7;
	g->ARC[53].start.x = 10;
	g->ARC[53].start.y = 8;
	g->ARC[53].end.x   = 10;
	g->ARC[53].end.y   = 7;

	g->ARC[54].start.x = 2;
	g->ARC[54].start.y = 7;
	g->ARC[54].end.x   = 2;
	g->ARC[54].end.y   = 6;
	g->ARC[55].start.x = 5;
	g->ARC[55].start.y = 7;
	g->ARC[55].end.x   = 5;
	g->ARC[55].end.y   = 6;
	g->ARC[56].start.x = 8;
	g->ARC[56].start.y = 7;
	g->ARC[56].end.x   = 8;
	g->ARC[56].end.y   = 6;

	g->ARC[57].start.x = 3;
	g->ARC[57].start.y = 6;
	g->ARC[57].end.x   = 3;
	g->ARC[57].end.y   = 5;
	g->ARC[58].start.x = 6;
	g->ARC[58].start.y = 6;
	g->ARC[58].end.x   = 6;
	g->ARC[58].end.y   = 5;
	g->ARC[59].start.x = 9;
	g->ARC[59].start.y = 6;
	g->ARC[59].end.x   = 9;
	g->ARC[59].end.y   = 5;

	g->ARC[60].start.x = 1;
	g->ARC[60].start.y = 5;
	g->ARC[60].end.x   = 1;
	g->ARC[60].end.y   = 4;
	g->ARC[61].start.x = 4;
	g->ARC[61].start.y = 5;
	g->ARC[61].end.x   = 4;
	g->ARC[61].end.y   = 4;
	g->ARC[62].start.x = 7;
	g->ARC[62].start.y = 5;
	g->ARC[62].end.x   = 7;
	g->ARC[62].end.y   = 4;

	g->ARC[63].start.x = 2;
	g->ARC[63].start.y = 4;
	g->ARC[63].end.x   = 2;
	g->ARC[63].end.y   = 3;
	g->ARC[64].start.x = 5;
	g->ARC[64].start.y = 4;
	g->ARC[64].end.x   = 5;
	g->ARC[64].end.y   = 3;
	g->ARC[65].start.x = 8;
	g->ARC[65].start.y = 4;
	g->ARC[65].end.x   = 8;
	g->ARC[65].end.y   = 3;

	g->ARC[66].start.x = 0;
	g->ARC[66].start.y = 3;
	g->ARC[66].end.x   = 0;
	g->ARC[66].end.y   = 2;
	g->ARC[67].start.x = 3;
	g->ARC[67].start.y = 3;
	g->ARC[67].end.x   = 3;
	g->ARC[67].end.y   = 2;
	g->ARC[68].start.x = 6;
	g->ARC[68].start.y = 3;
	g->ARC[68].end.x   = 6;
	g->ARC[68].end.y   = 2;

	g->ARC[69].start.x = 1;
	g->ARC[69].start.y = 2;
	g->ARC[69].end.x   = 1;
	g->ARC[69].end.y   = 1;
	g->ARC[70].start.x = 4;
	g->ARC[70].start.y = 2;
	g->ARC[70].end.x   = 4;
	g->ARC[70].end.y   = 1;

	g->ARC[71].start.x = 2;
	g->ARC[71].start.y = 1;
	g->ARC[71].end.x   = 2;
	g->ARC[71].end.y   = 0;
}