//Pin Setup 
const int MotionDetectPin = 7;
const int LightDetectPin = 2;
const int ButtonPin = 10;
const int LEDPin = 12;

boolean ButtonState;
boolean MotionDetected;
boolean LEDState;
boolean InputDetected = false;
int detect;

int DarknessLevel;
int InputTimeout = 0;
int MotionTimeout = 0;

void setup() 
{
  pinMode (LEDPin, OUTPUT);
  pinMode(MotionDetectPin, INPUT);
  pinMode(ButtonPin, INPUT_PULLUP);   
  Serial.begin(9600);
  Serial.print("System Online!\n"); 
} 

void loop() 
{
  DarknessLevel = analogRead(LightDetectPin);
  LEDState = digitalRead(LEDPin);
  ButtonState = digitalRead(ButtonPin);
  detect = digitalRead(MotionDetectPin);

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!MOTION DETECTED CLOCK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
  if (detect == 1)
  {
    MotionTimeout = 60;
  }
  if (MotionTimeout != 0)
  {
    MotionDetected = true;
    MotionTimeout = MotionTimeout - 1;

    if (InputTimeout == 0)
    {
      Serial.print(MotionTimeout);Serial.print(" - Motion Timeout\n");
    }
  }
  else
  {
    MotionDetected = false;
  }

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!IF NO HUMAN INPUT DETECTED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  if (InputDetected == false)
  {
    //IF DARKNESS LEVEL HIGH AND LIGHT IS OFF AND MOTION IS DETECTED TURN THE LIGHT ON
    if (DarknessLevel > 250 && LEDState == false && MotionDetected == true)
    {
      digitalWrite (LEDPin, HIGH);
      Serial.print("Low Light & Movement Detected, Turning the lights on!\n");
    }
    //IF DARKNESS LEVEL LOW AND LIGHT IS ON TURN THE LIGHT OFF
    else if (DarknessLevel < 175 && LEDState == true)
    {
      digitalWrite (LEDPin, LOW);
      Serial.print("Light Detected, Deactivating Lights!\n");
    }
    //IF NO MOTION DETECTED AND LIGHT IS ON, TURN THE LIGHT OFF
    else if (MotionDetected == false && LEDState == true)
    {
      digitalWrite (LEDPin, LOW);
      Serial.print("No People Detected, Deactivating Lights!\n");
    }  
  }
  
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!IF BUTTON IS PRESSED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  if (ButtonState == 0)
  {
    if (LEDState == true)
    {
      Serial.print("Button Pressed, Deactivating Lights!\n");
      digitalWrite (LEDPin, LOW);
      InputTimeout = 60;
      delay(100);
    }
    else if (LEDState == false)
    {
      Serial.print("Button Pressed, Activating Lights!\n");
      digitalWrite (LEDPin, HIGH);
      InputTimeout = 60;
      delay(100);
    }
  }
  
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!HUMAN INPUT CLOCK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  
  if (InputTimeout == 0)
  {
    InputDetected = false;
  }
  else if (InputTimeout > 0 && InputTimeout <= 3600)
  {
    InputDetected = true;
    Serial.print(InputTimeout);Serial.print(" - Input Timeout!\n");
    InputTimeout = InputTimeout - 1;
  }
  delay(100);
}
