#pragma once
#include <string>
#include <vector>
#include "Interaction.h"
#include <map>
class Area
{
	std::pair<int,int> entryDetectionChance;
	std::pair<int,int> exitDetectionChance;
	std::string areaName;
	std::string areaDescription;
	std::map<std::string, Interaction*> interactions;

public:
	Area(std::string areaName, int entryDetectionChanceWorker, int entryDetectionChanceSoldier, int exitDetectionChanceWorker, int exitDetectionChanceSoldier, std::string areaDescription);
	~Area();
	void addInteraction(Interaction* interaction);
	void displayInteractions();
	void completeInteration(std::string interactionName);

	//getters

	std::pair<int, int> getEntryDetectionChance();
	std::pair<int, int> getExitDetectionChance();
	std::string getAreaDescription();

};

