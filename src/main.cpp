/*********************************************************************************************************
*                                               <Module name>
*						<Module description>
*
*						<Copyright>
*
*						<Copyright or distribution terms>
*
*
*********************************************************************************************************/

/*********************************************************************************************************
*                                               <File description>
*
* Filename	: Filename
* Version	: Module version					
* Programmer(s) : Programmer initial(s)
**********************************************************************************************************
*  Note(s):
*
*
*
*********************************************************************************************************/

/*********************************************************************************************************
 *
 * \file		${file_name}
 * \brief		Descripcion del modulo
 * \date		${date}
 * \author		Nicolas Ferragamo nferragamo@frba.utn.edu.ar
 * \version 
*********************************************************************************************************/

/*********************************************************************************************************
 *** INCLUDES
*********************************************************************************************************/

#include <Arduino.h>
#include <util/delay.h>

/*********************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
*********************************************************************************************************/


/*********************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
*********************************************************************************************************/
#define SET_PIN(PORT,PIN) (PORT|= 1<<PIN)
#define CLEAR_PIN(PORT,PIN) (PORT&=~(1<<PIN))
#define IS_CLEAR_PIN(PORT,PIN) (((PORT>>PIN)&0x01)==0 ? 1 :0)
#define IS_SET_PIN(PORT,PIN) (((PORT>>PIN)&0x01)==1 ? 1 :0)

// ejemplo si quiere usar una macro para cada botón
#define Boton1 ((PINDC >> PC0) & 0x01)
#define Boton2 ((PINDC >> PC1) & 0x01)
#define Boton3 ((PINDC >> PC2) & 0x01)
#define Boton4 ((PINDC >> PC3) & 0x01)

volatile uint8_t tecla1;
volatile uint8_t tecla2;
volatile uint8_t tecla3;
volatile uint8_t tecla4;

volatile uint8_t boton1;
volatile uint8_t boton2;
volatile uint8_t boton3;
volatile uint8_t boton4;

volatile uint8_t Antecla1 = 0;
volatile uint8_t Antecla2;
volatile uint8_t Antecla3;
volatile uint8_t Antecla4;

volatile long int i = 0;

volatile uint32_t vel = 50000;

enum play_t
{
  PAUSA = 0,
  PLAY
};
play_t pausa = PAUSA;
play_t play = PLAY;
volatile uint8_t cont = 0;
/*********************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
*********************************************************************************************************/

/*********************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
*********************************************************************************************************/
void init(void)
{
  DDRD |= 1 << PD2;
  DDRD |= 1 << PD3;
  DDRD |= 1 << PD4;
  DDRD |= 1 << PD5;
  DDRD |= 1 << PD6;
  DDRD |= 1 << PD7;

  DDRB |= 1 << PB0;
  DDRB |= 1 << PB1;

  PORTC &= ~(1 << PC0);
  PORTC &= ~(1 << PC1);
  PORTC &= ~(1 << PC2);
  PORTC &= ~(1 << PC3);
}
void Mostrar_LED(void)
{
  switch (cont)
  {
  case 1:
    PORTD |= (1 << PD2);
    break;
  case 2:
    PORTD |= (1 << PD3);
    PORTD &= ~(1 << PD2);
    break;
  case 3:
    PORTD |= (1 << PD4);
    PORTD &= ~(1 << PD3);
    break;
  case 4:
    PORTD |= (1 << PD5);
    PORTD &= ~(1 << PD4);
    break;
  case 5:
    PORTD |= (1 << PD6);
    PORTD &= ~(1 << PD5);
    break;
  case 6:
    PORTD |= (1 << PD7);
    PORTD &= ~(1 << PD6);
    break;
  case 7:
    PORTB |= (1 << PB0);
    PORTD &= ~(1 << PD7);
    break;
  case 8:
    PORTB |= (1 << PB1);
    PORTB &= ~(1 << PB0);
    break;
  case 9:
    PORTB |= (1 << PB0);
    PORTB &= ~(1 << PB1);
    break;
  case 10:
    PORTD |= (1 << PD7);
    PORTB &= ~(1 << PB0);
    break;
  case 11:
    PORTD |= (1 << PD6);
    PORTD &= ~(1 << PD7);
    break;
  case 12:
    PORTD |= (1 << PD5);
    PORTD &= ~(1 << PD6);
    break;
  case 13:
    PORTD |= (1 << PD4);
    PORTD &= ~(1 << PD5);
    break;
  case 14:
    PORTD |= (1 << PD3);
    PORTD &= ~(1 << PD4);
    break;
  case 15:
    PORTD |= (1 << PD2);
    PORTD &= ~(1 << PD3);
    break;
  case 16:
    PORTD &= ~(1 << PD2);
    break;
  }
}
/*********************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 *   se escriben en CamelCase y están precedidas por la identificación del 
 *   módulo seguida de un _ 
 *   ej: MEM_POOL  Mem_PoolHeap; 
*********************************************************************************************************/

volatile uint8_t Multiplicador = 0;

/*********************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 *   se declaran con static y se escriben en CamelCase y están precedidas por la 
 *   identificación del módulo seguida de un _ y usan _ para separar las palabras
 *   cuando tienen nombres compuestos
 *   ej: static MEM_POOL  Mem_Pool_Heap; 
*********************************************************************************************************/



/*********************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 * se declaran como estaticas y se escriben en CamelCase, están precedidas por la
 * identificación del módulo seguida de un _. No se decaran en el .h
 * ej static void Clk_DateTimer(parametros)
*********************************************************************************************************/
void config_TIMER0(void);


/*********************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
*********************************************************************************************************/

void config_TIMER0(void)
{
  TCCR0A = (1 << WGM01);              //Activa el bit CTC (clear timer on compare match)
                                      //del TCCR0A (timer counter/control register)
  OCR0A = 155;                        //valor de comparacion de int cada 10ms
  TCCR0B = (1 << CS00) | (1 << CS02); //preescaler dividiendo 1024
  TIMSK0 = (1 << OCIE0A);             //Habilita las interrupciones entimer compare
}




/*********************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
*********************************************************************************************************/

/**
	\fn  		Nombre de la Funcion
	\brief 		Descripcion
 	\author 	Nombre
 	\date 		${date}
 	\param [in] 	parametros de entrada
 	\param [out] 	parametros de salida
	\return tipo 	y descripcion de retorno
*/


ISR(TIMER0_COMPA_vect)
{
  Multiplicador++;
  if (Multiplicador > 100)
  {
    PORTB ^= (1 << PORTB5);
    Multiplicador = 0;
  }
}


/*

Respetar este pin out.

PC0 -> BOTON 1 
PC1 -> BOTON 2 
PC2 -> BOTON 3 
PC3 -> BOTON 4

PD2 -> LED 1   
PD3 -> LED 2 
PD4 -> LED 3
PD5 -> LED 4 
PD6 -> LED 5 
PD7 -> LED 6
PB0 -> LED 7
PB1 -> LED 8

*/

/*
** The main function. Application starts here.
*/
int main (void)
{
 
  //! aca se escriben las inicializasiones
  DDRB = (1 << PB5);
  PORTB = (1 << PB5);
  config_TIMER0();
  sei(); //Habilita interrupciones globales

  while(1)
  {
   //! aca se escribe el programa principal
  }

  return 0;
}

/*********************************************************************************************************
** end of file
*********************************************************************************************************/
