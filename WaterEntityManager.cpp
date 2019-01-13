#include "WaterEntityManager.h"
#include <iostream> 
#include <string>


WaterEntityManager::WaterEntityManager(){}; //default constructor, should not ever be called explicitly 

WaterEntityManager::WaterEntityManager(std::vector<WaterEntity*>* arg_ptr_vec_waterentities, long double  arg_timestep, long double  arg_gravity)
{
	//standard constructor, will set stored data within the WaterEnityManager to those passed as arguments 
	//will also move on the simulation to the end of the first timestep
	dec_waterentities.push_back(std::deque<std::unique_ptr<WaterEntity>>());
	for(auto& firstiterator : *arg_ptr_vec_waterentities)
	{
		dec_waterentities[0].push_back(std::unique_ptr<WaterEntity>(firstiterator));
	}
	//printDeque(&(dec_waterentities));
	setTimeStep(arg_timestep);
	setGravity(arg_gravity);
	sortWaterEntities();
	//printDeque(&(dec_waterentities));
	moveOnSteps(1);
	
}

WaterEntityManager::~WaterEntityManager()
{
	//default destructor, only needs to be declared as there are no special deletion methods 
};

bool WaterEntityManager::compareObjects(WaterEntity* obja, WaterEntity* objb)
{
	//recursive 
	//if a is above b then return true
	//each WaterEntity contains a pointer to the one below it 
	//getDestination() returns pointer to WaterEntity below 
	if (obja==NULL || obja->getDestination() == NULL || objb==NULL)
	{
		return false;
	}
	else
	{
		if (obja->getDestination() == objb)
		{
			return true;
		}
		else
		{
			return compareObjects(obja->getDestination(), objb);
		}
	}
}

long double  WaterEntityManager::getGravity()
{
	//getter for gravity 
	return gravity;
}

long double  WaterEntityManager::getTimeStep()
{
	//getter for timestep
	return timestep;
}

bool WaterEntityManager::setGravity(long double  arg_gravity)
{
	//setGravity in WaterEntityManager and all WaterEntitys in particular simulation 
	//assumes that WaterEntityManager value of gravity is the same as in all of the WaterEntitys contained within initially 
	if(fabs(arg_gravity)>0)
	{
		gravity=fabs(arg_gravity);
		for(auto& x : dec_waterentities)
		{
			for(auto& y : x)
			{
				y->setGravity(arg_gravity);
			}
		}
		return true;
	}
	//if invalid set to a standard gravity 
	else
	{
		gravity=long double (9.81);
		return false;
	}
}

bool WaterEntityManager::setTimeStep(long double  arg_timestep)
{
	//set timestep within WaterEntityManager and all WaterEntitys in specific simulation 
	if(fabs(arg_timestep)>0)
	{
		timestep=fabs(arg_timestep);
		return true;
	}
	else
	{
		timestep=long double (0.01);
		return false;
	}
	for (auto& x : dec_waterentities)
	{
		for (auto& y : x)
		{
			y->setTimeStep(timestep);
		}
	}
}

bool WaterEntityManager::moveOnSteps(int steps)
{
	
	//will move on number of steps specified as argument 
	//return false if something goes wrong 
	bool noerrors=true;
	for(int x=0; x<steps; x++)
	{
		for(auto& firstiterator : dec_waterentities)
		{
			for(auto& seconditerator : firstiterator)
			{
				if(!seconditerator.get()->moveOnStep())
				{
						noerrors=false;
				}
			}
		}
		if(noerrors==false)
		{
			return false;
		}
	}
	return true;
}

bool WaterEntityManager::moveOnTime(long double  arg_time)
{
	//will move on amount of time specified as argument 
	//means that it will moveOnSteps(arg_time/timestep)
	bool noerrors=true;
	for(int x=0; x<int((arg_time/getTimeStep())); x++)
	{
		for(auto& firstiterator : dec_waterentities)
		{
			for(auto& seconditerator : firstiterator)
			{
				if(!seconditerator.get()->moveOnStep())
				{
						noerrors=false;
				}
			}
		}
		if(noerrors==false)
		{
			return false;
		}
	}
	return true;
}

bool WaterEntityManager::sortWaterEntities()
{
	//unmoved will store whether the particular WaterEntity being looked at has been moved yet or not
	//this ensures that a null pointer is not treated as a proper WaterEntity, causing a crash
	bool unmoved=true;
	

	//first add n new elements to the deque, to be able to accomodate the sorted WaterEntitys, however they are laid out
	//all WaterEntitys will be moved to the newly added layers during the function 
	for (int x = 0; x <= getDequeSize(&(dec_waterentities)); x++)
	{
		dec_waterentities.push_back(std::deque<std::unique_ptr<WaterEntity>>());
	}

	//generate the final element in dec_waterentities(WaterEntitys that do not feed into anything)
	for (int y =0; y<dec_waterentities[0].size(); y++)
	{
		//must check if the pointer is NULL before checking if the destination is NULL to avoid possible referencing of non-existent objects/functions/variables
		if (dec_waterentities[0][y]!=NULL && dec_waterentities[0][y]->getDestination()==NULL)
		{
			dec_waterentities.back().push_back(std::move(dec_waterentities[0][y]));
		}
	}

	//subject layer is the layer that will have WaterEntitys appended to it 
	for (int subjectlayer=dec_waterentities.size()-2; subjectlayer>=0; subjectlayer--)
	{
		//subjectentity is the entity in dec_waterentities[0] that may be moved if conditions are met 
		for(int subjectentity=0; subjectentity<dec_waterentities[0].size(); subjectentity++)
		{
			//every time a new subjectentity is looked at it can be assumed that it has not been moved
			unmoved=true;
			//compentity is the (comp)arison entity, that in the layer below the subject layer
			//this will not be changed during the comparison 
			//all entities in the layer below subjectlayer must be compared to each subjectentity
			//to see if the subjectentity must be moved
			for (int compentity=0; compentity<dec_waterentities[subjectlayer+1].size(); compentity++)
			{
				//if(unmoved) ensures that I do not try to call functions on a NULL pointer
				//once a unique_ptr is moved with std::move it is replaced with a NULL pointer and unmoved stores whether this has happened or not to subjectentity 
				// if it has happened(unmoved==false) then no functions in the element are called and the program does not crash
				//if subjectentity has been moved then the loop will continue to iterate but nothing will be done
				if(unmoved)
				{
					//this if statement also has checks to ensure that no non-existent functions or variables are called and also ensures that the subjectentity is
					//only moved at the correct time
					if (dec_waterentities[0][subjectentity]!=NULL && dec_waterentities[subjectlayer+1][compentity]!=NULL && dec_waterentities[0][subjectentity]->getDestination()==dec_waterentities[subjectlayer+1][compentity].get())
					{
						//the subjectentity is moved to the subjectlayer, leaving a NULL pointer in its place
						dec_waterentities[subjectlayer].push_back(std::move(dec_waterentities[0][subjectentity]));
						unmoved=false;
					}
				}
			}
		}
	}

	//now all of the WaterEntitys are in the correct positions relative to each other
	//but there are likely to be blank layers
	
	//the first layer must be erased
	//the first layer acts as a carrier for the newly added WaterEntitys, they are all moved to later layers dutring the run of the function
	//it must be removed seperately to make the deletion of the other layers quicker 
	//since deques are fasted when operations are performed on the front or back
	dec_waterentities.erase(dec_waterentities.begin());
	
	//work through the deque and delete any empty elements 
	while (dec_waterentities.front() == std::deque<std::unique_ptr<WaterEntity>>())
	{
		dec_waterentities.erase(dec_waterentities.begin());
	}
	
	//all WaterEntitys are sorted correctly
	//print them to show that they are in their correct positions
	printDeque(&dec_waterentities);
	return true;
}



bool WaterEntityManager::printDeque(std::deque<std::deque<std::unique_ptr<WaterEntity>>>* dequee)
{
	//purely for debugging
	//will print out the complete hierarchy based on WaterEntity positions in dec_waterentities
	std::cout<< "print deque, length = " << (*dequee).size() << ", number of elements = " << getDequeSize(dequee) << std::endl;
	for (auto& iterator : *dequee)
	{
		std::cout<< "<---------->" << std::endl;
		for (auto& iterator2 : iterator)
		{
			std::cout<< iterator2->getId() << " ";
			std::cout<< &(*(iterator2.get())) << " ";
			std::cout<< iterator2->getDestination() << " " << std::endl;
		}
		
	}
	std::cout<< "@----------@" << std::endl;
	return true;
}

int WaterEntityManager::getDequeSize(std::deque<std::deque<std::unique_ptr<WaterEntity>>>* dequee)
{
	//return total number of waterentities within the dec
	int num = 0;
	for (auto& iterator1 : *dequee)
	{
		for (auto& iterator2 : iterator1)
		{
			if (iterator2 != NULL)
			{
				num++;
			}
		}
	}
	return num;
}

WaterEntity* WaterEntityManager::getEntityAtPosition(int a, int b)
{
	//returns a pointer to the WaterEntity at the specified position (outer element , inner element)
	//if element does not exist then return a NULL pointer
	if (dec_waterentities.size() - 1 >= a && dec_waterentities[a].size() - 1 >= b)
	{
		return (dec_waterentities[a][b]).get();
	}
	else
	{
		return NULL;
	}
}