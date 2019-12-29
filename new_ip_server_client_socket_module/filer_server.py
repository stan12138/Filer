from server import Server
import time
import threading

class MyServer(Server): 
    def __init__(self, ip, port): 
        Server.__init__(self, ip, port)
        self.info_record = {}

    def run(self): 
        listen_thread = threading.Thread(target=self._listen, daemon=True)
        report_thread = threading.Thread(target=self.broadcast, daemon=True)


        listen_thread.start()
        report_thread.start()

        while True: 
            pass

    def broadcast(self): 
        while True:
            now = time.time()
            broadcast_message = ""
            remove_key = []
            for message in self.info_record: 
                if message in self.messenger and now-message.recv_time<=5:
                    broadcast_message += self.info_record[message] + ";"
                else: 
                    remove_key.append(message)

            broadcast_message = broadcast_message[:-1]

            self._broadcast({"TP":"broadcast"}, broadcast_message.encode("utf-8"))

            for message in remove_key: 
                try: 
                    self.info_record.pop(message)
                except: 
                    pass

            print(self.info_record)

            time.sleep(5)



    def process_read(self, message): 
        if message in self.info_record :
            self.info_record[message] = message.header["PT"]+","+message.header["ID"]+","+message.addr[0]
        else :
            self.info_record[message] = message.header["PT"]+","+message.header["ID"]+","+message.addr[0]



if __name__ == '__main__':
    server = MyServer("0.0.0.0", 63335)
    server.run()