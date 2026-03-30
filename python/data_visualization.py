import serial
import matplotlib.pyplot as plt

ser = serial.Serial('COM3', 9600)

temps = []
humidity = []

while True:
    line = ser.readline().decode().strip()
    print(line)

    try:
        values = line.split(',')

        if len(values) == 4:
            t = float(values[0])
            h = float(values[1])

            temps.append(t)
            humidity.append(h)

            plt.clf()
            plt.plot(temps, label="Temperature")
            plt.plot(humidity, label="Humidity")
            plt.legend()
            plt.pause(0.1)

    except:
        pass
