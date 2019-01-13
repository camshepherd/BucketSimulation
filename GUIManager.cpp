#include "GUIManager.h"
#include <SFML\System.hpp>
#include <cmath>


//safestold() is only required in GUIManager
long double safestold(std::string arg)
{
	//this is used to replace the std::stold function in almost all cases 
	//if an invalid argument is passed to std::stold it will break the program so I use this to 
	//ensure that the pogram will not crash even if invalid characters end up in the editboxes 
	//it is perfectly fine to assume that the editbox value is zero if the value is invalid
	if(arg=="-" || arg=="+" || arg=="." || arg==",")
	{
		return 0;
	}
	else
	{
		return std::stold(arg);
	}
}

void GUIManager::newSimulationFromSettings()
{
	//this will create a new simulation and then simulate it
	//method of different but almost identical actions for each state is clumsy but there is not a better way to do it. 
	
	time = 0;
	//set slider position to 0 to make sure that time and slider position are initially valid
	tgui::Slider::Ptr(gui->get("slider1"))->setValue(0);
	tgui::EditBox::Ptr(gui->get("time"))->setText(sf::String("0"));
	//each of these cases is getting the values for all variables in the simulation, and the values are what are in the EditBoxes
	//first case: units in m
	if (tgui::RadioButton::Ptr(gui->get("radiom"))->isChecked())
	{
		topheight = safestold((tgui::EditBox::Ptr(gui->get("topheight"))->getText()).toAnsiString());
		topradius = safestold((tgui::EditBox::Ptr(gui->get("topradius"))->getText()).toAnsiString());
		if ((tgui::EditBox::Ptr(gui->get("topholeposition"))->getText()) == sf::String("Bottom"))
		{
			topholeposition = Bucket::HolePosition::Bottom;
		}
		else if ((tgui::EditBox::Ptr(gui->get("topholeposition"))->getText()) == sf::String("Side"))
		{
			topholeposition = Bucket::HolePosition::Side;
		}
		else
		{
			topholeposition = Bucket::HolePosition::Bottom;
		}
		topholeheight = safestold(std::string(tgui::EditBox::Ptr(gui->get("topholeheight"))->getText().toAnsiString()));
		topholeradius = safestold(tgui::EditBox::Ptr(gui->get("topholeradius"))->getText().toAnsiString());
		topinitialvolume = safestold(tgui::EditBox::Ptr(gui->get("topinitialvolume"))->getText().toAnsiString());
		botheight = safestold((tgui::EditBox::Ptr(gui->get("botheight"))->getText()).toAnsiString());
		botradius = safestold((tgui::EditBox::Ptr(gui->get("botradius"))->getText()).toAnsiString());
		if ((tgui::EditBox::Ptr(gui->get("botholeposition"))->getText()) == sf::String("Bottom"))
		{
			botholeposition = Bucket::HolePosition::Bottom;
		}
		else if ((tgui::EditBox::Ptr(gui->get("botholeposition"))->getText()) == sf::String("Side"))
		{
			botholeposition = Bucket::HolePosition::Side;
		}
		else
		{
			botholeposition = Bucket::HolePosition::Bottom;
		}
		botholeheight = safestold((tgui::EditBox::Ptr(gui->get("botholeheight"))->getText()).toAnsiString());
		botholeradius = safestold((tgui::EditBox::Ptr(gui->get("botholeradius"))->getText()).toAnsiString());
		botinitialvolume = safestold(tgui::EditBox::Ptr(gui->get("botinitialvolume"))->getText().toAnsiString());
		timestep = safestold(tgui::EditBox::Ptr(gui->get("stepsize"))->getText().toAnsiString());
		gravity = safestold(tgui::EditBox::Ptr(gui->get("gravity"))->getText().toAnsiString());
		alpha = safestold(tgui::EditBox::Ptr(gui->get("alpha"))->getText().toAnsiString());
		distance = safestold(tgui::EditBox::Ptr(gui->get("distance"))->getText().toAnsiString());
		units = UnitSystem::m;
	}
	//second case, units are in cm
	else if (tgui::RadioButton::Ptr(gui->get("radiocm"))->isChecked())
	{
		topheight = 0.01*safestold((tgui::EditBox::Ptr(gui->get("topheight"))->getText()).toAnsiString());
		topradius = 0.01*safestold((tgui::EditBox::Ptr(gui->get("topradius"))->getText()).toAnsiString());
		if ((tgui::EditBox::Ptr(gui->get("topholeposition"))->getText()) == sf::String("Bottom"))
		{
			topholeposition = Bucket::HolePosition::Bottom;
		}
		else if ((tgui::EditBox::Ptr(gui->get("topholeposition"))->getText()) == sf::String("Side"))
		{
			topholeposition = Bucket::HolePosition::Side;
		}
		else
		{
			topholeposition = Bucket::HolePosition::Bottom;
		}
		topholeheight = 0.01*safestold(std::string(tgui::EditBox::Ptr(gui->get("topholeheight"))->getText().toAnsiString()));
		topholeradius = 0.01*safestold(tgui::EditBox::Ptr(gui->get("topholeradius"))->getText().toAnsiString());
		topinitialvolume = 0.01*0.01*0.01*safestold(tgui::EditBox::Ptr(gui->get("topinitialvolume"))->getText().toAnsiString());
		botheight = 0.01*safestold((tgui::EditBox::Ptr(gui->get("botheight"))->getText()).toAnsiString());
		botradius = 0.01*safestold((tgui::EditBox::Ptr(gui->get("botradius"))->getText()).toAnsiString());
		if ((tgui::EditBox::Ptr(gui->get("botholeposition"))->getText()) == sf::String("Bottom"))
		{
			botholeposition = Bucket::HolePosition::Bottom;
		}
		else if ((tgui::EditBox::Ptr(gui->get("botholeposition"))->getText()) == sf::String("Side"))
		{
			botholeposition = Bucket::HolePosition::Side;
		}
		else
		{
			botholeposition = Bucket::HolePosition::Bottom;
		}
		botholeheight = 0.01*safestold((tgui::EditBox::Ptr(gui->get("botholeheight"))->getText()).toAnsiString());
		botholeradius = 0.01*safestold((tgui::EditBox::Ptr(gui->get("botholeradius"))->getText()).toAnsiString());
		botinitialvolume = 0.01*0.01*0.01*safestold(tgui::EditBox::Ptr(gui->get("botinitialvolume"))->getText().toAnsiString());
		timestep = safestold(tgui::EditBox::Ptr(gui->get("stepsize"))->getText().toAnsiString());
		gravity = 0.01*safestold(tgui::EditBox::Ptr(gui->get("gravity"))->getText().toAnsiString());
		alpha = safestold(tgui::EditBox::Ptr(gui->get("alpha"))->getText().toAnsiString());
		distance = 0.01*safestold(tgui::EditBox::Ptr(gui->get("distance"))->getText().toAnsiString());
		units = UnitSystem::cm;
	}
	//third case: units in mm
	else if (tgui::RadioButton::Ptr(gui->get("radiomm"))->isChecked())
	{
		topheight = 0.001*safestold((tgui::EditBox::Ptr(gui->get("topheight"))->getText()).toAnsiString());
		topradius = 0.001*safestold((tgui::EditBox::Ptr(gui->get("topradius"))->getText()).toAnsiString());
		if ((tgui::EditBox::Ptr(gui->get("topholeposition"))->getText()) == sf::String("Bottom"))
		{
			topholeposition = Bucket::HolePosition::Bottom;
		}
		else if ((tgui::EditBox::Ptr(gui->get("topholeposition"))->getText()) == sf::String("Side"))
		{
			topholeposition = Bucket::HolePosition::Side;
		}
		else
		{
			topholeposition = Bucket::HolePosition::Bottom;
		}
		topholeheight = 0.001*safestold(std::string(tgui::EditBox::Ptr(gui->get("topholeheight"))->getText().toAnsiString()));
		topholeradius = 0.001*safestold(tgui::EditBox::Ptr(gui->get("topholeradius"))->getText().toAnsiString());
		topinitialvolume = 0.001*0.001*0.001*safestold(tgui::EditBox::Ptr(gui->get("topinitialvolume"))->getText().toAnsiString());
		botheight = 0.001*safestold((tgui::EditBox::Ptr(gui->get("botheight"))->getText()).toAnsiString());
		botradius = 0.001*safestold((tgui::EditBox::Ptr(gui->get("botradius"))->getText()).toAnsiString());
		if ((tgui::EditBox::Ptr(gui->get("botholeposition"))->getText()) == sf::String("Bottom"))
		{
			botholeposition = Bucket::HolePosition::Bottom;
		}
		else if ((tgui::EditBox::Ptr(gui->get("botholeposition"))->getText()) == sf::String("Side"))
		{
			botholeposition = Bucket::HolePosition::Side;
		}
		else
		{
			botholeposition = Bucket::HolePosition::Bottom;
		}
		botholeheight = 0.001*safestold((tgui::EditBox::Ptr(gui->get("botholeheight"))->getText()).toAnsiString());
		botholeradius = 0.001*safestold((tgui::EditBox::Ptr(gui->get("botholeradius"))->getText()).toAnsiString());
		botinitialvolume = 0.001*0.001*0.001*safestold(tgui::EditBox::Ptr(gui->get("botinitialvolume"))->getText().toAnsiString());
		timestep = safestold(tgui::EditBox::Ptr(gui->get("stepsize"))->getText().toAnsiString());
		gravity = 0.001*safestold(tgui::EditBox::Ptr(gui->get("gravity"))->getText().toAnsiString());
		alpha = safestold(tgui::EditBox::Ptr(gui->get("alpha"))->getText().toAnsiString());
		distance = 0.001*safestold(tgui::EditBox::Ptr(gui->get("distance"))->getText().toAnsiString());
		units = UnitSystem::mm;
	}
	
	
	
	//this next section will make sure that before the simulation is started that the values that are put into it are valid. 
	if(topheight == 0)
	{
		//height cannot be 0 as the bucket must be able to hold a volume
		topheight=0.00001;
		//this is the smallest value of topheight that can be displayed in the character limit
		topholeheight=0;
		//it is likely that the simulation using the values after being changed will not be what the user wants 
		//it should however ensure that the simulation will run and create valid values 
		//the user should also notice that their settings have been discarded since the new ones will be displayed
	}
	if(botheight == 0)
	{
		
		botheight=0.00001;
		botholeheight=0;
	}
	if(topradius==0)
	{
		//radius must be >0 as the bucket must be able to hold water 
		topradius=0.00001;
		//new value is smallest value that can be displayed
	}
	if(botradius == 0)
	{
		botradius=0.00001;
	}
	
	if(topholeposition==Bucket::HolePosition::Bottom)
	{
		if(topholeradius>topradius)
		{
			topholeradius=topradius;
		}
		if(topholeheight>topheight)
		{
			topholeheight=topheight;
		}
	}
	else
	{
		
		if(topheight < (2*topholeradius) + topholeheight)
		{
			topholeradius=0.5*(topheight-(topholeheight));
		}
		
		if(2 * topholeradius > pi * topradius)
		{
			topholeradius = 0.5* pi * topradius;
		}
	}
	if(botholeposition==Bucket::HolePosition::Bottom)
	{
		if(botholeradius>botradius)
		{
			botholeradius=botradius;
		}
		if(botholeheight>botheight)
		{
			botholeheight=botheight;
		}
	}
	else
	{
		
		if(botheight < (2*botholeradius) + botholeheight)
		{
			botholeradius=0.5*(botheight-(botholeheight));
		}
		
		if(2 * botholeradius > pi * botradius)
		{
			botholeradius = 0.5* pi * botradius;
		}
	}
	
	if (distance<0)
	{
		distance=fabs(distance);
	}
	
	
	
	
	
	//at this point the values have been made valid and so the simulation is created
	
	
	
	
	//each WaterEntity must be created in the correct order: bottom to top so that the pointer to the WaterEntity below can be passed
	Bucket* botbucket = new Bucket(NULL, "botbucket", botinitialvolume, alpha, botheight, botradius, botholeradius, botholeheight, botholeposition, timestep, gravity);
	WaterFall* fall = new WaterFall(botbucket, "fall", distance, timestep, gravity);
	Bucket* topbucket = new Bucket(fall, "topbucket", topinitialvolume, alpha, topheight, topradius, topholeradius, topholeheight, topholeposition, timestep, gravity);
	//all WaterEntitys appended to vec_waterentities then passed to new WaterEntityManager
	std::vector<WaterEntity*> vec_waterentities;
	vec_waterentities.push_back(botbucket);
	vec_waterentities.push_back(fall); 
	vec_waterentities.push_back(topbucket);
	//new WaterEntityManager created
	WaterEntityManager* watermanager1 = new WaterEntityManager(&vec_waterentities, timestep, gravity);
	//below calls destructor of preexisting WaterEntityManager so that all existing data is deleted, ready for the new simulation to replace it
	ptr_watermanager->~WaterEntityManager();
	//ptr_watermanager given a new value and all traces of previous WaterEntityManager removed
	ptr_watermanager = watermanager1;
	//there must be values contained within each WaterEntityManager so that the values at time 0 can be displayed immediately 
	ptr_watermanager->moveOnSteps(1);
	//make sure that values are set
	timesimulated = 0;
	//percentsimulated is a number between 0 and 1 where 1 is 100% and 0 is 0%
	percentsimulated = 0;
	//nothing has been simulated so the loading bar should reflect this
	tgui::LoadingBar::Ptr(gui->get("LoadingBar1"))->setValue(0);
	//finetocontinuesimulating will show whether enough values have been simulated
	finetocontinuesimulating = true;
	
	//following section will create the buckets that the user can see in the screen
	//this is not an elegant way to create the buckets but there is not a cleaner way
	if (topholeposition == Bucket::HolePosition::Bottom)
	{
		bucketoutlinetop = sf::RectangleShape(sf::Vector2f(432,184));
		bucketoutlinetop.setPosition(sf::Vector2f(384, 25));
		bucketoutlinetop.setFillColor(sf::Color::Transparent);
		bucketoutlinetop.setOutlineThickness(2);
		bucketoutlinetop.setOutlineColor(sf::Color::Black);

		bucketholetop = sf::RectangleShape(sf::Vector2f(432*(2*topholeradius/topradius),(184*(topholeheight/topheight))));
		bucketholetop.setPosition(sf::Vector2f(600-432*(topholeradius/topradius), 25+(184-184*(topholeheight/topheight))));
		bucketholetop.setFillColor(sf::Color::Blue);
		bucketholetop.setOutlineThickness(-2);
		bucketholetop.setOutlineColor(sf::Color::Black);

		bucketwatertop = sf::RectangleShape(sf::Vector2f(864 * (topholeradius / topradius),276));
		bucketwatertop.setPosition(sf::Vector2f(600-(432*topholeradius/topradius), 209));
		bucketwatertop.setFillColor(sf::Color::Blue);
	}
	else
	{
		bucketoutlinetop = sf::RectangleShape(sf::Vector2f(288, 184));
		bucketoutlinetop.setPosition(sf::Vector2f(384, 25));
		bucketoutlinetop.setFillColor(sf::Color::Transparent);
		bucketoutlinetop.setOutlineThickness(2);
		bucketoutlinetop.setOutlineColor(sf::Color::Black);

		bucketholetop = sf::RectangleShape(sf::Vector2f(18, 184*(2*topholeradius/topheight)));
		bucketholetop.setPosition(654, 25+(184-184*((2*topholeradius/topheight)+(topholeheight/topheight))));
		bucketholetop.setFillColor(sf::Color::Blue);
		bucketholetop.setOutlineThickness(-2);
		bucketholetop.setOutlineColor(sf::Color::Black);
		
		bucketwatertop = sf::RectangleShape(sf::Vector2f(34, 92));
		bucketwatertop.setPosition(672, 25+(184-(368*topholeradius/topheight)));
		bucketwatertop.setFillColor(sf::Color::Blue);
	}
	
	if (botholeposition == Bucket::HolePosition::Bottom)
	{
		bucketoutlinebot = sf::RectangleShape(sf::Vector2f(432, 184));
		bucketoutlinebot.setPosition(sf::Vector2f(384, 301));
		bucketoutlinebot.setFillColor(sf::Color::Transparent);
		bucketoutlinebot.setOutlineThickness(2);
		bucketoutlinebot.setOutlineColor(sf::Color::Black);

		bucketholebot = sf::RectangleShape(sf::Vector2f(432 * (2 * botholeradius / botradius), (184 * (botholeheight / botheight))));
		bucketholebot.setPosition(sf::Vector2f(600 - 432 * (botholeradius / botradius), 301 + (184 - 184 * (botholeheight / botheight))));
		bucketholebot.setFillColor(sf::Color::Blue);
		bucketholebot.setOutlineThickness(-2);
		bucketholebot.setOutlineColor(sf::Color::Black);
	}
	else
	{
		bucketoutlinebot = sf::RectangleShape(sf::Vector2f(288, 184));
		bucketoutlinebot.setPosition(sf::Vector2f(528, 301));
		bucketoutlinebot.setFillColor(sf::Color::Transparent);
		bucketoutlinebot.setOutlineThickness(2);
		bucketoutlinebot.setOutlineColor(sf::Color::Black);

		bucketholebot = sf::RectangleShape(sf::Vector2f(18, 184 * (2 * botholeradius / botheight)));
		bucketholebot.setPosition(528, 301 + (184 - 184 * ((2 * botholeradius / botheight) + (botholeheight / botheight))));
		bucketholebot.setFillColor(sf::Color::Blue);
		bucketholebot.setOutlineThickness(-2);
		bucketholebot.setOutlineColor(sf::Color::Black);
	}
	//after everything has been created the simulation should be simulated immediately and stop when the total water in the simulation 
	//is less than or equal to 0.01 of the original value
	simulate(0.01);
	//this causes a call of leftMouseClicked so that the callback associated with the revert button is called 
	//this system is used as I canot create a callback that pretends to be from revert so the only way for the 
	//program to act as if it has been pressed is to actually press it
	tgui::Button::Ptr(gui->get("revert"))->leftMousePressed(0,0); 
	//I click and release the button in its top left corner 
	//this does not affect the actual position of the mouse
	tgui::Button::Ptr(gui->get("revert"))->leftMouseReleased(0,0);
}

void GUIManager::startClock(const tgui::Callback& callback)
{
	//this starts the two clocks 
	//startpointclock is used for measuring the time since the value of startposition was changed 
	if(callback.id==47)
	{
		startpointclock.restart();
	}
	//finishpointclock measures the time since finishposition was changed
	else if (callback.id==48)
	{
		finishpointclock.restart();
	}
}

bool GUIManager::launchProgram()
{
	//this is called to begin the program and is the main loop of the program
	//it will open and close the program and simply calling this will make the program start without any other calls required
	time=0;
	//create window with dimensions and title 
	ptr_window=new sf::RenderWindow(sf::VideoMode(1248, 800), "Bucket Simulation");
	//create the gui
	gui=new tgui::Gui(*ptr_window);
	//font must be set BEFORE any widgets are loaded and fonts cannot be changed without recreating the widget
	//this is an inherent problem with TGUI
	gui->setGlobalFont("fonts/DejaVuSans.ttf");
	
	//below checks if the font exists and if not will print error
	sf::Font font1;
	if (!font1.loadFromFile("fonts/DejaVuSans.ttf"))
	{
		std::cout << "ERROR: Failed to load font/s " << std::endl;
	}
	
	if (!gui->loadWidgetsFromFile("bucketsimulation1.txt"))
	{
		//give out appropriate error message since nothing can be done to fix it 
		std::cout << "ERROR: Failed to load widgets " << std::endl;
	}
	//widgetpointers contains pointers to all widgets 
	widgetpointers = gui->getWidgets();
	//create three panels:units,load and save since radiobuttons are exclusively on compared to other raduiobuttons in scope, which is all radiobuttons in the same panel
	//without radiobuttons being put into different panels only a single radiobutton in the entire program could ever be on
	//panels have no physical presence
	panelunits=tgui::Panel::Ptr(*gui, "panelunits");
	panelload=tgui::Panel::Ptr(*gui, "panelload");
	panelsave=tgui::Panel::Ptr(*gui, "panelsave");
	panelunits->setBackgroundColor(sf::Color::Transparent);
	panelload->setBackgroundColor(sf::Color::Transparent);
	panelsave->setBackgroundColor(sf::Color::Transparent);
	//following is all callbacks being binded
	//this is way is crude but it is the only way to do it since it is impossible to bind calls of functions to events in a settings file 
	//bindCallBackEx will call the specified function in the event of the particular event happening but will also pass
	//a callback to the function when it is called
	//bindCallback() merely calls the void function with no arguments(if function is specified)
	//otherwise bindCallBack() will result in a callback being released and another function having to pick it up
	(tgui::Button::Ptr(gui->get("simulate")))->bindCallback(&GUIManager::newSimulationFromSettings, this,  tgui::ClickableWidget::ClickableWidgetCallbacks::LeftMouseClicked);
	tgui::Slider::Ptr(gui->get("slider1"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::Slider::SliderCallbacks::ValueChanged);
	tgui::Button::Ptr(gui->get("simulate"))->bindCallback(tgui::ClickableWidget::ClickableWidgetCallbacks::LeftMouseClicked);
	//define callbacks below to make editbox values valid at all times and after any user input has been detected
	tgui::EditBox::Ptr(gui->get("topheight"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("topradius"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("topholeradius"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("topholeheight"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("topinitialvolume"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("botheight"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("botradius"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("botholeradius"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("botholeheight"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("botinitialvolume"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);

	tgui::EditBox::Ptr(gui->get("speed"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("time"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("startpoint"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("startpoint"))->bindCallbackEx(&GUIManager::startClock, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("startpoint"))->bindCallbackEx(&GUIManager::setToExistingValues, this, tgui::EditBox::WidgetCallbacks::Unfocused);
	tgui::EditBox::Ptr(gui->get("finishpoint"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("finishpoint"))->bindCallbackEx(&GUIManager::startClock, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("finishpoint"))->bindCallbackEx(&GUIManager::setToExistingValues, this, tgui::EditBox::WidgetCallbacks::Unfocused);

	tgui::EditBox::Ptr(gui->get("topvolume"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("topvolumepercent"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("topwaterheight"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("topflowout"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("topexitvelocity"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);

	tgui::EditBox::Ptr(gui->get("botvolume"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("botvolumepercent"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("botwaterheight"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("botflowout"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("botexitvelocity"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);

	tgui::EditBox::Ptr(gui->get("fallvolume"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("fallgapsize"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);
	tgui::EditBox::Ptr(gui->get("fallflowout"))->bindCallbackEx(&GUIManager::makeWidgetValid, this, tgui::EditBox::EditBoxCallbacks::TextChanged);

	tgui::Button::Ptr(gui->get("loadbutton"))->bindCallback(tgui::ClickableWidget::ClickableWidgetCallbacks::LeftMouseClicked);
	tgui::Button::Ptr(gui->get("savebutton"))->bindCallback(tgui::ClickableWidget::ClickableWidgetCallbacks::LeftMouseClicked);

	//add all radiobuttons to their respective panels 
	panelunits->add(gui->get("radiom"));
	panelunits->add(gui->get("radiocm"));
	panelunits->add(gui->get("radiomm"));

	panelload->add(gui->get("load1"));
	panelload->add(gui->get("load2"));
	panelload->add(gui->get("load3"));
	panelload->add(gui->get("load4"));
	panelload->add(gui->get("load5"));
	panelload->add(gui->get("load6"));
	panelload->add(gui->get("load7"));
	panelload->add(gui->get("load8"));
	panelload->add(gui->get("load9"));
	panelload->add(gui->get("load10"));

	panelsave->add(gui->get("save1"));
	panelsave->add(gui->get("save2"));
	panelsave->add(gui->get("save3"));
	panelsave->add(gui->get("save4"));
	panelsave->add(gui->get("save5"));
	panelsave->add(gui->get("save6"));
	panelsave->add(gui->get("save7"));
	panelsave->add(gui->get("save8"));
	panelsave->add(gui->get("save9"));
	panelsave->add(gui->get("save10"));

	//set initial radiobuttons to be checked, radiobutton m is already checked or going to be checked when simulation is created
	tgui::RadioButton::Ptr(gui->get("save1"))->check();
	tgui::RadioButton::Ptr(gui->get("load1"))->check();

	//make sure that the showed savenames are all correct
	updateSaveBoxes();
	

	//sets initial values for the two overlaid percentages on the buckets
	overlaypercenttop = sf::Text(sf::String("0%"), font1, 78);
	overlaypercenttop.setPosition(386, 76);
	overlaypercenttop.setColor(sf::Color::White);

	overlaypercentbot = sf::Text(sf::String("0%"), font1, 78);
	overlaypercentbot.setPosition(530, 340);
	overlaypercentbot.setColor(sf::Color::White);
	
	//must immediately create new simulation using default values so that there is something to display
	newSimulationFromSettings();
	std::cout << "simulation has finished" << std::endl;
	
	//mintime is minimum possible time, there is no ability to have this anything other than 0
	mintime = 0;
	
	//main loop below
	while(ptr_window->isOpen())
	{
		sf::Event event;
		while(ptr_window->pollEvent(event))
		{
			//checks if SFML event closed is released and if so will close the simulation, no other events have to be handled explicitly 
			//minimise and maximise and resize are handled naturally by SFML and TGUI
			if(event.type==sf::Event::Closed)
			{
				ptr_window->close();
			}
			gui->handleEvent(event);
		}
		tgui::Callback callback;
		sf::Time timeelapsed = clock.getElapsedTime();
		//this passes the timeelapsed since the clock was started and passes it to updateTimes()
		//this function will only do anything if the simulation is playing since it is used to move the slider when the simulation is playing 
		updateTimes(timeelapsed);
		updateReadings();

		//below will pass all callbacks to all widgets and deal with any callbacks produced by pasing them to acceptCallback()
		while(gui->pollCallback(callback))
		{
		
			for (auto& name : (gui->getWidgetNames()))
			{
				acceptCallback(callback, gui->get(name));
			}
		}
		

		/*
		this section is unlikely to be necessary but could conceivably create problems by being commented out
		for (auto & name : gui->getWidgetNames())
		{
			acceptCallback(tgui::Callback(), gui->get(name));
		}
		*/

		//standard display of window: clear window, draw window then display it, every frame
		ptr_window->clear();		
		gui->draw(ptr_window);
		ptr_window->draw(bucketwatertop);
		ptr_window->draw(bucketwaterbot);
		ptr_window->draw(bucketwaterfalltop);
		ptr_window->draw(bucketwaterfallbot);
		ptr_window->draw(bucketoutlinetop);
		ptr_window->draw(bucketoutlinebot);
		ptr_window->draw(bucketholetop);
		ptr_window->draw(bucketholebot);
		ptr_window->draw(overlaypercenttop);
		ptr_window->draw(overlaypercentbot);
		ptr_window->display();
	}
	return true;
}

bool GUIManager::acceptCallback(tgui::Callback callback, tgui::Widget::Ptr pointer)
{
	//this will handle any callback passed to it from a widget by passing the same arguments to the correct function for that type of widget 
	switch (pointer->getWidgetType())
	{
	case tgui::WidgetTypes::Type_Button:
		acceptCallbackButton(callback, pointer);
		break;
	case tgui::WidgetTypes::Type_EditBox:
		acceptCallbackEditBox(callback, pointer);
		break;
	case tgui::WidgetTypes::Type_Label:
		acceptCallbackLabel(callback, pointer);
		break;
	case tgui::WidgetTypes::Type_Slider:
		acceptCallbackSlider(callback, pointer);
		break;
	case tgui::WidgetTypes::Type_LoadingBar:
		acceptCallbackLoadingBar(callback, pointer);
		break;
	case tgui::WidgetTypes::Type_Picture:
		acceptCallbackPicture(callback, pointer);
		break;
	case tgui::WidgetTypes::Type_RadioButton:
		acceptCallbackRadioButton(callback, pointer);
		break;
	case tgui::WidgetTypes::Type_Panel:
		break;
	default: 
		//there should never be a callback from another type of widget so if there is an error should be displayed
		std::cout << "ERROR: unexpected widget type" << std::endl;
		break;
	}
	return true;
}

bool GUIManager::simulate(long double minvolumeasdecimal)
{
	//this will create a new main loop fpor the period that the program is simulating
	//this main loop is virtually the same as the one in launchProgram() but having it here rather than changing global states makes the program faster in normal operation
	//these are both local variables 
	long double maxvolume = ptr_watermanager->getEntityAtPosition(0, 0)->getVolumeAtPosition(timesimulated / ptr_watermanager->getTimeStep()) + ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(timesimulated / ptr_watermanager->getTimeStep());
	//somethingnotgonehoriblywrong will say whether something has gone wrong and if so it will result in the ending of values being simulated
	bool somethingnotgonehorriblywrong = true;
	//vec_percentsimulated will store all previous values of percentsimulated so that it is known what the previous value was
	//this allows me to ensure that the loading bar will never show the percent simulated decreasing
	std::vector <long double> vec_percentsimulated;
	//while(totalwaterinsimulation>minvolumeasdecimal)below
	while ((ptr_watermanager->getEntityAtPosition(0, 0)->getVolumeAtPosition(timesimulated / ptr_watermanager->getTimeStep()) + (ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(timesimulated / ptr_watermanager->getTimeStep())/maxvolume>minvolumeasdecimal)) 
	&& somethingnotgonehorriblywrong==true)
	{
		//move on 50 steps regardless of step size or simulation complexity
		ptr_watermanager->moveOnSteps(50);
		timesimulated += 50*timestep; //move on time appropriately
		//change maximum displayable time 
		maxtime = timesimulated;
		//percentsimulated = 1-(totalvolumeinsimulation)/maxvolume
		percentsimulated = 1 - ((ptr_watermanager->getEntityAtPosition(0, 0)->getVolumeAtPosition(timesimulated / ptr_watermanager->getTimeStep()) + (ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(timesimulated / ptr_watermanager->getTimeStep()))) / maxvolume);
		vec_percentsimulated.push_back(percentsimulated);
		//if the back of vec_percentsimulated is the same as 30 elements previously, something has gone horribly wrong
		if (vec_percentsimulated.size()>30 && vec_percentsimulated.back() == *(vec_percentsimulated.end() - 29))
		{
			somethingnotgonehorriblywrong = false;
		}
		
		//below is main event loop for while the program is simulating
		//it is quicker to copy the main loop to here to remove an extra if() statement every frame
		if(ptr_window->isOpen())
		{
			sf::Event event;
			while(ptr_window->pollEvent(event))
			{
				if(event.type==sf::Event::Closed)
				{
					ptr_window->close();
				}
				gui->handleEvent(event);
			}
			tgui::Callback callback;
			while(gui->pollCallback(callback))
			{
				for (auto& name : (gui->getWidgetNames()))
				{
					acceptCallback(callback, gui->get(name));
				}
			}
			for (auto & name : gui->getWidgetNames())
			{
				acceptCallback(tgui::Callback(), gui->get(name));
			}
			updateReadings();
			ptr_window->clear();
			gui->draw(ptr_window);
			ptr_window->draw(bucketwatertop);
			ptr_window->draw(bucketwaterbot);
			ptr_window->draw(bucketwaterfalltop);
			ptr_window->draw(bucketwaterfallbot);
			ptr_window->draw(bucketoutlinetop);
			ptr_window->draw(bucketoutlinebot);
			ptr_window->draw(bucketholetop);
			ptr_window->draw(bucketholebot);
			ptr_window->draw(overlaypercenttop);
			ptr_window->draw(overlaypercentbot);
			ptr_window->display();
		}
		//below make finishpoint fit maxtime
		tgui::EditBox::Ptr(gui->get("finishpoint"))->setText(sf::String(std::to_string(maxtime)));
	}
	//below are initial settings for when the values have been finished
	mintime = 0;
	tgui::EditBox::Ptr(gui->get("startpoint"))->setText("0000");
	tgui::EditBox::Ptr(gui->get("finishpoint"))->setText(sf::String(std::to_string(maxtime)));
	maxsettime = maxtime;
	tgui::Slider::Ptr(gui->get("slider1"))->setMaximum(maxtime);
	percentsimulated = 1; //once simulation has finished it must be displayed to the user 
	return true;
}

	//following acceptCallback..... functions will handle all callbacks that are released from their specific widget, rather than all callbacks that affect that widget
	//these will address widgets using their unique IDs to increase speed and for practicality(less lines of code)
	//even though it makes it harder to read
	//consult design documentation or bucketsimulation1.txt (in the absence of design documentation) for asignment of callback IDs
bool GUIManager::acceptCallbackButton(tgui::Callback callback, tgui::Button::Ptr button)
{ 
	//this will handle all callbacks that are released from a button, rather than all callbacks that affect a button
	//this will address widgets using their unique IDs to increase speed and for practicality(less lines of code)
	//even though it makes it harder to read
	if (callback.id == 43 && callback.trigger == tgui::ClickableWidget::ClickableWidgetCallbacks::LeftMouseClicked)
	{
		//case pauseplay_button
		if (playing == false)
		{
			playing = true;
		}
		else if (playing == true)
		{
			playing = false;
		}
		if (playing == true)
		{
			timetoplayfrom = time;
		}
		clock.restart();
	}
	if (callback.id == 38 && callback.trigger == tgui::ClickableWidget::ClickableWidgetCallbacks::LeftMouseClicked)
	{
		//case simulate_button
		finetocontinuesimulating = false;
	}
	return true; 
};
bool GUIManager::acceptCallbackEditBox(tgui::Callback callback, tgui::EditBox::Ptr editbox)
{
	//this will handle all callbacks that are released from an EditBox, rather than all callbacks that affect an EditBox
	//this will address widgets using their unique IDs to increase speed and for practicality(less lines of code)
	//even though it makes it harder to read
	//consult design documentation or bucketsimulation1.txt for asignment of callback IDs
	if (callback.id == 42 && callback.trigger == tgui::EditBox::EditBoxCallbacks::TextChanged && editbox->getCallbackId() == 42)
	{
		if (editbox->getText() != sf::String("") && editbox->getText() != sf::String("+") && editbox->getText() != sf::String("-"))
		{
			speed = safestold(std::string(editbox->getText()));
		}
	}
	if (editbox->getCallbackId() == 45)
	{
		if (callback.id == 46 && callback.trigger == tgui::Slider::SliderCallbacks::ValueChanged &&  tgui::Slider::Ptr(gui->get("slider1"))->Focused==1/*callback.trigger==tgui::Widget::WidgetCallbacks::Focused*/  /*&& tgui::Slider::Ptr(gui->get("slider1"))->isFocused()*/)
		{
			editbox->setText(sf::String(tgui::Slider::Ptr(gui->get("slider1"))->getValue()));
			time = tgui::Slider::Ptr(gui->get("slider1"))->getValue();
		}
	}
	if (callback.id == 46 && callback.trigger == tgui::Slider::SliderCallbacks::ValueChanged)
	{
		if (editbox->getCallbackId() == 45)
		{
			editbox->setText(sf::String(tgui::Slider::Ptr(gui->get("slider1"))->getValue()));
		}
	}
	if (callback.id == 48 && callback.trigger == tgui::EditBox::EditBoxCallbacks::TextChanged)
	{
		if (editbox->getCallbackId() == 48 && editbox->isFocused() && editbox->getText() != sf::String("") && safestold(std::string(editbox->getText())) > maxtime)
		{
			maxsettime = safestold(std::string(editbox->getText()));
			editbox->setText(std::to_string(maxsettime));
		}
	}
	if (callback.id == 37 && callback.trigger == tgui::ClickableWidget::ClickableWidgetCallbacks::LeftMouseClicked)
	{
		switch (editbox->getCallbackId())
		{
		case 4:
			editbox->setText(sf::String(std::to_string(topheight)));
			break;
		case 6:
			editbox->setText(sf::String(std::to_string(topradius)));
			break;
		case 8:
			if (topholeposition == Bucket::HolePosition::Bottom)
			{
				editbox->setText(sf::String("Bottom"));
			}
			else if (topholeposition==Bucket::HolePosition::Side)
			{
				editbox->setText("Side");
			}
			else
			{
				topholeposition = Bucket::HolePosition::Bottom;
				editbox->setText(sf::String("Bottom"));
			}
			break;
		case 10:
			editbox->setText(sf::String(std::to_string(topholeradius)));
			break;
		case 12:
			editbox->setText(sf::String(std::to_string(topholeheight)));
			break;
		case 15:
			editbox->setText(sf::String(std::to_string(botheight)));
			break;
		case 17:
			editbox->setText(sf::String(std::to_string(botradius)));
			break;
		case 19:
			if (botholeposition == Bucket::HolePosition::Bottom)
			{
				editbox->setText("Bottom");
			}
			else if (botholeposition == Bucket::HolePosition::Side)
			{
				editbox->setText("Side");
			}
			break;
		case 21:
			editbox->setText(sf::String(std::to_string(botholeradius)));
			break;
		case 23:
			editbox->setText(sf::String(std::to_string(botholeheight)));
			break;
		case 26:
			editbox->setText(std::to_string(distance));
			break;
		case 28:
			editbox->setText(std::to_string(alpha));
			break;
		case 34:
			editbox->setText(std::to_string(gravity));
			break;
		case 36:
			editbox->setText(std::to_string(timestep));
			break;
		case 114:
			editbox->setText(std::to_string(topinitialvolume));
			break;
		case 115:
			editbox->setText(std::to_string(botinitialvolume));
			break;
		}
	}
	if (callback.id == 30 && callback.trigger == tgui::RadioButton::RadioButtonCallbacks::Checked)
	{
		switch (editbox->getCallbackId())
		{
		case 4:
			editbox->setText(sf::String(std::to_string(topheight)));
			break;
		case 6:
			editbox->setText(sf::String(std::to_string(topradius)));
			break;
		case 8:
			if (topholeposition == Bucket::HolePosition::Bottom)
			{
				editbox->setText(sf::String("Bottom"));
			}
			else if (topholeposition == Bucket::HolePosition::Side)
			{
				editbox->setText("Side");
			}
			else
			{
				topholeposition = Bucket::HolePosition::Bottom;
				editbox->setText(sf::String("Bottom"));
			}
			break;
		case 10:
			editbox->setText(sf::String(std::to_string(topholeradius)));
			break;
		case 12:
			editbox->setText(sf::String(std::to_string(topholeheight)));
			break;
		case 15:
			editbox->setText(sf::String(std::to_string(botheight)));
			break;
		case 17:
			editbox->setText(sf::String(std::to_string(botradius)));
			break;
		case 19:
			if (botholeposition == Bucket::HolePosition::Bottom)
			{
				editbox->setText("Bottom");
			}
			else if (botholeposition == Bucket::HolePosition::Side)
			{
				editbox->setText("Side");
			}
			break;
		case 21:
			editbox->setText(sf::String(std::to_string(botholeradius)));
			break;
		case 23:
			editbox->setText(sf::String(std::to_string(botholeheight)));
			break;
		case 26:
			editbox->setText(std::to_string(distance));
			break;
		case 28:
			editbox->setText(std::to_string(alpha));
			break;
		case 34:
			editbox->setText(std::to_string(gravity));
			break;
		case 36:
			editbox->setText(std::to_string(timestep));
			break;
		case 114:
			editbox->setText(std::to_string(topinitialvolume));
			break;
		case 115:
			editbox->setText(std::to_string(botinitialvolume));
			break;
		}
	}
	if (callback.id == 31 && callback.trigger == tgui::RadioButton::RadioButtonCallbacks::Checked)
	{
		switch (editbox->getCallbackId())
		{
		case 4:
			editbox->setText(sf::String(std::to_string(topheight*100)));
			break;
		case 6:
			editbox->setText(sf::String(std::to_string(topradius*100)));
			break;
		case 8:
			if (topholeposition == Bucket::HolePosition::Bottom)
			{
				editbox->setText(sf::String("Bottom"));
			}
			else if (topholeposition == Bucket::HolePosition::Side)
			{
				editbox->setText("Side");
			}
			else
			{
				topholeposition = Bucket::HolePosition::Bottom;
				editbox->setText(sf::String("Bottom"));
			}
			break;
		case 10:
			editbox->setText(sf::String(std::to_string(topholeradius*100)));
			break;
		case 12:
			editbox->setText(sf::String(std::to_string(topholeheight*100)));
			break;
		case 15:
			editbox->setText(sf::String(std::to_string(botheight*100)));
			break;
		case 17:
			editbox->setText(sf::String(std::to_string(botradius*100)));
			break;
		case 19:
			if (botholeposition == Bucket::HolePosition::Bottom)
			{
				editbox->setText("Bottom");
			}
			else if (botholeposition == Bucket::HolePosition::Side)
			{
				editbox->setText("Side");
			}
			break;
		case 21:
			editbox->setText(sf::String(std::to_string(botholeradius*100)));
			break;
		case 23:
			editbox->setText(sf::String(std::to_string(botholeheight*100)));
			break;
		case 26:
			editbox->setText(std::to_string(distance*100));
			break;
		case 28:
			editbox->setText(std::to_string(alpha));
			break;
		case 34:
			editbox->setText(std::to_string(gravity*100));
			break;
		case 36:
			editbox->setText(std::to_string(timestep));
			break;
		case 114:
			editbox->setText(std::to_string(topinitialvolume*100*100*100));
			break;
		case 115:
			editbox->setText(std::to_string(botinitialvolume*100*100*100));
			break;
		}
	}

	if (callback.id == 32 && callback.trigger == tgui::RadioButton::RadioButtonCallbacks::Checked)
	{
		switch (editbox->getCallbackId())
		{
		case 4:
			editbox->setText(sf::String(std::to_string(topheight * 1000)));
			break;
		case 6:
			editbox->setText(sf::String(std::to_string(topradius * 1000)));
			break;
		case 8:
			if (topholeposition == Bucket::HolePosition::Bottom)
			{
				editbox->setText(sf::String("Bottom"));
			}
			else if (topholeposition == Bucket::HolePosition::Side)
			{
				editbox->setText("Side");
			}
			else
			{
				topholeposition = Bucket::HolePosition::Bottom;
				editbox->setText(sf::String("Bottom"));
			}
			break;
		case 10:
			editbox->setText(sf::String(std::to_string(topholeradius * 1000)));
			break;
		case 12:
			editbox->setText(sf::String(std::to_string(topholeheight * 1000)));
			break;
		case 15:
			editbox->setText(sf::String(std::to_string(botheight * 1000)));
			break;
		case 17:
			editbox->setText(sf::String(std::to_string(botradius * 1000)));
			break;
		case 19:
			if (botholeposition == Bucket::HolePosition::Bottom)
			{
				editbox->setText("Bottom");
			}
			else if (botholeposition == Bucket::HolePosition::Side)
			{
				editbox->setText("Side");
			}
			break;
		case 21:
			editbox->setText(sf::String(std::to_string(botholeradius * 1000)));
			break;
		case 23:
			editbox->setText(sf::String(std::to_string(botholeheight * 1000)));
			break;
		case 26:
			editbox->setText(std::to_string(distance * 1000));
			break;
		case 28:
			editbox->setText(std::to_string(alpha));
			break;
		case 34:
			editbox->setText(std::to_string(gravity * 1000));
			break;
		case 36:
			editbox->setText(std::to_string(timestep));
			break;
		case 114:
			editbox->setText(std::to_string(topinitialvolume * 1000 * 1000 * 1000));
			break;
		case 115:
			editbox->setText(std::to_string(botinitialvolume * 1000 * 1000 * 1000));
			break;
		}
	}
	
	return true; 
};
bool GUIManager::acceptCallbackLabel(tgui::Callback, tgui::Label::Ptr)
{
	//this function should exist for completeness but there are no callbacks for labels so no handling of those callbacks is required
	return true;
}
bool GUIManager::acceptCallbackSlider(tgui::Callback callback, tgui::Slider::Ptr slider)
{
	if (callback.id == 45 &&((tgui::EditBox::Ptr(gui->get("time"))->isFocused() && callback.trigger==tgui::EditBox::EditBoxCallbacks::ReturnKeyPressed) || callback.trigger==tgui::Widget::WidgetCallbacks::Unfocused))
	{
		long double timevalue = safestold(std::string(tgui::EditBox::Ptr(gui->get("time"))->getText()));
		slider->setValue(timevalue);
	}
	if (callback.id == 47 && callback.trigger == tgui::EditBox::EditBoxCallbacks::TextChanged)
	{
		if (tgui::EditBox::Ptr(gui->get("startpoint"))->getText() != sf::String("") && tgui::EditBox::Ptr(gui->get("startpoint"))->getText() != sf::String("-"))
		{
			long double localmintime = safestold(std::string(tgui::EditBox::Ptr(gui->get("startpoint"))->getText()));
			if (localmintime>maxsettime && localmintime<=maxtime && startpointclock.getElapsedTime().asSeconds()>=2)
			{
				tgui::EditBox::Ptr(gui->get("finishpoint"))->setText(std::to_string(maxsettime));
				minsettime=maxsettime;
			}
			else if (localmintime > time && localmintime < maxsettime && localmintime<maxtime && localmintime>=mintime)
			{
				minsettime=localmintime;
				slider->setMinimum(localmintime);
				slider->setValue(localmintime);
			}
			else if (localmintime<time && localmintime < maxsettime && localmintime<maxtime && localmintime>=mintime)
			{
				minsettime=localmintime;
				slider->setMinimum(localmintime);
			}
			
		}
	}
	if (callback.id == 48 && callback.trigger == tgui::EditBox::EditBoxCallbacks::TextChanged)
	{
		if (tgui::EditBox::Ptr(gui->get("finishpoint"))->getText() != sf::String("") && tgui::EditBox::Ptr(gui->get("finishpoint"))->getText() != sf::String("-"))
		{
			long double localmaxtime = safestold(std::string(tgui::EditBox::Ptr(gui->get("finishpoint"))->getText()));
			if (localmaxtime>maxtime)
			{
				tgui::EditBox::Ptr(gui->get("finishpoint"))->setText(std::to_string(maxtime));
				slider->setValue(maxtime);
				maxsettime=maxtime;
			}
			else if (localmaxtime<minsettime && finishpointclock.getElapsedTime().asSeconds()>=1 && localmaxtime>mintime)
			{
				tgui::EditBox::Ptr(gui->get("finishpoint"))->setText(std::to_string(minsettime + 1));
				maxsettime=minsettime + 1;
			}
			else if (localmaxtime > time && localmaxtime > minsettime && localmaxtime<maxtime)
			{
				maxsettime=localmaxtime;
				slider->setMaximum(localmaxtime);
			}
			else if (localmaxtime<time && localmaxtime > minsettime && localmaxtime<maxtime)
			{
				maxsettime=localmaxtime;
				slider->setMaximum(localmaxtime);
				slider->setValue(localmaxtime);
			}
		}
	}
	return true; 
};
bool GUIManager::acceptCallbackPicture(tgui::Callback callback, tgui::Picture::Ptr)
{
	// no pictures release callbacks so this function only exists for completeness
	return true;
}
bool GUIManager::acceptCallbackLoadingBar(tgui::Callback callback, tgui::LoadingBar::Ptr  loadingbar)
{
	//the only loading bar will release callbacks if its value changes
	if (loadingbar->getValue() != loadingbar->getMaximum())
	{
		loadingbar->setText("Simulating");
		loadingbar->setValue((loadingbar->getMaximum())*percentsimulated);
	}
	else if (loadingbar->getValue() == loadingbar->getMaximum())
	{
		loadingbar->setText("Simulated");
	}
	return true; 
};
bool GUIManager::acceptCallbackRadioButton(tgui::Callback callback, tgui::RadioButton::Ptr radiobutton)
{
	if (callback.id == 37 && callback.trigger == tgui::ClickableWidget::ClickableWidgetCallbacks::LeftMouseClicked && radiobutton->getCallbackId()>=30 && radiobutton->getCallbackId()<=32)
	{
		if (units == m)
		{
			(tgui::RadioButton::Ptr(gui->get("radiom")))->check();
		}
		if (units == cm)
		{
			(tgui::RadioButton::Ptr(gui->get("radiocm")))->check();
		}
		if (units == mm)
		{
			(tgui::RadioButton::Ptr(gui->get("radiomm")))->check();
		}
	}
	else if (callback.id == 79 && callback.trigger == tgui::ClickableWidget::ClickableWidgetCallbacks::LeftMouseClicked && radiobutton->getCallbackId()>=93 && radiobutton->getCallbackId()<=102)
	{
		if (radiobutton->isChecked())
		{
			loadSettingsFromFile(radiobutton->getCallbackId() - 92);
		}
	}
	else if (callback.id == 80 && callback.trigger == tgui::ClickableWidget::ClickableWidgetCallbacks::LeftMouseClicked && radiobutton->getCallbackId() >= 83 && radiobutton->getCallbackId() <= 92)
	{
		if (radiobutton->isChecked())
		{
			saveSettingsToFile(radiobutton->getCallbackId() - 82);
		}
	}
	return true;
}

GUIManager::GUIManager(WaterEntityManager* watermanager1)
{
	//standard expected constructor for GUIManager
	//will set all values to standard
	//there is no better way to do this
	ptr_watermanager = watermanager1;
	time = 0;
	maxsettime=0;
	minsettime = 0;
	maxtime=0;
	mintime = 0;
	timesimulated = 0;
	percentsimulated=0;
	topheight=0.5;
	topradius=0.3;
	topholeradius=0.012;
	topholeheight=0.1;
	topholeposition== Bucket::HolePosition::Side;
	topinitialvolume = 0.0989600;
	botheight=0.5;
	botradius=0.3;
	botholeposition = Bucket::HolePosition::Bottom;
	botholeradius=0.012;
	
	botholeheight=0;
	botinitialvolume = 0.000000;
	alpha=0.62;
	distance=0.08;
	gravity=9.81;
	timestep=0.1;
	topvolume=0; 
	topvolumepercent=0;
	topwaterheight=0;
	topflowout=0;
	topexitvelocity=0;
	units = m;
	botvolume=0;
	botvolumepercent=0;
	botwaterheight=0;
	botflowout=0;
	botexitvelocity=0;
	fallvolume=0;
	fallmeanvelocity=0;
	fallflowout=0;
	speed = 1;
	finetocontinuesimulating = true;
	playing = false;
	timetoplayfrom;
}

GUIManager::GUIManager(){
	//this is the default constructor for GUIManager
	//should never be called explicitly but needs to exist
	time = 0; 
};

void GUIManager::makeWidgetValid(const tgui::Callback& callback)
{
	//this will make the widget that released callback valid(or attempt to) 
	//in the case of most editboxes it will make sure that no invalid characters will be left in the box 
	//this will also make the time-related widgets valid
	//a switch statement is used rather than a for loop since only the sender of callback should be made valid, not every widget
	switch (callback.id)
	{
	case 4:
		if (tgui::EditBox::Ptr(gui->get("topheight"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("topheight"))->setText(sf::String("0"));
		}
		break;
	case 6:
		if (tgui::EditBox::Ptr(gui->get("topradius"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("topradius"))->setText(sf::String("0"));
		}
		break;

	case 10:
		if (tgui::EditBox::Ptr(gui->get("finishpoint"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("topholeradius"))->setText(sf::String("0"));
		}
		break;
	case 12:
		if (tgui::EditBox::Ptr(gui->get("topholeheight"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("topholeheight"))->setText(sf::String("0"));
		}
		break;
	case 114:
		if (tgui::EditBox::Ptr(gui->get("topinitialvolume"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("topinitialvolume"))->setText(sf::String("0"));
		}
		break;
	case 15:
		if (tgui::EditBox::Ptr(gui->get("botheight"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("botheight"))->setText(sf::String("0"));
		}
		break;
	case 17:
		if (tgui::EditBox::Ptr(gui->get("botradius"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("botradius"))->setText(sf::String("0"));
		}
		break;

	case 21:
		if (tgui::EditBox::Ptr(gui->get("botholeradius"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("botholeradius"))->setText(sf::String("0"));
		}
		break;
	case 23:
		if (tgui::EditBox::Ptr(gui->get("botholeheight"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("botholeheight"))->setText(sf::String("0"));
		}
		break;
	case 115:
		if (tgui::EditBox::Ptr(gui->get("botinitialvolume"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("botinitialvolume"))->setText(sf::String("0"));
		}
		break;
	case 26:
		if (tgui::EditBox::Ptr(gui->get("distance"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("distance"))->setText(sf::String("0"));
		}
		break;
	case 28:
		if (tgui::EditBox::Ptr(gui->get("alpha"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("alpha"))->setText(sf::String("0"));
		}
		break;
	case 34:
		if (tgui::EditBox::Ptr(gui->get("gravity"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("gravity"))->setText(sf::String("0"));
		}
		break;
	case 36:
		if (tgui::EditBox::Ptr(gui->get("stepsize"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("stepsize"))->setText(sf::String("0"));
		}
		break;
	case 46:
		if (tgui::Slider::Ptr(gui->get("slider1"))->getValue() < mintime)
		{
			tgui::Slider::Ptr(gui->get("slider1"))->setValue(mintime);
		}
		else if (tgui::Slider::Ptr(gui->get("slider1"))->getValue() > maxtime)
		{
			tgui::Slider::Ptr(gui->get("slider1"))->setValue(maxtime);
		}
	case 52:
		if (tgui::EditBox::Ptr(gui->get("topvolume"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("topvolume"))->setText(sf::String("0"));
		}
		break;
	case 54:
		if (tgui::EditBox::Ptr(gui->get("topvolumepercent"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("topvolumepercent"))->setText(sf::String("0"));
		}
		break;
	case 56:
		if (tgui::EditBox::Ptr(gui->get("topwaterheight"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("topwaterheight"))->setText(sf::String("0"));
		}
		break;
	case 58:
		if (tgui::EditBox::Ptr(gui->get("topflowout"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("topflowout"))->setText(sf::String("0"));
		}
		break;
	case 60:
		if (tgui::EditBox::Ptr(gui->get("topexitvelocity"))->getText() == sf::String("") )
		{
			tgui::EditBox::Ptr(gui->get("topexitvelocity"))->setText(sf::String("0"));
		}
		break;
	case 63:
		if (tgui::EditBox::Ptr(gui->get("botvolume"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("botvolume"))->setText(sf::String("0"));
		}
		break;
	case 65:
		if (tgui::EditBox::Ptr(gui->get("botvolumepercent"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("botvolumepercent"))->setText(sf::String("0"));
		}
		break;
	case 67:
		if (tgui::EditBox::Ptr(gui->get("botwaterheight"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("botwaterheight"))->setText(sf::String("0"));
		}
		break;
	case 69:
		if (tgui::EditBox::Ptr(gui->get("botflowout"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("botflowout"))->setText(sf::String("0"));
		}
		break;
	case 71:
		if (tgui::EditBox::Ptr(gui->get("botexitvelocity"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("botexitvelocity"))->setText(sf::String("0"));
		}
		break;
	case 74:
		if (tgui::EditBox::Ptr(gui->get("fallvolume"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("fallvolume"))->setText(sf::String("0"));
		}
		break;
	case 76:
		if (tgui::EditBox::Ptr(gui->get("fallgapsize"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("fallgapsize"))->setText(sf::String("0"));
		}
		break;
	case 78:
		if (tgui::EditBox::Ptr(gui->get("fallflowout"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("fallflowout"))->setText(sf::String("0"));
		}
		break;
	case 42:
		if (tgui::EditBox::Ptr(gui->get("speed"))->getText() == sf::String(""))
		{
			tgui::EditBox::Ptr(gui->get("speed"))->setText(sf::String("0"));
		}
		break;
	case 45:
		if (tgui::EditBox::Ptr(gui->get("time"))->getText() == sf::String("") || tgui::EditBox::Ptr(gui->get("time"))->getText() == sf::String("-") || tgui::EditBox::Ptr(gui->get("time"))->getText() == sf::String("+") || tgui::EditBox::Ptr(gui->get("time"))->getText() == sf::String(",") || tgui::EditBox::Ptr(gui->get("time"))->getText() == sf::String("."))
		{
			tgui::EditBox::Ptr(gui->get("time"))->setText(sf::String("0"));
		}
		break;
	//below is ensuring that all time-related widgets are valid (specifically startpoint and finishpoint)
	case 47:
		if (tgui::EditBox::Ptr(gui->get("startpoint"))->getText() == sf::String("") || tgui::EditBox::Ptr(gui->get("startpoint"))->getText() == sf::String("-"))
		{
			tgui::EditBox::Ptr(gui->get("startpoint"))->setText(sf::String("0"));
		}
		else if (safestold(std::string(tgui::EditBox::Ptr(gui->get("startpoint"))->getText())) <mintime)
		{
			time = mintime;
			tgui::EditBox::Ptr(gui->get("startpoint"))->setText(std::to_string(mintime));
			tgui::Slider::Ptr(gui->get("slider1"))->setMinimum(mintime);
			tgui::Slider::Ptr(gui->get("slider1"))->setValue(mintime);
		}
		break;
	case 48:

		if (tgui::EditBox::Ptr(gui->get("finishpoint"))->getText() == sf::String("") || tgui::EditBox::Ptr(gui->get("finishpoint"))->getText() == sf::String("-"))
		{
			tgui::EditBox::Ptr(gui->get("finishpoint"))->setText(sf::String("0"));
		}
		else if (safestold(std::string(tgui::EditBox::Ptr(gui->get("finishpoint"))->getText())) > maxtime)
		{
			time = maxtime;
			tgui::EditBox::Ptr(gui->get("finishpoint"))->setText(std::to_string(maxtime));
			tgui::Slider::Ptr(gui->get("slider1"))->setMaximum(maxtime);
			tgui::Slider::Ptr(gui->get("slider1"))->setValue(maxtime);
		}
		break;
	}
}

bool GUIManager::updateReadings()
{
	//this should be called every frame and will ensure that every box that shows readings has the correct ones in it
	//to ensure this it also includes some validation of the timebox-since that will directly interact with the 
	//time value that the other boxes will read at
	if (tgui::EditBox::Ptr(gui->get("time"))->getText() != sf::String("") && tgui::EditBox::Ptr(gui->get("time"))->getText() != sf::String("-"))
	{
		if (tgui::EditBox::Ptr(gui->get("time"))->getText() != sf::String("+") && safestold(std::string(tgui::EditBox::Ptr(gui->get("time"))->getText())) != time)
		{
			time = safestold(std::string(tgui::EditBox::Ptr(gui->get("time"))->getText()));
		}
	}
	else
	{
		tgui::EditBox::Ptr(gui->get("time"))->setText(std::to_string(time));
	}

	//volumepercent=volume/maximumvolume
	topvolumepercent = ptr_watermanager->getEntityAtPosition(0, 0)->getVolumeAtPosition(time / timestep) / (pi*topradius*topradius*topheight);
	botvolumepercent = ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(time / timestep) / (pi*botradius*botradius*botheight);
	
	//next three sets of commands are almost identical but must exist in the current format as there is no identical
	//behaviour of different EditBoxes
	//three cases are units in m, cm and mm
	if (tgui::RadioButton::Ptr(gui->get("radiom"))->isChecked())
	{

		overlaypercenttop.setString(std::string(std::to_string(int(0.5 + (100 * topvolumepercent))) + "%"));
		overlaypercenttop.setColor(sf::Color::White);
		if (int(0.5 + (100 * topvolumepercent))>100)
		{
			overlaypercenttop.setString(sf::String(">100%"));
			overlaypercenttop.setColor(sf::Color::Red);
		}
		else if (overlaypercenttop.getString() == sf::String("100%"))
		{
			overlaypercenttop.setColor(sf::Color::Red);
		}

		overlaypercentbot.setString(std::string(std::to_string(int(0.5 + (100 * botvolumepercent))) + "%"));
		overlaypercentbot.setColor(sf::Color::White);
		if (int(0.5 + (100 * botvolumepercent)) > 100)
		{
			overlaypercentbot.setString(sf::String(">100%"));
			overlaypercentbot.setColor(sf::Color::Red);
		}
		else if (overlaypercentbot.getString() == sf::String("100%"))
		{
			overlaypercentbot.setColor(sf::Color::Red);
		}
		

		tgui::EditBox::Ptr(gui->get("topvolume"))->setText(std::to_string(ptr_watermanager->getEntityAtPosition(0, 0)->getVolumeAtPosition(time / timestep)));
		
		tgui::EditBox::Ptr(gui->get("topvolumepercent"))->setText(std::to_string(100*topvolumepercent));
		tgui::EditBox::Ptr(gui->get("topwaterheight"))->setText(std::to_string(ptr_watermanager->getEntityAtPosition(0, 0)->getVolumeAtPosition(time / timestep) / (pi*topradius*topradius)));
		tgui::EditBox::Ptr(gui->get("topflowout"))->setText(std::to_string(ptr_watermanager->getEntityAtPosition(0, 0)->getRateOfFlowAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("topexitvelocity"))->setText(std::to_string(ptr_watermanager->getEntityAtPosition(0, 0)->getRateOfFlowAtPosition(time / timestep) / (alpha*pi*topholeradius*topholeradius)));

		tgui::EditBox::Ptr(gui->get("botvolume"))->setText(std::to_string(ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("botvolumepercent"))->setText(std::to_string(100*botvolumepercent));
		tgui::EditBox::Ptr(gui->get("botwaterheight"))->setText(std::to_string(ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(time / timestep) / (pi*botradius*botradius)));
		tgui::EditBox::Ptr(gui->get("botflowout"))->setText(std::to_string(ptr_watermanager->getEntityAtPosition(2, 0)->getRateOfFlowAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("botexitvelocity"))->setText(std::to_string(ptr_watermanager->getEntityAtPosition(2, 0)->getRateOfFlowAtPosition(time / timestep) / (alpha*pi*botholeradius*botholeradius)));

		tgui::EditBox::Ptr(gui->get("fallvolume"))->setText(std::to_string(ptr_watermanager->getEntityAtPosition(1, 0)->getVolumeAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("fallgapsize"))->setText(std::to_string(distance + (botholeheight - (ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(time / timestep) / (pi*botradius*botradius)))));
		tgui::EditBox::Ptr(gui->get("fallflowout"))->setText(std::to_string(ptr_watermanager->getEntityAtPosition(1, 0)->getRateOfFlowAtPosition(time / timestep)));
	}
	else if (tgui::RadioButton::Ptr(gui->get("radiocm"))->isChecked())
	{
		overlaypercenttop.setString(std::string(std::to_string(int(0.5 + (100 * topvolumepercent))) + "%"));
		overlaypercenttop.setColor(sf::Color::White);
		if (int(0.5 + (100 * topvolumepercent))>100)
		{
			overlaypercenttop.setString(sf::String(">100%"));
			overlaypercenttop.setColor(sf::Color::Red);
		}
		else if (overlaypercenttop.getString() == sf::String("100%"))
		{
			overlaypercenttop.setColor(sf::Color::Red);
		}

		overlaypercentbot.setString(std::string(std::to_string(int(0.5 + (100 * botvolumepercent))) + "%"));
		overlaypercentbot.setColor(sf::Color::White);
		if (int(0.5 + (100 * botvolumepercent)) > 100)
		{
			overlaypercentbot.setString(sf::String(">100%"));
			overlaypercentbot.setColor(sf::Color::Red);
		}
		else if (overlaypercentbot.getString() == sf::String("100%"))
		{
			overlaypercentbot.setColor(sf::Color::Red);
		}


		tgui::EditBox::Ptr(gui->get("topvolume"))->setText(std::to_string(100*(ptr_watermanager->getEntityAtPosition(0, 0)->getVolumeAtPosition(time / timestep))));
		tgui::EditBox::Ptr(gui->get("topvolumepercent"))->setText(std::to_string(100 * topvolumepercent));
		tgui::EditBox::Ptr(gui->get("topwaterheight"))->setText(std::to_string(100*ptr_watermanager->getEntityAtPosition(0, 0)->getVolumeAtPosition(time / timestep) / (pi*topradius*topradius)));
		tgui::EditBox::Ptr(gui->get("topflowout"))->setText(std::to_string(100*ptr_watermanager->getEntityAtPosition(0, 0)->getRateOfFlowAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("topexitvelocity"))->setText(std::to_string(100*ptr_watermanager->getEntityAtPosition(0, 0)->getRateOfFlowAtPosition(time / timestep) / (alpha*pi*topholeradius*topholeradius)));

		tgui::EditBox::Ptr(gui->get("botvolume"))->setText(std::to_string(100*100*100*ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("botvolumepercent"))->setText(std::to_string(100 * botvolumepercent));
		tgui::EditBox::Ptr(gui->get("botwaterheight"))->setText(std::to_string(100*ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(time / timestep) / (pi*botradius*botradius)));
		tgui::EditBox::Ptr(gui->get("botflowout"))->setText(std::to_string(100 * 100*100*ptr_watermanager->getEntityAtPosition(2, 0)->getRateOfFlowAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("botexitvelocity"))->setText(std::to_string(100 * ptr_watermanager->getEntityAtPosition(2, 0)->getRateOfFlowAtPosition(time / timestep) / (alpha*pi*botholeradius*botholeradius)));

		tgui::EditBox::Ptr(gui->get("fallvolume"))->setText(std::to_string(100*100*100*ptr_watermanager->getEntityAtPosition(1, 0)->getVolumeAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("fallgapsize"))->setText(std::to_string(100*(distance + (botholeheight - (ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(time / timestep) / (pi*botradius*botradius))))));
		tgui::EditBox::Ptr(gui->get("fallflowout"))->setText(std::to_string(100*100*100*ptr_watermanager->getEntityAtPosition(1, 0)->getRateOfFlowAtPosition(time / timestep)));
	}
	else if (tgui::RadioButton::Ptr(gui->get("radiomm"))->isChecked())
	{
		overlaypercenttop.setString(std::string(std::to_string(int(0.5 + (100 * topvolumepercent))) + "%"));
		overlaypercenttop.setColor(sf::Color::White);
		if (int(0.5 + (100 * topvolumepercent))>100)
		{
			overlaypercenttop.setString(sf::String(">100%"));
			overlaypercenttop.setColor(sf::Color::Red);
		}
		else if (overlaypercenttop.getString() == sf::String("100%"))
		{
			overlaypercenttop.setColor(sf::Color::Red);
		}

		overlaypercentbot.setString(std::string(std::to_string(int(0.5 + (100 * botvolumepercent))) + "%"));
		overlaypercentbot.setColor(sf::Color::White);
		if (int(0.5 + (100 * botvolumepercent)) > 100)
		{
			overlaypercentbot.setString(sf::String(">100%"));
			overlaypercentbot.setColor(sf::Color::Red);
		}
		else if (overlaypercentbot.getString() == sf::String("100%"))
		{
			overlaypercentbot.setColor(sf::Color::Red);
		}


		tgui::EditBox::Ptr(gui->get("topvolume"))->setText(std::to_string(1000 * 1000*1000*(ptr_watermanager->getEntityAtPosition(0, 0)->getVolumeAtPosition(time / timestep))));
		tgui::EditBox::Ptr(gui->get("topvolumepercent"))->setText(std::to_string(100 * topvolumepercent));
		tgui::EditBox::Ptr(gui->get("topwaterheight"))->setText(std::to_string(1000 * ptr_watermanager->getEntityAtPosition(0, 0)->getVolumeAtPosition(time / timestep) / (pi*topradius*topradius)));
		tgui::EditBox::Ptr(gui->get("topflowout"))->setText(std::to_string(1000*1000*1000*ptr_watermanager->getEntityAtPosition(0, 0)->getRateOfFlowAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("topexitvelocity"))->setText(std::to_string(1000*ptr_watermanager->getEntityAtPosition(0, 0)->getRateOfFlowAtPosition(time / timestep) / (alpha*pi*topholeradius*topholeradius)));

		tgui::EditBox::Ptr(gui->get("botvolume"))->setText(std::to_string(1000 *1000*1000* ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("botvolumepercent"))->setText(std::to_string(100 * botvolumepercent));
		tgui::EditBox::Ptr(gui->get("botwaterheight"))->setText(std::to_string(1000 * ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(time / timestep) / (pi*botradius*botradius)));
		tgui::EditBox::Ptr(gui->get("botflowout"))->setText(std::to_string(1000 * 1000*1000*ptr_watermanager->getEntityAtPosition(2, 0)->getRateOfFlowAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("botexitvelocity"))->setText(std::to_string(1000 * ptr_watermanager->getEntityAtPosition(2, 0)->getRateOfFlowAtPosition(time / timestep) / (alpha*pi*botholeradius*botholeradius)));
		
		tgui::EditBox::Ptr(gui->get("fallvolume"))->setText(std::to_string(1000*1000*1000*ptr_watermanager->getEntityAtPosition(1, 0)->getVolumeAtPosition(time / timestep)));
		tgui::EditBox::Ptr(gui->get("fallgapsize"))->setText(std::to_string(distance + (botholeheight - (ptr_watermanager->getEntityAtPosition(2, 0)->getVolumeAtPosition(time / timestep) / (pi*botradius*botradius)))));
		tgui::EditBox::Ptr(gui->get("fallflowout"))->setText(std::to_string(1000*1000*1000*ptr_watermanager->getEntityAtPosition(1, 0)->getRateOfFlowAtPosition(time / timestep)));
	}
	//below will update the graphical representation and the savenames along with the readings
	updateBuckets();
	updateSaveNamesFromFile();
	return true;
}

bool GUIManager::updateTimes(sf::Time timeelapsed)
{
	//this will update the slider position and times while the simulation is playing
	//this will not validate time-related widgets 
	if (playing)
	{
		if (timetoplayfrom + (timeelapsed.asSeconds()*speed) <= maxsettime)
		{
			tgui::EditBox::Ptr(gui->get("time"))->focus();
			tgui::EditBox::Ptr(gui->get("time"))->setText(sf::String(std::to_string(timetoplayfrom + (timeelapsed.asSeconds()*speed))));
			time = timetoplayfrom + timeelapsed.asSeconds();
			tgui::EditBox::Ptr(gui->get("time"))->setText(sf::String(std::to_string(timetoplayfrom + (timeelapsed.asSeconds()*speed))));
			tgui::Slider::Ptr(gui->get("slider1"))->setValue(timetoplayfrom + (timeelapsed.asSeconds()*speed));
		}
		else
		{
			playing = false;
			tgui::EditBox::Ptr(gui->get("time"))->setText(std::to_string(maxsettime));
			time = maxsettime;
			tgui::EditBox::Ptr(gui->get("time"))->setText(std::to_string(maxsettime));
			tgui::Slider::Ptr(gui->get("slider1"))->setValue(maxsettime);
		}
	}
	return true;
};

bool GUIManager::updateBuckets()
{
	//this will update the graphical representation
	//this will change the dimensions and colours of the basic SFML shapes
	if (topholeposition == Bucket::HolePosition::Bottom)
	{
		bucketoutlinetop = sf::RectangleShape(sf::Vector2f(432, 184));
		bucketoutlinetop.setPosition(sf::Vector2f(384, 25));
		bucketoutlinetop.setFillColor(sf::Color::Transparent);
		bucketoutlinetop.setOutlineThickness(2);
		bucketoutlinetop.setOutlineColor(sf::Color::Black);

		bucketholetop = sf::RectangleShape(sf::Vector2f(432 * (2 * topholeradius / topradius), (184 * (topholeheight / topheight))));
		bucketholetop.setPosition(sf::Vector2f(600 - 432 * (topholeradius / topradius), 25 + (184 - 184 * (topholeheight / topheight))));
		bucketholetop.setFillColor(sf::Color::Transparent);
		bucketholetop.setOutlineThickness(-2);
		bucketholetop.setOutlineColor(sf::Color::Black);

		if (topvolumepercent > topholeheight / topheight)
		{
			bucketwaterfalltop = sf::RectangleShape(sf::Vector2f(864 * (topholeradius / topradius), 92 + (184 * (1 - botvolumepercent))));
			bucketwaterfalltop.setPosition(sf::Vector2f(600 - (432 * topholeradius / topradius), 209));
			bucketwaterfalltop.setFillColor(sf::Color::Blue);
		}
		else
		{
			bucketwaterfalltop = sf::RectangleShape(sf::Vector2f(1, 1));
			bucketwaterfalltop.setPosition(0, 0);
			bucketwaterfalltop.setFillColor(sf::Color::Transparent);
		}
		bucketwatertop = sf::RectangleShape(sf::Vector2f(432, 184 * topvolumepercent));
		bucketwatertop.setPosition(384, 25 + (184 * (1 - topvolumepercent)));
		bucketwatertop.setFillColor(sf::Color::Blue);
	}
	else if (topholeposition==Bucket::HolePosition::Side)
	{
		bucketoutlinetop = sf::RectangleShape(sf::Vector2f(288, 184));
		bucketoutlinetop.setPosition(sf::Vector2f(384, 25));
		bucketoutlinetop.setFillColor(sf::Color::Transparent);
		bucketoutlinetop.setOutlineThickness(2);
		bucketoutlinetop.setOutlineColor(sf::Color::Black);

		bucketholetop = sf::RectangleShape(sf::Vector2f(18, 184 * (2 * topholeradius / topheight)));
		bucketholetop.setPosition(654, 25 + (184 - 184 * ((2 * topholeradius / topheight) + (topholeheight / topheight))));
		bucketholetop.setFillColor(sf::Color::Transparent);
		bucketholetop.setOutlineThickness(-2);
		bucketholetop.setOutlineColor(sf::Color::Black);

		if (topvolumepercent > ((2 * topholeradius) + topholeheight) / topheight)
		{
			bucketwaterfalltop = sf::RectangleShape(sf::Vector2f(34, 92 +(184*((2*topholeradius/topheight) + topholeheight/topheight))+(184*(1-botvolumepercent))));
			bucketwaterfalltop.setPosition(672, 25 + (184 - ((368 * topholeradius / topheight)+(184*topholeheight/topheight))));
			bucketwaterfalltop.setFillColor(sf::Color::Blue);
		}
	
		else if (topvolumepercent <= topholeheight / topheight)
		{
			bucketwaterfalltop = sf::RectangleShape(sf::Vector2f(1, 1));
			bucketwaterfalltop.setPosition(0, 0);
			bucketwaterfalltop.setFillColor(sf::Color::Transparent);

		}
		else
		{
			bucketwaterfalltop = sf::RectangleShape(sf::Vector2f(34, 92 + (184 * topvolumepercent) + (184 * (1 - botvolumepercent))));
			bucketwaterfalltop.setPosition(672, 25 + (184 * (1 - topvolumepercent)));
			bucketwaterfalltop.setFillColor(sf::Color::Blue);
		}

		bucketwatertop = sf::RectangleShape(sf::Vector2f(288, 184 * topvolumepercent));
		bucketwatertop.setPosition(384, 25 + (184 * (1 - topvolumepercent)));
		bucketwatertop.setFillColor(sf::Color::Blue);
	}

	if (botholeposition == Bucket::HolePosition::Bottom)
	{
		bucketoutlinebot = sf::RectangleShape(sf::Vector2f(432, 184));
		bucketoutlinebot.setPosition(sf::Vector2f(384, 301));
		bucketoutlinebot.setFillColor(sf::Color::Transparent);
		bucketoutlinebot.setOutlineThickness(2);
		bucketoutlinebot.setOutlineColor(sf::Color::Black);

		bucketholebot = sf::RectangleShape(sf::Vector2f(432 * (2 * botholeradius / botradius), (184 * (botholeheight / botheight))));
		bucketholebot.setPosition(sf::Vector2f(600 - 432 * (botholeradius / botradius), 301 + (184 - 184 * (botholeheight / botheight))));
		bucketholebot.setFillColor(sf::Color::Transparent);
		bucketholebot.setOutlineThickness(-2);
		bucketholebot.setOutlineColor(sf::Color::Black);

		if (botvolumepercent > botholeheight / botheight)
		{
			bucketwaterfallbot = sf::RectangleShape(sf::Vector2f(864 * (botholeradius / botradius), 25));
			bucketwaterfallbot.setPosition(600 - (432 * botholeradius / botradius), 485);
			bucketwaterfallbot.setFillColor(sf::Color::Blue);
		}
		else
		{
			bucketwaterfallbot = sf::RectangleShape(sf::Vector2f(1, 1));
			bucketwaterfallbot.setPosition(0, 0);
			bucketwaterfallbot.setFillColor(sf::Color::Transparent);
		}
		bucketwaterbot = sf::RectangleShape(sf::Vector2f(432, 184 * botvolumepercent));
		bucketwaterbot.setPosition(384, 301 + (184 * (1 - botvolumepercent)));
		bucketwaterbot.setFillColor(sf::Color::Blue);
	}
	else if (botholeposition==Bucket::HolePosition::Side)
	{
		bucketoutlinebot = sf::RectangleShape(sf::Vector2f(288, 184));
		bucketoutlinebot.setPosition(sf::Vector2f(528, 301));
		bucketoutlinebot.setFillColor(sf::Color::Transparent);
		bucketoutlinebot.setOutlineThickness(2);
		bucketoutlinebot.setOutlineColor(sf::Color::Black);

		bucketholebot = sf::RectangleShape(sf::Vector2f(18, 184 * (2 * botholeradius / botheight)));
		bucketholebot.setPosition(528, 301 + (184 - 184 * ((2 * botholeradius / botheight) + (botholeheight / botheight))));
		bucketholebot.setFillColor(sf::Color::Transparent);
		bucketholebot.setOutlineThickness(-2);
		bucketholebot.setOutlineColor(sf::Color::Black);

		if (botvolumepercent > ((2 * botholeradius) + botholeheight) / botheight)
		{
			bucketwaterfallbot = sf::RectangleShape(sf::Vector2f(34, 25+(184 * botholeheight / botheight) + (184 * 2 * botholeradius / botheight)));
			bucketwaterfallbot.setPosition(494, 485 - (184 * botholeradius*2/botheight)-(184*botholeheight/botheight));
			bucketwaterfallbot.setFillColor(sf::Color::Blue);
		}
		else if (botvolumepercent <= botholeheight / botheight)
		{
			bucketwaterfallbot = sf::RectangleShape(sf::Vector2f(1, 1));
			bucketwaterfallbot.setPosition(0, 0);
			bucketwaterfallbot.setFillColor(sf::Color::Transparent);
		}
		else 
		{
			bucketwaterfallbot = sf::RectangleShape(sf::Vector2f(34, 25 + (184 * botvolumepercent)));
			bucketwaterfallbot.setPosition(494, 485 - (184 * botvolumepercent));
			bucketwaterfallbot.setFillColor(sf::Color::Blue);
		}

		bucketwaterbot = sf::RectangleShape(sf::Vector2f(288, 184 * botvolumepercent));
		bucketwaterbot.setPosition(528, 301 + (184 * (1 - botvolumepercent)));
		bucketwaterbot.setFillColor(sf::Color::Blue);
	}

	return true;
}

void GUIManager::updateSaveNamesFromFile()
{
	//this will update the displayed save names of the save files
	updateSaveBoxes(); //this makes sure that the vector of saveboxes is correct so that they can be iterated through easily
	for (int x = 0; x <=9; x++)
	{
		std::ifstream reader(std::string("Saves/preset" + std::to_string(x+1) + ".txt"));
		std::string savename;
		std::getline(reader, savename);
		saveboxes[x]->setText(savename);
	}
}

void GUIManager::updateSaveBoxes()
{
	//this appends pointers to every savebox to the vector of save boxes
	saveboxes.clear();
	saveboxes.push_back(gui->get("savename1"));
	saveboxes.push_back(gui->get("savename2"));
	saveboxes.push_back(gui->get("savename3"));
	saveboxes.push_back(gui->get("savename4"));
	saveboxes.push_back(gui->get("savename5"));
	saveboxes.push_back(gui->get("savename6"));
	saveboxes.push_back(gui->get("savename7"));
	saveboxes.push_back(gui->get("savename8"));
	saveboxes.push_back(gui->get("savename9"));
	saveboxes.push_back(gui->get("savename10"));
}

bool GUIManager::loadSettingsFromFile(int filenum)
{
	//this will load the settings from the specified filenum(which is 1 to 10 inclusive)
	
	std::ifstream reader(std::string("Saves/preset" + std::to_string(filenum) + ".txt"));
	//must read every line one after the other and apply the readings taken from it
	std::string line;
	std::getline(reader, line);
	std::getline(reader, line);
	std::getline(reader, line);
	topheight = safestold(line);
	std::getline(reader, line);
	topholeradius = safestold(line);
	std::getline(reader, line);
	if (line == "1")
	{
		topholeposition = Bucket::HolePosition::Bottom;
	}
	else
	{
		topholeposition = Bucket::HolePosition::Side;
	}
	std::getline(reader, line);
	topholeradius = safestold(line);
	std::getline(reader, line);
	topholeheight = safestold(line);
	std::getline(reader, line);
	topinitialvolume = safestold(line);
	std::getline(reader, line);
	std::getline(reader, line);
	botheight = safestold(line);
	std::getline(reader, line);
	botradius = safestold(line);
	std::getline(reader, line);
	if (line == "0")
	{
		botholeposition = Bucket::HolePosition::Side;
	}
	else
	{
		botholeposition = Bucket::HolePosition::Bottom;
	}
	std::getline(reader, line);
	botholeradius = safestold(line);
	std::getline(reader,line);
	std::getline(reader, line);
	botinitialvolume = safestold(line);
	std::getline(reader, line);
	std::getline(reader, line);
	distance = safestold(line);
	std::getline(reader, line);
	std::getline(reader, line);
	alpha = safestold(line);
	std::getline(reader, line);
	gravity = safestold(line);
	std::getline(reader, line);
	timestep = safestold(line);
	units = m;
	//reader must be closed once finished to avoid problems
	reader.close();
	//below causes the call of leftMouseClicked from the revert button
	//this makes sure that the displayed settings are the ones that have just been applied
	tgui::Button::Ptr(gui->get("revert"))->leftMousePressed(1,1);
	tgui::Button::Ptr(gui->get("revert"))->leftMouseReleased(1,1);
	return true;
};

bool GUIManager::saveSettingsToFile(int filenum)
{
	//filenum is between 1 and 10 inclusive
	//this will save all the settings that are currently held by the GUIManager to the correct .txt file 
	
	std::ofstream writer=std::ofstream(std::string("Saves/preset" + std::to_string(filenum) + ".txt"), std::ofstream::trunc);
	//below, each line must be written one after the other 
	writer << std::string(tgui::EditBox::Ptr(gui->get("savename"))->getText()) << std::endl;;
	writer << std::string("///topbucket///") << std::endl;
	writer << topheight << std::endl;
	writer << topradius << std::endl;
	if (topholeposition == Bucket::HolePosition::Bottom)
	{
		writer << "1" << std::endl;
	}
	else
	{
		writer << "0" << std::endl;
	}
	writer << topholeradius << std::endl;
	writer << topholeheight << std::endl;
	writer << topinitialvolume << std::endl;
	
	writer << std::string("///botbucket///") << std::endl;
	writer << botheight << std::endl;
	writer << botradius << std::endl;
	if (botholeposition == Bucket::HolePosition::Bottom)
	{
		writer << "1" << std::endl;
	}
	else
	{
		writer << "0" << std::endl;
	}
	writer << botholeradius << std::endl;
	writer << botholeheight << std::endl;
	writer << botinitialvolume << std::endl;

	writer << std::string("///waterfall///") << std::endl;
	writer << distance << std::endl;

	writer << std::string("///settings///") << std::endl;
	writer << alpha << std::endl;
	writer << gravity << std::endl;
	writer << timestep << std::endl;
	//writer must be closed once finished to avoid future problems
	writer.close();
	return true;
};

void GUIManager::setToExistingValues(const tgui::Callback& callback)
{
	//this function will set the value of the widget with ID passed through a callback
	//to the value stored by GUIManager behind the scenes 
	//could theoretically be able to accomodate every widget but no other widgets ever call this function or have need of it
	//so it would not achieve anything by adding that functionality at the moment
	switch(callback.id)
	{
	case 45:
		tgui::EditBox::Ptr(gui->get("time"))->setText(sf::String(std::to_string(time)));
		break;
	case 47:
		tgui::EditBox::Ptr(gui->get("startpoint"))->setText(sf::String(std::to_string(minsettime)));
	break;

	case 48:
		tgui::EditBox::Ptr(gui->get("finishpoint"))->setText(sf::String(std::to_string(maxsettime)));
	break;
	
	}
}