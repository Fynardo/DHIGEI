/* DISPOSITIVOS HARDWARE E INTERFACES
 * Practica 2: Reloj
 * 
 * Autor: Diego Noceda Davila
 * Fecha: 26/02/2015
 *
 * El programa es un reloj que se actualiza una vez por segundo mediante 
 * un timer (librera MsTimer2) y envia la hora por el puerto serie. La funcion
 * "contar" es la encargada de actualizar la hora cada vez que salta la 
 * interrupcion del timer, cambiar el estado de los leds e imprimir en el 
 * puerto serie.
 * Para la puesta en hora del arduino se lee la entrada del puerto serie con
 * las funciones "Serial.available()" y "Serial.readBytes()", luego se "parsean"
 * los valores de hora, minuto y segundo con la funcion "strtok" de C. Tras leer los
 * nuevos valores de la hora se comprueba que ninguno se salga del limite y se actualizan
 * los valores. Si alguno de los valores excede el limite se pasa al modo "power-down",
 * del cual podremos salir accionando el pulsador (a traves de la interrupcion externa 1,
 * funcion "interrupcion")
*/

#include <MsTimer2.h>
#include <avr/sleep.h>

const int ledRojo = 10;
const int ledVerde = 5;
const int boton = 3;

int estadoLed  = HIGH;
int horas = 0;
int horas_prov;
int minutos = 0;
int minutos_prov;
int segundos = 0;
int segundos_prov;

char leido[9];
char * token;

void setup() {
  Serial.begin(9600);
  
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(boton, INPUT);
  
  MsTimer2::set(1000, contar);
  MsTimer2::start();

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(1,interrupcion, RISING);
}

//Manejo de la interrupcion, salir del modo power-down
void interrupcion() {
 sleep_disable(); 
}

void loop() {
  //Lectura de la hora enviada por puerto serial
  if (Serial.available() > 0) {  
    Serial.readBytes(leido, 8);
    leido[8] = 0;
    
    //Valor leido, provisional, de las horas
    token = strtok(leido, ":"); 
    horas_prov = atoi(token); 
    
    //Valor leido, provisional, de los minutos  
    token = strtok(0,":"); 
    minutos_prov = atoi(token);
    
    //Valor leido, provisional, de los segundos
    token = strtok(0,":"); 
    segundos_prov = atoi(token);
      
    //Paso condicional al modo power-down  
    if (horas_prov > 23 || minutos_prov > 59 || segundos_prov > 59){
      Serial.println("modo power down!");
      delay(20);
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde,LOW);
      sleep_mode();
    }    
    else { 
      //Actualiza la hora
      horas = horas_prov;
      minutos = minutos_prov;
      segundos = segundos_prov;
    }
      
    //limpia la entrada
    Serial.flush();  
    leido[0] = 0;
 
  }  
}

void contar() {
  //Cambio del estado de los led
  digitalWrite(ledVerde, estadoLed);
  digitalWrite(ledRojo, !estadoLed);
  estadoLed = !estadoLed;
  //---
  
  //Actualizacion de la hora
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
  //-----
  
  //Impresion de la hora por el puerto serie
  Serial.print(horas);
  Serial.print(":"); 
  Serial.print(minutos);
  Serial.print(":");
  Serial.println(segundos);
  //-----
}
