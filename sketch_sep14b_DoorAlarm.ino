/*
  Door Motion Detector with Pulsing Alarm

  This sketch uses a PIR sensor and a reed switch module to detect
  a combined event: motion is detected AND the door is open.
  When both conditions are true, the LED blinks and the buzzer
  sounds a pulsing alarm continuously.
*/

// Define the pins for the components
const int pirPin = 8;        // PIR sensor's signal pin
const int reedSwitchPin = 7; // Reed switch module's signal pin
const int ledPin = 9;        // LED's control pin
const int buzzerPin = 10;    // Buzzer's control pin

// Timing variables for non-blocking operations
unsigned long previousLedMillis = 0;
const long ledInterval = 250; // The interval for LED blinking
int ledState = LOW; // ledState is used to set the LED

unsigned long previousBuzzerMillis = 0;
const long buzzerInterval = 250; // The interval for buzzer pulsing
int buzzerState = LOW; // buzzerState is used to control the tone

void setup() {
  // Set up the pins as outputs and inputs
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(reedSwitchPin, INPUT);
  
  // No pinMode() is needed for the buzzer with tone(), but it's good practice
  // pinMode(buzzerPin, OUTPUT);
  
  // Begin serial communication for debugging
  Serial.begin(9600);
  Serial.println("System Ready.");
}

void loop() {
  // Read the current state of both sensors
  int pirState = digitalRead(pirPin);
  int reedState = digitalRead(reedSwitchPin);

  // Check for the alarm conditions:
  if (pirState == HIGH && reedState == HIGH) {
    
    // --- Alarm Triggered ---
    
    // Check if it's time to change the LED state
    unsigned long currentMillis = millis();
    if (currentMillis - previousLedMillis >= ledInterval) {
      previousLedMillis = currentMillis;

      // Toggle the LED state
      ledState = (ledState == LOW) ? HIGH : LOW;
      digitalWrite(ledPin, ledState);
    }
    
    // Check if it's time to change the buzzer state (create pulsing)
    if (currentMillis - previousBuzzerMillis >= buzzerInterval) {
      previousBuzzerMillis = currentMillis;
      
      // Toggle the buzzer state and play/stop the tone
      if (buzzerState == LOW) {
        buzzerState = HIGH;
        tone(buzzerPin, 1000); // Play a 1000 Hz tone
      } else {
        buzzerState = LOW;
        noTone(buzzerPin); // Stop the tone
      }
    }

    Serial.println("ALERT! Motion AND door open.");

  } else {
    // --- Alarm Inactive ---
    
    // Ensure both the LED and the buzzer are off
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    
    // Reset the timing variables for next time
    ledState = LOW;
    buzzerState = LOW;
    previousLedMillis = millis();
    previousBuzzerMillis = millis();
  }
}