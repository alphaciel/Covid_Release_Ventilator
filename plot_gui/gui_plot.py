#!/usr/bin/env/python3
# -*- coding: utf-8 -*-

# authors Reginalds

###################################################################
#                                                                 #
#                         Ventilator Graph                        #
#                  -----------------------------                  #
#          God create the Games and Human end those Games         #
#                  Cause Human tires of those Games               #
#                                                                 #
#                                                                 # 
###################################################################

import sys
import re
import os
import glob


from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import AppDesign
import functools

import numpy as np
import matplotlib
matplotlib.use("Qt5Agg")
from matplotlib.figure import Figure
from matplotlib import animation
from matplotlib.lines import Line2D
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib import pyplot as plt
import matplotlib.font_manager as fm

import threading
import serial
import time
import random

#class SerialCommunicate(Object):
#    def __init__(self):
        
class ComboBox(QComboBox):
    popupAboutToBeShown = pyqtSignal()

    def showPopup(self):
        self.popupAboutToBeShown.emit()
        super(ComboBox, self).showPopup()
    
        
        
class Applications(QMainWindow, AppDesign.Ui_MainWindow):
    def __init__(self, parent=None):
        super(Applications, self).__init__()
        self.m = PlotCanvas(self, width=5, height=4)
        self.m.move(0,0)
        self.setupUi(self)
        self.hgraph.addWidget(self.m)
        self.cbserial= ComboBox(self)
        self.cbserial.popupAboutToBeShown.connect(self.overUpdate)
        self.cbserial.popupAboutToBeShown.connect(self.clearCBserial)
    def overUpdate(self):
        self.listusb = ['']
        self.listusb.append(glob.glob("/dev/ttyA*"))
        self.listusb.append(glob.glob("/dev/ttyU*"))
        print(self.listusb)
        print(len(self.listusb))
        for listusbA in range(0,len(self.listusb[1])):
            print(type(self.listusb[1][listusbA]))
            self.cbserial.addItem(self.listusb[1][listusbA])
        for listusbU in range(0,len(self.listusb[2])):
            print(type(self.listusb[2][listusbU]))
            self.cbserial.addItem(self.listusb[2][listusbU])
    def clearCBserial(self):
        self.cbserial.clear()
class PlotCanvas(FigureCanvas):

    def __init__(self, parent=None, width=5, height=4, dpi=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(211)
        self.fp1=fm.FontProperties(fname="/usr/share/fonts/truetype/khmeros/KhmerOSsys.ttf")

        FigureCanvas.__init__(self, fig)
        self.setParent(parent)
        
        FigureCanvas.setSizePolicy(self,
                QSizePolicy.Expanding,
                QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)
        self.plot()

        
    def plot(self):
        data = [random.random() for i in range(25)]
        ax = self.figure.add_subplot(211)
        ax.plot(data, 'r-')
        ax.set_title(u'សម្ពាធ - Pressure',fontproperties=self.fp1)
        data = [random.random() for i in range(25)]
        # ploting sub 2
        ax = self.figure.add_subplot(212)
        ax.set_title(u'សីតុណ្ហភាព - Temperature ',fontproperties=self.fp1)
        data = [random.random() for i in range(25)]
        ax.plot(data, 'r-')
        self.draw()
        
        
def main():
    
    app = QApplication(sys.argv)
    form = Applications()
    form.showFullScreen()
    app.exec_()

if __name__ == '__main__':
    main()
    