#!/usr/bin/env/python3

###################################################################
#                                                                 #
#                         Ventilator Graph                        #
#                  -----------------------------                  #
#            EMBED A MATPLOTLIB ANIMATION INSIDE YOUR             #
#            OWN GUI!                                             #
#                                                                 #
###################################################################

import sys
import numpy as np 
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import functools
import numpy as np
import serial
import matplotlib
matplotlib.use("Qt5Agg")
from matplotlib.figure import Figure
from matplotlib.animation import TimedAnimation
from matplotlib.lines import Line2D
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas

import time
import threading

class PlottingMainWindow(QMainWindow):
    def __init__(self):
        super(PlottingMainWindow, self).__init__()
        self.setGeometry(300,300,800,400)
        self.setWindowTitle("")