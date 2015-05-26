#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

action decideAction2 (Game g) {
	action nextAction;
	//gets data
	int amPlayer = getWhoseTurn(g);
	//int THD = getStudents(g, amPlayer, STUDENT_THD);
	int BPS = getStudents(g, amPlayer, STUDENT_BPS);
	int BQN = getStudents(g, amPlayer, STUDENT_BQN);
	int MJ = getStudents(g, amPlayer, STUDENT_MJ);
	int MTV = getStudents(g, amPlayer, STUDENT_MTV);
	int MMONEY = getStudents(g, amPlayer, STUDENT_MMONEY);
/*
	int JtoPS = getExchangeRate(g, amPlayer, STUDENT_MJ, STUDENT_BPS);
	int JtoQN = getExchangeRate(g, amPlayer, STUDENT_MJ, STUDENT_BQN);
	int TVtoPS = getExchangeRate(g, amPlayer, STUDENT_MTV, STUDENT_BPS);
	int TVtoQN = getExchangeRate(g, amPlayer, STUDENT_MTV, STUDENT_BQN);
	int MONtoPS = getExchangeRate(g, amPlayer, STUDENT_MMONEY, STUDENT_BPS);
	int MONtoQN = getExchangeRate(g, amPlayer, STUDENT_MMONEY, STUDENT_BQN);
    int QNtoJ = getExchangeRate(g, amPlayer, STUDENT_BQN, STUDENT_MJ);
	int QNtoTV = getExchangeRate(g, amPlayer, STUDENT_BQN, STUDENT_MTV);
	int QNtoMON = getExchangeRate(g, amPlayer, STUDENT_BQN, STUDENT_MMONEY);
	int QStoJ = getExchangeRate(g, amPlayer, STUDENT_BPS, STUDENT_MJ);
	int QStoTV = getExchangeRate(g, amPlayer, STUDENT_BPS, STUDENT_MTV);
	int QStoMON = getExchangeRate(g, amPlayer, STUDENT_BPS, STUDENT_MMONEY);
*/
/*
	if ((BPS >= 1) && (BQN >= 1) {
		nextAction.actionCode = OBTAIN_ARC;
		//needs to use data from coordinates
		path destination
	} else if ((BPS == 0) && (MJ >=JtoPS) || (MTV >= TVtoPS) || (MMONEY >=MONtoPS)) {
		nextAction.actionCode = RETRAIN_STUDENTS;
		nextAction.disciplineFrom = mostStudents(MJ, MTV, MMONEY);
		nextAction.disciplineTo = BPS;
	} else if (BQN == 0) && (MJ >=JtoQN) || (MTV >= TVtoQN) || (MMONEY >=MONtoQN)) {
		nextAction.actionCode = RETRAIN_STUDENTS;
		nextAction.disciplineFrom = mostStudents(MJ, MTV, MMONEY);
		nextAction.disciplineTo = BPS;
	}
*/
	//pass and spinoff
	if ((MJ >= 1) && (MTV >= 1) && (MMONEY >= 1)) {
		nextAction.actionCode = START_SPINOFF;
	} else if ((BPS <= 3) && (BQN <= 6) && (MTV == 0)) {
		nextAction.actionCode = PASS;
	} else if ((BPS <= 6) && (BQN <= 3) && (MTV == 0)) {
		nextAction.actionCode = PASS;
	} else if ((BPS >= 3) || (BQN >= 3)) {
		nextAction.actionCode = RETRAIN_STUDENTS;
		nextAction.disciplineFrom = mostSpin2(BPS, BQN);
		nextAction.disciplineTo = leastSpin2(MTV, MJ, MMONEY);
	} else {
		nextAction.actionCode = PASS;
	}

    return nextAction;
}

int mostSpin2(int a, int b) {
	int mostStud = 0;
	if (a >= b) {
		mostStud = STUDENT_BPS;
	} else {
		mostStud = STUDENT_BQN;
	}
	return mostStud;
}

int leastSpin2(int a, int b, int c) {
	int leastStud = 0;
	if ((a <= b) && (a <= c)) {
		leastStud = STUDENT_MTV;
	} else if (b <= c) {
		leastStud = STUDENT_MJ;
	} else {
		leastStud = STUDENT_MMONEY;
	}
	return leastStud;
}

