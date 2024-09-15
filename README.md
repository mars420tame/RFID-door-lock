# RFID Door Lock System

## How it Works
When the RFID door lock system is powered on, the servo motor moves the lock to the "open" position by default. The LCD displays “Welcome! Put your card.” When an RFID card is brought near the RFID reader, it scans the card, and the LCD shows “Scanning.”

- If the scanned RFID tag matches the stored UID, the servo motor will:
   - **Lock the door**: If the door is currently unlocked, the servo motor pushes the lock forward, and the LCD displays “Door is locked.” The red LED will light up.
   - **Unlock the door**: If the door is currently locked, the servo motor pulls the lock back, and the LCD displays “Door is open.” The green LED will light up.

- If an incorrect RFID tag is scanned, the LCD displays “Wrong card!” and the red LED blinks continuously. A buzzer will sound until the button is pressed to reset the system.

## Components Required:
- **Arduino UNO board x 1**
- **RFID module x 1**
- **LCD (16x2) x 1**
- **I2C module x 1**
- **Servo motor x 1**
- **Door lock mechanism x 1**
- **Button x 1**
- **Red and Green LEDs x 1 each**
- **RGB LED x 1**
- **Buzzer x 1**
- **Jumper wires**
- **Foamboard or suitable housing material**
- **Iron stick or lock support**
