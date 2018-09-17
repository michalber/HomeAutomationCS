//#include <LinkedList.h>
//#include <ESP8266WiFi.h>
//#include <Wire.h>                   // I2C->OLED
//#include <Adafruit_GFX.h>           // OLED
//#include <Adafruit_SSD1306.h>       // OLED
#include "PCSerial.h"
#include "Serwer.h"
// ----------------------------------------------------------------------------------------------------------------------------
//#define MAX_ESP_NUMB 20
//
//#define OLED_RESET 1
//Adafruit_SSD1306 oled(OLED_RESET);
// ----------------------------------------------------------------------------------------------------------------------------
//const char* ssid = "FunBox-5CFD";
//const char* password = "12345678";
// ----------------------------------------------------------------------------------------------------------------------------
//LinkedList<String> commandList[MAX_ESP_NUMB];
//IPAddress ip(192, 168, 4, 10);
//WiFiServer server(80);
//String recievedMessage="";
Serwer nodeMCUSerwer(10,10);
PCSerial PCCommunication(10,10);
// ----------------------------------------------------------------------------------------------------------------------------

void setup()
{
  nodeMCUSerwer.Init();
  PCCommunication.Init(nodeMCUSerwer.getIP());

//  Serial.begin(9600);
//  Serial.println();
//
//  Wire.begin();                               // default SDA and SCL
//  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);     // I2C address of my b&w OLED
//  oled.setTextColor(WHITE);
//  oled.setTextSize(1);
//  oled.clearDisplay();
//  oled.print("NodeMCU server");
//  oled.display();
  

  //Serial.printf("Connecting to %s ", ssid);
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    delay(500);
//    //Serial.print(".");
//  }
  //Serial.println(" connected");

//  server.begin();
//  oled.setCursor(0,15);
//  oled.println(WiFi.localIP().toString().c_str());
//  oled.display();
  //Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}
// ----------------------------------------------------------------------------------------------------------------------------

//// prepare a web page to be send to a client (web browser)
//String prepareHtmlPage()
//{
//  String htmlPage =
//     String("HTTP/1.1 200 OK\r\n") +
//            "Content-Type: text/html\r\n" +
//            "Connection: close\r\n" +  // the connection will be closed after completion of the response
//            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
//            "\r\n" +
//            "<!DOCTYPE HTML>" +
//            "<html>" +
//            "Analog input:  " + String(analogRead(A0)) +
//            "</html>" +
//            "\r\n";
//  return htmlPage;
//}
// ----------------------------------------------------------------------------------------------------------------------------

// funkcja do oblusgi odbieranych wiadomosci
//void processRecievedMessage(String message) {
//  //ESP##GP##
//  if(String(message[0]+message[1]+message[2]) == "ESP"){
//    int ESPNumber = String(message[3]+message[4]).toInt();    
//    commandList[ESPNumber].add(String(message[5]+message[6]+message[7]+message[8]));
//  }
//}
// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------

void loop()
{
  nodeMCUSerwer.UpdateSerwer();
  String IP = nodeMCUSerwer.getIP();
  PCCommunication.Update();
//  WiFiClient client = server.available();
//  // wait for a client (web browser) to connect
//  if (client)
//  {
//    //Serial.println("\n[Client connected]");
//    while (client.connected())
//    {
//      // read line by line what the client (web browser) is requesting
//      if (client.available())
//      {
//        String line = client.readStringUntil('\r');
//        //Serial.print(line);
//        // serwer dostaje wiadomosc np ESP##
//        int ESPNumber = String(line[3]+line[4]).toInt();  // odczytujemy ## z wiadomosci
//        // jezeli server dostanie odpowiedz ze podlaczonego urzadzenia esp to wtedy wysle mu wiadomosc 
//        if (String(line[0]+line[1]+line[2]) == "ESP") {
//            String message = commandList[ESPNumber].pop();            
//          client.println(message + "\r\n");
//          
//          break;
//        }
//        // oblsuga kompa
//        // wait for end of client's request, that is marked with an empty line
//        else if (line.length() == 1 && line[0] == '\n')
//        {
//          client.println(prepareHtmlPage());
//          break;
//        }
//      }
//    }
//    delay(100); // give the web browser time to receive the data
//
//    // close the connection:
//    client.stop();
//    //Serial.println("[Client disonnected]");
//  }
// // ------------------------------------
  

//  if(Serial.available() > 0) {
//  Serial.println("elo");
//  oled.clearDisplay();
//  oled.setTextColor(WHITE);
//  oled.setTextSize(2);
//  oled.setCursor(0,0);
//  recievedMessage = Serial.readString();
//  oled.print(recievedMessage);
//  oled.display();
//  processRecievedMessage(recievedMessage);
//  }
  }

