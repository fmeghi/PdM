/*=============================================================================
 * Author: Federico Meghinasso <fmeghi@gmail.com>
 * Date: 2021/04/15
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "estados_MEF.h"
#include "sapi.h"
#include "mensajes_UART.h"

/*=====[Definition macros of private constants]==============================*/

#define BITS_ADC 1024
#define VALOR_ALARMA_ADC_INI BITS_ADC/3
#define VALOR_ALERTA_ADC_INI VALOR_ALARMA_ADC_INI*2

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/


static estado_t estadoMEF;
static uint16_t valorAlertaADC;
static uint16_t valorAlarmaADC;

/*=====[Implementation of public functions]==================================*/


void iniciarMEF(void){
	estadoMEF = NORMAL;
	valorAlarmaADC = VALOR_ALARMA_ADC_INI;
	valorAlertaADC = VALOR_ALERTA_ADC_INI;
	iniciarUART();
	adcInit(ADC_ENABLE);
}


void actualizarMEF(void){
	uint16_t valorADC;
	valorADC = adcRead(CH1);
	if (dataEnUART()){
		recivirConfiguracion(&valorAlertaADC, &valorAlarmaADC);
	}

	switch (estadoMEF){
	case NORMAL:
		//Actualiza salidas
		gpioWrite(LED1, OFF);
		gpioWrite(LED2, OFF);
		gpioWrite(LED3, ON);
		//Actualizar estados
		if (valorAlertaADC >= valorADC){
			estadoMEF = ALERTA;
			enviarMensajeUART(ALERTA);
		}
		break;
	case ALERTA:
		//Actualiza salidas
		gpioWrite(LED1, ON);
		gpioWrite(LED2, OFF);
		gpioWrite(LED3, OFF);
		//Actualiza estados
		if (valorAlertaADC < valorADC){
			estadoMEF = NORMAL;
			enviarMensajeUART(NORMAL);
		}else if (valorAlarmaADC >= valorADC){
			estadoMEF = ALARMA;
			enviarMensajeUART(ALARMA);
		}
		break;
	case ALARMA:
		// Actualizar salidas
		gpioWrite(LED1, OFF);
		gpioWrite(LED2, ON);
		gpioWrite(LED3, OFF);
		//Actualizar estados
		if (valorAlertaADC < valorADC){
			estadoMEF = NORMAL;
			enviarMensajeUART(NORMAL);
		}
		break;
	default:
		iniciarMEF();
		break;
	}
}


