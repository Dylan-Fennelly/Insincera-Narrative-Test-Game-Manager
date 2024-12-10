#include <iostream>
#include "Area.h"
#include "Interaction.h"
#include "GameManger.h"
int main()
{
	Area area("starterArea", 10, 10, 10, 10, "Where the game starts");
	Interaction interaction("Leave the facility", 100, 100, 30, "Leave the facility forever");
	area.addInteraction(&interaction);
	area.displayInteractions();
	GameManager gameManager(&area);
	gameManager.addInteraction(&interaction);
	gameManager.displayAreas();
	gameManager.displayInteractions();
	gameManager.completeInteraction("Leave the facility");
	gameManager.displayCurrentArea();
	gameManager.displayConnectedAreas();
	gameManager.displayInteractions();
    std::cout << "Hello World!\n";
}


