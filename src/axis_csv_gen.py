
import serial
import csv
import os


#cambiar aqui el nombre del puerto (debe coincidir con el que esta en Arduino IDE)
puerto = "/dev/ttyACM0"
#serializamos
#En port ponemos el valor que se obtiene al ejeciutar el script virtualport.sh
ser = serial.Serial(port = puerto,baudrate=9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS) 
#ser = serial.Serial(port = '/dev/pts/3',baudrate=9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS) 
current_directory = os.getcwd()
#cambiar el segundo argumento por alguno de estos cuando se esten guardando los datos:
'''
  1. Mover el brazo hacia arriba    ->  circular.csv
  2. Mover el brazo hacia abajo     ->  flexion.csv
  3. Mover el brazo hacia al frente ->  flexion.csv
'''
#Asegurarse que el dump file quede dentro del mismo dir
csv_path = os.path.join(current_directory, "flexion.csv")
#pequena tabla para ver la duracion de las interaciones
'''
Iteraciones   tiempo(s)
1500          ~13  
1000          ~9.2
'''
with open(csv_path, mode ='w') as csv_file:
  writer = csv.writer(csv_file)
  writer.writerow(['aX', 'aY', 'aZ', 'gX', 'gY', 'gZ'])
  #cambiar el valor muestras por el valor de muestras que se desean
  muestras = 1000
  cnt = 0
  while True:
    line = ser.readline().decode().strip()
    data = line.split('\t')
    ax = float(data[0])
    ay = float(data[1])
    az = float(data[2])
    gx = float(data[3])
    gy = float(data[4])
    gz = float(data[5])
    writer.writerow([ ax, ay, az, gx, gy, gz])
    #Con fines de debug
    print(f"aX: {ax}, aY: {ay}, aZ: {az}, gX: {gx}, gY: {gy}, gZ: {gz}")
    cnt += 1
    if cnt >= muestras:
      break
