#pragma once
#include <string>
#include <vector>
class Interaction
{
private:
	std::pair<int, int> detectionChance;//worker, soldier, using a pair to store the detection chance for both worker and soldier
	int dangerContribution;// how much danger this interaction contributes to the global danger level
	std::string interactionName;//name of the interaction
	std::string interactionDescription;//description of the interaction
	bool interactionCompleted = false;//if the interaction has been completed
	bool isInteractable = true;//if the interaction is interactable
	std::vector<Interaction*> exclusiveInteractions;//interactions that are exclusive to this interaction ie, if this interaction is completed, the exclusive interactions are no longer interactable

public:
	Interaction(std::string interactionName, int detectionChanceWorker, int detectionChanceSoldier, int dangerContribution, std::string interactionDescription);
	~Interaction();
	
	void addExclusiveInteraction(Interaction* exclusiveInteraction);
	void completeInteraction();

	//getters
	std::string getInteractionName();
	std::pair<int, int> getDetectionChance();
	int getDangerContribution();
	std::string getInteractionDescription();

private:
	//setters
	void setInteractionCompleted(bool interactionCompleted);
	void setIsInteractable(bool isInteractable);
};

