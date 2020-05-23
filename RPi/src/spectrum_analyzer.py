from pyqtgraph import QtGui, QtCore
import pyqtgraph as pg
import numpy as np
import serial
import RPi.GPIO as GPIO
import datetime
import random
import scipy.fftpack
import scipy.signal

#GPIO settings
#Set communication pin to GPIO21
commPin = 40
GPIO.setmode(GPIO.BOARD)
GPIO.setup(commPin, GPIO.OUT)

#Serial settings
ser = serial.Serial("/dev/ttyACM0", 115200)
ser.baudrate = 115200

# PyQtGraph setup
app = QtGui.QApplication([])
win = pg.GraphicsWindow(title="Spectrum analyzer")
win.resize(1000, 600)
win.setWindowTitle("Spectrum analyzer")
pg.setConfigOptions(antialias=True)
raw_sound_plot = win.addPlot(title="Raw sound")
win.nextRow()
fft_plot = win.addPlot(title="FFT")
vb = fft_plot.vb
label = pg.LabelItem(text="Hello", parent=fft_plot)

def onMouseMoved(evt):
    pos = evt
    if fft_plot.sceneBoundingRect().contains(pos):
        mousePoint = vb.mapSceneToView(pos)
        indx = (mousePoint.x())
        if indx > 0:
            label.setText(
                "<span style='font-size: 12pt; color: yellow'>%0.3f</span>"
                % indx
            )
        else:
            label.setText("")
            
fft_plot.scene().sigMouseMoved.connect(onMouseMoved)

while True:
    # Clear variables
    i = 0
    error = 0
    sync = 0
    val = 0
    raw_data = []
    
    # Signal that we are ready for the data transfer
    GPIO.output(commPin, GPIO.HIGH)
    # The data transfer starts after a -1 was sent, so wait for it
    while sync != -1:
        try:
            sync = int(ser.readline().strip())
        except:
            sync = int(ser.readline().strip())
    
    # The data transfer ends with a -3
    # So read data until that is sent
    while val != -3:
        try:
            val = int(ser.readline().strip())
            raw_data.append(val)
        except Exception:
            pass
    
    # Signal that we are not ready for the data transfer now
    GPIO.output(commPin, GPIO.LOW)
    
    # Calculate indices accordong to the used protocol
    time_index = len(raw_data) - 2
    data_lastindex = time_index - 1
    
    elapsed_time = raw_data[time_index]
    raw_data = raw_data[0:data_lastindex]
    N = len(raw_data)
    avg_sample_duration = elapsed_time/N
    
    fft_values = scipy.fftpack.fft(raw_data)
    fft_to_plot = 2.0 / N * np.abs(fft_values[:N//2])
    fft_x_axis = np.linspace(0.0, 1.0 / (2.0 * avg_sample_duration), N/2)
    #print(scipy.signal.find_peaks(fft_to_plot, prominence = 1))
    raw_sound_plot.plot(raw_data, clear=True, pen="g")
    fft_plot.plot(fft_x_axis, fft_to_plot, clear=True, pen="c")
    
    pg.QtGui.QApplication.processEvents()