#include "Interaction.h"
#include "Utility.h"

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

int Interaction::getNumberOfTimesInteracted()
{
	return this->numberOfTimesInteracted;
}


void Interaction::addExclusiveInteraction(Interaction* exclusiveInteraction)
{
	exclusiveInteractions.emplace_back(exclusiveInteraction);
}

bool Interaction::completeInteraction(int culmativeDanger)
{
	if (!isInteractable)
	{
		throw std::exception("Interaction is not interactable");
	}
	setInteractionCompleted(true);
	setIsInteractable(false);
	incrementNumberOfTimesInteracted();

	for (auto& interaction : exclusiveInteractions)
	{
		interaction->setIsInteractable(false);
	}

	// Generate two separate dice rolls
	int diceRollWorker = Utility::generateRandomNumber(0,100);
	//int diceRollSoldier = Utility::generateRandomNumber(0, 100);

	// Check if caught by either group
	bool caughtByWorker = diceRollWorker <= detectionChance.first +culmativeDanger;
	//bool caughtBySoldier = diceRollSoldier <= detectionChance.second +culmativeDanger;

	return caughtByWorker;

}

void Interaction::incrementNumberOfTimesInteracted()
{
	numberOfTimesInteracted++;
}

void Interaction::resetInteraction(int detectionChanceWorker, int detectionChanceSoldier)
{
	setInteractionCompleted(false);
	setIsInteractable(true);
	detectionChance = std::make_pair(detectionChanceWorker, detectionChanceSoldier);
}

void Interaction::setInteractionCompleted(bool interactionCompleted)
{
	this->interactionCompleted = interactionCompleted;
}

void Interaction::setIsInteractable(bool isInteractable)
{
	this->isInteractable = isInteractable;
}


