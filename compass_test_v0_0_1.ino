#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <math.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
//Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

/*void acceldisplaySensorDetails(void)
{
	sensor_t sensor;
	accel.getSensor(&sensor);
	Serial.println("------------------------------------");
	Serial.print  ("Sensor:       "); Serial.println(sensor.name);
	Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
	Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
	Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
	Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
	Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
	Serial.println("------------------------------------");
	Serial.println("");
	delay(500);
}
*/
void magdisplaySensorDetails(void)
{
	sensor_t sensor;
	mag.getSensor(&sensor);
	Serial.println("------------------------------------");
	Serial.print  ("Sensor:       "); Serial.println(sensor.name);
	Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
	Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
	Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
	Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
	Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
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
	//accel.getEvent(&event);
	
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
	//Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
	//Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
	//Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
	delay(500);
}
