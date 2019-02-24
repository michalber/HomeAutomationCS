#ifndef PCSerial_h
#define PCSerial_h

#include <LinkedList.h>
#include <Wire.h>                   // I2C->OLED
#include <Adafruit_GFX.h>           // OLED
#include <Adafruit_SSD1306.h>       // OLED
// ----------------------------------------------------------------------------------------------------------------------------
#define MAX_ESP_NUMB  99
#define OLED_RESET  1
// ----------------------------------------------------------------------------------------------------------------------------
Adafruit_SSD1306 oled(OLED_RESET);
LinkedList<String> commandList;
LinkedList<String> sendToPC;

class PCSerial {
  
  private:        
    String recievedMessage="";
    String ServerIP;

  public:
    PCSerial();
    void Init(String);
    void displayIP(String);
    void Update();
    void UpdateOLED();
    void WriteData();
  private:
    void processRecievedMessage();
    
};

// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
PCSerial::PCSerial() {
}
// ----------------------------------------------------------------------------------------------------------------------------
void PCSerial::Init(String IP) {    
  Wire.begin();                               // default SDA and SCL
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);     // I2C address of my b&w OLED
  oled.setTextColor(WHITE);
  oled.setTextSize(1);
  oled.clearDisplay();
  oled.print("NodeMCU server");
  oled.setCursor(0,10);
  displayIP(IP);
  oled.display();
  delay(100);
  Serial.begin(115200);
  Serial.println("<PC Communication is ready>");
  delay(50);
}
// ----------------------------------------------------------------------------------------------------------------------------
void PCSerial::processRecievedMessage() {
  //ESP##GP##   
  if(recievedMessage.substring(0,3) == "ESP"){   
    commandList.add(recievedMessage);       
  }  
}
// ----------------------------------------------------------------------------------------------------------------------------
void PCSerial::UpdateOLED() {
  
  
}
// ----------------------------------------------------------------------------------------------------------------------------
void PCSerial::Update() {  
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.print("Server IP: "+ ServerIP);
  oled.setCursor(0,10);
   
   while(Serial.available() > 0) {    
    recievedMessage = Serial.readString();         
    processRecievedMessage();  
    oled.setCursor(0,20);                
    oled.print(recievedMessage);
    oled.display();
  }     
}
// ----------------------------------------------------------------------------------------------------------------------------
void PCSerial::WriteData() {
  Serial.println(sendToPC.pop());
}
// ----------------------------------------------------------------------------------------------------------------------------
void PCSerial::displayIP(String IP) {
  ServerIP = IP;
  oled.setCursor(0,10);
  oled.println(IP.c_str());
}
// ----------------------------------------------------------------------------------------------------------------------------
#endif
