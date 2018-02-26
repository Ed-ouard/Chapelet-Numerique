int SER_Pin = 5;   //pin 14 on the 75HC595
int RCLK_Pin = 4;  //pin 12 on the 75HC595
int SRCLK_Pin = 3; //pin 11 on the 75HC595
int LED1 = 10; //pin 12
int LED2 = 1; //pin 13
const int buttonPin = 2; 
const int vibreur = 7;

 
int buttonState = 0;
int state = 0;
//How many of the shift registers - change this
#define number_of_74hc595s 1 
 
//do not touch
#define numOfRegisterPins number_of_74hc595s * 8
 

boolean registers[numOfRegisterPins];
 
void setup(){
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
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
void writeRegisters(){
 
  digitalWrite(RCLK_Pin, LOW);
 
    digitalWrite(SRCLK_Pin, LOW);
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
 
    int val = registers[i];
    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);
 
  }
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
    next();
    //vibrate();
  } else {
    // turn LED off:
  }
 
 // writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
  //Only call once after the values are set how you need.
}

void next() {
  vibrate(1000);
  if(state==4) {
    //state++;
  }
  switch(state) {
    case 0: 
    setActivePin(-1);
    digitalWrite(LED1, HIGH); state++; break;
    case 1: digitalWrite(LED1, LOW); digitalWrite(LED2, HIGH); state++; break;
    case 2: digitalWrite(LED1, LOW); digitalWrite(LED2, LOW);
    setActivePin(state-2);
    state++; 
    break;
    default:
    setActivePin(state-2);
    state++;
  if(state==11) {
  vibrate(4000);
    state=0;}       
  }
  
  digitalWrite(RCLK_Pin, LOW);
    delay(2000);
}
void vibrate(int t) {
    digitalWrite(vibreur, HIGH);
    delay(t);
    digitalWrite(vibreur, LOW);
}


