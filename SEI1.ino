#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Floor simulation
int floorNum = 1;
int direction = 1; // 1 = up, -1 = down

const int MIN_FLOOR = 1;
const int MAX_FLOOR = 10;

int lastFloor = -1;

void drawHeader() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Shabbat Elev.");
}

void drawFloor(int floor, int dir) {
  lcd.setCursor(0, 1);
  lcd.print("Floor:        ");

  lcd.setCursor(7, 1);
  lcd.print(floor);

  lcd.setCursor(11, 1);
  if (dir == 1) lcd.print("^");
  else lcd.print("v");
}

void setup() {
  Wire.begin(21, 22);
  delay(100);

  lcd.init();
  lcd.backlight();

  drawHeader();
}

void loop() {

  // Only update display if floor changed
  if (floorNum != lastFloor) {
    drawFloor(floorNum, direction);
    lastFloor = floorNum;
  }

  delay(1200); // simulate elevator speed

  // Move elevator
  floorNum += direction;

  if (floorNum >= MAX_FLOOR) {
    floorNum = MAX_FLOOR;
    direction = -1;
  }

  if (floorNum <= MIN_FLOOR) {
    floorNum = MIN_FLOOR;
    direction = 1;
  }
}