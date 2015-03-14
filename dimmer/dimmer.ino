#include <LiquidCrystal.h>

/*** Declaración de variables (globales por comodidad para la práctica) ***/
int pulsador = 7;

// Inicializacion del LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
/*****/

void setup() { 
  //Setup de la LCD
  lcd.begin(16, 2);
  analogWrite(6,60);
  
}
 
void loop() {
  
}
