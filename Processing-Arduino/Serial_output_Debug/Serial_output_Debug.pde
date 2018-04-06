////testing to see what the serialOut payload is without the need for a serial device. 
//writes out the frames frames.txt in the sketch directory, by  using PrintWriter; all lines refereing to serial removed.  
//use framEnd to select the final serialOut you want sent to file. 

import ddf.minim.*;

// globals
float scale; // this is just a variable we can alter on the fly
Minim minim;
AudioInput in;
int pixelSize = 15;
PGraphics pg;
String serialOut;
PrintWriter output;
int i = 1 ; //int to hold the current framenumber.
int frameEnd = 1 ; //framenumber you want the output to stop at. 
void setup() {
  background(0);
  fullScreen();
  noCursor();
  pg = createGraphics(30, 19); // size of the led array 
  minim = new Minim(this);
  //minim.debugOn(); no microphone attached 
  in = minim.getLineIn(Minim.STEREO, 512);
  output = createWriter("frame.txt");
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
  output.println("frame" + i);
  for (int y = 0; y < pg.height; y++) {
    for (int x = 0; x < pg.width; x++) {
      int loc = x + y*pg.width;
      color clr = pg.pixels[loc];
      //float red = floor(red(clr));
      //float green = floor(green(clr));
      //float blue = floor(blue(clr));
      int red = floor(red(clr));
      int green = floor(green(clr));
      int blue = floor(blue(clr));
      fill(clr);
      rect((3*x +1)*pixelSize, (3*y +1)*pixelSize, pixelSize, pixelSize);
      serialOut = serialOut + (y - 19 + "," + x + "," + red + "," + green + "," + blue + ",");
    }
  }
  output.println(serialOut); //save to file 
  //image(pg, 0 , 0); // uncomment this to see the debug image
  println("frame" + i); //print to standard console
    i = i +1;
    if (i >= frameEnd+1) {  // When 'i' is less than 2..ie frame1  
    stop() ;  // stop 
  }
}

void stop(){
  //filewriter stop
  output.flush();  // Writes the remaining data to the file
  output.close();  // Finishes the file
  // always close Minim audio classes when you are done with them
  in.close();
  minim.stop();
  super.stop();
}