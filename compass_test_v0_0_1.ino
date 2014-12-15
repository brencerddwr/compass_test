#include <Wire.h>
#include <LSM303.h>
#include <math.h>
LSM303 compass;
void setup() {
	Serial.begin(115200);
	Wire.begin();
	compass.init();
	compass.enableDefault();
	/*
	Calibration values; the default values of +/-32767 for each axis
	lead to an assumed magnetometer bias of 0. Use the Calibrate example
	program to determine appropriate values for your particular unit.
	*/
	compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
	compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};
}
void loop(void)
{
	/* Get a new sensor event */
	compass.read();
	double heading = compass.heading();
	double roll = (atan2(-compass.a.y,compass.a.x)*180)/PI;
	double pitch = (atan2(compass.a.x,sqrt(pow(compass.a.y,2)+pow(compass.a.z,2)))*180)/PI;
	
	Serial.print("X: "); Serial.print(compass.m.x); Serial.print("  ");
	Serial.print("Y: "); Serial.print(compass.m.y); Serial.print("  ");
	Serial.print("Z: "); Serial.println(compass.m.z);
	
	/* Display the results (acceleration is measured in m/s^2) */
	Serial.print("X: "); Serial.print(compass.a.x); Serial.print("  ");
	Serial.print("Y: "); Serial.print(compass.a.y); Serial.print("  ");
	Serial.print("Z: "); Serial.println(compass.a.z);
	/* Display calculated results */
	Serial.print("Pitch: ");Serial.print(pitch);
	Serial.print(" Roll: ");Serial.print(roll);
	Serial.print(" Compass Heading: ");Serial.println(compass.heading());
		 
	delay(500);
}
