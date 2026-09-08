#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "218CLARO_2G";
const char* senha = "Weiss36337420";

const int pinoLampada = 27;

WebServer server(80);

void paginaPrincipal() {
  String pagina = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body {
        font-family: Arial;
        text-align: center;
        margin-top: 50px;
      }

      button {
        width: 180px;
        height: 70px;
        font-size: 22px;
        margin: 10px;
        border: none;
        border-radius: 10px;
      }

      .ligar {
        background: #4CAF50;
        color: white;
      }

      .desligar {
        background: #f44336;
        color: white;
      }
    </style>
  </head>

  <body>
    <h1>Estufa Pro Max</h1>
    <h2>Controle da Lâmpada</h2>

    <a href="/ligar">
      <button class="ligar">LIGAR</button>
    </a>

    <a href="/desligar">
      <button class="desligar">DESLIGAR</button>
    </a>
  </body>
  </html>
  )rawliteral";

  server.send(200, "text/html", pagina);
}

void ligarLampada() {
  digitalWrite(pinoLampada, HIGH);
  Serial.println("LAMPADA LIGADA");

  server.sendHeader("Location", "/");
  server.send(303);
}

void desligarLampada() {
  digitalWrite(pinoLampada, LOW);
  Serial.println("LAMPADA DESLIGADA");

  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  pinMode(pinoLampada, OUTPUT);
  digitalWrite(pinoLampada, LOW);

  WiFi.begin(ssid, senha);

  Serial.print("Conectando");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WIFI CONECTADO");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", paginaPrincipal);
  server.on("/ligar", ligarLampada);
  server.on("/desligar", desligarLampada);

  server.begin();

  Serial.println("Servidor iniciado");
}

void loop() {
  server.handleClient();
}