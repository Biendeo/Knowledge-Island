/*
 *  Mr Pass.  Brain the size of a planet!
 *
 *  Proundly Created by Richard Buckland
 *  Share Freely Creative Commons SA-BY-NC 3.0. 
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#include "Game.h"
#include "mechanicalTurk.h"
 
action decideAction (Game g) {
   action nextAction;
   
   short iAmPlayer = whoseTurn(g);
   short currentTHDs = getStudents(g, iAmPlayer, STUDENT_THD);
   short currentBPSs = getStudents(g, iAmPlayer, STUDENT_BPS);
   short currentBQNs = getStudents(g, iAmPlayer, STUDENT_BQN);
   short currentMJs = getStudents(g, iAmPlayer, STUDENT_MJ);
   short currentMTVs = getStudents(g, iAmPlayer, STUDENT_MTV);
   short currentMMONEYs = getStudents(g, iAmPlayer, STUDENT_MMONEY);
   
   if (currentMJs >= 1 && currentMTVs >= 1 && currentMMONEYs >= 1) {
       nextAction.actionCode = START_SPINOFF;
   } else {
      nextAction.actionCode = PASS;
   }

   return nextAction;
}
