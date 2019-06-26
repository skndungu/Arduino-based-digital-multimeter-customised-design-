/////////////////////////////
///////OPTIONS BUTTON///////

// Pin  declarations
const int selection_btn = 2;

// Vairables

int selection_btn_value = 0;
int last_selection_btn_value = 0; 
bool button_press = false;

int selection_count = 0; // number of btn presses

/////////////////////////////
////////CONTINUITY//////////

// Pin  declarations
const int continuity_probe_1 = 3;
const int continuity_buzzer = 4;
const int continuity_probe_2 = 5;

// Vairables
int buzzer_value;



/////////////////////////////
//////////VOLTAGE DC////////

// Pin  declarations
const int dc_measurement = A2;

// Vairables

float dc_raw_value = 0.0;
int mapped_raw_value = 0;
float dc_voltage_out;
float compute_dc_voltage_out = 0;
float dc_actual_voltage = 0.0;
int reference_voltage_val = 5;
float reference_decimal_val =255;

float resistor_R1 = 1000000;
float resistor_R2 = 100000;
float resistance_ratio = 0.0;


/////////////////////////////
//////////CURRENT////////

// Pin  declarations
const int current_measurement_pin = A4;

// Vairables
int current_sensor_sensitivity = 100;
float current_raw_value = 0;
float offset_voltage = 2500;

float current_sensor_voltge = 0;
float current_value = 0;



/////////////////////////////
//////////OHM METER////////

// variables 

const int resistor_measurement_pin = A1;

float resistor_raw_value = 0;
float mapped_resistor_raw_value = 0;
float resistor_divider_v_out = 0.00;
float microcontroller_vin = 5.08;
float measured_resistor_value = 0;

float offset = 25;

// setting different measurement ranges

// controller pins:

const int microcontroller_voltage_pin = 7;
const int channel_2K_pin = 8;
const int channel_20K_pin = 9;
const int channel_200K_pin = 10;
const int channel_1M_pin = 11;

// channel selection states:

bool channel_2K_state = false;
bool channel_20K_state = false;
bool channel_200K_state = false;
bool channel_1M_state = false;

float channel_2K_value = 1000;
float channel_20K_value = 20000;
float channel_200K_value = 200000;
float channel_1M_value = 1000000;
