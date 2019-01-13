#ifndef GUIMANAGER_H
#define GUIMANAGER_H 
#include <TGUI\TGUI.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "WaterEntityManager.h"
#include "Bucket.h"
#include "WaterFall.h"
enum UnitSystem{ m, cm, mm };
class GUIManager
{
public:
	GUIManager();
	GUIManager(WaterEntityManager*);
	~GUIManager();
	bool launchProgram();
	bool simulate(long double);
	void newSimulationFromSettings();
	void makeWidgetValid(const tgui::Callback&);
	void startClock(const tgui::Callback&);
	void setToExistingValues(const tgui::Callback&);
	bool acceptCallback(tgui::Callback, tgui::Widget::Ptr);
	bool acceptCallbackEditBox(tgui::Callback, tgui::EditBox::Ptr);
	bool acceptCallbackButton(tgui::Callback, tgui::Button::Ptr);
	bool acceptCallbackLabel(tgui::Callback, tgui::Label::Ptr);
	bool acceptCallbackSlider(tgui::Callback, tgui::Slider::Ptr);
	bool acceptCallbackLoadingBar(tgui::Callback, tgui::LoadingBar::Ptr);
	bool acceptCallbackPicture(tgui::Callback, tgui::Picture::Ptr);
	bool acceptCallbackRadioButton(tgui::Callback, tgui::RadioButton::Ptr);
	bool updateReadings();
	bool updateTimes(sf::Time timeelapsed);
	bool updateBuckets();
	void updateSaveBoxes();
	void updateSaveNamesFromFile();
	bool loadSettingsFromFile(int);
	bool saveSettingsToFile(int);
private:
	sf::RenderWindow* ptr_window;
	tgui::Gui* gui;
	sf::Clock clock;
	sf::Clock finishpointclock;
	sf::Clock startpointclock;
	WaterEntityManager* ptr_watermanager;
	long double time;
	long double maxsettime;
	long double minsettime;
	long double maxtime;
	long double mintime;
	long double timesimulated ;
	std::vector<tgui::Widget::Ptr> widgetpointers;
	long double percentsimulated;
	long double topheight;
	long double topradius;
	Bucket::HolePosition topholeposition; 
	long double topholeradius;
	long double topholeheight;
	long double topinitialvolume;
	long double botheight;
	long double botradius;
	Bucket::HolePosition botholeposition;
	long double botholeradius;
	long double botholeheight;
	long double botinitialvolume;
	long double alpha;
	long double distance;
	long double gravity;
	long double timestep;
	UnitSystem units;
	long double topvolume;
	long double topvolumepercent;
	long double topwaterheight;
	long double topflowout;
	long double topexitvelocity;
	long double botvolume;
	long double botvolumepercent;
	long double botwaterheight;
	long double botflowout;
	long double botexitvelocity;
	long double fallvolume;
	long double fallmeanvelocity;
	long double fallflowout;
	long double speed;
	bool finetocontinuesimulating;
	bool playing;
	std::vector<tgui::Label::Ptr> saveboxes;
	long double timetoplayfrom;
	tgui::Panel::Ptr panelunits;
	tgui::Panel::Ptr panelload;
	tgui::Panel::Ptr panelsave;
	sf::Text overlaypercenttop, overlaypercentbot;
	sf::RectangleShape bucketoutlinetop, bucketoutlinebot, bucketwatertop, bucketwaterbot, bucketwaterfallbot, bucketwaterfalltop,
		bucketholetop, bucketholebot;
	
};

#endif