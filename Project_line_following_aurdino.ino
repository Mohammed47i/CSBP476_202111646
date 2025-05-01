// define mode Switch pin
#define modeSwitch 2
 
// define motors pins
#define PWMA 5    // controls power to right motor
#define PWMB 6    // controls power to left motor
#define AIN1 7    // controls direction of right motor, HIGH = FORWARD, LOW = REVERSE
#define BIN1 8    // controls direction of left motor, HIGH = FORWARD, LOW = REVERSE
#define STBY 3    // controls standby if LOW, run if HIGH
 
// define ultrasonic pins
#define TRIG_PIN 13   // pin to trigger pin on the ultrasonic sensor
#define ECHO_PIN 12   // pin to echo pin on the ultrasonic sensor
#define MAX_DISTANCE 20   // maximum distance we want to ping for (in centimeters)
 
// define line tracking pins
#define ITR_R A0    // pin to right sensor
#define ITR_M A1    // pin to middle sensor
#define ITR_L A2    // pin to left sensor
 
void setup() {
  // motors initialization
  pinMode(PWMA, OUTPUT); 
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH); // enable motors to run
  
  // ultrasonic module initialization
  pinMode(ECHO_PIN, INPUT); 
  pinMode(TRIG_PIN, OUTPUT);
 
  // line tracking module initialization
  pinMode(ITR_R, INPUT);
  pinMode(ITR_M, INPUT);
  pinMode(ITR_L, INPUT);
}
 
void loop() {
  while (digitalRead(modeSwitch) == 1);   // wait for mode switch to be pressed
  delay(1000);    // wait 1 second then start to ensure stable startup
 
  while (true) {
    obstacle_detection();   // function for obstacle detection
    line_tracking();        // function for line tracking
  }
}
 
// obstacle detection function logic
void obstacle_detection() {
  long duration;
  int distance;
  while (true) {    // keep checking until the obstacle is removed
    // short pulse to trigger the ultrasonic sensor
    digitalWrite(TRIG_PIN, LOW);
    delay(2);
    digitalWrite(TRIG_PIN, HIGH);
    delay(10);
    digitalWrite(TRIG_PIN, LOW);
    
    // read the echo pin and calculate the distance
    duration = pulseIn(ECHO_PIN, HIGH); //measures the echo duration
    distance = duration * 0.034 / 2;  // Convert to cm
    
    // if an obstacle is detected within MAX_DISTANCE, stop the robot
    if (distance > 0 && distance <= MAX_DISTANCE) { stop(); }
    else { break; }   // exit the loop when the obstacle is removed
    delay(500);      // small delay to avoid excessive sensor readings
  }
}
 
// line tracking function logic
void line_tracking(){
  // booleans to store sensor values: 1 for black, 0 for white
  bool left = digitalRead(ITR_L);
  bool middle = digitalRead(ITR_M);
  bool right = digitalRead(ITR_R);
 
  if (!left && middle && !right) {    // centered on the line
    forward();                    // move forward
  } 
  else if (left && middle) {        // line detected between left and middle
    turnLeft();                     // drifting right → gentle left correction
  } 
  else if (middle && right) {      // line detected between middle and right
    turnRight();                   // drifting left → gentle right correction
  }
  else if (left && !middle) {     // line detected on most left 
    sharpLeft();                  // far right of line → sharp left turn
  }
  else if (!middle && right) {   // line detected on most right
    sharpRight();                // Far left of line → sharp right turn
  }
  else if (!left && !middle && !right) {   // line is not detected
    recover();                             // Lost line → search for line
  }
  else {    // if none of the above, stop for safety
    stop();
  }
}
 
// motor control functions
// motor A: right, motor B: left
void stop() {
  // set both motor speeds to 0
  analogWrite(PWMB, 0);
  analogWrite(PWMA, 0);
}
 
void forward() {
  // set them to forward direction and same speed
 //Both motors rotate in the same direction
  digitalWrite(AIN1, HIGH);   
  digitalWrite(BIN1, HIGH);
  analogWrite(PWMA, 120);
  analogWrite(PWMB, 120);
}
 
void backward() {
  // set them to reverse direction and same speed
 //Both motors rotate in the same direction
  digitalWrite(AIN1, LOW); 
  digitalWrite(BIN1, LOW);
  analogWrite(PWMA, 150);
  analogWrite(PWMB, 150);
}
 
void turnLeft() {
  // gentle left turn: both to forward direction but reduce left speed, increase right speed
  digitalWrite(AIN1, HIGH); 
  digitalWrite(BIN1, HIGH);
  analogWrite(PWMA, 110); // Faster right
  analogWrite(PWMB, 50);  // Slower left
}
 
void turnRight() {
  // gentle right turn: both to forward direction but reduce right speed, increase left speed
  digitalWrite(AIN1, HIGH); 
  digitalWrite(BIN1, HIGH);
  analogWrite(PWMA, 50);
  analogWrite(PWMB, 110);
}
 
void sharpLeft() {
  // turn sharply left: same speed for both but left reverse, right forward
  digitalWrite(AIN1, HIGH); 
  analogWrite(PWMA, 70);
  digitalWrite(BIN1, LOW);
  analogWrite(PWMB, 70);
}
 
void sharpRight() {
  // turn sharply right: same speed for both but right reverse, left forward
  digitalWrite(AIN1, LOW);
  analogWrite(PWMA, 70); // Right motor reverse
  digitalWrite(BIN1, HIGH);
  analogWrite(PWMB, 70); // Left motor forward
}
 
void recover() {  // recovering algorithm when robot loses the line
  stop(); //to prevent unintended forward motion
  backward();
  delay(10);
  stop(); //ensuring the robot does not overshoot or drift
}
