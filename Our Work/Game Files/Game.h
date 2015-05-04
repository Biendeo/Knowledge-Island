/// These are the number of players.
#define NUM_UNIS 3

/// These are the player IDs. The null team is so that you can have an
/// "empty" team on everything initially.
#define NO_ONE 0
#define UNI_A 1
#define UNI_B 2
#define UNI_C 3

/// These are the different things that can be on a line. Basically,
/// it's empty, or it belongs to one of the three teams.
#define VACANT_ARC 0
#define ARC_A 1
#define ARC_B 2
#define ARC_C 3

/// These are the different kinds of things that can be on a corner.
/// A, B, and C are the different players.
#define VACANT_VERTEX 0  
#define CAMPUS_A 1
#define CAMPUS_B 2
#define CAMPUS_C 3
#define GO8_A 4
#define GO8_B 5
#define GO8_C 6

/// These are the IDs for the different actions. We need to just ask if
/// a player's input matches these actions (so that means we need to
/// translate their commands into actions).
#define PASS 0
#define BUILD_CAMPUS 1
#define BUILD_GO8 2
#define OBTAIN_ARC 3
#define START_SPINOFF 4
#define OBTAIN_PUBLICATION 5
#define OBTAIN_IP_PATENT 6
#define RETRAIN_STUDENTS 7

/// These are the resource IDs that the player uses. The specific
/// values are stored in the game struct.
#define STUDENT_THD 0
#define STUDENT_BPS 1
#define STUDENT_BQN 2
#define STUDENT_MJ  3
#define STUDENT_MTV 4
#define STUDENT_MMONEY 5

/// These are some constants for the game.
#define NUM_REGIONS 19
#define PATH_LIMIT 150

/// This is so you can say TRUE/FALSE all the time in the code.
#define TRUE 1
#define FALSE 0

/// This is the game struct. WE DESIGN THIS and put it in game.c.
/// Basicaly, this stores ALL the data for the game (who's playing,
/// resources, etc.). This lets the programmer just pass in the pointer
/// to the game data, and the functions will take what they need and
/// return what they want. 
typedef struct _game * Game;

/// Paths are defined as either going left, right, or backwards when
/// going by edges. This is supposed to store a path to either a corner,
/// or the last ARC grant it goes across. It can loop, but it can't be
/// longer than 149 lines (there's a terminating character 0).
/// There's a starting point in the top-centre (a bit to the left).
typedef char path[PATH_LIMIT];

/// This stores what the player wants to do, multiple times a turn if
/// he wants.
	/// The actionCode is a number that just defines what the player
	/// does.
	/// The destination directs to where they are interacting to if
	/// they're building an ARC grant or a campus.
	/// The next two are used if the user is converting types of
	/// resources.
	/// Destination and disciplineFrom/To are not used simulatneously.
	/// actionCode == PASS is supposed to end the turn.
typedef struct _action {
   int actionCode;
   path destination;
   int disciplineFrom;
   int disciplineTo;
} action;

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
//   int disciplines[] = DEFAULT_DISCIPLINES;
//   int dice[] = DEFAULT_DICE;
//   Game g = newGame (disciplines, dice);
Game newGame (int discipline[], int dice[]);

/// This frees the game when you're done. THIS IS IMPORTANT.
void disposeGame (Game g);

/// This does an action the user inputs. I guess the AI will jump
/// directy to this step on his turn.
void makeAction (Game g, action a);

/// This advances the game to the next turn. It increases the turn
/// number, and gives a dice roll.
// advance the game to the next turn, 
// assuming that the dice has just been rolled and produced diceScore
// the game starts in turn -1 (we call this state "Terra Nullis") and 
// moves to turn 0 as soon as the first dice is thrown. 
void throwDice (Game g, int diceScore);

/// These are the "getter" functions. They return something based on
/// what you tell them.

/// This asks for a hexagon number, and returns what kind of resource
/// it is.
int getDiscipline (Game g, int regionID);

/// This asks for a hexagon number, and returns the dice number on it.
int getDiceValue (Game g, int regionID);

/// This returns who has the most ARCs (I think).
int getMostARCs (Game g);

/// This returns who has the most publications (I think).
int getMostPublications (Game g);

/// This returns the turn number.
int getTurnNumber (Game g);

/// This returns whose turn it is.
int getWhoseTurn (Game g);

/// This asks for a path to a vertex, and returns what is on it.
int getCampus(Game g, path pathToVertex);

/// This asks for a path to an edge, and returns what is on it.
int getARC(Game g, path pathToEdge);

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
int isLegalAction (Game g, action a);

/// These are getters for specific player data.

/// This asks for a player, and returns how many KPI points they have.
int getKPIpoints (Game g, int player);

/// This asks for a player, and returns how many ARCs they have.
int getARCs (Game g, int player);

/// This asks for a player, and returns how many GO8s they have.
int getGO8s (Game g, int player);

/// This asks for a player, and returns how many campuses they have.
int getCampuses (Game g, int player);

/// This asks for a player, and returns how many IP patents they have.
int getIPs (Game g, int player);

/// This asks for a player, and returns how many publications they have.
int getPublications (Game g, int player);

/// This asks for a player and a resource type, and returns how many
/// of that they have.
int getStudents (Game g, int player, int discipline);

/// This asks for a player, and two types of resources, and returns how
/// many of one type of resource is used to convert to another type.
int getExchangeRate (Game g, int player, 
                     int disciplineFrom, int disciplineTo);
