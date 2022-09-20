#include <Servo.h>
Servo myservo;
int pos = 0;
int sen1 = 2;
int sen2 = 3;
unsigned long time1 = 0;
unsigned long time2 = 0;
float Speed;
int l1 = 6;
int l2 = 7;

void setup() 
{
  pinMode(sen1, INPUT);
  pinMode(sen2, INPUT);
  pinMode(l1, INPUT);
  pinMode(l2, INPUT);
  myservo.attach(5);
  Serial.begin(9600);  // initialize the serial port
}

void loop() 
{
  while (digitalRead(sen1));
  while (digitalRead(sen1) == 0);
  time1 = millis();
  while (digitalRead(sen2));
  time2 = millis();
  Speed = time2 - time1;
  Speed = Speed / 1000; //convert millisecond to second
  Speed = (18.0 / Speed); //speed=distance/time
  if (Speed > 10) 
  {
    digitalWrite(l1, HIGH); //Red led's on
    digitalWrite(l2, LOW); //Green led's off
    Serial.println("\nSpeed Measurement \n");
    Serial.println("Overspeed detected");
    Serial.print(Speed); //Calculated speed is displayed
    Serial.println(" cm/sec   ");
    Serial.println("Speed Breaker Raised"); //motor will rotate clockwise
    for (pos = 0; pos <= 190; pos += 1) 
    {
      myservo.write(pos);
      delay(10);
    }
    delay(4000);//delay of 4 ms to depress motor
    Serial.println("Speed Breaker Depressed"); //motor will rotate anti-clockwise
    for (pos = 190; pos >= 0; pos -= 1) 
    {
      myservo.write(pos);
      delay(10);
    }      
  }
  else if (Speed < 10 && Speed != 0) 
  {
    Serial.println("\nSpeed Measurement \n");
    Serial.println("Moderate Speed");
    Serial.print(Speed); //Calculated speed is displayed
    Serial.println(" cm/sec   ");
  }
  digitalWrite(l2, HIGH);// Green led's on
  digitalWrite(l1, LOW);//Red led's off
}
