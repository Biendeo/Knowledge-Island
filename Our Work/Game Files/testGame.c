// ADD YOUR COMP1917 COMMENT UP HERE.

// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 1/05/2015
// This program communicates with game.h to play Knowledge Island.

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
}
