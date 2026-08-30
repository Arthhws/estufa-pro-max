#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Rede";
const char* senha = "Senha";

WebServer server(80);

const char pagina[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Teste</title>

  <style>
    body {
      font-family: Arial;
      text-align: center;
      margin-top: 50px;
    }

    input {
      padding: 12px;
      width: 70%;
      font-size: 18px;
    }

    button {
      padding: 12px 20px;
      font-size: 18px;
      margin-top: 10px;
    }
  </style>
</head>

<body>

  <h2>Enviar mensagem para o ESP32</h2>

  <input type="text" id="mensagem" placeholder="Digite alguma coisa">

  <br>

  <button onclick="enviar()">Enviar</button>

  <p id="resposta"></p>

  <script>
    function enviar() {
      let msg = document.getElementById("mensagem").value;

      fetch("/enviar?msg=" + encodeURIComponent(msg))
        .then(response => response.text())
        .then(data => {
          document.getElementById("resposta").innerHTML = data;
        });
    }
  </script>

</body>
</html>
)rawliteral";


void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println("Conectando ao Wi-Fi...");

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
    server.send(200, "text/html", pagina);
  });


  // Receber mensagem
  server.on("/enviar", []() {

    if (server.hasArg("msg")) {

      String mensagem = server.arg("msg");

      Serial.print("Mensagem recebida: ");
      Serial.println(mensagem);

      server.send(200, "text/plain", "Mensagem enviada!");

    } else {

      server.send(400, "text/plain", "Nenhuma mensagem recebida");
    }

  });


  server.begin();

  Serial.println("Servidor iniciado!");
}


void loop() {

  server.handleClient();

}