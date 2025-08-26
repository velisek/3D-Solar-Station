#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSerifBold18pt7b.h>

#include "img.h" // Pozadi
#include "cudl.h" // Cudl

#define DC    17  
#define RST   16  
#define BUSY  4 
#define POWER 2

// Inicializace displeje 2.13" černobílý (SSD1680 driver)
GxEPD2_BW<GxEPD2_213_B74, GxEPD2_213_B74::HEIGHT> display(GxEPD2_213_B74(SS, DC, RST, BUSY));

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);

  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, HIGH); // Zapnout napájení displeje
  Serial.println("Display power ON");
  delay(1000);

  display.init(115200, true, 2, false); // Inicializace displeje s reset pulsem 2ms

  if (display.pages() > 1) {
    delay(100);
    Serial.print("pages = ");
    Serial.print(display.pages());
    Serial.print(" page height = ");
    Serial.println(display.pageHeight());
    delay(1000);
  }


//----------------------------------------------------------------
//   PROGRAM   ---------------------------------------------------
  render();
  delay(10000);
  //display.fillScreen(GxEPD_WHITE);  // vymazat displej
  display.display(true); // Aktualizace displeje (bez plného refresh)
  delay(100);
  digitalWrite(POWER, LOW);  // Vypnout napájení displeje
  display.powerOff();
  Serial.println("setup done");
//   PROGRAM   ---------------------------------------------------
//----------------------------------------------------------------
}

void loop() {
  // Nic se zde nedělá
}



//----------------------------------------------------------------
void render() {

  int baterie_1 = 100; // příklad hodnoty
  int baterie_2 = 100; // příklad hodnoty
  int baterie_3 = 100; // příklad hodnoty
  int baterie_4 = 20; // příklad hodnoty
  int baterie_5 = 75; // příklad hodnoty
  int baterie_6 = 10; // příklad hodnoty

  double teplota = 26.9;
  int vlhkost = 37;

  
  display.setRotation(0);
  display.setFont(0); // Nejmenší defaultní font
  //display.setFont(&FreeMonoBold9pt7b);
  
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  //display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = 10;
  uint16_t y = 80;
  display.setFullWindow();
  display.firstPage();
  do {
    display.drawBitmap(0, 0, epd_bitmap_UX_128_250, 128, 250, GxEPD_BLACK); // Pozadí IMG





    // Baterie 1 ----------------------------------------------------
    // Procenta baterie ------------------------
    if (baterie_1 == 100) {
      display.setCursor(11, 77);
    } else {
      display.setCursor(15, 77);
    }
    display.print(baterie_1); 
    // Procenta baterie ------------------------
    
    if (baterie_1 > 75) {
      // Zobraz všechny 4 políčka baterie
      display.drawBitmap(5, 7, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);   // políčko baterie 4 (nejvyšší)
      display.drawBitmap(5, 21, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 3
      display.drawBitmap(5, 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 2
      display.drawBitmap(5, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 1 (nejnižší)
    } else if (baterie_1 > 50) {
      // Zobraz políčka 1, 2, 3
      display.drawBitmap(5, 21, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(5, 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(5, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_1 > 25) {
      // Zobraz políčka 1, 2
      display.drawBitmap(5, 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(5, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_1 > 0) {
      // Zobraz políčko 1 pouze
      display.drawBitmap(5, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
    }
    // Baterie 1 ----------------------------------------------------

    

    // Baterie 2 ----------------------------------------------------
    // Procenta baterie ------------------------
    if (baterie_2 == 100) {
      display.setCursor(51, 77);
    } else {
      display.setCursor(55, 77);
    }
    display.print(baterie_2); 
    // Procenta baterie ------------------------
    
    if (baterie_2 > 75) {
      // Zobraz všechny 4 políčka baterie
      display.drawBitmap(46, 7, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);   // políčko baterie 4 (nejvyšší)
      display.drawBitmap(46, 21, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 3
      display.drawBitmap(46, 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 2
      display.drawBitmap(46, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 1 (nejnižší)
    } else if (baterie_2 > 50) {
      // Zobraz políčka 1, 2, 3
      display.drawBitmap(46, 21, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(46, 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(46, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_2 > 25) {
      // Zobraz políčka 1, 2
      display.drawBitmap(46, 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(46, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_2 > 0) {
      // Zobraz políčko 1 pouze
      display.drawBitmap(46, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
    }
    // Baterie 2 ----------------------------------------------------
    

    // Baterie 3 ----------------------------------------------------
    // Procenta baterie ------------------------
    if (baterie_3 == 100) {
      display.setCursor(93, 77);
    } else {
      display.setCursor(97, 77);
    }
    display.print(baterie_3); 
    // Procenta baterie ------------------------
    
    if (baterie_3 > 75) {
      // Zobraz všechny 4 políčka baterie
      display.drawBitmap(87, 7, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);   // políčko baterie 4 (nejvyšší)
      display.drawBitmap(87, 21, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 3
      display.drawBitmap(87, 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 2
      display.drawBitmap(87, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 1 (nejnižší)
    } else if (baterie_3 > 50) {
      // Zobraz políčka 1, 2, 3
      display.drawBitmap(87, 21, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(87, 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(87, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_3 > 25) {
      // Zobraz políčka 1, 2
      display.drawBitmap(87, 35, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(87, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_3 > 0) {
      // Zobraz políčko 1 pouze
      display.drawBitmap(87, 49, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
    }
    // Baterie 3 ----------------------------------------------------



    // Baterie 4 ----------------------------------------------------
    // Procenta baterie ------------------------
    if (baterie_4 == 100) {
      display.setCursor(11, 115);
    } else {
      display.setCursor(15, 115);
    }
    display.print(baterie_4); 
    // Procenta baterie ------------------------
    
    if (baterie_4 > 75) {
      // Zobraz všechny 4 políčka baterie (odshora dolu)
      display.drawBitmap(5, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 4 (nejvyšší)
      display.drawBitmap(5, 164, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 3
      display.drawBitmap(5, 150, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 2
      display.drawBitmap(5, 136, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 1 (nejnižší)
    } else if (baterie_4 > 50) {
      // Zobraz políčka 1, 2, 3
      display.drawBitmap(5, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(5, 164, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(5, 150, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_4 > 25) {
      // Zobraz políčka 1, 2
      display.drawBitmap(5, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(5, 164, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_4 > 0) {
      // Zobraz políčko 1 pouze
      display.drawBitmap(5, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
    }
    // Baterie 4 ----------------------------------------------------

    
    // Baterie 5 ----------------------------------------------------
    // Procenta baterie ------------------------
    if (baterie_5 == 100) {
      display.setCursor(51, 115);
    } else {
      display.setCursor(55, 115);
    }
    display.print(baterie_5); 
    // Procenta baterie ------------------------
    
    if (baterie_5 > 75) {
      // Zobraz všechny 4 políčka baterie
      display.drawBitmap(46, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 4 (nejvyšší)
      display.drawBitmap(46, 164, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 3
      display.drawBitmap(46, 150, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 2
      display.drawBitmap(46, 136, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 1 (nejnižší)
    } else if (baterie_5 > 50) {
      // Zobraz políčka 1, 2, 3
      display.drawBitmap(46, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK); 
      display.drawBitmap(46, 164, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(46, 150, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);   
    } else if (baterie_5 > 25) {
      // Zobraz políčka 1, 2
      display.drawBitmap(46, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(46, 164, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_5 > 0) {
      // Zobraz políčko 1 pouze
      display.drawBitmap(46, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
    }
    // Baterie 5 ----------------------------------------------------

    // Baterie 6 ----------------------------------------------------
    // Procenta baterie ------------------------
    if (baterie_6 == 100) {
      display.setCursor(93, 115);
    } else {
      display.setCursor(97, 115);
    }
    display.print(baterie_6); 
    // Procenta baterie ------------------------
    
    if (baterie_6 > 75) {
      // Zobraz všechny 4 políčka baterie
      display.drawBitmap(87, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 4 (nejvyšší)
      display.drawBitmap(87, 164, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 3
      display.drawBitmap(87, 150, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 2
      display.drawBitmap(87, 136, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  // políčko baterie 1 (nejnižší)
    } else if (baterie_6 > 50) {
      // Zobraz políčka 1, 2, 3
      display.drawBitmap(87, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
      display.drawBitmap(87, 164, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(87, 150, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_6 > 25) {
      // Zobraz políčka 1, 2
      display.drawBitmap(87, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
      display.drawBitmap(87, 164, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);  
    } else if (baterie_6 > 0) {
      // Zobraz políčko 1 pouze
      display.drawBitmap(87, 178, epd_bitmap_cudl, 31, 14, GxEPD_BLACK);
    }
    // Baterie 6 ----------------------------------------------------




    // Teplota ----------------------------------------------------
    //display.setFont(&FreeMonoBold9pt7b); 
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(23, 225);
    display.print(teplota, 1); // počet desetiných míst
    display.write(176); // ASCII kód pro znak °
    display.print(" C");
    // Teplota ----------------------------------------------------

    // vlhkost ----------------------------------------------------
    //display.setFont(&FreeMonoBold9pt7b); 
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(50, 245);
    display.print(vlhkost, 1); // počet desetiných míst
    display.write(176); // ASCII kód pro znak °
    display.print(" %");
    // vlhkost ----------------------------------------------------


    
  } while (display.nextPage());
}
//----------------------------------------------------------------
