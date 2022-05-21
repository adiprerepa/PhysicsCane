#define PI 3.1415926535897932384626433832795
int m1 = 2;
int m2 m = 3;
int echo1 = 4;
int trig1 = 5;
int echo2 = 7;
int trig2 = 6;
int echo3 = 8;
int trig3 = 9;
int ena = 10;

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(ena, OUTPUT);
  Serial.begin(9600);
}

// todo:
//  - just sweeping mode
//  - just distance sensing/adjusting mode
//  - combined (maybe)
void loop() {
  // v = v_max*sin(t)
  // positive velocity -> m1 HIGH m2 LOW
  // negative velocity -> m1 LOW m2 HIGH
  int t = 0;
  int ms_inc = 500;
  int period = 6000;
  double lastVelocity = 0;
  while (true) {
    
    //    int d1 = getDistance(echo1, trig1);
    //    int d2 = getDistance(echo2, trig2);
    //    int d3 = getDistance(echo3, trig3);
    double v = 255 * sin(2 * PI * t * ms_inc / period);
    if (lastVelocity > 0 && v < 0) {
      // reverse direction to "positive"
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
    } else if (lastVelocity < 0 && v > 0) {
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
    }
    Serial.println(v);
    analogWrite(ena, abs(int(v)));
    lastVelocity = v;
    delay(ms_inc);
    t++;

  }


}

int getDistance(int echoPin, int trigPin) {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // variable for the duration of sound wave travel

  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // returns distance
  return distance;
}
