#include <math.h>

class Coordinate {
  
  const float skipX = 12.8;
  const float skipY = 25.2632;

  float x, y, d;
  int convertedX, convertedY, convertedD;
  int ledX, ledY;
  int ledNumber;
  
  Coordinate::Coordinate(float x, float y, float d) {
    this->x = x;
    this->y = y;
    this->d = d;
  }

  runCoordinateConversion() {   
    this->convertCoordinate();
    this->calculateLedAddress();
  }

  void convertCoordinate() {
    this->setConvertedX(this->convertX(this->getX()));
    this->setConvertedY(this->convertY(this->getY()));
    this->setConvertedD(this->convertD(this->getD()));   
  }

  void calculateLedAddress() {
    int x = this->convertLedX();
    
    if (this->getConvertedY() % 2 == 0) {
      this->ledY = ((this->getConvertedY() * 10) - x);
    } else {
      this->ledY = ((this->getConvertedY() * 10) + x);
    }
  }

  int convertLedX() {
    if (this->getConvertedX() >= 1 && this->getConvertedX() <= 10) {
      return this->getConvertedX();
    } else if (this->getConvertedX() >= 11 && this->getConvertedX() <= 20) {
      return this->getConvertedX() - 10;
    } else if (this->getConvertedX() >= 21 && this->getConvertedX() <= 30) {
      return this->getConvertedX() - 20;
    } else if (this->getConvertedX() >= 31 && this->getConvertedX() <= 40) {
      return this->getConvertedX() - 30;
    } else if (this->getConvertedX() >= 41 && this->getConvertedX() <= 50) {
      return this->getConvertedX() - 40;
    }
  }
  
  int convertX(float x) {    
    int convertedX = ceil((x / this->skipX));
    return convertedX;
  }

  int convertY(float y) {   
    int convertedY = ceil((y / this->skipY));
    convertedY = 20 - convertedY;   
    return convertedY;
  }

  int convertD(float d) {
    // Perform x coordinate conversion in here
    return this->convertedD;
  }

  float getX() {
    return this->x;
  }

  void setX(float x) {
    this->x = x;
  }

  float getY() {
    return this->y;
  }

  void setY(float y) {
    this->y = y;
  }

  float getD() {
    return this->d;
  }

  void setD(float d) {
    this->d = d;
  }

  int getConvertedX() {
    return this->convertedX;
  }

  void setConvertedX(int convertedX) {
    this->convertedX = convertedX;
  }

  int getConvertedY() {
    return this->convertedY;
  }

  void setConvertedY(int convertedY) {
    this->convertedY = convertedY;
  }

  int getConvertedD() {
    return this->convertedD;
  }

  void setConvertedD(int convertedD) {
    this->convertedD = convertedD;
  }

  int getLedX() {
    return this->ledX;
  }

  void setX(int ledX) {
    this->ledX = ledX;
  }

  int getLedY() {
    return this->ledY;
  }

  void setLedY(int ledX) {
    this->ledX = ledX;
  }
};

