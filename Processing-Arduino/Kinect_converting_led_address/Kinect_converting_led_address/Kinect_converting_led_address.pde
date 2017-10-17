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

int panelNumber;
int convertedX;
int convertedY;
int ledAddress;

int[][] testData = {{150,450}};

void setup() {
  // Rendering in P3D
  size(512, 424, P3D);
  //kinect = new Kinect(this);
  //kinect.initDepth();
  //kinect.setTilt(-35);
  
  printArray(Serial.list());
  
  String portName = Serial.list()[arduinoPort];
  serialConnection = new Serial(this, portName, 9600);
}

void draw() {

  /*background(0);

  PImage img = kinect.getDepthImage();
  int[] depth = kinect.getRawDepth();
  image(img, 0, 0);
  
  float sumX = 0;
  float sumY = 0;
  float sumZ = 0;
  float sumD = 0;
  float totalPixels = 0;
  
  //float recordY = 0;
  //float recordX = 0;
  //float recordD = 0;
  
  for (int x = 0; x < img.width; x += skipX) {
    for (int y = 0; y < img.height; y += skipY) {
      int index = x + y * img.width;
      int d = depth[index];
      //float b = brightness(img.pixels[index]);
      //float z = map(b, 0, 255, 255, -250);
      
      if (d > minThresh && d < maxThresh) {
        sumX += x;
        sumY += y;
        sumD += d;
        totalPixels++;
        
        //String data = "x" + x + ",y" + y + ",d" + d;
        //System.out.println(data);
        //serialConnection.write(data);
        //delay(200);        
        //if (serialConnection.available() > 0) {
        //  System.out.println(serialConnection.readString());
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
  float avgD = sumD / totalPixels; 
  int ledAddress = runCoordinateConversion(avgX, avgY);
 
  System.out.println("x" + avgX + ",y" + avgY + ",d" + avgD + ",l" + ledAddress);
  String data = "l" + ledAddress + "p" + panelNumber + "d" + avgD;
  serialConnection.write(data);
  //delay(200);        
  //if (serialConnection.available() > 0) {
  //  System.out.println(serialConnection.readString());
  //}
  */
  for (int x = 0; x < 200; x++) {
    int ledAddress = runCoordinateConversion(testData[0][0], testData[0][1]);
    int avgD = 300;
    String data = "l" + ledAddress + ",p" + panelNumber + ",d" + avgD;
    //System.out.println(data);
    serialConnection.write(data);
    delay(200);
    if (serialConnection.available() > 0) {
      //System.out.println(serialConnection.readString());
    }
  }        
}

int runCoordinateConversion(float x, float y) {   
  convertCoordinate(x, y);   
  setPanel();
  return calculateLedAddress();
}

int calculateLedAddress() {
  int ledX = convertLedX();
  int ledNumber = 0;
  
  if (convertedY % 2 == 0) {
    ledNumber = ((convertedY * 10) - ledX);
  } else {
    ledNumber = ((convertedY * 10) - (10 -  ledX));
  }
  
  return ledNumber;
}

int convertLedX() {
  int localLedX = 0;
  if (convertedX >= 1 && convertedX <= 10) {
    localLedX = convertedX;
  } else if (convertedX >= 11 && convertedX <= 20) {
    localLedX = convertedX - 10;
  } else if (convertedX >= 21 && convertedX <= 30) {
    localLedX = convertedX - 20;
  } else if (convertedX >= 31 && convertedX <= 40) {
    localLedX = convertedX - 30;
  } else if (convertedX >= 41 && convertedX <= 50) {
    localLedX = convertedX - 40;
  }
  return localLedX;
}

void setPanel() {
  if (convertedX >= 1 && convertedX <= 10) {
    panelNumber = 0;
  } else if (convertedX >= 11 && convertedX <= 10) {
    panelNumber = 1;
  } else if (convertedX >= 21 && convertedX <= 30) {
    panelNumber = 2;
  } else if (convertedX >= 31 && convertedX <= 40) {
    panelNumber = 3;
  } else if (convertedX >= 41 && convertedX <= 50) {
    panelNumber = 4;
  }
}

void convertCoordinate(float x, float y) {
  convertedX = convertX(x);
  setPanel();
  convertedY = convertY(y);  
}

int convertX(float x) {  
  return ceil((x / skipX));
}

int convertY(float y) {  
  return 20 - (ceil((y / skipY)));
}