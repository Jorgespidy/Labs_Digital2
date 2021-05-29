/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server 
  Basándose en los ejemplos de: 
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**************************************************************************************************/
//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <WebServer.h>
//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
const char* ssid = "Jorge’s iPhone";  // Enter your SSID here
const char* password = "jagerules";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

int p1;
int p2;
int p3;
int p4;
int cant;

#define RX2 16
#define TX2 17

String libre = "\t <td style=\"background-color: #41A317;\"><h2><span style='font-size:100px;'>&#10004</h2></td>\t\n"; //se muestra en la tabla cuando haya un parqueo libre
String ocupado = "\t <td style=\"background-color: #E41B17;\"><h2><span style='font-size:100px;'>&#9940</h2></td>\t\n"; //cuando haya un parqueo ocupado
//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RX2, TX2);

  while (!Serial2);
  
  Serial.println("Try Connecting to ");
  Serial.println(ssid);



  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // para conexion ip
  
  
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}
//************************************************************************************************
// loop principal
//************************************************************************************************
void loop() {
  server.handleClient();

  if (Serial2.available() > 0) { //se guarda lo que le entra al UART2
    cant = Serial2.read();// aqui se guardan los valores binarios del UART1 de la TIVA
  }
  // parqueo 4
  if(cant >= 8){
     p4 = 1;
     cant = cant - 8;
  }
  else{
    p4 = 0;
  }

    // parqueo 3
  if(cant >= 4){
     p3 = 1;
     cant = cant - 4;
  }
  else{
    p3 = 0;
  }

    // parqueo 2
  if(cant >= 2){
     p2 = 1;
     cant = cant - 2;
  }
  else{
    p2 = 0;
  }

    // parqueo 1
  if(cant >= 1){
     p1 = 1;
     cant = cant - 1;
  }
  else{
    p1 = 0;
  }
  

}
//************************************************************************************************
// Handler de Inicio página
//************************************************************************************************
void handle_OnConnect() {
 
  server.send(10, "text/html", SendHTML2());
}
//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML2() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Parqueo-MATIC</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #E5E4E2;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";//platinum
  ptr += "table {";
  ptr += "  font-family: Helvetica, sans-serif;";
  ptr += "  border-collapse: collapse;";
  ptr += "  width: 100%;";
  ptr += "  margin: 50px auto 30px;";
  ptr += "  text-align: center;";
  ptr += "}";
  ptr += "td, th {";
  ptr += " border: 2px solid #101010;";
  ptr += " text-align: center;";
  ptr += " padding: 12px;  ";
  ptr += "  background-color: #C19A6B;";
  ptr += "}";
  ptr += "tr:nth-child(even) {";
  ptr += "  background-color: #FFFFFF;";
  ptr += "}  ";
  ptr += ".button {display: block;width: 80px;background-color: #C19A6B;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #C19A6B;}\n";
  ptr += ".button-on:active {background-color: #C19A6B;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Parqueo MATIC &#128664</h1>\n";
  ptr += "<h3>Jorge Castillo - 18209 </h3>\n";
  ptr += "<h2> </h2>";



  //************************ REFRESH 1HZ********************************
  ptr += "<script>\n";
  ptr += "<!--\n";
  ptr += "function timedRefresh(timeoutPeriod) {\n";
  ptr += "\tsetTimeout(\"location.reload(true);\",timeoutPeriod);\n";
  ptr += "}\n";
  ptr += "\n";
  ptr += "window.onload = timedRefresh(400);\n";
  ptr += "\n";
  ptr += "//   -->\n";
  ptr += "</script>";
  //********************************************************************

  //******************Tabla de parqueos******************************
  ptr += "</head>\n";
  ptr += "<body>\n";

  ptr += "<table>";
  ptr += " <table style= margin: 0 auto;>";
  ptr += " <tr>";
  ptr += "   <th><span style='font-size:40px;'>Parqueo 1</th>";
  ptr += "   <th><span style='font-size:40px;'>Parqueo 2 </th>";
  ptr += "   <th><span style='font-size:40px;'>Parqueo 3 </th>";
  ptr += "   <th><span style='font-size:40px;'>Parqueo 4</th>";
  ptr += " </tr>";
  ptr += "  <tr>";

  // Parqueo 1
  if (p1 == 0) {
    ptr += libre;
  }
  else if (p1 == 1) {
    ptr += ocupado;
  }

  // Parqueo 2
  if (p2 == 0) {
   ptr += libre;
  }
  else if (p2 == 1) {
    ptr += ocupado;
  }

  //Parqueo 3
  if (p3 == 0) {
    ptr +=  libre;
  }
  else if (p3 == 1) {
    ptr += ocupado;
  }

// Parqueo 4
  if (p4 == 0) {
    ptr += libre;
  }
  else if (p4 == 1) {
    ptr += ocupado;
  }
  

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
