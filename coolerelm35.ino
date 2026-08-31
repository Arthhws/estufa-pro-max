const int pinoLM35 = 32;
const int pinoCooler = 26;

void setup() {
  Serial.begin(115200);

  pinMode(pinoCooler, OUTPUT);
  digitalWrite(pinoCooler, LOW);

  analogReadResolution(12);

  Serial.println("Teste LM35 + Cooler");
}

void loop() {
  int leitura = analogRead(pinoLM35);

  float tensao = leitura * (3.3 / 4095.0);
  float temperatura = tensao * 100.0;

  Serial.print("ADC: ");
  Serial.print(leitura);

  Serial.print(" | Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.println(" °C");

  // Liga o cooler se chegar a 30 °C
  if (temperatura >= 14.0) {
    digitalWrite(pinoCooler, HIGH);
    Serial.println("COOLER: LIGADO");
  }

  // Desliga abaixo de 28 °C
  else if (temperatura <= 28.0) {
    digitalWrite(pinoCooler, LOW);
    Serial.println("COOLER: DESLIGADO");
  }

  Serial.println("--------------------");

  delay(1000);
}