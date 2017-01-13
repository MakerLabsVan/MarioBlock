/*-----( Import)-----*/
#include <Wire.h> //Include the Wire library
#include <MMA_7455.h> //Include the MMA_7455 library

/*-----( Declare Variables )-----*/
MMA_7455 mySensor = MMA_7455(); //Make an instance of MMA_7455
#define numElements(x) sizeof(x)/sizeof(x[0])
char xOldVal, yOldVal, zVal, xNewVal, yNewVal; //Variables for the values from the sensor
char sensitivity = 10; //used to calculate difference between old and new position; the lower the number, the more sensitive
char speakerPin = 8;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
  delay(500);
  // Set the sensitivity you want to use
  // 2 = 2g, 4 = 4g, 8 = 8g
  mySensor.initSensitivity(2); // Good for "Tilt" measurements
/* Calibrate the Offset. Calibrate, in Flat position, try to
    get: xVal = 0, yVal = 0, zVal = +63 (1 G)
   !!!Activate this after having the first values read out!!!
   Suggestion: Run this with offsets = 0,0,0 and see needed correction
*/
  // mySensor.calibrateOffset(0,0,0); //Uncomment for first try: find offsets
  // mySensor.calibrateOffset(-5.0, 13.0, -12.0); //Then Uncomment and use this
  
}//--(end setup )---

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  xOldVal = mySensor.readAxis('x'); //Read out the 'x' Axis
  yOldVal = mySensor.readAxis('y'); //Read out the 'y' Axis
  zVal = mySensor.readAxis('z'); //Read out the 'z' Axis
  delay(200);
  xNewVal = mySensor.readAxis('x'); //Read out the 'x' Axis
  yNewVal = mySensor.readAxis('y'); //Read out the 'y' Axis
/*--( Show tilt [Assumes unit has been calibrated ] )----*/  
  if (abs(xNewVal-xOldVal) >= sensitivity || (yNewVal-yOldVal) >= sensitivity){ //if positions change, play sound
    Serial.println("Shaked"); 
    playCoinSound();
    delay(250);
  }
  if (zVal < -45 ) Serial.println("UPSIDE DOWN!");    
  delay(200);
}//--(end main loop )---

void playCoinSound() { //plays mario coin block sound
  int coinNotes[] = { 988, 1319 };
  int coinNoteDurations[] = { 125, 400 };
  int numCoinNotes = numElements(coinNotes);

  for (int i = 0; i < numCoinNotes; i++) {
        tone(speakerPin, coinNotes[i]);
        delay(coinNoteDurations[i]);
        noTone(speakerPin);
    }
}
