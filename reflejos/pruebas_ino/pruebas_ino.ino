const int pulsador = 3;
const int ledPinVerde = 5;
const int ledPinRojo = 10;

void setup() {
  Serial.begin(9600);
  pinMode(ledPinVerde, OUTPUT);
  pinMode(ledPinRojo, OUTPUT);
  pinMode(pulsador, INPUT);
}

void loop() {
  //digitalWrite(ledPinVerde, digitalRead(pulsador));
  //digitalWrite(ledPinRojo, digitalRead(pulsador));
  digitalWrite(ledPinVerde, HIGH);
  Serial.println(digitalRead(pulsador));
}
