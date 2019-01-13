#include <iostream> 

#include "Master.h"
int main()
{
	//MUST BE CREATED IN THE CORRECT ORDER: BOTTOM to TOP, OTHERWISE DESTINATION WILL NOT BE INITIALISED AND PROGRAM WILL BREAK

	Bucket* botbucket = new Bucket(NULL,"botbucket",0.09896,0.62,0.5,0.3,0.012,0.1,Bucket::HolePosition::Side,0.01,9.81);
	WaterFall* fall = new WaterFall(botbucket,"fall",0.113,0.01,9.81);
	Bucket* topbucket = new Bucket(fall, "topbucket", 0, 0.62, 0.5, 0.3, 0.012, 0, Bucket::HolePosition::Bottom, 0.01, 9.81);

	std::vector<WaterEntity*> firstvector;
	
	firstvector.push_back(botbucket);
	firstvector.push_back(topbucket);
	firstvector.push_back(fall);
	
	WaterEntityManager* watermanager1=new WaterEntityManager(&firstvector,0.01,9.81);
	watermanager1->getTimeStep();
	GUIManager* guimanager1 = new GUIManager(watermanager1);
	Master* ptr_master = new Master(watermanager1, guimanager1);
	ptr_master->launchProgram();
	std::cout << "ended" << std::endl;
	return 1;
	getchar();
	getchar();
};