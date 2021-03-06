#define _TINY_ 1
//#define _ARDUINO_ 1

#if defined(_TINY_)
  int SER_Pin = 5;   //pin 14 on the 75HC595
  int RCLK_Pin = 4;  //pin 12 on the 75HC595
  int SRCLK_Pin = 3; //pin 11 on the 75HC595
  int DISPLAY_LEDS = 9; //pin 9 on the 75HC595
  int LED2 = 10; //pin 1
  int LED1 = 1; //pin 10
  const int buttonPin = 2; 
  const int vibreur = 7; 
  const int delay_press = 2000;
  const int delay_vibrate_short = 1000;
  const int delay_vibrate_end = 4000;

#elif defined(_ARDUINO_)
  int SER_Pin = 7;   //pin 14 on the 75HC595
  int RCLK_Pin = 8;  //pin 12 on the 75HC595
  int SRCLK_Pin = 9; //pin 11 on the 75HC595
  int LED1 = 12; //pin 12
  int LED2 = 13; //pin 13
  const int buttonPin = 2; 
  const int vibreur = 6; 
  const int delay_press = 200;
  const int delay_vibrate_short = 100;
  const int delay_vibrate_end = 1000;
#endif

int buttonState = 0;
int state = 0;
//How many of the shift registers - change this
#define number_of_74hc595s 1 
 
//do not touch
#define numOfRegisterPins number_of_74hc595s * 8
 

boolean registers[numOfRegisterPins];
 
void setup(){
#if defined(_ARDUINO_)
  Serial.begin(9600);
#endif
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(DISPLAY_LEDS, OUTPUT);
  pinMode(vibreur, OUTPUT);
  pinMode(buttonPin, INPUT);
 
  //reset all register pins
  clearRegisters();
 // writeRegisters();

 
  digitalWrite(RCLK_Pin, LOW);
 setRegisterPin(0, LOW);
  setRegisterPin(1, LOW);
  setRegisterPin(2, LOW);
  setRegisterPin(3, LOW);
  setRegisterPin(4, LOW);
  setRegisterPin(5, LOW);
 setRegisterPin(6, LOW);
 setRegisterPin(7, LOW);
  digitalWrite(RCLK_Pin, HIGH);
  digitalWrite(RCLK_Pin, LOW);
  digitalWrite(DISPLAY_LEDS, HIGH);
}               
 
//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
  digitalWrite(RCLK_Pin, LOW);
     registers[i] = LOW;
  setRegisterPin(i, LOW);
  digitalWrite(RCLK_Pin, HIGH);
  digitalWrite(RCLK_Pin, LOW);
  }
} 
 
//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(int mode){
   digitalWrite(RCLK_Pin, LOW);
    digitalWrite(SRCLK_Pin, LOW);
    digitalWrite(SER_Pin, mode);
    digitalWrite(SRCLK_Pin, HIGH);
  digitalWrite(RCLK_Pin, HIGH);
 
}
 
//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
    digitalWrite(SRCLK_Pin, LOW);
    digitalWrite(SER_Pin, value);
    digitalWrite(SRCLK_Pin, HIGH);
}

void setActivePin(int value){
  digitalWrite(RCLK_Pin, LOW);
  digitalWrite(RCLK_Pin, HIGH);
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);
    if(i == value) {
      digitalWrite(SER_Pin, HIGH);
    }
    else digitalWrite(SER_Pin, LOW);
    digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK_Pin, LOW);
}
 
 
void loop(){
 
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
 
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {

#if defined(_ARDUINO_)
    Serial.print("Boutton !!!!");
#endif
    next();
  }
}

void next() {
    vibrate(delay_vibrate_short);
  switch(state) {
    case 8: 
      writeRegisters(0);
      digitalWrite(LED1, HIGH); 
      state++; 
      break;
    case 9: 
      digitalWrite(LED1, LOW); 
      digitalWrite(LED2, HIGH); 
        vibrate(delay_vibrate_end);
        state=0;
      break;
    case 0: 
      digitalWrite(LED1, LOW); 
      digitalWrite(LED2, LOW);
      writeRegisters(1);
      state++; 
    break;
    default:
      writeRegisters(0);
      state++;   
    }
  
    digitalWrite(RCLK_Pin, LOW);

      delay(delay_press);
}
void vibrate(int t) {
    digitalWrite(vibreur, HIGH);
    delay(t);
    digitalWrite(vibreur, LOW);
}


