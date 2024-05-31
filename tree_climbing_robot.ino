#include <Servo.h>

// Create Servo objects to control the grippers, flippers, and rotation mechanism
Servo gripper_1;
Servo gripper_2;
Servo flip_1;
Servo flip_2;
Servo rotate_servo; // Rename to avoid confusion

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

// Function declarations
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

// Function to read FSR value
int fsr(int fsrPin, int &fsrReading) {
  fsrReading = analogRead(fsrPin);  // Read the FSR value
  delay(10);  // Short delay for stable reading
  Serial.print(fsrPin);
  Serial.print(" FSR Reading: ");
  Serial.println(fsrReading);
  return fsrReading;
}

// Close gripper 1 based on FSR readings
void gripperClose_1() {
    if (!closed_1) {  // Check if gripper is already closed
        for (float angle = 270; angle >= 0; angle -= 3) {
            fsr(fsrPin_1, fsrReading_1);  // Read FSR value
            if (fsrReading_1 >= 400) {  // Check if gripping force is sufficient
                closed_1 = true;  // Mark gripper as closed
                break;
            } else {
                gripper_1.write(angle);  // Move gripper to the new angle
            }
            final_angle_1 = angle;  // Update final angle
        }
        Serial.print("Final angle for gripper_1: ");
        Serial.println(final_angle_1);
    }
}

// Open gripper 1
void gripperOpen_1() {
    gripper_1.write(270);  // Move gripper to open position
    closed_1 = false;  // Mark gripper as open
}

// Close gripper 2 based on FSR readings
void gripperClose_2() {
    if (!closed_2) {  // Check if gripper is already closed
        for (float angle = 270; angle >= 0; angle -= 3) {
            fsr(fsrPin_2, fsrReading_2);  // Read FSR value
            if (fsrReading_2 >= 400) {  // Check if gripping force is sufficient
                closed_2 = true;  // Mark gripper as closed
                break;
            } else {
                gripper_2.write(angle);  // Move gripper to the new angle
            }
            final_angle_2 = angle;  // Update final angle
        }
        Serial.print("Final angle for gripper_2: ");
        Serial.println(final_angle_2);
    }
}

// Open gripper 2
void gripperOpen_2() {
    gripper_2.write(270);  // Move gripper to open position
    closed_2 = false;  // Mark gripper as open
}

// Flip up mechanism
void flip_up() {
  if (!fliped_up) {
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_2.write(angle);
        delay(10);  // Delay for smooth movement
    }
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_1.write(angle);
        delay(10);  // Delay for smooth movement
    }
  } else {
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_1.write(angle);
        delay(10);  // Delay for smooth movement
    }
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_2.write(angle);
        delay(10);  // Delay for smooth movement
    }
  }
  fliped_up = !fliped_up;  // Toggle flip state
}

// Flip down mechanism
void flip_down() {
  if (!fliped_down) {
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_1.write(angle);
        delay(10);  // Delay for smooth movement
    }
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_2.write(angle);
        delay(10);  // Delay for smooth movement
    }
  } else {
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_2.write(angle);
        delay(10);  // Delay for smooth movement
    }
    for (float angle = 0; angle <= 180; angle += 1) {
        flip_1.write(angle);
        delay(10);  // Delay for smooth movement
    }
  }
  fliped_down = !fliped_down;  // Toggle flip state
}

// Rotate to avoid obstacles
void rotate() {
    Serial.println("Rotating to avoid obstacle");
    rotate_servo.write(90); // Move servo to rotate
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
        rotate();  // Rotate if obstacle is detected within range
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
    rotate_servo.attach(8); // Attach the rotation servo
}

// Main loop function
void loop() {
    if (!reached_top) {
      if (!fliped_up) {
        avoid(trigPin_1, echoPin_1);
        avoid(trigPin_2, echoPin_2);
        gripperClose_1();
        gripperClose_2();
        flip_up();
        gripperOpen_2();
        gripperClose_2();
      } else {
        avoid(trigPin_1, echoPin_1);
        avoid(trigPin_2, echoPin_2);
        gripperClose_1();
        gripperClose_2();
        flip_up();
        gripperOpen_1();
        gripperClose_1();
      }
    } else {
        if (!fliped_down) {
        avoid(trigPin_1, echoPin_1);
        avoid(trigPin_2, echoPin_2);
        gripperClose_1();
        gripperClose_2();
        flip_down();
        gripperOpen_1();
        gripperClose_1();
      } else {
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
