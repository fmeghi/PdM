/*=============================================================================
 * Author: Federico Meghinasso <fmeghi@gmail.com>
 * Date: 2021/04/15
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "estados_MEF.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

#define BITS_ADC 1024
#define VALOR_ALARMA_ADC_INI BITS_ADC/3
#define VALOR_ALERTA_ADC_INI VALOR_ALARMA_ADC_INI*2

/*=====[Definitions of private data types]===================================*/

typedef enum{
	NORMAL,
	ALERTA,
	ALARMA,
}estado_t;

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

static estado_t estadoMEF;
static uint16_t valorAlertaADC;
static uint16_t valorAlarmaADC;
static uint16_t valorADC;

/*=====[Implementation of public functions]==================================*/


void iniciarMEF(void){
	estadoMEF = NORMAL;
	valorAlarmaADC = VALOR_ALARMA_ADC_INI;
	valorAlertaADC = VALOR_ALERTA_ADC_INI;
	//iniciar uart
	adcInit(ADC_ENABLE);
}


void actualizarMEF(void){
	valorADC = adcRead(CH1);

	switch (estadoMEF){
	case NORMAL:
		//Actualizar salidas
		gpioWrite(LED1, ON);
		gpioWrite(LED2, OFF);
		gpioWrite(LED3, OFF);
		//Actualizar estados
		if (valorAlertaADC >= valorADC){
			estadoMEF = ALERTA;
		}
		break;
	case ALERTA:
		//Actualizar salidas
		gpioWrite(LED1, OFF);
		gpioWrite(LED2, ON);
		gpioWrite(LED3, OFF);
		//Actualizar estados
		if (valorAlertaADC < valorADC){
			estadoMEF = NORMAL;
		}else if (valorAlarmaADC >= valorADC){
			estadoMEF = ALARMA;
		}
		break;
	case ALARMA:
		// Actualizar salidas
		gpioWrite(LED1, OFF);
		gpioWrite(LED2, OFF);
		gpioWrite(LED3, ON);
		//Actualizar estados
		if (valorAlertaADC < valorADC){
			estadoMEF = NORMAL;
		}
		break;
	default:
		iniciarMEF();
		break;
	}
}


