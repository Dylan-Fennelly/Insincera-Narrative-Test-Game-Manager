#pragma once
#include "Area.h"
#include "Interaction.h"
#include <vector>
class GameManger
{
public :
	std::vector<Area*> areas;
	std::vector<Interaction*> interactions;
	Area* currentArea;
	int culmulativeDanger = 0;

public:
	GameManger(Area* starterArea);
	~GameManger();

	void addArea(Area* area);
	void addInteraction(Interaction* interaction);
	void displayAreas();
	void displayInteractions();
	void completeInteraction(std::string interactionName);
	void moveArea(std::string areaName);
	void displayCurrentArea();
	void displayConnectedAreas();
	void addCulmulativeDanger(int danger);
	void endGame(bool killed);
	void moveToCombatArea(Area* areaAfterCombat);


	

};

