import processing.serial.*;
import ddf.minim.*;

// globals
float scale; // this is just a variable we can alter on the fly
Minim minim;
AudioInput in;
int pixelSize = 15;
PGraphics pg;
String serialOut;

Serial myPort;

void setup() {
  background(0);
  fullScreen();
  noCursor();
  pg = createGraphics(30, 19);
  minim = new Minim(this);
  minim.debugOn();
  in = minim.getLineIn(Minim.STEREO, 512);
  String portName = Serial.list()[1]; // change this to match the arduino, usually 1 - remove the [1] to see a full list
  println(portName);
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  scale = in.left.get(1) * 100;
  pg.beginDraw();
    pg.noStroke();
    pg.fill(32);
    pg.rect(0, 0, pg.width, pg.height);
    pg.fill(#ffffff);
    pg.ellipse(pg.width / 2, pg.height / 2, scale, scale);
    pg.loadPixels();
  pg.endDraw();
  for (int y = 0; y < pg.height; y++) {
    for (int x = 0; x < pg.width; x++) {
      int loc = x + y*pg.width;
      color clr = pg.pixels[loc];
      float red = floor(red(clr));
      float green = floor(green(clr));
      float blue = floor(blue(clr));
      fill(clr);
      rect((3*x +1)*pixelSize, (3*y +1)*pixelSize, pixelSize, pixelSize);
      serialOut = serialOut + (y - 19 + "," + x + "," + red + "," + green + "," + blue + ",");
    }
  }
  myPort.write(serialOut); // send this 2k monster down the serial pipe  
  myPort.write(30); //add a new line character
  //image(pg, 0 , 0); // uncomment this to see the debug image
}

void stop(){
  // always close Minim audio classes when you are done with them
  in.close();
  minim.stop();
  super.stop();
}
