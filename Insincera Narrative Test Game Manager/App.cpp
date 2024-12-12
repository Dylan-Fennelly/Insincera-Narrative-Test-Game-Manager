#include <iostream>
#include "Area.h"
#include "Interaction.h"
#include "GameManger.h"
#include "json.hpp"
#include "Utility.h"
int main()
{
	GameManager gameManager;
	gameManager.displayCurrentArea();
//	gameManager.moveArea("Cool Area");
	gameManager.displayConnectedAreas();
	gameManager.displayInteractions();
	gameManager.completeInteraction("Pick up rock");
	gameManager.displayCurrentArea();
	gameManager.displayInteractions();
	/*gameManager.completeInteraction("Fight the enemy");*/


}



