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

  BLECharacteristic heartRate = peripheral.characteristic("2A37");

  if (heartRate){
    if (heartRate.canSubscribe()) {
      heartRate.subscribe(notificationCallback);
      Serial.println("Subscribed to Heart Rate readout");
    } else {
      Serial.println("Can not subscribe");
    }
  } else {
    Serial.println("Heart Rate Characteristic not found");
  }

}

void loop() {
  // Check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

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

      // Discover peripheral services and characteristics
      if (peripheral.discoverAttributes()) {
        Serial.println("Attributes discovered");
        // Iterate through services and characteristics
        for (int i = 0; i < peripheral.serviceCount(); i++) {
          BLEService service = peripheral.service(i);
          Serial.print("Service UUID: ");
          Serial.println(service.uuid());

          for (int j = 0; j < service.characteristicCount(); j++) {
            BLECharacteristic characteristic = service.characteristic(j);
            Serial.print("  Characteristic UUID: ");
            Serial.println(characteristic.uuid());
          }
        }
      } else {
        Serial.println("Attribute discovery failed");
        peripheral.disconnect();
      }


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


