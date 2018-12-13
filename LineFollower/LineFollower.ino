
/*
 * Time variables
 */
unsigned long oldTime;
unsigned long currentTime;
unsigned long deltaTime;


/*
 * Control flags
 */
bool _startFlag = false;
bool _isError = false;
bool _isDebug = false;

void setup() {
/*
 * Initialize serial ports
 */
  Serial1.begin(9600);  // Initialize the BT serial port
  Serial.begin(9600);   // Initialize the serial port
  
  MultiplexerInitialize();
  MotorsInitialize();
  SetupQtr();

  currentTime= millis();
}

void loop() {
/*
 * Calculate delta time
 */
  oldTime = currentTime;
  currentTime = millis();
  deltaTime = currentTime - oldTime;

  comunicationLoop();
  
  if(_startFlag){
    raceControl();
    if(!_isError)
      setMotorSpeeds();
  }

  if(_isError)
    stop();
}
