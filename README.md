# ME104_LoadScale

# Arduino Digital Scale with HX711

This Arduino project implements a digital scale using an HX711 load cell amplifier. It displays the weight on the Serial Monitor and supports taring the scale and switching between grams and ounces.

This code is an application of a load cell and HX711, using pre-set calibration values. For initial setup, you will need to calibrate your specific load cell and HX711 module to determine the correct `loadCellOffset` and `loadCellScale` values. The original library by Rob Tillaart (linked below) may contain calibration-specific sketches or instructions.

## Features

* Reads weight from a load cell via the HX711 amplifier.
* Displays weight in grams or ounces on the Serial Monitor.
* Tare functionality using a dedicated button.
* Unit switching (grams/ounces) using a dedicated button.
* Uses user-defined calibration values for offset and scale.

## Hardware Requirements

* Arduino compatible microcontroller (e.g., Arduino Uno, Nano, ESP32, etc.)
* HX711 load cell amplifier module
* Load cell (e.g., a bathroom scale load cell)
* 2 x Push buttons
* Connecting wires
* 10k Ohm resistors (optional, if not using `INPUT_PULLUP` for buttons, but the code uses `INPUT_PULLUP`)

## Software Requirements

* [Arduino IDE](https://www.arduino.cc/en/software)
* **HX711 Library by Rob Tillaart**:
    * You can install this library through the Arduino Library Manager. Search for "HX711" by Rob Tillaart.
    * Alternatively, find it on GitHub: [https://github.com/RobTillaart/HX711](https://github.com/RobTillaart/HX711)

## Pin Configuration

Make sure your hardware is connected according to these pin definitions in the sketch. You can modify these in the code if needed.

* HX711 Data Pin (`dataPin`): `4`
* HX711 Clock Pin (`clockPin`): `5`
* Tare Button Pin (`tareButtonPin`): `2` (connected to GND on the other side, uses `INPUT_PULLUP`)
* Unit Switch Button Pin (`unitButtonPin`): `3` (connected to GND on the other side, uses `INPUT_PULLUP`)

## Setup and Installation

1.  **Connect Hardware**:
    * Connect the load cell to the HX711 module.
    * Connect the HX711 module to the Arduino:
        * HX711 VCC to Arduino 5V (or 3.3V, check module specs)
        * HX711 GND to Arduino GND
        * HX711 DT to `dataPin` (default: 4)
        * HX711 SCK to `clockPin` (default: 5)
    * Connect the Tare button: one pin to `tareButtonPin` (default: 2) and the other pin to GND.
    * Connect the Unit Switch button: one pin to `unitButtonPin` (default: 3) and the other pin to GND.
2.  **Install Library**:
    * Open the Arduino IDE.
    * Go to Sketch > Include Library > Manage Libraries...
    * Search for "HX711" and install the library by Rob Tillaart.
3.  **Load the Sketch**:
    * Open the `HX_application.ino` (or your renamed sketch file) in the Arduino IDE.
4.  **Calibrate Your Scale (IMPORTANT!)**:
    * The provided `loadCellOffset` and `loadCellScale` values are placeholders:
        ```cpp
        long loadCellOffset = -25820;    // Replace with your determined offset
        float loadCellScale = -22.3071f; // Replace with your determined scale factor
        ```
    * You **MUST** determine these values for your specific load cell and HX711 module.
    * **To calibrate:**
        1.  You might need a separate calibration sketch (often provided with HX711 libraries, or you can adapt this one).
        2.  **Offset (Tare Value)**: With no weight on the scale, read the raw value from `myScale.read_average()`. This is your approximate offset. You can use the tare function initially or refine this value.
        3.  **Scale Factor**:
            * After setting the offset (or taring), place a known weight (e.g., 1000 grams) on the scale.
            * Read the raw value from `myScale.read_average()` again. Let this be `rawValueWithKnownWeight`.
            * The scale factor is then roughly `(rawValueWithKnownWeight - offsetValue) / knownWeightInGrams`.
            * Adjust this value until `myScale.get_units()` reports the correct known weight. You might need to invert the sign of the scale factor depending on your setup.
    * Update the `loadCellOffset` and `loadCellScale` variables in the sketch with your calibrated values.
5.  **Upload to Arduino**:
    * Select your board and port in the Arduino IDE.
    * Click the "Upload" button.

## Usage

1.  After uploading the sketch, open the Serial Monitor (Tools > Serial Monitor).
2.  Set the baud rate to `115200`.
3.  The scale will initialize and indicate it's ready.
4.  **Tare the Scale**:
    * Ensure no weight is on the scale.
    * Press the Tare button. The Serial Monitor will indicate that the scale is being tared.
5.  **Switch Units**:
    * Press the Unit button to toggle the display between grams (g) and ounces (oz).
6.  **Measure Weight**:
    * Place an object on the scale.
    * The weight will be displayed on the Serial Monitor.

## Code Author and Origin

* **Original HX711 Library Author**: Rob Tillaart
* **Library URL**: [https://github.com/RobTillaart/HX711](https://github.com/RobTillaart/HX711)
* This sketch (`HX_application.ino`) is an application example demonstrating the use of the HX711 library for a functional bathroom scale.


<small> *Google, "Assistance in generating README.md file content, based on user prompt to create documentation for provided Arduino code," Gemini Large Language Model. Accessed: May 13, 2025.*
---
