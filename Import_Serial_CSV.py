import serial
import csv
from datetime import datetime

def read_data_from_arduino(serial_port, baud_rate):
    arduino = serial.Serial(serial_port, baud_rate, timeout=1)

    # Generate a unique file name based on the current date and time 
    timestamp_str = datetime.now().strftime("%Y%m%d_%H%M%S")
    file_name = f"data_from_arduino_{timestamp_str}.csv"

    with open(file_name, 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(['Timestamp', 'AccX1', 'AccY1', 'AccZ1', 'GyX1', 'GyY1', 'GyZ1', 'AccX2', 'AccY2', 'AccZ2', 'GyX2', 'GyY2', 'GyZ2'])  # Write CSV header

        while True:
            line = arduino.readline().decode().strip()
            if line:
                data = line.split(',')
                timestamp = int(data[0])
                accX1, accY1, accZ1, gyroX1, gyroY1, gyroZ1, accX2, accY2, accZ2, gyroX2, gyroY2, gyroZ2 = map(float, data[1:])
                
                csv_writer.writerow([timestamp, accX1, accY1, accZ1, gyroX1, gyroY1, gyroZ1, accX2, accY2, accZ2, gyroX2, gyroY2, gyroZ2])
                print(f"Received data: Timestamp = {timestamp}, AccX1 = {accX1}, AccY1 = {accY1}, AccZ1 = {accZ1}, GyroX1 = {gyroX1}, GyroY1 = {gyroY1}, GyroZ1 = {gyroZ1}, AccX2 = {accX2}, AccY2 = {accY2}, AccZ2 = {accZ2}, GyroX2 = {gyroX2}, GyroY2 = {gyroY2}, GyroZ2 = {gyroZ2}")

if __name__ == "__main__":
    serial_port = 'COM4'  # Change this to your Arduino's serial port
    baud_rate = 9600  # Make sure it matches the Arduino's baud rate
    read_data_from_arduino(serial_port, baud_rate)
