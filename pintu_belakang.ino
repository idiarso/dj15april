// Pin Definitions
const int relayPin = D3;     // Pin for the relay control (GPIO0)

// Variables
unsigned long lastTriggerTime = 0; // Timestamp of the last trigger
const unsigned long cooldownPeriod = 5000; // 5 seconds cooldown period

void setup() {
  // Initialize Serial communication at 9600 baud rate
  Serial.begin(9600);

  // Configure pin modes
  pinMode(relayPin, OUTPUT); // Relay as output

  // Ensure the relay is initially off
  digitalWrite(relayPin, LOW);
}

void loop() {
  // Check if data is available on the serial port
  if (Serial.available() > 0) {
    // Read the incoming command
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove any extra whitespace or newline characters

    // Process the command
    if (command == "ON") {
      // Check if the cooldown period has passed
      unsigned long currentTime = millis();
      if ((currentTime - lastTriggerTime) >= cooldownPeriod) {
        // Step 1: Turn on the relay
        digitalWrite(relayPin, HIGH);

        // Step 2: Send a message to indicate the relay is on
        Serial.println("Relay ON");

        // Step 3: Turn off the relay after 1 second
        delay(1000); // Keep the relay on for 1 second
        digitalWrite(relayPin, LOW);

        // Step 4: Update the last trigger time
        lastTriggerTime = currentTime;

        // Step 5: Send a message to indicate the relay is off
        Serial.println("Relay OFF");
      } else {
        // Cooldown period not over, send a message
        Serial.println("Cooldown active. Please wait.");
      }
    } else if (command == "OFF") {
      // Turn off the relay immediately (if needed)
      digitalWrite(relayPin, LOW);
      Serial.println("Relay OFF");
    } else {
      // Invalid command received
      Serial.println("Invalid command. Use 'ON' or 'OFF'.");
    }
  }
}

-------------------------------------------------------------||||----------------------------------------------------------------------------

  // Pin Definitions
const int relayPin = D3; // Pin for the relay control (GPIO0)

void setup() {
  // Initialize Serial communication at 115200 baud rate
  Serial.begin(115200);

  // Configure pin modes
  pinMode(relayPin, OUTPUT);

  // Ensure the relay is initially off
  digitalWrite(relayPin, LOW);

  // Print a startup message
  Serial.println("Relay Control Ready. Send 'ON' to activate or 'OFF' to deactivate.");
}

void loop() {
  // Check if data is available on the serial port
  if (Serial.available() > 0) {
    // Read the incoming command
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove any extra whitespace or newline characters

    // Process the command
    if (command == "ON") {
      // Turn on the relay
      digitalWrite(relayPin, HIGH);
      Serial.println("Relay ON");
    } else if (command == "OFF") {
      // Turn off the relay
      digitalWrite(relayPin, LOW);
      Serial.println("Relay OFF");
    } else {
      // Invalid command received
      Serial.println("Invalid command. Use 'ON' or 'OFF'.");
    }
  }
}
