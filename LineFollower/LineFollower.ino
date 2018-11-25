
/*
 * Pins configuration
 */
const int selectPins[3] = {A1, A2, A3};
const int zInput = A0;


int STBY = 9; //standby
int PWMA = 5; //Speed control
int AIN1 = 2; //Direction
int AIN2 = 4; //Direction
int PWMB = 6; //Speed control
int BIN1 = 7; //Direction
int BIN2 = 8; //Direction

/*
 * Control flags
 */
bool _startFlag = false;
bool _isDragRace = false;
bool _isError = false;


/*
 * Algorithm values
 */
int blackColor;
int whiteColor;
int errorColor;

unsigned int frontSensorsOutputs[2];
unsigned int backSensorsOutputs[6];
bool frontSensors[2];
bool backSensors[6];

byte motorASpeed;
bool motorADirection;
byte motorBSpeed;
bool motorBDirection;


void setup() {
/*
 * Initialize serial ports
 */
  Serial1.begin(9600);// Initialize the BT serial port
  //Serial.begin(9600); // Initialize the serial port
  
/*
 * Initialize multiplexer ports
 */
  for (int i = 0; i < 3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zInput, INPUT); // Set up Z as an input

/*
 * Initialize sensor
 */
  sensorsCalibration();
  
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
}

void loop() {
  comunicationLoop();
  if(_startFlag){
    if(_isDragRace)
      dragRaceControl();
    else
      normalRaceControl();
      
    if(!_isError){
      move(0, motorASpeed, motorADirection);
      move(1, motorBSpeed, motorBDirection);
    }
  }

  if(_isError)
    stop();
}
