#include "Watchy_Tower.h"

int UteZ = 0;
int UteM = 0;
int8_t batLev;

void WatchyTower::drawWatchFace(){
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    drawTime();
    drawBattery();
    
}
void WatchyTower::drawTime(){
  
    int8_t Stunde = currentTime.Hour ;
    int8_t Minute = currentTime.Minute;

    // reset step counter at midnight
    if (currentTime.Hour == 00 && currentTime.Minute == 00){
      sensor.resetStepCounter();
              //turn off radios
      WiFi.mode(WIFI_OFF);
      btStop();
    }
// time adjustment of 15,15 seconds each day (Watchy runs to fast)
    if (currentTime.Hour == 00 && currentTime.Minute == 30){
        
        RTC.read(currentTime);
        int8_t sekunde = currentTime.Second;
        int8_t minute = currentTime.Minute;
        int8_t hour = currentTime.Hour;
        int8_t day = currentTime.Day;
        int8_t month = currentTime.Month;
        int8_t year = tmYearToY2k(currentTime.Year);

        delay(15150);

        tmElements_t tm;
        tm.Month = month;
        tm.Day = day;
        tm.Year = y2kYearToTm(year);
        tm.Hour = hour;
        tm.Minute = minute ;
        tm.Second = sekunde;

        RTC.set(tm);     
         }
    // end of time adjustment, if you don't like a time adjustment, just delete above lines

    display.setFont(&FreeMonoBoldOblique22pt7b);
    display.setCursor(5,30);
    if (Stunde < 10) {
        display.print("0");
    }
    display.println(Stunde);
    display.setCursor(50, 30);
    display.print(":");
    
    if (Minute < 10) {
        display.print("0");
    }
    display.println(Minute);

    display.setFont(&FreeMonoBoldOblique15pt7b);

    String wTag = dayShortStr(currentTime.Wday);
    display.setCursor(5, 70);
    display.println(wTag);

    display.setCursor(5, 110);
        if (currentTime.Day < 10) {
        display.print("0");
    }
    display.println(currentTime.Day);
    display.setCursor(40, 110);
    display.print(".");
    display.println(monthShortStr(currentTime.Month));

    

    UteM = Minute / 10;
    Minute = Minute - (UteM * 10);

    display.drawBitmap(150, 0, rheinturm, 32, 200, GxEPD_BLACK);
    for (int n = 1; n < 10; n++) {
        if (n <= Minute) {
            display.fillCircle(165, 200 - (n * 4), 2, GxEPD_WHITE);
        }
        else display.drawCircle(165, 200 - (n * 4), 2, GxEPD_WHITE);
    }
    for (int n = 1; n < 6; n++) {
        if (n <= UteM) {
            display.fillCircle(165, 160 - (n * 4), 2, GxEPD_WHITE);
        }
        else display.drawCircle(165, 160 - (n * 4), 2, GxEPD_WHITE);
    }

    UteZ = Stunde / 10;
    Stunde = Stunde - (UteZ * 10);

    for (int n = 1; n < 10; n++) {
        if (n <= Stunde) {
            display.fillCircle(165, 135 - (n * 4), 2, GxEPD_WHITE);
        }
        else  display.drawCircle(165, 135 - (n * 4), 2, GxEPD_WHITE);
    }
    for (int n = 1; n < 3; n++) {
        if (n <= UteZ) {
            display.fillCircle(165, 95 - (n * 4), 2, GxEPD_WHITE);
        }
        else
        display.drawCircle(165, 95 - (n * 4), 2, GxEPD_WHITE);
    }
    

}
void WatchyTower::drawBattery() {

    float VBAT = getBatteryVoltage();

    if (VBAT > 4.15) {
        batLev = 100;
    }
    else batLev = 100 - ((4.15 - VBAT) * 100);

    display.drawBitmap(5, 130, akku, 30, 20, GxEPD_BLACK);
    display.setCursor(40, 150);
    display.println(batLev);
    if (batLev >= 100) {
        display.setCursor(100, 150);
    }
    else display.setCursor(80, 150);
    display.print("%");

        display.drawBitmap(5, 170, steps, 19, 23, GxEPD_BLACK);
        display.setCursor(30, 190);
        display.println(sensor.getCounter());
}


