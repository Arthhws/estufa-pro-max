const int pinoUmidade = 35;

const int valorSeco = 2390;
const int valorMolhado = 823;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
}

void loop() {
  int leitura = analogRead(pinoUmidade);

  int umidade = map(leitura, valorSeco, valorMolhado, 0, 100);

  umidade = constrain(umidade, 0, 100);

  Serial.print("ADC: ");
  Serial.print(leitura);

  Serial.print(" | Umidade: ");
  Serial.print(umidade);

  Serial.println("%");

  delay(1000);
}