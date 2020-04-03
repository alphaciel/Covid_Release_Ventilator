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
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.vergraph = QtWidgets.QVBoxLayout()
        self.vergraph.setContentsMargins(-1, -1, 0, -1)
        self.vergraph.setObjectName("vergraph")
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setObjectName("pushButton")
        self.vergraph.addWidget(self.pushButton)
        self.gridLayout.addLayout(self.vergraph, 1, 3, 1, 1)
        self.form_grid = QtWidgets.QFormLayout()
        self.form_grid.setObjectName("form_grid")
        self.potpb1 = QtWidgets.QProgressBar(self.centralwidget)
        self.potpb1.setProperty("value", 24)
        self.potpb1.setObjectName("potpb1")
        self.form_grid.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.potpb1)
        self.potlabel1 = QtWidgets.QLabel(self.centralwidget)
        self.potlabel1.setObjectName("potlabel1")
        self.form_grid.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.potlabel1)
        self.potlabel2 = QtWidgets.QLabel(self.centralwidget)
        self.potlabel2.setObjectName("potlabel2")
        self.form_grid.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.potlabel2)
        self.potpb2 = QtWidgets.QProgressBar(self.centralwidget)
        self.potpb2.setProperty("value", 24)
        self.potpb2.setObjectName("potpb2")
        self.form_grid.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.potpb2)
        self.potlabel3 = QtWidgets.QLabel(self.centralwidget)
        self.potlabel3.setObjectName("potlabel3")
        self.form_grid.setWidget(2, QtWidgets.QFormLayout.LabelRole, self.potlabel3)
        self.potpb3 = QtWidgets.QProgressBar(self.centralwidget)
        self.potpb3.setProperty("value", 24)
        self.potpb3.setObjectName("potpb3")
        self.form_grid.setWidget(2, QtWidgets.QFormLayout.FieldRole, self.potpb3)
        self.potlabel4 = QtWidgets.QLabel(self.centralwidget)
        self.potlabel4.setObjectName("potlabel4")
        self.form_grid.setWidget(3, QtWidgets.QFormLayout.LabelRole, self.potlabel4)
        self.potpb4 = QtWidgets.QProgressBar(self.centralwidget)
        self.potpb4.setProperty("value", 24)
        self.potpb4.setObjectName("potpb4")
        self.form_grid.setWidget(3, QtWidgets.QFormLayout.FieldRole, self.potpb4)
        self.gridLayout.addLayout(self.form_grid, 1, 5, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.pushButton.setText(_translate("MainWindow", "PushButton"))
        self.potlabel1.setText(_translate("MainWindow", "Potential 1"))
        self.potlabel2.setText(_translate("MainWindow", "Potential 2"))
        self.potlabel3.setText(_translate("MainWindow", "Potential 3"))
        self.potlabel4.setText(_translate("MainWindow", "Potential 4"))

