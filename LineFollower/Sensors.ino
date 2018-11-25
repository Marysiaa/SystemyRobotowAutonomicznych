#include <QTRSensors.h>

QTRSensorsAnalog qtr((unsigned char[]) {
  A0
}, 1);

void sensorsCalibration(){

  int i;
  for (i = 0; i < 250; i++)  // make the calibration take about 5 seconds
  {
    qtr.calibrate();
    delay(20);
  }

  
/*
 * setup 3 parameters:
int blackColor;
int whiteColor;
int errorColor;
 */
 //TODO: add calibration for sensors outputs
}

void getFrontSensorsValues(){
  frontSensorsOutputs[0] =getSensorOutput(6);
  frontSensorsOutputs[1] =getSensorOutput(7);

  frontSensors[0] = getSensorStatus(frontSensorsOutputs[0]);
  frontSensors[1] = getSensorStatus(frontSensorsOutputs[1]);
}

void getBackSensorsValues(){
  for (byte sensor = 0; sensor < 6; sensor++)
  {
    backSensorsOutputs[sensor] = getSensorOutput(sensor);
  }

  for (byte sensor = 0; sensor < 6; sensor++)
  {
    backSensors[sensor] = getSensorStatus(backSensorsOutputs[sensor]);
  }
}

bool getSensorStatus(unsigned int value){
  if(value > blackColor-errorColor && value < blackColor+errorColor)
    return 1;
  return 0;
}

void selectMuxPin(byte pin)
{
  for (int i = 0; i < 3; i++)
  {
    if (pin & (1 << i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}

unsigned int _sensorTemp[1];
unsigned int getSensorOutput(byte pin){
  selectMuxPin(pin);
  qtr.read(_sensorTemp);
  return _sensorTemp[0];
}
