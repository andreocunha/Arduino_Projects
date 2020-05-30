#include "Servo.h" //biblioteca

#define SERVO 6 //porta digital 6

int pinoLdr = A5;
int valorLdr = 0;

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO);
  servo.write(0);
}

void loop() {
  valorLdr = analogRead(pinoLdr);
  Serial.println(valorLdr);
  if(valorLdr >= 47){
    servo.write(45);
  }
  else if(valorLdr <42){
    servo.write(60);
    delay(150);
  }

}
