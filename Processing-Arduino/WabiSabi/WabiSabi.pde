// globals
float scale; // this is just a variable we can alter on the fly
int pixelSize = 15;
PGraphics pg;
PFont f;
  char[] dictionary;
  //dictionary["wabi sabi"] this will eventually have an array of words
  
  
void setup() {
  //background(0);
  fullScreen();
  noCursor();
  noSmooth(); //otherwise the font looks washed out
  pg = createGraphics(30, 19); // the size of the array of leds we had at the hack
  printArray(PFont.list());
  f = createFont("ClearSans",9);
  textFont(f);
  background(102);
  textAlign(CENTER);
}

void draw() {
  //scale = in.left.get(1) * 100;
  pg.beginDraw();
    pg.noStroke();
    pg.fill(0);
    pg.rect(0, 0, pg.width, pg.height);
    pg.fill(#ffffff);
    pg.textAlign(CENTER);
    pg.fill(255);
    pg.text("wabi", 15, 9);
    pg.text("sabi", 15, 19);
    pg.loadPixels();
  pg.endDraw();
  for (int y = 0; y < pg.height; y++) {
    for (int x = 0; x < pg.width; x++) {
      int loc = x + y*pg.width;
      color clr = pg.pixels[loc];
      fill(clr);
      rect((2*x +1)*pixelSize, (2*y +1)*pixelSize, pixelSize, pixelSize);// 2* multiplier for my screen rather than a retina display  
    }
  }
  delay(50);
}
}
