import ddf.minim.*;
import ddf.minim.analysis.*;
// globals
float scale; // this is just a variable we can alter on the fly
Minim minim;
AudioInput in;
int pixelSize = 15;
PGraphics pg;

void setup() {
  background(0);
  fullScreen();
  noCursor();
  pg = createGraphics(30, 19);
  minim = new Minim(this);
  minim.debugOn();
  in = minim.getLineIn(Minim.STEREO, 512);
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
      fill(clr);
      rect((3*x +1)*pixelSize, (3*y +1)*pixelSize, pixelSize, pixelSize);
    }
  }
  //image(pg, 0 , 0); // uncomment this to see the debug image
  delay(50);
}

void stop(){
  // always close Minim audio classes when you are done with them
  in.close();
  minim.stop();
  super.stop();
}
