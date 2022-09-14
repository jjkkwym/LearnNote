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
        self.update_config()

    def update_config(self):
        with open('config.json','r') as f:
            data = f.read()
            f.close()

        self.data_parse = json.loads(data)
        self.target_addr = self.data_parse['target_addr']
        self.serial_setting = self.data_parse['serial_setting']
        self.baudrate = self.serial_setting['baudrate']
        self.cmd_list_size = len(self.data_parse['cmd_list'])
        self.cmd_list = self.data_parse['cmd_list']
        #print(self.target_addr)
    def print_parse(self):
        print(self.data_parse)
        cmd_list_size = len(self.data_parse['cmd_list'])
        for i in range(cmd_list_size):
            print(self.data_parse['cmd_list'][i]['cmd'])                    
            print(self.data_parse['cmd_list'][i]['params'])                    
        # return self.target_addr

    def search_cmd_list(self,cmd):
        for i in range(self.cmd_list_size):
            print(self.data_parse['cmd_list'][i]['cmd'])                    
            print(self.data_parse['cmd_list'][i]['params'])                    
            if cmd == data_parse['cmd_list'][i]['cmd']:
                return data_parse['cmd_list'][i]['cmd'],data_parse['cmd_list'][i]['params']
        return None

if __name__ == '__main__':
    config = parse_config()
    config.print_parse()

