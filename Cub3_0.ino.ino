#include <dht.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//CLASSE
dht DHT;
Adafruit_SSD1306 display(128, 32, &Wire, -1);


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Address 0x3D for 128x64
  pinMode(4, OUTPUT); //5v
  pinMode(5, OUTPUT); //GND 
  pinMode(12, OUTPUT); //GND
  pinMode(6, OUTPUT); //Trig
  pinMode(7, INPUT);  //Echo
  pinMode(11,OUTPUT); //5v
}


void SHOW(int size, int clear, int x, int y, String msg) {
  if (clear) {
    display.clearDisplay();
  }
  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  // Display static text
  display.println(msg);
  display.display();
}


void temperature() {

  // READ DATA
  int chk = DHT.read11(8);

  // DISPLAY DATA
  String h = "Humidity: " + String(DHT.humidity) + " %";
  SHOW(1, 1, 0, 10, h);
  //Serial.println(DHT.temperature);
  String t = "Temperature: " + String(DHT.temperature) + " C";
  SHOW(1, 0, 0, 25, t);
}


void distance() {

  digitalWrite(4, HIGH); //Enable 5v
  digitalWrite(5, LOW); //Enable GND

  digitalWrite(11,HIGH); /Enable 5v

  digitalWrite(6, LOW);

  delayMicroseconds(2);

  digitalWrite(6, HIGH);

  delayMicroseconds(10);

  digitalWrite(6, LOW);

  float t = pulseIn(7, HIGH);
  float d = t * 0.034 / 2;
  String distance = String(d) + "cm";

  SHOW(2, 1, 0, 15, String(distance));
}


void alarm(){
  SHOW(2,1,0,15,"ALARM!");
}


void loop() {
  //BUTTON
  int buttonStatus = analogRead(A5);

  static int buttonPressed = 0;

  digitalWrite(12, LOW); //Enable GND

  //isButton Pressed?
  if (buttonStatus == 0 && buttonPressed == 0) {
    buttonPressed = 1;
  }else if(buttonStatus == 0 && buttonPressed == 1){
    buttonPressed = 2;
  }else if(buttonStatus == 0 && buttonPressed == 2){
    buttonPressed = 0;  
  }

  if (buttonPressed == 0) {
    temperature();
  }
  if (buttonPressed == 1) {
    distance();
  }
  if (buttonPressed == 2){
    alarm();    
  }
  
  delay(500);

}