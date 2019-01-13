#include "WaterFall.h"
#include "Bucket.h"
#include <iostream> 
#include <string> 
WaterFall::WaterFall()
{
	//default constructor
	distance = 0;
}

WaterFall::WaterFall(WaterEntity* arg_ptr_destination, std::string id, long double  arg_distance, long double  arg_timestep, long double  arg_gravity)
{
	//standard constructor, sets variables to those specified as arguments 
	setDistance(arg_distance);
	setId(id);
	setTimeStep(arg_timestep);
	setGravity(arg_gravity);
	setDestination(arg_ptr_destination);
}

WaterFall::~WaterFall()
{
	//default destructor 
};

bool WaterFall::setDistance(long double  arg_distance)
{
	//setter for distance 
	//DISTANCE BETWEEN LOWEST POINT OF HOLE OF BUCKET AND TOP OF NEXT BUCKET
	if (arg_distance >= 0)
	{
		distance = arg_distance;
		return true;
	}
	else
	{
		distance = 0;
		return false;
	}
}

long double WaterFall::getDistance()
{
	//getter for stored value of distance(not necessarily up to date) 
	return distance;
}

bool WaterFall::acceptVolume(long double  arg_volume)
{
	//creates a WaterPacket to 'take' the entire arg_volume and initialises said packet 
	//if volume is 0 do nothing 
	//if volume is invalid return false and do nothing 
	if (arg_volume > 0)
	{
		WaterPacket* newpacket = new WaterPacket(timestep, fabs(arg_volume), &(vec_ratesofflow), gravity);
		vec_waterpackets.push_back(std::unique_ptr<WaterPacket>(newpacket));
		return true;
	}
	else if (arg_volume == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool WaterFall::moveOnStep()
{
	//will move on a single timestep of the simulation based off of existing values 
	//will move on all WaterPackets which themselves append to the ratesofflow 
	//once ratesofflow for the particular time is finished, add volume to destination
	//then append to vec_volumes
	vec_ratesofflow.push_back(0);
	for (auto& iterator = vec_waterpackets.begin(); iterator < vec_waterpackets.end();)
	{
		iterator->get()->moveOnStep(distance+getExtraDistanceToFall());
		if (iterator->get()->getVolume() == 0)
		{
			iterator = vec_waterpackets.erase(iterator);
		}
		else
		{
			iterator++;
		}
	}
	ptr_destination->acceptVolume(vec_ratesofflow.back()*timestep);
	long double totalvolume = 0;
	//totalvolume is the total volume within the WaterFall
	for (auto& y : vec_waterpackets)
	{
		totalvolume += y->getVolume();
	}
	vec_volumes.push_back(totalvolume);
	return true;
	
}

long double  WaterFall::getExtraDistance()
{
	//needs to exist as this is a function included with WaterEntity
	//serves no useful purpose and should never be called 
	return long double (0);
}

long double  WaterFall::getExtraDistanceToFall()
{
	//getter for extradistancetofall
	//extradistancetofall is the distance to fall beyond the local variable distance 
	return ptr_destination->getExtraDistance();
}