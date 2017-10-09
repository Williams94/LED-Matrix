#include <Math.h>

class Coordinate {
  
  const float skipX = 12.8;
  const float skipY = 25.2632;

  float x, y, d;
  int convertedX, convertedY, convertedD;
  int ledX, ledY;
  int ledNumber;
  
  public::Coordinate(float x, float y, float d) {
    this.x = x;
    this.y = y;
    this.d = d;
  }

  public function runCoordinateConversion() : Coordinate {   
    this.convertCoordinate();
    this.calculateLedAddress();
    return new Coordinate(this.getLedX(), this.getLedY(), this.getConvertedD());
  }

  public function convertCoordinate() {
    this.setConvertedX(this.convertX(this.getX());
    this.setConvertedY(this.convertY(this.getY());
    this.setConvertedD(this.convertD(this.getD());   
  }

  public function calculateLedAddress() {
    int x = this.calculateLedX();
    
    if (this.getConvertedY() % 2 == 0) {
      this.ledY = ((this.getConvertedY() * 10) - x);
    } else {
      this.ledY = ((this.getConvertedY() * 10) + x);
    }
  }

  public function convertLedX() {
    if (this.getConvertedX >= 1 && this.getConvertedX <= 10) {
      return this.getConvertedX;
    } else if (this.getConvertedX >= 11 && this.getConvertedX <= 20) {
      return this.getConvertedX - 10;
    } else if (this.getConvertedX >= 21 && this.getConvertedX <= 30) {
      return this.getConvertedX - 20;
    } else if (this.getConvertedX >= 31 && this.getConvertedX <= 40) {
      return this.getConvertedX - 30;
    } else if (this.getConvertedX >= 41 && this.getConvertedX <= 50) {
      return this.getConvertedX - 40;
    }
  }
  
  public function convertX(float x) : int {    
    int convertedX = Math.round((x / this.skipX));
    return convertedX;
  }

  public function convertY(float y) : int {   
    int convertedY = Math.round((y / this.skipY));
    convertedY = 20 - convertedY;   
    return convertedY;
  }

  public function convertD(float d) : int {
    // Perform x coordinate conversion in here
    return this.convertedD;
  }

  public function getX() : float {
    return this.x;
  }

  public function setX(float x) {
    this.x = x;
  }

  public function getY() : float {
    return this.y;
  }

  public function setY(float y) {
    this.y = y;
  }

  public function getD() : float {
    return this.d;
  }

  public function setD(float d) {
    this.d = d;
  }

  public function getConvertedX() : int {
    return this.convertedX;
  }

  public function setConvertedX(int convertedX) {
    this.convertedX = convertedX;
  }

  public function getConvertedY() : int {
    return this.convertedY;
  }

  public function setConvertedY(int convertedY) {
    this.convertedY = convertedY;
  }

  public function getConvertedD() : int {
    return this.convertedD;
  }

  public function setConvertedD(int convertedD) {
    this.convertedD = convertedD;
  }

  public function getLedX() : int {
    return this.ledX;
  }

  public function setX(int ledX) {
    this.ledX = ledX;
  }

  public function getLedY() : int {
    return this.ledY;
  }

  public function setLedY(int ledX) {
    this.ledX = ledX;
  }
}

