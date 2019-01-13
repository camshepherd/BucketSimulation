#ifndef WATERENTITY_H
#define WATERENTITY_H
#include <vector>
extern const long double  pi;
#include <iostream> 
class WaterEntity
{
public:
	WaterEntity();
	~WaterEntity();
	virtual bool moveOnStep()=0;
	bool setDestination(WaterEntity* arg_ptr_destination);
	WaterEntity* getDestination();
	bool setTimeStep(long double  arg_timestep);
	long double  getTimeStep();
	bool setGravity(long double  arg_gravity);
	long double  getGravity();
	virtual bool acceptVolume(long double  arg_volume)=0;
	virtual long double  getExtraDistance()=0;
	std::string getId();
	void setId(std::string thing);
	long double getRateOfFlowAtPosition(int);
	long double getVolumeAtPosition(int);
protected:
	std::vector<long double > vec_volumes;
	std::vector<long double > vec_ratesofflow;
	long double  timestep;
	long double  gravity;
	WaterEntity* ptr_destination;
	std::string id;
};

#endif