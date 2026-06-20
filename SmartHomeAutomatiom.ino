#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <SoftwareSerial.h> 
#include <DHT.h> 
// ---------------- LCD Setup ---------------- 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
// ---------------- Bluetooth Setup ---------------- 
SoftwareSerial BT(10, 11); // RX, TX 
// ---------------- DHT11 Setup ---------------- 
#define DHTPIN 12 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 
// ---------------- Pin Define ---------------- 
#define LED1 6 
#define LED2 7 
#define RELAY1 4 
#define RELAY2 5 
#define PB1 2 
#define PB2 3 
// ---------------- State Variables ---------------- 
bool state1 = LOW; 
bool state2 = LOW; 
char Incoming_value = 0;  // Bluetooth simple commands 
// ---------------- Page Variables ---------------- 
unsigned long lastPageChange = 0; 
int currentPage = 0;  // 0 = Relay Status, 1 = Temp+Humidity 
void setup() { 
Serial.begin(9600);   
BT.begin(9600);       
dht.begin(); 
lcd.init(); 
lcd.backlight(); 
// PC Serial 
// Bluetooth Serial 
pinMode(LED1, OUTPUT); 
pinMode(LED2, OUTPUT); 
pinMode(RELAY1, OUTPUT); 
pinMode(RELAY2, OUTPUT); 
  pinMode(PB1, INPUT_PULLUP); 
  pinMode(PB2, INPUT_PULLUP); 
 
  // Start OFF 
  digitalWrite(LED1, LOW); 
  digitalWrite(LED2, LOW); 
  digitalWrite(RELAY1, HIGH);  // Active Low → HIGH = OFF 
  digitalWrite(RELAY2, HIGH); 
 
  // LCD Welcome 
  lcd.clear(); 
  lcd.setCursor(3, 0); 
  lcd.print("SMART HOME"); 
  lcd.setCursor(5, 1); 
  lcd.print("Group 2"); 
  delay(2000); 
 
  updateLCD(); 
  updateSerial(); 
} 
 
void loop() { 
  // ---------- Push Button ---------- 
  if (digitalRead(PB1) == LOW) { 
    delay(50); 
    while (digitalRead(PB1) == LOW); 
    state1 = !state1; 
    digitalWrite(LED1, state1); 
    digitalWrite(RELAY1, state1 ? LOW : HIGH); 
    updateLCD(); 
    updateSerial(); 
  } 
 
  if (digitalRead(PB2) == LOW) { 
    delay(50); 
    while (digitalRead(PB2) == LOW); 
    state2 = !state2; 
    digitalWrite(LED2, state2); 
    digitalWrite(RELAY2, state2 ? LOW : HIGH); 
    updateLCD(); 
    updateSerial(); 
  } 
 
  // ---------- Bluetooth App Control (1,2,3,4) ---------- 
  if (BT.available() > 0) { 
    Incoming_value = BT.read(); 
 
    if (Incoming_value == '1') state1 = true;      // Relay1 ON 
    else if (Incoming_value == '2') state1 = false; // Relay1 OFF 
    else if (Incoming_value == '3') state2 = true;  // Relay2 ON 
    else if (Incoming_value == '4') state2 = false; // Relay2 OFF 
 
    digitalWrite(LED1, state1); 
    digitalWrite(RELAY1, state1 ? LOW : HIGH); 
 
    digitalWrite(LED2, state2); 
    digitalWrite(RELAY2, state2 ? LOW : HIGH); 
 
    updateLCD(); 
    updateSerial(); 
  } 
 
  // ---------- Voice / Serial String Commands ---------- 
  if (Serial.available()) { 
    String command = Serial.readStringUntil('\n'); 
    command.trim(); 
    command.toLowerCase(); // ছ োট হোতের অক্ষতর রূপোন্তর 
 
    if (command == "light on") { 
      state1 = true; 
    } else if (command == "light off") { 
      state1 = false; 
    } else if (command == "fan on") { 
      state2 = true; 
    } else if (command == "fan off") { 
      state2 = false; 
    } 
 
    digitalWrite(LED1, state1); 
    digitalWrite(RELAY1, state1 ? LOW : HIGH); 
 
    digitalWrite(LED2, state2); 
    digitalWrite(RELAY2, state2 ? LOW : HIGH); 
 
    updateLCD(); 
    updateSerial(); 
  } 
 
  // ---------- LCD Page Loop ---------- 
  unsigned long now = millis(); 
  if (now - lastPageChange > 2000) {  // প্রতে 2 ছেতেতে ছপজ পতরবেতন 
    lcd.clear(); 
    if (currentPage == 0) { 
      showRelayStatus(); 
      currentPage = 1; 
    } else { 
      showDHTorExit(); 
      currentPage = 0; 
    } 
    lastPageChange = now; 
  } 
} 
 
void updateLCD() { 
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Relay1: "); 
  lcd.print(state1 ? "ON " : "OFF"); 
 
  lcd.setCursor(0, 1); 
  lcd.print("Relay2: "); 
  lcd.print(state2 ? "ON " : "OFF"); 
} 
 
void showRelayStatus() { 
  lcd.setCursor(0, 0); 
  lcd.print("Relay1: "); 
  lcd.print(state1 ? "ON " : "OFF"); 
  lcd.setCursor(0, 1); 
  lcd.print("Relay2: "); 
  lcd.print(state2 ? "ON " : "OFF"); 
} 
 
void showDHTorExit() { 
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
 
  if (isnan(h) || isnan(t)) { 
    lcd.setCursor(0, 0); 
    lcd.print("DHT Error!"); 
  } else { 
    // Temp & Humidity first 
    lcd.setCursor(0, 0); 
    lcd.print("Temp:"); 
    lcd.print(t); 
    lcd.print((char)223);  
    lcd.print("C   "); 
 
    lcd.setCursor(0, 1); 
    lcd.print("Humi:"); 
    lcd.print(h); 
    lcd.print("%   "); 
 
    // Warning if Light+Fan ON and Temp > 30°C 
    if (state1 && state2 && t > 30) { 
      delay(2000); // show temp/humi for 2 sec 
      lcd.clear(); 
      lcd.setCursor(0, 0); 
      lcd.print("WARNING!!!   "); 
      lcd.setCursor(0, 1); 
      lcd.print("EXIT ROOM    "); 
 
      Serial.println("ALERT: TEMP HIGH! EXIT ROOM"); 
      BT.println("ALERT: TEMP HIGH! EXIT ROOM"); 
      delay(2000); // show warning for 2 sec 
    } 
  } 
} 
 
void updateSerial() { 
  String msg = "Relay1 = "; 
  msg += (state1 ? "ON" : "OFF"); 
  msg += " | Relay2 = "; 
  msg += (state2 ? "ON" : "OFF"); 
 
  Serial.println(msg); 
  BT.println(msg); 
} 
 
 