#include "GameManger.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
//TODO: Fix this constructor to not rely on magic bullshit
GameManager::GameManager(Area* starterArea)
	:currentArea(starterArea)
{
	//we need to add the starter area to the areas vector
	areas.emplace_back(starterArea);
	srand(time(0));
	int chanceToEscapeWorker = rand() % 100 + 1;
	int chanceToEscapeSoldier = rand() % 100 + 1;
	int chanceToKillWorker = rand() % 100 + -40;
	int chanceToKillSoldier = rand() % 100 + -40;
	chanceToKillWorker = abs(chanceToKillWorker);
	chanceToKillSoldier = abs(chanceToKillSoldier);
	Area* combatArea = new Area("Combat Area", 0, 0, 0, 0, "You are in combat");
	Interaction* combatInteraction = new Interaction("Fight the enemy", chanceToKillWorker, chanceToKillSoldier, 5, "Use your weapon to fight the enemy!");
	combatArea->addInteraction(combatInteraction);
	areas.emplace_back(combatArea);
	loadfromJSON("D:\\C++\\Insincera Narrative Test Game Manager\\game.json");
	currentArea->addConnectedArea(findAreaByString("Cool Area"));
}

GameManager::~GameManager()
{
	//Todo: make this deconstuctor acctually work 
	////if the game manger goes out of scope, we need to delete the areas and interactions
	//for (auto& area : areas)
	//{
	//	delete area;
	//}
	//for (auto& interaction : interactions)
	//{
	//	delete interaction;
	//}

}

void GameManager::addArea(Area* area)
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


void GameManager::addInteraction(Interaction* interaction)
{
	this->interactions.emplace_back(interaction);
}

void GameManager::displayAreas()
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
			continue   ;
		}
		std::cout << area->getAreaName() << std::endl;
	}
}

void GameManager::displayInteractions()
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
		
		std::cout << std::endl;
	}
	if (!hasInteractable)
	{
		std::cout << "No interactions available" << std::endl;
	}
}

void GameManager::completeInteraction(std::string interactionName)
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
		else
		{
			//the player can move out of the combat area
			std::cout << "Player won the fight" << std::endl;
			
		}
	}
	else if (interactionName == "Leave the facility" && wasCaught==false)
	{ 
		endGame(false);
	}
	else 
	{
		// Handle the case for non-combat interactions
		if (wasCaught)
		{
			// Enter combat phase if caught
			moveToCombatArea(currentArea->getAreaName());
			
		}
		addCulmulativeDanger(interaction->getDangerContribution());
	}
}

 
void GameManager::moveArea(std::string areaName)
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
				moveToCombatArea(areaName);
				return;
			}
			else
			{
				Area* temp = nullptr;
				if (currentArea->getAreaName() == "Combat Area")
				{
					temp = currentArea;
				}
				currentArea = area;
				//todo:reset the combat area's interaction and reroll numbers
				return;
			}
		}
	}
	if (areaName == "Combat Area")
	{
		currentArea = findAreaByString("Combat Area");
		return;
	}
	std::cout << "Area not found" << std::endl;


}

void GameManager::displayCurrentArea()
{
	std::cout << currentArea->getAreaName() + ": " + currentArea->getAreaDescription() << std::endl;

}

void GameManager::displayConnectedAreas()
{
	for (auto& area : currentArea->getConnectedAreas())
	{
		std::cout << area->getAreaName() + ": " + area->getAreaDescription() << std::endl;
	}
}
//Start using this function to add danger to the global danger level
void GameManager::addCulmulativeDanger(int danger)
{
	this->culmulativeDanger += danger;
}

void GameManager::endGame(bool killed)
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

void GameManager::moveToCombatArea(std::string areaAfterCombat)
{
	moveArea("Combat Area");
	//we need to add the area the player wanted to move to after the combat phase to the connected areas of the combat area
	//so we need to remove all of the connected areas of the combat area and add the new area
	auto combatArea = currentArea;
	combatArea->getConnectedAreas().clear();
	combatArea->addConnectedArea(findAreaByString(areaAfterCombat));

}
 
Area* GameManager::findAreaByString(std::string areaName)
{

	for (auto& area : areas)
	{
		if (area->getAreaName() == areaName)
		{
			return area;
		}
	}

		throw std::exception("Area not found");
}

bool GameManager::getIsGameRunning()
{
	return this->isGameRunning;
}

void GameManager::loadfromJSON(const std::string fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open JSON file: " + fileName);
	}

	nlohmann::json json;
	file >> json;

	// Temporary cache for unresolved connections
	std::vector<std::pair<Area*, std::vector<std::string>>> areaConnectionsCache;
	std::vector<std::pair<Interaction*, std::vector<std::string>>> interactionExclusivesCache;

	// Load areas
	if (json.contains("areas") && json["areas"].is_array())
	{
		for (const auto& areaJson : json["areas"])
		{
			// Parse area details
			std::string name = areaJson.value("name", "Unnamed Area");
			std::string description = areaJson.value("description", "");
			int entryWorker = areaJson.value("entryDetectionChanceWorker", 0);
			int entrySoldier = areaJson.value("entryDetectionChanceSoldier", 0);
			int exitWorker = areaJson.value("exitDetectionChanceWorker", 0);
			int exitSoldier = areaJson.value("exitDetectionChanceSoldier", 0);

			// Create the Area object
			Area* area = new Area(name, entryWorker, entrySoldier, exitWorker, exitSoldier, description);
			areas.emplace_back(area);

			// Cache connected area names for later linking
			if (areaJson.contains("connectedAreas") && areaJson["connectedAreas"].is_array())
			{
				std::vector<std::string> connectedNames;
				for (const auto& connectedAreaName : areaJson["connectedAreas"])
				{
					connectedNames.push_back(connectedAreaName);
				}
				areaConnectionsCache.emplace_back(area, connectedNames);
			}

			// Parse interactions
			if (areaJson.contains("interactions") && areaJson["interactions"].is_array())
			{
				for (const auto& interactionJson : areaJson["interactions"])
				{
					std::string interactionName = interactionJson.value("name", "Unnamed Interaction");
					std::string interactionDescription = interactionJson.value("description", "");
					int detectionWorker = interactionJson.value("detectionChanceWorker", 0);
					int detectionSoldier = interactionJson.value("detectionChanceSoldier", 0);
					int dangerContribution = interactionJson.value("dangerContribution", 0);

					Interaction* interaction = new Interaction(interactionName, detectionWorker, detectionSoldier, dangerContribution, interactionDescription);

					// Cache exclusive interaction names for later linking
					if (interactionJson.contains("exclusiveInteractions") && interactionJson["exclusiveInteractions"].is_array())
					{
						std::vector<std::string> exclusiveNames;
						for (const auto& exclusiveName : interactionJson["exclusiveInteractions"])
						{
							exclusiveNames.push_back(exclusiveName);
						}
						interactionExclusivesCache.emplace_back(interaction, exclusiveNames);
					}

					area->addInteraction(interaction); // Add interaction to the area
					interactions.emplace_back(interaction); // Store interaction globally
				}
			}
		}
	}

	// Resolve and link connected areas
	for (const auto& [area, connectedNames] : areaConnectionsCache)
	{
		for (const std::string& connectedName : connectedNames)
		{
			Area* connectedArea = findAreaByString(connectedName);
			if (connectedArea)
			{
				area->addConnectedArea(connectedArea); // Assume this adds the pointer to the connected area
			}
			else
			{
				std::cerr << "Warning: Connected area '" << connectedName << "' not found for area '" << area->getAreaName() << "'\n";
			}
		}
	}

	// Resolve exclusive interaction pointers
	for (const auto& [interaction, exclusiveNames] : interactionExclusivesCache)
	{
		for (const std::string& exclusiveName : exclusiveNames)
		{
			Interaction* exclusiveInteraction = findInteractionByName(exclusiveName);
			if (exclusiveInteraction)
			{
				interaction->addExclusiveInteraction(exclusiveInteraction); // Assuming this method adds a pointer
			}
			else
			{
				std::cerr << "Warning: Exclusive interaction '" << exclusiveName << "' not found for interaction '" << interaction->getInteractionName() << "'\n";
			}
		}
	}
}

Interaction* GameManager::findInteractionByName(std::string interactionName)
{
	for (auto interaction : interactions)
	{
		if (interaction->getInteractionName() == interactionName)
		{
			return interaction;
		}
	}
	return nullptr;
}
