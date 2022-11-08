# TP5

## Uso de Timer. 

Utilizando un Arduino Nano (`atmega328p`), `8 LEDs` y `4 Pulsadores` se pide:

En el Trabajo Practico 3 se realiza una secuencia y se elimina el rebote de los pulsadores
mediante el uso de retardos. Esto produce 2 inconvenientes, por un lado un control de tiempo
es inexacto e imposible de ajustar utilizando lenguajes de alto nivel. Por otro lado, eliminar los
rebotes por espera y verificación implica el uso de código bloqueante, lo cual puede ser un inconveniente en muchas aplicaciones.

Retome el programa del TP3 y modifíquelo tal que:

1. Utilice **Interrupciones** por **TIMER** para controlar la velocidad del efecto de luces.

2.  Utilizar **detección de flanco** y **eliminación** de rebote por interrupción eliminando el código
bloqueante.

> Nota: Todos los pulsadores `deben` tener habilitada la resistencia de `pull-up`.

> el incremento o decremento debe de producirse en una unidad por pulsación. Utilice `debouncing` 

> Utilice Flags para no tener que mantener presionado los botones al cambiar de velocidad y que no aumente o disminuya de a varios niveles a la vez.

> Asi mismo los LEDs deben conectarse con su resistencia limitadora de corriente asegurando no superar la corriente máxima que puede entregar el pin. Al menos de 330 Ohms.

---

## ¡USAR LOS PINES INDICADOS NO CAMBIARLOS!

``` C
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

```
## Pinout

![PINOUT](Arduino-Nano-Pinout.png "pinout")

## Circuito

![Circuito](circuito.png "circuito")


## El auto fantástico. 

Utilizando un Arduino Nano (`atmega328p`), `8 LEDs` y `4 Pulsadores` se pide:

1. Al presionar el `pulsador 1` se **enciende** o se **apaga** el efecto.

2.  Al presionar los `pulsadores 2` y `3` **simultáneamente** *Baja* la velocidad del efecto.

3. Al presionar los `pulsadores 2` y `4` **simultáneamente** *Sube* la velocidad del efecto.

## Estados
![estados](estados.png "estados")

---
# clases grabadas que les pueden ser útilies 

