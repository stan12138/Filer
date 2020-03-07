## README

这是一个局域网内文件传输和短消息传输工具

工具包内包含了数个版本的客户端，以及一个ip server。其中ip服务器负责向各用户提供ip服务，每个客户端在工作的工程中均会首先向服务器汇报自己的ip地址，同时从ip服务器获取其他用户的ip地址。用户在得到ip之后将会直接在两个需要通信的客户端建立tcp连接，用户之间直接通过socket以tcp协议完成短消息和文件的收发。

### 文件内容

项目包含以下文件夹：

~~~
------build
    |
    --command line
    |
    --ip server
    |
    --ipad
    |
    --iphone
    |
    --Qt source code

~~~

- build文件夹提供最新版本的windows客户端，已完成编译
- command line文件夹提供一个命令行版本的工具，基于python3，用户需安装python3。同时提供了一个适用于windows的注册表，运行该注册表，将在用户的右键菜单添加复制当前文件路径功能，以便于文件的传输。
- ip server文件夹提供两个版本的ip服务器，分别是python命令行版本，和exe版本，前者需要python3环境，后者直接双击运行即可。使用者可自由选择。
- ipad文件夹提供适用于9.7英寸iPad的客户端，客户端为纯python版本，运行需要依赖iOS应用：Pythonista。提供了ui界面，以及共享菜单内运行功能。主文件是`File_transfer.py`
- iphone文件夹提供了适用于4英寸iPhone的客户端，同样依赖Pythonista，功能与文件构成类似于ipad版本。
- Qt source code文件夹提供了最新版本windows客户端的Qt源码

备注：之所以说两个iOS的客户端只适用于特定尺寸的设备是因为ui是专门为这种尺寸的设备设计的，感觉`Pythonista`的ui设计工具虽然不错，但似乎有些问题，也许是我用的不熟吧。。。

### 使用方法

这个工具只能在只适用于可直接通信的网络环境中的两个客户端之间，例如两个设备处于同一局域网内，或者同时处于公网。

ip服务器是必须的，它提供了设备之间互相发现的功能。用户应该首先运行ip服务器，服务器运行之后会首先给出自己所在的ip地址，以及工作端口。然后用户可以开始运行各客户端，在客户端的设置页面或者conf配置文件中填写ip服务器的ip地址和端口号。为方便起见，建议用户设置本设备的ID。

客户端的使用基本上遵循这样的流程：选择通信的对象，进入通信界面，开始通信。

选择通信对象之后，本客户端和对方的客户端会同时自动跳入通讯界面。

iPad与iPhone客户端可以通过文件夹窗口选择要传输的文件；命令行版本默认处于消息传输功能中，输入file，回车，进入文件传输功能，应该手动输入文件路径，或者直接粘贴使用右键菜单复制的文件路径；Qt版本支持直接拖拽文件进入界面和点击`+`选择文件的功能，已选择的文件路径会被自动填入消息输入框，点击发送即可，取消发送当前已选择的文件只需修改消息输入框的内容即可。

![qt_talk_page](image/qt_talk_page.png)

Qt版本在通信界面提供了`restart`功能，可以在不关闭应用的情况下重启通信。

![qt_set_page](image/qt_set_page.png)

特别的，针对Qt客户端，可能需要重新设置文件发送时延，发送时延应该与当前网络环境的网络带宽相匹配。一个合适的时延将不会在任务管理器中观察到客户端的内存占用持续上升。以`10MB/s`的网络带宽为参考，合适的时延应该是`50ms`。如果时延设置过小，将会在传输过大文件的过程中导致内存占用持续上升，当内存占用超过1GB时，客户端随时可能崩溃。



所以，从性能来讲，客户端的文件传输速度至多达到网络带宽上限。所以在传输大型文件的时候速度也不要希望能有多快。为避免过长的等待，以`10MB/s`的网络环境为例，`2GB`大小的文件大概是一个比较合理的建议尺寸上限。当然，只要网络带宽够大，传输时延设置合理，客户端并不会限制传输文件的大小(只要你愿意等)。

另外，Qt客户端使用时需要build文件夹下的所有文件，接收到的文件将自动储存在这个文件夹下的`inbox`文件夹中

### 未来

接下来，会继续进行功能的优化以及Qt客户端的美化，升级。未来还可能提供基于Kotlin的安卓客户端，以及基于Swift的iOS客户端.....



### 更新记录

`18.7.11`

提供一个新的版本，大概也是近期的最后一个版本了。这个版本修复了几个bug，同时也提供了几个新的功能。这个版本的使用细节见上述使用说明部分。

这个版本同样存在着很多的问题，当然也有很多似乎应该加上的功能，因为各种各样的原因没能加上，通信界面的美化调整估计也要遥遥无期了。

最新版本的源码处在一个十分混乱的状态，充斥着大量因为设计失误而没有必要存在的标志位，信号，槽，还有很多测试中使用的qDebug输出未注释掉，总之源码的状况相当糟糕。但是一般情况下，客户端应该不会出太大的问题。

意识到文件传输速度绝对不会超过网络带宽这个显而易见的事实之后，我受到了一些打击，感觉很难忍受如此慢的速度。所以，工具的功能定位大概要改一改了，改成什么呢？无惧网络环境，一般不断线？。。。大概也不见得吧。总而言之，这个工具似乎愈发的鸡肋了，可能只对我自己有意义吧。



`19.10.21`

竟然已经一年多了!!!长久以来,我其实挺依赖这个工具的, 使用频率还是相当高的. 但是现在, 我发现原本的设计存在相当多的问题, 在线设备的维护和更新存在相当严重的问题, 无论是服务器和客户端. 

(Ps. 其实我很怀疑离开学校之后, 我是不是还会依赖它, 毕竟, 我在学校的时间也只有几个月了)

最近在某些方面遭遇了非常严重的挫折和打击, 给自己找点事情忙一下, 也许可以转移一下注意力, 可能会感觉稍微好一点. 

今天, 我重新设计了IP服务器, 增加了若干新的特性, 例如设备生存周期, 信息存储结构, 工作流程, select等等, 基本上, 现在的IP服务器问题是比较少的, 比以前合理蛮多的.

但是, 现在, 问题主要在于客户端, 平心而论, 三种客户端的设计都存在非常多的问题, 例如工作协议和新的IP服务器不匹配, 都需要大量的修改. 然后另外一个非常糟糕的问题是, 三个客户端的代码设计都是一团乱麻, 几乎需要重写一遍, 我现在感觉有点头皮发麻, 都没信心能够完成.

问题:

~~~
ios 上面, 关闭UI似乎并无法彻底关闭socket, 然后服务器根本收不到断开的信息
~~~



19.10.26

最近一段时间，我每天都会上好几个小时处理这个工具的问题， 包括ip服务器和Qt客户端。主要准备做的东西是对于通信协议及通信流程做一些调整， 但是现在ip服务器还没有调整好，依旧小毛病不少，偶尔也会导致错误无法捕捉而崩溃，总之还不能使用。因为协议的调整幅度不算大，所以旧有的客户端实际上也能在新的服务器上工作， 但是缺陷就是新增特性几乎完全无效了。

对于客户端的修改是一个比较棘手的问题，因为相比服务器，具有GUI的客户端设计更为复杂，并且包含了Qt和python两套代码，旧有的设计都非常混乱，代码的组织以及信号传输体系也非常混杂。

现阶段我基本将Qt客户端重写了一遍，架构也基本重新设计了，现在包含了IP_Handler, TCP_Server和TCP_Client，以及Controller和UI五个大部分， 将信号与槽重新精简规范了一遍， 同时逻辑与界面分离设计，Controller统一接管通信逻辑，简化和界面之间的通信, 额外也提供了一个日志体系。这样，为后期将C++的UI设计全面转换为QML设计打下了基础，后期界面的美化与改版可能也会方便一些(虽然我还不知道怎么结合C++和QML), 但是现在新的客户端还无法使用, 因为组件之间的配合我还没有搞定, 各种小毛病也很多.







19.12.30 2:28

现在，我重新设计了一个tcp socket编程的模块，这个模块提供了一个服务器和客户端的基类，基于这个基类，可以比较简单的完成服务器和ip的设计，并且不需要考虑太多应用层协议的事情。

然后，作为一个测试和示例，我继承这两个基类，设计了一个Filer的新的服务器和客户端，他们的基本特性是：

~~~
客户端定时向服务器汇报自身信息，服务器不做回复，转而以定时广播的形式，向所有客户端广播合法在线设备(维持着连接，同时在按时向服务器汇报了信息)的信息
~~~

工作状况看起来蛮好的，可以比较快速的发现在线设备的更新，并且比较稳定。

也许我会尽快考虑完成基于新的应用层协议，以及设备汇报协议的Filer

最近也在尝试重新设计电脑端Filer的界面，尚不知何时可以完成。

![image-20200108212857831](images/image-20200108212857831.png)

(还有不到46个小时，19年就要结束了。元旦快乐。刚刚过去的这个晚上我还是蛮开心的。

2020年，听起来蛮科幻的，只是我依旧没有什么改变， Nothing change)



2020.1.8 21：26

欧科，关于服务器方面，我没有再做更多的内容。

这些天我一直在考虑关于新的UI的设计，学AI软件的使用，学习QML，以及到处看各种UI设计作品，提升自己的审美能力，So，今天晚上，我暂时拿出了一个新的版本的UI，不再是上面那种性冷淡风，如下：

![image-20200108213016727](images/image-20200108213016727.png)

这种设计会有更多的色彩，也会使用比较多的阴影效果，从而让界面显得更加立体。我还挺喜欢的。但是还有设置和通信两个界面，依旧完全没设计，主题风格虽然已经确定了，但是也未必就会简单很多。

对了，还有icon要设计。

在我的未来要做的清单里，也有设计一款APP的计划，而这个APP蛮可能就是Filer的。虽然不知道到什么猴年马月才能完成。




2020.1.9 21：06

今天首先大概做了以下设置界面的初步设计，效果如下：

![image-20200109210826315](images/image-20200109210826315.png)

这里继续延续大量的阴影效果，采用了一些胶囊，非对称的设计，也使用了一些算是撞色的方案吧，虽然这个配色并不成功。

设置界面还不算完成吧。但骨架基本上就这样了。

今天做的另外一件事情是，我终于把旧版的Filer(新版本遥遥无期)在Mac上编译通过了，虽然很丑，但是至少现在可以用它在win和mac之间传输文件了，蛮有用的对我而言。编译过程并非顺利，当然，详细问题笔记现在并不打算写，只是大概记录一下：

1. 原本没有设置背景色和字体颜色的所有组件，在Mac下都会出问题，基本上就是背景色会变成黑色，字体颜色变成白色，然后要注意微软雅黑Mac并没有。这些都要修复
2. server类在发送数据的时候，我写了一句free(data)之类的(当时c++学的太垃圾了，现在也是)，这个完全没有必要，在win上至少不会出问题，但是在mac上会直接导致程序crash
3. mac上文件拖拽发送的功能报废了
4. 配置文件的路径那里，源码写的有很严重的问题，应该通过QtCore里面的`QCoreApplication::applicationDirPath()`来获取应用程序的绝对路径，再拼接上配置文件的名字，否则Mac上将无法使用配置文件，无法修改和保存配置信息
5. Mac上的应用程序图标按照源码是无法起效的，需要使用`sips`工具从图标文件生成一个icns文件，然后再配置`ICON = myIcon.icns`
6. 分辨率问题，界面的按钮图标分辨率太低了，Mac上效果极差。进度条部件的默认样式也和win完全不同。

基本上，修复这些问题之后，至少能编译出来一个release，并且可以工作的版本。

2020.1.10 23：50

今天初步完成了UI的设计：

![image-20200110235117008](images/image-20200110235117008.png)



2020.2.24

肺炎疫情严重，开学被延迟，日期未定。

1月13日之前我在AI上基本完成了风格和上面的界面保持一致的APP，虽然我设计之中的新的网络通信模块应该是一个可以多连接的点对点模块，但是现在设计的界面依旧只能实现单点通信功能。

拖延许久，经历了在swift，ios编程，swiftui开发上面的长久挣扎，然后又花了许多时间处理论文和毕业相关的事情处理上，虽然现在依旧远未结束，但是最近这些日子始终沉不下心来开始毕业论文的写作，于是闲暇时间里重新捡起了已经几乎被忘光的QML，到今晚为止，终于搞定了无数的问题，完成了QML的UI设计的实现，现在的界面实现工作已经全部完成，界面剩余的工作也就只是一些微调工作，当然后端模块远未完成，所以也不着急着理清界面的接口。也许接下来这一部分会再次被放下。不知道毕业之前我是否能够完成新版软件的设计。

现在大概整理了一部分新学习到的QML的知识，会被合并进入Archive得Qt学习笔记中，更详细的整理工作会逐步完成。暂时就这样吧。



2020.3.1

对UI界面进行了小幅度的完善，主要包括：

- 在线设备列表(即：主页)使用ListView，为每个条目新增一个ToolTip提示，并为了优化滚动体验，设置了ToolTip得一些小特性
- 优化了聊天界面的气泡对话框效果，并加入抗锯齿效果

由于之前一直都是在Mac下做的界面设计和测试，今天将项目导入到了windows上重新测试了一遍，简直服了，界面几乎是一团糊，素材和图片估计要完全重新导出。windows对于高清显示的支持太差了



2020.3.5  20:59

今天基本完成了Qt版本的socket module的设计，然后在次基础上完成了IP handler，客户端通信部份也就顺其自然地完成了，现在只差完成最后的客户端通信协议的构建，然后后台部分就搞定了。



2020.3.8  01:21

终于调试完了后台，前两天搞定了通信协议的实现，但是万万没想到最后无论是Qt socket还是python socket都卡在了文件传输上了，遇到了巨多的问题，顺便也发现了原本的python socket module的设计问题。截止到刚才已经写完，也测试完了两个端的各自的收发效果。太晚了，来不及整理上传，明天再说。