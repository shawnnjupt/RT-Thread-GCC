# rt-thread-pro（gcc移植，非arm)

![image-20230411223407545](D:\code\mcu\stm32\rt-thread-pro\assets\image-20230411223407545.png)

![image-20230411223340890](D:\code\mcu\stm32\rt-thread-pro\assets\image-20230411223340890.png)

#### 介绍
rt-thread的移植

硬件平台：CT117E-M4（stm32g431rbt6)

编译链：GCC

IDE : Clion/vscode

#### 软件架构
RT-THREAD nano core

组件：finsh

hal_driver

#### 说明

##### 1.关闭finsh

注释掉rtconfig.h里面

![image-20230411222034566](D:\code\mcu\stm32\rt-thread-pro\assets\image-20230411222034566.png)

##### 2.主函数为application.c里面的main.c

##### 3.cubemx生成代码的话注意将生成的 int main(void)删除



#### GCC移植注意：

##### 1.修改startupxxxxxx.s里面的初始化跳转函数

![image-20230411222409967](D:\code\mcu\stm32\rt-thread-pro\assets\image-20230411222409967.png)

原因为GNUC跳转的是  **entry** 非arm里面的 **$Sub$$main**

![image-20230411222535147](D:\code\mcu\stm32\rt-thread-pro\assets\image-20230411222535147.png)

##### 2.如要增加finsh组件，那么链接文件.ld里面添加

![image-20230411222758293](D:\code\mcu\stm32\rt-thread-pro\assets\image-20230411222758293.png)

#### 运行截图

![image-20230411223147877](D:\code\mcu\stm32\rt-thread-pro\assets\image-20230411223147877.png)
