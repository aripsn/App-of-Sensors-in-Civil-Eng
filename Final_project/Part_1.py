import serial
import matplotlib.pyplot as plt
from drawnow import *

# Replace 'COMX' with the appropriate serial port where Arduino is connected
ser = serial.Serial('COM6', 9600)

humidity_data = []
temperature_data = []
photo_data = []
plt.ion()  # Tell matplotlib you want interactive mode to plot live data
cnt = 0

def makeFig(): #Create a function that makes our desired plot
    plt.ylim(20,40)                                 #Set y min and max values
    plt.title('Sensor Data')      #Plot the title
    plt.grid(True)                                  #Turn the grid on
    plt.ylabel('Temp C')                            #Set ylabels
    plt.plot(temperature_data, 'ro-', label='Degrees C')       #plot the temperature
    plt.legend(loc='upper left')                    #plot the legend
    plt2=plt.twinx()                                #Create a second y axis
    #plt.ylim(93450,93525)                           #Set limits of second y axis- adjust to readings you are getting
    plt2.plot(photo_data, 'b^-', label='Intensity') #plot Intensity data
    plt2.set_ylabel('Intensity')                    #label second y axis
    plt2.ticklabel_format(useOffset=False)           #Force matplotlib to NOT autoscale y axis
    plt2.legend(loc='upper right')                  #plot the legend


try:
    while True:
        # Read the data from Arduino
        data = ser.readline().decode().strip()
        humidity, temp, intensity = map(float, data.split(','))
        print(humidity, temp, intensity)

        # Append the data to the respective lists
        humidity_data.append(humidity)
        temperature_data.append(temp)
        photo_data.append(intensity)
        drawnow(makeFig)  # Call drawnow to update our live graph
        plt.pause(0.000001)  # Pause briefly. Important to keep drawnow from crashing
        cnt += 1
        if cnt > 50:  # If you have 50 or more points, delete the first one from the array
            temp.pop(0)  # This allows us to just see the last 50 data points
            pressure.pop(0)
except KeyboardInterrupt:
    print("Stopping data acquisition.")
