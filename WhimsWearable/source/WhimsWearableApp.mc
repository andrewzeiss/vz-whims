import Toybox.Application;
import Toybox.Lang;
import Toybox.WatchUi;

class WhimsWearableApp extends Application.AppBase {

    function initialize() {
        AppBase.initialize();
    }

    // onStart() is called on application start up
    function onStart(state as Dictionary?) as Void {
    }

    // onStop() is called when your application is exiting
    function onStop(state as Dictionary?) as Void {
    }

    // Return the initial view of your application here
    function getInitialView() as [Views] or [Views, InputDelegates] {
        // utlizes mvc patterm, App is the controller, View is the view, and Delegate is the model
        return [ new WhimsWearableView(), new WhimsWearableDelegate() ];
    }

}

function getApp() as WhimsWearableApp {
    return Application.getApp() as WhimsWearableApp;
}