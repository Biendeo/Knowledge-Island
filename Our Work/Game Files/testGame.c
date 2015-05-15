// ADD YOUR COMP1917 COMMENT UP HERE.

// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 1/05/2015
// This program tests the functions of Game.h.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"

#define LEFT 'L'
#define RIGHT 'R'
#define BACK 'B'

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS, STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

int main(int argc, char *argv[]) {
	/// Firstly, the game loads the default map data, and then uses that
	/// to initialise the game (g).
	int disciplines[19] = DEFAULT_DISCIPLINES;
	int dice[19] = DEFAULT_DICE;
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
	printf("%d\n",(getDiscipline(g, 0)));
	printf("%d\n",(getDiscipline(g, 1)));
	printf("%d\n",(getDiscipline(g, 2)));
	printf("%d\n",(getDiscipline(g, 3)));
	printf("%d\n",(getDiscipline(g, 4)));
	printf("%d\n",(getDiscipline(g, 5)));
	printf("%d\n",(getDiscipline(g, 6)));
	printf("%d\n",(getDiscipline(g, 7)));
	printf("%d\n",(getDiscipline(g, 8)));
	printf("%d\n",(getDiscipline(g, 9)));
	printf("%d\n",(getDiscipline(g, 10)));
	printf("%d\n",(getDiscipline(g, 11)));
	printf("%d\n",(getDiscipline(g, 12)));
	printf("%d\n",(getDiscipline(g, 13)));
	printf("%d\n",(getDiscipline(g, 14)));
	printf("%d\n",(getDiscipline(g, 15)));
	printf("%d\n",(getDiscipline(g, 16)));
	printf("%d\n",(getDiscipline(g, 17)));
	printf("%d\n",(getDiscipline(g, 18)));
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
	
	// You can only assert these on turn -1, they might change.
	if (getTurnNumber(g) == -1) {
		assert (getKPIpoints(g, UNI_A) == 20);
		assert (getKPIpoints(g, UNI_B) == 20);
		assert (getKPIpoints(g, UNI_C) == 20);
		assert (getCampuses(g, UNI_A) == 2);
		assert (getCampuses(g, UNI_B) == 2);
		assert (getCampuses(g, UNI_C) == 2);
		assert (getWhoseTurn(g) == NO_ONE);
		assert (getStudents(g, UNI_A, STUDENT_THD) == 0);
		assert (getStudents(g, UNI_A, STUDENT_BPS) == 3);
		assert (getStudents(g, UNI_A, STUDENT_BQN) == 3);
		assert (getStudents(g, UNI_A, STUDENT_MJ) == 1);
		assert (getStudents(g, UNI_A, STUDENT_MTV) == 1);
		assert (getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
		assert (getStudents(g, UNI_B, STUDENT_THD) == 0);
		assert (getStudents(g, UNI_B, STUDENT_BPS) == 3);
		assert (getStudents(g, UNI_B, STUDENT_BQN) == 3);
		assert (getStudents(g, UNI_B, STUDENT_MJ) == 1);
		assert (getStudents(g, UNI_B, STUDENT_MTV) == 1);
		assert (getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
		assert (getStudents(g, UNI_C, STUDENT_THD) == 0);
		assert (getStudents(g, UNI_C, STUDENT_BPS) == 3);
		assert (getStudents(g, UNI_C, STUDENT_BQN) == 3);
		assert (getStudents(g, UNI_C, STUDENT_MJ) == 1);
		assert (getStudents(g, UNI_C, STUDENT_MTV) == 1);
		assert (getStudents(g, UNI_C, STUDENT_MMONEY) == 1);

		assert (getExchangeRate(g, UNI_A, STUDENT_BPS, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_BQN, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_BPS, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MJ, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_BPS, STUDENT_MTV) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MTV, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_BPS, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MMONEY, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_BQN, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MJ, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_BQN, STUDENT_MTV) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MTV, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_BQN, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MMONEY, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MJ, STUDENT_MTV) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MTV, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MJ, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MMONEY, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MTV, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_A, STUDENT_MMONEY, STUDENT_MTV) == 3);

		assert (getExchangeRate(g, UNI_B, STUDENT_BPS, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_BQN, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_BPS, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MJ, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_BPS, STUDENT_MTV) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MTV, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_BPS, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MMONEY, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_BQN, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MJ, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_BQN, STUDENT_MTV) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MTV, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_BQN, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MMONEY, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MJ, STUDENT_MTV) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MTV, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MJ, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MMONEY, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MTV, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_B, STUDENT_MMONEY, STUDENT_MTV) == 3);

		assert (getExchangeRate(g, UNI_C, STUDENT_BPS, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_BQN, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_BPS, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MJ, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_BPS, STUDENT_MTV) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MTV, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_BPS, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MMONEY, STUDENT_BPS) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_BQN, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MJ, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_BQN, STUDENT_MTV) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MTV, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_BQN, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MMONEY, STUDENT_BQN) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MJ, STUDENT_MTV) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MTV, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MJ, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MMONEY, STUDENT_MJ) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MTV, STUDENT_MMONEY) == 3);
		assert (getExchangeRate(g, UNI_C, STUDENT_MMONEY, STUDENT_MTV) == 3);
	}


	// action a;
	// Add some action checks.
	// It is not legal to make any action during Terra Nullis ie
	// before the game has started.
	
	// Those are not valid arguments.
	/*
	assert (isLegalAction(g, 1) == FALSE);
	assert (isLegalAction(g, 2) == FALSE);
	assert (isLegalAction(g, 3) == FALSE);
	assert (isLegalAction(g, 4) == FALSE);
	assert (isLegalAction(g, 5) == FALSE);
	assert (isLegalAction(g, 6) == FALSE);
	assert (isLegalAction(g, 7) == FALSE);
	*/
	throwDice(g, 2);
	
	disposeGame(g);
	
	printf("All tests passed, you are Awesome!\n");
	return EXIT_SUCCESS;
}
