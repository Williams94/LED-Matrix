import processing.serial.*;

Serial myPort;  // Create object from Serial class

void setup() {
  size(200,200); //make our canvas 200 x 200 pixels big
  String portName = Serial.list()[3]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  if (mousePressed == true) {
    myPort.write('1');
    println("1");   
  } else {
    myPort.write('0');
  }   
}