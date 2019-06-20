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
