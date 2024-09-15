#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
String UID = "72 D4 45 51";
byte lock = 0;
int redPin = 5;
int greenPin = 6;
int buzzerPin = 7;  // Buzzer pin
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);
int buttonPin = 2;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // 50 ms debounce delay

void setup() {
  Serial.begin(9600);
  servo.write(105);
  lcd.init();
  lcd.backlight();
  servo.attach(3);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
  pinMode(buttonPin, INPUT);  // Button input pin
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");

  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (!rfid.PICC_ReadCardSerial())
    return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();

  // Correct card: Lock/Unlock logic
  if (ID.substring(1) == UID && lock == 0) {
    // Lock the door
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    servo.write(2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is locked");
    delay(1500);
    lcd.clear();
    lock = 1;

  } else if (ID.substring(1) == UID && lock == 1) {
    // Unlock the door
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
    servo.write(105);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is open");
    delay(1500);
    lcd.clear();
    lock = 0;

  } else {
    // Wrong card: Blink red LED and buzz until button press
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong card!");
    delay(1500);
    lcd.clear();

    while (true) {
      // Blink the red LED
      digitalWrite(redPin, HIGH);
      digitalWrite(buzzerPin, HIGH);  // Turn buzzer on
      delay(500);
      digitalWrite(redPin, LOW);
      digitalWrite(buzzerPin, LOW);  // Turn buzzer off
      delay(500);
      
      // Check if button is pressed
      if (digitalRead(buttonPin) == LOW) {
        // Break the loop if button is pressed
        break;
      }
    }
  }
}
