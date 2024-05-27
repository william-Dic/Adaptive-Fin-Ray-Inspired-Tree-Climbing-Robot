#include <Servo.h>

Servo gripper_1;
Servo gripper_2;
Servo flip_1;
Servo flip_2;
Servo rotate_servo; // Rename to avoid confusion

const int trigPin_1 = 8;
const int echoPin_1 = 9;
const int trigPin_2 = 10;
const int echoPin_2 = 11;

int fsrPin_1 = 0; 
int fsrReading_1;  
int fsrPin_2 = 1; 
int fsrReading_2;   

int final_angle_1;
int final_angle_2;

bool closed_1 = false;  
bool closed_2 = false;  

bool reached_top = false; 
bool fliped_up = false;
bool fliped_down = false;

void gripperClose_1();
void gripperClose_2();
void gripperOpen_1();
void gripperOpen_2();
void flip_up();
void flip_down();
void rotate();
void setup();
float distance_detect(int trigPin, int echoPin);
void avoid(int trigPin, int echoPin);

int fsr(int fsrPin, int &fsrReading) {
  fsrReading = analogRead(fsrPin);  
  delay(10);
  Serial.print(fsrPin);
  Serial.print(" FSR Reading: ");
  Serial.println(fsrReading);
  return fsrReading;
}

void gripperClose_1() {
    if (!closed_1) {
        for (float angle = 270; angle >= 0; angle -= 3) {
            fsr(fsrPin_1, fsrReading_1);
            if (fsrReading_1 >= 400) {
                closed_1 = true;
                break;
            } else {
                gripper_1.write(angle);
            }
            
            final_angle_1 = angle;
        }
        Serial.print("Final angle for gripper_1: ");
        Serial.println(final_angle_1);
    }
}

void gripperOpen_1() {
    gripper_1.write(270);
    closed_1 = false;
}

void gripperClose_2() {
    if (!closed_2) {
        for (float angle = 270; angle >= 0; angle -= 3) {
            fsr(fsrPin_2, fsrReading_2);
            if (fsrReading_2 >= 400) {
                closed_2 = true;
                break;
            } else {
                gripper_2.write(angle);
            }
            final_angle_2 = angle;
        }
        Serial.print("Final angle for gripper_2: ");
        Serial.println(final_angle_2);
    }
}

void gripperOpen_2() {
    gripper_2.write(270);
    closed_2 = false;
}

void flip_up() {
  if (!fliped_up){
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_2.write(angle);
        delay(10);
    }

    for (float angle = 0; angle <= 180; angle += 1) {
        flip_1.write(angle);
        delay(10);
    }
  }else{
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_1.write(angle);
        delay(10);
    }

    for (float angle = 0; angle <= 180; angle += 1) {
        flip_2.write(angle);
        delay(10);
    }
  }
  fliped_up = !fliped_up;
}

void flip_down() {
  if (!fliped_down){
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_1.write(angle);
        delay(10);
    }

    for (float angle = 0; angle <= 180; angle += 1) {
        flip_2.write(angle);
        delay(10);
    }
  }else{
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_2.write(angle);
        delay(10);
    }

    for (float angle = 0; angle <= 180; angle += 1) {
        flip_1.write(angle);
        delay(10);
    }
  }
  fliped_down = !fliped_down;
}

void rotate() {
    Serial.println("Rotating to avoid obstacle");
    rotate_servo.write(90); // Use the correct servo
}

float distance_detect(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    if (duration == 0) {
        Serial.println("No echo received");
    }
    float distance = (duration * 0.0343) / 2;
    Serial.println("Obstacle Distance:");
    Serial.println(distance);
    return distance;
}

void avoid(int trigPin, int echoPin) {
    float distance = distance_detect(trigPin, echoPin);
    if (distance <= 30 && distance > 10) {
        rotate();
    } else if (distance <= 10) {
        reached_top = true;
        Serial.println("Reached Top");
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(trigPin_1, OUTPUT);
    pinMode(echoPin_1, INPUT);
    pinMode(trigPin_2, OUTPUT);
    pinMode(echoPin_2, INPUT);
    gripper_1.attach(3);
    gripper_2.attach(7);
    flip_1.attach(6);
    flip_2.attach(5);
    rotate_servo.attach(8); // Use the correct servo
}

void loop() {
    if (!reached_top) {
      if (!fliped_up){
        avoid(trigPin_1, echoPin_1);
        avoid(trigPin_2, echoPin_2);
        gripperClose_1();
        gripperClose_2();
        flip_up();
        gripperOpen_2();
        gripperClose_2();
      }else{
        avoid(trigPin_1, echoPin_1);
        avoid(trigPin_2, echoPin_2);
        gripperClose_1();
        gripperClose_2();
        flip_up();
        gripperOpen_1();
        gripperClose_1();
      }
    } else {
        if (!fliped_down){
        avoid(trigPin_1, echoPin_1);
        avoid(trigPin_2, echoPin_2);
        gripperClose_1();
        gripperClose_2();
        flip_down();
        gripperOpen_1();
        gripperClose_1();
      }else{
        avoid(trigPin_1, echoPin_1);
        avoid(trigPin_2, echoPin_2);
        gripperClose_1();
        gripperClose_2();
        flip_down();
        gripperOpen_2();
        gripperClose_2();
      }
    }
}
