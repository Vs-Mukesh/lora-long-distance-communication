#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 15
#define RFM95_RST 16
#define RFM95_INT 2

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(9600);

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  if (!rf95.init()) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  rf95.setFrequency(433.0);

  Serial.println("Receiver with ADR Ready");
}

void loop() {
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      String data = "";

      for (int i = 0; i < len; i++) {
        data += (char)buf[i];
      }

      int rssi = rf95.lastRssi();

      Serial.print("Received: ");
      Serial.println(data);

      Serial.print("RSSI: ");
      Serial.println(rssi);

      // 🔥 ADR Logic (Decision Making)
      if (rssi > -70) {
        Serial.println("Strong signal → Reduce power / increase data rate");
      }
      else if (rssi < -100) {
        Serial.println("Weak signal → Increase power / reduce data rate");
      }
      else {
        Serial.println("Moderate signal → Keep settings");
      }

