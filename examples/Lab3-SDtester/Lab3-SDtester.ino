// These are the pins your MicroSD Card Adapter will be connected to.
// These pins are specific and should not change. You do not need to worry
// about why these are the pins, just connect them as listed.
// MOSI - pin 11
// MISO - pin 12
// CLK  - pin 13

// Update this variable to the correct pin 
const int SDLoggerChipSelect = ??;

// This is the string that goes at the top of your csv file. They are the column headers for your spreadsheet.
const String header = "Time (ms),Voltage (V),TMP36 (V),BME_Temp (V),Pressure (V),Humidity (V),Accel_x (V),Accel_y (V),Accel_z (V)";

#include <SPI.h>
#include <SD.h>

void setup() {
    Serial.begin(9600);

    delay(100); // arbitrary delay to let the serial monitor start up
    Serial.print("Initializing SD card...");

    // see if the card is present and can be initialized:
    if (!SD.begin(SDLoggerChipSelect)) {
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

    double vDivVal = 0;
    double tmp1Val = 1;
    double tmp2Val = 2;
    double pressVal = 3;
    double humidVal = 4;
    double accelxVal = 5;
    double accelyVal = 6;
    double accelzVal = 7;

    // Now let's make a nice string to write to the file.
    // This is a comma-separated value (csv) file, so we need to separate each value with a comma.
    String dataString = "";
    // add the time (since boot) in milliseconds
    dataString += String(millis());
    dataString += ",";
    // add the adjusted voltage divider value
    dataString += String(vDivVal);
    dataString += ",";
    // add the TMP36 value
    dataString += String(tmp1Val);
    dataString += ",";
    // add the BME680 value
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