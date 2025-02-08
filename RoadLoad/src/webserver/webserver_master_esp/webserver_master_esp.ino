#define TASK1_PIN 25 //My Task: Max Speed
#define TASK3_PIN 26 //MyTask: Balancing
#define TASK4_PIN 27 //Task from Sercan

#include <WiFi.h>
const char* ssid = "Galaxy XCover 5 278E";
const char* password = "yrar9667";

WiFiServer server(80);

String header;

String output25State = "off";
String output26State = "off";
String output27State = "off";

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  pinMode(TASK1_PIN,OUTPUT);
  pinMode(TASK3_PIN, OUTPUT);
  pinMode(TASK4_PIN, OUTPUT);
  
  digitalWrite(TASK1_PIN, LOW);
  digitalWrite(TASK3_PIN, LOW);
  digitalWrite(TASK4_PIN, LOW);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (client){
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n'){
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /TASK1/on") >= 0) {
              Serial.println("Max Speed Choosen");
              output25State = "on";
              digitalWrite(TASK1_PIN, HIGH);
            } else if (header.indexOf("GET /TASK1/off") >= 0) {
              Serial.println("No Speed");
              output25State = "off";
              digitalWrite(TASK1_PIN, LOW);
            } else if (header.indexOf("GET /TASK3/on") >= 0) {
              Serial.println("Balancing");
              output26State = "on";
              digitalWrite(TASK3_PIN, HIGH);
            } else if (header.indexOf("GET /TASK3/off") >= 0) {
              Serial.println("No Balancing");
              output26State = "off";
              digitalWrite(TASK3_PIN, LOW);
            } else if (header.indexOf("GET /TASK4/on") >= 0) {
              Serial.println("Draw Eight");
              output27State = "on";
              digitalWrite(TASK4_PIN, HIGH);
            } else if (header.indexOf("GET /TASK4/off") >= 0) {
              Serial.println("Draw No Eight");
              output27State = "off";
              digitalWrite(TASK4_PIN, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");

            // Display current state, and ON/OFF buttons for GPIO 25  
            client.println("<p>GPIO 25 - State " + output25State + "</p>");
            // If the output25State is off, it displays the ON button       
            if (output25State=="off") {
              client.println("<p><a href=\"/TASK1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/TASK1/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="off") {
              client.println("<p><a href=\"/TASK3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/TASK3/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/TASK4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/TASK4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println();
            break;
          } else {
            currentLine = "";
          }
        }else if (c!= '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client Disconnected.");
    Serial.println("");
  }
}
