//Funciones de visualizacion en el LCD
void sel_ganancia(String nombre, uint8_t pulsos, float val) {
  lcd.setCursor(0, 0);
  lcd.print("Seleccione ");
  lcd.print(nombre);
  lcd.setCursor(3, 1);
  lcd.print(pulsos);
  lcd.setCursor(7, 1);
  lcd.print(val);
}
//-------------------------------------------------------------

void mostrar_ganancias() {
  //Control P
  if (tipo_control == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Con=");
    lcd.print(controlador[tipo_control]);
    lcd.setCursor(7, 0);
    lcd.print(" Kp=");
    lcd.print(Kp);
    lcd.setCursor(0, 1);
    lcd.print("Ki=0.0");
    lcd.setCursor(8, 1);
    lcd.print(" Kd=0.0");
  }
  //Control PI
  else if (tipo_control == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Con=");
    lcd.print(controlador[tipo_control]);
    lcd.setCursor(7, 0);
    lcd.print(" Kp=");
    lcd.print(Kp);
    lcd.setCursor(0, 1);
    lcd.print("Ki=");
    lcd.print(Ki);
    lcd.setCursor(8, 1);
    lcd.print(" Kd=0.0");
  }
  //Control PD
  else if (tipo_control == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Con=");
    lcd.print(controlador[tipo_control]);
    lcd.setCursor(7, 0);
    lcd.print(" Kp=");
    lcd.print(Kp);
    lcd.setCursor(0, 1);
    lcd.print("Ki=0.0");
    lcd.setCursor(8, 1);
    lcd.print(" Kd=");
    lcd.print(Kd);
  }
  //Control PID
  else if (tipo_control == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Con=");
    lcd.print(controlador[tipo_control]);
    lcd.setCursor(7, 0);
    lcd.print(" Kp=");
    lcd.print(Kp);
    lcd.setCursor(0, 1);
    lcd.print("Ki=");
    lcd.print(Ki);
    lcd.setCursor(8, 1);
    lcd.print(" Kd=");
    lcd.print(Kd);
  }
}
//-------------------------------------------------------------

void acciones_control(String nombre) {
  lcd.setCursor(1, 0);
  lcd.print("Seleccione el");
  lcd.setCursor(0, 1);
  lcd.print("controlador(");
  lcd.print(nombre);
  lcd.print(")");
}

