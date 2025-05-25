#include <WiFiS3.h>
#include <ArduinoOSCWiFi.h>
WiFiUDP Udp;

int status = WL_IDLE_STATUS;
#include "secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;

unsigned int localPort = 8101;

const int sendPort = 8001;
const char* sendIP = "192.168.4.2";

int touch1 = 0, touch2 = 0, touch3 = 0;
String incoming;

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }

  //check newest firmwareversion
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // Start the Access Point
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    while (true);
  } else {
    Serial.println("Access Point Created");
  }

  printWifiStatus();

  Serial.println("\nStarting connection to server...");

  // if you get a connection, report back via serial:
  Udp.begin(localPort);
}

void loop() {
  if (Serial1.available()) {
    String incoming = Serial1.readStringUntil('\n');  // non-blocking line-based read
    incoming.trim();                                  // remove whitespace and newline

    Serial.print("Received: ");
    Serial.println(incoming);

    if (incoming.startsWith("touch ")) {
      int id = incoming.substring(6).toInt();  // parse number after "touch "
      if (id == 0) touch1 = 1;
      else if (id == 1) touch2 = 1;
      else if (id == 2) touch3 = 1;
    } else if (incoming.startsWith("release ")) {
      int id = incoming.substring(8).toInt();  // parse number after "release "
      if (id == 0) touch1 = 0;
      else if (id == 1) touch2 = 0;
      else if (id == 2) touch3 = 0;
    }
  }

  OscWiFi.publish(sendIP, sendPort, "/arduino/touch1", touch1);
  OscWiFi.publish(sendIP, sendPort, "/arduino/touch2", touch2);
  OscWiFi.publish(sendIP, sendPort, "/arduino/touch3", touch3);
  OscWiFi.update();
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}