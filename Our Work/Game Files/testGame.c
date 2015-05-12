// ADD YOUR COMP1917 COMMENT UP HERE.

// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 1/05/2015
// This program tests the functions of Game.h.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "game.h"


int main(int argc, char *argv[]) {
   action discFrom;
   discFrom = 3;
   //if discFrom = 3
   //then discTo = 1
   //but discFrom >= 3
   action discTo;
   discTo = discFrom/3;
   assert (discTo == 1);
   
   //this is for actioncode in action struct
   //this is a intend
   action actCode;
   actCode = PASS;
   action actExecute;
   actExecute = actCode;
   assert (actExecute == 0);

   printf ("You've passed all test!");
   printf ("You're awesome!");
	// MAIN STUFF, ADD THIS WHEN THE PLAN IS DONE.
	/// Firstly, the game loads the default map data, and then uses that
	/// to initialise the game (g).
	int disciplines[] = DEFAULT_DISCIPLINES;
	int dice[] = DEFAULT_DICE;
	Game g = newGame(disciplines, dice);
	
	assert (getDiscipline(g,  0) == STUDENT_BQN);
	assert (getDiscipline(g,  1) == STUDENT_MMONEY);
	assert (getDiscipline(g,  2) == STUDENT_MJ);
	assert (getDiscipline(g,  3) == STUDENT_MMONEY);
	assert (getDiscipline(g,  4) == STUDENT_MJ);
	assert (getDiscipline(g,  5) == STUDENT_BPS);
	assert (getDiscipline(g,  6) == STUDENT_MTV);
	assert (getDiscipline(g,  7) == STUDENT_MTV);
	assert (getDiscipline(g,  8) == STUDENT_BPS);
	assert (getDiscipline(g,  9) == STUDENT_MTV);
	assert (getDiscipline(g, 10) == STUDENT_BQN);
	assert (getDiscipline(g, 11) == STUDENT_MJ);
	assert (getDiscipline(g, 12) == STUDENT_BQN);
	assert (getDiscipline(g, 13) == STUDENT_THD);
	assert (getDiscipline(g, 14) == STUDENT_MJ);
	assert (getDiscipline(g, 15) == STUDENT_MMONEY);
	assert (getDiscipline(g, 16) == STUDENT_MTV);
	assert (getDiscipline(g, 17) == STUDENT_BQN);
	assert (getDiscipline(g, 18) == STUDENT_BPS);
	assert (getDiceValue(g,  0) == 9);
	assert (getDiceValue(g,  1) == 10);
	assert (getDiceValue(g,  2) == 8);
	assert (getDiceValue(g,  3) == 12);
	assert (getDiceValue(g,  4) == 6);
	assert (getDiceValue(g,  5) == 5);
	assert (getDiceValue(g,  6) == 3);
	assert (getDiceValue(g,  7) == 11);
	assert (getDiceValue(g,  8) == 3);
	assert (getDiceValue(g,  9) == 11);
	assert (getDiceValue(g, 10) == 4);
	assert (getDiceValue(g, 11) == 6);
	assert (getDiceValue(g, 12) == 4);
	assert (getDiceValue(g, 13) == 7);
	assert (getDiceValue(g, 14) == 9);
	assert (getDiceValue(g, 15) == 2);
	assert (getDiceValue(g, 16) == 8);
	assert (getDiceValue(g, 17) == 10);
	assert (getDiceValue(g, 18) == 5);
	
	assert (getTurnNumber(g) == -1);
	assert (getKPIpoints(g, UNI_A) == 20);
	assert (getKPIpoints(g, UNI_B) == 20);
	assert (getKPIpoints(g, UNI_C) == 20);
	assert (getCampuses(g, 0) == 2);
	assert (getCampuses(g, 1) == 2);
	assert (getCampuses(g, 2) == 2);
	assert (getCampuses(g, 3) == 2);
	assert (getWhoseTurn(g) == 0);
	assert (getStudents(g, 1, STUDENT_THD) == 0);
	assert (getStudents(g, 1, STUDENT_BPS) == 0);
	assert (getStudents(g, 1, STUDENT_BQN) == 0);
	assert (getStudents(g, 1, STUDENT_MJ) == 0);
	assert (getStudents(g, 1, STUDENT_MTV) == 0);
	assert (getStudents(g, 1, STUDENT_MMONEY) == 0);
	assert (getStudents(g, 2, STUDENT_THD) == 0);
	assert (getStudents(g, 2, STUDENT_BPS) == 0);
	assert (getStudents(g, 2, STUDENT_BQN) == 0);
	assert (getStudents(g, 2, STUDENT_MJ) == 0);
	assert (getStudents(g, 2, STUDENT_MTV) == 0);
	assert (getStudents(g, 2, STUDENT_MMONEY) == 0);
	assert (getStudents(g, 3, STUDENT_THD) == 0);
	assert (getStudents(g, 3, STUDENT_BPS) == 0);
	assert (getStudents(g, 3, STUDENT_BQN) == 0);
	assert (getStudents(g, 3, STUDENT_MJ) == 0);
	assert (getStudents(g, 3, STUDENT_MTV) == 0);
	assert (getStudents(g, 3, STUDENT_MMONEY) == 0);
	
	assert (getExchangeRate(g, 1, STUDENT_BPS, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 1, STUDENT_BQN, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 1, STUDENT_BPS, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MJ, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 1, STUDENT_BPS, STUDENT_MTV) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MTV, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 1, STUDENT_BPS, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MMONEY, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 1, STUDENT_BQN, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MJ, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 1, STUDENT_BQN, STUDENT_MTV) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MTV, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 1, STUDENT_BQN, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MMONEY, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MJ, STUDENT_MTV) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MTV, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MJ, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MMONEY, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MTV, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 1, STUDENT_MMONEY, STUDENT_MTV) == 3);
	
	assert (getExchangeRate(g, 2, STUDENT_BPS, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 2, STUDENT_BQN, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 2, STUDENT_BPS, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MJ, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 2, STUDENT_BPS, STUDENT_MTV) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MTV, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 2, STUDENT_BPS, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MMONEY, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 2, STUDENT_BQN, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MJ, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 2, STUDENT_BQN, STUDENT_MTV) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MTV, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 2, STUDENT_BQN, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MMONEY, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MJ, STUDENT_MTV) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MTV, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MJ, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MMONEY, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MTV, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 2, STUDENT_MMONEY, STUDENT_MTV) == 3);
	
	assert (getExchangeRate(g, 3, STUDENT_BPS, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 3, STUDENT_BQN, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 3, STUDENT_BPS, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MJ, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 3, STUDENT_BPS, STUDENT_MTV) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MTV, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 3, STUDENT_BPS, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MMONEY, STUDENT_BPS) == 3);
	assert (getExchangeRate(g, 3, STUDENT_BQN, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MJ, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 3, STUDENT_BQN, STUDENT_MTV) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MTV, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 3, STUDENT_BQN, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MMONEY, STUDENT_BQN) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MJ, STUDENT_MTV) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MTV, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MJ, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MMONEY, STUDENT_MJ) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MTV, STUDENT_MMONEY) == 3);
	assert (getExchangeRate(g, 3, STUDENT_MMONEY, STUDENT_MTV) == 3);
	action a;
	// Add some action checks.
	throwDice(g, 2);
	// It is not legal to make any action during Terra Nullis ie 
	// before the game has started.
	// Does this include PASS?
	assert (isLegalAction(g, 0) == FALSE);
	assert (isLegalAction(g, 1) == FALSE);
	assert (isLegalAction(g, 2) == FALSE);
	assert (isLegalAction(g, 3) == FALSE);
	assert (isLegalAction(g, 4) == FALSE);
	assert (isLegalAction(g, 5) == FALSE);
	assert (isLegalAction(g, 6) == FALSE);
	assert (isLegalAction(g, 7) == FALSE);
	
	printf("All tests passed, you are Awesome!\n");
	return EXIT_SUCCESS;
}
