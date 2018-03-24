import processing.video.*;
import processing.serial.*;

// globals
float scale;
int pixelSize = 15;
PGraphics buffer;
String serialOut;

Serial myPort;
Movie movie;

void setup() {
  background(0);
  fullScreen();
  noCursor();
  buffer = createGraphics(30, 19);
  buffer.beginDraw();
  buffer.background(0);
  buffer.endDraw();
  buffer.clear();
  movie = new Movie(this, "ipod.mp4");
  movie.loop();
  String portName = Serial.list()[1]; // change this to match the arduino, usually 1 - remove the [1] to see a full list
  println(portName);
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  PImage screen = get(0, 0, width, height); 
  buffer.beginDraw();
  buffer.image(movie, 0, 0, 30, 19);
  buffer.endDraw();
  buffer.loadPixels();
  for (int y = 0; y < buffer.height; y++) {
    for (int x = 0; x < buffer.width; x++) {
      int loc = x + y*buffer.width;
      color clr = buffer.pixels[loc];
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
}

void movieEvent(Movie m) {
  m.read();
}
