#include "MenuManager.h"
#include <iostream>

MenuManager::MenuManager(GameManager* gameManager) :gameManager(gameManager)
{

}

MenuManager::~MenuManager()
{
	delete gameManager;
}

void MenuManager::displayMainMenu()
{
    displayAreas();
	std::cout << "1. Move to another area" << std::endl;
	std::cout << "2. Investigate Interactions" << std::endl;
	std::cout << "3. Exit" << std::endl;
}

void MenuManager::handlePlayerInput() {
    int choice;
    std::cin >> choice;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
    }
    switch (choice) {
    case 1:
        movePlayer();
        break;
    case 2:
        completeInteraction();
        break;
    case 3:
        std::cout << "Exiting game...\n";
		gameManager->endGame(false,true);
		break;
    default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
}

void MenuManager::displayAreas()
{
    gameManager->displayAreas();
}

void MenuManager::displayInteractions()
{
    gameManager->displayInteractions();
}

void MenuManager::movePlayer()
{
    auto areas = gameManager->getCurrentArea()->getConnectedAreas();
    std::cout << "Select an area to move to:\n";

    for (size_t i = 0; i < areas.size(); ++i)
    {
        std::cout << i + 1 << ". " << areas[i]->getAreaName() <<
            " (Detection Chance: "
            << areas[i]->getEntryDetectionChance().first << "% by workers, "
            << areas[i]->getEntryDetectionChance().second << "% by soldiers.)\n";
    }

    // Display the Back option
    size_t backOption = areas.size() + 1;
    std::cout << backOption << ". Back\n";

    int choice;
    std::cin >> choice;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please try again.\n";
        return;
    }

    if (choice > 0 && choice <= areas.size()) 
    {
        gameManager->moveArea(areas[choice - 1]->getAreaName());
    }
    else if (choice == backOption)
    { // Player chose the "Back" option
        std::cout << "Returning to previous menu.\n";
        return;
    }
    else 
    {
        std::cout << "Invalid choice. Please try again.\n";
    }
}
void MenuManager::completeInteraction()
{
    auto interactions = gameManager->getCurrentArea()->getInteractions();
    std::vector<std::string> interactableKeys; // Stores only the keys of interactable interactions

    std::cout << "Select an interaction to complete:\n";
    int index = 1;

    for (const auto& interactionPair : interactions) {
        if (!interactionPair.second->getIsInteractable()) {
            continue;
        }
        std::cout << index++ << ". " << interactionPair.second->getInteractionName() << " (Detection Chance: "
            << interactionPair.second->getDetectionChance().first << "% by workers, "
            << interactionPair.second->getDetectionChance().second << "% by soldiers.)\n";
        interactableKeys.push_back(interactionPair.first); // Store only interactable keys
    }

    if (interactableKeys.empty()) {
        std::cout << "No available interactions to complete.\n";
        return;
    }

    // Display the Back option
    std::cout << index << ". Back\n";

    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please try again.\n";
        return;
    }

    // Check if input is valid relative to interactable options
    if (choice > 0 && choice <= interactableKeys.size()) {
        std::string selectedKey = interactableKeys[choice - 1]; // Map player choice to key
        gameManager->completeInteraction(selectedKey);
    }
    else if (choice == index) { // Player chose the "Back" option
        std::cout << "Returning to previous menu.\n";
        return;
    }
    else {
        std::cout << "Invalid choice. Please try again.\n";
    }
}

   