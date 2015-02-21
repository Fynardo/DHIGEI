const int pulsador = 3;
const int ledPinVerde = 5;
const int ledPinRojo = 10;
int estado = 0;
int reset = 0;
unsigned long timeIni;
unsigned long timeFin;
unsigned long timeRes;

void setup() {
 Serial.begin(9600);
 pinMode(ledPinVerde, OUTPUT);
 pinMode(ledPinRojo, OUTPUT);
 pinMode(pulsador, INPUT);
}

void loop() {
  if (estado == 0) { //Estoy con el led verde encencido
    digitalWrite(ledPinVerde,HIGH);
    if (digitalRead(pulsador) == HIGH) {
       delay(200);
       if (digitalRead(pulsador) == LOW) {
         estado = 1;
         digitalWrite(ledPinVerde,LOW);
       }
    }
    
  }
  
  if (estado == 1) { //Estoy en medio del delay
//    delay(200);
    attachInterrupt(1, maneja, HIGH);
    delay(random(500,1500));
    detachInterrupt(1);
    if (!reset){
      estado = 2;
    }
    reset = 0;
  }

  if (estado == 2) { //Estoy con el led rojo encendido     
      digitalWrite(ledPinRojo, HIGH);
      timeIni = millis();
      while (digitalRead(pulsador) == LOW); 
      
        while (digitalRead(pulsador) == HIGH);
      
        timeFin = millis();
        timeRes = timeFin - timeIni;
        
        digitalWrite(ledPinRojo, LOW);
        estado = 0;
        
        Serial.print(timeRes);
        Serial.print("ms  ");
        if (timeRes < 100)
          Serial.println("ENHORABUENA! Excelentes reflejos");
        else if (timeRes < 200)
                Serial.println("BIEN! Buenos reflejos");
             else 
                 Serial.println("Intente de nuevo");
  
        delay(1000);  
  }
}
 
void maneja() {
  if(estado == 1)
    if (digitalRead(pulsador) == HIGH) {
     Serial.println("NO SE PRECIPITE. Intente de nuevo");
     reset = 1;
     estado = 0;
  }
}


