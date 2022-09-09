#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>//

#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "geometry_msgs/Twist.h"
#include "tf/transform_broadcaster.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Twist.h"
#include "yhs_can_msgs/ctrl_cmd.h"
#include "yhs_can_msgs/io_cmd.h"
#include "yhs_can_msgs/ctrl_fb.h"
#include "yhs_can_msgs/lr_wheel_fb.h"
#include "yhs_can_msgs/rr_wheel_fb.h"
#include "yhs_can_msgs/lf_wheel_fb.h"
#include "yhs_can_msgs/rf_wheel_fb.h"
#include "yhs_can_msgs/io_fb.h"
#include "yhs_can_msgs/steering_ctrl_cmd.h"
#include "yhs_can_msgs/front_angle_free_ctrl_cmd.h"
#include "yhs_can_msgs/front_velocity_free_ctrl_cmd.h"
#include "yhs_can_msgs/rear_angle_free_ctrl_cmd.h"
#include "yhs_can_msgs/rear_velocity_free_ctrl_cmd.h"
#include "yhs_can_msgs/bms_fb.h"
#include "yhs_can_msgs/bms_flag_fb.h"
#include "yhs_can_msgs/steering_ctrl_fb.h"
#include "yhs_can_msgs/front_angle_fb.h"
#include "yhs_can_msgs/rear_angle_fb.h"


#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <string>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <geometry_msgs/Twist.h>


float cmd_linear=0,cmd_angular=0;
uint8_t yhs_gear_on = 06,yhs_gear_off=00;
yhs_can_msgs::ctrl_cmd yhs_cmd;

void cmdvelCallBack(const geometry_msgs::Twist& cmd_vel){
	cmd_linear=cmd_vel.linear.x;
	cmd_angular=cmd_vel.angular.z;
	ROS_INFO("cmd_vel : %f %f",cmd_linear,cmd_angular);
}

//主函数
int main(int argc, char ** argv)
{	
	ros::init(argc, argv, "cmdvel2yhs");
	ros::NodeHandle nh;
	ros::Subscriber cmd_sub = nh.subscribe("cmd_vel", 1000, cmdvelCallBack);
	ros::Publisher ctrl_cmd_pub = nh.advertise<yhs_can_msgs::ctrl_cmd>("ctrl_cmd",5);

	ros::Rate loop(100);
	while(ros::ok())
	{
		if(fabs(cmd_linear)<1.5){
			yhs_cmd.ctrl_cmd_gear = yhs_gear_on;
			yhs_cmd.ctrl_cmd_linear = cmd_linear;
			yhs_cmd.ctrl_cmd_angular = 180.0/3.141592*cmd_angular;
			yhs_cmd.ctrl_cmd_slipangle = 0;
			//ROS_INFO("%f %f \n",yhs_cmd.ctrl_cmd_linear,yhs_cmd.ctrl_cmd_angular);
			ctrl_cmd_pub.publish(yhs_cmd);
		}

		ros::spinOnce();   
		loop.sleep();
	}


	return 0;
}
