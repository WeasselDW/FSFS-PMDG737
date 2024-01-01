# Arduino and PMDG 737 Link

## Overview

Elevate your flight simulation experience by establishing a seamless communication link between an Arduino and the PMDG 737 aircraft in Microsoft Flight Simulator 2020. This project aims to enhance the interaction and data exchange between the physical Arduino device and the virtual cockpit, providing a more immersive and realistic simulation.

## Features

- **Bi-directional Communication:** Enable robust communication between Arduino and PMDG 737, facilitating data exchange in both directions.
- **Custom Commands:** Define and implement personalized commands to take control of specific features within the aircraft.
- **Real-time Interaction:** Experience real-time interaction with the aircraft through external hardware connected to the Arduino.

## Important Notes

### 1. SDK Integration
- Utilize the `PMDG_NG3_SDK.h` from the PMDG installation directory's SDK folder to identify switches and events available in the PMDG SDK. The SDK folder is typically located within the PMDG installation directory in your Microsoft Flight Simulator 2020 setup.

### 2. Arduino Code and Serial Communication
- The Arduino code is not included in this repository. Create your own Arduino code to interact with the PMDG 737 and establish serial communication between the Arduino and your computer. Customize the Arduino code based on your hardware and specific requirements.

### 3. Barebones Functionality
- This project provides only "Barebones" functions to establish a link between the Arduino and the PMDG 737. It serves as a starting point for further development. Feel free to expand upon the existing functionality by adding more features and interactions according to your needs.

## Requirements

- Arduino boards compatible with the Arduino IDE and equipped for serial interfacing.
- PMDG 737 add-on for Microsoft Flight Simulator 2020.

## Setup

1. **Hardware Connection:**
   - Connect your Arduino to the computer via USB.
   - Ensure the correct COM port is selected in the Arduino IDE.

2. **Arduino Code:**
   - Upload the provided Arduino sketch to your Arduino board using the Arduino IDE.

3. **Serial Communication:**
   - Utilize the provided C++ program on your computer to establish serial communication with the Arduino.
   - Update the COM port in the C++ program to match the Arduino's COM port.

4. **Flight Simulator Configuration:**
   - Start Microsoft Flight Simulator 2020 and load the PMDG 737 aircraft.
   - Ensure that the simulator is running in the background.

5. **Run the C++ Program:**
   - Compile and run the C++ program on your computer.

## Usage

- Once the setup is complete, unleash commands from the Arduino to control specific features of the PMDG 737 aircraft.
- Monitor the C++ program console for messages and feedback from the Arduino and the flight simulator.

## Important Functions

### Arduino Communication

#### `Arduino->ReadString()`

- **Description:**
  - Reads a string from the Arduino through serial communication.

- **Usage:**
  ```cpp
  // Example Usage
  std::string receivedData = Arduino->ReadString();
  ```
#### `Arduino->WriteString(const std::wstring& data)`

- **Description:**
  - Sends a string to the Arduino through serial communication.

- **Parameters:**
  - `data`: The string data to be sent.

- **Usage:**
  ```cpp
  // Example Usage
  Arduino->WriteString("YourDataToSend");
   ```

### Simulator Data Access

#### `sim->data`

- **Description:**
  - Provides access to the data structure containing information from the simulator (PMDG 737).

- **Usage:**
  ```cpp
  // Example Usage
  if (sim->data) {
      // Access simulator data fields
      if (sim->data->CDU_annunEXEC[0]) {
          // Implement your logic based on simulator data
      }
  }
   ```
  ## Simulator Button Press Function

### `Sim::pressBtn(int btn)`

- **Description:**
  - Simulates a button press in the simulator by updating client data using SimConnect.

- **Parameters:**
  - `btn`: An integer representing the button ID to be pressed.

- **Example Usage:**
  ```cpp
  // Example usage to simulate a button press for button ID 123
  sim->pressBtn(123);
Note: This function is a part of the larger codebase that communicates with Microsoft Flight Simulator using SimConnect. Ensure proper initialization of the SimConnect connection (hSimConnect) and inclusion of relevant headers for PMDG 737NG SDK.
## Contributing

Contributions are welcome! If you have suggestions, improvements, or additional features, feel free to fork the repository and submit a pull request.

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).

## Acknowledgments

- Thanks to [PMDG](https://www.pmdg.com/) for providing a comprehensive SDK for interfacing with their aircraft.
- The Arduino community for valuable resources and libraries.

## Disclaimer

This project is developed independently and is not affiliated with PMDG, Microsoft, or the Arduino project.

