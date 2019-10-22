"""
将会自动根据平台选择使用select,poll或者epoll
使用方式与epoll保持一致，首先实例化一个SEpoll对象，然后注册文件描述符
每一个socket都应该被设置为非阻塞的
然后事件类型不可设置，都被设置为了可读事件和错误事件
取消也使用unregister
等待和epoll一致，调用poll方法，返回值只包含了可读socket的文件描述符，不包含event

"""

import select

__all__ = ["SEpoll"]


class SEpoll:
    def __init__(self) :
        """
        此处决定使用哪种方法
        检验name可得知,未知平台name=-1
        """
        if "epoll" in dir(select) :
            print("OS of this computer could use epoll...")
            self.platform = "linux"
            self.selector = select.epoll()
            self.name = "epoll"
        elif "poll" in dir(select) :
            print("OS of this computer could only use poll...")
            self.platform = "ios"
            self.selector = select.poll()
            self.name = "poll"
        elif "select" in dir(select) :
            print("OS of this computer use select...")
            self.platform = "win"
            self.selector = -1
            self.name = "select"
        else :
            self.platform = 'unknow'
            self.selector = -1
            self.name = -1
            print("Can not find select, poll or epoll, please stop !!!!!!")
        self.read_list = []
        self.erro_list = []

    def register(self, fd) :
        """
        注册事件
        """
        if self.platform=="win" :
            self.read_list.append(fd)
            self.erro_list.append(fd)
        elif self.platform=="linux" :
            self.selector.register(fd, select.EPOLLIN | select.EPOLLRDHUP)
        elif self.platform=="ios" :
            self.selector.register(fd, select.POLLIN | select.POLLRDHUP)

    def poll(self) :
        if self.platform=="win" :
            r_list, w_list, erro_list = select.select(self.read_list, [], self.erro_list)

            return r_list, erro_list
        elif self.platform=="linux" :
            event_list = self.selector.poll()
            r_list = []
            erro_list = []
            for fd, event in event_list :
                if event==select.EPOLLIN :
                    r_list.append(fd)
                elif event==select.EPOLLRDHUP :
                    erro_list.append(fd)
        elif self.platform=="ios" :
            event_list = self.selector.poll()
            r_list = []
            erro_list = []
            for fd, event in event_list :
                if event==select.POLLIN :
                    r_list.append(fd)
                elif event==select.POLLRDHUP :
                    erro_list.append(fd)
        return r_list, erro_list

    def unregister(self, fd) :
        if self.platform=="win" :
            self.read_list.remove(fd)
            self.erro_list.remove(fd)
        else :
            self.selector.unregister(fd)


if __name__ == '__main__':

    import socket

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setblocking(False)
    server.bind(('0.0.0.0',6000))
    server.listen(10)

    watcher = SEpoll()
    watcher.register(server)

    client_record = {}

    while True :
        read_list, error_list = watcher.poll()
        for s in read_list :
            if s is server :
                client, client_address = s.accept()
                client.setblocking(False)
                watcher.register(client)
                client_record[client] = client_address
                print("get new client", client_address)

            else :
                data = s.recv(1024)
                if data == b'' :
                    print(client_record[s], "empty data")
                    watcher.unregister(s)
                    client_record.pop(s)
                else :
                    print(client_record[s], data)
        for s in error_list :
            print(client_record[s], "error happend")
            watcher.unregister(s)
            client_record.pop(s)