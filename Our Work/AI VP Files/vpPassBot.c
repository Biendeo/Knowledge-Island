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
