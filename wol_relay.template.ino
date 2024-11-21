#include <WakeOnLan.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char* wifiSsId = <id>;
const char* wifiPassword = <password>;
const char* deviceMacAddress = <MAC>;
const char* endPoint = "GET /encryptedEndpoint ";

const char HTTP_OK[] = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\nConnection: close\r\n\r\n";
const char HTTP_404[] = "HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\n";

WiFiServer server(80);
WiFiUDP UDP;
WakeOnLan WOL(UDP);

void setup() {
  WiFi.begin(wifiSsId, wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
  WiFi.setSleep(WIFI_PS_MAX_MODEM);
  WOL.setRepeat(3, 100);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    char buffer[100];
    int index = 0;
    while (client.available() && index < sizeof(buffer) - 1) {
      char c = client.read();
      if (c == '\n')
        break;
      buffer[index++] = c;
    }
    buffer[index] = '\0';
    if (strstr(buffer, endPoint)) {
      client.print(HTTP_OK);
      WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask());
      WOL.sendMagicPacket(deviceMacAddress);  // int second param for port other than 9
    } else {
      client.print(HTTP_404);
    }
    client.stop();
  }
  delay(100);
}
