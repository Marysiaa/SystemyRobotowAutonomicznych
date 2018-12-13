/*
 * Robot configuration parameters
 */
int kProviderFront = 50;
int kProviderBack = 300;
int errorMax = 200;
int maxSpeed = 180; //max value is 255
int minSpeed = 10;
float alpha = 5;


/*
 * Algorithm values
 */

unsigned int frontSensorsOutputs[2];
unsigned int backSensorsOutputs[6];
bool frontSensors[2];
bool backSensors[6];
float accelerationMotorA;
float accelerationMotorB;
