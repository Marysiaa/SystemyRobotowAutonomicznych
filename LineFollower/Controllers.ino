

char _commandCharacter;
void comunicationLoop(){
  if (Serial1.available()) {
    _commandCharacter = Serial1.read();
    switch(_commandCharacter){
      case 's':
        startRaceFunction();
        break;
      case 'k':
        kProviderBack = Serial1.parseInt();
        break;
      case 'l':
        kProviderFront = Serial1.parseInt();
        break;
      case 'e':
        _isError = true;
        break;
      case 'a':
        minSpeed = Serial1.parseInt();
        break;
      case 'b':
         maxSpeed = Serial1.parseInt();
        break;
      case 'x':
        errorMax = Serial1.parseInt();
        break;
      case 'g':
        alpha = Serial1.parseInt();
      case 'd':
        if(_isDebug)
          _isDebug = false;
        else
          _isDebug = true;
        break;
      default:
        break;
    }
    printConfiguration();
  }
  
  if(_isDebug && _startFlag && !_isError){
    printSensorValues();
    printSpeedValues();
    Serial.println();
  }
}

void startRaceFunction(){
  sensorsCalibration();
  _startFlag = true;
  _isError = false;
}

void printConfiguration(){
  Serial1.print("maxSpeed: ");
  Serial1.print(maxSpeed);
  Serial1.print(" minSpeed: ");
  Serial1.print(minSpeed);
  Serial1.print(" kProviderBack: ");
  Serial1.print(kProviderBack);
  Serial1.print(" kProviderFront: ");
  Serial1.print(kProviderFront);
  Serial1.print(" errorMax: ");
  Serial1.print(errorMax);
  Serial1.print(" alpha: ");
  Serial1.print(alpha);
  Serial1.println();
}

int eFunctionFront(){
  if(frontSensors[0] &&frontSensors[1])
    return 0;
  else if (!frontSensors[0])
    return -1;
  return 1;
}

int eFunctionBack(){
  for( int k = 0; k < 3;k++){
    if(backSensors[k])
      return 3-k;
    else if(backSensors[5-k])
      return k-3;
  }
  return 0;
}

int _prevE =0;
int _du, _e,_k;
int _countError = 0;
void raceControl(){

  getFrontSensorsValues();
  
  //both front sensors returned black colors
  if(!frontSensors[0] && !frontSensors[1]){

    getBackSensorsValues();
    _e = eFunctionBack();

    if(_e == 0){
       _countError++;
      _e = _prevE;
    }else{
      _countError = 0;
      _prevE = _e;
    }
    _k = kProviderBack;  
  }else{
    _countError = 0;
    _e = eFunctionFront();    
    _k = kProviderFront;
  }

  if(_countError > errorMax)
    _isError = true;
  
  _du = _k * _e;

  accelerationMotorA =_du ;
  accelerationMotorB =  -_du;
}
