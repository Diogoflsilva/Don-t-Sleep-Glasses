// Libraries
#include "BluetoothSerial.h"

// Checking if bluetooth is on
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth
BluetoothSerial SerialBT;

// GPIO Components
const int ledPin1 = 22;
const int ledPin2 = 27;
const int Buzzer =  23;
const int IRSensor = 21;          

// Auxilary variables 
String message = "";
char incomingChar;
String IRSensorString = "";

      

void setup() {
  pinMode(Buzzer, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(IRSensor, INPUT);
  Serial.begin(115200);

  // Bluetooth device name
  SerialBT.begin("Don't Sleep Glasses");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  int statusSensor = digitalRead (IRSensor);

  if (statusSensor == 1) {
    digitalWrite(Buzzer, LOW);
  }

  if (statusSensor == 0) {
    digitalWrite(Buzzer, HIGH);
    SerialBT.println(statusSensor);
    delay(2500);
  }
  
  // Read received messages
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  // Check received message and control output accordingly
  if (message =="a"){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    message = "";
    
  }
  if (message =="b"){
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    message = "";
    
  }
  delay(20);
}
