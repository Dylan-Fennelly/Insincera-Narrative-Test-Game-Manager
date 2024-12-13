#pragma once
#include <string>
#include <vector>
#include "Interaction.h"
#include <map>
class Area
{
	std::string areaName;
	std::string areaDescription;
	std::pair<int,int> entryDetectionChance;
	std::pair<int,int> exitDetectionChance;
	std::map<std::string, Interaction*> interactions;
	std::vector<Area*> connectedAreas;
	int culmulativeDanger = 0;
	bool isCombatArea = false;

public:
	Area(std::string areaName, int entryDetectionChanceWorker, int entryDetectionChanceSoldier, int exitDetectionChanceWorker, int exitDetectionChanceSoldier, std::string areaDescription);
	~Area();
	void addInteraction(Interaction* interaction);
	void displayInteractions();
	void addConnectedArea(Area* connectedArea);

	

	//getters

	std::pair<int, int> getEntryDetectionChance();
	std::pair<int, int> getExitDetectionChance();
	std::string getAreaDescription();
	std::string getAreaName();
	std::vector<Area*>& getConnectedAreas();
	std::map<std::string, Interaction*> getInteractions();
	bool getIsCombatArea();
	//setters
	void setIsCombatArea(bool isCombatArea);
	void setEntryDetectionChance(int detectionChanceWorker, int detectionChanceSoldier);
	void setExitDetectionChance(int detectionChanceWorker, int detectionChanceSoldier);


};

	