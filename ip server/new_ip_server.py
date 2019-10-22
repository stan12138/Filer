import socket
import select
import logging
import logging.config
from select_epoll import SEpoll
import time
import threading

import os
import sys
#是否要持久化数据？数据库？文件？抑或不持久化，直接存入字典，或者列表。需要一个时间戳，以保证在线设备是最新的

#是不是应该采用OOP
logging.config.fileConfig("stan.conf")
log = logging.getLogger("second")

def get_ip() :
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(("baidu.com", 80))
        ip = s.getsockname()[0]
        s.close()
    except :
        ip = "N/A"
    return ip

class IP_Server :
    def __init__(self, Max_Alive_Time=2*60) :
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setblocking(False)
        self.server.bind(('0.0.0.0',6000))
        self.server.listen(10)

        self.log = log

        self.max_alive_time = Max_Alive_Time

        self.client_record = {}

        self.send_lock = threading.Lock()

        self.poll = SEpoll()

        self.poll.register(self.server)

        log.info("ip server start bind in port 6000")

    def run(self) :
        broadcast_thread = threading.Thread(target=self.broadcast, daemon=True)
        listen_thread = threading.Thread(target=self.listen, daemon=True)
        
        listen_thread.start()
        broadcast_thread.start()

        while True :
            pass

        #每个工作线程都是守护线程,同时也不调用任意一个线程的join方法,而是通过主线程的
        #死循环不让主线程结束, 这样主线程就可以捕捉到ctrl-c来终止运行

    def broadcast(self) :
        while True :
            time.sleep(5)
            self.tell_other_device()
        
    def listen(self) :
        while True:
            read_list, erro_list = self.poll.poll()

            for s in read_list :
                if s is self.server :
                    client, client_address = s.accept()
                    if client in self.client_record :
                        pass
                    else :
                        client.setblocking(False)
                        self.client_record[client] = [client_address[0], time.time(), bytes(client_address[0], 'utf-8'), False]
                        # 客户端信息记录: (IP, 时间戳, message, 已报告)
                        self.poll.register(client)
                        print(client_address,'is on-line')
                        self.log.info("IP: %s, port: %s is on-line"%client_address)
                else :
                    try :
                        data = s.recv(1024)
                    except Exception as er :
                        self.log.info("!!!!!!recv data fail, IP: %s"%client_record[s][0]+er)
                        self.close_one_client(s)
                        self.tell_other_device()
                        
                    else :
                        if data.decode('utf-8') == 'off-line' :
                            self.log.info("%s is off-line"%self.client_record[s][0])
                            self.close_one_client(s)

                        elif self.check_report(data, s) :
                            #防止有人动手脚
                            self.client_record[s][2] = data + b'\n' + self.client_record[s][2]
                            self.client_record[s][1] = time.time()
                            self.client_record[s][3] = True
                            s.send(b'get')
                            self.log.info("recv report from %s (%s), and send get to it already"%(self.client_record[s][0], self.client_record[s][1]))
                        else :
                            """
                            据测试发现,如果客户端直接关闭了链接, 服务器会收到b''
                            """
                            self.log.info("!!!!data error, IP: %s, going to close"%client_record[s][0]+data)
                            self.close_one_client(s)
                        
                        self.tell_other_device()

            for s in erro_list :
                # print(s)
                self.log.info("!!!! error list, IP: %s, going to close"%client_record[s][0])
                self.close_one_client(s)
                self.tell_other_device()

    def close_one_client(self, s) :
        # if s.fileno()!=-1 :
            # 现在我并不清楚为什么会出现-1的socket
        self.send_lock.acquire()
        try :
            # print(self.client_record[s][1:], "off line")
            self.poll.unregister(s)
            self.client_record.pop(s)
            
        except Exception as er :
            self.log.info("!!!! error when close client, IP:%s"%self.client_record[s][0]+er)
            # print(er, list(self.client_record.keys()))

        s.close()
        self.log.info("close one client success")
        self.send_lock.release()




    def check_report(self,data, s) :
        try :
            data = data.decode('utf-8')
            data = data.split('\n')
        except Exception as er :
            self.log.error("%s send wrong format data, can't decode (%s) , error is %s , going to close"%(self.client_record[s][0], data, er))
            #self.close_one_client(s)
            return False
        if len(data)==2 and len(data[0])<40 and len(data[1])<20 :
            return True
        else :
            self.log.warning("%s send wrong message (%s), going to close"%(self.client_record[s][0], data))
            return False

    def tell_other_device(self) :
        self.send_lock.acquire()
        if len(self.client_record) > 1 :
            message = b""
            keys = list(self.client_record.keys())
            for client in keys :
                if time.time()-self.client_record[client][1] > self.max_alive_time :
                    self.log.info("client did not report for a long time, IP:%s, going close"%self.client_record[client][0])
                    self.poll.unregister(client)
                    self.client_record.pop(client)
                    client.close()
                elif self.client_record[client][3] :
                    message += self.client_record[client][2] + b'\n\n'

            for client in self.client_record.keys() :
                if self.client_record[client][3] :
                    new_message = message.replace(self.client_record[client][2]+b'\n\n', b'')
                    client.send(new_message)
                    # print(new_message)
        elif len(self.client_record) == 1 :
            for client in self.client_record :
                client.send(b'0')

        self.send_lock.release()

print("Server ip is :", get_ip(), "Server Port is : 6000")
Server = IP_Server()
Server.run()
