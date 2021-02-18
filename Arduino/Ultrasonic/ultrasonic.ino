#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
float distance; // variable for the distance measurement
float maxDistance;// maximum distance of the tank
float waterPercentage;// the water percentage that the tank has
float totalPercentage;// the mode of X number of signals
int signalNumber = 200; // signal number
int signalTemp = 200; // a editable signal number
float signalArray[200]; // array of signals

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
}
void loop() {
  while(signalTemp-1 >= 0){
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = (duration-10) * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    /*if(distance > 33){
      distance = 33;
    }*/
    waterPercentage = 100-((distance/33)*100);
    signalArray[signalTemp-1]=waterPercentage;
    signalTemp--;
    Serial.print(signalNumber-signalTemp);
    Serial.print(")");
    //Serial.println(waterPercentage);
    Serial.println(distance);
  }
    Serial.print("Total Percentage: ");
    mode();
    Serial.print(totalPercentage);
    Serial.println(" %");
    delay(400000);
}

void mode(){
  float finale;
  float ct = 0;
  float v = -1;
  float modeCt = 0;
  float modeV = -1;

for(int i = 0; i < signalNumber; i++) {
  if(signalArray[i] != v) {
    v = signalArray[i];
    ct = 0;
  }

  ct ++;

  if(ct > modeCt) {
    modeCt = ct;
    modeV = v;
  }
}
  totalPercentage = modeV;
}
