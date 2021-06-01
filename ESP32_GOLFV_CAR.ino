/*
 *LABOR INFORMATIK SS2021
 *Projekt:  GOLF V MODELL REMOTE CONTROLLED
 *USING:  BLYNK APP
 *        ESP32
 *        L298n Motor Controller
 *        
 *by Hala1014        
 */
 
#include <WiFi.h>
#include <Blynk.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_PRINT Serial
#define BLYNK_DEBUG 
    
// Motor A            //Declaring the GPIOs for Motor Side A
int IN1 = 26; 
int IN2 = 25; 
int ENA = 14;

//Motor B             //Declaring the GPIOs for Motor Side B
int IN3 = 33; 
int IN4 = 32; 
int ENB = 27;

//Blynk Authentification & WIFI Connection
char auth[] = "Token";
char ssid[] = "Netzwerk Name";
char pass[] = "Passwort";

//Setting PWM properties
const int freq = 30000;
const int pwmChannelA = 0;
const int pwmChannelB = 1;
const int resolution = 8;
int dutyCycle = 225;
int dutyCycle_turn = 200;

//Variables for Blynk Motor Control
int x = 512;  //Forward & Backward
int y = 512;  //Steering Right & Left

//BLYNK_WRITE(V2) reads VirtualPin 1 in Blynk APP
//IF Clauses decide Motor Direction
BLYNK_WRITE(V2)
{
  int x = param.asInt();      //Param from Blynk is x
  if(x>514)
  {
    //MOVE FORWARD
    Serial.print(" FORWARD ");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(pwmChannelA, dutyCycle); 
    ledcWrite(pwmChannelB, dutyCycle);  
    Serial.print(" Forward with duty cycle ");
    Serial.println(dutyCycle);
  }else{
      if(x<510)
      {
      //MOVE BACKWARD
      Serial.print(" BACKWARD ");
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      ledcWrite(pwmChannelA, dutyCycle); 
      ledcWrite(pwmChannelB, dutyCycle);  
      Serial.print(" BACK with duty cycle ");
      Serial.println(dutyCycle);
      }else{
      //STOP
      Serial.print(" STOP ");
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW); 
      }
  }
}
 

//BLYNK_WRITE(V4) reads VirtualPin 4 in Blynk APP
//IF Clauses decide Motor Direction
BLYNK_WRITE(V3)                       
{
  int y = param.asInt();      //Param from Blynk is y 
  if(y<510)
  {
    //TURN LEFT
    Serial.print(" TURN LEFT ");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(pwmChannelA, dutyCycle_turn); 
    ledcWrite(pwmChannelB, dutyCycle_turn);  
    Serial.print(" LEFT with duty cycle ");
    Serial.println(dutyCycle_turn);
  }else{
    if(y>514)
      {
      //TURN RIGHT
      Serial.print(" TURN RIGHT ");
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      ledcWrite(pwmChannelA, dutyCycle_turn); 
      ledcWrite(pwmChannelB, dutyCycle_turn);  
      Serial.print(" RIGHT with duty cycle ");
      Serial.println(dutyCycle_turn );
      }else{
      //STOP
      Serial.print(" STOP ");
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      }
  }
}


void setup() 
{
  //Blynk Setup
  Blynk.begin(auth, ssid, pass);

  //Declaring pins as OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
   
  //configure PWM functionalitites
  ledcSetup(pwmChannelA, freq, resolution);
  ledcSetup(pwmChannelB, freq, resolution);
   
  //attach the channel to the GPIO to be controlled
  ledcAttachPin(ENA, pwmChannelA);
  ledcAttachPin(ENB, pwmChannelB);

  //Setting Baud Rate
  Serial.begin(115200);
 
  //CONSOLE CHECK
  Serial.print("Testing DC Motor...");
}

void loop() 
{
  Blynk.run();
}
