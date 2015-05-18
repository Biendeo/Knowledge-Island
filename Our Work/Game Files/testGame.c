// ADD YOUR COMP1917 COMMENT UP HERE.

// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 1/05/2015
// This program tests the functions of Game.h.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

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
	srand(time(NULL));
	
	printf("******************************\n");
	printf("*          testGame.c        *\n");
	printf("*   By Vincent Tan, Pua Pao, *\n");
	printf("*      Thomas Moffet, and    *\n");
	printf("*       George Mountakis     *\n");
	printf("******************************\n");
	
	printf("\n** Test freshly cooked on 19/05/15\n\n");
	printf("** If you see a line starting with **, then it's from this testGame.c.\n");
	
	printf("\n");
	printf("** Setting board values.\n");
	int disciplines[19] = DEFAULT_DISCIPLINES;
	int dice[19] = DEFAULT_DICE;
	
	printf("** Initialising the game.\n");
	Game g = newGame(disciplines, dice);

	printf("\n");
	printf("** Testing board values.\n");
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
	
	printf("** Checking initial player values.\n");
	assert (getKPIpoints(g, UNI_A) == 20);
	assert (getKPIpoints(g, UNI_B) == 20);
	assert (getKPIpoints(g, UNI_C) == 20);
	assert (getCampuses(g, UNI_A) == 2);
	assert (getCampuses(g, UNI_B) == 2);
	assert (getCampuses(g, UNI_C) == 2);
	assert (getARCs(g, UNI_A) == 0);
	assert (getARCs(g, UNI_B) == 0);
	assert (getARCs(g, UNI_C) == 0);
	assert (getMostARCs(g) == NO_ONE);
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

	printf("** Checking exchange rates.\n");
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
	
	printf("** Checking turn -1 actions.\n");
	action a;
	a.actionCode = BUILD_CAMPUS;
	strcpy(a.destination, "R");
	assert (isLegalAction(g, a) == FALSE);
	a.actionCode = BUILD_GO8;
	assert (isLegalAction(g, a) == FALSE);
	a.actionCode = OBTAIN_ARC;
	assert (isLegalAction(g, a) == FALSE);
	a.actionCode = START_SPINOFF;
	assert (isLegalAction(g, a) == FALSE);
	a.actionCode = OBTAIN_PUBLICATION;
	assert (isLegalAction(g, a) == FALSE);
	a.actionCode = OBTAIN_IP_PATENT;
	assert (isLegalAction(g, a) == FALSE);
	a.actionCode = RETRAIN_STUDENTS;
	a.disciplineFrom = STUDENT_BQN;
	a.disciplineTo = STUDENT_BPS;
	assert (isLegalAction(g, a) == FALSE);
	a.actionCode = PASS;
	assert (isLegalAction(g, a) == FALSE);
	
	printf("\n");
	printf("** Simulating a diceroll (dice = 11).\n");
	throwDice(g, 11);
	
	printf("** Checking that P1 got another MTV and everything else is good.\n");
	assert (getWhoseTurn(g) == UNI_A);
	assert (getStudents(g, UNI_A, STUDENT_THD) == 0);
	assert (getStudents(g, UNI_A, STUDENT_BPS) == 3);
	assert (getStudents(g, UNI_A, STUDENT_BQN) == 3);
	assert (getStudents(g, UNI_A, STUDENT_MJ) == 1);
	assert (getStudents(g, UNI_A, STUDENT_MTV) == 2);
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
	
	printf("** Building two ARCs for P1.\n");
	a.actionCode = OBTAIN_ARC;
	strncpy(a.destination, "L", PATH_LIMIT - 1);
	assert (isLegalAction(g, a) == TRUE);
	makeAction(g, a);
	strncpy(a.destination, "LR", PATH_LIMIT - 1);
	assert (isLegalAction(g, a) == TRUE);
	makeAction(g, a);
	
	printf("** Checking that you can't build off the board.\n");
	strncpy(a.destination, "LL", PATH_LIMIT - 1);
	assert (isLegalAction(g, a) == FALSE);
	
	printf("** Checking P1's points.\n");
	assert (getMostARCs(g) == UNI_A);
	assert (getARCs(g, UNI_A) == 2);
	assert (getKPIpoints(g, UNI_A) == 34);
	
	printf("** Checking the getARC function.\n");
	path testPath = {0};
	strncpy(testPath, "L", PATH_LIMIT - 1);
	assert (getARC(g, testPath) == UNI_A);
	strncpy(testPath, "R", PATH_LIMIT - 1);
	assert (getARC(g, testPath) == VACANT_ARC);
	strncpy(testPath, "LR", PATH_LIMIT - 1);
	assert (getARC(g, testPath) == UNI_A);
	
	printf("** Building a campus for P1.\n");
	a.actionCode = BUILD_CAMPUS;
	strncpy(a.destination, "LR", PATH_LIMIT - 1);
	assert (isLegalAction(g, a) == TRUE);
	makeAction(g, a);
	
	printf("** Testing that P1 can retrain MMONEYs for less.\n");
	assert (getExchangeRate(g, UNI_A, STUDENT_MMONEY, STUDENT_BQN) == 2);
	
	printf("** Testing if P1 can end a turn.\n");
	a.actionCode = PASS;
	assert (isLegalAction(g, a) == TRUE);
	
	printf("\n");
	printf("** Moving to P2's turn.\n");
	throwDice(g, 5);
	assert (getWhoseTurn(g) == UNI_B);
	assert (getStudents(g, UNI_A, STUDENT_THD) == 0);
	assert (getStudents(g, UNI_A, STUDENT_BPS) == 0);
	assert (getStudents(g, UNI_A, STUDENT_BQN) == 0);
	assert (getStudents(g, UNI_A, STUDENT_MJ) == 0);
	assert (getStudents(g, UNI_A, STUDENT_MTV) == 1);
	assert (getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
	assert (getStudents(g, UNI_B, STUDENT_THD) == 0);
	/// P2 should have gotten another BPS with that roll.
	assert (getStudents(g, UNI_B, STUDENT_BPS) == 4);
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
	
	printf("** Building an ARC for P2.\n");
	a.actionCode = OBTAIN_ARC;
	strncpy(a.destination, "LRLRLRRLRL", PATH_LIMIT - 1);
	assert (isLegalAction(g, a) == TRUE);
	makeAction(g, a);
	assert (getKPIpoints(g, UNI_B) == 22);
	
	printf("** Converting 3 BPSs to an MMONEY.\n");
	a.actionCode = RETRAIN_STUDENTS;
	a.disciplineFrom = STUDENT_BPS;
	a.disciplineTo = STUDENT_MMONEY;
	assert (isLegalAction(g, a) == TRUE);
	makeAction(g, a);
	assert (getStudents(g, UNI_B, STUDENT_BPS) == 0);
	assert (getStudents(g, UNI_B, STUDENT_MMONEY) == 2);
	
	printf("** Testing a spin-off.\n");
	a.actionCode = START_SPINOFF;
	assert (isLegalAction(g, a) == TRUE);
	makeAction(g, a);
	assert ((getIPs(g, UNI_B) == 1) || (getPublications(g, UNI_B) == 1));
	
	if (getIPs(g, UNI_B) == 1) {
		printf("** Your spin-off gave a patent!\n");
	} else if (getPublications(g, UNI_B) == 1) {
		printf("** Your spin-off gave a paper!\n");
	}
	
	assert (getKPIpoints(g, UNI_B) == 32);
	
	printf("\n");
	printf("** As a bonus test, your spin-off will be tested 100,000 times.\n");
	printf("** Ideally, patents should appear 33.33%% of the time, papers 66.66%%.\n");
	printf("** Don't worry if they're off by 1%% or 2%%.\n");
	long iterations = 0;
	throwDice(g, 2);
	a.actionCode = START_SPINOFF;
	while (iterations < 100000) {
		makeAction(g, a);
		iterations++;
	}
	printf("\n");
	printf("Patents appeared %g%% of the time.\n", (double)getIPs(g, UNI_C) / 1000);
	printf("Papers appeared %g%% of the time.\n", (double)getPublications(g, UNI_C) / 1000);
	
	printf("\n");
	printf("** Almost done, now to just dispose the game.\n");
	disposeGame(g);
	
	printf("** All tests passed, you are Awesome!\n");
	return EXIT_SUCCESS;
}
