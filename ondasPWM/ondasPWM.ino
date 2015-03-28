/* DISPOSITIVOS HARDWARE E INTERFACES
 * Práctica 6: Generación PWM y adquisición de señales *
 * Autores: Enrique Goberna García / Diego Noceda Davila
 * Fecha: XX/XX/2015
 *
 */

#include <MsTimer2.h>

const float pi= 3.1416;
const unsigned int Ts= 5; // Intervalo entre puntos generados ms
const unsigned int Tg= 5; // Intervalo entre puntos leidos
const unsigned int Vm= 50; // Voltaje máximo*10 en V

volatile unsigned int n= 0; // Número del punto (0 a N-1)
volatile unsigned int ch[6]; // Valores calculados  

//Variables de las señales
unsigned const int dc = 512;
unsigned int N= 200; // Número de puntos por ciclo
unsigned int Ns[4] = {200,200,200,200};
unsigned int Am1= 0;
unsigned int Am2= 0;

//Potenciómetros
const int potA1 = A2;
const int potA2 = A3;
const int potF = A4;
//Switches
const int sw1 = 3;
const int sw2 = 2;
//PWM
const int pg1 = 9;
const int pg2 = 10;

const int pr1 = A0;
const int pr2 = A1;
//Señales
unsigned int sg1, sr1, sg2, sr2;

void setup() {
  Serial.begin(1000000);  
  //Serial.begin(9600);  
  
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  //pinMode(sg1, OUTPUT);
  //pinMode(sg2, OUTPUT);
  
  MsTimer2::set(Ts, actualizar); // Int. Timer2 cada Ts ms
  MsTimer2::start();
}

void loop() {
  Am1 = map(analogRead(potA1), 0, 1023, 0, 511);
  Am2 = map(analogRead(potA2), 0, 1023, 0, 511);
 // N = map(analogRead(potF), 0, 1023, 50, 4000);
  Ns[0] = analogRead(potF);
  Ns[1] = analogRead(potF);
  Ns[2] = analogRead(potF);
  Ns[3] = analogRead(potF); 
  N = map(Ns[0] + Ns[1] + Ns[2] + Ns[3] /4, 0, 1023, 50, 4000);
 
 /* Serial.print(analogRead(potA1));
  Serial.print(" - "); 
  Serial.print(analogRead(potA2));
  Serial.print(" - "); 
  Serial.println(analogRead(potF)); 
  delay(50);
 */
}

void actualizar() {
  sg1 = dc + Am1*sin(n*2*pi/N); 
  sg1 = map(sg1, 0, 1023, 0, 255);
  analogWrite(pg1, sg1);
  ch[0] = analogRead(pr1);
  
  sg2 = dc + Am2*sin(n*2*pi/N); 
  sg2 = map(sg2, 0, 1023, 0, 255);
  analogWrite(pg2, sg2);
  ch[1] = analogRead(pr2);
  
  ch[2] = N;
  ch[3] = 0;
  ch[4] = 0;
  ch[5] = 0;
    
    if (n++== N) { // Incrementa número índice del punto
      n= 0;
    }  
    // Envía mensaje de datos cada Ts ms a Visorduino
    Serial.print("A6"); // Cabecera de mensaje
    Serial.write(Ts); // Envía intervalo tiempo Ts  
    Serial.write(Vm); // Envía voltaje máximo   
    for (int i=0; i<6; i++) {
      Serial.write(ch[i] & 0xFF); //  Envía Byte bajo de Chi
      Serial.write((ch[i] >> 8) & 0x03); // y byte alto  
    }
 
}
