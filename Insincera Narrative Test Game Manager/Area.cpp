#include "Area.h"
#include <iostream>

Area::Area(std::string areaName, int entryDetectionChanceWorker,int entryDetectionChanceSoldier, int exitDetectionChanceWorker,int exitDetectionChanceSoldier, std::string areaDescription)
	:areaName(areaName),
	entryDetectionChance(std::make_pair(entryDetectionChanceWorker,entryDetectionChanceSoldier)),
	exitDetectionChance(std::make_pair(exitDetectionChanceWorker, exitDetectionChanceSoldier)),
	areaDescription(areaDescription)
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

void Area::completeInteration(std::string interactionName)
{
	auto interaction = interactions.find(interactionName);
	if (interaction == interactions.end())
	{
		throw std::exception("Interaction not found");
	}
	interaction->second->completeInteraction();
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
