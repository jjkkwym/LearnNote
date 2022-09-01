#!/usr/bin/env python

import serial
from serial.tools.list_ports import comports
import threading
import time
import datetime
import parse_config



class serial_tool(serial.Serial):
    
    def __init__(self) -> None:
        super().__init__()
        self.baudrate = 115200
        self.timeout = 0
        self.port = '/dev/ttyUSB0'
        self.recv_thread = None
        self.is_alive = None
        #self.open_port()
    def open_port(self):        
        self.open()
        self.recv_thread = threading.Thread(target=self.recv_handler, name='recv')
        self.is_alive = True
        self.recv_thread.daemon = True
        self.recv_thread.start()
    def close_port(self):
        #锁定线程
        self.is_alive = False
        self.close()
        self.recv_thread.join()

    def recv_handler(self):
        print('rx start')
        unhandle_data = ''
        unhandle_data_timeout_count = 0
        while self.is_alive:
            data_in_waiting = self.in_waiting
            if self.in_waiting:
                data = self.read(1024)
                if data:
                    timestamp = datetime.datetime.now().strftime('[%Y-%m-%d %H:%M:%S.%f]')
                    #print(timestamp,'rx raw data:',data)
                    data = data.decode('utf-8')

                    if unhandle_data != '':
                        data = unhandle_data + data
                        #print('merge data:',data)
                        unhandle_data = ''
                    #timestamp = datetime.datetime.now().strftime('[%Y-%m-%d %H:%M:%S.%f]')
                    #print(timestamp,end=' ')                    
                    split_data : str 
                    split_data = data.split('\r\n')
                    
                    split_data_len = len(split_data)
                    #print('split data: ',split_data)
                    for i in range(split_data_len - 1):
                        timestamp = datetime.datetime.now().strftime('[%Y-%m-%d %H:%M:%S.%f]')
                        
                        self.at_cmd_handler(split_data[i])                        
                        print(timestamp,split_data[i])
                    if split_data[-1] == '':
                        unhandle_data = ''
                        #print('revc data end with CR LF')
                    else:
                        unhandle_data = split_data[-1]
                        unhandle_data_timeout_count = 5
            else:
                if unhandle_data != '':
                    timestamp = datetime.datetime.now().strftime('[%Y-%m-%d %H:%M:%S.%f]')
                    unhandle_data_timeout_count -= 1
                    print(timestamp,'unhandle_data_timeout_count:',unhandle_data_timeout_count)
                    if unhandle_data_timeout_count == 0:
                        print(timestamp,'unhandle_data timeout,data:',unhandle_data)
                        unhandle_data = ''
            time.sleep(0.01)

    def list_port(self):
        
        self.serial_port_list = sorted(comports())

        for port, desc, hwid in self.serial_port_list:
            print("{}: {} [{}]".format(port, desc, hwid))

    def send_at_cmd(self,cmd,params=None):
        data = ''
        if params == None:
            data = 'AT+B %s\r\n' % cmd
        else:
            data = 'AT+B %s %s\r\n' % (cmd,params)
        print('tx data: ',data)
        self.write(data.encode('utf-8'))

    def at_cmd_parser(self,data : str):
        if data:
            parse_data = data.split(' ',maxsplit = 2)
            parse_data_len = len(parse_data)
            
            if parse_data_len < 3:
                params = ''
            elif parse_data_len == 3:
                params = parse_data[2].split(',')
            
            if parse_data[0] == 'AT-B':
                cmd = parse_data[1]
            else:
                cmd = ''
                params = ''

            return cmd,params

    def at_cmd_executor(self,cmd : str,params):
        if cmd == 'A2DPSTAT':
            if config.target_addr == params[1]:
                a2dpstat = params[0]
        elif cmd == 'AGSTAT':
            #print(cmd,params)
            if params[1] == config.target_addr and params[0] == '2':
                self.send_at_cmd('A2DPDISC')
        elif cmd == 'ACLDISC':
            if params[1] == config.target_addr:
                #test_count += 1
                print('acl disc')
                #self.send_at_cmd('A2DPCONN',config.target_addr)

    def at_cmd_handler(self,data):
        cmd,params = self.at_cmd_parser(data)

        # print('cmd:',cmd)
        # if params != '':
            # print('params:',params)
        
        self.at_cmd_executor(cmd,params)   

if __name__ == "__main__":
    ser_tool = serial_tool()
    print(ser_tool.baudrate)
    
    config = parse_config.parse_config()
    print(config.target_addr)
    while True:
        opcode = input()
        if opcode == '1':
            ser_tool.list_port()
        elif opcode == '2':
            ser_tool.open_port()
        elif opcode == '3':
            ser_tool.close_port()
        elif opcode == '4':
            ser_tool.write('AT+B GPRL\r\n'.encode('utf-8'))
        elif opcode == '5':
            ser_tool.send_at_cmd('INQU','2')
        elif opcode == '6':
            ser_tool.send_at_cmd('A2DPCONN',config.target_addr)
        elif opcode == 'CONN':
            ser_tool.send_at_cmd('A2DPCONN',config.target_addr)
        elif opcode == 'DISC':
            ser_tool.send_at_cmd('A2DPDISC')
        elif opcode == 'START':
            ser_tool.send_at_cmd('A2DPSTART')
        elif opcode == 'SUSPEND':
            ser_tool.send_at_cmd('A2DPSUSPEND')
        elif opcode == 'CLOSE':
            ser_tool.send_at_cmd('A2DPCLOSE')
        elif opcode == 'GLBD':
            ser_tool.send_at_cmd('GLBD')
        elif opcode == 'GPRL':
            ser_tool.send_at_cmd('GPRL')
        elif opcode == 'DPRD':
            ser_tool.send_at_cmd('DPRD','00000000000000')
        elif opcode == 'INQU':
            ser_tool.send_at_cmd('INQU','2')
        elif opcode == 'AGCONN':
            ser_tool.send_at_cmd('AGCONN',config.target_addr)
        elif opcode == 'AGDISC':    
            ser_tool.send_at_cmd('AGDISC')
        
        time.sleep(0.01)

        """ time.sleep(5)
        ser_tool.list_port()
        if flag == 1:
            ser_tool.close_port()
            flag = 0
            print('close port')
        else:
            ser_tool.open_port()
            flag = 1
            ser_tool.write('AT+B GPRL\r\n'.encode('utf-8'))
            print('open port')            
        print('app heartbeat') """