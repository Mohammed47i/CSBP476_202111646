
#define Rpwm_pin 10//enable B
#define Lpwm_pin 5//enable A
int M1_Speed = 80; // speed of motor 1
int M2_Speed = 80; // speed of motor 2
int LeftSpeed = 250;  // Left  Speed
int RightSpeed = 250; // Right Speed
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6

void setup() {//input output setup
  pinMode(IN1,OUTPUT);//set motors as outputs
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(Rpwm_pin,OUTPUT);//set enables as outputs
  pinMode(Lpwm_pin,OUTPUT);

  pinMode(A0, INPUT); // initialize Left sensor setup as input
  pinMode(A1, INPUT); // initialize Right sensor setup as input
}

void loop() {
  int LS = digitalRead(A0);//reading the value of the left IR sensor
  int RS = digitalRead(A1);//reading the value of the right IR sensor

  if(RS==0 && LS==0) {// if both sensors detect black, the car moves forward
    forward(); 
  }
  else if(RS==0 && LS==1) {// if only the right sensor detects black, the car moves left
    left();
  }
  else if(RS==1 && LS==0) {// if only the left sensor detects black, the car moves right
    right();
  }
  else if(RS==1 && LS==1) {// if both sensors detect white, the car stops
    Stop(); 
  }
}

// motion controling functions
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(Rpwm_pin, M1_Speed);
  analogWrite(Lpwm_pin, M2_Speed);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(Rpwm_pin, M1_Speed);
  analogWrite(Lpwm_pin, M2_Speed);
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(Rpwm_pin, LeftSpeed);
  analogWrite(Lpwm_pin, RightSpeed);
}

void left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(Rpwm_pin, LeftSpeed);
  analogWrite(Lpwm_pin, RightSpeed);
}
