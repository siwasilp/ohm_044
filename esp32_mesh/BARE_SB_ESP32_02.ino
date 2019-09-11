//====== 620828 - ESP32 to ESP32 [P2P]     ======
//====== Rqs. AJP 620827  CP. PK_LAB 2019  ====== 
//====== File 2/2  : BARE_SB_ESP32_02.ino  ======

#include <WiFi.h>
IPAddress server(192,168,4,15);    
WiFiClient client;

byte ledPin = 2;
char ssid[] = "pk_007";           // SSID of your AP
char pass[] = "12345678";         // password of your AP

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("BARE_SB_ESP32_02.ino");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledPin, HIGH);delay(250);
    Serial.print(".");
    digitalWrite(ledPin, LOW);delay(250);
  }
  Serial.println("Connected");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(ledPin, OUTPUT);
}

String msg="";      // *** OK use it
String answer="";   // *** OK use it

void loop() {
  Commu_sb();
}

void Commu_sb(){
  //======================================
  if (Serial.available()) {
  msg=Serial.readString();  }
  //======================================
  if(millis()%2000==0){  // Rqs. Time SYNC [2 Sec]
  client.connect(server, 80);
  digitalWrite(ledPin, HIGH);
  Serial.println("*******************************[My SB.]");
  Serial.print(" OUT > ");
  Serial.println(msg);
  client.print(msg+"\r");
  answer = client.readStringUntil('\r');
  Serial.println(" INP > " + answer);
  client.flush();
  digitalWrite(ledPin, LOW);
  client.stop();
  }
}

//=================== Commu_sb || OK. =====================
