import org.openkinect.freenect.*;
import org.openkinect.processing.*;

ParticleSystem ps;

// Kinect Library object
Kinect kinect;

float minThresh = 350;
float maxThresh = 800;
int skip = 15;

ArrayList<Coordinate> edges = new ArrayList<Coordinate>();
ArrayList<Coordinate> coordinates = new ArrayList<Coordinate>();

void setup() {
  // Rendering in P3D
  size(512, 424, P3D);
  kinect = new Kinect(this);
  kinect.initDepth();
  
  ps = new ParticleSystem(new PVector(width/2, 50));
}

void draw() {

  background(0);

  PImage img = kinect.getDepthImage();
  int[] depth = kinect.getRawDepth();
  //image(img, 0, 0);
  
  float sumX = 0;
  float sumY = 0;
  float sumZ = 0;
  float totalPixels = 0;
  
  float recordY = 0;
  float recordX = 0;
  float recordD = 0;
  
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
      //println(x, y, d);
      
      //recordY = recordY >= y ? y : recordY;
      
      if (d > minThresh && d < maxThresh) {      
        coordinates.add(new Coordinate(x, y, d, z));
        
        if (isEdge(coordinates)) {
        //  sumX += x;
        //  sumY += y;
        //  sumZ += z;
        //  totalPixels++;
          rect(0, 0, skip/1.4, skip/1.4);
        }
      }
      popMatrix();
    }
  }
  
  float avgX = sumX / totalPixels;
  float avgY = sumY / totalPixels;
  float avgZ = sumZ / totalPixels;
      
  //for (int i = 0; i < 2; i++) {
  //  ps.addTwoDParticle(avgX, avgY); 
  //  //ps.addThreeDParticle(avgX, avgY, avgZ); 
  //}
  //ps.run();
}

boolean isEdge(ArrayList coordinates) {
  for (int i = 0; i < coordinates.size(); i++) {
    Coordinate c = (Coordinate) coordinates.get(i);
    println(c.x);
          //if (i != 0 && i != coordinates.size()) {
          //  if (((coordinates.get(i - 1).getX() + skip) == edges.get(i).x) 
          //        || (coordinates.get(i + 1).x - skip == coordinates.get(i).x)) {
          //          // There is a sqaure to the left or right of the current square 
          //          // that is within the depth threshold
          //  }  
          //}
        }
  
  return true;
}