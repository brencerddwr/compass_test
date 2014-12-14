#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <math.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
//Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

void acceldisplaySensorDetails(void)
{
	sensor_t accel_sensor;
	accel.getSensor(&accel_sensor);
	Serial.println("------------------------------------");
	Serial.print  ("Sensor:       "); Serial.println(accel_sensor.name);
	Serial.print  ("Driver Ver:   "); Serial.println(accel_sensor.version);
	Serial.print  ("Unique ID:    "); Serial.println(accel_sensor.sensor_id);
	Serial.print  ("Max Value:    "); Serial.print(accel_sensor.max_value); Serial.println(" m/s^2");
	Serial.print  ("Min Value:    "); Serial.print(accel_sensor.min_value); Serial.println(" m/s^2");
	Serial.print  ("Resolution:   "); Serial.print(accel_sensor.resolution); Serial.println(" m/s^2");
	Serial.println("------------------------------------");
	Serial.println("");
	delay(500);
}

void magdisplaySensorDetails(void)
{
	sensor_t mag_sensor;
	mag.getSensor(&mag_sensor);
	Serial.println("------------------------------------");
	Serial.print  ("Sensor:       "); Serial.println(mag_sensor.name);
	Serial.print  ("Driver Ver:   "); Serial.println(mag_sensor.version);
	Serial.print  ("Unique ID:    "); Serial.println(mag_sensor.sensor_id);
	Serial.print  ("Max Value:    "); Serial.print(mag_sensor.max_value); Serial.println(" uT");
	Serial.print  ("Min Value:    "); Serial.print(mag_sensor.min_value); Serial.println(" uT");
	Serial.print  ("Resolution:   "); Serial.print(mag_sensor.resolution); Serial.println(" uT");
	Serial.println("------------------------------------");
	Serial.println("");
	delay(500);
}

void setup(void)
{
	Serial.begin(9600);
	Serial.println("Magnetometer Test"); Serial.println("");
	
	/* Enable auto-gain */
	mag.enableAutoRange(true);
	
	
	/* Initialise the sensor */
	if(!mag.begin())
	{
		/* There was a problem detecting the LSM303 ... check your connections */
		Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
		while(1);
	}
	
	/* Display some basic information on this sensor */
	magdisplaySensorDetails();
	//acceldisplaySensorDetails();
}

void loop(void)
{
	/* Get a new sensor event */
	sensors_event_t mag_event;
	mag.getEvent(&mag_event);
	sensors_event_t &accel_event;
	accel.getEvent(&accel_event);
	
	/* Display the results (magnetic vector values are in micro-Tesla (uT)) */
	Serial.print("X: "); Serial.print(mag_event.magnetic.x); Serial.print("  ");
	Serial.print("Y: "); Serial.print(mag_event.magnetic.y); Serial.print("  ");
	Serial.print("Z: "); Serial.print(mag_event.magnetic.z); Serial.print("  ");Serial.println("uT");
	 float heading = (atan2(mag_event.magnetic.y,mag_event.magnetic.x) * 180) / PI;
	 // Normalize to 0-360
	 if (heading < 0)
	 {
		 heading = 360 + heading;
	 }
	 Serial.print("Compass Heading: ");
	 Serial.println(heading);
	
	/* Display the results (acceleration is measured in m/s^2) */
	Serial.print("X: "); Serial.print(accel_event.acceleration.x); Serial.print("  ");
	Serial.print("Y: "); Serial.print(accel_event.acceleration.y); Serial.print("  ");
	Serial.print("Z: "); Serial.print(accel_event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
	delay(500);
}
