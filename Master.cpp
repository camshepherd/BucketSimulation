#include "Master.h"

Master::Master(WaterEntityManager* a, GUIManager* b)
{
	ptr_watermanager = a;
	ptr_guimanager = b;
}

bool Master::launchProgram()
{
	ptr_guimanager->launchProgram();
	return true;
}


Master::Master(){};