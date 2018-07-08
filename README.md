## README

这是一个局域网内文件传输和短消息传输工具



### 文件结构

同时提供iPhone端，iPad端，命令行版本，windows版本客户端以及IP Server

其中，build文件夹为windows客户端编译完成的版本，Qt source code是windows客户端的Qt源代码，上述内容基于C++

另外，command line是命令行版本，同时提供了一个用于在windows下添加右键复制路径功能的注册表。这个版本基于python3，需要安装python才能使用

ip server是服务器，提供向各个客户端接收和发送ip地址的功能。上述所有传输工具的使用必须建立在服务器已经运行的条件下。服务器同样基于python，需要安装python。

ipad和iphone分别是ipad和iphone的客户端，同样基于python构建。这两个客户端建立在iOS应用pythonista的基础上，使用者必须安装pythonista才能使用。



### 使用方法

首先，需要运行ip server中的`ip_server.py`，直接在命令行下运行`python ip_server.py`命令即可，服务器默认运行在6000端口。

建议提供一个长时间开机的设备，可以一直运行这个ip server服务。

然后就可以根据情况启用不同的客户端，客户端需要根据情况指定ip服务器的ip地址和端口号。



### 未来

接下来，会继续进行功能的优化以及Qt客户端的美化，升级。未来还可能提供基于Kotlin的安卓客户端，以及基于Swift的iOS客户端.....