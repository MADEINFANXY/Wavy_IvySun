/*
  Project Title: Wavy (Arduino Code)
  Student Name & ID: Ivy Sun 3183268
  Course Code & Titlel: DIGF-2015-001 Atelier II: Collaboration
  Instructor: Dr. Adam Tindale
  OCAD University
  Modified by Ivy Sun in Apr. 2022
  Based on:
  Arduino Tutorials/References/Resources/Built-In Examples:

  Sample Code file "AnalogReadSerial" from Arduino Built-In Examples Library
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial

  Sample Code file "AnalogInOutSerial" by Tom Igoe from Arduino Built-In Examples Library
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInOutSerial

  Sample Code file "SerialCallResponseASCII" by Tom Igoe, Scott Fitzgerald and Greg Shakar from Arduino Built-In Examples Library
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialCallResponseASCII

  Sample Code file "Calibration" by David A Mellis, Tom Igoe and Zachary J. Fields from Arduino Built-In Examples Library
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Calibration

  https://www.arduino.cc/en/Reference/Map

  Online Resources:
  
  Lab: Intro to Asynchronous Serial Communications - ITP Physical Computing
  https://itp.nyu.edu/physcomp/lab-intro-to-serial-communications/
*/

/*
  Reads an analog input on pin 0, pin 1 and pin2 prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).

  The Circuit:
  Attach the center pin of 20k potentiometer to pin A0, and the outside pins to +5V and ground.
  Attach the center pin of 10k potentiometer to pin A1, and the outside pins to +5V and ground.
  Attach one pin of a photoresistor to pin A2, and the outside pins to +5V.
  Attach one pin of a resistor to pin A2, and the outside pins to ground.
*/

//int incoming; //variable for storing incoming data from p5.js

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int pot1Val = analogRead(A0); //big potentiometer pin
  // read the input on analog pin 1:
  int pot2Val = analogRead(A1); //small potentiometer pin
  // read the input on analog pin 2:
  int ldrVal = analogRead(A2); //photoresistor pin

  //SENDING SERIAL TO P5.JS
  //special formatting: strings separated by commas (ASCII)
  // print out the value you read:
  Serial.print(pot1Val);
  Serial.print(",");
  Serial.print(pot2Val);
  Serial.print(",");
  Serial.println(ldrVal);

  // delay in between reads for stability
  // wait 1 millisecond before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1); //slow data

  /*
  //RECEIVING SERIAL FROM P5.JS
  if (Serial.available() > 0) {
    incoming = Serial.read(); //store data
  }
  */
}
