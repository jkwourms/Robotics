#include <ros/ros.h>
#include <minimal_nodes/serviceMsg.h>
#include <iostream>
#include <string>
#include <math.h>
#include <std_msgs/Float64.h>

static double in_amplitude;
static double in_frequency;
static double x_cmd = 0.0;
static double v_cmd = 0.0;
static double omega;
static double phase = 0.0;

bool callback(minimal_nodes::serviceMsgRequest& request, minimal_nodes::serviceMsgResponse& response) {
	ROS_INFO("callback activated");
	in_amplitude = request.amplitude;
	in_frequency = request.frequency;
	response.velocity = v_cmd;

	return true;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "service_commander");
	ros::NodeHandle nh;

	ros::init(argc, argv, "minimal_publisher"); // name of this node will be "minimal_publisher"
    	ros::Publisher my_publisher_object = nh.advertise<std_msgs::Float64>("vel_cmd", 1);

	ros::ServiceServer service = nh.advertiseService("send_amplitude_frequency", callback);
	ROS_INFO("Ready to calculate velocity.");

	
	while (ros::ok()) {
		ROS_INFO("whow");
		omega = in_frequency * 2.0 * M_PI;
		double dt = 0.01;
		ros::Rate sample_rate(1/dt);
		std_msgs::Float64 vel_pub;
		phase += omega * dt;
		if (phase > 2.0 * M_PI)
			phase -= 2.0 * M_PI;
		x_cmd = in_amplitude * sin(phase);
		v_cmd = omega * in_amplitude * cos(phase);

		vel_pub.data = v_cmd;

		//publish velocity 
		my_publisher_object.publish(vel_pub);

		ros::spinOnce();
		sample_rate.sleep();
	}

	

	return 0;
}
