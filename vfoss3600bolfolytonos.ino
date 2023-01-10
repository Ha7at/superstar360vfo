/*
   MC145106 vfo pll programozasa,
   Kristalyfrekvencia 14010kHz kf 10695kHz
   superstar3600 26605-29815kHz 
   oled kijelzö
  + varicap kijezés
  

*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const int  g0 = 12; // g0+ gomb
const int  g1 = 11; // g1- gomb
const int  numPins = 9;
byte pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
void setup() {
  for (int i = 0; i < numPins; i++)
    pinMode(pins[i], OUTPUT);
  pinMode(g0, INPUT);
  pinMode(g1, INPUT);



// Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
//  delay(200);
 // Clear the buffer.
  display.clearDisplay();
  }

int x =186;  //x= g0-g1 vfo szorzo

 int h= ((x* 10)+24705);

int g0State = 0;
int g1State = 0;    // gomb nyomas
int lastg0State = 0;
int lastg1State = 0;// elozo gomb nyomas

void loop() {
  // read the pushbutton input pin:
  g0State = digitalRead(g0);
  g1State = digitalRead(g1);
  

  // compare the g0State to its previous state
  if (g0State != lastg0State) {
    if (g0State == HIGH) {
      x++;
    }
    
     delay(250);
  }
  if (g1State != lastg1State) {

    if (g1State == HIGH) {
      x--;
      delay(250);

    }
    if (x< 186){ (x=512) ;}
     if (x>512){ (x=186) ;
    } 
    
  }
  
  
  lastg1State = g0State;

  {

    int num = x;  for  ( int i = 0; i < numPins; i++) {
      int state = bitRead(num, i);
      digitalWrite(pins[i], state);
      //Serial.print(state);
       // read the input on analog pin 2:
  int vcb = analogRead(A2); //varicap feszultseg
  // Konvert varikap feszultseg frekvcia vc :
//float  vc = vcb * (100 / 1023.0);
//delay (100);
int ht=0 ; // frekvecia korrekcio
if (vcb<= 28) ht=0;
if (vcb>= 51) ht=1;
if (vcb>= 80) ht=2;
if (vcb>= 118) ht=3;
if (vcb>= 156) ht=4;
if (vcb>= 201) ht=5;
if (vcb>= 250) ht=6;
if (vcb>= 301) ht=7;
if (vcb>= 363) ht=8;
if (vcb>= 425) ht=9;
if (vcb>= 495) ht=10;
if (vcb>= 570) ht=11;
if (vcb>= 650) ht=12;
//if (vcb>= 28) ht=13;

      long h= ((x* 10)+(24700+ht)); // frekvencia kijelzes. 

      
       display.setTextSize(3) ;
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
 // delay(10);
  display.println(h);
  display.setTextSize(3) ;
  display.print("  '");
  display.display();
  delay(10);
    }
  }


}
