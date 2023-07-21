#!/usr/bin/env python
# -*- coding: utf-8 -*-

<<<<<<< Updated upstream
from http.client import NON_AUTHORITATIVE_INFORMATION
from pickle import TRUE
import sys
from PySide6.QtWidgets import QApplication
from PySide6.QtCore import QObject, Signal, Slot
from PySide6.QtWidgets import QWidget, QPushButton, QVBoxLayout, QHBoxLayout, QLabel, QLineEdit, QMessageBox,QTextBrowser,QListView,QListWidget,QComboBox
from PySide6.QtGui import QIcon,QFont,QColor
from PySide6.QtNetwork import QNetworkAccessManager, QNetworkRequest, QNetworkReply
import datetime
import threading

from serial.tools.list_ports import comports
import serial


=======
import datetime
import sys
import threading

import serial
from PySide6.QtCore import QObject, Signal, Slot
from PySide6.QtGui import QColor, QFont, QIcon
from PySide6.QtNetwork import (QNetworkAccessManager, QNetworkReply,
                               QNetworkRequest)
from PySide6.QtWidgets import (QApplication, QComboBox, QHBoxLayout, QLabel,
                               QLineEdit, QListView, QListWidget, QMessageBox,
                               QPushButton, QTextBrowser, QVBoxLayout, QWidget)
from serial.tools.list_ports import comports

import serial_tool
>>>>>>> Stashed changes
class serial_list_combox(QComboBox):
    def __init__(self):
        super().__init__()

    def showPopup(self) -> None:
        self.update_port_list()
        return super().showPopup()

    def update_port_list(self):
        ser_port = self.currentText()
        print('curr ser_port',ser_port)
        self.clear()
        for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
            print(port, desc, hwid)
            self.addItem(desc)
            if ser_port == desc:
                #self.setCurrentIndex(n)
                self.setCurrentText(desc)
    
    def get_current_port(self):
        ser_port = self.currentText()
        #获取串口号 
        for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
            if ser_port == desc:
                return port
<<<<<<< Updated upstream
        return None                    


class serial_tool(QWidget):
    def __init__(self):
        super().__init__()
=======
        return None
        
class serial_tool_gui(QWidget):
    
   
    
    def __init__(self):
        super().__init__()
        self.ser_tool = serial_tool.Serial_tool()
>>>>>>> Stashed changes
        self.init_ui()
        self.port = None
        self.serial = None
        self.isopen = 0

    def init_ui(self):
        
        #选择串口
        self.isopen = 0
        
        # set icon

        self.setWindowIcon(QIcon('icons/serialport.png'))
        self.port_label = QLabel('serial:')
        self.port_label.setFixedWidth(30)

        self.port_list = serial_list_combox()
        self.update_port_list()


        #点击后更新串口列表
        #self.port_list.showPopup.connect(self.update_port_list)
        #self.port_list.currentTextChanged.connect(self.update_port_list)
        
        #self.port_edit.setReadOnly(True)
        self.port_button = QPushButton('open')
        #禁止连续点击
        self.port_button.setFixedWidth(60)
        self.port_button.setFixedHeight(30)
        self.port_button.setStyleSheet("QPushButton{background-color:rgb(255,255,255);border:1px solid rgb(0,0,0);border-radius:5px;}"
                                        "QPushButton:hover{background-color:rgb(0,0,0);color:rgb(255,255,255);}")
        self.port_button.setFont(QFont('Consolas', 10))
        self.port_button.setText('open')
<<<<<<< Updated upstream
        self.port_button.setToolTip('选择串口')
        self.port_button.setStatusTip('选择串口')
        self.port_button.setWhatsThis('选择串口')
=======
        self.port_button.setToolTip('select')
        self.port_button.setStatusTip('select')
        self.port_button.setWhatsThis('select')
>>>>>>> Stashed changes
        self.port_button.setShortcut('Ctrl+P')
        self.port_button.setShortcutEnabled(True)
        self.port_button.setIcon(QIcon('port.png'))
        #self.port_button.setIconSize(QSize(20, 20))
        #self.port_button.setCheckable(True)
        #self.port_button.setChecked(True)
        #self.port_button.setAutoRepeat(True)
        #self.port_button.setAutoRepeatDelay(100)
        #self.port_button.setAutoRepeatInterval(100)
        #self.port_button.setDefault(True)

        self.port_button.clicked.connect(self.port_button_clicked)

        
        self.setWindowTitle('serial')
        self.setGeometry(300, 200, 600, 400)
        self.setWindowIcon(QIcon('web.png'))

        self.button = QPushButton('Click me')
        self.button.clicked.connect(self.buttonClicked)
        
        self.text_browser = QTextBrowser()
        self.text_browser.setFont(QFont('Consolas', 10))
        #自动滚动
    


        self.line = QLineEdit()
        self.line.setText('AT#MY')
        #self.line.textChanged.connect(self.textChanged)
        self.cmd_list = QListWidget()
        self.cmd_list.addItem('AT#MY')
        self.cmd_list.addItem('AT#MY')
        self.cmd_list.addItem('AT#MY')
        self.cmd_list.addItem('AT#MY')
        self.cmd_list.setFixedWidth(200)
        # cmd list 间隔
        self.cmd_list.setSpacing(5)
        self.cmd_list.itemClicked.connect(self.cmd_list_clicked)

<<<<<<< Updated upstream
        self.layout_main = QHBoxLayout()
        self.layout = QVBoxLayout()

        self.layout1 = QHBoxLayout()
        self.layout1.addWidget(self.port_label)
        self.layout1.addWidget(self.port_list)
        self.layout1.addWidget(self.port_button)
=======
        self.layout_root = QHBoxLayout()
        self.layout = QVBoxLayout()

        self.layout_show = QHBoxLayout()
        self.layout_show.addWidget(self.port_label)
        self.layout_show.addWidget(self.port_list)
        self.layout_show.addWidget(self.port_button)
>>>>>>> Stashed changes
        
        
        self.layout2 = QHBoxLayout()
        self.layout2.addWidget(self.line)
        self.layout2.addWidget(self.button)
    
<<<<<<< Updated upstream
        self.layout.addLayout(self.layout1)
=======
        self.layout.addLayout(self.layout_show)
>>>>>>> Stashed changes
        self.layout.addWidget(self.text_browser)
        self.layout.addLayout(self.layout2)
        # self.layout.addWidget(self.line)
        # self.layout.addWidget(self.button)
<<<<<<< Updated upstream
        self.layout_main.addLayout(self.layout)
        self.layout_main.addWidget(self.cmd_list)

        self.setLayout(self.layout_main)
=======
        self.layout_root.addLayout(self.layout)
        self.layout_root.addWidget(self.cmd_list)

        self.setLayout(self.layout_root)
>>>>>>> Stashed changes
    
    def cmd_list_clicked(self):
        print('cmd_list_clicked')
        self.line.setText(self.cmd_list.currentItem().text())
        self.line.setFocus()
        self.line.selectAll()

    @Slot()
    def buttonClicked(self):
        line_text = self.line.text()
        line_text = line_text + '\r\n'

        timestamp = datetime.datetime.now().strftime('[%Y-%m-%d %H:%M:%S.%f]')
        self.text_browser.append(timestamp + ' [TX]\n' + line_text)
        print('line text:',line_text)
        self.ser.write(line_text.encode())

    @Slot(str)
    def textChanged(self, text):
        self.text_browser.append(text)

    @Slot()
    def update_port_list(self):
<<<<<<< Updated upstream
        self.port_list.clear()
        for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
            print(port, desc, hwid)
            self.port_list.addItem(desc)

            self.port_list.setCurrentIndex(n)
=======
        port_list = self.ser_tool.list_port()
        
        self.port_list.clear()
        for (port, desc, hwid) in port_list:
            print(port, desc, hwid)
            self.port_list.addItem(desc)

            #self.port_list.setCurrentIndex(n)
>>>>>>> Stashed changes
    
    @Slot()
    def port_button_clicked(self):
        print('port_button_clicked')
        if self.isopen == False:
            if self.open_serial_port() == True:
                self.isopen = True
                self.port_button.setText('close')
        else:
            self.isopen = False
            self.serial_rx_thread.join()
            self.ser.close()
            self.port_button.setText('open')
    
    def serial_rx_handler(self):
        
        print('serial_rx_handler %d' % self.isopen)
        while self.isopen:
            # read all that is there or wait for one byte
            try:
                data = self.ser.read(1024)  # serial.in_waiting
                if data:
                    # print('data',data)
                    text = data.decode(encoding='utf-8', errors='ignore')
                    timestamp = datetime.datetime.now().strftime('[%Y-%m-%d %H:%M:%S.%f]')
                    
                    print(timestamp, text)
                    #字体设置为红色
                    #self.text_browser.setTextColor(QColor(255, 0, 0))
                    self.text_browser.append(timestamp + ' [RX]\n')
                    #self.text_browser.setTextColor(QColor(0, 0, 0))
                    self.text_browser.append(text)
                    self.text_browser.moveCursor(self.text_browser.textCursor().End)
                    # for transformation in self.rx_transformations:
                    #     text = transformation.rx(text)
                    # timestamp=time.strftime('[%Y-%m-%d_%H:%M:%S.%f]',time.localtime())

                    # print(timestamp,end='')
                    # print(text)
                    # text = text.replace('\r\n', '\n')
                    # text = text.replace('\r', '\n')
                    # for ts in text.split('\n'):
                    #     if ts != '':
                    #         timestamp = datetime.datetime.now().strftime(
                    #             '[%H:%M:%S.%f]')  # [%Y-%m-%d_%H:%M:%S.%f]
                    #         print(timestamp, ts)
                    #         self.text_browser.append(timestamp + ' ' + ts)

            except KeyboardInterrupt:
                break

    def open_serial_port(self):
        ser_port_desc = self.port_list.currentText()
        ser_port = None
        #获取串口号 
        for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
            if ser_port_desc == desc:
                ser_port = port
                break
        if ser_port != None:
            print('opene serial protr %s' % port)
            self.ser = serial.Serial(ser_port, 115200, timeout=0.02)
            self.serial_rx_thread = threading.Thread(target=self.serial_rx_handler)
            self.serial_rx_thread.start()
            return True
        return False

    def closeEvent(self, event):
        self.isopen = False
        self.ser.close()
        sys.exit(0)

if __name__ == "__main__":

    #创建窗口
    app = QApplication(sys.argv)
    
<<<<<<< Updated upstream
    mywidget = serial_tool()
    mywidget.show()
    
    app.exec()
    #win.setWindowFlags(Qt.FramelessWindowHint)
=======
    mywidget = serial_tool_gui()
    mywidget.show()
    
    app.exec()
    #win.setWindowFlags(Qt.FramelessWindowHint)
>>>>>>> Stashed changes
