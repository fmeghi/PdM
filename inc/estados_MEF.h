/*=============================================================================
 * Author: Federico Meghinasso <fmeghi@gmail.com>
 * Date: 2021/04/15
 * Version: 1
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __ESTADOS_MEF_H__
#define __ESTADOS_MEF_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

typedef enum{
	NORMAL,
	ALERTA,
	ALARMA,
}estado_t;

/*=====[Prototypes (declarations) of public functions]=======================*/
void iniciarMEF(void);
void actualizarMEF(void);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __ESTADOS_MEF_H__ */
