#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi de casa
const char* ssid = "x";
const char* senha = "y";

// LM35 no GPIO32 (D32)
const int pinoLM35 = 32;

WebServer server(80);


// ---------- LEITURA DO LM35 ----------
float lerTemperatura() {

  int leitura = analogRead(pinoLM35);

  float tensao = leitura * (3.3 / 4095.0);

  // LM35 = 10 mV por °C
  float temperatura = tensao * 100.0;

  return temperatura;
}


// ---------- SITE ----------
String pagina() {

  float temperatura = lerTemperatura();

  String html = R"rawliteral(
<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">

<title>Estufa Pro Max</title>

<style>

body {
  font-family: Arial;
  text-align: center;
  background-color: #f2f2f2;
  padding-top: 50px;
}

.caixa {
  background: white;
  width: 280px;
  margin: auto;
  padding: 30px;
  border-radius: 15px;
}

h1 {
  font-size: 25px;
}

.temperatura {
  font-size: 50px;
  font-weight: bold;
}

</style>

</head>

<body>

<div class="caixa">

<h1>Estufa Pro Max</h1>

<p>Temperatura atual</p>

<div class="temperatura">
)rawliteral";

  html += String(temperatura, 1);
  html += " &deg;C";

  html += R"rawliteral(
</div>

<p>LM35 + ESP32</p>

</div>

<script>

// Atualiza a página a cada 2 segundos
setTimeout(function(){
  location.reload();
}, 2000);

</script>

</body>
</html>
)rawliteral";

  return html;
}


// ---------- CONFIGURAÇÃO ----------
void setup() {

  Serial.begin(115200);

  analogReadResolution(12);

  Serial.println();
  Serial.println("Conectando ao Wi-Fi...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, senha);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");

  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());


  // Página principal
  server.on("/", []() {
    server.send(200, "text/html", pagina());
  });

  server.begin();

  Serial.println("Servidor iniciado!");
}


// ---------- LOOP ----------
void loop() {

  server.handleClient();

  static unsigned long tempoAnterior = 0;

  if (millis() - tempoAnterior >= 1000) {

    tempoAnterior = millis();

    Serial.print("Temperatura: ");
    Serial.print(lerTemperatura(), 1);
    Serial.println(" °C");
  }
}