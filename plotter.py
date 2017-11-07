import matplotlib.pyplot as plt
import serial
import sys

WAVE=1
FFT=2
NONE=0

arduino = serial.Serial(port=sys.argv[1], baudrate=115200)
# mode = NONE

fig = plt.figure()
plt.title('FFT')
plt.axis([0.4,2.1,0,15])
plt.ion()
fig.show()

xlist = [0]*12
ylist = [0]*12

fft, = plt.plot(xlist, ylist)

def capture_fft():
    while True:
        line = arduino.readline()
        line = line.strip()
        print(line)
        if len(line) == 0:
            break

        xy = line.split(' ')
        x,y = float(xy[0]),float(xy[1])
        xlist.append(x)
        ylist.append(y)

while True:
    line = arduino.readline()
    line = line.strip()
    print(line)
    if line.startswith('FFT'):
        print('Going into FFT')
        xlist = list()
        ylist = list()

        capture_fft()

        fft.set_xdata(xlist)
        fft.set_ydata(ylist)
        fig.canvas.draw()
    elif line.startswith('Heart rate:'):
        hrt = line[11:]
        plt.title('FFT, Heart Rate = %s bpm' % hrt)
        fig.canvas.draw()
