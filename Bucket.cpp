#include "Bucket.h"
#include <iostream> 
#include <string>
#include <math.h>

//everything in Bucket is in units metres or seconds or a positive power of each(m^3 or ms^4 but not m^-2)

Bucket::~Bucket()
{
	//default destructor onl needs to be declared as there are no special deletion methods
};

Bucket::Bucket(){};//default constructor 

Bucket::Bucket(WaterEntity* arg_ptr_destination, std::string id, long double  arg_volume, long double  arg_alpha, long double  arg_height, long double  arg_radius, long double  arg_holeradius, long double  arg_holeheight, HolePosition arg_holeposition,long double  arg_timestep,long double  arg_gravity)
{
	//constructor that is required for the instance to be of any use
	//this will set the new bucket's settings to the ones sepecified by the user as arguments in the function
	setDestination(arg_ptr_destination);
	setId(id);
	vec_volumes.push_back(fabs(arg_volume));
	setAlpha(arg_alpha);
	setHeight(arg_height);
	setRadius(arg_radius);
	setHolePosition(arg_holeposition);
	
	setHoleRadius(arg_holeradius);
	setHoleHeight(arg_holeheight);
	
	setTimeStep(arg_timestep);
	setGravity(arg_gravity);
}

bool Bucket::setAlpha(long double  arg_alpha)
{
	//simple setter for the bucket 
	//alpha is allowed to be between 0 and 1
	if (fabs(arg_alpha) > 0 && fabs(arg_alpha) <= 1)
	{
		alpha = fabs(arg_alpha);
	}
	return true;
}

bool Bucket::setHeight(long double  arg_height)
{
	//simple setter for height
	if (arg_height > 0)
	{
		height = arg_height;
		return true;
	}
	else
	{
		return false;
	}
}

bool Bucket::setRadius(long double  arg_radius)
{
	//setter for radius
	if (arg_radius > 0 )
	{
		radius = arg_radius;
		return true;
	}
	else
	{
		return false;
	}
}

bool Bucket::setHoleHeight(long double  arg_holeheight)
{
	//#######HOLERADIUS AND HEIGHT MUST ALREADY BE INITIALISED FOR THIS TO VALIDATE HOLEHEIGHT PROPERLY#########
	if (holeposition==HolePosition::Side)
	{
		if (arg_holeheight + (holeradius) > height)
		{
			holeheight = height - (holeradius);
			return false;
		}
		else if (arg_holeheight - (holeradius)<0)
		{
			holeheight = (0.5*holeradius);
			return false;
		}
		else
		{
			holeheight = arg_holeheight;
			return true;
		}
	}
	else if (holeposition==HolePosition::Bottom)
	{
		if (arg_holeheight > height)
		{
			holeheight = height;
			return false;
		}
		else if (arg_holeheight < 0)
		{
			holeheight = 0; 
			return false;
		}
		else
		{
			holeheight = arg_holeheight;
			return true;
		}
	}
	else
	{
		holeheight = 0;
		return false;
	}
}

bool Bucket::setHoleRadius(long double  arg_holeradius)
{
	//setter for holeradius that ensures that the holeradius is valid for the bucket 
	//#######HEIGHT, RADIUS AND HOLEPOSITION MUST ALREADY BE SET FOR THIS TO VALIDATE HOLERADIUS PROPERLY#########
	if (arg_holeradius > 0)
	{
		if (holeposition == HolePosition::Bottom && arg_holeradius <= radius)
		{
			holeradius = arg_holeradius;
			return true;
		}
		else if (holeposition == HolePosition::Side && arg_holeradius<0.5*pi*radius && arg_holeradius<height)
		{
			holeradius = arg_holeradius;
			return true;
		}
		else 
		{
			holeradius = radius*0.02;
			return false;
		}
	
	}
	else
	{
		return false;
	}
}

bool Bucket::setHolePosition(HolePosition arg_enum_holeposition)
{
	//setter for holeposition 
	if(arg_enum_holeposition==HolePosition::Bottom)
	{
		holeposition=HolePosition::Bottom;
		return true;
	}
	else if(arg_enum_holeposition==HolePosition::Side)
	{
		holeposition=HolePosition::Side;
		return true;
	}
	else
	{
		holeposition=HolePosition::Bottom;
		return false;
	}
}

long double  Bucket::getHeight()
{
	//getter for height
	return height;
}

long double  Bucket::getRadius()
{
	//getter for radius
	return radius;
}

long double  Bucket::getHoleRadius()
{
	//getter for holeradius
	return holeradius;
}

long double  Bucket::getHoleHeight()
{
	//getter for holeheight
	return holeheight;
}

Bucket::HolePosition Bucket::getHolePosition()
{
	//getter for holeposition
	return holeposition;
}

bool Bucket::moveOnStep()
{
	//this will simulate the next time period of length local timestep using the existing values stored in vectors
	vec_ratesofflow.push_back(alpha*holeradius*holeradius*pi*sqrt(2 * gravity*getHeightAbove()));
	if (getWaterHeight() >= height)
	{
		vec_volumes.push_back((getHeight()*getRadius()*getRadius()*pi) - (vec_ratesofflow.back()*getTimeStep()));
	}
	else
	{
		vec_volumes.push_back((getWaterHeight()*getRadius()*getRadius()*pi) - (vec_ratesofflow.back()*getTimeStep()));
	}
	if (vec_volumes.back() < 0)
	{
		vec_volumes.back() = 0;
	}
	if (ptr_destination != NULL)
	{
		ptr_destination->acceptVolume(vec_ratesofflow.back()*timestep);
	}
	return true;
}

bool Bucket::acceptVolume(long double  arg_volume)
{
	//adds volume arg_volume to self
	//expect to be called by external object
	vec_volumes.back() += fabs(arg_volume);
	return true;
}

long double  Bucket::getHeightAbove()
{
	//returns the height of water above the lowest point of the hole. 
	if (getWaterHeight() < holeheight)
	{
		return 0;
	}
	else
	{
		return getWaterHeight() - holeheight;
	}
}

long double  Bucket::getExtraDistance()
{
	//returns the distance between the top of the bucket and the top of the water 
	return height - getWaterHeight();
};

long double  Bucket::getWaterHeight()
{
	//returns the height of water above the base of the bucket 
	long double  waterheight;
	waterheight = (fabs(vec_volumes.back()) / (pi*radius*radius));
	if (waterheight >= height)
	{
		return height;
	}
	else
	{
		return waterheight;
	}
}