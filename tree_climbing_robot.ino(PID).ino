#include <Servo.h>

// Create Servo objects to control the grippers, flippers, and rotation mechanism
Servo gripper_1;
Servo gripper_2;
Servo flip_1;
Servo flip_2;
Servo rotate_servo;
Servo sensor_release_servo; // Declare sensor release servo

// Define pins for the ultrasonic sensors
const int trigPin_1 = 8;
const int echoPin_1 = 9;
const int trigPin_2 = 10;
const int echoPin_2 = 11;

// Define pins and variables for force sensitive resistors (FSRs)
int fsrPin_1 = 0; 
int fsrReading_1;  
int fsrPin_2 = 1; 
int fsrReading_2;   

// Variables to store final angles for the grippers
int final_angle_1;
int final_angle_2;

// Flags to indicate the state of the grippers and the robot
bool closed_1 = false;  
bool closed_2 = false;  
bool reached_top = false; 
bool fliped_up = false;
bool fliped_down = false;
bool sensor_delivered = false; // Declare sensor delivered flag

// PID parameters for gripper 1
float kp_1 = 1.0;
float ki_1 = 0.1;
float kd_1 = 0.05;
float previous_error_1 = 0;
float integral_1 = 0;

// PID parameters for gripper 2
float kp_2 = 1.0;
float ki_2 = 0.1;
float kd_2 = 0.05;
float previous_error_2 = 0;
float integral_2 = 0;

// Function declarations
void gripperControl_1();
void gripperControl_2();
void gripperOpen_1();
void gripperOpen_2();
void flip_up();
void flip_down();
void rotate();
void sensor_release();
void setup();
float distance_detect(int trigPin, int echoPin);
void avoid(int trigPin, int echoPin);

// Function to read FSR value
int fsr(int fsrPin, int &fsrReading) {
  fsrReading = analogRead(fsrPin);  // Read the FSR value
  delay(10);  // Short delay
  Serial.print(fsrPin);
  Serial.print(" FSR Reading: ");
  Serial.println(fsrReading);
  return fsrReading;
}

// PID control function
float PID_control(float setpoint, float current_value, float &previous_error, float &integral, float kp, float ki, float kd) {
    float error = setpoint - current_value;
    integral += error;
    float derivative = error - previous_error;
    float output = kp * error + ki * integral + kd * derivative;
    previous_error = error;
    return output;
}

// Control gripper 1 based on FSR readings using PID
void gripperControl_1() {
    fsr(fsrPin_1, fsrReading_1);
    float pid_output = PID_control(400, fsrReading_1, previous_error_1, integral_1, kp_1, ki_1, kd_1);
    float angle = constrain(final_angle_1 + pid_output, 0, 270);
    gripper_1.write(angle);
    final_angle_1 = angle;
}

// Open gripper 1
void gripperOpen_1() {
    gripper_1.write(270);
    closed_1 = false;
    final_angle_1 = 270;
}

// Control gripper 2 based on FSR readings using PID
void gripperControl_2() {
    fsr(fsrPin_2, fsrReading_2);
    float pid_output = PID_control(400, fsrReading_2, previous_error_2, integral_2, kp_2, ki_2, kd_2);
    float angle = constrain(final_angle_2 + pid_output, 0, 270);
    gripper_2.write(angle);
    final_angle_2 = angle;
}

// Open gripper 2
void gripperOpen_2() {
    gripper_2.write(270);
    closed_2 = false;
    final_angle_2 = 270;
}

// Flip up mechanism
void flip_up() {
  if (!fliped_up) {
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_2.write(angle);
        delay(10);
    }
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_1.write(angle);
        delay(10);
    }
  } else {
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

// Flip down mechanism
void flip_down() {
  if (!fliped_down) {
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_1.write(angle);
        delay(10);
    }
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_2.write(angle);
        delay(10);
    }
  } else {
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

// Release the sensor
void sensor_release() {
    sensor_release_servo.write(270);
}

// Rotate to avoid obstacles
void rotate() {
    Serial.println("Rotating to avoid obstacle");
    rotate_servo.write(90); // Use the correct servo
}

// Detect distance using ultrasonic sensor
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

// Avoid obstacles based on distance detected
void avoid(int trigPin, int echoPin) {
    float distance = distance_detect(trigPin, echoPin);
    if (distance <= 30 && distance > 10) {
        rotate();
    } else if (distance <= 10) {
        reached_top = true;
        Serial.println("Reached Top");
    }
}

// Setup function to initialize pins and servos
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
    sensor_release_servo.attach(4); // Attach the sensor release servo
    rotate_servo.attach(8); // Attach the rotation servo
    final_angle_1 = 270;
    final_angle_2 = 270;
}

// Main loop function
void loop() {
    if (!reached_top) {
      if (!fliped_up) {
        avoid(trigPin_1, echoPin_1);
        avoid(trigPin_2, echoPin_2);
        gripperControl_1();
        gripperControl_2();
        flip_up();
        gripperOpen_2();
        gripperControl_2();
      } else {
        avoid(trigPin_1, echoPin_1);
        avoid(trigPin_2, echoPin_2);
        gripperControl_1();
        gripperControl_2();
        flip_up();
        gripperOpen_1();
        gripperControl_1();
      }
    } else {
      if (!sensor_delivered) {
        sensor_release();
      } else {
        if (!fliped_down) {
          avoid(trigPin_1, echoPin_1);
          avoid(trigPin_2, echoPin_2);
          gripperControl_1();
          gripperControl_2();
          flip_down();
          gripperOpen_1();
          gripperControl_1();
        } else {
          avoid(trigPin_1, echoPin_1);
          avoid(trigPin_2, echoPin_2);
          gripperControl_1();
          gripperControl_2();
          flip_down();
          gripperOpen_2();
          gripperControl_2();
        }
      }
    }
}
