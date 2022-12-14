# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '.\MainWindow.ui'
#
# Created by: PyQt5 UI code generator 5.15.7
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(820, 620)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.apply_ip = QtWidgets.QPushButton(self.centralwidget)
        self.apply_ip.setGeometry(QtCore.QRect(50, 80, 93, 28))
        self.apply_ip.setObjectName("apply_ip")
        self.label_ip = QtWidgets.QLabel(self.centralwidget)
        self.label_ip.setGeometry(QtCore.QRect(50, 18, 55, 16))
        self.label_ip.setObjectName("label_ip")
        self.log_content = QtWidgets.QScrollArea(self.centralwidget)
        self.log_content.setGeometry(QtCore.QRect(20, 426, 781, 131))
        self.log_content.setWidgetResizable(True)
        self.log_content.setObjectName("log_content")
        self.scrollAreaWidgetContents = QtWidgets.QWidget()
        self.scrollAreaWidgetContents.setGeometry(QtCore.QRect(0, 0, 779, 129))
        self.scrollAreaWidgetContents.setObjectName("scrollAreaWidgetContents")
        self.log_content.setWidget(self.scrollAreaWidgetContents)
        self.timeout_slider_fast = QtWidgets.QSlider(self.centralwidget)
        self.timeout_slider_fast.setGeometry(QtCore.QRect(40, 230, 251, 27))
        self.timeout_slider_fast.setMinimum(10)
        self.timeout_slider_fast.setMaximum(1000)
        self.timeout_slider_fast.setOrientation(QtCore.Qt.Horizontal)
        self.timeout_slider_fast.setTickPosition(QtWidgets.QSlider.TicksBelow)
        self.timeout_slider_fast.setTickInterval(99)
        self.timeout_slider_fast.setObjectName("timeout_slider_fast")
        self.timeout_fast = QtWidgets.QLabel(self.centralwidget)
        self.timeout_fast.setGeometry(QtCore.QRect(155, 260, 31, 21))
        self.timeout_fast.setObjectName("timeout_fast")
        self.line = QtWidgets.QFrame(self.centralwidget)
        self.line.setGeometry(QtCore.QRect(20, 123, 771, 16))
        self.line.setFrameShape(QtWidgets.QFrame.HLine)
        self.line.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line.setObjectName("line")
        self.line_2 = QtWidgets.QFrame(self.centralwidget)
        self.line_2.setGeometry(QtCore.QRect(395, 140, 20, 261))
        self.line_2.setFrameShape(QtWidgets.QFrame.VLine)
        self.line_2.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_2.setObjectName("line_2")
        self.fast_title = QtWidgets.QLabel(self.centralwidget)
        self.fast_title.setGeometry(QtCore.QRect(40, 140, 321, 41))
        font = QtGui.QFont()
        font.setPointSize(14)
        font.setBold(True)
        font.setWeight(75)
        self.fast_title.setFont(font)
        self.fast_title.setObjectName("fast_title")
        self.slow_title = QtWidgets.QLabel(self.centralwidget)
        self.slow_title.setGeometry(QtCore.QRect(430, 140, 331, 41))
        font = QtGui.QFont()
        font.setPointSize(14)
        font.setBold(True)
        font.setWeight(75)
        self.slow_title.setFont(font)
        self.slow_title.setObjectName("slow_title")
        self.log_title = QtWidgets.QLabel(self.centralwidget)
        self.log_title.setGeometry(QtCore.QRect(20, 410, 55, 16))
        self.log_title.setObjectName("log_title")
        self.send_RequestForFastResponse = QtWidgets.QPushButton(self.centralwidget)
        self.send_RequestForFastResponse.setGeometry(QtCore.QRect(40, 360, 93, 28))
        self.send_RequestForFastResponse.setObjectName("send_RequestForFastResponse")
        self.send_RequestForSlowResponse = QtWidgets.QPushButton(self.centralwidget)
        self.send_RequestForSlowResponse.setGeometry(QtCore.QRect(430, 360, 93, 28))
        self.send_RequestForSlowResponse.setObjectName("send_RequestForSlowResponse")
        self.timeout_slider_slow = QtWidgets.QSlider(self.centralwidget)
        self.timeout_slider_slow.setGeometry(QtCore.QRect(430, 230, 251, 27))
        self.timeout_slider_slow.setMinimum(10)
        self.timeout_slider_slow.setMaximum(1000)
        self.timeout_slider_slow.setOrientation(QtCore.Qt.Horizontal)
        self.timeout_slider_slow.setTickPosition(QtWidgets.QSlider.TicksBelow)
        self.timeout_slider_slow.setTickInterval(99)
        self.timeout_slider_slow.setObjectName("timeout_slider_slow")
        self.timeout_slow = QtWidgets.QLabel(self.centralwidget)
        self.timeout_slow.setGeometry(QtCore.QRect(545, 260, 31, 21))
        self.timeout_slow.setObjectName("timeout_slow")
        self.label_timeout_fast = QtWidgets.QLabel(self.centralwidget)
        self.label_timeout_fast.setGeometry(QtCore.QRect(40, 204, 81, 16))
        self.label_timeout_fast.setObjectName("label_timeout_fast")
        self.label_timeout_slow = QtWidgets.QLabel(self.centralwidget)
        self.label_timeout_slow.setGeometry(QtCore.QRect(430, 205, 81, 16))
        self.label_timeout_slow.setObjectName("label_timeout_slow")
        self.enter_sleep = QtWidgets.QLineEdit(self.centralwidget)
        self.enter_sleep.setGeometry(QtCore.QRect(430, 300, 61, 31))
        self.enter_sleep.setObjectName("enter_sleep")
        self.sleep_label = QtWidgets.QLabel(self.centralwidget)
        self.sleep_label.setGeometry(QtCore.QRect(430, 280, 55, 16))
        self.sleep_label.setObjectName("sleep_label")
        self.label_sec = QtWidgets.QLabel(self.centralwidget)
        self.label_sec.setGeometry(QtCore.QRect(500, 310, 55, 16))
        self.label_sec.setObjectName("label_sec")
        self.label_port = QtWidgets.QLabel(self.centralwidget)
        self.label_port.setGeometry(QtCore.QRect(210, 18, 55, 16))
        self.label_port.setObjectName("label_port")
        self.label_reconnect = QtWidgets.QLabel(self.centralwidget)
        self.label_reconnect.setGeometry(QtCore.QRect(460, 20, 301, 16))
        self.label_reconnect.setObjectName("label_reconnect")
        self.apply_port = QtWidgets.QPushButton(self.centralwidget)
        self.apply_port.setGeometry(QtCore.QRect(210, 80, 93, 28))
        self.apply_port.setObjectName("apply_port")
        self.apply_reconnect = QtWidgets.QPushButton(self.centralwidget)
        self.apply_reconnect.setGeometry(QtCore.QRect(460, 80, 93, 28))
        self.apply_reconnect.setObjectName("apply_reconnect")
        self.reconnect_slider = QtWidgets.QSlider(self.centralwidget)
        self.reconnect_slider.setGeometry(QtCore.QRect(465, 40, 251, 27))
        self.reconnect_slider.setMinimum(1)
        self.reconnect_slider.setMaximum(10)
        self.reconnect_slider.setPageStep(1)
        self.reconnect_slider.setProperty("value", 1)
        self.reconnect_slider.setOrientation(QtCore.Qt.Horizontal)
        self.reconnect_slider.setTickPosition(QtWidgets.QSlider.TicksBelow)
        self.reconnect_slider.setTickInterval(1)
        self.reconnect_slider.setObjectName("reconnect_slider")
        self.recconect = QtWidgets.QLabel(self.centralwidget)
        self.recconect.setGeometry(QtCore.QRect(590, 70, 21, 21))
        self.recconect.setObjectName("recconect")
        self.enter_ip = QtWidgets.QLineEdit(self.centralwidget)
        self.enter_ip.setGeometry(QtCore.QRect(50, 45, 113, 22))
        self.enter_ip.setObjectName("enter_ip")
        self.enter_port = QtWidgets.QLineEdit(self.centralwidget)
        self.enter_port.setGeometry(QtCore.QRect(210, 45, 113, 22))
        self.enter_port.setObjectName("enter_port")
        self.label_ms_1 = QtWidgets.QLabel(self.centralwidget)
        self.label_ms_1.setGeometry(QtCore.QRect(300, 230, 41, 16))
        self.label_ms_1.setObjectName("label_ms_1")
        self.label_ms_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_ms_2.setGeometry(QtCore.QRect(690, 230, 41, 16))
        self.label_ms_2.setObjectName("label_ms_2")
        self.label_sec_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_sec_2.setGeometry(QtCore.QRect(720, 40, 51, 16))
        self.label_sec_2.setObjectName("label_sec_2")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 820, 26))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Client"))
        self.apply_ip.setText(_translate("MainWindow", "apply"))
        self.label_ip.setText(_translate("MainWindow", "ip:"))
        self.timeout_fast.setText(_translate("MainWindow", "10"))
        self.fast_title.setText(_translate("MainWindow", "Request For Fast Response"))
        self.slow_title.setText(_translate("MainWindow", "Request For Slow Responce"))
        self.log_title.setText(_translate("MainWindow", "log"))
        self.send_RequestForFastResponse.setText(_translate("MainWindow", "Send"))
        self.send_RequestForSlowResponse.setText(_translate("MainWindow", "Send"))
        self.timeout_slow.setText(_translate("MainWindow", "10"))
        self.label_timeout_fast.setText(_translate("MainWindow", "Set timeout"))
        self.label_timeout_slow.setText(_translate("MainWindow", "Set timeout"))
        self.sleep_label.setText(_translate("MainWindow", "Sleep:"))
        self.label_sec.setText(_translate("MainWindow", "seconds"))
        self.label_port.setText(_translate("MainWindow", "port:"))
        self.label_reconnect.setText(_translate("MainWindow", "in case of connection failure, reconnect every:"))
        self.apply_port.setText(_translate("MainWindow", "apply"))
        self.apply_reconnect.setText(_translate("MainWindow", "apply"))
        self.recconect.setText(_translate("MainWindow", "1"))
        self.label_ms_1.setText(_translate("MainWindow", "ms"))
        self.label_ms_2.setText(_translate("MainWindow", "ms"))
        self.label_sec_2.setText(_translate("MainWindow", "seconds"))
