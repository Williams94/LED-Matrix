import cc.arduino.*;
import org.firmata.*;

import org.openkinect.freenect.*;
import org.openkinect.processing.*;
import processing.serial.*;

Kinect kinect;
Serial serialConnection;
Arduino arduino;
int arduinoPort = 3;

float minThresh = 400;
float maxThresh = 900;
float threshRange = maxThresh - minThresh;
float skipX = 12.8;
float skipY = 25.2632;

void setup() {
  // Rendering in P3D
  size(512, 424, P3D);
  kinect = new Kinect(this);
  kinect.initDepth();
  kinect.setTilt(-35);
  
  printArray(Serial.list());
  
  String portName = Serial.list()[arduinoPort];
  serialConnection = new Serial(this, portName, 9600);
}

void draw() {

  background(0);

  PImage img = kinect.getDepthImage();
  int[] depth = kinect.getRawDepth();
  image(img, 0, 0);
  
  float sumX = 0;
  float sumY = 0;
  float sumZ = 0;
  float totalPixels = 0;
  
  float recordY = 0;
  float recordX = 0;
  float recordD = 0;
  
  for (int x = 0; x < img.width; x += skipX) {
    for (int y = 0; y < img.height; y += skipY) {
      int index = x + y * img.width;
      int d = depth[index];
      float b = brightness(img.pixels[index]);
      float z = map(b, 0, 255, 255, -250);
      
      if (d > minThresh && d < maxThresh) {
        String data = "x" + x + ",y" + y + ",d" + d;
        System.out.println(data);
        serialConnection.write(data);
        delay(200);
        //if (serialConnection.readString() != null) {
        if (serialConnection.available() > 0) {
          System.out.println(serialConnection.readString());
        }           
        //}
        //colorMode(RGB, threshRange + 30, 255, threshRange + 10);
        //fill(maxThresh - d, 20, d - minThresh);
        //pushMatrix();
        //translate(x, y);
        //rect(0, 0, skipX/1.4, skipY/1.4);
        //popMatrix();
      }
    }
  }
  
  float avgX = sumX / totalPixels;
  float avgY = sumY / totalPixels;
  float avgZ = sumZ / totalPixels;
}