# yhs_driver


## 安装can驱动

### 1.进入工作空间并clone repo

`$ cd {workspace}/src`

`$ git clone https://github.com/skstudying/yhs_driver.git `



### 2.配置rc.local文件

查看/etc目录下有没有rc.local文件



**如果有**：

在rc.local文件的`exit 0`代码上方加入



    sleep 2
    sudo ip link set can0 type can bitrate 500000
    sudo ip link set can0 up



后进行保存



**如果没有：**

`$ cd {workspace}/src/yhs_driver/canConfig`

`$ sudo cp rc.local /etc`



### 3.设置can盒子usb权限



`$ cd {workspace}/src/yhs_driver/canConfig`



打开opencan.sh文件，将两处123456修改为你的电脑root密码，保存，然后执行

`$ sudo cp opencan.sh /opt/mnt`

`$ sudo cp opencan.rules /etc/udev/rules.d`

`$ sudo chmod 777 /etc/udev/rules.d/usbcan.rules`



### 4.重新拔插can usb, 看到RX和TX灯亮起就说明配置成功





## 运行yhs_driver

### 1.进入工作空间并编译

`$ cd {workspace}`

`$ catkin build `



### 2.运行launch文件

`$ source devel/setup.bash`

`$ roslaunch yhs_can_contrl yhs_can_control.launch`

如果输出"**>>open can deivce success!**" 则表示打开成功



### 3.确定can卡与底盘通信正常

`$ rostopic echo /ctrl_fb`

如果有消息显示表示通讯正常，如果没有则检查接线是否正确



### 4.发布话题让底盘运动

`$ rostopic pub -r 100 /ctrl_cmd yhs_can_msgs/ctrl_cmd`

后面的内容用tab键补全，注意角速度的单位是“角度/秒”



当然也可以直接发布“/cmd_vel” 来控制底盘运动



### 5.其他topic可以看doc目录下canTopic文档
