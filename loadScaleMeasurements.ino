//
//    FILE: HX_calibration.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 calibration finder for offset and scale  // User's original comment, though this version is the application, not the finder
//     URL: https://github.com/RobTillaart/HX711


#include "HX711.h"

HX711 myScale;

//  adjust pins if needed.
uint8_t dataPin = 4;
uint8_t clockPin = 5;

const int tareButtonPin = 2;
const int unitButtonPin = 3;

int tareButtonState = 0;
int lastTareButtonState = 0;
int unitButtonState = 0;
int lastUnitButtonState = 0;

bool useOunces = false;

// Conversion factor
const float GRAMS_TO_OUNCES = 0.035274;

// These are the values you would update after calibration
long loadCellOffset = -25820;      // Replace with your determined offset
float loadCellScale = -22.3071f;    // Replace with your determined scale factor

void setup()
{
  Serial.begin(115200);
  Serial.println("Bathroom Scale Initializing...");
  Serial.print("HX711_LIB_VERSION: ");
  Serial.println(HX711_LIB_VERSION);
  Serial.println();

  myScale.begin(dataPin, clockPin);

  // Set the calibration values (REPLACE WITH YOURS!)
  myScale.set_offset(loadCellOffset);
  myScale.set_scale(loadCellScale);

  // Initialize button pins as inputs with internal pull-up resistors
  pinMode(tareButtonPin, INPUT_PULLUP);
  pinMode(unitButtonPin, INPUT_PULLUP);

  Serial.println("Scale ready.");
  Serial.println("Press Tare button to zero the scale.");
  Serial.println("Press Unit button to switch between grams and ounces.");

  // Perform an initial tare - you might keep this commented if set_offset is sufficient
  // myScale.tare(20); // Average 20 readings for a stable tare
  // Serial.println("Initial tare complete."); // Only print if you tare
}

void loop()
{
  // Read button states
  tareButtonState = digitalRead(tareButtonPin);
  unitButtonState = digitalRead(unitButtonPin);

  // --- Tare Button Logic ---
  // Check if the tare button is pressed (it's LOW when pressed due to INPUT_PULLUP)
  // and was not pressed in the previous loop (to detect a single press)
  if (tareButtonState == LOW && lastTareButtonState == HIGH) {
    Serial.println("Tare button pressed. Taring...");
    myScale.tare(20); // Tare the scale, average 20 readings
    Serial.println("Scale tared.");
    delay(50); // Simple debounce delay
  }
  lastTareButtonState = tareButtonState;

  // --- Unit Switch Button Logic ---
  // Check if the unit button is pressed and was not pressed in the previous loop
  if (unitButtonState == LOW && lastUnitButtonState == HIGH) {
    useOunces = !useOunces; // Toggle the unit
    if (useOunces) {
      Serial.println("Switched to Ounces.");
    } else {
      Serial.println("Switched to Grams.");
    }
    delay(50); // Simple debounce delay
  }
  lastUnitButtonState = unitButtonState;

  // --- Read and Display Weight ---
  if (myScale.is_ready()) {
    float weight = myScale.get_units(10); // Get average of 10 readings

    Serial.print("Weight: ");
    if (useOunces) { 
      float weightOunces = weight * GRAMS_TO_OUNCES;
      Serial.print(weightOunces, 2); // Print ounces with 2 decimal places
      Serial.println(" oz");
    } else {
      Serial.print(weight, 1); // Print grams with 1 decimal place
      Serial.println(" g");
    }
  } else {
    Serial.println("HX711 not found.");
  }

  delay(100); // Add a small delay to make the serial output readable
              // and to not overwhelm the HX711 with requests
}



//  -- END OF FILE --

