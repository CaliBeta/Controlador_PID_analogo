/*
  Project : Interface visual lcd
  Version : 2.0
  Date    : 15/10/2017
  Author  : Carlos Andres Betancourt
  Company :  Ingenialo industrias SAS
  Comments:

  Chip type               : ATmega32U4-AU
  Program type            : Application
  AVR Core Clock frequency: 16.000000 MHz
  Memory model            : Small
  External RAM size       : 0
  Data Stack size         : 512
  commit: Cambio de potenciometros mecanicos por digitales
  ------------------------------------------------------------
  Conexiones electricas
  lcd I2C
  VCC pin a +5V
  SDA pin a pin digital 2
  SCL pin a pin digital 3
  GND pin a GND

  Potenciometro digital XC104P
  INC(1) pin a pin digital INC(x)
  U/D(2) pin a pin digital U_D(x)
  Rhi(3) pin no se conecta
  GND(4) pin a GND
  Wiper(5) pin a OPAM correcpondiente del controlador PID
  Rlo(6) pin a OPAM correcpondiente del controlador PID
  CS(7) pin a pin digital CS(x)
  VCC(8) pin a +5V
  ------------------------------------------------------------*/

//Incluimos las librerias necesarias
#include "Descriptors.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//-----------------------------------------------------------

//Instanciamos los objetos de las librerias
LiquidCrystal_I2C lcd(LCD_DIR, COLUM, FILAS);
//-----------------------------------------------------------

//Declaramos las variables necesarias
String controlador[] = {"P", "PI", "PD", "PID"};
uint8_t tipo_control = 0;
//Almacena la cantidad de pulsos U/D para cada potenciometro
uint8_t pulsos[3] = {0, 0, 0};
uint8_t estado = 0;

float Ci = 0.000010;
float Cd = 0.000047;
float R1p = 10000;
float R2p = 1000;
float R1i = 10000;
float R1d = 1000;
float R3p;
float R2i;
float R2d;
float Kp;
float Ki;
float Kd;
//-------------------------------------------------------------

//Funcion de configuracion
void setup() {
  //Serial.begin(115200); //Puerto Serial a 115200 baudios
  lcd.init();       //inicializamos el LCD
  lcd.backlight();  //Activamos la luz de fondo

  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(OK, INPUT);

  pinMode(INC1, OUTPUT);
  pinMode(INC2, OUTPUT);
  pinMode(INC3, OUTPUT);
  pinMode(U_D1, OUTPUT);
  pinMode(U_D2, OUTPUT);
  pinMode(U_D3, OUTPUT);
  pinMode(CS1, OUTPUT);
  pinMode(CS2, OUTPUT);
  pinMode(CS3, OUTPUT);

  //Ponemos todos los pines de control en estado bajo
  digitalWrite(INC1, LOW);
  digitalWrite(U_D1, LOW);
  digitalWrite(CS1, LOW);
  digitalWrite(INC2, LOW);
  digitalWrite(U_D2, LOW);
  digitalWrite(CS2, LOW);
  digitalWrite(INC3, LOW);
  digitalWrite(U_D3, LOW);
  digitalWrite(CS3, LOW);

  //Ponemos todos los pines de las acciones de control en estado bajo
  digitalWrite(KP, LOW);
  digitalWrite(KI, LOW);
  digitalWrite(KD, LOW);
  
  //Aseguramos que todos los potenciometros inicien en la posicion 0
  almacenar(INC1, U_D1, CS1);
  almacenar(INC2, U_D2, CS2);
  almacenar(INC3, U_D3, CS3);

  lcd.setCursor(1, 0);
  lcd.print("Ganancias del");
  lcd.setCursor(2, 1);
  lcd.print("controlador");
  delay(3000);
  lcd.clear();
}

//Funcion de bucle infinito
void loop() {
  R3p = calcula_Rpot(100, pulsos[0], 200000);
  R2i = calcula_Rpot(100, pulsos[1], 200000);
  R2d = calcula_Rpot(100, pulsos[2], 200000);

  Kp = (R2p + R3p) / R1p;
  Ki = 1 / ((R1i + R2i) * Ci);
  Kd = (Cd * (R1d + R2d)) / 1.2;

  //dependiendo del estado, se ejecutan diversas funciones
  switch (estado) {
    case 0:
      acciones_control(controlador[tipo_control]);
      sel_controlador(tipo_control);
      break;

    case 1:
      sel_ganancia("Kp(P)", pulsos[0], Kp);
      break;

    case 2:
      sel_ganancia("Ki(I)", pulsos[1], Ki);
      break;

    case 3:
      sel_ganancia("Kd(D)", pulsos[2], Kd);
      break;

    case 4:
      mostrar_ganancias();
      break;
  }

  //Condiciones para incrementar el valor de los potenciometros
  if (digitalRead(UP) == HIGH && digitalRead(DOWN) == LOW) {
    if (tipo_control < 3 && estado == 0) {
      tipo_control++;
      delay(300);
      lcd.clear();
    }
    if (pulsos[0] < 99 && estado == 1) {
      incremento(INC1, U_D1, CS1);
      pulsos[0]++;
      delay(300);
      lcd.clear();
    }
    else  if (pulsos[1] < 99 && estado == 2) {
      incremento(INC2, U_D2, CS2);
      pulsos[1]++;
      delay(300);
      lcd.clear();
    }
    else if (pulsos[2] < 99 && estado == 3) {
      incremento(INC3, U_D3, CS3);
      pulsos[2]++;
      delay(300);
      lcd.clear();
    }
  }

  //Condiciones para decrementar los valores de los potenciometros
  else if (digitalRead(UP) == LOW && digitalRead(DOWN) == HIGH) {
    if (tipo_control > 0 && estado == 0) {
      tipo_control--;
      delay(300);
      lcd.clear();
    }
    if (pulsos[0] > 0 && estado == 1) {
      decremento(INC1, U_D1, CS1);
      pulsos[0]--;
      delay(300);
      lcd.clear();
    }
    else if (pulsos[1] > 0 && estado == 2) {
      decremento(INC2, U_D2, CS2);
      pulsos[1]--;
      delay(300);
      lcd.clear();
    }
    else if (pulsos[2] > 0 && estado == 3) {
      decremento(INC3, U_D3, CS3);
      pulsos[2]--;
      delay(300);
      lcd.clear();
    }
  }

  //Condicion para saltar al siguiente estado
  else if (digitalRead(OK) == HIGH) {
    estado++;
    delay(300);
    lcd.clear();
  }

  //Condicion de retorno al inicio
  if (estado > 4) {
    estado = 0;
  }
}
