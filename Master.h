#ifndef MASTER_H
#define MASTER_H
#include "GUIManager.h"
class Master
{
public:
	Master();
	~Master();
	Master(WaterEntityManager*, GUIManager*);
	bool launchProgram();
private:
	WaterEntityManager* ptr_watermanager;
	GUIManager* ptr_guimanager;
};

#endif