/*
	SharpIR

	Arduino library for retrieving distance (in cm) from the analog GP2Y0A21Y and GP2Y0A02YK

	From an original version of Dr. Marcal Casas-Cartagena (marcal.casas@gmail.com)

	Version : 1.0 : Guillaume Rico

	https://github.com/guillaume-rico/SharpIR

*/

#ifndef SharpIR_h
#define SharpIR_h

#define NB_SAMPLE 50

#include "Arduino.h"
#include <assert.h>
#ifdef ROS_USED 
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#endif 
#ifndef ARDUINO_ARCH_AVR
#include "WMath.h"
#endif
//#include <sensor_msgs/Range.h>


class ZSharpIR
{

public:

	ZSharpIR(int irPin, const uint32_t _sensorType);
	int distance();
	int getAccuracy();
	static const uint32_t GP2Y0A41SK0F = 430;
	static const uint32_t GP2Y0A21YK0F = 1080;
	static const uint32_t GP2D12_24 = 1081;
	static const uint32_t GP2Y0A02YK0F = 20150;
	static const uint32_t GP2Y0A02 = 20150;
	static const uint32_t GP2Y0A710K0F = 100500;
	static const uint32_t CALIBRATED_SHORT = 1;
	static const uint32_t CALIBRATED_LONG = 2;
	static const uint32_t CALIBRATED = -1;

	int getMax();
	int getMin();
	int getRaw();
	int getIrPin();
	void setARefVoltage(int refV);
	void SetAnalogReadResolution(int res);

#ifdef ROS_USED 
	void setup(ros::NodeHandle  *myNodeHandle, const char   *	topic);
	void loop();
#endif 

	void CalibrateStart();
	void CalibrateNextStep();
	void ApplyCalibration(int atable[20]);

	void DisplayCalibration(Stream & Serial);

private:
	int compute(int ir_val);
#ifdef ROS_USED 
	ros::NodeHandle  *nh;
	sensor_msgs::Range range_msg;
	ros::Publisher *pub_range;
#endif
	int    _Adcres;
	int _refVoltage;

	int* sort(int a[], int size);

	int _irPin;
	int _indexZSharpIR;
	int table[20];
	uint32_t _model;
};

#endif
