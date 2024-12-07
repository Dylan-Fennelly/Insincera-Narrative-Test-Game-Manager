#include "GameManger.h"
#include <iostream>

GameManger::GameManger(Area* starterArea)
	:currentArea(starterArea)
{
	//we need to add the starter area to the areas vector
	areas.emplace_back(starterArea);
	int chanceToEscape = rand() % 100 + 1;
	int chanceToKill = rand() % 100 + 1;
	Area* combatArea = new Area("Combat Area", 0, 0, chanceToEscape, chanceToEscape, "You are in combat");
	Interaction* combatInteraction = new Interaction("Fight the enemy", chanceToKill, chanceToKill, 5, "Use your weapon to fight the enemy!");
	combatArea->addInteraction(combatInteraction);
	areas.emplace_back(combatArea);
}

GameManger::~GameManger()
{
	//if the game manger goes out of scope, we need to delete the areas and interactions
	for (auto& area : areas)
	{
		delete area;
	}
	for (auto& interaction : interactions)
	{
		delete interaction;
	}

}

void GameManger::addArea(Area* area)
{
	//always add the combat area to the areas vector
	Area* combatArea = nullptr;
	for (auto& area : areas)
	{
		if (area->getAreaName() == "Combat Area")
		{
			combatArea = area;
		}
	}
	if (combatArea == nullptr)
	{
		throw std::exception("Combat Area not found");
	}
	area->addConnectedArea(combatArea);
	this->areas.emplace_back(area);
}


void GameManger::addInteraction(Interaction* interaction)
{
	this->interactions.emplace_back(interaction);
}

void GameManger::displayAreas()
{
	auto currentAreaName = currentArea->getAreaName();
	std::cout << "Current Area: " + currentAreaName << std::endl;
	std::cout << "Connected Areas: " << std::endl;
	for (auto& area : currentArea->getConnectedAreas())
	{
		//skip displaying the combat area
		//the player should not be able to move to the combat area on their own
		if (area->getAreaName() == "Combat Area")
		{
			return;
		}
		std::cout << area->getAreaName() << std::endl;
	}
}

void GameManger::displayInteractions()
{
	bool hasInteractable = false;
	for (auto& interaction : currentArea->getInteractions())
	{
		if (interaction.second->getIsInteractable())
		{
			hasInteractable = true;
			auto detectionChance = interaction.second->getDetectionChance();
			std::cout << " - " << interaction.second->getInteractionName() << ": "
				<< interaction.second->getInteractionDescription() << "\n"
				<< "   Chance to get caught: "
				<< detectionChance.first << "% by workers, "
				<< detectionChance.second << "% by soldiers.\n";
			
		}
		if (!hasInteractable)
		{
			std::cout << "No interactions available" << std::endl;
		}
		std::cout << std::endl;
	}
}

void GameManger::completeInteraction(std::string interactionName)
{
	// Find the interaction once
	auto interactionsMap = currentArea->getInteractions();
	auto interactionIter = interactionsMap.find(interactionName);
	if (interactionIter == interactionsMap.end())
	{
		throw std::exception("Interaction not found");
	}

	Interaction* interaction = interactionIter->second;
	bool wasCaught = interaction->completeInteraction();

	if (currentArea->getAreaName() == "Combat Area")
	{
		// Handle the case where the player is in the combat area
		if (wasCaught)
		{
			std::cout << "Player lost the fight" << std::endl;
			endGame(true);
		}
	}
	else
	{
		// Handle the case for non-combat interactions
		if (wasCaught)
		{
			// Enter combat phase if caught
			moveArea("Combat Area");
		}
		addCulmulativeDanger(interaction->getDangerContribution());
	}
}


void GameManger::moveArea(std::string areaName)
{
	//We need to check if the area the player wants to move to is connected to the current area
	//We also need to check if the risk  of moving and calculate the risk of moving to the new area
	//We then dice roll to see if the player gets caught
	//If the player gets caught, we need to enter the combat phase
	//We can then move the player to the a special combat area where the player can fight the enemy
	//If the player wins, we can move the player to the new area they wanted to move to
	//If the player loses, we can end the game and display the interactions the player completed from the master list
	//If the player does not get caught, we can move the player to the new area

	auto connectedAreas = currentArea->getConnectedAreas();
	for (auto& area : connectedAreas)
	{
		if (area->getAreaName() == areaName)
		{
			//check if the player gets caught
			auto detectionChance = area->getEntryDetectionChance();
			auto diceRoll = rand() % 100 + 1;
			if (diceRoll <= detectionChance.first)
			{
				//player gets caught
				//enter combat phase
				//move player to combat area
				//if player wins, move player to new area
				//if player loses, end game
				std::cout << "Player got caught" << std::endl;
				//move player to combat area
				moveArea("Combat Area");
				return;
			}
			else
			{
				currentArea = area;
				return;
			}
		}
	}
	std::cout << "Area not found" << std::endl;


}

void GameManger::displayCurrentArea()
{
	std::cout << currentArea->getAreaName() + ": " + currentArea->getAreaDescription() << std::endl;

}

void GameManger::displayConnectedAreas()
{
	for (auto& area : currentArea->getConnectedAreas())
	{
		std::cout << area->getAreaName() << std::endl;
	}
}

void GameManger::addCulmulativeDanger(int danger)
{
	this->culmulativeDanger += danger;
}

void GameManger::endGame(bool killed)
{
	if (killed)
	{
		std::cout << "Player was killed" << std::endl;
		std::cout << "Game Over" << std::endl;
	}
	else
	{
		std::cout << "Player has successfully escaped" << std::endl;
	}

	std::cout << "Final Culmulative Danger: " << culmulativeDanger << std::endl;
	std::cout << "Interactions Completed: " << std::endl;
	for (auto& interaction : interactions)
	{
		if (interaction->getInteractionCompleted())
		{
			std::cout << interaction->getInteractionName() << std::endl;
		}
	}
	std::cout << "Thank you for playing" << std::endl;
}

void GameManger::moveToCombatArea(Area* areaAfterCombat)
{
	moveArea("Combat Area");
	//we need to add the area the player wanted to move to after the combat phase to the connected areas of the combat area
	//so we need to remove all of the connected areas of the combat area and add the new area
	auto combatArea = currentArea;
	combatArea->getConnectedAreas().clear();
	combatArea->addConnectedArea(areaAfterCombat);

}
