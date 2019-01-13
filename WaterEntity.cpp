#include "WaterEntity.h"
//pi is put in this file as WaterEntity.h is included in all files that would need acces to pi
//it does not seem worth it to make a new .h file just for pi
const long double  pi = long double (3.141592653);


//there are no complicated functions defined in this file since all complicated functions have specific functionality 
//related to the specific child of WaterEntity that has it
//WaterEntity only has generic functions defined that would be needed in all WaterEntitys
WaterEntity::WaterEntity(){};

WaterEntity::~WaterEntity()
{

};

bool WaterEntity::setDestination(WaterEntity* arg_ptr_destination)
{
	ptr_destination = arg_ptr_destination;
	return true;
}

WaterEntity* WaterEntity::getDestination()
{
	return ptr_destination;
}

long double  WaterEntity::getGravity()
{
	return gravity;
}

long double  WaterEntity::getTimeStep()
{
	return timestep;
}

bool WaterEntity::setGravity(long double  arg_gravity)
{
	if (fabs(arg_gravity) > 0)
	{
		gravity = fabs(arg_gravity);
		return true;
	}
	else
	{
		return false;
	}
}

bool WaterEntity::setTimeStep(long double  arg_timestep)
{
	if (fabs(arg_timestep) > 0)
	{
		timestep = fabs(arg_timestep);
		return true;
	}
	else
	{
		return false;
	}
}

std::string WaterEntity::getId()
{
	return id;
}

void WaterEntity::setId(std::string thing)
{
	id = thing;
}

long double WaterEntity::getRateOfFlowAtPosition(int pos)
{
	if (pos > vec_ratesofflow.size() - 1 || pos<0)
	{
		return 0;
	}
	else
	{
		return vec_ratesofflow[pos];
	}
}

long double WaterEntity::getVolumeAtPosition(int pos)
{
	if (pos>vec_volumes.size() - 1 || pos < 0)
	{
		std::cout << "ERROR: 706c " << std::endl;
		return 0;
	}
	else
	{
		return vec_volumes[pos];
	}
	return 1;
	
}