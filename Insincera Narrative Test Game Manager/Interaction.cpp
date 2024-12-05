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

void Interaction::addExclusiveInteraction(Interaction* exclusiveInteraction)
{
	exclusiveInteractions.emplace_back(exclusiveInteraction);
}

void Interaction::completeInteraction()
{
	if (!isInteractable)
	{
		throw std::exception("Interaction is not interactable");
	}
	setInteractionCompleted(true);
	for (auto& interaction : exclusiveInteractions)
	{
		interaction->setIsInteractable(false);
	}
}

void Interaction::setInteractionCompleted(bool interactionCompleted)
{
	this->interactionCompleted = interactionCompleted;
}

void Interaction::setIsInteractable(bool isInteractable)
{
	this->isInteractable = isInteractable;
}


