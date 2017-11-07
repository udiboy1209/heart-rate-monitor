Heart Rate Monitor using PPG
================

Sensors course project by Meet Udeshi and Pulkit Goyal

Dependencies
============

Arduino code requires:

 - ArduinoFFT library: https://github.com/kosme/arduinoFFT
 - Metro library: https://github.com/thomasfredericks/Metro-Arduino-Wiring

Plotter code requires:

 - pySerial
 - matplotlib

Install using

```
pip install serial matplotlib
```

Run plotter using (where COM-PORT is "COMx" on windows or "/dev/ttyACMx" etc)

```
python plotter.py <COM-PORT>
```
