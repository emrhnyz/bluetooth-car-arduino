
        // Arduino IDE
        // L293D Bluetooth controlled 2 motor car
        // 11 PWM value ena enb  1,9
        // ard -> l293d
        // 7 2 left front motor
        // 6 7 
        // 5 15 right front motor
        // 4 10
        // hc06 rx2 tx3
        #include 
        #include 
        #include "SPI.h"              // Adding the SPI library
        #include "Wire.h"             // Adding the Wire library
        #include "Adafruit_SSD1306.h" // Adding Adafruit's SSD1306 library
        
        int width = 128; // OLED screen width
        int height = 64; // OLED screen height
        int address = 0x3C;   // OLED screen I2C address
        
        Adafruit_SSD1306 screen(width, height, &Wire); 
        
        const unsigned char My_bitmap_Logomark_Black_RGB[] PROGMEM = {
        
        };
        
        LiquidCrystal_I2C lcd(0x27, 16, 2); 
        byte fullBlock[8] = {
          B11111,
          B11111,
          B11111,
          B11111,
          B11111,
          B11111,
          B11111,
          B11111
        };
        
        byte halfBlock[8] = {
          B11111,
          B11111,
          B11111,
          B11111,
          B00000,
          B00000,
          B00000,
          B00000
        };
        
        byte emptyBlock[8] = {
          B00000,
          B00000,
          B00000,
          B00000,
          B00000,
          B00000,
          B00000,
          B00000
        };
        
        byte heart1[8] = {B00000, B01010, B11111, B11111, B01110, B00100, B00000, B00000};
        byte heart2[8] = {B00000, B01010, B11111, B11111, B11111, B01110, B00100, B00000};
        int RX = 2;
        int TX = 3;
        String input = "S";
        int Speed = 0;
        SoftwareSerial bluetooth (RX,TX);
        
        void setup() {
          Serial.begin(9600);
          lcd.begin();
          lcd.clear();
          lcd.createChar(0, heart1);
          lcd.createChar(1, heart2);
          bluetooth.begin(9600);
          pinMode(7,OUTPUT);
          pinMode(6,OUTPUT);
          pinMode(5,OUTPUT);
          pinMode(4,OUTPUT);
          pinMode(11,OUTPUT);
          lcd.setCursor(2,0);
          lcd.print(" Emirhan "); // Adding text 
          lcd.setCursor(0,1);
          lcd.print("    Yıldız  "); // Adding text 
          lcd.setCursor(0,0);
          lcd.setCursor(0, 0);
          lcd.write(byte(1)); // Big heart
          lcd.setCursor(15, 0);
          lcd.write(byte(1));
          OLED();
        }
        
        void loop() {
          screen.display();
          if(bluetooth.available()){ input = String((char)bluetooth.read()); }
          if(Serial.available()){ input = String((char)Serial.read()); }   // When Bluetooth receives data, assign it to the input variable
          motorActions();
          if(input == "0") {Speed = 0;}
          else if(input == "1") {Speed = 100;}
          else if(input == "2") {Speed = 150;}
          else if(input == "3") {Speed = 200;}
          else if(input == "4") {Speed = 255;}
          analogWrite(11,Speed);
        
          // ANIMATIONS
        }
        
        void motorActions() {
          if(input == "F" )  // forward
          {
            digitalWrite(7,HIGH);
            digitalWrite(6,LOW);
            digitalWrite(5,HIGH);
            digitalWrite(4,LOW);
          }
          else if(input == "B") // backward
          {
            digitalWrite(7,LOW);
            digitalWrite(6,HIGH);
            digitalWrite(5,LOW);
            digitalWrite(4,HIGH);
          }
          else if(input == "L") // left
          {
            digitalWrite(7,LOW);
            digitalWrite(6,HIGH);
            digitalWrite(5,HIGH);
            digitalWrite(4,LOW);
          }
          else if(input == "R") // right
          {
            digitalWrite(7,HIGH);
            digitalWrite(6,LOW);
            digitalWrite(5,LOW);
            digitalWrite(4,HIGH);
          }
          else if (input ==  "S")    // stop motors
          {
            digitalWrite(7,HIGH);
            digitalWrite(6,HIGH);
            digitalWrite(5,HIGH);
            digitalWrite(4,HIGH);
          }
        }
        
        void animation () {
            lcd.setCursor(0,0);
          lcd.print(" ");
          lcd.setCursor(15,0);
          lcd.print(" ");
          lcd.setCursor(0, 0);
          lcd.write(byte(0)); // Small heart
          lcd.setCursor(15, 0);
          lcd.write(byte(0)); // Small heart
          delay(500);
          lcd.setCursor(0,0);
          lcd.print(" ");
          lcd.setCursor(15,0);
          lcd.print(" ");
          lcd.setCursor(0, 0);
          lcd.write(byte(1)); // Big heart
          lcd.setCursor(15, 0);
          lcd.write(byte(1)); // Big heart
          delay(500);
        }
        
        void OLED () {
            screen.invertDisplay(true);
          screen.begin(SSD1306_SWITCHCAPVCC, address);
           screen.clearDisplay(); // Clear screen
          screen.drawBitmap(
            0, 0,          // Bitmap starting point (x, y)
            My_bitmap_Logomark_Black_RGB,      // Bitmap name
            128,      // Bitmap width
            64,     // Bitmap height
            SSD1306_WHITE  // Drawing color (white)
          );
          screen.setTextSize(2); // Text size
          screen.setTextColor(SSD1306_BLACK); // Text color
          screen.setCursor(28, 0); // Starting point for text (X, Y)
          screen.println("");
        
          screen.display();
        }