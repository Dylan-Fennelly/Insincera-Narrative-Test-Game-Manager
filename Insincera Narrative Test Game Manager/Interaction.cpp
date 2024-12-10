#include "Interaction.h"


Interaction::Interaction(std::string interactionName,int detectionChanceWorker,int detectionChanceSoldier, int dangerContribution, std::string interactionDescription)
	:interactionName(interactionName),
	detectionChance(std::make_pair(detectionChanceWorker, detectionChanceSoldier)),//worker, soldier
	dangerContribution(dangerContribution),
	interactionDescription(interactionDescription)
{
}

Interaction::~Interaction()
{
	//we dont need to delete the contents of the vector as this class does not own the memory of the interactions
	//but rather just points to them
	//we dont need to delete the pointers as they are not dynamically allocated and 
	//will be deleted when the vector goes out of scope

}

std::string Interaction::getInteractionName()
{
	return interactionName;
}
std::pair<int, int> Interaction::getDetectionChance()
{
	return detectionChance;
}

int Interaction::getDangerContribution()
{
	return dangerContribution;
}

std::string Interaction::getInteractionDescription()
{
	return interactionDescription;
}

bool Interaction::getInteractionCompleted()
{
	return this->interactionCompleted;
}

bool Interaction::getIsInteractable()
{
	return this->isInteractable;
}


void Interaction::addExclusiveInteraction(Interaction* exclusiveInteraction)
{
	exclusiveInteractions.emplace_back(exclusiveInteraction);
}
//Todo: this feels messy and the random number generation should be tider, maybe it should be given to a utility class
bool Interaction::completeInteraction()
{
	if (!isInteractable)
	{
		throw std::exception("Interaction is not interactable");
	}
	setInteractionCompleted(true);
	setIsInteractable(false);
	

	for (auto& interaction : exclusiveInteractions)
	{
		interaction->setIsInteractable(false);
	}
	//true if the interaction was completed without being caught


	// Generate two separate dice rolls
	int diceRollWorker = rand() % 100 + 1;
	int diceRollSoldier = rand() % 100 + 1;

	// Check if caught by either group
	bool caughtByWorker = diceRollWorker <= detectionChance.first;
	bool caughtBySoldier = diceRollSoldier <= detectionChance.second;

	if (caughtByWorker || caughtBySoldier) {
		return true; // Player was caught
	}

	return false; // Interaction completed while being caught

}

void Interaction::setInteractionCompleted(bool interactionCompleted)
{
	this->interactionCompleted = interactionCompleted;
}

void Interaction::setIsInteractable(bool isInteractable)
{
	this->isInteractable = isInteractable;
}


