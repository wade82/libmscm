
　　　　　　　　　　     LIBMSCM
====
　　　　　　　　　　　　　　Author: wade
----
　　　　　　　　　 E-mail: wei.zhang@genetalks.com
----
Middleware for Message publishing/subscribing.

用于无人系统中消息发布订阅的中间件，数据格式采用json字符串。集成了[RapidJson](http://rapidjson.org/)在include中。目前已封装了LCM。ROS和DDS还未实现。
消息的通道称为channel（ROS中称为topic）


## Source Code Directory
```
.
│── /bin/            # executable files of the example
│── /example/        # example codes
│── /include/        # header files for user applications
│── /lib/            # libs generated
│── /Makefile        # script for build
│── /obj/            # object files
│── /READEME.md      # This file
└── /src             # source codes of this lib
```

## Requirements

* [LCM](http://lcm-proj.github.io/)


## Getting Started
编译

```shell
$ cd libmscm
$ make
```

将include和lib放在自己的工程中，或在编译时指定其路径。

## API

已定义的处理器类型

- LCM
- ROS
- DDS

类及接口

* **CMessageHandlerFactory** 工厂类，生产具体的消息处理器

|   function  |      description      |
|:-------------|:---------------------|
|CreateMessageHandler|创建消息处理器|


* **CMessageHandler**

|   function  |      description      |
|:------------|:---------------------|
| init        | 初始化   | 
| publish     | 发布消息 |
| subscribe   | 订阅消息 |
| unsubscribe | 取消订阅 |
| spin        | 循环消息回调处理 |
| spinOnce    | 单次消息回调处理 |
| getData     | 获取最新数据，json字符串 |

