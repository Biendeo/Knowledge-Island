#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#include "Game.h"
#include "mechanicalTurk.h"
 
action decideAction (Game g) {
	action nextAction;
	//gets data
	int amPlayer = getWhoseTurn(g);
	int THD = getStudents(g, amPlayer, STUDENT_THD);
	int BPS = getStudents(g, amPlayer, STUDENT_BPS);
	int BQN = getStudents(g, amPlayer, STUDENT_BQN);
	int MJ = getStudents(g, amPlayer, STUDENT_MJ);
	int MTV = getStudents(g, amPlayer, STUDENT_MTV);
	int MMONEY = getStudents(g, amPlayer, STUDENT_MMONEY);
	int JtoPS = getExchangeRate(g, amPlayer, MJ, BPS);
	int JtoQN = getExchangeRate(g, amPlayer, MJ, BQN);
	int TVtoPS = getExchangeRate(g, amPlayer, MTV, BPS);
	int TVtoQN = getExchangeRate(g, amPlayer, MTV, BQN);
	int MONtoPS = getExchangeRate(g, amPlayer, MTV, BPS);
	int MONtoQN = getExchangeRate(g, amPlayer, MTV, BQN);
   int freeARC = getARC(Game g, path pathToEdge);
   int move = isLegalAction(Game g, action a);
	
	
	if ((BPS >= 1) && (BQN >= 1) {
      if ((freeARC == VACANT_ARC) && (ID != NOT_FOUND)){ 
		   nextAction.actionCode = OBTAIN_ARC;
      }
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
	
	//pass and spinoff
	if ((MJ >= 1) && (MTV >= 1) && (MMONEY >= 1)) {
		nextAction.actionCode = START_SPINOFF;
	} else {
		nextAction.actionCode = PASS;
	}
    return nextAction;
}

   
   
int mostStudents(int a, int b, int c) {
	int mostStud = 0;
	if ((a >= b) && (a >= c) {
		mostStud = a;
	} else if (b >= c) {
		mostStud = b;
	} else {
		mostStud = c;
	}
	return mostStud;
}
