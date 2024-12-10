#include "Area.h"
#include <iostream>

Area::Area(std::string areaName, int entryDetectionChanceWorker,int entryDetectionChanceSoldier, int exitDetectionChanceWorker,int exitDetectionChanceSoldier, std::string areaDescription)
	:areaName(areaName),
	areaDescription(areaDescription),
	entryDetectionChance(std::make_pair(entryDetectionChanceWorker,entryDetectionChanceSoldier)),
	exitDetectionChance(std::make_pair(exitDetectionChanceWorker, exitDetectionChanceSoldier))
	
{
}

Area::~Area()
{
}

void Area::addInteraction(Interaction* interaction)
{
	interactions.emplace(interaction->getInteractionName(), interaction);
}

void Area::displayInteractions()
{
	for (auto& interaction : interactions)
	{
		std::cout << interaction.second->getInteractionName() +": " + interaction.second->getInteractionDescription() << std::endl;
	}
}


void Area::addConnectedArea(Area* connectedArea)
{
	connectedAreas.emplace_back(connectedArea);
}



std::pair<int,int> Area::getEntryDetectionChance()
{
	return entryDetectionChance;
}

std::pair<int,int> Area::getExitDetectionChance()
{
	return exitDetectionChance;
}

std::string Area::getAreaDescription()
{
	return areaDescription;
}

std::string Area::getAreaName()
{
	return this->areaName;
}

std::vector<Area*> Area::getConnectedAreas()
{
	return this->connectedAreas;
}

std::map<std::string, Interaction*> Area::getInteractions()
{
	return this->interactions;
}
