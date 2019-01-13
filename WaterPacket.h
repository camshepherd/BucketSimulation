#ifndef WATERPACKET_H
#define WATERPACKET_H
#include <math.h>
#include <vector>

//represents a portion of water radiating out in a straight line from a centre point
//for use within WaterFall for falling water but inside takes water as going away from a point rather than down from a position 

class WaterPacket
{
public:
	WaterPacket();
	WaterPacket(long double  arg_timestep,long double  arg_volume,std::vector<long double >* arg_ptr_vec_ratesofflow,long double  arg_gravity );
	~WaterPacket();
	bool moveOnStep(long double  arg_distance);
	long double  getFrontPos();
	long double  getFrontSpeed();
	long double  getBackPos();
	long double  getBackSpeed();
	long double  getVolume();
	bool setGravity(long double  arg_gravity);
	bool setTimeStep(long double  arg_timestep);
protected:
	long double  timestep;
	long double  gravity;
	long double  frontpos;
	long double  frontspeed;
	long double  backpos;
	long double  backspeed;
	long double  volume;
	std::vector<long double >* ptr_vec_ratesofflow;
};

#endif