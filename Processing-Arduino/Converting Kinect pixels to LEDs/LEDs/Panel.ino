class Panel {

  int convertedX, panelNumber, panelX;

  public::Panel(int convertedX) {
    this.convertedX = convertedX;
    if (this.x >= 1 && this.x <= 10) {
      this.panelNumber = 1;
    } else if (this.x >= 1 && this.x <= 10) {
      this.panelNumber = 2;
    } else if (this.x >= 21 && this.x <= 30) {
      this.panelNumber = 3;
    } else if (this.x >= 31 && this.x <= 40) {
      this.panelNumber = 4;
    } else if (this.x >= 41 && this.x <= 50) {
      this.panelNumber = 5;
    }
  }

  public function getPanelNumber() : int {
    return this.panelNumber;
  }
}

