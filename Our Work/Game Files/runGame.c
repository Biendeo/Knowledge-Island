// ADD YOUR COMP1917 COMMENT UP HERE.

// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 1/05/2015
// This program communicates with game.h to play Knowledge Island.

#include <stdio.h>
#include <stdlib.h>
#include <time.h> /// For the random dice roll function.

#include "Game.h"

#define TRUE !FALSE
#define FALSE 0
#define POINTS_TO_WIN 150

int playTurn(Game g);
int checkWin(Game g);
void printWinner(Game g, int gHasWon);

int main(int argc, char *argv[]) {
	/// This just sets the random dice roll seed.
	srand(time(NULL));
	
	/// Firstly, the game loads the default map data, and then uses that
	/// to initialise the game (g).
	int disciplines[] = DEFAULT_DISCIPLINES;
	int dice[] = DEFAULT_DICE;
	
	// This bit is an alternative that randomly generates the hexs.
	/*
		/// A random number is created to determine what discipline each
		/// hexagon gets. 19 is the number of hexs, 6 is the number of
		/// disciplines.
		// If we can, we should convert these to #defines.
		short pos = 0;
		while (pos < NUM_REGIONS) {
			discipline[pos] = (rand() % 6);
			pos++;
		}
		
		/// Then we do the same for the dice numbers. They are between 2 and
		/// 12, so the formula is as that.
		pos = 0;
		while (pos < NUM_REGIONS) {
			dice[pos] = (rand() % 6) + 2;
			pos++
		}
	*/
	
	Game g = newGame(disciplines, dice);
	
	/// Then, the game begins. This will constantly ask for input, and
	/// loop until the game is won.
	/// This loop is basically a turn.
	int gHasWon = 0;
	int gDiceScore = 0;
	
	/// This system allows one to just create a second newgame, and add
	/// another condition to the while loop to keep it in the game. Then
	/// the loop only ends when both games finish, but won't play a
	/// single game that has finished.
	while (gHasWon == FALSE) {
		if (gHasWon == FALSE) {
			throwDice(g, diceScore);
			
			playTurn(g);
		}
		gHasWon = checkWin(g);
	}
	
	/// The winner is printed, and the game is unloaded.
	printWinner(g, gHasWon);
	disposeGame(g);
	
	return EXIT_SUCCESS;
}

/// This is the main playing function.
int playTurn(Game g) {
	/// The action is created. The action is given a value so that it
	/// doesn't accidentally skip the user's turn.
	action a;
	action.actionCode = 8;
	
	while (action.actionCode != PASS) {
      /// building arc branch
      /// can cts build if you have the resources
      
      while ((getStudents(g, 1, STUDENT_BPS) >= 1) && ((getStudents(g, 1, STUDENT_BQN) >= 1)) {
         // Need to know: How to refer to the vertex
         // if = vertex existed
         if (/*vertex exist*/)  {
            action.actionCode == OBTAIN_ARC;
            getStudents(g, 1, STUDENT_BPS) = getStudents(g, 1, STUDENT_BPS) - 1;
            getStudents(g, 1, STUDENT_BQN) = getStudents(g, 1, STUDENT_BQN) - 1;
         }
      } 
      while ((getStudents(g, 1, STUDENT_BPS) >= 1) && (getStudents(g, 1, STUDENT_BQN) >= 1) &&
              (getStudents(g, 1, STUDENT_MJ) >= 1) && (getStudents(g, 1, STUDENT_MTV) >= 1)) {
         if (/*vertex exist*/) {
            action.actionCode == BUILD_CAMPUS;
            getStudents(g, 1, STUDENT_BPS) = getStudents(g, 1, STUDENT_BPS) - 1;
            getStudents(g, 1, STUDENT_BQN) = getStudents(g, 1, STUDENT_BQN) - 1;
            getStudents(g, 1, STUDENT_MJ) = getStudents(g, 1, STUDENT_MJ) - 1;
            getStudents(g, 1, STUDENT_MTV) = getStudents(g, 1, STUDENT_MTV) - 1;
         }
      }
      while ((getStudents(g, 1, STUDENT_MJ) >= 2) && (getStudents(g, 1, STUDENT_MTV >= 3) && (int getCampus(Game g, path pathToVertex >= 1)) {
            //Not sure about path to vertex >=1
         if (/*vertex exist*/) {
            action.actionCode == BUILD_G08;
            getStudents(g, 1, STUDENT_MJ) = getStudents(g, 1, STUDENT_MJ) - 2;
            getStudents(g, 1, STUDENT_MTV) = getStudents(g, 1, STUDENT_MTV) - 3;
            //how to call a building?
         }
		// Here, the user needs to input an action.

		isLegalAction(g, a);
	}
	
	return EXIT_SUCCESS;
}

/// This function just checks if any of the players has won the game
/// yet. This runs at the end of a turn to see if a player has won.
int checkWin(Game g) {
	int hasWon = FALSE;
	
	if (getKPIpoints(g, UNI_A) >= POINTS_TO_WIN) {
		hasWon = UNI_A;
	} else if (getKPIpoints(g, UNI_B) >= POINTS_TO_WIN) {
		hasWon = UNI_B;
	} else if (getKPIpoints(g, UNI_C) >= POINTS_TO_WIN) {
		hasWon = UNI_C;
	}
	
	return hasWon;
}

/// This function just prints the winner at the end of the game.
void printWinner(Game g, int hasWon) {
	if (hasWon == UNI_A) {
		printf("Player 1 ");
	} else if (hasWon == UNI_B) {
		printf("Player 2 ");
	} else if (hasWon == UNI_C) {
		printf("Player 3 ");
	}
	printf("is the winner!\n");
}
