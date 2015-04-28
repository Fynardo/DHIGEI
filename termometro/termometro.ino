#include <MsTimer2.h>

const int sensorPin = A0;
const int Ts = 5;
const int Tp = 40;
int n = 0;

int tmp = 0;
int tmpAcum = 0;

// Asignación de pines a segmentos
const byte segs[8]= {10,11,7,6,4,8,5,9}; //p-k-f-e-d-c-b-a

// Asignación de pines a dígitos
const byte digs[2]= {3,2}; // 1-2

// Segmentos que encienden cada dígito del 0 al 9
const byte digitos[10]= {0b00111111, 0b00000110, 0b11011011,
            0b01001111, 0b11100110, 0b11101101, 0b11111101,
            0b00000111, 0b11111111, 0b11101111};

byte byte1 = 0;
byte byte2 = 0;
byte digito = 0;

void setup() {
  Serial.begin(9600);
  
  analogReference(INTERNAL);
  
  for (int pin= 2; pin< 12; pin++) { // Pone modo salidas
    pinMode(pin, OUTPUT);
  }  
  
  
  MsTimer2::set(Ts, actualizar); // Int. Timer2 cada Ts ms
  MsTimer2::start();
}

void loop() {

}

void actualizar() {
 tmpAcum += (analogRead(sensorPin) - 5120/11)*110/1025;
 
 if(n++==Tp){
  n = 0;
  tmp = tmpAcum/Tp;
  tmpAcum = 0;
 }
 
 byte1 = tmp/10;
 byte2 = tmp%10;
 
  digitalWrite(digs[0],HIGH); // Apaga D1
  digitalWrite(digs[1],HIGH); // Apaga D2
  switch (digito) {
    case 0:
    segmentos(byte1); // Saca segmentos digito 1
    digitalWrite(digs[digito],LOW); // Enciende D1
    digito= 1;
    break;
    case 1:
    segmentos(byte2); // Saca segmentos digito 2
    digitalWrite(digs[digito],LOW); // Enciende D2
    digito= 0;
    break;
  }
 
 
}

void segmentos(byte valor) {
  for(int seg= 0; seg< 8; seg++) {
    digitalWrite(segs[seg], !bitRead(digitos[valor], seg));
  }
}

