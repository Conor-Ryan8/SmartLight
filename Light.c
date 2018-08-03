//Pin Setup 
const int PhotoresistorPin = 2; //define analog pin 2
const int ButtonPin = 10;
const int LightPin = 13;
const int LightPin2 = 12;
const int LightPin3 = 11;
const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 8;
const int g = 9;

//Status of the Button
boolean ButtonState = true;

//Status of the Light
boolean LightState = false;

//Status of Motion Detection
boolean HumansDetected = true;

//Measures level of darkness in the room
int DarknessLevel = 0;

//Used when human input is detected
double InputTimeout = 0;

int lastnotified;

void setup() 
{
  //Initialize Pins
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
  pinMode (LightPin, OUTPUT);
  pinMode (LightPin2, OUTPUT);
  pinMode (LightPin3, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);   
  Serial.begin(9600);
  Serial.print("System Online!\n"); 
} 

void loop() 
{
  //Initialize Variables
  DarknessLevel = analogRead(PhotoresistorPin);
  int BrightnessLevel = (500 - DarknessLevel)/50;
  displayDigit(BrightnessLevel);
  LightState = digitalRead(LightPin);
  ButtonState = digitalRead(ButtonPin);
  
  if (DarknessLevel > 250 && LightState == false && InputTimeout == 0 && HumansDetected == true)
  {
    TurnOnLight();
    Serial.print("Low Light Detected, Activating Lights!\n");
  }
  else if (DarknessLevel < 150 && LightState == true && InputTimeout == 0)
  {
    TurnOffLight();
    Serial.print("Light Detected, Deactivating Lights!\n");
  }
  else if (ButtonState == false && LightState == true)
  {
    Serial.print("Button Pressed, Deactivating Lights!\n");
    TurnOffLight();
    Serial.print("Human input detected, Sleeping for 60min\n");
    InputTimeout = 3599.9;
    delay(100); 
  }
  else if (ButtonState == false && LightState == false)
  {
    Serial.print("Button Pressed, Activating Lights!\n");
    TurnOnLight();
    Serial.print("Human input detected, Sleeping for 60min\n");
    InputTimeout = 3599.9;

    delay(100);
  }
  if (InputTimeout == 0)
  {
    //No Human Input Detected
  }
  else if (InputTimeout > 0 && InputTimeout < 3600)
  {
    InputTimeout = InputTimeout - 0.1;
    
   if (lastnotified != int(InputTimeout))
   { 
   Serial.print(int(InputTimeout)/60);Serial.print(" Minutes and ");Serial.print(int(InputTimeout)%60);Serial.print(" Seconds until Auto Control\n");
   lastnotified = int(InputTimeout);
   }
  }
  else if (InputTimeout == 3600)
  {
    InputTimeout = 0;
    Serial.print("The Arduino is now taking back control xD\n");
  }
  delay(100);
}

void TurnOnLight()
{
  digitalWrite (LightPin, HIGH);
  digitalWrite (LightPin2, HIGH);
  digitalWrite (LightPin3, HIGH);
  LightState = true;
}

void TurnOffLight()
{
  digitalWrite (LightPin, LOW);
  digitalWrite (LightPin2, LOW);
  digitalWrite (LightPin3, LOW);
  LightState = false;
}

void displayDigit(int digit)
{
 //Conditions for displaying segment A
  if(digit!=1 && digit != 4)
  {
    digitalWrite(a,HIGH);
  }
  else
  {
    digitalWrite(a,LOW);
  }
  //Conditions for displaying segment B
  if(digit != 5 && digit != 6)
  {
    digitalWrite(b,HIGH);
  }
  else
  {
    digitalWrite(b,LOW);
  }
  //Conditions for displaying segment C
  if(digit !=2)
  {
    digitalWrite(c,HIGH);
  }
  else
  {
    digitalWrite(c,LOW);
  }
  //Conditions for displaying segment D
  if(digit != 1 && digit !=4 && digit !=7)
  {
    digitalWrite(d,HIGH);
  }
  else
  {
    digitalWrite(d,LOW);
  } 
  //Conditions for displaying segment E 
  if(digit == 2 || digit ==6 || digit == 8 || digit==0)
  {
    digitalWrite(e,HIGH);
  }
  else
  {
    digitalWrite(e,LOW);
  }
  //Conditions for displaying segment F
  if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
  {
    digitalWrite(f,HIGH);
  }
  else
  {
    digitalWrite(f,LOW);
  }
  //Conditions for displaying segment G
  if (digit!=0 && digit!=1 && digit !=7)
  {
    digitalWrite(g,HIGH);
  }
  else
  {
    digitalWrite(g,LOW);
  }
}
