# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'design.ui'
#
# Created by: PyQt5 UI code generator 5.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 600)
        MainWindow.setStyleSheet("background:color(\"white\");")
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setStyleSheet("background:color(rgb(255, 255, 255));")
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.hgraph = QtWidgets.QHBoxLayout()
        self.hgraph.setContentsMargins(-1, -1, 0, -1)
        self.hgraph.setObjectName("hgraph")
        self.form_grid = QtWidgets.QFormLayout()
        self.form_grid.setObjectName("form_grid")
        self.potlabel1 = QtWidgets.QLabel(self.centralwidget)
        self.potlabel1.setObjectName("potlabel1")
        self.form_grid.setWidget(2, QtWidgets.QFormLayout.LabelRole, self.potlabel1)
        self.potpb1 = QtWidgets.QProgressBar(self.centralwidget)
        self.potpb1.setProperty("value", 24)
        self.potpb1.setObjectName("potpb1")
        self.form_grid.setWidget(2, QtWidgets.QFormLayout.FieldRole, self.potpb1)
        self.potlabel2 = QtWidgets.QLabel(self.centralwidget)
        self.potlabel2.setObjectName("potlabel2")
        self.form_grid.setWidget(3, QtWidgets.QFormLayout.LabelRole, self.potlabel2)
        self.potpb2 = QtWidgets.QProgressBar(self.centralwidget)
        self.potpb2.setProperty("value", 24)
        self.potpb2.setObjectName("potpb2")
        self.form_grid.setWidget(3, QtWidgets.QFormLayout.FieldRole, self.potpb2)
        self.potlabel3 = QtWidgets.QLabel(self.centralwidget)
        self.potlabel3.setObjectName("potlabel3")
        self.form_grid.setWidget(4, QtWidgets.QFormLayout.LabelRole, self.potlabel3)
        self.potpb3 = QtWidgets.QProgressBar(self.centralwidget)
        self.potpb3.setProperty("value", 24)
        self.potpb3.setObjectName("potpb3")
        self.form_grid.setWidget(4, QtWidgets.QFormLayout.FieldRole, self.potpb3)
        self.potlabel4 = QtWidgets.QLabel(self.centralwidget)
        self.potlabel4.setObjectName("potlabel4")
        self.form_grid.setWidget(5, QtWidgets.QFormLayout.LabelRole, self.potlabel4)
        self.potpb4 = QtWidgets.QProgressBar(self.centralwidget)
        self.potpb4.setProperty("value", 24)
        self.potpb4.setObjectName("potpb4")
        self.form_grid.setWidget(5, QtWidgets.QFormLayout.FieldRole, self.potpb4)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setContentsMargins(-1, 0, 0, -1)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.cbserial = QtWidgets.QComboBox(self.centralwidget)
        self.cbserial.setObjectName("cbserial")
        self.horizontalLayout.addWidget(self.cbserial)
        self.connectserial = QtWidgets.QPushButton(self.centralwidget)
        self.connectserial.setObjectName("connectserial")
        self.horizontalLayout.addWidget(self.connectserial)
        self.form_grid.setLayout(0, QtWidgets.QFormLayout.FieldRole, self.horizontalLayout)
        spacerItem = QtWidgets.QSpacerItem(20, 30, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.form_grid.setItem(1, QtWidgets.QFormLayout.FieldRole, spacerItem)
        self.hgraph.addLayout(self.form_grid)
        self.gridLayout.addLayout(self.hgraph, 1, 3, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.potlabel1.setText(_translate("MainWindow", "Potential 1"))
        self.potlabel2.setText(_translate("MainWindow", "Potential 2"))
        self.potlabel3.setText(_translate("MainWindow", "Potential 3"))
        self.potlabel4.setText(_translate("MainWindow", "Potential 4"))
        self.label.setText(_translate("MainWindow", "Connect USB"))
        self.connectserial.setText(_translate("MainWindow", "Connect"))

