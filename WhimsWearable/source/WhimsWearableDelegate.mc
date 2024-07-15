import Toybox.Lang;
import Toybox.WatchUi;

class WhimsWearableDelegate extends WatchUi.BehaviorDelegate {

    function initialize() {
        BehaviorDelegate.initialize();
    }

    function onMenu() as Boolean {
        WatchUi.pushView(new Rez.Menus.MainMenu(), new WhimsWearableMenuDelegate(), WatchUi.SLIDE_UP);
        return true;
    }

}