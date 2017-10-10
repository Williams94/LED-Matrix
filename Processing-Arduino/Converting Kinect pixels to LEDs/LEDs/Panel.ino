class Panel {

  int convertedX, panelNumber, panelconvertedX;

  Panel::Panel(int convertedX) {
    convertedX = convertedX;
    if (convertedX >= 1 && convertedX <= 10) {
      panelNumber = 1;
    } else if (convertedX >= 1 && convertedX <= 10) {
      panelNumber = 2;
    } else if (convertedX >= 21 && convertedX <= 30) {
      panelNumber = 3;
    } else if (convertedX >= 31 && convertedX <= 40) {
      panelNumber = 4;
    } else if (convertedX >= 41 && convertedX <= 50) {
      panelNumber = 5;
    }
  }

  int getPanelNumber() {
    return panelNumber;
  }
};

