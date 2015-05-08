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
   
  if ((getStudents(g, 1, STUDENT_MJ) >= 1) && (getStudents(g, 1, STUDENT_MMONEY) >= 1) &&
    (getStudents(g, 1, STUDENT_MTV) >= 1)) {
      nextAction.actionCode = START_SPINOFF;
  } else {
  nextAction.actionCode = PASS;
  }
  return nextAction;
}
/*
while ((getStudents(g, 1, STUDENT_BPS) >= 1) && ((getStudents(g, 1, STUDENT_BQN) >= 1)) {
         // Need to know: How to refer to the vertex
         // if = vertex existed
         if (vertex exist)  {
            makeAction(g, OBTAIN_ARC)
            //getStudents(g, 1, STUDENT_BPS) = getStudents(g, 1, STUDENT_BPS) - 1;
            //getStudents(g, 1, STUDENT_BQN) = getStudents(g, 1, STUDENT_BQN) - 1;
         }
      } 
      while ((getStudents(g, 1, STUDENT_BPS) >= 1) && (getStudents(g, 1, STUDENT_BQN) >= 1) &&
              (getStudents(g, 1, STUDENT_MJ) >= 1) && (getStudents(g, 1, STUDENT_MTV) >= 1)) {
         if (vertex exist) {
            makeAction(g, BUILDING_CAMPUS);
           //getStudents(g, 1, STUDENT_BPS) = getStudents(g, 1, STUDENT_BPS) - 1;
           //getStudents(g, 1, STUDENT_BQN) = getStudents(g, 1, STUDENT_BQN) - 1;
           //getStudents(g, 1, STUDENT_MJ) = getStudents(g, 1, STUDENT_MJ) - 1;
           //getStudents(g, 1, STUDENT_MTV) = getStudents(g, 1, STUDENT_MTV) - 1;
         }
      }
      while ((getStudents(g, 1, STUDENT_MJ) >= 2) && (getStudents(g, 1, STUDENT_MTV >= 3) && (int getCampus(Game g, path pathToVertex >= 1)) {
            //Not sure about path to vertex >=1
         if (vertex exist) {
            makeAction(g, BUILD_G08);
           //getStudents(g, 1, STUDENT_MJ) = getStudents(g, 1, STUDENT_MJ) - 2;
            //getStudents(g, 1, STUDENT_MTV) = getStudents(g, 1, STUDENT_MTV) - 3;
            //how to call a building?
         }*/
