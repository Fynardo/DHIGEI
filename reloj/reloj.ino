#include <MsTimer2.h>

int horas;
int minutos;
int segundos;

void setup() {
  Serial.begin(9600);
  MsTimer2::set(1000, contar);
  MsTimer2::start();
}

void loop() {
  
  
}

void contar() {
  
  segundos = segundos + 1;
  if (segundos == 60) {
    segundos = 0;
    minutos = minutos + 1;
    if (minutos == 60) {
      minutos = 0;
      horas = horas + 1;
      if (horas == 24) {
        horas = 0;
      }
    }
  }
  Serial.print(horas);
  Serial.print(":"); 
  Serial.print(minutos);
  Serial.print(":");
  Serial.println(segundos);
}
