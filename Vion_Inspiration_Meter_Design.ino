////////////////////////////
/// CUSTOM HEADERS ///

#include "variables.h"

void setup()
{
    Serial.begin(9600);
    //////////////////////////////////
    ////////CONTINUTY TEST///////////
    pinMode(continuity_probe_1, INPUT);  // initialize pin as an input
    pinMode(continuity_buzzer, OUTPUT);  // initialize the buzzer as an output
    pinMode(continuity_probe_2, OUTPUT); // initialize the buzzer as an output
    digitalWrite(continuity_probe_2, HIGH);
}

void loop()
{

    buzzer_value = digitalRead(continuity_probe_1); // check the pin status
    Serial.println(buzzer_value);

    (buzzer_value == 1) ? digitalWrite(continuity_buzzer, HIGH) : digitalWrite(continuity_buzzer, LOW);
}

//////////////////////////////////
////////CONTINUTY TEST///////////