import Toybox.Lang;
import Toybox.WatchUi;
import Toybox.System;
import Toybox.BluetoothLowEnergy;

class WhimsWearableDelegate extends WatchUi.BehaviorDelegate {

    var onSignal = new [1];

    function initialize() {
        BehaviorDelegate.initialize();
    }

    function onKey(key) {
        // key 4 represents the top button on the watch
        if (key.getKey() == 4) {
            // Bluetooth connectivity here, unsure how to start scan. Once started, the logic should be correct
            System.println("Connecting to Arduino...");
            // if (scanResult.getName == "Arduino") {
            //    pairDevice(scanResult);
            //    System.println("Connected to Arduino!");}

            return true;
        }
        return false;
    }

    // write the byte array to the arduino when the stress threshold is met, unsure the complete correct synta
    function onThreshold(){
        //requestWrite
        // onCharacteristicWrite(onSignal)
    }

}