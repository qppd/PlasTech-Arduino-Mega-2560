#include <SoftwareSerial.h>

#define MEGA_RX 7  // Connect to MEGA's TX
#define MEGA_TX 6  // Connect to MEGA's RX

SoftwareSerial MEGASerial(MEGA_RX, MEGA_TX);  // RX, TX

void initSERIAL() {
  Serial.begin(9600);     // Default serial monitor baud rate
  MEGASerial.begin(9600);  // Communication baud rate with MEGA
  Serial.println("NodeMCU ready to communicate with MEGA");
}

void receiveSERIAL() {
  if (MEGASerial.available()) {
    String data = MEGASerial.readStringUntil('\r\n');
    Serial.print("Receiving: ");
    Serial.print(data);
  }
}
