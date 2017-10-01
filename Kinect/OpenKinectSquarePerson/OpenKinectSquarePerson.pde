import org.openkinect.freenect.*;
import org.openkinect.processing.*;

// Kinect Library object
Kinect kinect;

float minThresh = 350;
float maxThresh = 850;

void setup() {
  // Rendering in P3D
  size(1000, 800, P3D);
  kinect = new Kinect(this);
  kinect.initDepth();
}

void draw() {

  background(0);

  PImage img = kinect.getDepthImage();
  int[] depth = kinect.getRawDepth();
  //image(img, 0, 0);

  int skip = 10;
  for (int x = 0; x < img.width; x += skip) {
    for (int y = 0; y < img.height; y += skip) {
      int index = x + y * img.width;
      int d = depth[index];
      float b = brightness(img.pixels[index]);
      float z = map(b, 0, 255, 255, -250);
      
      fill(255+b);
      pushMatrix();
      translate(x, y);
      //translate(x, y, z);
      if (d > minThresh && d < maxThresh) {
        println(img.pixels[index] + " " + b);
        rect(0, 0, skip/1.4, skip/1.4);
      }
      popMatrix();
    }
  }
}