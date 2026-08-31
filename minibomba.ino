const int pinoBomba = 25;

void setup() {
  Serial.begin(115200);

  pinMode(pinoBomba, OUTPUT);
  digitalWrite(pinoBomba, LOW);

  Serial.println("Teste da mini bomba");
}

void loop() {

  Serial.println("BOMBA LIGADA");
  digitalWrite(pinoBomba, HIGH);
  delay(3000);

  Serial.println("BOMBA DESLIGADA");
  digitalWrite(pinoBomba, LOW);
  delay(10000);
}