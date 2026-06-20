# Smart-Home-Automation-System-with-Voice-Control-and-Manual-Using-Arduino-Uno

Objective

This project presents the design and implementation of a Smart Home Automation System using Arduino UNO that integrates appliance control, security, and environmental monitoring. A 4×4 keypad and servo motor are used to create a password-protected door lock mechanism, ensuring restricted access. Household appliances such as a DC fan and DC light are controlled through a two-channel relay module, which supports three modes of operation: manual push buttons, Bluetooth mobile application, and voice/serial commands. A DHT11 sensor continuously monitors the temperature and humidity, displaying real-time data on a 16×2 I2C LCD. If the temperature exceeds a predefined threshold (33°C), the system triggers warning messages on the LCD and sends alerts via Serial Monitor and Bluetooth, enhancing safety. The proposed system demonstrates a low-cost, multifunctional, and reliable automation solution, suitable for smart home applications. Future improvements may include IoT-based remote monitoring, cloud integration, and additional sensor-based security features.

____________________________________________________________________________________________________________________________

Introduction

Home automation integrates sensors, actuators, microcontrollers, and communication modules to provide control, monitoring, and security in residential or industrial applications.

In this project:

1. Arduino UNO acts as the central controller.
2. 4x4 Keypad and Servo Motor provide door security, allowing only authorized users (password entry) to unlock the door.
3. Two-channel relay module controls the DC fan and light, allowing manual (push buttons), Bluetooth (mobile app), or voice/serial commands to operate appliances.
4. DHT11 sensor monitors room temperature and humidity, displayed on a 16×2 I2C LCD.
5. A temperature threshold is implemented: if temperature exceeds 33°C, the system displays a warning message and sends alerts via Serial Monitor and Bluetooth, improving safety.

This system demonstrates integration of security, environmental monitoring, and automated control for smart homes.

____________________________________________________________________________________________________________________________

Equipments:

1. DC Fan (12V)	
2. DC Light (12V)
3. 4x4 Keypad	
4. Servo Motor	
5. DHT11 Humidity & Temperature Sensor	
6. Two-Channel Relay Module	
7. I2C LCD (16×2)	
8. HC-05 Bluetooth Module	
9. Arduino UNO	
10. Push Buttons	
11. 2kΩ Resistors	
12. 12V AC-DC Adapter	
13. 5V AC-DC Adapter	
14. Jumper Wires
15. Breadboard	

____________________________________________________________________________________________________________________________

Flowchart

<img width="512" height="951" alt="Flowchart" src="https://github.com/user-attachments/assets/74696ba3-97fa-4c9a-b2bb-8bc7a6c75b62" />
____________________________________________________________________________________________________________________________


Pin Diagram

<img width="429" height="504" alt="Pin Diagram" src="https://github.com/user-attachments/assets/80bb7eba-c36e-4b36-9a74-26da8c57071a" />

____________________________________________________________________________________________________________________________


Connection :

<img width="975" height="527" alt="image" src="https://github.com/user-attachments/assets/8ea538eb-4141-4d07-9a92-9909101d2af7" />

<img width="975" height="635" alt="image" src="https://github.com/user-attachments/assets/48fa2605-a330-4cfe-83aa-d6460dc9ed0b" />

____________________________________________________________________________________________________________________________


Procedure

Step 1: System Setup and Power Supply
             1. Place the Arduino UNO on the breadboard or work area.
             2. Connect the 5V and GND pins of Arduino to the power rails of the breadboard.
             3. Connect the 12V AC-DC adapter to the relay module, DC fan, and DC light circuits for powering the loads.
             4. Ensure the 5V AC-DC adapter powers the Arduino, I2C LCD, DHT11 sensor, and keypad.
       
Step 2: Connecting Input Devices
             1. Push Buttons:
                   a. Connect PB1 to Arduino pin D2 and PB2 to D3.
                   b. Connect a 2kΩ pull-up resistor to each button or use Arduino’s INPUT_PULLUP mode.
             2. 4x4 Keypad:
                   a. Connect rows to analog pins: A0, A1, A2, A3.
                   b. Connect columns to digital pins: D6, D7, D8, D13.
             3. DHT11 Sensor:
                   a. Connect VCC to 5V, GND to GND, and data pin to D12.
Step 3: Connecting Output Devices
             1. Relay Module:
                   a. Relay1 controls the DC light, connected to D4 of Arduino.
                   b. Relay2 controls the DC fan, connected to D5 of Arduino.
             2. Servo Motor:
                   a. Connect signal pin of the servo to D9.
                   b. VCC → 5V, GND → GND.
             3. I2C LCD:
                   a. Connect SDA to A4, SCL to A5, VCC → 5V, GND → GND.
             4. HC-05 Bluetooth Module:
                   a. RX → Arduino D10, TX → Arduino D11 through a voltage divider (to reduce 5V TX to 3.3V for HC-05).VCC → 5V, GND → GND.
Step 4: Arduino Initialization
             1. Power on the Arduino.
             2. Upload the Arduino code provided for the system.
             3. Arduino initializes:
                   a. LCD displays “SMART HOME – Group 2” for 2 seconds.
                   b. Servo motor moves to locked position (0°).
                   c. System waits for password entry.
Step 5: Door Security Operation
             1. Enter the password (default: 1234) using the keypad.
             2. Press # to confirm.
                   a. If correct:
                            Servo rotates to 90°, unlocking the door.
                            LCD displays “Door Open – Welcome”.
                            Bluetooth app receives a message “Door Open – Welcome”.
                   b. If incorrect:
                            LCD displays “Wrong Password!” for 2 seconds.
                            Prompt to re-enter the password.
Step 6: Manual Control of Loads
1.	Push Button Control:
o	Press PB1 → toggle DC light (Relay1 ON/OFF).
o	Press PB2 → toggle DC fan (Relay2 ON/OFF).
o	LCD updates Relay1 and Relay2 status.
o	Status is sent to Serial Monitor and Bluetooth.
Step 7: Remote Control via Bluetooth / Voice
1.	Send commands from a mobile app connected via HC-05 or via Serial Monitor:
o	Bluetooth Commands:
	1 → Light ON
	2 → Light OFF
	3 → Fan ON
	4 → Fan OFF
o	Voice/Serial Commands:
	"relay1 on/off" → Light
	"relay2 on/off" → Fan
2.	Arduino reads the command, updates relay states, and refreshes the LCD.
Step 8: Environmental Monitoring
1.	The DHT11 sensor continuously reads temperature and humidity.
2.	Arduino calculates temperature in °C and humidity in %.
3.	LCD alternates every 2 seconds between:
o	Relay Status Page → Shows ON/OFF state of light and fan.
o	Temperature & Humidity Page → Shows real-time sensor readings.
Step 9: Temperature Warning System
1.	Arduino checks the temperature from DHT11.
2.	If temperature > 33°C:
o	LCD displays “WARNING!!! TEMP > 33C”.
o	Serial Monitor prints “ALERT: TEMPERATURE HIGH!”.
o	Bluetooth sends the same alert to the mobile app.
3.	This warning repeats until temperature falls below the threshold.
Step 10: Continuous Operation
1.	After initialization and successful door unlock, the system continuously monitors:
o	Push button states
o	Bluetooth commands
o	Voice/serial commands
o	Temperature & humidity
2.	LCD updates every 2 seconds, providing real-time feedback.
3.	The system loops indefinitely, maintaining automation, monitoring, and safety

____________________________________________________________________________________________________________________________

Output
1.	The LCD alternates between relay status and temperature/humidity.
2.	Push buttons, Bluetooth commands, and voice commands successfully turn appliances ON/OFF.
3.	Correct password entry unlocks the door (servo rotates).
4.	When temperature > 33°C, the LCD shows:
       1.	WARNING!!!
       2.	TEMP > 33C
       3.	Serial Monitor and Bluetooth app also receive alerts.
____________________________________________________________________________________________________________________________

Discussion

The system demonstrates a fully functional smart home automation setup that integrates security, environmental monitoring, and automated control. It offers several advantages, including multi-mode appliance control through manual operation, Bluetooth, and voice commands, as well as real-time temperature and humidity monitoring. Temperature-based safety alerts help prevent overheating, and a password-protected door adds an extra layer of security to the home. However, the system also has some limitations. For instance, the temperature threshold is fixed, which can be improved in the future by introducing adjustable limits. Additional actuators such as fans, alarms, or air conditioning units could also be integrated to provide automatic responses to high temperatures. Extending IoT connectivity would allow remote monitoring and control via the internet, while adding extra sensors like smoke and motion detectors could further enhance the overall safety and reliability of the smart home.


____________________________________________________________________________________________________________________________







