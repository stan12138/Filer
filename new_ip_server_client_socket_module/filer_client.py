from client import Client
import threading
import time

class MyClient(Client):

    def __init__(self, ip, port, ID, myport): 
        Client.__init__(self, ip, port)

        self.id = ID
        self.myport = myport 

    def run(self): 
        listen_thread = threading.Thread(target=self._listen, daemon=True)
        report_thread = threading.Thread(target=self.report, daemon=True)


        listen_thread.start()
        report_thread.start()

        while True: 
            pass

    def update_info(self, ID, myport): 
        self.id = ID
        self.myport = myport

    def report(self): 

        while True: 
            header = {"ID":self.id, "PT":self.myport}
            self.messenger.send(header)
            time.sleep(4)

    def process_read(self, message): 
        print(message.header, message.content)
        s = message.content.decode("utf-8")
        s = s.split(";")
        res = []
        for item in s: 
            port, ID, IP = item.split(",")
            res.append((IP, ID, int(port)))

        print(res)


if __name__ == '__main__':
    
    client = MyClient("127.0.0.1", 63335, "C1", 63334)
    client.run()