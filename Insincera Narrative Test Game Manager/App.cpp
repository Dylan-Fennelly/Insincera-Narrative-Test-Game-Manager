#include <iostream>
#include "Area.h"
#include "Interaction.h"
#include "GameManger.h"
#include "json.hpp"
int main()
{
	//TODO: Get rid of this random starter ,it should be handled by the constructor 
	Area area("starterArea", 10, 10, 0, 0, "Where the game starts");
	Interaction escape("Leave the facility", 0, 0, 0, "Leave the facility forever");
	area.addInteraction(&escape);
	area.displayInteractions();
	Interaction lookAround("Look around", 100, 100, 0, "Look around the area");
	area.addInteraction(&lookAround);
	
	GameManager gameManager(&area);
	gameManager.addInteraction(&escape);
	gameManager.addInteraction(&lookAround);
	//gameManager.displayAreas();
	//gameManager.displayInteractions();
	//gameManager.completeInteraction("Leave the facility");
	//gameManager.displayCurrentArea();
	//gameManager.displayConnectedAreas();
	//gameManager.displayInteractions();
	////gameManager.completeInteraction("Fight the enemy");
	//gameManager.displayInteractions();
	//gameManager.loadfromJSON("D:\\C++\\Insincera Narrative Test Game Manager\\game.json");
	
	gameManager.displayCurrentArea();
	gameManager.moveArea("Cool Area");
	gameManager.displayConnectedAreas();
	gameManager.displayInteractions();
	gameManager.completeInteraction("Pick up rock");
	gameManager.displayInteractions();


}



