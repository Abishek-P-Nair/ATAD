#include <WiFi.h>

// Wi-Fi Credentials
const char* ssid = "ESP32_AP";
const char* password = "12345678";
WiFiServer server(4210);

// LoRa Module UART Pins
#define LORA_TX 17  // ESP32 TX -> LoRa RX
#define LORA_RX 16  // ESP32 RX <- LoRa TX

HardwareSerial LoRaSerial(1);

void setup() {
    Serial.begin(115200);
    LoRaSerial.begin(115200, SERIAL_8N1, LORA_RX, LORA_TX); // Initialize LoRa UART

    // Start Wi-Fi AP
    WiFi.softAP(ssid, password);
    Serial.println("ESP32 AP Started");
    Serial.print("ESP32 AP IP: ");
    Serial.println(WiFi.softAPIP());
    
    server.begin();

    delay(1000);
    Serial.println("Configuring LoRa module...");

    // Check LoRa module connection
    LoRaSerial.print("AT\r\n");
    delay(500);
    while (LoRaSerial.available()) {
        Serial.write(LoRaSerial.read());
    }

    // Set LoRa parameters
    LoRaSerial.print("AT+ADDRESS=0\r\n");   // Sender Address: 0
    delay(500);
    LoRaSerial.print("AT+NETWORKID=5\r\n"); // Network ID (must match receiver)
    delay(500);
    LoRaSerial.print("AT+PARAMETER=12,7,1,4\r\n"); // SF=12, BW=7, CR=1, PL=4
    delay(500);

    Serial.println("LoRa setup complete.");
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        Serial.println("Client connected");
        unsigned long lastDataTime = millis();

        while (client.connected()) {
            if (client.available()) {
                String gpsData = client.readStringUntil('\n');
                gpsData.trim();
                Serial.println("Received GPS Data: " + gpsData);

                if (gpsData.length() > 0) {
                    sendToLoRa(gpsData);
                }

                client.println("ACK: " + gpsData);
                lastDataTime = millis();
            }

            if (millis() - lastDataTime > 10000) {
                Serial.println("Client timeout, disconnecting...");
                break;
            }
        }

        client.stop();
        Serial.println("Client disconnected");
    }
}

void sendToLoRa(String data) {
    String command = "AT+SEND=1," + String(data.length()) + "," + data + "\r\n";
    LoRaSerial.print(command);
    Serial.println("Sent to LoRa: " + command);
}
