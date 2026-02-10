#include <SoftwareSerial.h>

SoftwareSerial gps(2, 3); // RX, TX

bool isVerbose = true;

void setup() {

  // Start the serial monitor:
  if (isVerbose) 
    Serial.begin(9600);

  // set the data rate for the SoftwareSerial port
  gps.begin(9600);
  while (!gps) {
    delay(2); // wait
  }

  // set the gps port to listen:
  gps.listen();
  if (isVerbose)
    Serial.println("GPS is initialized!");

  // reduce noise to make sure gps hears command
  gps.println("$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28");

  // send balloon mode command to gps
  gps.print("$PMTK886,3*2B\r\n");
  Serial.println("Sent command!");

  // check to see if ballon mode was received and accepted
  if (waitForConfirmation886(3000)) 
    Serial.println("✅ Balloon mode command received");
  else
    Serial.println("⚠️ No command seen (check wiring/baud/command format/bad timing)");
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

//checks if gps returned confirmation string from balloon mode
bool waitForConfirmation886(unsigned long timeout_ms) {
  String line;
  unsigned long t0 = millis();

  while (millis() - t0 < timeout_ms) {
    while (gps.available()) {
      char c = gps.read();
      if (c == '\r') 
        continue;

      if (c == '\n') {
        if (line.length() > 0) {
          Serial.println(line);
          if (line.startsWith("$PMTK001,886,3")) 
            return true;
        }
        line = "";
      } else {
        if (line.length() < 120) 
          line += c;
        else 
          line = "";
      }
    }
  }
  return false;
}
