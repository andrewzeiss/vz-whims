#include <ArduinoBLE.h>

#define vibePin1 2
#define vibePin1 3
#define vibePin1 4
#define vibePin1 5
#define vibePin1 6

#define DEBUG true

int vibePins[5] = { 2, 3, 4, 5, 6 };
int i, j, p, pos;
bool approved, questionAnswered = false, readyToContinueToNext = false;

int num_of_vibes = sizeof(vibePins) / sizeof(vibePins[0]);  //stores the # of items in servoArray
unsigned long runTime = 15000; //5000
unsigned long vibeRunTime = runTime / sizeof(vibePins);
unsigned long delayTime = runTime / 10, halfDelay = delayTime / 2;

// These UUIDs have been randomly generated. - they must match between the Central and Peripheral devices
// Any changes you make here must be suitably made in the Python program as well

BLEService nanoService("13012F00-F8C3-4F4A-A8F4-15CD926DA146"); // BLE Service

// BLE Characteristics - custom 128-bit UUID, read and writable by central device
BLEByteCharacteristic hapticCharacteristic("0000ffe1-0000-1000-8000-00805f9b34fb", BLERead | BLEWrite);
void setup() {
    Serial.begin(9600);

        if (DEBUG) {
      while(!Serial);
    }
    
   // begin initialization
    if (!BLE.begin()) {
        Serial.println("Starting BLE failed!");
        while (1);
    }

    // set advertised local name and service UUID:
    BLE.setLocalName("Arduino Nano 33 IoT");
    BLE.setAdvertisedService(nanoService);

    // add the characteristic to the service
    nanoService.addCharacteristic(hapticCharacteristic);

    // add service
    BLE.addService(nanoService);

    // set the initial value for the characeristic:
    hapticCharacteristic.writeValue(0);

    // start advertising
    BLE.advertise();
    delay(100);
    Serial.println("WHIMS Controller is online!");
}

void loop() {
    // listen for BLE centrals to connect:
    BLEDevice central = BLE.central();

    // if a central is connected to peripheral:
    if (central) {
        Serial.print("Connected to central: ");
        // print the central's MAC address:
        Serial.println(central.address());

        // while the central is still connected to peripheral:
        while (central.connected()) {
            if (hapticCharacteristic.written()) {
                if (hapticCharacteristic.value()) {   
                    Serial.println("Haptic signal recieved!");
                    SingleCycle();
                    hapticCharacteristic.writeValue(0);
                }
            }
        }
        // when the central disconnects, print it out:
        Serial.print(F("Disconnected from central: "));
        Serial.println(central.address());
    }
}


void SingleCycle() {
  Serial.println(num_of_vibes);
  for (i = 0; i <= num_of_vibes - 1; i++) {
    Serial.println(i + 1);
    if (i == 0) {
      digitalWrite(vibePins[i], HIGH);
      delay(delayTime);
    } else {
      digitalWrite(vibePins[i - 1], LOW);
      digitalWrite(vibePins[i], HIGH);
      delay(delayTime);
    }
  }
  for (p = 0; p <= num_of_vibes - 1; p++) {
    digitalWrite(vibePins[p], LOW);
  }
  delay(delayTime);
  for (i = num_of_vibes - 1; i >= 0; i--) {
    Serial.println(i + 1);
    digitalWrite(vibePins[i + 1], LOW);
    digitalWrite(vibePins[i], HIGH);
    delay(delayTime);
  }
  for (p = 0; p <= num_of_vibes - 1; p++) {
    digitalWrite(vibePins[p], LOW);
  }
}




