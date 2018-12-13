#include <QTRSensors.h>

/*
 * Pins configuration
 */
const int selectPins[3] = {A1, A2, A3};
const int zInput = A0;

/*
 * Algorithm values
 */
int lineColor;
int bgColor;
int errorColor;

float frontColor0 = 0;
float frontColor1 = 0;

QTRSensorsAnalog qtr((unsigned char[]) {
  A0
}, 1);


void SetupQtr(){
  for (int i = 0; i < 250; i++)
  {
    qtr.calibrate();
    delay(20);
  }
}

void MultiplexerInitialize(){
  for (int i = 0; i < 3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zInput, INPUT); // Set up Z as an input
}

void sensorsCalibration(){
  
  int _lineColorsAcum =0, _bgColorAcum =0;

  for (int i = 0; i < 10; i++){
    getFrontSensorsValues();
    getBackSensorsValues();
    _lineColorsAcum =  (_lineColorsAcum + frontSensorsOutputs[0]+frontSensorsOutputs[1]);
    _bgColorAcum = (_bgColorAcum + backSensorsOutputs[0]+backSensorsOutputs[1] + backSensorsOutputs[4]+backSensorsOutputs[5]);
  }

  bgColor = _bgColorAcum*0.025;
  lineColor = _lineColorsAcum*0.05;


  if(  lineColor > bgColor)
    errorColor=0.20*lineColor;  
  else
    errorColor=0.50*lineColor;

  
  for (int i = 0; i < 10; i++){
    getFrontSensorsValues();

    frontColor0 = frontColor0 +frontSensorsOutputs[0];
    frontColor1 = frontColor1 +frontSensorsOutputs[1];
  }
  frontColor0 = frontColor0 * 0.1;
  frontColor1 = frontColor1 * 0.1;
}

void getFrontSensorsValues(){
  frontSensorsOutputs[0] =getSensorOutput(6);
  frontSensorsOutputs[1] =getSensorOutput(7);

  frontSensors[0] = getSensorStatus(frontSensorsOutputs[0],frontColor0);
  frontSensors[1] = getSensorStatus(frontSensorsOutputs[1],frontColor1);
}

void getBackSensorsValues(){
  for (byte sensor = 0; sensor < 6; sensor++)
    backSensorsOutputs[sensor] = getSensorOutput(sensor);

  for (byte sensor = 0; sensor < 6; sensor++)
    backSensors[sensor] = getSensorStatus(backSensorsOutputs[sensor],lineColor);
}

bool getSensorStatus(unsigned int value,unsigned int centralValue){
  if(value > centralValue-errorColor && value < centralValue+errorColor)
    return 1;
  return 0;
}

void selectMuxPin(byte pin){
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

void printSensorValues(){
  Serial.print("f: ");
  for (int k =0; k < 2; k++){
    Serial.print(frontSensors[k]);
    Serial.print(" ");
  }
  Serial.print("b: ");
  for (int k =0; k <6;k++){
    Serial.print(backSensors[k]);
    Serial.print(" ");
  }
  Serial.print(" front0 ");
  Serial.print(frontSensorsOutputs[0]);
  Serial.print(" front1 ");
  Serial.print(frontSensorsOutputs[1]);
  Serial.print("\t");
}
