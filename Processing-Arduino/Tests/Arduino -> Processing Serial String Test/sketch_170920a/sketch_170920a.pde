import processing.serial.*;

Serial arduinoPort;  // Create object from Serial class
String serialData;     // Data received from the serial port

void setup() {
  // I know that the first port in the serial list on my mac
  // is Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[3]; //change the 0 to a 1 or 2 etc. to match your port
  arduinoPort = new Serial(this, portName, 9600);
}

void draw() {
  if ( arduinoPort.available() > 0) {
    serialData = arduinoPort.readStringUntil('\n');
  } 
  println(serialData);
}