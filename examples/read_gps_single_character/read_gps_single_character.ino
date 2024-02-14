
#include <SoftwareSerial.h>

SoftwareSerial gps(2, 3); // RX, TX

bool isVerbose = true;

void setup() {

  // Start the serial monitor:
  if (isVerbose) Serial.begin(9600);

  // set the data rate for the SoftwareSerial port
  gps.begin(9600);
  while (!gps) {
    delay(2); // wait
  }

  // set the gps port to listen:
  gps.listen();
  if (isVerbose) Serial.println("GPS is initialized!");  
  
}

void loop() {
  // put your main code here, to run repeatedly:

  char t;
  if (gps.available()) {
    t = gps.read();
    if (isVerbose) {
      Serial.print(t);
    }
  } 
  delay(1);

}
