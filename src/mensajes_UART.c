/*=============================================================================
 * Author: Federico Meghinasso <fmeghi@gmail.com>
 * Date: 2021/04/15
 * Version: 1
 *===========================================================================*/

#include "mensajes_UART.h"
#include "sapi.h"

#define BITS_ADC 1024


void iniciarUART(void){
	uartInit( UART_USB, 115200 );
}


void enviarMensajeUART(estado_t estado){
	switch (estado){
	case NORMAL:
		uartWriteString( UART_USB, "El nivel de piezas es aceptable.\r\n" );
		uartWriteString( UART_USB, "Ingrese una tecla si desea configurar los valores de transicion.\r\n" );
		break;
	case ALERTA:
		uartWriteString( UART_USB, "El nivel de piezas no es aceptable. Se debe poner la pieza en cola de produccion.\r\n" );
		uartWriteString( UART_USB, "Ingrese una tecla si desea configurar los valores de transicion.\r\n" );
		break;
	case ALARMA:
		uartWriteString( UART_USB, "El nivel de piezas es muy bajo. Es urgente que se repongan.\r\n" );
		uartWriteString( UART_USB, "Ingrese una tecla si desea configurar los valores de transicion.\r\n" );
		break;
	}
}


uint8_t dataEnUART(void){
	return uartRxReady(UART_USB);
}


void recivirConfiguracion(uint16_t *valorAlerta, uint16_t *valorAlarma){
	delay_t delayEntrada;
	uint16_t nuevaAlerta = 0xFFFF;
	uint16_t nuevaAlarma = 0xFFFF;
	delayInit(&delayEntrada, 10000);
	uartRxFlush(UART_USB);
	uartWriteString( UART_USB, "Ingrese un valor limite para generar una alerta\r\n" );
	uartWriteString( UART_USB, "dentro de los proximos 10 segundos.\r\n" );
	while(!delayRead(&delayEntrada)){
		if(dataEnUART()){
			scanf("%d", &nuevaAlerta);
			break;
		}
	}
	if (0xFFFF == nuevaAlerta){
		uartWriteString( UART_USB, "TIME OUT! Ingrese un caracter para intentar nuevamente.\r\n" );
		return;
	}
	if (0 < nuevaAlerta && BITS_ADC > nuevaAlerta){
		*valorAlerta = nuevaAlerta;
		uartWriteString( UART_USB, "El valor ingresado es correcto.\r\n" );
	}else{
		uartWriteString( UART_USB, "El valor es incorrecto. Ingrese un caracter para intentar nuevamente.\r\n" );
		return;
	}
	delayInit(&delayEntrada, 10000);
	uartRxFlush(UART_USB);
	uartWriteString( UART_USB, "Ingrese un valor limite para generar una alarma\r\n" );
	uartWriteString( UART_USB, "dentro de los proximos 10 segundos.\r\n" );
	while(!delayRead(&delayEntrada)){
		if(dataEnUART()){
			scanf("%d", &nuevaAlarma);
			break;
		}
	}
	if (0xFFFF == nuevaAlarma){
		uartWriteString( UART_USB, "TIME OUT! Ingrese un caracter para intentar nuevamente.\r\n" );
		return;
	}
	if(0 < nuevaAlarma && *valorAlerta > nuevaAlarma){
		*valorAlarma = nuevaAlarma;
		uartWriteString( UART_USB, "Los valores se ingresaron correctamente.\r\n" );
		return;
	}
	uartWriteString( UART_USB, "Los valores ingresados no son validos.\r\n" );
	uartWriteString( UART_USB, "Ingrese un caracter para volver a intentarlo.\r\n" );
	uartRxFlush(UART_USB);
}






