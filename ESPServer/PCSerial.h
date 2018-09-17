#ifndef PCSerial_h
#define PCSerial_h

#include <LinkedList.h>
#include <Wire.h>                   // I2C->OLED
#include <Adafruit_GFX.h>           // OLED
#include <Adafruit_SSD1306.h>       // OLED
// ----------------------------------------------------------------------------------------------------------------------------
#define MAX_ESP_NUMB  20
#define OLED_RESET  1
// ----------------------------------------------------------------------------------------------------------------------------
Adafruit_SSD1306 oled(OLED_RESET);
LinkedList<String> commandList[MAX_ESP_NUMB];

class PCSerial {
  
  private:        
    String recievedMessage="";
    String ServerIP;

    long OnTime;     // milliseconds of on-time
    long OffTime;    // milliseconds of off-time  
    unsigned long previousMillis;    // will store last time LED was updated

  public:
    PCSerial(long, long);
    void Init(String);
    void displayIP(String);
    void Update();
  private:
    void processRecievedMessage();
    
};

// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
PCSerial::PCSerial(long on_time, long off_time) {
  OnTime = on_time;
  OffTime = off_time;
  previousMillis = 0;
}
// ----------------------------------------------------------------------------------------------------------------------------
void PCSerial::Init(String IP) {
  Serial.begin(9600);
  Wire.begin();                               // default SDA and SCL
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);     // I2C address of my b&w OLED
  oled.setTextColor(WHITE);
  oled.setTextSize(1);
  oled.clearDisplay();
  oled.print("NodeMCU server");
  oled.setCursor(0,10);
  displayIP(IP);
  oled.display();
}
// ----------------------------------------------------------------------------------------------------------------------------
void PCSerial::processRecievedMessage() {
  //ESP##GP##   
  if(recievedMessage.substring(0,3) == "ESP"){
    int ESPNumber = recievedMessage.substring(3,5).toInt();    
    commandList[ESPNumber].add(recievedMessage.substring(5,9));       
  }  
}
// ----------------------------------------------------------------------------------------------------------------------------
void PCSerial::Update() {
   if(Serial.available() > 0) {    
    oled.clearDisplay();
    oled.setCursor(0,0);
    oled.print(ServerIP);
    oled.setCursor(0,10);
    recievedMessage = Serial.readString();
    oled.print(recievedMessage);
    oled.display();
    processRecievedMessage();
  }
}
void PCSerial::displayIP(String IP) {
  ServerIP = IP;
  oled.setCursor(0,10);
  oled.println(IP.c_str());
}
#endif
