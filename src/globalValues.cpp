#include "globalValues.hpp"

namespace GlobalValues {
    typedef struct {
        std::bitset<6> state;
        int minTime;
        int maxTime;
    } TrafficLightState;

    TrafficLightState states[QNT_DEFAULT_STATES], nightModeStates[QNT_NIGHT_MODE_STATES], emergencyModeState;
    bool inoutNightMode = false, inoutEmergencyMode = false;
    bool pedestrianButton1Pressed = false, pedestrianButton2Pressed = false;
    bool passageSensorPressed = false;
}