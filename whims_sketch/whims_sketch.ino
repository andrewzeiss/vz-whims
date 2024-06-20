#include <ArduinoBLE.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  Serial.println("BLE Central - Scanning for peripherals...");
  BLE.scan();

}

void loop() {
  // Check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();


  BLECharacteristic heartRate = peripheral.characteristic("2A37");

  if (peripheral) {
    // Print the discovered peripheral address
    Serial.print("Discovered peripheral: ");
    Serial.println(peripheral.address());

    // Attempt to connect to the peripheral
    //Specific to my heart rate monitor
    if (peripheral.localName() == "HRMPro+:192052" || peripheral.address() == "e8:5c:11:c3:66:0b") {
      Serial.print("Connecting to peripheral: ");
      Serial.println(peripheral.address());

      // Stop scanning while connecting
      BLE.stopScan();

      if (peripheral.connect()) {
        Serial.println("Connected to peripheral");
      } else {
        Serial.println("Failed to connect");
        BLE.scan(); // Resume scanning if connection fails
        return;
      }
     
      Serial.println("Subscribing to heart rate monitor... ");
      if (!heartRate) {
        Serial.println("no heart rate characteristic found");
        peripheral.disconnect();
        return;
      } else if (!heartRate.canSubscribe()) {
        Serial.println("Heart rate is not subscribable");
        peripheral.disconnect();
        return;
      } else if (!heartRate.subscribe()) {
        Serial.println("Subscription failed");
        peripheral.disconnect();
        return;
      }

      notificationCallback(heartRate);

      // Resume scanning
      BLE.scan();
    }
  }
}

void notificationCallback(BLECharacteristic& characteristic) {
  Serial.print("Received Heart Rate Measurement Notification: ");

  String value = characteristic.value();

  Serial.println(value);
}


