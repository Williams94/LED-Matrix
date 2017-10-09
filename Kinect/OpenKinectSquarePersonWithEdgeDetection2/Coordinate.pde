
class Coordinate {
  
  float x;
  float y;
  float d;
  float z;
  
  Coordinate(float x, float y, float d, float z) {
    this.x = x;
    this.y = y;
    this.d = d;
    this.z = z;
  }
  
   String toString() {
   return "x: " + this.x + " y: " + this.y + " d: " + this.d + " z: " + this.z;
  }
  
  public float getX() {
    return this.x;
  }
  
  float getY() {
    return this.y;
  }
  
  float getD() {
    return this.d;
  }
  
  float getZ() {
    return this.z;
  }
  
}