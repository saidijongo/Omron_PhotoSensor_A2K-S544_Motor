#define CW_PIN 5
#define CCW_PIN 6

#define RIGHT_SENSOR 11
#define LEFT_SENSOR 10

#define RIGHT_LED 8
#define LEFT_LED 9

int current_angle = 0;

void setup() {
  pinMode(CW_PIN, OUTPUT);
  pinMode(CCW_PIN, OUTPUT);
  pinMode(RIGHT_SENSOR, INPUT_PULLUP);
  pinMode(LEFT_SENSOR, INPUT_PULLUP);
  pinMode(RIGHT_LED, OUTPUT);
  pinMode(LEFT_LED, OUTPUT);
  Serial.begin(9600);
}

void rotate_motor(int steps, int direction) {
  digitalWrite(direction, HIGH);
  for (int i = 0; i < steps; i++) {
    digitalWrite(CW_PIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(CW_PIN, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(direction, LOW);
}

void loop() {
  if (digitalRead(RIGHT_SENSOR) == LOW) {
    digitalWrite(RIGHT_LED, HIGH);
    delay(3000);
    digitalWrite(RIGHT_LED, LOW);

    rotate_motor(8 * 50, CCW_PIN); // Rotating 8 degrees in CCW direction
    delay(1000);  // Pause for 1 second
    rotate_motor(8 * 50, CW_PIN);  // Rotating back 8 degrees in CW direction
    current_angle = 0; // Updating the current angle
    Serial.println("Home Position");
  }

  if (digitalRead(LEFT_SENSOR) == LOW) {
    digitalWrite(LEFT_LED, HIGH);
    delay(3000);
    digitalWrite(LEFT_LED, LOW);

    rotate_motor(8 * 50, CCW_PIN); // Rotating 8 degrees in CCW direction
    delay(1000);  // Pause for 1 second
    rotate_motor(8 * 50, CW_PIN);  // Rotating back 8 degrees in CW direction
    current_angle = 0; // Updating the current angle
    Serial.println("Home position");
  }

  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'C') {
      rotate_motor(90 * 50, CW_PIN); // Rotating 90 degrees in CW direction
      current_angle += 90; // Updating current angle
      Serial.println(current_angle);
    } else if (command == 'D') {
      rotate_motor(90 * 50, CCW_PIN); // Rotating 90 degrees in CCW direction
      current_angle -= 90; // Updating the current angle
      Serial.println(current_angle);
    } else if (command == 'S') {
      // Stopping motor immediately
      digitalWrite(CW_PIN, LOW);
      digitalWrite(CCW_PIN, LOW);
      Serial.println(current_angle);
    }
  }
}
