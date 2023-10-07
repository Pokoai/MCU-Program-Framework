## 各目录说明

- common 目录，其中 51config.h 为配置文件，设置外设参数以及为外设分配端口；head.h 声明项目需要的所有头文件以及进行全局类型定义；
- source 目录下存放所有源文件；
- include 目录存放相应源文件的头文件，向外提供各外设 API；
- app 目录存放 main.c 文件；
- project 是工程目录，建议把工程建到这个文件夹下；
- output 是输出目录，在 keil 中可以设置 hex 输出到此。

## 使用说明  

**各模块 API 请参考对应的 include 目录下的头文件**

## 注意

- 欢迎以同样思路**封装模块代码**，并提交上来，请尽量尊重本工程代码的风格

## 其他

### 去除函数未被调用的警告

1. Options -> Device -> √Use Extended Linker(LX51)instead of BL51
2. Options -> LX51 Misc -> Misc controls -> 填入REMOVEUNUSED 
