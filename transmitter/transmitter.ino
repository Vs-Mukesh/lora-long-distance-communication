#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 15
#define RFM95_RST 16
#define RFM95_INT 2

RH_RF95 rf95(RFM95_CS, RFM95_INT);

int txPower = 20;

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
  rf95.setTxPower(txPower, false);

  Serial.println("Transmitter with ADR Ready");
}

void loop() {
  String data = "28.5,65.2,101325,300";

  rf95.send((uint8_t *)data.c_str(), data.length());
  rf95.waitPacketSent();

  Serial.println("Sent: " + data);

  delay(3000);
}
