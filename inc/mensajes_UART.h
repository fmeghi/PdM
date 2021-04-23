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

/**
 * @brief Se inicializa la uart.
 * 
 */
void iniciarUART(void);

/**
 * @brief Se envia un mensaje por la uart indicando el mensaje para cada una de las tranciciones.
 * 
 * @param estado Se paso el estado al que se hizo la transicion 
 */
void enviarMensajeUART(estado_t estado);

/**
 * @brief Esta funcion devuelve un true(1) si hay datos en el buffer de la uart para ser leidos
 * 
 * @return uint8_t se uso este tipo de variable porque con bool_t no compilo
 */
uint8_t dataEnUART(void);

/**
 * @brief Se encarga de mandar los mensajes por uart necesarios para poder configurar los valores de las alarmas 
 * y las alertas. Cuando se le ingresa un valo, se verifica antes de pasarlo a los parametros de entrada. Si alguno
 * de los valores no es correcto se sale de la funcion sin cargar el daro erroneo.
 * 
 * @param valorAlerta Puntero a uint16_t del valor de alerta de los estados
 * @param valorAlarma Puntero a uint16_t del valor de alarma de los estados
 */
void recivirConfiguracion(uint16_t *valorAlerta, uint16_t *valorAlarma);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __MENSAJES_UART_H__ */
