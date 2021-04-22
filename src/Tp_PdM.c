/*=============================================================================
 * Author: Federico Meghinasso <fmeghi@gmail.com>
 * Date: 2021/04/15
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "Tp_PdM.h"
#include "sapi.h"
#include "estados_MEF.h"

/*=====[Definition macros of private constants]==============================*/

#define CICLO_MEF 5 //Tiempo del ciclo de actualizacion de la maquina de estados

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   delay_t delayMEF;
	// ----- Setup -----------------------------------
   boardInit();
   delayInit(&delayMEF, CICLO_MEF);
   iniciarMEF();

   // ----- Repeat for ever -------------------------
   while( true ) {
      if(delayRead(&delayMEF)){
    	  actualizarMEF();
      }
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
