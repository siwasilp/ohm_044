//======  620828 - ESP8266 to ESP8266 [P2P]  ======
//======  Rqs. AJP 620827  CP. PK_LAB 2019   ====== 
//======  File 1/2 : accesspoint_bare_01.ino ======

#include <ESP8266WiFi.h>
WiFiServer server(80);
IPAddress IP(192,168,4,15);  
IPAddress mask = (255, 255, 255, 0);

byte ledPin = 2;
char ssid[] = "pk_007";           // SSID of your AP
char pass[] = "12345678";         // password of your AP

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("accesspoint_bare_01.ino");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,pass);
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  pinMode(ledPin, OUTPUT);
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
}

String msg = "";       // *** OK use it
String request = "";   // *** OK use it

void loop() {
  Commu_ap();
}

void Commu_ap(){
  WiFiClient client = server.available();
  //============================================
  if (Serial.available()) {
  msg=Serial.readString();  }
  //===========================================
  if (!client) {return;}
  digitalWrite(ledPin, LOW);
  request = client.readStringUntil('\r');
  Serial.println("********************************[My AP.]");
  Serial.println(" INP > " + request);
  client.flush();
  Serial.print(  " OUT > ");   Serial.println(msg);
  client.println(msg + "\r");  client.println(request + "\r");
  digitalWrite(ledPin, HIGH); 
  }
  
//================== Commu_ap || OK. ==================
