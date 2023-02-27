/*
Este modulo se encarga de leer los movimientos del giroscopio del Arduino
Nano 33 BLE Sense Lite y escribir esas lecturas en varios csv's a segun el movimiento.
Los movimientos son 3: 
1. Mover el brazo hacia arriba    ->  brazo_arriba.csv
2. Mover el brazo hacia abajo     ->  brazo_abajo.csv
3. Mover el brazo hacia al frente ->  golpe.csv
Dichos movimientos se registran en otro script de Python que guarda esos valores via usb. 
El scrit se llama axis_csv_gen.py. El nombre que se le asigna a cada archivo que guarda son los mencionados
anteriormente
*/
#include <LSM9DS1.h>

void setup() {
  Serial.begin(9600);
	while (!Serial);
	//Serial.println("Started");
  if (!IMU.begin()) {
    //Serial.println("Failed to initialize IMU!");
		while (1);
	}
	//Serial.print("Gyroscope sample rate = ");
	//Serial.print(IMU.gyroscopeSampleRate());
	//Serial.println(" Hz");
	//Serial.println();
	//Serial.println("Gyroscope in degrees/second");
	//Serial.println("\tTimestamp\tX\tY\tZ");
}

void loop() {
  float x, y, z;
	unsigned long timestamp = millis();
	if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
		//Serial.print('\t');    
		Serial.print(timestamp);
		Serial.print('\t');    
		Serial.print(x);
		Serial.print('\t');
		Serial.print(y);
		Serial.print('\t');
		Serial.println(z);
	}
}