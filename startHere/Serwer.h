#ifndef Serwer_h
#define Serwer_h

#include <ESP8266WiFi.h>
#include "PCSerial.h"
// ----------------------------------------------------------------------------------------------------------------------------
IPAddress ip(192,168,1,20);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
WiFiServer server(80);
  
class Serwer {
  
  const char* ssid = "FunBox-5CFD";
  const char* password = "12345678";
  
  String recievedMessageFromClient = "";

public:
  Serwer();
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
Serwer::Serwer() {
}
// ----------------------------------------------------------------------------------------------------------------------------
void Serwer::Init() {
  WiFi.mode(WIFI_STA);
  WiFi.config(ip,gateway,subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(10);
  }  
  server.begin();
  delay(50);
}
// ----------------------------------------------------------------------------------------------------------------------------
// prepare a web page to be send to a client (web browser)
String Serwer::prepareHtmlPage()
{
//  String htmlPage =
//     String("HTTP/1.1 200 OK\r\n") +
//            "Content-Type: text/html\r\n" +
//            "Connection: close\r\n" +  // the connection will be closed after completion of the response            
//            "\r\n" +
//            "<!DOCTYPE HTML> <html> <style> .hero { height: 100vh; background-image: url(\"https://mdbootstrap.com/img/Photos/Horizontal/Nature/full%20page/img(11).jpg\"); background-repeat: no-repeat; background-size: cover; } .body { background-color: #000; } .p { align-content: center; font-size: 200%; font-family: 'Montserrat', sans-serif; } .hero h1 { font-family: 'Montserrat', sans-serif; padding: 50px 0; margin: 0; padding-bottom: 30px; text-align: center; } .hero p { font-size: 20px; font-family: 'Montserrat', sans-serif; } button { padding-left: 100px; font-family: 'Montserrat', sans-serif; } #switch { padding-left: 10px; } .disconnect { padding: 100px 0; } .circle { height: 25px; width: 25px; border-radius: 50%; border: 1px solid rgb(151, 151, 151); } .table { font-size: 130%; } .circle-on { background-color: rgb(0, 210, 0); } </style> <head> <meta charset=\"utf-8\"> <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css\"> <link href=\"https://fonts.googleapis.com/css?family=Montserrat\" rel=\"stylesheet\"> <!-- jQuery library --> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script> <!-- Latest compiled JavaScript --> <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js\"></script> </head> <body> <div class=\"hero\"> <div style=\"background-color:rgba(0, 0, 0, 0.15);height: 100vh;\"> <h1>HOME AUTOMATION</h1> <br> <div class=\"container table-responsive-md\"> <table class=\"table table-hover\"> <thead> <tr> <th scope=\"col\">ESP</th> <th scope=\"col\">Turn on GPIO0</th> <th scope=\"col\">Turn off GPIO0</th> <th scope=\"col\">Turn on GPIO2</th> <th scope=\"col\">Turn off GPIO2</th> <th scope=\"col\">Available</th> </tr> </thead> <tbody> <tr> <th scope=\"row\">1</th> <td><a id=\"switch\" href=\"switch1On\"><button type=\"button\" class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button type=\"button\" class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button type=\"button\" class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button type=\"button\" class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">2</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">3</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">4</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">5</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">6</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">7</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">8</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> </tbody> </table> </div> <div class=\"text-centered\"> <a style=\"position:absolute;bottom:20px;left:50%;transform: translateX(-50%);\" id=\"switch\" href=\"switch1On\"><button class=\"btn btn-dark\">Reset Server</button></a> </div> </div> </div> </body> </html>";
  String htmlPage =
        String("HTTP/1.1 200 OK\r\n") +
               "Content-Type: text/html\r\n" +
               "\r\n" +
               "<!DOCTYPE HTML> <html> <style> .hero { height: 100vh; background-image: url(\"https://mdbootstrap.com/img/Photos/Horizontal/Nature/full%20page/img(11).jpg\"); background-repeat: no-repeat; background-size: cover; } .body { background-color: #000; } .p { align-content: center; font-size: 200%; font-family: 'Montserrat', sans-serif; } .hero h1 { font-family: 'Montserrat', sans-serif; padding: 50px 0; margin: 0; padding-bottom: 30px; text-align: center; } .hero p { font-size: 20px; font-family: 'Montserrat', sans-serif; } button { padding-left: 100px; font-family: 'Montserrat', sans-serif; } #switch { padding-left: 10px; } .disconnect { padding: 100px 0; } .circle { height: 25px; width: 25px; border-radius: 50%; border: 1px solid rgb(151, 151, 151); } .table { font-size: 130%; } .circle-on { background-color: rgb(0, 210, 0); } </style> <head> <meta charset=\"utf-8\"> <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css\"> <link href=\"https://fonts.googleapis.com/css?family=Montserrat\" rel=\"stylesheet\"> <!-- jQuery library --> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script> <!-- Latest compiled JavaScript --> <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js\"></script> </head> <body> <div class=\"hero\"> <div style=\"background-color:rgba(0, 0, 0, 0.15);height: 100vh;\"> <h1>HOME AUTOMATION</h1> <br> <div class=\"container table-responsive-md\"> <table class=\"table table-hover\"> <thead> <tr> <th scope=\"col\">ESP</th> <th scope=\"col\">Turn on GPIO0</th> <th scope=\"col\">Turn off GPIO0</th> <th scope=\"col\">Turn on GPIO2</th> <th scope=\"col\">Turn off GPIO2</th> <th scope=\"col\">Available</th> </tr> </thead> <tbody> <tr> <th scope=\"row\">1</th> <td><a id=\"switch\" href=\"ESP01GP01\"><button type=\"button\" class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"ESP01GP00\"><button type=\"button\" class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"ESP01GP21\"><button type=\"button\" class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"ESP01GP20\"><button type=\"button\" class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">2</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">3</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">4</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">5</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">6</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">7</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> <tr> <th scope=\"row\">8</th> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-success\">ON</button></a></td> <td><a id=\"switch\" href=\"switch1On\"><button class=\"btn btn-outline-danger\">OFF</button></a></td> <td><div class=\"circle circle\"></div></td> </tr> </tbody> </table> </div> <div class=\"text-centered\"> <a style=\"position:absolute;bottom:20px;left:50%;transform: translateX(-50%);\" id=\"switch\" href=\"switch1On\"><button class=\"btn btn-dark\">Reset Server</button></a> </div> </div> </div> </body> </html>";


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
        recievedMessageFromClient = client.readStringUntil('\r');
        //Serial.print(line);
// ----------------------------------------------------------------------------------------------------------------------------
        // serwer dostaje wiadomosc np ESP##
        int ESPNumber = recievedMessageFromClient.substring(3,5).toInt();  // odczytujemy ## z wiadomosci
        // jezeli server dostanie odpowiedz ze podlaczonego urzadzenia esp to wtedy wysle mu wiadomosc 
        if (recievedMessageFromClient.substring(0,3) == "ESP") {
            oled.setCursor(0,10);    
            oled.print("ESP connected");
            oled.display();
            String message = commandList[ESPNumber].pop();            
            client.println(message + "\r\n");                    
        }
// ----------------------------------------------------------------------------------------------------------------------------
        // ESP wysyła komende do serwera o jego statusie
        // SRV### - gdzie pierwsze 2 ## to nr. ESP a 3cia to jego status (0 lub 1)
        else if (recievedMessageFromClient.substring(0,3) == "SRV") {
          sendToPC.add(recievedMessageFromClient);
        }
// ----------------------------------------------------------------------------------------------------------------------------
        // oblsuga kompa
        // wait for end of client's request, that is marked with an empty line
        else if (recievedMessageFromClient.length() == 1 && recievedMessageFromClient[0] == '\n')
        {
          oled.setCursor(0,20);    
          oled.print("PC connected");
          oled.display();
          client.println(prepareHtmlPage());          
        }
        // ----------------------------------------------------------------------------------------------------------------------------
        // obsługa poleceń wydanych ze strony
        if(recievedMessageFromClient.indexOf("/ESP01GP20") != -1) {
          commandList[1].add("GP20");    
        }       
        else if(recievedMessageFromClient.indexOf("/ESP01GP21") != -1) {
          commandList[1].add("GP21");    
        }
// ----------------------------------------------------------------------------------------------------------------------------
      }
    }
    delay(100); // give the web browser time to receive the data
    client.flush();
    // close the connection:
    client.stop();
    return true;
    //Serial.println("[Client disonnected]");
  }
  else {
    client.stop();
    return false;
  }
}
// ----------------------------------------------------------------------------------------------------------------------------
#endif
