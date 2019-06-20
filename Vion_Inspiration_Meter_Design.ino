////////////////////////////
/// CUSTOM HEADERS ///

#include "variables.h"
#include "oled_definitions.h"


void setup()
{
    Serial.begin(9600);
    //////////////////////////////////
    ////////CONTINUTY TEST///////////
    pinMode(continuity_probe_1, INPUT);  // initialize pin as an input
    pinMode(continuity_buzzer, OUTPUT);  // initialize the buzzer as an output
    pinMode(continuity_probe_2, OUTPUT); // initialize the buzzer as an output
    digitalWrite(continuity_probe_2, HIGH);

    //////////////////////////////////
    //////// VOLTAGE DC /////////////

     


    /////////////////////////////
    ///////OPTIONS BUTTON////////
    pinMode(selection_btn, INPUT_PULLUP); // initialize pin as an input


     /////////////////////////////
    /////OLED INITIALIZATION//////

    // initialize and clear display
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();
    display.display();

    // display a line of text
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5,0);
    display.print("Vion Meter");
    display.setCursor(49,10);
    display.print("Welcome !");
    display.setCursor(23,20);
    display.print("Select to measure");
    // update display with all of the above graphics
    display.display();
}

void loop()
{
   button_states();
   button_selection_count();
   change_measurement_param();

//   measure_vdc();
}




//////////////////////////////////
////////CONTINUTY TEST///////////

void continuty_test() {
buzzer_value = digitalRead(continuity_probe_1); // check the pin status
 Serial.println(buzzer_value); //Serial.println(buzzer_value);                                     
(buzzer_value == 1) ? digitalWrite(continuity_buzzer, HIGH) : digitalWrite(continuity_buzzer, LOW);
}


//////////////////////////////////
////////FUNCTIONS///////////

void button_states()
{
    selection_btn_value = digitalRead(selection_btn);
//   Serial.println(selection_btn_value);

}

int button_selection_count()
{
  button_states();
  
  if(selection_btn_value != last_selection_btn_value){
    if(selection_btn_value == 1) {
      button_press = true;
      selection_count++;
      Serial.println(selection_count);
    }
    delay(50);
  }
    last_selection_btn_value = selection_btn_value;
}

void change_measurement_param(){
    button_selection_count();
    if(selection_count == 1){
      // Voltage Measurement
      display_oled_voltage_dc();
        Serial.println("Voltage");
    }
    if(selection_count == 2){
      // Voltage Measurement
      display_oled_voltage_ac();
        Serial.println("Voltage");
    }
    if(selection_count == 3){
      // Current Measurement
      display_oled_current();
        Serial.println("Current");
    }
    if(selection_count == 4){
      // Continuity test
      display_oled_continuity();
        Serial.println("Continuity");
    }
    if(selection_count == 5){
      //Resistnace Measurement
         display_oled_resistance();
        Serial.println("Resistance");
    }

    if(selection_count > 5){
      // Reset Count
        selection_count = 1;
        display_oled_voltage_dc();
    }
}


void display_oled_voltage_dc(){
 
  // display a line of text
  display.clearDisplay();
  display.setCursor(5,0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75,0);
  display.print("V DC");
  measure_vdc();
// update display with all of the above
  display.display();

}
void display_oled_voltage_ac(){
 
  // display a line of text
  display.clearDisplay();
  display.setCursor(5,0);
  display.setTextSize(1);
  display.print("Vion Meter");
  display.setTextColor(WHITE);
  display.setCursor(75,0);
  display.print("V AC");

// update display with all of the above
  display.display();

}


void display_oled_current(){
 
  // display a line of text
  display.clearDisplay();
    display.setCursor(5,0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75,0);
  display.print("A");

// update display with all of the above
  display.display();

}



void display_oled_resistance(){
 
  // display a line of text
  display.clearDisplay();
    display.setCursor(5,0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75,0);
  display.print("Ohms");

// update display with all of the above
  display.display();

}


void display_oled_continuity(){
 
  // display a line of text
  display.clearDisplay();
    display.setCursor(5,0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75,0);
  display.print("Conti");

// update display with all of the above
  display.display();

}


    //////////////////////////////////
    //////// VOLTAGE DC /////////////

void measure_vdc(){
  dc_raw_value = analogRead(dc_measurement);
  mapped_raw_value = map(dc_raw_value, 0, 1023, 0, 255);
  Serial.println(mapped_raw_value );
  
  dc_voltage_out = (mapped_raw_value * (float)reference_voltage_val) / reference_decimal_val;
  Serial.println(dc_voltage_out);
  
  resistance_ratio = resistor_R2 / (resistor_R1 + resistor_R2);

  dc_actual_voltage = dc_voltage_out / resistance_ratio;
  Serial.println(dc_actual_voltage);
//   delay(300);


  display.clearDisplay();
  display.setCursor(5,0);
  display.setTextSize(1);
  display.print("Vion Meter");
  display.setTextColor(WHITE);
  display.setCursor(75,0);
  display.print("V DC");
  display.setTextSize(2);
  display.setCursor(40,15);
  display.print(dc_actual_voltage);
  display.print("V");



}



