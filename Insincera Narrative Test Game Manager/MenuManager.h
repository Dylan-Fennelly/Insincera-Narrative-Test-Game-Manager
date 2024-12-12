#pragma once
#include "GameManger.h"
class MenuManager
{
	//this class will house the menu logic and allow the player to interact eith the game
private:
	GameManager* gameManager;
public:
	MenuManager(GameManager* gameManager);
	~MenuManager();
	void displayMainMenu();
	void handlePlayerInput();

private:
	void displayAreas();
	void displayInteractions();
	void movePlayer();
	void completeInteraction();


};

