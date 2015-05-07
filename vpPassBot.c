/*
 *  Mr Pass.  Brain the size of a planet!
 *
 *  Proundly Created by Richard Buckland
 *  Share Freely Creative Commons SA-BY-NC 3.0. 
 *  This is Vincent and Pua's A.I.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

action decideAction (Game g) {

   
   action nextAction;
   nextAction.actionCode = PASS;
   
   if (discipline[STUDENT_MTV] >= 1 && discipline[STUDENT_MJ] >= 1 &&
      discipline[STUDENT_MMONEY] >= 1) {
      nextAction.actionCode = START_SPINOFF;
      discipline[STUDENT_MTV] = discipline[STUDENT_MTV] - 1;
      discipline[STUDENT_MJ] = discipline[STUDENT_MJ] - 1;
      discipline[STUDENT_MMONEY] = discipline[STUDENT_MMONEY] - 1;
      
   
   return nextAction;
}
