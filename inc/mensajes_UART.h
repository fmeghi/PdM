/*=============================================================================
 * Author: Federico Meghinasso <fmeghi@gmail.com>
 * Date: 2021/04/15
 * Version: 1
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __MENSAJES_UART_H__
#define __MENSAJES_UART_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>
#include "estados_MEF.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

/*=====[Prototypes (declarations) of public functions]=======================*/

void iniciarUART(void);
void enviarMensajeUART(estado_t estado);
uint8_t dataEnUART(void);
void recivirConfiguracion(uint16_t *valorAlerta, uint16_t *valorAlarma);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __MENSAJES_UART_H__ */
