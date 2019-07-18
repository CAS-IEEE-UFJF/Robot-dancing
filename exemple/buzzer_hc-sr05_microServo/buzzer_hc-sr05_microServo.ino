#include <Ultrasonic.h>

#define TRIGGER_PIN  4
#define ECHO_PIN     0

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
#include <Servo.h>

#define SERVO 5 // Porta Digital 6 PWM

Servo s; // Variável Servo
int pos; // Posição Servo

void setup ()
{
  s.attach(SERVO);
  Serial.begin(115200);
  s.write(0); // Inicia motor posição zero
}
void loop()
  {
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  Serial.print("MS: ");
  Serial.print(microsec);
  Serial.print(", CM: ");
  Serial.print(cmMsec);
  Serial.print(", IN: ");
  Serial.println(inMsec);
  if(cmMsec<30){
     for (pos = 0; pos < 180; pos++)
  {
    s.write(pos);
    delay(15);
    Serial.println(pos);
  }
  tone(2,440);//digitalWrite(2,HIGH);
  delay(1000);
  noTone(2);//digitalWrite(2,LOW);
  for (pos = 180; pos >= 0; pos--)
  {
    s.write(pos);
    delay(15);
    Serial.println(pos);
  }
  }
  }
  
  