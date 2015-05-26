// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 19/05/2015
// This is our AI for the Knowledge Island project.

// A lot of this was extracted from our Game.c, so the documentation may
// not be completely relevant.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define NUM_EDGES 72
#define NUM_VERTICES 54

#define PERFORM_SPINOFF 1
#define MAKE_CAMPUS 2
#define MAKE_GO8 3
#define MAKE_ARC 4

#define NOT_FOUND -1

#define LEFT  'L'
#define RIGHT 'R'
#define BACK  'B'

typedef struct _coordinate {
	char x;
	char y;
} Coord;

/// This stores specific data about a player. Just have three of them
/// in _game.
typedef struct _player {
	/// This stores the ID of the player.
	int playerID;
	
	/// This stores the KPI points of each player.
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

typedef struct _data {
	/// This stores what turn the game is up to. In game.h, they start
	/// at -1, so this has to be signed.
	int turnNumber;

	/// This stores whose turn it is.
	int whoseTurn;

	/// This stores the disciplines and dice layout of the board.
	int discipline[NUM_REGIONS];
	int dice[NUM_REGIONS];

	/// This stores which player has the most ARCs and papers. When
	/// checking who has the most, this updates. If it's a tie for who
	/// has the most, this says who previously held it.
	int mostARCs;
	int mostPapers;
	
	/// This stores all the data of the possible buildings on the board.
	Edge ARC[NUM_EDGES];
	Vertex campus[NUM_VERTICES];

	/// These store specific data about each player. Their info is
	/// above.
	Player p1;
	Player p2;
	Player p3;
} * Data;

Data readGameData(Game g);
void flushPath (path destination);
void convertVertex(Data d, path destination, Coord start);
void convertEdge(Data d, path destination, Coord start, Coord end);
short searchForCampus(Data d, Coord coord);
short searchForARC(Data d, Coord start, Coord end);
void checkValidPositions(Data d, int player, char validCampuses[], char validGO8s[], char validARCs[]);
short validCampusPositions(Data d, int player, short ID);
short validARCPositions(Data d, int player, short ID);
void readInitialiseVertices(Data d);
void readInitialiseEdges(Data d);

action decideAction (Game g) {
	action nextAction;
	
	/// Firstly, the bot reads in all the data of the board.
	Data d = readGameData(g);
	
	/// It then stores what values are its own from here.
	short iAmPlayer = d->whoseTurn;
	short myARCs = 0;
	short myCampuses = 0;
	short myGO8s = 0;
	// short myPatents = 0;
	// short myPapers = 0;
	short myKPIs = 0;
	// short myTHDs = 0;
	short myBPSs = 0;
	short myBQNs = 0;
	short myMJs = 0;
	short myMTVs = 0;
	short myMMONEYs = 0;
	if (iAmPlayer == UNI_A) {
		myARCs = d->p1.ARCs;
		myCampuses = d->p1.campuses;
		myGO8s = d->p1.GO8s;
		// myPatents = d->p1.patents;
		// myPapers = d->p1.papers;
		myKPIs = d->p1.KPIs;
		// myTHDs = d->p1.THDs;
		myBPSs = d->p1.BPSs;
		myBQNs = d->p1.BQNs;
		myMJs = d->p1.MJs;
		myMTVs = d->p1.MTVs;
		myMMONEYs = d->p1.MMONEYs;
	} else if (iAmPlayer == UNI_B) {
		myARCs = d->p2.ARCs;
		myCampuses = d->p2.campuses;
		myGO8s = d->p2.GO8s;
		// myPatents = d->p2.patents;
		// myPapers = d->p2.papers;
		myKPIs = d->p2.KPIs;
		// myTHDs = d->p2.THDs;
		myBPSs = d->p2.BPSs;
		myBQNs = d->p2.BQNs;
		myMJs = d->p2.MJs;
		myMTVs = d->p2.MTVs;
		myMMONEYs = d->p2.MMONEYs;
	} else if (iAmPlayer == UNI_C) {
		myARCs = d->p3.ARCs;
		myCampuses = d->p3.campuses;
		myGO8s = d->p3.GO8s;
		// myPatents = d->p3.patents;
		// myPapers = d->p3.papers;
		myKPIs = d->p3.KPIs;
		// myTHDs = d->p3.THDs;
		myBPSs = d->p3.BPSs;
		myBQNs = d->p3.BQNs;
		myMJs = d->p3.MJs;
		myMTVs = d->p3.MTVs;
		myMMONEYs = d->p3.MMONEYs;
	}
	
	/// Here's a splash so we know whose AI this is. It will only put
	/// this message once (hopefully).
	if ((getTurnNumber(g) < 3) && (myKPIs == 20)) {
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		printf("!      mechanicalTurk.c      !\n");
		printf("!    By Thomas Moffet and    !\n");
		printf("!      George Mountakis      !\n");
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		
		printf("\n!! Game freshly fried on 22/05/15\n");
		printf("!! If you see a line starting with !!, then it's from this mechanicalTurk.c.\n\n");
	}
	
	// printf("KPIs = %d, THDs = %d, BPS = %d, BQN = %d, MJ = %d, MTV = %d, MMONEY = %d\n", myKPIs, myTHDs, myBPSs, myBQNs, myMJs, myMTVs, myMMONEYs);
	
	/// These store the amount of students that can be converted from
	/// each type of student. This can be used as quick reference to
	/// determine if the player can convert a number of students.
	short convertibleBPSs = myBPSs / (getExchangeRate(g, iAmPlayer, STUDENT_BPS, STUDENT_BPS));
	short convertibleBQNs = myBQNs / (getExchangeRate(g, iAmPlayer, STUDENT_BQN, STUDENT_BPS));
	short convertibleMJs = myMJs / (getExchangeRate(g, iAmPlayer, STUDENT_MJ, STUDENT_BPS));
	short convertibleMTVs = myMTVs / (getExchangeRate(g, iAmPlayer, STUDENT_MTV, STUDENT_BPS));
	short convertibleMMONEYs = myMMONEYs / (getExchangeRate(g, iAmPlayer, STUDENT_MMONEY, STUDENT_BPS));
	
	/// This stores all the positions that the AI can build things,
	/// regardless of their resources. It only depends on the board
	/// placement.
	char validCampuses[54] = {-1};
	char validGO8s[54] = {-1};
	char validARCs[72] = {-1};
	
	checkValidPositions(d, iAmPlayer, validCampuses, validGO8s, validARCs);
	
	short whatDoIWantToDo = 0;
	path destination = {0};
	
	/// This determines what the AI wants to accomplish.
	// Right now, it just wants to perform a spinoff. Later, this will
	// be the determinating logic. It should be based mostly on the
	// board situation, or KPIs, rather than resources on-hand. This
	// should give the AI a "goal", which should make its actions more
	// consistent.
	
	if (((myCampuses >= 5) && (myGO8s != 0)) && (validGO8s[0] != -1)) {
		whatDoIWantToDo = MAKE_GO8;
	} else if ((((float)myARCs / (myCampuses + myGO8s)) > 2) && (validCampuses[0] != -1)) {
		whatDoIWantToDo = MAKE_CAMPUS;
	} else if ((myARCs < 10) && (validARCs[0] != -1)) {
		whatDoIWantToDo = MAKE_ARC;
	} else {
		whatDoIWantToDo = PERFORM_SPINOFF;
	}
	
	/// Then it makes its action.
	/// Right now, the AI will make a spin-off if it has the resources
	/// to, and a pass if it doesn't.
	
	if (whatDoIWantToDo == MAKE_CAMPUS) {
		short shortBPSs = 0;
		if (myBPSs >= 1) {
			shortBPSs = 1;
		}
		short shortBQNs = 0;
		if (myBQNs >= 1) {
			shortBQNs = 1;
		}
		short shortMJs = 0;
		if (myMJs >= 1) {
			shortMJs = 1;
		}
		short shortMTVs = 0;
		if (myMTVs >= 1) {
			shortMTVs = 1;
		}
		
		if (myBPSs >= 1 && myBQNs >= 1 && myMJs >= 1 && myMTVs >= 1) {
			short ID = validCampuses[0];
			nextAction.actionCode = BUILD_CAMPUS;
			Coord entryStart = d->campus[ID].start;
			convertVertex(d, nextAction.destination, entryStart);
			// FIGURE OUT WHEN TO CONVERT RESOURCES
		} else if ((convertibleBPSs + convertibleBQNs) >= (4 - (shortBPSs + shortBQNs + shortMJs + shortMTVs))) {
			nextAction.actionCode = RETRAIN_STUDENTS;
			if (convertibleBPSs >= 2) {
				nextAction.disciplineFrom = STUDENT_BPS;
			} else if (convertibleBQNs >= 1) {
				nextAction.disciplineFrom = STUDENT_BQN;
			} else if (convertibleMJs >= 1) {
				nextAction.disciplineFrom = STUDENT_MJ;
			} else if (convertibleMTVs >= 1) {
				nextAction.disciplineFrom = STUDENT_MTV;
			} else if (convertibleMMONEYs >= 1) {
				nextAction.disciplineFrom = STUDENT_MMONEY;
			}
			
			if (myBPSs < 1) {
				nextAction.disciplineTo = STUDENT_BPS;
			} else if (myBQNs < 1) {
				nextAction.disciplineTo = STUDENT_BQN;
			} else if (myMJs < 1) {
				nextAction.disciplineTo = STUDENT_MJ;
			} else if (myMTVs < 1) {
				nextAction.disciplineTo = STUDENT_MTV;
			}
		} else {
			nextAction.actionCode = PASS;
			nextAction.disciplineFrom = 0;
			nextAction.disciplineTo = 0;
		}
	} else if (whatDoIWantToDo == MAKE_ARC) {
		short shortBPSs = 0;
		if (myBPSs >= 1) {
			shortBPSs = 1;
		}
		short shortBQNs = 0;
		if (myBQNs >= 1) {
			shortBQNs = 1;
		}
		
		if (myBPSs >= 1 && myBQNs >= 1) {
			short ID = validARCs[0];
			nextAction.actionCode = OBTAIN_ARC;
			Coord entryStart = d->campus[ID].start;
			Coord entryEnd = d->ARC[ID].end;
			convertEdge(d, nextAction.destination, entryStart, entryEnd);
			// FIGURE OUT WHEN TO CONVERT RESOURCES
		} else if ((convertibleMJs + convertibleMTVs + convertibleMMONEYs) >= (2 - (shortBPSs + shortBQNs ))) {
			nextAction.actionCode = RETRAIN_STUDENTS;
			if (convertibleMJs >= 1) {
				nextAction.disciplineFrom = STUDENT_MJ;
			} else if (convertibleMTVs >= 1) {
				nextAction.disciplineFrom = STUDENT_MTV;
			} else if (convertibleMMONEYs >= 1) {
				nextAction.disciplineFrom = STUDENT_MMONEY;
			}
			
			if (myBPSs < 1) {
				nextAction.disciplineTo = STUDENT_BPS;
			} else if (myBQNs < 1) {
				nextAction.disciplineTo = STUDENT_BQN;
			}
		} else {
			nextAction.actionCode = PASS;
			nextAction.disciplineFrom = 0;
			nextAction.disciplineTo = 0;
		}
	} else if (whatDoIWantToDo == PERFORM_SPINOFF) {
		/// This stores what resources all already at the necessary
		/// amounts to perform this action.
		short shortMJs = 0;
		if (myMJs >= 1) {
			shortMJs = 1;
		}
		short shortMTVs = 0;
		if (myMTVs >= 1) {
			shortMTVs = 1;
		}
		short shortMMONEYs = 0;
		if (myMMONEYs >= 1) {
			shortMMONEYs = 1;
		}
		if (myMJs >= 1 && myMTVs >= 1 && myMMONEYs >= 1) {
			nextAction.actionCode = START_SPINOFF;
			nextAction.disciplineFrom = 0;
			nextAction.disciplineTo = 0;
		} else if ((convertibleBPSs + convertibleBQNs) >= (3 - (shortMJs + shortMTVs + shortMMONEYs))) {
			nextAction.actionCode = RETRAIN_STUDENTS;
			if (convertibleBPSs >= 1) {
				nextAction.disciplineFrom = STUDENT_BPS;
			} else if (convertibleBQNs >= 1) {
				nextAction.disciplineFrom = STUDENT_BQN;
			}
			
			if (myMJs < 1) {
				nextAction.disciplineTo = STUDENT_MJ;
			} else if (myMTVs < 1) {
				nextAction.disciplineTo = STUDENT_MTV;
			} else if (myMMONEYs < 1) {
				nextAction.disciplineTo = STUDENT_MMONEY;
			}
		} else {
			nextAction.actionCode = PASS;
			nextAction.disciplineFrom = 0;
			nextAction.disciplineTo = 0;
		}
	} else {
		nextAction.actionCode = PASS;
		nextAction.disciplineFrom = 0;
		nextAction.disciplineTo = 0;
	}
	
	/// Now we copy the destination to the action's destination.
	strncpy(nextAction.destination, destination, PATH_LIMIT - 1);
	
	/// As a final check, we check if that move is valid in terms of
	/// Game.c. Otherwise, we save ourselves the trouble, and just
	/// pass.
	if (isLegalAction(g, nextAction) == FALSE) {
		nextAction.actionCode = PASS;
		nextAction.disciplineFrom = 0;
		nextAction.disciplineTo = 0;
	}
	
	printf("!! My goal is %d.\n", whatDoIWantToDo);
	short poopypos = 0;
	printf("Valid campuses: ");
	while (poopypos < NUM_VERTICES) {
		printf("%d ", validCampuses[poopypos]);
		poopypos++;
	}
	poopypos = 0;
	printf("\nValid GO8s: ");
	while (poopypos < NUM_VERTICES) {
		printf("%d ", validGO8s[poopypos]);
		poopypos++;
	}
	poopypos = 0;
	printf("\nValid ARCs: ");
	while (poopypos < NUM_EDGES) {
		printf("%d ", validARCs[poopypos]);
		poopypos++;
	}
	printf("\n");
	
	printf("!! Doing action %d, path %s, disc. from %d, disc. to %d.\n", nextAction.actionCode, nextAction.destination, nextAction.disciplineFrom, nextAction.disciplineTo);
	getchar();
	free(d);
	
	return nextAction;
}

Data readGameData(Game g) {
	Data d = malloc(sizeof(struct _data));
	/// This is used to fill out the discipline and dice layouts.
	short pos = 0;

	d->turnNumber = getTurnNumber(g);
	d->whoseTurn = getWhoseTurn(g);
	d->mostARCs = getMostARCs(g);
	d->mostPapers = getMostPublications(g);
	
	while (pos < NUM_REGIONS) {
		d->discipline[pos] = getDiscipline(g, pos);
		d->dice[pos] = getDiceValue(g, pos);
		pos++;
	}
	
	readInitialiseVertices(d);
	readInitialiseEdges(d);
	
	pos = 0;
	path destination = {0};
	Coord start;
	Coord end;
	while (pos < NUM_EDGES) {
		if (pos < NUM_VERTICES) {
			start.x = d->campus[pos].start.x;
			start.y = d->campus[pos].start.y;
			convertVertex(d, destination, start);
			d->campus[pos].type = getCampus(g, destination);
			// printf("Campus %d at %s is type %d.\n", pos, destination, d->campus[pos].type);
			
			flushPath(destination);
		}
		start.x = d->ARC[pos].start.x;
		start.y = d->ARC[pos].start.y;
		end.x = d->ARC[pos].end.x;
		end.y = d->ARC[pos].end.y;
		convertEdge(d, destination, start, end);
		d->ARC[pos].type = getARC(g, destination);
		// printf("ARC %d at %s is type %d.\n", pos, destination, d->ARC[pos].type);
		pos++;
		
		flushPath(destination);
	}
	
	/// Now the player data.
	d->p1.playerID = UNI_A;
	d->p1.KPIs = getKPIpoints(g, UNI_A);
	d->p1.ARCs = getARCs(g, UNI_A);
	d->p1.campuses = getCampuses(g, UNI_A);
	d->p1.GO8s = getGO8s(g, UNI_A);
	d->p1.patents = getIPs(g, UNI_A);
	d->p1.papers = getPublications(g, UNI_A);
	d->p1.THDs = getStudents(g, UNI_A, STUDENT_THD);
	d->p1.BPSs = getStudents(g, UNI_A, STUDENT_BPS);
	d->p1.BQNs = getStudents(g, UNI_A, STUDENT_BQN);
	d->p1.MJs = getStudents(g, UNI_A, STUDENT_MJ);
	d->p1.MTVs = getStudents(g, UNI_A, STUDENT_MTV);
	d->p1.MMONEYs = getStudents(g, UNI_A, STUDENT_MMONEY);
	
	d->p2.playerID = UNI_B;
	d->p2.KPIs = getKPIpoints(g, UNI_B);
	d->p2.ARCs = getARCs(g, UNI_B);
	d->p2.campuses = getCampuses(g, UNI_B);
	d->p2.GO8s = getGO8s(g, UNI_B);
	d->p2.patents = getIPs(g, UNI_B);
	d->p2.papers = getPublications(g, UNI_B);
	d->p2.THDs = getStudents(g, UNI_B, STUDENT_THD);
	d->p2.BPSs = getStudents(g, UNI_B, STUDENT_BPS);
	d->p2.BQNs = getStudents(g, UNI_B, STUDENT_BQN);
	d->p2.MJs = getStudents(g, UNI_B, STUDENT_MJ);
	d->p2.MTVs = getStudents(g, UNI_B, STUDENT_MTV);
	d->p2.MMONEYs = getStudents(g, UNI_B, STUDENT_MMONEY);
	
	d->p3.playerID = UNI_C;
	d->p3.KPIs = getKPIpoints(g, UNI_C);
	d->p3.ARCs = getARCs(g, UNI_C);
	d->p3.campuses = getCampuses(g, UNI_C);
	d->p3.GO8s = getGO8s(g, UNI_C);
	d->p3.patents = getIPs(g, UNI_C);
	d->p3.papers = getPublications(g, UNI_C);
	d->p3.THDs = getStudents(g, UNI_C, STUDENT_THD);
	d->p3.BPSs = getStudents(g, UNI_C, STUDENT_BPS);
	d->p3.BQNs = getStudents(g, UNI_C, STUDENT_BQN);
	d->p3.MJs = getStudents(g, UNI_C, STUDENT_MJ);
	d->p3.MTVs = getStudents(g, UNI_C, STUDENT_MTV);
	d->p3.MMONEYs = getStudents(g, UNI_C, STUDENT_MMONEY);
	return d;
}

/// This function changes all the values in a path to 0.
void flushPath(path destination) {
	short pos = 0;
	while (pos < PATH_LIMIT) {
		destination[pos] = 0;
		pos++;
	}
}

/// This function converts a co-ordinate into a path.
void convertVertex(Data d, path destination, Coord start) {
	/// This co-ordinate tracks where on the board the path is up to.
	/// It starts where all paths start.
	Coord currentCoord;
	currentCoord.x = 7;
	currentCoord.y = 10;
	
	/// This co-ordinate is used for testing if the path has gone off
	/// the board.
	Coord testCoord;
	testCoord.x = currentCoord.x;
	testCoord.y = currentCoord.y;
	
	/// This stores which direction the path is going (think of it as
	/// (2n+1) o'clock). It starts in the 5 o'clock direction.
	short direction = 2;
	
	/// This stores the next direction the path will go.
	char nextPathItem = 0;
	
	short pos = 0;
	// Anyone doing MATH1081 would see this De Morgan's law right here. :)
	while (((currentCoord.x != start.x) || (currentCoord.y != start.y)) && (pos < PATH_LIMIT)) {
		/// The AI basically determines if it needs to go left or right
		/// depending on which direction it is going, and if it is to
		/// the left, right, above, or below the destination.
		
		testCoord.x = currentCoord.x;
		testCoord.y = currentCoord.y;
		
		if (direction == 0) {
			if (testCoord.x > start.x) {
				nextPathItem = LEFT;
			}
			if (testCoord.y > start.y) {
				nextPathItem = RIGHT;
			}
			if (testCoord.x < start.x) {
				nextPathItem = RIGHT;
			}
			if (testCoord.y < start.y) {
				nextPathItem = LEFT;
			}
			// You can change a variable in the middle of an if/else
			// section and not trigger anything else. :)
			if (nextPathItem == LEFT) {
				testCoord.y++;
			} else if (nextPathItem == RIGHT) {
				testCoord.x++;
			}
		} else if (direction == 1) {
			if (testCoord.x > start.x) {
				nextPathItem = RIGHT;
			}
			if (testCoord.y > start.y) {
				nextPathItem = RIGHT;
			}
			if (testCoord.x < start.x) {
				nextPathItem = LEFT;
			}
			if (testCoord.y < start.y) {
				nextPathItem = LEFT;
			}
			
			if (nextPathItem == LEFT) {
				testCoord.x++;
				testCoord.y++;
			} else if (nextPathItem == RIGHT) {
				testCoord.y--;
			}
		} else if (direction == 2) {
			if (testCoord.x > start.x) {
				nextPathItem = RIGHT;
			}
			if (testCoord.y > start.y) {
				nextPathItem = RIGHT;
			}
			if (testCoord.x < start.x) {
				nextPathItem = LEFT;
			}
			if (testCoord.y < start.y) {
				nextPathItem = LEFT;
			}
			
			if (nextPathItem == LEFT) {
				testCoord.x++;
			} else if (nextPathItem == RIGHT) {
				testCoord.x--;
				testCoord.y--;
			}
		} else if (direction == 3) {
			if (testCoord.x > start.x) {
				nextPathItem = RIGHT;
			}
			if (testCoord.y > start.y) {
				nextPathItem = LEFT;
			}
			if (testCoord.x < start.x) {
				nextPathItem = LEFT;
			}
			if (testCoord.y < start.y) {
				nextPathItem = RIGHT;
			}
			
			if (nextPathItem == LEFT) {
				testCoord.y--;
			} else if (nextPathItem == RIGHT) {
				testCoord.x--;
			}
		} else if (direction == 4) {
			if (testCoord.x > start.x) {
				nextPathItem = LEFT;
			}
			if (testCoord.y > start.y) {
				nextPathItem = LEFT;
			}
			if (testCoord.x < start.x) {
				nextPathItem = RIGHT;
			}
			if (testCoord.y < start.y) {
				nextPathItem = RIGHT;
			}
			
			if (nextPathItem == LEFT) {
				testCoord.x--;
				testCoord.y--;
			} else if (nextPathItem == RIGHT) {
				testCoord.y++;
			}
		} else if (direction == 5) {
			if (testCoord.x > start.x) {
				nextPathItem = LEFT;
			}
			if (testCoord.y > start.y) {
				nextPathItem = LEFT;
			}
			if (testCoord.x < start.x) {
				nextPathItem = RIGHT;
			}
			if (testCoord.y < start.y) {
				nextPathItem = RIGHT;
			}
			
			if (nextPathItem == LEFT) {
				testCoord.x--;
			} else if (nextPathItem == RIGHT) {
				testCoord.x++;
				testCoord.y++;
			}
		}
		
		/// Then, if that direction leads off the board, then it'll
		/// just choose the other direction, and move everything there.
		// Basically copy-paste searchForCampus() in later.
		if (searchForCampus(d, testCoord) == NOT_FOUND) {
			if (nextPathItem == LEFT) {
				if (direction == 0) {
					direction = 1;
					currentCoord.x++;
				} else if (direction == 1) {
					direction = 2;
					currentCoord.y--;
				} else if (direction == 2) {
					direction = 3;
					currentCoord.x--;
					currentCoord.y--;
				} else if (direction == 3) {
					direction = 4;
					currentCoord.x--;
				} else if (direction == 4) {
					direction = 5;
					currentCoord.y++;
				} else if (direction == 5) {
					direction = 0;
					currentCoord.x++;
					currentCoord.y++;
				}
				nextPathItem = RIGHT;
			} else if (nextPathItem == RIGHT) {
				if (direction == 0) {
					direction = 5;
					currentCoord.y++;
				} else if (direction == 1) {
					direction = 0;
					currentCoord.x++;
					currentCoord.y++;
				} else if (direction == 2) {
					direction = 1;
					currentCoord.x++;
				} else if (direction == 3) {
					direction = 2;
					currentCoord.y--;
				} else if (direction == 4) {
					direction = 3;
					currentCoord.x--;
					currentCoord.y--;
				} else if (direction == 5) {
					direction = 4;
					currentCoord.x--;
				}
				nextPathItem = LEFT;
			}
		} else {
			if (nextPathItem == LEFT) {
				if (direction == 0) {
					direction = 5;
					currentCoord.y++;
				} else if (direction == 1) {
					direction = 0;
					currentCoord.x++;
					currentCoord.y++;
				} else if (direction == 2) {
					direction = 1;
					currentCoord.x++;
				} else if (direction == 3) {
					direction = 2;
					currentCoord.y--;
				} else if (direction == 4) {
					direction = 3;
					currentCoord.x--;
					currentCoord.y--;
				} else if (direction == 5) {
					direction = 4;
					currentCoord.x--;
				}
			} else if (nextPathItem == RIGHT) {
				if (direction == 0) {
					direction = 1;
					currentCoord.x++;
				} else if (direction == 1) {
					direction = 2;
					currentCoord.y--;
				} else if (direction == 2) {
					direction = 3;
					currentCoord.x--;
					currentCoord.y--;
				} else if (direction == 3) {
					direction = 4;
					currentCoord.x--;
				} else if (direction == 4) {
					direction = 5;
					currentCoord.y++;
				} else if (direction == 5) {
					direction = 0;
					currentCoord.x++;
					currentCoord.y++;
				}
			}
		}
		
		destination[pos] = nextPathItem;
		pos++;
	}
}

void convertEdge(Data d, path destination, Coord start, Coord end) {
	/// Firstly, a path to one side of the edge is determined.
	convertVertex(d, destination, start);
	
	/// Then,we determine the last direction they went in.
	char direction = 2;
	short pos = 0;
	while ((destination[pos] == LEFT) || (destination[pos] == RIGHT)) {
		if (destination[pos] == LEFT) {
			direction--;
		} else if (destination[pos] == RIGHT) {
			direction++;
		}
		
		pos++;
	}
	
	while (direction < 0) {
		direction += 6;
	}
	
	while (direction > 5) {
		direction -= 6;
	}
	
	/// Then we determine which direction is the next point.
	char nextDirection = 0;
	if ((start.x == (end.x - 1)) && (start.y == (end.y - 1))) {
		nextDirection = 0;
	} else if ((start.x == (end.x - 1)) && (start.y == end.y)) {
		nextDirection = 1;
	}   if ((start.x == end.x) && (start.y == (end.y + 1))) {
		nextDirection = 2;
	}   if ((start.x == (end.x + 1)) && (start.y == (end.y + 1))) {
		nextDirection = 3;
	}   if ((start.x == (end.x + 1)) && (start.y == end.y)) {
		nextDirection = 4;
	}   if ((start.x == end.x) && (start.y == (end.y - 1))) {
		nextDirection = 5;
	}
	
	// printf("Start: %d, %d; End: %d, %d\n", start.x, start.y, end.x, end.y);
	// printf("Dir = %d, nextDir = %d\n", direction, nextDirection);
	
	/// Then we determine which direction the path needs to go to get there.
	if (((nextDirection - direction) == -1) || ((nextDirection - direction) == 5)) {
		destination[pos] = LEFT;
	} else if (((nextDirection - direction) == 1) || ((nextDirection - direction) == -5)) {
		destination[pos] = RIGHT;
	} else {
		destination[pos] = BACK;
	}
}

/// This function compares a coordinate with the campuses stored in
/// memory, and returns the array position of the matching one, or
/// NOT_FOUND if no match was found.
short searchForCampus(Data d, Coord coord) {
	short ID = NOT_FOUND;
	short pos = 0;

	/// Every vertex is checked until the given co-ordinate's x and y
	/// values match that vertex's. Then, it breaks and returns that ID.
	while ((pos < NUM_VERTICES) && (ID == NOT_FOUND)) {
		if ((coord.x == d->campus[pos].start.x) &&
			(coord.y == d->campus[pos].start.y)) {
			ID = pos;
		}
		pos++;
	}

	return ID;
}

/// This is the same as above, just with two coords for edges.
short searchForARC(Data d, Coord start, Coord end) {
	short ID = NOT_FOUND;
	short pos = 0;

	/// Every edge is checked until the given co-ordinate's x and y
	/// values match that edge's. Then, it breaks and returns that ID.
	/// It checks if either of the ends of an edge match
	while ((pos < NUM_EDGES) && (ID == NOT_FOUND)) {
		if (((start.x == d->ARC[pos].start.x) &&
		     (start.y == d->ARC[pos].start.y) &&
			 (end.x == d->ARC[pos].end.x) &&
			 (end.y == d->ARC[pos].end.y)) ||
			((start.x == d->ARC[pos].end.x) &&
		     (start.y == d->ARC[pos].end.y) &&
			 (end.x == d->ARC[pos].start.x) &&
			 (end.y == d->ARC[pos].start.y))) {
				ID = pos;
			}
		pos++;
	}
	
	return ID;
}

/// This function changes three arrays and changes them to say which
/// spaces buildings can be built.
void checkValidPositions(Data d, int player, char validCampuses[54], char validGO8s[54], char validARCs[72]) {
	short arrayPos = 0;
	short ID = 0;
	while (ID < NUM_VERTICES) {
		if (validCampusPositions(d, player, ID) == TRUE) {
			validCampuses[arrayPos] = ID;
			arrayPos++;
		}
		ID++;
	}
	
	arrayPos = 0;
	ID = 0;
	while (ID < NUM_VERTICES) {
		if (d->campus[ID].type == player) {
			validGO8s[arrayPos] = ID;
			arrayPos++;
		}
		ID++;
	}
	
	arrayPos = 0;
	ID = 0;
	while (ID < NUM_EDGES) {
		if (validARCPositions(d, player, ID) == TRUE) {
			validARCs[arrayPos] = ID;
			arrayPos++;
		}
		ID++;
	}
}

short validCampusPositions(Data d, int player, short ID) {
	/// This stores whether their campus can actually be placed there.
	short isItValid = FALSE;
	
	/// This stores how many directions we've tested. This should stop
	/// at 6.
	short iterations = 0;
	short testID = NOT_FOUND;
	
	/// This stores the co-ordinate of where they want to go.
	Coord givenStart;
	givenStart.x = d->campus[ID].start.x;
	givenStart.y = d->campus[ID].start.y;
	
	/// And this is the co-ordinate of the test. This will be one grid
	/// space away from the given co-ordinate. The end of an ARC will
	/// just use the given co-ordinate.
	Coord testEnd;
	
	/// And this is the ID of the vertex we are testing.
	
	/// Firstly, we check to see if it's touching a friendly road.
	/// If it is, it's valid.
	
	while ((iterations < 6) && (isItValid == FALSE)) {
		/// First, we set what vertex we're checking.
		if (iterations == 0) {
			/// This checks the 1 o'clock position.
			testEnd.x = givenStart.x + 1;
			testEnd.y = givenStart.y + 1;
		} else if (iterations == 1) {
			/// This checks the 3 o'clock position.
			testEnd.x = givenStart.x + 1;
			testEnd.y = givenStart.y;
		} else if (iterations == 2) {
			/// This checks the 5 o'clock position.
			testEnd.x = givenStart.x;
			testEnd.y = givenStart.y - 1;
		} else if (iterations == 3) {
			/// This checks the 7 o'clock position.
			testEnd.x = givenStart.x - 1;
			testEnd.y = givenStart.y - 1;
		} else if (iterations == 4) {
			/// This checks the 9 o'clock position.
			testEnd.x = givenStart.x + 1;
			testEnd.y = givenStart.y;
		} else if (iterations == 5) {
			/// This checks the 11 o'clock position.
			testEnd.x = givenStart.x;
			testEnd.y = givenStart.y + 1;
		}
		
		/// Then, we store that edge's ID.
		testID = searchForARC(d, givenStart, testEnd);
		
		/// If that was an invalid edge, then it doesn't bother.
		if (testID != NOT_FOUND) {
			/// Otherwise, we check if that belongs to that player.
			if (player == UNI_A) {
				if (d->ARC[testID].type == ARC_A) {
					isItValid = TRUE;
				}
			} else if (player == UNI_B) {
				if (d->ARC[testID].type == ARC_B) {
					isItValid = TRUE;
				}
			} else if (player == UNI_C) {
				if (d->ARC[testID].type == ARC_C) {
					isItValid = TRUE;
				}
			}
		}
		iterations++;
	}
	
	/// If they're connected to a road, we have to double-check that
	/// they're not directly next to another campus.
	if (isItValid == TRUE) {
	iterations = 0;
		while ((iterations < 6) && (isItValid == TRUE)) {
			/// First, we set what vertex we're checking.
			if (iterations == 0) {
				/// This checks the 1 o'clock position.
				testEnd.x = givenStart.x + 1;
				testEnd.y = givenStart.y + 1;
			} else if (iterations == 1) {
				/// This checks the 3 o'clock position.
				testEnd.x = givenStart.x + 1;
				testEnd.y = givenStart.y;
			} else if (iterations == 2) {
				/// This checks the 5 o'clock position.
				testEnd.x = givenStart.x;
				testEnd.y = givenStart.y - 1;
			} else if (iterations == 3) {
				/// This checks the 7 o'clock position.
				testEnd.x = givenStart.x - 1;
				testEnd.y = givenStart.y - 1;
			} else if (iterations == 4) {
				/// This checks the 9 o'clock position.
				testEnd.x = givenStart.x - 1;
				testEnd.y = givenStart.y;
			} else if (iterations == 5) {
				/// This checks the 11 o'clock position.
				testEnd.x = givenStart.x;
				testEnd.y = givenStart.y + 1;
			}
			
			/// Then, we store that vertex's ID.
			short testID = searchForCampus(d, testEnd);
			
			/// If that was an invalid vertex, then it doesn't bother.
			if (testID != NOT_FOUND) {
				/// Otherwise, we check if that belongs to that player.
				if (player == UNI_A) {
					if ((d->campus[testID].type == CAMPUS_A) ||
					    (d->campus[testID].type == GO8_A)) {
						isItValid = FALSE;
					}
				} else if (player == UNI_B) {
					if ((d->campus[testID].type == CAMPUS_B) ||
					    (d->campus[testID].type == GO8_B)) {
						isItValid = FALSE;
					}
				} else if (player == UNI_C) {
					if ((d->campus[testID].type == CAMPUS_C) ||
					    (d->campus[testID].type == GO8_C)) {
						isItValid = FALSE;
					}
				}
			}
			iterations++;
		}		
	}
	return isItValid;
}

/// This function checks if a specific player can build an ARC based on
/// what's around the given position. It doesn't take into count the
/// user's resources, or what is already on that space. That's handled
/// by the rest of isLegalAction. It does have exceptions if the user
/// has not yet built an ARC.
short validARCPositions(Data d, int player, short ID) {
	/// This stores whether their campus can actually be placed there.
	short isItValid = FALSE;
	
	/// This stores how many directions we've tested. This should stop
	/// at 12.
	short iterations = 0;
	short testID = NOT_FOUND;
	
	/// This stores the co-ordinate of where they want to go.
	Coord givenStart;
	givenStart.x = d->ARC[ID].start.x;
	givenStart.y = d->ARC[ID].start.y;
	Coord givenEnd;
	givenEnd.x = d->ARC[ID].end.x;
	givenEnd.y = d->ARC[ID].end.y;
	
	/// And this is the co-ordinate of the test. This will be one grid
	/// space away from the given co-ordinate. The end of an ARC will
	/// just use the given co-ordinate.
	Coord testEnd;
	
	/// And this is the ID of the vertex we are testing.
	
	/// Firstly, we check to see if it's touching a friendly road.
	/// If it is, it's valid.
	
	while ((iterations < 12) && (isItValid == FALSE)) {
		/// First, we set what vertex we're checking.
		if (iterations == 0) {
			/// This checks the 1 o'clock position.
			testEnd.x = givenStart.x + 1;
			testEnd.y = givenStart.y + 1;
		} else if (iterations == 1) {
			/// This checks the 3 o'clock position.
			testEnd.x = givenStart.x + 1;
			testEnd.y = givenStart.y;
		} else if (iterations == 2) {
			/// This checks the 5 o'clock position.
			testEnd.x = givenStart.x;
			testEnd.y = givenStart.y - 1;
		} else if (iterations == 3) {
			/// This checks the 7 o'clock position.
			testEnd.x = givenStart.x - 1;
			testEnd.y = givenStart.y - 1;
		} else if (iterations == 4) {
			/// This checks the 9 o'clock position.
			testEnd.x = givenStart.x - 1;
			testEnd.y = givenStart.y;
		} else if (iterations == 5) {
			/// This checks the 11 o'clock position.
			testEnd.x = givenStart.x;
			testEnd.y = givenStart.y + 1;
		} else if (iterations == 6) {
			/// This checks the 1 o'clock position.
			testEnd.x = givenEnd.x + 1;
			testEnd.y = givenEnd.y + 1;
		} else if (iterations == 7) {
			/// This checks the 3 o'clock position.
			testEnd.x = givenEnd.x + 1;
			testEnd.y = givenEnd.y;
		} else if (iterations == 8) {
			/// This checks the 5 o'clock position.
			testEnd.x = givenEnd.x;
			testEnd.y = givenEnd.y - 1;
		} else if (iterations == 9) {
			/// This checks the 7 o'clock position.
			testEnd.x = givenEnd.x - 1;
			testEnd.y = givenEnd.y - 1;
		} else if (iterations == 10) {
			/// This checks the 9 o'clock position.
			testEnd.x = givenEnd.x - 1;
			testEnd.y = givenEnd.y;
		} else if (iterations == 11) {
			/// This checks the 11 o'clock position.
			testEnd.x = givenEnd.x;
			testEnd.y = givenEnd.y + 1;
		}
		
		/// Then, we store that edge's ID. We check 6 directions based
		/// on one vertex, then the other vertex.
		if (iterations < 6) {
			testID = searchForARC(d, givenStart, testEnd);
		} else {
			testID = searchForARC(d, givenEnd, testEnd);
		}
		
		/// If that was an invalid edge, then it doesn't bother.
		if (testID != NOT_FOUND) {
			/// Otherwise, we check if that belongs to that player.
			if (player == UNI_A) {
				if (d->ARC[testID].type == ARC_A) {
					isItValid = TRUE;
				}
			} else if (player == UNI_B) {
				if (d->ARC[testID].type == ARC_B) {
					isItValid = TRUE;
				}
			} else if (player == UNI_C) {
				if (d->ARC[testID].type == ARC_C) {
					isItValid = TRUE;
				}
			}
		}
		
		/// As a corner-case, we will end up counting the line itself,
		/// so we have an exception case here.
		if (((testEnd.x == givenEnd.x) && (testEnd.y == givenEnd.y)) ||
		    ((testEnd.x == givenStart.x) && (testEnd.y == givenStart.y))) {
			isItValid = FALSE;
		}
		
		iterations++;
	}
	
	/// Another corner-case, if the user has not built an ARC yet, they
	/// wouldn't be able to put an ARC next to an existing one. So, we
	/// just explicitly write some exceptions.
	if ((player == UNI_A) && (d->p1.ARCs == 0)) {
		if ((ID == 0) || (ID == 24) || (ID == 23) || (ID == 47)) {
			isItValid = TRUE;
		}
	} else if ((player == UNI_B) && (d->p2.ARCs == 0)) {
		if ((ID == 27) || (ID == 54) || (ID == 44) || (ID == 65)) {
			isItValid = TRUE;
		}
	} else if ((player == UNI_C) && (d->p3.ARCs == 0)) {
		if ((ID == 5) || (ID == 53) || (ID == 18) || (ID == 66)) {
			isItValid = TRUE;
		}
	}
	
	return isItValid;
}

void readInitialiseVertices(Data d) {
	// Each vertex will be smooshed into one function, so you'll just
	// see: setVertex(d, 0, 7, 10) for this first one for example.
	/// These are arranged by rows.
	d->campus[ 0].start.x = 7;
	d->campus[ 0].start.y = 10;
	d->campus[ 1].start.x = 8;
	d->campus[ 1].start.y = 10;

	d->campus[ 2].start.x = 5;
	d->campus[ 2].start.y = 9;
	d->campus[ 3].start.x = 6;
	d->campus[ 3].start.y = 9;
	d->campus[ 4].start.x = 8;
	d->campus[ 4].start.y = 9;
	d->campus[ 5].start.x = 9;
	d->campus[ 5].start.y = 9;

	d->campus[ 6].start.x = 3;
	d->campus[ 6].start.y = 8;
	d->campus[ 7].start.x = 4;
	d->campus[ 7].start.y = 8;
	d->campus[ 8].start.x = 6;
	d->campus[ 8].start.y = 8;
	d->campus[ 9].start.x = 7;
	d->campus[ 9].start.y = 8;
	d->campus[10].start.x = 9;
	d->campus[10].start.y = 8;
	d->campus[11].start.x = 10;
	d->campus[11].start.y = 8;

	d->campus[12].start.x = 2;
	d->campus[12].start.y = 7;
	d->campus[13].start.x = 4;
	d->campus[13].start.y = 7;
	d->campus[14].start.x = 5;
	d->campus[14].start.y = 7;
	d->campus[15].start.x = 7;
	d->campus[15].start.y = 7;
	d->campus[16].start.x = 8;
	d->campus[16].start.y = 7;
	d->campus[17].start.x = 10;
	d->campus[17].start.y = 7;

	d->campus[18].start.x = 2;
	d->campus[18].start.y = 6;
	d->campus[19].start.x = 3;
	d->campus[19].start.y = 6;
	d->campus[20].start.x = 5;
	d->campus[20].start.y = 6;
	d->campus[21].start.x = 6;
	d->campus[21].start.y = 6;
	d->campus[22].start.x = 8;
	d->campus[22].start.y = 6;
	d->campus[23].start.x = 9;
	d->campus[23].start.y = 6;

	d->campus[24].start.x = 1;
	d->campus[24].start.y = 5;
	d->campus[25].start.x = 3;
	d->campus[25].start.y = 5;
	d->campus[26].start.x = 4;
	d->campus[26].start.y = 5;
	d->campus[27].start.x = 6;
	d->campus[27].start.y = 5;
	d->campus[28].start.x = 7;
	d->campus[28].start.y = 5;
	d->campus[29].start.x = 9;
	d->campus[29].start.y = 5;

	d->campus[30].start.x = 1;
	d->campus[30].start.y = 4;
	d->campus[31].start.x = 2;
	d->campus[31].start.y = 4;
	d->campus[32].start.x = 4;
	d->campus[32].start.y = 4;
	d->campus[33].start.x = 5;
	d->campus[33].start.y = 4;
	d->campus[34].start.x = 7;
	d->campus[34].start.y = 4;
	d->campus[35].start.x = 8;
	d->campus[35].start.y = 4;

	d->campus[36].start.x = 0;
	d->campus[36].start.y = 3;
	d->campus[37].start.x = 2;
	d->campus[37].start.y = 3;
	d->campus[38].start.x = 3;
	d->campus[38].start.y = 3;
	d->campus[39].start.x = 5;
	d->campus[39].start.y = 3;
	d->campus[40].start.x = 6;
	d->campus[40].start.y = 3;
	d->campus[41].start.x = 8;
	d->campus[41].start.y = 3;

	d->campus[42].start.x = 0;
	d->campus[42].start.y = 2;
	d->campus[43].start.x = 1;
	d->campus[43].start.y = 2;
	d->campus[44].start.x = 3;
	d->campus[44].start.y = 2;
	d->campus[45].start.x = 4;
	d->campus[45].start.y = 2;
	d->campus[46].start.x = 6;
	d->campus[46].start.y = 2;
	d->campus[47].start.x = 7;
	d->campus[47].start.y = 2;

	d->campus[48].start.x = 1;
	d->campus[48].start.y = 1;
	d->campus[49].start.x = 2;
	d->campus[49].start.y = 1;
	d->campus[50].start.x = 4;
	d->campus[50].start.y = 1;
	d->campus[51].start.x = 5;
	d->campus[51].start.y = 1;

	d->campus[52].start.x = 2;
	d->campus[52].start.y = 0;
	d->campus[53].start.x = 3;
	d->campus[53].start.y = 0;
}

void readInitialiseEdges(Data d) {
	// Each edge will be smooshed into one function, so you'll just see:
	// setEdge(d, 0, 7, 10, 8, 10) for this first one for example.
	/// These are arranged by rows.
	/// Firstly, horizontal edges.
	d->ARC[ 0].start.x = 7;
	d->ARC[ 0].start.y = 10;
	d->ARC[ 0].end.x   = 8;
	d->ARC[ 0].end.y   = 10;

	d->ARC[ 1].start.x = 5;
	d->ARC[ 1].start.y = 9;
	d->ARC[ 1].end.x   = 6;
	d->ARC[ 1].end.y   = 9;
	d->ARC[ 2].start.x = 8;
	d->ARC[ 2].start.y = 9;
	d->ARC[ 2].end.x   = 9;
	d->ARC[ 2].end.y   = 9;

	d->ARC[ 3].start.x = 3;
	d->ARC[ 3].start.y = 8;
	d->ARC[ 3].end.x   = 4;
	d->ARC[ 3].end.y   = 8;
	d->ARC[ 4].start.x = 6;
	d->ARC[ 4].start.y = 8;
	d->ARC[ 4].end.x   = 7;
	d->ARC[ 4].end.y   = 8;
	d->ARC[ 5].start.x = 9;
	d->ARC[ 5].start.y = 8;
	d->ARC[ 5].end.x   = 10;
	d->ARC[ 5].end.y   = 8;

	d->ARC[ 6].start.x = 4;
	d->ARC[ 6].start.y = 7;
	d->ARC[ 6].end.x   = 5;
	d->ARC[ 6].end.y   = 7;
	d->ARC[ 7].start.x = 7;
	d->ARC[ 7].start.y = 7;
	d->ARC[ 7].end.x   = 8;
	d->ARC[ 7].end.y   = 7;

	d->ARC[ 8].start.x = 2;
	d->ARC[ 8].start.y = 6;
	d->ARC[ 8].end.x   = 3;
	d->ARC[ 8].end.y   = 6;
	d->ARC[ 9].start.x = 5;
	d->ARC[ 9].start.y = 6;
	d->ARC[ 9].end.x   = 6;
	d->ARC[ 9].end.y   = 6;
	d->ARC[10].start.x = 8;
	d->ARC[10].start.y = 6;
	d->ARC[10].end.x   = 9;
	d->ARC[10].end.y   = 6;

	d->ARC[11].start.x = 3;
	d->ARC[11].start.y = 5;
	d->ARC[11].end.x   = 4;
	d->ARC[11].end.y   = 5;
	d->ARC[12].start.x = 6;
	d->ARC[12].start.y = 5;
	d->ARC[12].end.x   = 7;
	d->ARC[12].end.y   = 5;

	d->ARC[13].start.x = 1;
	d->ARC[13].start.y = 4;
	d->ARC[13].end.x   = 2;
	d->ARC[13].end.y   = 4;
	d->ARC[14].start.x = 4;
	d->ARC[14].start.y = 4;
	d->ARC[14].end.x   = 5;
	d->ARC[14].end.y   = 4;
	d->ARC[15].start.x = 7;
	d->ARC[15].start.y = 4;
	d->ARC[15].end.x   = 8;
	d->ARC[15].end.y   = 4;

	d->ARC[16].start.x = 2;
	d->ARC[16].start.y = 3;
	d->ARC[16].end.x   = 3;
	d->ARC[16].end.y   = 3;
	d->ARC[17].start.x = 5;
	d->ARC[17].start.y = 3;
	d->ARC[17].end.x   = 6;
	d->ARC[17].end.y   = 3;

	d->ARC[18].start.x = 0;
	d->ARC[18].start.y = 2;
	d->ARC[18].end.x   = 1;
	d->ARC[18].end.y   = 2;
	d->ARC[19].start.x = 3;
	d->ARC[19].start.y = 2;
	d->ARC[19].end.x   = 4;
	d->ARC[19].end.y   = 2;
	d->ARC[20].start.x = 6;
	d->ARC[20].start.y = 2;
	d->ARC[20].end.x   = 7;
	d->ARC[20].end.y   = 2;

	d->ARC[21].start.x = 1;
	d->ARC[21].start.y = 1;
	d->ARC[21].end.x   = 2;
	d->ARC[21].end.y   = 1;
	d->ARC[22].start.x = 4;
	d->ARC[22].start.y = 1;
	d->ARC[22].end.x   = 5;
	d->ARC[22].end.y   = 1;

	d->ARC[23].start.x = 2;
	d->ARC[23].start.y = 0;
	d->ARC[23].end.x   = 3;
	d->ARC[23].end.y   = 0;

	/// Secondly, edges that do up-right.
	d->ARC[24].start.x = 6;
	d->ARC[24].start.y = 9;
	d->ARC[24].end.x   = 7;
	d->ARC[24].end.y   = 10;

	d->ARC[25].start.x = 4;
	d->ARC[25].start.y = 8;
	d->ARC[25].end.x   = 5;
	d->ARC[25].end.y   = 9;
	d->ARC[26].start.x = 7;
	d->ARC[26].start.y = 8;
	d->ARC[26].end.x   = 8;
	d->ARC[26].end.y   = 9;

	d->ARC[27].start.x = 2;
	d->ARC[27].start.y = 7;
	d->ARC[27].end.x   = 3;
	d->ARC[27].end.y   = 8;
	d->ARC[28].start.x = 5;
	d->ARC[28].start.y = 7;
	d->ARC[28].end.x   = 6;
	d->ARC[28].end.y   = 8;
	d->ARC[29].start.x = 8;
	d->ARC[29].start.y = 7;
	d->ARC[29].end.x   = 9;
	d->ARC[29].end.y   = 8;

	d->ARC[30].start.x = 3;
	d->ARC[30].start.y = 6;
	d->ARC[30].end.x   = 4;
	d->ARC[30].end.y   = 7;
	d->ARC[31].start.x = 6;
	d->ARC[31].start.y = 6;
	d->ARC[31].end.x   = 7;
	d->ARC[31].end.y   = 7;
	d->ARC[32].start.x = 9;
	d->ARC[32].start.y = 6;
	d->ARC[32].end.x   = 10;
	d->ARC[32].end.y   = 7;

	d->ARC[33].start.x = 1;
	d->ARC[33].start.y = 5;
	d->ARC[33].end.x   = 2;
	d->ARC[33].end.y   = 6;
	d->ARC[34].start.x = 4;
	d->ARC[34].start.y = 5;
	d->ARC[34].end.x   = 5;
	d->ARC[34].end.y   = 6;
	d->ARC[35].start.x = 7;
	d->ARC[35].start.y = 5;
	d->ARC[35].end.x   = 8;
	d->ARC[35].end.y   = 6;

	d->ARC[36].start.x = 2;
	d->ARC[36].start.y = 4;
	d->ARC[36].end.x   = 3;
	d->ARC[36].end.y   = 5;
	d->ARC[37].start.x = 5;
	d->ARC[37].start.y = 4;
	d->ARC[37].end.x   = 6;
	d->ARC[37].end.y   = 5;
	d->ARC[38].start.x = 8;
	d->ARC[38].start.y = 4;
	d->ARC[38].end.x   = 9;
	d->ARC[38].end.y   = 5;

	d->ARC[39].start.x = 0;
	d->ARC[39].start.y = 3;
	d->ARC[39].end.x   = 1;
	d->ARC[39].end.y   = 4;
	d->ARC[40].start.x = 3;
	d->ARC[40].start.y = 3;
	d->ARC[40].end.x   = 4;
	d->ARC[40].end.y   = 4;
	d->ARC[41].start.x = 6;
	d->ARC[41].start.y = 3;
	d->ARC[41].end.x   = 7;
	d->ARC[41].end.y   = 4;

	d->ARC[42].start.x = 1;
	d->ARC[42].start.y = 2;
	d->ARC[42].end.x   = 2;
	d->ARC[42].end.y   = 3;
	d->ARC[43].start.x = 4;
	d->ARC[43].start.y = 2;
	d->ARC[43].end.x   = 5;
	d->ARC[43].end.y   = 3;
	d->ARC[44].start.x = 7;
	d->ARC[44].start.y = 2;
	d->ARC[44].end.x   = 8;
	d->ARC[44].end.y   = 3;

	d->ARC[45].start.x = 2;
	d->ARC[45].start.y = 1;
	d->ARC[45].end.x   = 3;
	d->ARC[45].end.y   = 2;
	d->ARC[46].start.x = 5;
	d->ARC[46].start.y = 1;
	d->ARC[46].end.x   = 6;
	d->ARC[46].end.y   = 2;

	d->ARC[47].start.x = 3;
	d->ARC[47].start.y = 0;
	d->ARC[47].end.x   = 4;
	d->ARC[47].end.y   = 1;

	/// Finally, edges that do down-right.
	d->ARC[48].start.x = 8;
	d->ARC[48].start.y = 10;
	d->ARC[48].end.x   = 8;
	d->ARC[48].end.y   = 9;

	d->ARC[49].start.x = 6;
	d->ARC[49].start.y = 9;
	d->ARC[49].end.x   = 6;
	d->ARC[49].end.y   = 8;
	d->ARC[50].start.x = 9;
	d->ARC[50].start.y = 9;
	d->ARC[50].end.x   = 9;
	d->ARC[50].end.y   = 8;

	d->ARC[51].start.x = 4;
	d->ARC[51].start.y = 8;
	d->ARC[51].end.x   = 4;
	d->ARC[51].end.y   = 7;
	d->ARC[52].start.x = 7;
	d->ARC[52].start.y = 8;
	d->ARC[52].end.x   = 7;
	d->ARC[52].end.y   = 7;
	d->ARC[53].start.x = 10;
	d->ARC[53].start.y = 8;
	d->ARC[53].end.x   = 10;
	d->ARC[53].end.y   = 7;

	d->ARC[54].start.x = 2;
	d->ARC[54].start.y = 7;
	d->ARC[54].end.x   = 2;
	d->ARC[54].end.y   = 6;
	d->ARC[55].start.x = 5;
	d->ARC[55].start.y = 7;
	d->ARC[55].end.x   = 5;
	d->ARC[55].end.y   = 6;
	d->ARC[56].start.x = 8;
	d->ARC[56].start.y = 7;
	d->ARC[56].end.x   = 8;
	d->ARC[56].end.y   = 6;

	d->ARC[57].start.x = 3;
	d->ARC[57].start.y = 6;
	d->ARC[57].end.x   = 3;
	d->ARC[57].end.y   = 5;
	d->ARC[58].start.x = 6;
	d->ARC[58].start.y = 6;
	d->ARC[58].end.x   = 6;
	d->ARC[58].end.y   = 5;
	d->ARC[59].start.x = 9;
	d->ARC[59].start.y = 6;
	d->ARC[59].end.x   = 9;
	d->ARC[59].end.y   = 5;

	d->ARC[60].start.x = 1;
	d->ARC[60].start.y = 5;
	d->ARC[60].end.x   = 1;
	d->ARC[60].end.y   = 4;
	d->ARC[61].start.x = 4;
	d->ARC[61].start.y = 5;
	d->ARC[61].end.x   = 4;
	d->ARC[61].end.y   = 4;
	d->ARC[62].start.x = 7;
	d->ARC[62].start.y = 5;
	d->ARC[62].end.x   = 7;
	d->ARC[62].end.y   = 4;

	d->ARC[63].start.x = 2;
	d->ARC[63].start.y = 4;
	d->ARC[63].end.x   = 2;
	d->ARC[63].end.y   = 3;
	d->ARC[64].start.x = 5;
	d->ARC[64].start.y = 4;
	d->ARC[64].end.x   = 5;
	d->ARC[64].end.y   = 3;
	d->ARC[65].start.x = 8;
	d->ARC[65].start.y = 4;
	d->ARC[65].end.x   = 8;
	d->ARC[65].end.y   = 3;

	d->ARC[66].start.x = 0;
	d->ARC[66].start.y = 3;
	d->ARC[66].end.x   = 0;
	d->ARC[66].end.y   = 2;
	d->ARC[67].start.x = 3;
	d->ARC[67].start.y = 3;
	d->ARC[67].end.x   = 3;
	d->ARC[67].end.y   = 2;
	d->ARC[68].start.x = 6;
	d->ARC[68].start.y = 3;
	d->ARC[68].end.x   = 6;
	d->ARC[68].end.y   = 2;

	d->ARC[69].start.x = 1;
	d->ARC[69].start.y = 2;
	d->ARC[69].end.x   = 1;
	d->ARC[69].end.y   = 1;
	d->ARC[70].start.x = 4;
	d->ARC[70].start.y = 2;
	d->ARC[70].end.x   = 4;
	d->ARC[70].end.y   = 1;

	d->ARC[71].start.x = 2;
	d->ARC[71].start.y = 1;
	d->ARC[71].end.x   = 2;
	d->ARC[71].end.y   = 0;
}