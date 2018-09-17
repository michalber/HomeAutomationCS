#include <ESP8266WiFi.h>

const char* ssid = "FunBox-5CFD";
const char* password = "12345678";

IPAddress server(192,168,1,11);     // fix IP of the server
WiFiClient client;
const char* host = "192,168,1,11";
String line;
String ID = "ESP01";

void setup()
{
  Serial.begin(9600);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  digitalWrite(1,1);
  digitalWrite(2,1);
  delay(100);
}

// ----------------------------------------------------------------------------------------------------------------------------

// funkcja do oblusgi odbieranych wiadomosci
void processRecievedMessage(String message) {
  //ESP##GP##
  if(message.substring(0,2) == "GP"){
    int GPIONumber =  String(message[2]).toInt();
    bool GPIOState = String(message[3]).toInt();

    digitalWrite(GPIONumber,GPIOState);   
  }
}
// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
void loop()
{
  //Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(server, 80))
  {
    //Serial.println("connected]");

    //Serial.println("[Sending a request]");
    client.println(ID);

    //Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {
        line = client.readStringUntil('\r');
        //Serial.println(line);
        processRecievedMessage(line);
        // uruchomienie leda po odebraniu odpowiedzi od serwera
     
      client.stop();
      //Serial.println("\n[Disconnected]");
      }
    }
  }
  else
  {
    //Serial.println("connection failed!]");
    client.stop();

  
  delay(5000);
}
}
