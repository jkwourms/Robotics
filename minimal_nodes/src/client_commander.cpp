#include <ros/ros.h>
#include <minimal_nodes/serviceMsg.h>
#include <iostream>
#include <string>
#include <std_msgs/Float64.h>

int main(int argc, char **argv) {
	ros::init(argc, argv, "client_commander");
	ros::NodeHandle nh;
	ros::ServiceClient client = nh.serviceClient<minimal_nodes::serviceMsg>("send_amplitude_frequency");
	minimal_nodes::serviceMsg service;
	//initialize variables in service message here
	double velocity = 0.0;
	double in_amplitude;
	double in_frequency;

	while (ros::ok()) {
		std::cout << std::endl;
		std::cout << "Enter an amplitude (0 to quit): ";
		std::cin >> in_amplitude;
		if (in_amplitude == 0) 
			return 0;
		service.request.amplitude = in_amplitude;

		std::cout << std::endl;
		std::cout << "Enter a frequency (0 to quit): ";
		std::cin >> in_frequency;
		if (in_frequency == 0) 
			return 0;
		service.request.frequency = in_frequency;

		//do something with frequency & amplitude
		if (client.call(service))
			std::cout << "The velocity is: " << service.response.velocity << std::endl;
		else {
			ROS_ERROR("Failed to call service send_amplitude_frequency");
			return 1;
		}
	}
	return 0;
}
