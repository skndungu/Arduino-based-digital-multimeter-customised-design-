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

  //////////////////////////////////
  ////// RSISTANCE MEASUREMENT ////

  pinMode(microcontroller_voltage_pin, OUTPUT);
  pinMode(channel_2K_pin, INPUT);
  pinMode(channel_20K_pin, INPUT);
  pinMode(channel_200K_pin, INPUT);
  pinMode(channel_1M_pin, INPUT);

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
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setCursor(49, 10);
  display.print("Welcome !");
  display.setCursor(23, 20);
  display.print("Select to measure");
  // update display with all of the above graphics
  display.display();
}

void loop()
{
  button_states();
  button_selection_count();
  change_measurement_param();
}

//////////////////////////////////
////////CONTINUTY TEST///////////

void continuty_test()
{
  buzzer_value = digitalRead(continuity_probe_1); // check the pin status
  Serial.println(buzzer_value);                   //Serial.println(buzzer_value);
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

  if (selection_btn_value != last_selection_btn_value)
  {
    if (selection_btn_value == 1)
    {
      button_press = true;
      selection_count++;
      Serial.println(selection_count);
    }
    delay(10);
  }
  last_selection_btn_value = selection_btn_value;
}

void change_measurement_param()
{
  button_selection_count();
  measure_resistor();
  if (selection_count == 1)
  {
    // Voltage Measurement
    display_oled_voltage_dc();
    Serial.println("Voltage");
  }
  if (selection_count == 2)
  {
    // Voltage Measurement
    display_oled_voltage_ac();
    Serial.println("Voltage");
  }
  if (selection_count == 3)
  {
    // Current Measurement
    display_oled_current();
    Serial.println("Current");
  }
  if (selection_count == 4)
  {
    // Continuity test
    display_oled_continuity();
    Serial.println("Continuity");
  }

  if (selection_count == 5)
  {
    //Resistnace Measurement
    channel_2K_state = true;
    Serial.println("Resistance");
  }
  else
  {
    channel_2K_state = false;
  }

  if (selection_count == 6)
  {
    //Resistnace Measurement
    channel_20K_state = true;
    Serial.println("Resistance");
  }
  else
  {
    channel_20K_state = false;
  }

  if (selection_count == 7)
  {
    //Resistnace Measurement
    channel_200K_state = true;
    Serial.println("Resistance");
  }
  else
  {
    channel_200K_state = false;
  }

  if (selection_count == 8)
  {
    //Resistnace Measurement
    channel_1M_state = true;
    Serial.println("Resistance");
  }
  else
  {
    channel_1M_state = false;
  }

  if (selection_count > 8)
  {
    // Reset Count
    selection_count = 1;
    display_oled_voltage_dc();
  }
}

void display_oled_voltage_dc()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("V DC");
  measure_vdc();
  // update display with all of the above
  display.display();
}
void display_oled_voltage_ac()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.setTextSize(1);
  display.print("Vion Meter");
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("V AC");

  // update display with all of the above
  display.display();
}

void display_oled_current()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("A");

  measure_current();
  // update display with all of the above
  display.display();
}

void display_oled_continuity()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Conti");
  display.setCursor(10, 10);
  display.print("Continuity Test");
  display.setCursor(20, 20);
  display.print("in progress...");

  // update display with all of the above
  display.display();
}

void display_oled_resistance()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");

  // update display with all of the above
  display.display();
}

void display_oled_resistance_channel_2K()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("1 - 2k");
  display.setCursor(40, 22);
  display.print(measured_resistor_value);
  display.print(" Ohms");

  // update display with all of the above
  display.display();
}

void display_oled_resistance_channel_20K()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("2k - 20k");
  display.setCursor(40, 22);
  display.print(measured_resistor_value);
  display.print(" Ohms");

  // update display with all of the above
  display.display();
}

void display_oled_resistance_channel_200K()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("20k - 200k");
  display.setCursor(40, 22);
  display.print(measured_resistor_value);
  display.print(" Ohms");
  // update display with all of the above
  display.display();
}

void display_oled_resistance_channel_1M()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("200k - 1M");
  display.setCursor(40, 22);
  display.print(measured_resistor_value);
  display.print(" Ohms");

  // update display with all of the above
  display.display();
}

//////////////////////////////////
//////// VOLTAGE DC /////////////

void measure_vdc()
{
  dc_raw_value = analogRead(dc_measurement);
  mapped_raw_value = map(dc_raw_value, 0, 1023, 0, 255);
  Serial.println(mapped_raw_value);

  dc_voltage_out = (mapped_raw_value * (float)reference_voltage_val) / reference_decimal_val;
  Serial.println(dc_voltage_out);

  resistance_ratio = resistor_R2 / (resistor_R1 + resistor_R2);

  dc_actual_voltage = dc_voltage_out / resistance_ratio;
  Serial.println(dc_actual_voltage);
  //   delay(300);

  display.clearDisplay();
  display.setCursor(5, 0);
  display.setTextSize(1);
  display.print("Vion Meter");
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("V DC");
  display.setTextSize(2);
  display.setCursor(40, 15);
  display.print(dc_actual_voltage);
  display.print("V");
}

void measure_current()
{
  current_raw_value = analogRead(current_measurement_pin);

  //    Serial.println(current_raw_value);
  current_sensor_voltge = (current_raw_value / 1023) * 5000;

  Serial.println(current_sensor_voltge);
  delay(300);

  current_value = ((current_sensor_voltge - offset_voltage) / current_sensor_sensitivity);

  Serial.println(current_value);

  display.clearDisplay();
  display.setCursor(5, 0);
  display.setTextSize(1);
  display.print("Vion Meter");
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("A");
  display.setTextSize(2);
  display.setCursor(40, 15);
  display.print(current_value);
  display.print("A");
}

///////////////////////////////////////
///////////// OHM METER ///////////////

void measure_resistor()
{

  check_state_channel_2K();

  check_state_channel_20K();

  check_state_channel_200K();

  check_state_channel_1M();
}

void compute_reistance()
{
  resistor_raw_value = analogRead(resistor_measurement_pin);

  mapped_resistor_raw_value = map(resistor_raw_value, 0, 1023, 0, 255);

  resistor_divider_v_out = (mapped_resistor_raw_value * 5.08) / 255;

  Serial.println(resistor_raw_value);
  delay(200);
}

void check_state_channel_2K()
{
  if (channel_2K_state)
  {
    config_measure_channel_2K();
    compute_reistance();
    if (resistor_divider_v_out > 0.1)
    {
      //        Serial.println(measured_resistor_value);
      measured_resistor_value = channel_2K_value * (microcontroller_vin / resistor_divider_v_out - 1) - offset;

      if (measured_resistor_value > 2000 || measured_resistor_value == NULL)
      {
        config_measure_channel_2K();
        //          Serial.println("OL increase scale");
        // update on the Oled as well
        display_ol_change_scale_2K();
      }

      if (measured_resistor_value < 2000)
      {
        Serial.println(measured_resistor_value);
        config_measure_channel_2K();
        display_oled_resistance_channel_2K();
      }
    }
    else
    {
      display_zero_resistance_channel_2K();
    }
  }
}

void check_state_channel_20K()
{
  if (channel_20K_state)
  {
    config_measure_channel_20K();
    compute_reistance();
    if (resistor_divider_v_out > 0.1)
    {
      //        Serial.println(measured_resistor_value);
      measured_resistor_value = channel_20K_value * (microcontroller_vin / resistor_divider_v_out - 1) - offset;

      if (measured_resistor_value > 20000 || measured_resistor_value == NULL)
      {
        config_measure_channel_20K();
        //          Serial.println("OL increase scale");
        // update on the Oled as well
        display_ol_change_scale_20K();
      }

      if (measured_resistor_value < 20000)
      {
        Serial.println(measured_resistor_value);
        config_measure_channel_20K();
        display_oled_resistance_channel_20K();
      }
    }
    else
    {
      display_zero_resistance_channel_20K();
    }
  }
}

void check_state_channel_200K()
{
  if (channel_200K_state)
  {
    config_measure_channel_200K();
    compute_reistance();
    if (resistor_divider_v_out > 0.1)
    {
      //        Serial.println(measured_resistor_value);
      measured_resistor_value = channel_200K_value * (microcontroller_vin / resistor_divider_v_out - 1) - offset;

      if (measured_resistor_value > 200000 || measured_resistor_value == NULL)
      {
        config_measure_channel_200K();
        //          Serial.println("OL increase scale");
        // update on the Oled as well
        display_ol_change_scale_200K();
      }

      if (measured_resistor_value < 200000)
      {
        Serial.println(measured_resistor_value);
        config_measure_channel_200K();
        display_oled_resistance_channel_200K();
      }
    }
    else
    {
      display_zero_resistance_channel_200K();
    }
  }
}

void check_state_channel_1M()
{
  if (channel_1M_state)
  {
    config_measure_channel_1M();
    compute_reistance();
    if (resistor_divider_v_out > 0.1)
    {
      //        Serial.println(measured_resistor_value);
      measured_resistor_value = channel_1M_value * (microcontroller_vin / resistor_divider_v_out - 1) - offset;

      if (measured_resistor_value > 1000000 || measured_resistor_value == NULL)
      {
        config_measure_channel_1M();
        //          Serial.println("OL increase scale");
        // update on the Oled as well
        display_ol_change_scale_1M();
      }

      if (measured_resistor_value < 1000000)
      {
        Serial.println(measured_resistor_value);
        config_measure_channel_1M();
        display_oled_resistance_channel_1M();
      }
    }
    else
    {
      display_zero_resistance_channel_1M();
    }
  }
}

void config_measure_channel_2K()
{
  pinMode(microcontroller_voltage_pin, OUTPUT);
  pinMode(channel_2K_pin, OUTPUT);
  pinMode(channel_20K_pin, INPUT);
  pinMode(channel_200K_pin, INPUT);
  pinMode(channel_1M_pin, INPUT);

  digitalWrite(microcontroller_voltage_pin, HIGH);
  digitalWrite(channel_2K_pin, LOW);
}

void config_measure_channel_20K()
{
  pinMode(microcontroller_voltage_pin, OUTPUT);
  pinMode(channel_2K_pin, INPUT);
  pinMode(channel_20K_pin, OUTPUT);
  pinMode(channel_200K_pin, INPUT);
  pinMode(channel_1M_pin, INPUT);

  digitalWrite(microcontroller_voltage_pin, HIGH);
  digitalWrite(channel_20K_pin, LOW);
}

void config_measure_channel_200K()
{
  pinMode(microcontroller_voltage_pin, OUTPUT);
  pinMode(channel_2K_pin, INPUT);
  pinMode(channel_20K_pin, INPUT);
  pinMode(channel_200K_pin, OUTPUT);
  pinMode(channel_1M_pin, INPUT);

  digitalWrite(microcontroller_voltage_pin, HIGH);
  digitalWrite(channel_200K_pin, LOW);
}

void config_measure_channel_1M()
{
  pinMode(microcontroller_voltage_pin, OUTPUT);
  pinMode(channel_2K_pin, INPUT);
  pinMode(channel_20K_pin, INPUT);
  pinMode(channel_200K_pin, INPUT);
  pinMode(channel_1M_pin, OUTPUT);

  digitalWrite(microcontroller_voltage_pin, HIGH);
  digitalWrite(channel_1M_pin, LOW);
}

void display_ol_change_scale_2K()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("1 - 2K");
  display.setCursor(10, 22);
  display.print("OL increase scale !");

  // update display with all of the above
  display.display();
}

void display_ol_change_scale_20K()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("2k - 20K");
  display.setCursor(10, 22);
  display.print("OL increase scale !");

  // update display with all of the above
  display.display();
}

void display_ol_change_scale_200K()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("20k - 200K");
  display.setCursor(10, 22);
  display.print("OL increase scale !");

  // update display with all of the above
  display.display();
}

void display_ol_change_scale_1M()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("200k - 1M");
  display.setCursor(10, 22);
  display.print("OL !!!!!");

  // update display with all of the above
  display.display();
}

void display_zero_resistance_channel_2K()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("1 - 2k");
  display.setCursor(42, 22);
  display.print(" O.L Ohms");

  // update display with all of the above
  display.display();
}

void display_zero_resistance_channel_20K()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("2k - 20k");
  display.setCursor(42, 22);
  display.print("O.L k Ohms");

  // update display with all of the above
  display.display();
}

void display_zero_resistance_channel_200K()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("20k - 200k");
  display.setCursor(42, 22);
  display.print("O.L k Ohms");

  // update display with all of the above
  display.display();
}

void display_zero_resistance_channel_1M()
{

  // display a line of text
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("Vion Meter");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(75, 0);
  display.print("Ohms");
  display.setCursor(15, 10);
  display.print("Range:");
  display.setCursor(50, 10);
  display.print("200k - 1M");
  display.setCursor(42, 22);
  display.print("O.L M Ohms");

  // update display with all of the above
  display.display();
}
