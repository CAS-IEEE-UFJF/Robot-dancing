#include <Servo.h>

#define SERVO 5 // Porta Digital 6 PWM

Servo servo; // Variável Servo
int pos; // Posição Servo

void setup ()
{
  servo.attach(SERVO);
  Serial.begin(115200);
  servo.write(0); // Inicia motor posição zero
}

void loop()
{
  for (pos = 0; pos < 180; pos++)
  {
    servo.write(pos);
    delay(15);
    Serial.println(pos);
  }

  delay(1000);
  for (pos = 180; pos >= 0; pos--)
  {
    servo.write(pos);
    delay(15);
    Serial.println(pos);
  }
}
