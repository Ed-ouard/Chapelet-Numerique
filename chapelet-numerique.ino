int SER_Pin = 7;   //pin 14 on the 75HC595
int RCLK_Pin = 8;  //pin 12 on the 75HC595
int SRCLK_Pin = 9; //pin 11 on the 75HC595
 
//How many of the shift registers - change this
#define number_of_74hc595s 1 
 
//do not touch
#define numOfRegisterPins number_of_74hc595s * 8
 

boolean registers[numOfRegisterPins];
 
void setup(){
  Serial.begin(9600);
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
 
  //reset all register pins
  clearRegisters();
 // writeRegisters();

 
  digitalWrite(RCLK_Pin, LOW);
 setRegisterPin(0, LOW);
  setRegisterPin(1, HIGH);
  setRegisterPin(2, HIGH);
  setRegisterPin(3, LOW);
  setRegisterPin(4, LOW);
  setRegisterPin(5, LOW);
 setRegisterPin(6, HIGH);
 setRegisterPin(7, HIGH);
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
 Serial.print(val);
    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);
 
  }
  Serial.println();
  digitalWrite(RCLK_Pin, HIGH);
 
}
 
//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
    digitalWrite(SRCLK_Pin, LOW);
    digitalWrite(SER_Pin, value);
    digitalWrite(SRCLK_Pin, HIGH);
}
 
void loop(){
 
 
 // writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
  //Only call once after the values are set how you need.
}
