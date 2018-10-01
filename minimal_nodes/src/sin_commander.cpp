#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <math.h>
#include <iostream>

#define _USE_MATH_DEFINES

int main(int argc, char **argv) {
	ros::init(argc, argv, "sin_commander");
	ros::NodeHandle n;
	ros::Publisher my_publisher = n.advertise<std_msgs::Float64>("vel_cmd", 1);
	std_msgs::Float64 vel_pub;
	double frequency, amplitude, vel_cmd, dt, omega, phase;
	phase = 0.0;
	dt = 0.01;
	std::cout << "Enter a frequency: ";
	std::cin >> frequency;
	std::cout << "Enter an amplitude: ";
	std::cin >> amplitude;
	
	omega = 2.0 * M_PI * frequency;
	ros::Rate rate(1/dt);

	while (ros::ok()) {
		phase += omega * dt;
		if (phase > 2.0 * M_PI) {
			phase -= 2.0 * M_PI;
		}
		vel_cmd = omega * amplitude * std::cos(phase);
		vel_pub.data = vel_cmd;
		my_publisher.publish(vel_pub);
		rate.sleep();
	}
}
