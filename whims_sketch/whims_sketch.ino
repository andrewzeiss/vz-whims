#include <ArduinoBLE.h>

byte oldHR = 0;
BLECharacteristic heartRateMeasurement;

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


  BLECharacteristic heartRate = peripheral.characteristic("00002A37-0000-1000-8000-00805f9b34fb");


  //"6a4e310-667B-11e3-949a-0800200c9a66"

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
      }
      if (peripheral.discoverAttributes()) {
        Serial.println("Attributes Discovered");
/*
        int serviceCount = peripheral.serviceCount();
        for (int i = 0; i < serviceCount; i++) {
          BLEService service = peripheral.service(i);
          Serial.print("Service UUID: ");
          Serial.println(service.uuid());

          int characteristicCount = service.characteristicCount();
          for (int j = 0; j < characteristicCount; j++) {
            BLECharacteristic characteristic = service.characteristic(j);
            Serial.print("  Characteristic UUID: ");
            Serial.println(characteristic);
            Serial.print("  Properties: ");
            Serial.println(characteristic.properties());
          }
        }
      } else {
        Serial.println("Attribute discovery failed");
*/

        BLEService heartRateService = peripheral.service("180D");
        if (heartRateService) {
          heartRateMeasurement = heartRateService.characteristic("2A37");
          if (heartRateMeasurement) {
            heartRateMeasurement.subscribe();
            Serial.println("Subscribed to heart Rate measurement!!!");
          } else {
            Serial.println("Heart Rate measurement subscription failed...");
          }
        }
      }

/*
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
*/

      while (peripheral.connected()) {

        if (heartRateMeasurement.valueUpdated()) {

          byte heartRateData[2];
          heartRateMeasurement.readValue(heartRateData, 2);

          byte currentHR = heartRateData[1];

          if (oldHR != currentHR) {
            oldHR = currentHR;
            Serial.print("Heart Rate: ");
            Serial.println(currentHR);
          }
        }
      }
      // Resume scanning
      BLE.scan();
    }
  }
}


