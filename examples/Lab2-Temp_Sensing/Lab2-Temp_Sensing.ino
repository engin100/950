// These are the pins your MicroSD Card Adapter and BME680 will be connected to.
// These pins are specific and should not change. You do not need to worry
// about why these are the pins, just connect them as listed.
// MOSI - pin 11
// MISO - pin 12
// CLK  - pin 13

// You will pick which digital pin to connect to the chip select pin of the BME
const int BMEchipSelect = ??;

// Include necessary libraries for BME below:


// Instantiate BME here:


// The setup routine runs once when you press reset
void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  // Initialize the BME, oversampling, filter, and gas heater below:
  

}

// The loop routine runs over and over again forever
void loop() {
    // Placeholder temp value for BME680
    // REMINDER: We only care about temperature for this lab
    float bme_temperature = NAN;

    //Perform BME reading below:
    

    //Update the bme_temperature variable to the value that the BME just read down below:
    

    // Read the input on analog pin 1 or change the pin to the one you are using 
    // to read in the TMP36
    int sensorValue = analogRead(A1);

    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
    float voltage = sensorValue * (5.0 / 1023.0);


    // Don't worry about this until you get to
    // procedure Step 5: Modifying the Code
    // float slope = 100;
    // float intercept = -50;
    // float tempC = slope * voltage + intercept;


    // The dataString builds one line of text by combining two 
    // values (voltage and temperature) separated by a comma, 
    // so they can be printed together in a clean, readable format.
    String dataString;
    dataString += String(voltage); 
    dataString += ",";
    dataString += String(bme_temperature); // In Celsius

    // Print out the data string to the Serial monitor
    Serial.println(dataString);

    // Delay so that the numbers are slightly more readable
    delay(1000); // ms
}
