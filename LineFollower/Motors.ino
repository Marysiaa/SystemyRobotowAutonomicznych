
/*
 * Pins configuration
 */
const int STBY = 9; //standby
const int PWMA = 5; //Speed control
const int AIN1 = 2; //Direction
const int AIN2 = 4; //Direction
const int PWMB = 6; //Speed control
const int BIN1 = 7; //Direction
const int BIN2 = 8; //Direction

/*
 * Algorithm values
 */
int motorASpeed;
bool motorADirection;
int motorBSpeed;
bool motorBDirection;

float motorASpeedFloat;
float motorBSpeedFloat;




float accelerationA = 255;


void MotorsInitialize(){
 /*
 * Initialize motors ports
 */
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  motorADirection =1;
  motorBDirection =1;

  motorASpeedFloat=maxSpeed;
  motorBSpeedFloat=maxSpeed;
}




float backToDefault(int motor){
  int speed =  accelerationA;
  if(speed < maxSpeed){
    speed += alpha*(float)deltaTime;
    return speed;
  }
  return maxSpeed;
}

void setMotorSpeeds(){

  if(accelerationMotorA == 0 && accelerationMotorB==0){
    motorASpeedFloat=backToDefault(0);
    motorBSpeedFloat=backToDefault(1);
  }else{
    motorASpeedFloat += ((float)accelerationMotorA * (float)deltaTime * 0.001);
    motorBSpeedFloat += ((float)accelerationMotorB * (float)deltaTime *0.001);  
  }
  
  accelerationA = (motorASpeedFloat +motorBSpeedFloat)*0.5; 
    
  if(motorASpeedFloat < minSpeed)
    motorASpeedFloat=minSpeed;  
  else if(motorASpeedFloat > maxSpeed)
    motorASpeedFloat=maxSpeed;


  if(motorBSpeedFloat < minSpeed)
    motorBSpeedFloat=minSpeed;  
  else if(motorBSpeedFloat > maxSpeed)
    motorBSpeedFloat=maxSpeed;

  //move(1, (int)motorASpeedFloat, motorADirection);
  //move(0, (int)motorBSpeedFloat, motorBDirection);
}



void move(int motor, int speed, bool direction) {
  //Move specific motor at speed and direction
  //motor: 0 for A 1 for B
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise
    
  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if (motor == 0) {
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  } else {
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop() {
  //enable standby
  digitalWrite(STBY, LOW);
}

void printSpeedValues(){
    Serial.print(" motorASpeedFloat: ");
    Serial.print(motorASpeedFloat);
    Serial.print(" motorBSpeedFloat: ");
    Serial.print(motorBSpeedFloat);
    Serial.print(" accelerationMotorA: ");
    Serial.print(accelerationMotorA);
    Serial.print(" accelerationMotorB: ");
    Serial.print(accelerationMotorB);
    Serial.print("\t");
   // Serial.println();
}
