#ifndef Serwer_h
#define Serwer_h

#include <ESP8266WiFi.h>
#include "PCSerial.h"
// ----------------------------------------------------------------------------------------------------------------------------
IPAddress ip(192,168,4,10);
WiFiServer server(80);
  
class Serwer {
  
  const char* ssid = "FunBox-5CFD";
  const char* password = "12345678";
  
  String recievedMessageFromESP = "";

  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time  
  unsigned long previousMillis;    // will store last time LED was updated

public:
  Serwer(long, long);
  void Init();
  bool UpdateSerwer();
  String getIP();

private:
  String prepareHtmlPage();
};
// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
String Serwer::getIP() {
  return WiFi.localIP().toString();
}
// ----------------------------------------------------------------------------------------------------------------------------
Serwer::Serwer(long on_time, long off_time) {
  OnTime = on_time;
  OffTime = off_time;
  previousMillis = 0;
}
// ----------------------------------------------------------------------------------------------------------------------------
void Serwer::Init() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  //Serial.println(" connected");
  server.begin();
}
// ----------------------------------------------------------------------------------------------------------------------------
// prepare a web page to be send to a client (web browser)
String Serwer::prepareHtmlPage()
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html> <style> .hero { height: 100vh; background-image: url(\"https://mdbootstrap.com/img/Photos/Horizontal/Nature/full page/img(11).jpg\"); background-repeat: no-repeat; background-size: cover; } .body { background-color: #000; } .p { align-content: center; font-size: 200%; font-family: 'Montserrat', sans-serif; } .hero h1 { font-family: 'Montserrat', sans-serif; padding: 50px 0; margin: 0; padding-bottom: 30px; text-align: center; } .hero p { font-size: 20px; font-family: 'Montserrat', sans-serif; } button { padding-left: 100px; font-family: 'Montserrat', sans-serif; } #switch { padding-left: 10px; } .disconnect { padding: 100px 0; } </style> <head> <meta charset=\"utf-8\"> <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\"> <link href=\"https://fonts.googleapis.com/css?family=Montserrat\" rel=\"stylesheet\"> <!-- jQuery library --> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script> <!-- Latest compiled JavaScript --> <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\"></script> </head> <body> <div class=\"hero\"> <h1>HOME AUTOMATION</h1> <br> <p align ='center'>Switch #1 <a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-success\">ON</button></a>&nbsp;<a id=\"switch\" href=\"switch1Off\"><button class=\"btn btn-danger\">OFF</button></a></p> <br> <p align ='center'>Switch #2 <a id=\"switch\" href=\"switch2On\"><button class=\"btn btn-success\">ON</button></a>&nbsp;<a id=\"switch\" href=\"switch2Off\"><button class=\"btn btn-danger\">OFF</button></a></p> <br> <p align ='center'>Switch #3 <a id=\"switch\" href=\"switch3On\"><button class=\"btn btn-success\">ON</button></a>&nbsp;<a id=\"switch\" href=\"switch3Off\"><button class=\"btn btn-danger\">OFF</button></a></p>"
            + "<div> <p class=\"disconnect\" align ='center'> <!-- Tu wpisz tekst -->";
            + "\r\n";
  return htmlPage;
}
// ----------------------------------------------------------------------------------------------------------------------------
bool Serwer::UpdateSerwer() {
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    //Serial.println("\n[Client connected]");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        recievedMessageFromESP = client.readStringUntil('\r');
        //Serial.print(line);
        // serwer dostaje wiadomosc np ESP##
        int ESPNumber = recievedMessageFromESP.substring(3,5).toInt();  // odczytujemy ## z wiadomosci
        // jezeli server dostanie odpowiedz ze podlaczonego urzadzenia esp to wtedy wysle mu wiadomosc 
        if (recievedMessageFromESP.substring(0,3) == "ESP") {
            oled.setCursor(0,20);    
            oled.print("ESP connected");
            oled.display();
            String message = commandList[ESPNumber].pop();            
            client.println(message + "\r\n");          
          return true;
        }
        // oblsuga kompa
        // wait for end of client's request, that is marked with an empty line
        else if (recievedMessageFromESP.length() == 1 && recievedMessageFromESP[0] == '\n')
        {
          oled.setCursor(0,20);    
            oled.print("PC connected");
            oled.display();
          client.println(prepareHtmlPage());
          return true;
        }
      }
    }
    delay(100); // give the web browser time to receive the data

    // close the connection:
    client.stop();
    //Serial.println("[Client disonnected]");
  }
  else {
    client.stop();
    return false;
  }
}
// ----------------------------------------------------------------------------------------------------------------------------
#endif

