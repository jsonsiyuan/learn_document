# 蓝牙规范 #

参考网站：
	https://developer.aliyun.com/article/752526?spm=a2c6h.12873581.0.dArticle752526.3609589dyf4mWN&groupCode=genieaiot

![avatar](./pic/1.png)

1. 核心规范：Core Specifications，定义了蓝牙技术最核心的内容。覆盖了从物理层一直到传输层的内容。
2. Protocol规范： Protocol Specfications，在核心规范之上针对某一大类场景(例如音视频传输，线缆通信传输，网络通信传输)的数据通信需求来定义的传输协议，属于应用层协议，只在经典蓝牙中存在。
3. Profile规范：包含经典蓝牙的Traditional Profile Specifications和低功耗蓝牙的GATT Specifications。这类规范是针对某一个特定场景需求(例如听音乐，打电话)来对核心规范和protocol做出更细化的定义和对这些协议无法满足的一些细化需求做了补充协议。
4. 蓝牙mesh规范：Mesh Networking Specifications，这是蓝牙最新的mesh规范。只使用了低功耗蓝牙的还有就是一个需要注意的地方就是预分配序号：Assigned Numbers，蓝牙组织对某些字段的已经分配的数据定义，例如公司名，广播报文类型等等，都在这里可以查到。

![avatar](./pic/2.png)

- 蓝牙是工作在频率为2400MHz到2483.5MHz的无线通信协议，总共有83.5MHz的带宽资源。
- 在经典蓝牙的定义里，将这83.5MHz总共分为80个频道，每个频道是1MHz带宽，蓝牙连接管理是用连接管理协议(Link Manager Protocol LMP)。
- 而在低功耗蓝牙里，空中只有40个频道，每个频道是2MHz带宽，连接管理使用的是连接层(Link Layer)，空中数据包的结构也完全不同。
- 我们可以看到，Controler部分的功能完全是两个独立的路径，也就是说，经典蓝牙和低功耗蓝牙的controller可以独立存在，互相不依赖，所以目前市面上有只支持经典蓝牙的芯片，也有只支持低功耗蓝牙芯片，当然，也有两种蓝牙模式共存的芯片。
- 在Host端，经典蓝牙和低功耗蓝牙的设计思路也不一样，在经典蓝牙协议里，在逻辑链路控制与适配协议层(Logical Link Control and Adaptation Protocol L2CAP)之上，还根据不同的应用场景定义了不同的传输协议，例如RFCOM， AVDTP，AVCTP，在不同的传输协议之上才定义了不同的Profile，层次结构比较复杂，开发人员学习成本高。而低功耗蓝牙就比较简单，只定义了一个属性协议(Attribute Protocol ATT)，基于属性协议定义了一个通用属性场景规范(Generic Attribute Profile GATT)和其他的针对特定业务的场景规范(Profile)，开发起来比较简单，整体框架也比较容易实现私有场景的开发。
- 蓝牙mesh虽然使用了低功耗蓝牙的广播报文和GATT，但可以算是一个半独立模块，蓝牙mesh构建了自己的一套网络寻址和数据传输机制，而且在mesh的协议文档里也强烈推荐使用广播承载(ADV Bearer)的方式而不是GATT承载(GATT Bearer)。