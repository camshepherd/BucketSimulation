#include "WaterPacket.h"
#include <iostream>

WaterPacket::WaterPacket()
{
	//default constructor 
	//can be used after declaration 
	backpos, backspeed, frontpos, frontspeed = 0;
}

WaterPacket::WaterPacket(long double  arg_timestep, long double  arg_volume, std::vector<long double >* arg_ptr_vec_ratesofflow, long double  arg_gravity = 9.81)
{
	//standard constructor
	//sets initial front values to 1 step forward
	//sets initial back variables to -1 to indicate that the WaterPacket has not been moved on yet and is a new instance 
	setTimeStep(arg_timestep);
	volume=fabs(arg_volume);
	ptr_vec_ratesofflow=arg_ptr_vec_ratesofflow;
	setGravity(arg_gravity);
	backpos = -1.0;
	frontpos = 0 ;
	backspeed = -1.0;
	frontspeed = 0;
}

WaterPacket::~WaterPacket()
{
	//default destructor, no special deletion methods 
};

long double  WaterPacket::getBackPos()
{
	//gette for backpos 
	return backpos;
}

long double  WaterPacket::getFrontPos()
{
	//getter for frontpos 
	return frontpos;
}

long double  WaterPacket::getBackSpeed()
{
	//getter for backspeed 
	return backspeed;
}

long double  WaterPacket::getFrontSpeed()
{
	//getter for frontspeed 
	return frontspeed;
}

long double  WaterPacket::getVolume()
{
	//getter for volume 
	return volume;
}

bool WaterPacket::setGravity(long double  arg_gravity)
{
	//setter for gravity 
	//if invalid set it to standard 9.81 
	if (fabs(arg_gravity) > 0)
	{
		gravity = fabs(arg_gravity);
		return true;
	}
	else
	{
		gravity = 9.81;
		return false;
	}
}

bool WaterPacket::setTimeStep(long double  arg_timestep)
{
	//sets local timestep 
	//if invalid set to a default of 0.01
	if (arg_timestep > 0.0)
	{
		timestep = arg_timestep;
		return true;
	}
	else
	{
		timestep = 0.01;
		return false;
	}
}

bool WaterPacket::moveOnStep(long double  arg_distance)
{
	//moves on a single step
	//uses suvat equations to increase pos and speed of front and back 
	//on construction backpos and backspeed are set to -1 but frontpos and frontspeed are moved on a step 
	//if it has just been made then only then will it have negative backpos and backspeed
	//so that when moved on backpos and backspeed will both be set to 0 
	if (backpos >= 0)
	{
		backpos += long double ((backspeed*timestep) + (0.5*(timestep*timestep* gravity)));
		frontpos += long double((frontspeed*timestep) + (0.5*(timestep*timestep* gravity)));
		frontspeed += (timestep*gravity);
		backspeed += (timestep*gravity);
	}
	else
	{
		backpos = 0;
		backspeed = 0;
	}
	
	//appends to WaterFall's ratesofflow itelf assuming that its volume is distibuted evenly over the length of the WaterPacket 
	
	if (frontpos > arg_distance)
	{
		if (backpos > arg_distance)
		{
			ptr_vec_ratesofflow->back() += volume / timestep;
			volume = 0;
			return true;
		}
		else
		{
			ptr_vec_ratesofflow->back() += (volume*((frontpos - arg_distance) / (frontpos - backpos)))/timestep;
			volume -= (volume*((frontpos - arg_distance) / (frontpos - backpos)));
			return true;
		}
	}
	//all waterpackets will append to ratesofflow then WaterFall will append to its destination based on its ratesoflow.back()
}