#ifndef WATERENTITYMANGER_H
#define WATERENTITYMANAGER_H
#include "WaterEntity.h"
#include <deque>
#include <memory>

//manages all WaterEntiies in the simulation and contains unique_ptrs to them so that the WaterEntitys and their vectors of values are deleted properly

class WaterEntityManager
{
public:
	WaterEntityManager();
	WaterEntityManager(std::vector<WaterEntity*>* arg_ptr_vec_waterentities,long double  arg_timestep, long double  arg_gravity);
	~WaterEntityManager();
	bool moveOnTime(long double  arg_time);
	bool moveOnSteps(int arg_steps);
	bool setGravity(long double  arg_gravity);
	long double  getGravity();
	bool setTimeStep(long double  arg_timestep);
	long double  getTimeStep();
	bool sortWaterEntities();
	WaterEntity* getEntityAtPosition(int, int);
protected:
	bool compareObjects(WaterEntity* obja, WaterEntity* objb);
	std::deque<std::deque<std::unique_ptr<WaterEntity>>> dec_waterentities;
	long double  timestep;
	long double  gravity;
private:
	bool printDeque(std::deque<std::deque<std::unique_ptr<WaterEntity>>>* dequee);
	int getDequeSize(std::deque<std::deque<std::unique_ptr<WaterEntity>>>* dequee);
};

#endif