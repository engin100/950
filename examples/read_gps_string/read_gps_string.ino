#include <SoftwareSerial.h>

SoftwareSerial gps(2, 3); // RX, TX

bool isVerbose = true;

const int nChars = 500;
char gps_string[nChars];

// This function clears the GPS data array:
void clear_gps_string() {
  for (int i = 0; i < nChars ; i++) gps_string[i] = '\0';
}

// This function reads the GPS data into an array. It does this
// in 3 steps:
// 1. Wait until the buffer is cleared out (in case we arrive in
//    the middle of a message.
// 2. Wait until the buffer is available again.
// 3. Read the buffer.

void read_gps() {

  char t;

  // If we arrive in the middle of a gps_available
  // wait for that to go away:
  while (gps.available()) {
    t = gps.read(); // do nothing
    delay(1);
  }

  // ok, now wait until the gps is available again:
  while (!gps.available()) {
    delay(1); // do nothing
  }

  // now read in the GPS data:
  int iChar = 0;
  while (gps.available()) {
    gps_string[iChar] = gps.read();
    iChar++;
    delay(1);
  }

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

// Set up the gps and the Serial port:
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

// Read in the GPS and display it.
void loop() {
  clear_gps_string();
  read_gps();
  if (isVerbose) Serial.println(gps_string);
  delay(5000);
}