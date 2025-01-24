// These are the pins your MicroSD Card Adapter will be connected to.
// These pins are specific and should not change. You do not need to worry
// about why these are the pins, just connect them as listed.
// MOSI - pin 11
// MISO - pin 12
// CLK  - pin 13
// CS   - pin 10
const int chipSelect = 10;

// ############### START EDITING HERE (1/2) ###############
// Adjust the following pins according to your setup

// Pin for voltage divider
const int vDivPin = A0;

// Pin for first TMP36
const int tmp1Pin = A1;

// Pin for second TMP36
const int tmp2Pin = A2;

// Pin for pressure sensor
const int pressPin = A3;

// Pin for humidity sensor
const int humidPin = A4;

// Pins for accelerometer
const int accelxPin = A5;
const int accelyPin = A6;
const int accelzPin = A7;

// ############### END EDITING HERE (1/2) ###############

// For future labs, you may find it helpful to copy the above settings for additional sensors.
// **HINT HINT WINK WINK**

// This is the string that goes at the top of your csv file. They are the column headers for your spreadsheet.
const String header = "Time (ms),Voltage (V),TMP36_1 (V),TMP36_2 (V),Pressure (V),Humidity (V),Accel_x (V),Accel_y (V),Accel_z (V)";

#include <SPI.h>
#include <SD.h>

void setup() {
    Serial.begin(9600);

    delay(100); // arbitrary delay to let the serial monitor start up
    Serial.print("Initializing SD card...");

    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        // don't do anything more:
        while (1);
    }
    Serial.println("card initialized.");

    // now, before we actually start reading data, we need to write the header to the file.
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.csv", FILE_WRITE);
    if (dataFile) {
        dataFile.println(header);
        dataFile.close();
    } else {
        Serial.println("error opening datalog.csv");
    }
}

void loop() {

    // Note: in future labs, you may need to change this to add additional sensors.

    // ############### START EDITING HERE (2/2) ###############

    double vDivVal = analogRead(vDivPin); // Battery voltage reading (THIS IS FROM VOLTAGE DIVIDER AND IS RAW)
    
    double vDivAdj = ???; // What should this line be to make the vDivAdj accurately reflect the battery voltage?

    // ############### END EDITING HERE (2/2) ###############

    double tmp1Val = analogRead(tmp1Pin) * 5.0 / 1023.0; // First temperature reading (voltage)
    double tmp2Val = analogRead(tmp2Pin) * 5.0 / 1023.0; // Second temperature reading (voltage)
    double pressVal = analogRead(pressPin) * 5.0 / 1023.0; // Pressure reading (voltage)
    double humidVal = analogRead(humidPin) * 5.0 / 1023.0; // Humidity reading (voltage)
    double accelxVal = analogRead(accelxPin) * 5.0 / 1023.0; // X-Acceleration reading (voltage)
    double accelyVal = analogRead(accelyPin) * 5.0 / 1023.0; // Y-Acceleration reading (voltage)
    double accelzVal = analogRead(accelzPin) * 5.0 / 1023.0; // Z-Acceleration reading (voltage)

    // Now let's make a nice string to write to the file.
    // This is a comma-separated value (csv) file, so we need to separate each value with a comma.
    String dataString = "";
    // add the time (since boot) in milliseconds
    dataString += String(millis());
    dataString += ",";
    // add the adjusted voltage divider value
    dataString += String(vDivAdj);
    dataString += ",";
    // add the first TMP36 value
    dataString += String(tmp1Val);
    dataString += ",";
    // add the second TMP36 value
    dataString += String(tmp2Val);
    dataString += ",";
    // add the pressure value
    dataString += String(pressVal);
    dataString += ",";
    // add the humidity value
    dataString += String(humidVal);
    dataString += ",";
    // add the x-accel value
    dataString += String(accelxVal);
    dataString += ",";
    // add the y-accel value
    dataString += String(accelyVal);
    dataString += ",";
    // add the z-accel value
    dataString += String(accelzVal);

    // now let's open the file again
    File dataFile = SD.open("datalog.csv", FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
        dataFile.println(dataString);
        dataFile.close();
    }
    // if the file isn't open, pop up an error:
    else {
        Serial.println("error opening datalog.txt");
    }

    // This line means we will be printing data to the SD card about once every 500 milliseconds, or half a second
    delay(500);
}