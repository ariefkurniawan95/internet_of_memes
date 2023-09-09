#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

static const uint8_t PIN_MP3_TX = 13;
static const uint8_t PIN_MP3_RX = 12;

SoftwareSerial softwareSerial(PIN_MP3_RX,PIN_MP3_TX);
DFRobotDFPlayerMini player;

LiquidCrystal_I2C lcd(0x27, 16, 2);
int joyX, joyY;
int menuOption = 1;

void setup() {
  Serial.begin(9600);
  lcd.begin();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);            // Set the cursor to the top-left corner
  lcd.print("Pilih Univ:");         // Display the title
  lcd.setCursor(0, 1);            // Set the cursor to the second row
  lcd.print("1. UI");      // Display the first menu option

//  switch (menuOption) {
//     case 1:
//       player.volume(30);
//       player.play(0001);
//     case 2:
//       player.volume(30);
//       player.play(0002);
//     case 3:
//       player.volume(30);
//       player.play(0003);
//    }

      softwareSerial.begin(9600);
      player.begin(softwareSerial);
       player.volume(30);
       player.play(1);
}

void loop() {
  // Read joystick values
  joyX = analogRead(A0);
  joyY = analogRead(A1);

  // Check joystick position to navigate menu
  if (joyY < 100) {
    menuOption++;
    if (menuOption > 3) {
      menuOption = 1;
    }
    displayMenu();
    player.next();
    delay(200);
  }
  else if (joyY > 900) {
    menuOption--;
    if (menuOption < 1) {
      menuOption = 3;
    }
    displayMenu();
    player.next();
    delay(200);
  }

  // Check if joystick button is pressed to select menu option
  if (digitalRead(7) == LOW) { // Assuming the joystick button is connected to pin 2
    selectMenuOption();
    delay(200);
  }
}

void displayMenu() {
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear the previous menu option
  lcd.setCursor(0, 1);
  switch (menuOption) {
    case 1:
      lcd.print("1. UI");
      break;
    case 2:
      lcd.print("2. ITB");
      break;
    case 3:
      lcd.print("3. UGM");
      break;
  }
}

void selectMenuOption() {
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0);
  lcd.print("Pilih Univ : "); // Display the selected option
  lcd.setCursor(0, 1);
  if (menuOption==1){
    lcd.print("1. UI");
    }
  else if (menuOption==2){
    lcd.print("2. ITB");
    }
  else if(menuOption==3){
    lcd.print("3. UGM");
    }
  // Implement your code to perform the action for the selected option
  // For example, you can call a function or execute specific code here based on the selected option.
}
