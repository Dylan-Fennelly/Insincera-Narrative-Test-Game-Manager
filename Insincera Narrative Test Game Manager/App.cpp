#include <iostream>
#include "Area.h"
#include "Interaction.h"
#include "GameManger.h"
#include "json.hpp"
#include "Utility.h"
#include "MenuManager.h"
int main()
{
	GameManager* gameManager = new GameManager();
	MenuManager menuManager(gameManager);

	while(gameManager->getIsGameRunning())
	{
		menuManager.displayMainMenu();
		menuManager.handlePlayerInput();
	}


}



