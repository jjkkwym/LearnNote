#!/usr/bin/python
import json

data_de = { 'target_addr' : '20011500D5AF', 'b' : 2, 'c' : 3, 'd' : 4, 'e' : 5 }

# data2 = json.dumps(data,indent=4)
# print(data2)
# 
with open('config.json','r') as f:
    data = f.read()
    f.close()

data_parse = json.loads(data)
#print(data_parse)


class parse_config(object):
    def __init__(self) -> None:
        with open('config.json','r') as f:
            data = f.read()
            f.close()

        data_parse = json.loads(data)
        print(data_parse)
        self.target_addr = data_parse['target_addr']
        self.serial_setting = data_parse['serial_setting']
        self.baudrate = self.serial_setting['baudrate']
        #print(self.target_addr)
    # def target_addr(self):
        # return self.target_addr