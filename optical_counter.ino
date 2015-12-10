/*
 * Counts transitions in an TCRT5000 optical sensor. Also lights built in LED based on sensor reading.
 * Sends output to Serial.
 * 
 * Board: Teensy 3.1
 * 
 * T - Teensy 3.1
 * S - TCRT5000 optical sensor
 * R1 - 10K resistor
 * R2 - 330 Ohm resistor
 * 
 * Wiring:
 * T14  S3
 * GND  S2
 * R1a  3.3v
 * R1b  S3
 * R2a  3.3v
 * R2b  S1
 * S2   GND
 * 
 */
int pin_led = 13;
int pin_sensor = 14;

unsigned long count = 0;
void count_interrupt() {
  count++;
  digitalWrite(pin_led,digitalRead(pin_sensor));
}

void setup() {                
  Serial.begin(9600);
  Serial.println("started optical_counter");
  pinMode(pin_sensor,INPUT);
  pinMode(pin_led,OUTPUT);
  attachInterrupt(pin_sensor,count_interrupt, CHANGE);
  
}

unsigned long loop_count = 0;
unsigned long last_count = 0;

void loop() {
  unsigned long this_count = count;
  loop_count++;
  int sensorValue = analogRead(pin_sensor);
  Serial.print(loop_count);
  Serial.print(",");
  Serial.print(digitalRead(pin_sensor));
  Serial.print(",");
  Serial.print(this_count);
  Serial.print(",");
  Serial.print(this_count - last_count);
  Serial.print(",");
  Serial.println(sensorValue);
  last_count = this_count;
  delay(1000);
}
