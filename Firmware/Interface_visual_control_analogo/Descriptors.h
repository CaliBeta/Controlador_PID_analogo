#ifndef __Descriptors_H__
#define __Descriptors_H__

//Definicion de pines
//Comunicacion I2C
#define LCD_DIR   0x27
#define FILAS     2
#define COLUM     16
#define SDA       A4
#define SCL       A5

//Potenciometro digital Proporcional
#define INC1      3
#define U_D1      4
#define CS1       2

//Potenciometro digital Integral
#define INC2      5
#define U_D2      7
#define CS2       6

//Potenciometro digital Derivativo
#define INC3      8
#define U_D3      9
#define CS3       10

//Pulsadores de control
#define UP        A0
#define DOWN      A2
#define OK        A1

//Acciones de control
#define KP        11
#define KI        12
#define KD        13

#endif

