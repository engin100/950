

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
  if (isVerbose) Serial.println("GPS is initialized!");  

}

// Read in the GPS and display it.
void loop() {

  clear_gps_string();
  read_gps();
  if (isVerbose) Serial.println(gps_string);

}
