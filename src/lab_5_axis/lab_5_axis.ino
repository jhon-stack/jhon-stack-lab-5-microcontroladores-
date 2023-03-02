/*
Este modulo se encarga de leer los movimientos del giroscopio del Arduino
Nano 33 BLE Sense Lite y escribir esas lecturas en varios csv's a segun el movimiento.
Los movimientos son 3: 
1. Mover el brazo hacia arriba    ->  circular.csv
2. Mover el brazo hacia abajo     ->  flexion.csv
3. Mover el brazo hacia al frente ->  izquierda_derecha.csv
Dichos movimientos se registran en otro script de Python que guarda esos valores via usb. 
El scrit se llama axis_csv_gen.py. El nombre que se le asigna a cada archivo que guarda son los mencionados
anteriormente
*/
#include <LSM9DS1.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!IMU.begin()) {
		while (1);
  }

}

void loop() {
	float ax, ay, az;
  	float gx, gy, gz;
	unsigned long timestamp = millis();
  	//Agarramos los dos el giroscopio y el acelerometro
	if (IMU.gyroscopeAvailable() && IMU.accelerationAvailable() ) {
		IMU.readAcceleration(ax, ay, az);
    	IMU.readGyroscope(gx, gy, gz);
    	Serial.print('\t');    
		Serial.print(ax);
		Serial.print('\t');
		Serial.print(ay);
		Serial.print('\t');
		Serial.print(az);
		Serial.print('\t');    
		Serial.print(gx);
		Serial.print('\t');
		Serial.print(gy);
		Serial.print('\t');
		Serial.println(gz);
	}
}

