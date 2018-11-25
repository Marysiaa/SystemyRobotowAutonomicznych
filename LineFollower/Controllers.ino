

char _commandCharacter;
void comunicationLoop(){
  if (Serial1.available()) {
    _commandCharacter = Serial1.read();
    
    if(_commandCharacter =='s')
      _startFlag = true;
    else if(_commandCharacter =='d')
      _isDragRace = true;
      
    //TODO: add more parameters to configuration
   // Serial1.print("xd");
  //c=   Serial1.read() + 1;
  //  Serial1.print(c);
  }

  //TODO: add BT output (debug mode?) 
  //Serial1.print(String(sensors[0]) + "\t");  
}


void normalRaceControl(){

  getFrontSensorsValues();

  //both front sensors returned black colors
  if(frontSensors[0] && frontSensors[1]){
    getBackSensorsValues();

    
  }
  //TODO: add algorithm implementation for set motors settings

  /*
   * set valuse:
   * byte motorASpeed;
bool motorADirection;
byte motorBSpeed;
bool motorBDirection;
   * 
   */

  
}
void dragRaceControl(){
  getFrontSensorsValues();

  //TODO: add algorithm implementation for set motors settings
  
  /*
   * set valuse:
   * byte motorASpeed;
bool motorADirection;
byte motorBSpeed;
bool motorBDirection;
   * 
   */
}
