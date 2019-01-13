#ifndef WATERFALL_H
#define WATERFALL_H
#include "WaterEntity.h"
#include "WaterPacket.h"
#include <memory>

//simulates the falling of water between two WaterEntitys 
//this water is composed of a number of WaterPackets which together simulate the total volume of water falling 

class WaterFall :public WaterEntity
{
public:
	WaterFall();
	WaterFall(WaterEntity* arg_ptr_destination,std::string id, long double  arg_distance, long double  arg_timestep, long double  arg_gravity);
	~WaterFall();
	long double  getDistance();
	bool moveOnStep();
	bool acceptVolume(long double  arg_volume);
	long double  getExtraDistanceToFall();
	bool setDistance(long double  arg_distance);
protected:
	long double  distance;
	long double  getExtraDistance(); 
	std::vector<std::unique_ptr<WaterPacket>> vec_waterpackets;
};

#endif