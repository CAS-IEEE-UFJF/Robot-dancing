#include <Servo.h>
 #include <Arduino.h>
  #include <ESP8266WiFi.h>

  const char* ssid = "BRD";
  const char* password = "12345678";

  WiFiServer server(80);
  String header;

bool ligar = true;

Servo legE, legD, footE, footD;

int pos = 0;

void setup() {
  legE.attach(16);
  legD.attach(2);//5
  footE.attach(04);
  footD.attach(0);//0

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

String all_html ()
{
  String _html = "";
  //_html += "HTTP/1.1 200 OK";
  //_html += "Content-type:text/html";
  //_html += "Connection: close";
  // Display the HTML web page

  _html += "<!DOCTYPE html><html>";
  _html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  _html += "<link rel=\"icon\" href=\"data:,\">";

  _html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  _html += ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;";
  _html += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  _html += ".button2 {background-color: #77878A;}</style></head>";

  // Web Page Heading
  _html += "<body><h1>ESP8266 Web Server</h1>";

  _html += "<p><a href=\"/button1\"><button class=\"button\">ligar</button></a></p>";
  _html += "<p><a href=\"/button2\"><button class=\"button\">Desligar</button></a></p>";

  _html += "</body></html>";

  return _html;
}

void loop() {
  wifi();

  if(ligar){
  pos_natural();
  delay(1000);
  levantar_pe();
  delay(1000);
  rodar_perna();
  delay(1000);
  }
  //teste_servo();
  //legE_test();
  //legD_test();
  //footE_test();
  //footD_test();

  //leitura_serial();
}

void leitura_serial()
{
  if(Serial.available() > 0)
  {
    bool main = true;
    char s;
    s = Serial.read();

    if(s == 'p')
    {
      main = !main;
    }
  }
}

void legE_test ()
{
  for(int i = 50; i < 130; i++)
  {
    legE.write(i);
    delay(10);
    Serial.println(i);
  }

  delay(1000);
}

void footE_test ()
{
  for(int i = 50; i < 130; i++)
  {
    footE.write(i);
    delay(5);
    Serial.println(i);
  }

  delay(1000);
}

void teste_servo ()
{
  legE.write(160);                  // sets the servo position according to the scaled value
  delay(1500);
  legD.write(20);                  // sets the servo position according to the scaled value
  delay(800);
  legE.write(90);                  // sets the servo position according to the scaled value
  delay(1500);
  legD.write(90);                  // sets the servo position according to the scaled value
  delay(800);
  footE.write(20);                  // sets the servo position according to the scaled value
  delay(800);
  footD.write(160);                  // sets the servo position according to the scaled value
  delay(800);
  footE.write(90);                  // sets the servo position according to the scaled value
  delay(800);
  footD.write(90);                  // sets the servo position according to the scaled value
  delay(800);
}

void pos_natural()
{
  legE.write(0);                
  legD.write(90);                  
  footE.write(120);                  
  footD.write(90);  
}

void levantar_pe()
{
  for(int i = 50; i < 150; i++)
  {
     footD.write(i);
     delay(12);          
  }
 
  for(int i = 140; i > 50; i--)
  {
     footE.write(i);
     delay(12);          
  }


  //diminuir
 
  for(int i = 150; i < 90; i--)
  {
     footD.write(i);
     delay(6);          
  }

  for(int i = 50; i < 120; i++)
  {
     footE.write(i);
     delay(6);          
  }
}

void rodar_perna ()
{
  for(int i = 0; i < 30; i++)
  {
     legE.write(i);
     delay(12);          
  }
  for(int i = 90; i < 130; i++)
  {
     legD.write(i);
     delay(12);          
  }
 

  for(int i = 30; i > 0; i--)
  {
     legE.write(i);
     delay(6);          
  }
 
  for(int i = 130; i > 90; i--)
  {
     legD.write(i);
     delay(6);          
  }
}

void wifi()
{
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        header += c;

        if (c == '\n')
        {
          if (currentLine.length() == 0)
          {
            client.println(all_html()); //envia o html para o cliente

            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }
      }
    }

    if (header.indexOf("GET /button1") >= 0)
    {
      ligar = true;
    }

    if (header.indexOf("GET /button2") >= 0)
    {
      ligar = false;
      pos_natural();
    }

    header = "";
    client.stop();
  }
}
