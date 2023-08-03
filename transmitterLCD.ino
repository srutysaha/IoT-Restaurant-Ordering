#include <RH_ASK.h>

#include <SPI.h> // Not actually used but needed to compile

#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library

#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library

#include <SPFD5408_TouchScreen.h>

const char *msg ;

RH_ASK driver;

#define YP A1  // must be an analog pin, use "An" notation!

#define XM A2  // must be an analog pin, use "An" notation!

#define YM 7   // can be a digital pin

#define XP 6   // can be a digital pin

#define TS_MINX 125

#define TS_MINY 85

#define TS_MAXX 965

#define TS_MAXY 905

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3

#define LCD_CD A2

#define LCD_WR A1

#define LCD_RD A0

// optional

#define LCD_RESET A4

#define REDBAR_MINX 80

#define GREENBAR_MINX 130

#define BLUEBAR_MINX 180

#define BAR_MINY 30

#define BAR_HEIGHT 250

#define BAR_WIDTH 30

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BLACK   0x0000

int BLUE = tft.color565(50, 50, 255);

#define DARKBLUE 0x0010

#define VIOLET 0x8888

#define RED     0xF800

#define GREEN   0x07E0

#define CYAN    0x07FF

#define MAGENTA 0xF81F

#define YELLOW  0xFFE0

#define WHITE   0xFFFF

#define GREY   tft.color565(64, 64, 64);

#define GOLD 0xFEA0

#define BROWN 0xA145

#define SILVER 0xC618

#define LIME 0x07E0
//dish prices
#define dp1 50
#define dp2 60
#define dp3 70

void drawHome()

{

  tft.fillScreen(WHITE);

  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);     //Page border

  tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);

  tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);  //Dish1

  tft.fillRoundRect(30, 90, 100, 40, 8, GOLD);

  tft.drawRoundRect(30, 90, 100, 40, 8, WHITE);  //Dish2

  tft.fillRoundRect(30, 140, 100, 40, 8, GOLD);   //CANCLE

  tft.drawRoundRect(30, 140, 100, 40, 8, WHITE);

  tft.fillRoundRect(10, 190, 190, 40, 8, CYAN);

  tft.drawRoundRect(10, 190, 190, 40, 8, WHITE); //Confirm order

  tft.fillRoundRect(180, 40, 100, 40, 8, GOLD);

  tft.drawRoundRect(180, 40, 100, 40, 8, WHITE);  //CANCEL1

  tft.fillRoundRect(180, 90, 100, 40, 8, GOLD);

  tft.drawRoundRect(180, 90, 100, 40, 8, WHITE); //CANCEL2

  tft.fillRoundRect(180, 140, 100, 40, 8, GOLD);

  tft.drawRoundRect(180, 140, 100, 40, 8, WHITE); //CANCEL

  tft.fillRoundRect(210, 190, 100, 40, 8, GREEN);

  tft.drawRoundRect(210, 190, 100, 40, 8, WHITE); //Bill

  tft.setCursor(60, 0);

  tft.setTextSize(3);

  tft.setTextColor(LIME);

  tft.print("DIGITAL MENU");

  tft.setTextSize(2);

  tft.setTextColor(WHITE);

  tft.setCursor(37, 47);

  tft.print(" Dish1");

  tft.setCursor(37, 97);

  tft.print(" Dish2");

  tft.setCursor(37, 147);

  tft.print(" Dish3");

  tft.setCursor(23, 197);

  tft.print(" Confirm order");

  tft.setCursor(187, 47);

  tft.print(" CANCEL");

  tft.setCursor(187, 97);

  tft.print(" CANCEL");

  tft.setCursor(187, 147);

  tft.print(" CANCEL");

  tft.setCursor(227, 197);

  tft.print(" Bill");

    //delay(500);

}

int oldcolor, currentcolor, currentpcolour;

void setup(void) { 

  tft.reset();

  tft.begin(tft.readID());

  Serial.begin(9600);

  Serial.println();

  Serial.print("reading id...");

  delay(500);

  Serial.println(tft.readID(), HEX);  

  tft.fillScreen(BLACK);

  tft.setRotation(1);

  tft.setTextSize(3);

  tft.setTextColor(WHITE);

  tft.setCursor(50, 140);

  tft.print("PREPARING...");

  tft.setTextColor(tft.color565(255, 255, 0));

  
  tft.setCursor(30, 70);

  tft.print("By:");

  tft.setCursor(10, 100);
  
  tft.print("TEAM BUG SLAYERS");

  for (int i; i < 250; i++)

  {

    tft.fillRect(BAR_MINY - 10, BLUEBAR_MINX, i, 10, RED);

    delay(0.01);

  }

  tft.fillScreen(BLACK);
  if (!driver.init())

      Serial.println("init failed");

  drawHome();

  pinMode(13, OUTPUT);

}

#define MINPRESSURE 10

#define MAXPRESSURE 1000

void transmit()

{  

  driver.send((uint8_t *)msg, strlen(msg));

  driver.waitPacketSent();

  delay(1000);

  }
  void bill(int pn){
        Serial.println(pn);

  tft.fillScreen(DARKBLUE);
  tft.setCursor(20,20);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Total Bill:");
  tft.println(pn);

    delay(1500);
}
void confirm(){
  tft.fillScreen(DARKBLUE);
  tft.setCursor(20,20);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Order Confirmed");
  delay(1500);
  drawHome();
  

}
void loop()

{    int pr=0;

  digitalWrite(13, HIGH);

  TSPoint p = ts.getPoint();

  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins

  //pinMode(XP, OUTPUT);

  pinMode(XM, OUTPUT);

  pinMode(YP, OUTPUT);

  //pinMode(YM, OUTPUT);

  if (p.z > ts.pressureThreshhold)

    {

      p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);

      p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);      

      if (p.x > 30 && p.x < 130 && p.y > 40 && p.y < 80  && p.z > MINPRESSURE && p.z < MAXPRESSURE)

      {

        Serial.println("Dish1");

        msg = "Dish1 Ordered";
        pr=pr+dp1;
        Serial.println(pr);

        transmit();

        tft.fillRoundRect(30, 40, 100, 40, 8, WHITE);

        delay(70);

        tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);

        tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);

        tft.setCursor(37, 47);

        tft.println(" Dish1");

        delay(70);

        }

      if (p.x > 30 && p.x < 130 && p.y > 90 && p.y < 130  && p.z > MINPRESSURE && p.z < MAXPRESSURE)

      {

        Serial.println("Dish2");

        msg = "Dish2 Ordered";
        pr=pr+dp2;
Serial.println(pr);
        transmit();

        tft.fillRoundRect(30, 90, 100, 40, 8, WHITE);

        delay(70);

        tft.fillRoundRect(30, 90, 100, 40, 8, GOLD);

        tft.drawRoundRect(30, 90, 100, 40, 8, WHITE);

        tft.setCursor(37, 97);

        tft.println(" Dish2");

        delay(70);      

      }

      if (p.x > 30 && p.x < 130 && p.y > 140 && p.y < 180  && p.z > MINPRESSURE && p.z < MAXPRESSURE)

      {

        Serial.println("Dish3");

        msg = "Dish3 Ordered";
        pr=pr+dp3;
Serial.println(pr);


        transmit();

        tft.fillRoundRect(30, 140, 100, 40, 8, WHITE);   //rgb led

        delay(70);

        tft.fillRoundRect(30, 140, 100, 40, 8, GOLD);   //rgb led

        tft.drawRoundRect(30, 140, 100, 40, 8, WHITE);   //rgb led

        tft.setCursor(37, 147);

        tft.print(" Dish3");

        delay(70);       

      }

      if (p.x > 10 && p.x < 200 && p.y > 190 && p.y < 230  && p.z > MINPRESSURE && p.z < MAXPRESSURE)

      {

        Serial.println("Confirm order");

        msg = "Confirmed";

        transmit();

        tft.fillRoundRect(10, 190, 190, 40, 8, WHITE);

        delay(70);

        tft.fillRoundRect(10, 190, 190, 40, 8, CYAN);

        tft.drawRoundRect(10, 190, 190, 40, 8, WHITE);

        tft.setCursor(23, 197);

        tft.print(" Confirm order");

        delay(70);
        confirm();

      }

      if (p.x > 30 && p.x < 130 && p.y > 40 && p.y < 80  && p.z > MINPRESSURE && p.z < MAXPRESSURE)

      {

        Serial.println("CANCEL");
        if(pr>=dp1){
          pr=pr-dp1;
        }

        msg = "Dish1 CANCELED";

        transmit();

        tft.fillRoundRect(30, 40, 100, 40, 8, WHITE);

        delay(70);

        tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);

        tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);

        tft.setCursor(187, 47);

        tft.print(" CANCEL");

        delay(70);

      }

      if (p.x > 180 && p.x < 280 && p.y > 90 && p.y < 130  && p.z > MINPRESSURE && p.z < MAXPRESSURE )

      {

        Serial.println("CANCEL");
         if(pr>=dp2){
          pr=pr-dp2;
        }

        msg = "Dish2 CANCELED";

        transmit();

        tft.fillRoundRect(180, 90, 100, 40, 8, WHITE);

        delay(70);

        tft.fillRoundRect(180, 90, 100, 40, 8, GOLD);

        tft.drawRoundRect(180, 90, 100, 40, 8, WHITE);

        tft.setCursor(187, 97);

        tft.print(" CANCEL");

        delay(70);

      }

      if (p.x > 180 && p.x < 280 && p.y > 140 && p.y < 180  && p.z > MINPRESSURE && p.z < MAXPRESSURE)

      {

        Serial.println("CANCEL");
         if(pr>=dp3){
          pr=pr-dp3;
        }

        msg = "Dish3 Canceled";

        transmit();

        tft.fillRoundRect(180, 140, 100, 40, 8, WHITE);

        delay(70);

        tft.fillRoundRect(180, 140, 100, 40, 8, GOLD);

        tft.drawRoundRect(180, 140, 100, 40, 8, WHITE);

        tft.setCursor(187, 147);

        tft.print(" CANCEL");

        delay(70);

      }
Serial.println(pr+1);


      if (p.x > 210 && p.x < 310 && p.y > 190 && p.y < 230  && p.z > MINPRESSURE && p.z < MAXPRESSURE)

      {

        Serial.println("Bill");

        msg = "Send Bill";

        transmit();

        tft.fillRoundRect(210, 190, 100, 40, 8, WHITE);

        delay(70);

        tft.fillRoundRect(210, 190, 100, 40, 8, GREEN);

        tft.drawRoundRect(210, 190, 100, 40, 8, WHITE);

        tft.setCursor(227, 197);

        tft.print(" Bill");
        delay(70);
        bill(pr);
        Serial.println(pr);

      }

    }

}


 

