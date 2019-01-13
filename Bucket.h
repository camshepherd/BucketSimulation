#ifndef BUCKET_H
#define BUCKET_H
#include "WaterEntity.h"

//Represents a physical bucket with its functionality 
//A WaterEnity polymorph wih extra functionality 

class Bucket :public WaterEntity
{
public:
	enum class HolePosition {Side,Bottom};
	Bucket();
	Bucket(WaterEntity* arg_ptr_destination,std::string id, long double  arg_volume,long double  arg_alpha, long double  arg_height, long double  arg_radius, long double  arg_holeradius, long double  arg_holeheight, HolePosition arg_holeposition,long double  arg_timestep, long double  arg_gravity);
	~Bucket();
	long double  getHeight();
	long double  getRadius();
	long double  getHoleRadius();
	long double  getHoleHeight();
	bool setHeight(long double  arg_height);
	bool setRadius(long double  arg_radius);
	bool setHoleHeight(long double  arg_holeheight);
	bool setHoleRadius(long double  arg_holeradius);
	bool setAlpha(long double  arg_alpha);
	bool setHolePosition(HolePosition arg_enum_holeposition);
	HolePosition getHolePosition();
	long double  getExtraDistance();
	bool moveOnStep();
	long double  getHeightAbove();
	bool acceptVolume(long double  arg_volume);
	long double  getWaterHeight();
protected:
	long double  height;
	long double  radius;
	long double  holeradius;
	long double  holeheight;
	long double  alpha;
	HolePosition holeposition;
private:

};

#endif