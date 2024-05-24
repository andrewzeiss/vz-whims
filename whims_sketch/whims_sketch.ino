#define vibePin1 2
#define vibePin1 3
#define vibePin1 4
#define vibePin1 5
#define vibePin1 6
#include <ArduinoBLE.h>

char cmd;
string deviceName = "";

int vibePins[5] = { 2, 3, 4, 5, 6 };
int i, j, p, pos;
bool approved, questionAnswered = false, readyToContinueToNext = false;

int num_of_vibes = sizeof(vibePins) / sizeof(vibePins[0]);  //stores the # of items in servoArray
unsigned long runTime = 15000; //5000
unsigned long vibeRunTime = runTime / sizeof(vibePins);
unsigned long delayTime = runTime / 10, halfDelay = delayTime / 2;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  //begin initialization
  if(!BLE.begin()) {
    Serial.println("Bluetooth failed to start");

    while (1);
  }

  Serial.println("BLE Central scan");

  // Serial.println("Vibration Discrete Test");
  // for (p = 0; p <= num_of_vibes - 1; p++) {
  //   pinMode(vibePins[j], OUTPUT);
  // }

}

void loop() {

  //check for peripherals
  BLEDevice peripheral = BLE.scanForName("Venu Sq 2");

  if (peripheral) {
    //discovered a peripheral
    Serial.println("Discovered a peripheral");
    Serial.println("-------");

    //print address
    Serial.print("Address: ");
    Serial.println(peripheral.address());

    //print the local name if present
    if (peripheral.hasLocalName()){
      Serial.print("Local Name: ");
      Serial.println(peripheral.localName());
    }

    //print the advertised service UUIDs, if present
    if (peripheral.hasAdvertisedServiceUuid()) {
      Serial.print("Service UUIDs: ");
      for (int i = 0; i < peripheral.advertisedServiceUuidCount()); i++ {
        Serial.print(peripheral.advertisedServiceUuid(i));
      }
    }

    Serial.println();

    BLE.stopScan();

    monitorHR(peripheral);

    BLE.scanForName("Venu Sq 2");
  }
}


void monitorHR(peripheral) {

  // Conenct to the peripheral
  Serial.println("Connecting ...");

  if (peripheral.connect()) {
    Serial.println("Connected!");
  } else {
    Serial.println("Failed to connect :(");
  }

  //need the service Uuid and characteristic for heart rate broadcasting, then put it here

  // Discover the service
  if (peripheral.discoverService(serviceUuid)) {
    Serial.println("Service discovered!");

    // Discover the characteristic
    targetCharacteristic = peripheral.characteristic(serviceUuid, characteristicUuid);
    if (targetCharacteristic) {
      Serial.println("Characteristic discovered!");

      // Read the value of the characteristic
      if (targetCharacteristic.canRead()) {
        byte value[20];  // Adjust size as needed
        int length = targetCharacteristic.readValue(value, sizeof(value));

        Serial.print("Characteristic value: "); //set this to some variable
        for (int i = 0; i < length; i++) {
          Serial.print((char)value[i]);
        }
        Serial.println();
      } else {
        Serial.println("Characteristic is not readable!");
      }
    } else {
      Serial.println("Characteristic not found!");
    }
  } else {
    Serial.println("Service not found!");
  }

  //if some variable representing hr is over some certain threshhold, call singleCycle

}


void singleCycle() {
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

// void halfCycle() {
//   Serial.println(num_of_vibes);
//   for (i = 0; i <= num_of_vibes - 1; i++) {
//     Serial.println(i + 1);
//     if (i == 0) {
//       digitalWrite(vibePins[i], HIGH);
//       delay(delayTime);
//     } else {
//       digitalWrite(vibePins[i - 1], LOW);
//       digitalWrite(vibePins[i], HIGH);
//       delay(delayTime);
//     }
//   }
//   for (p = 0; p <= num_of_vibes - 1; p++) {
//     digitalWrite(vibePins[p], LOW);
//   }
//   GetApproval();
//   for (i = num_of_vibes - 1; i >= 0; i--) {
//     Serial.println(i + 1);
//     digitalWrite(vibePins[i + 1], LOW);
//     digitalWrite(vibePins[i], HIGH);
//     delay(delayTime);
//   }
//   for (p = 0; p <= num_of_vibes - 1; p++) {
//     digitalWrite(vibePins[p], LOW);
//   }
// }

