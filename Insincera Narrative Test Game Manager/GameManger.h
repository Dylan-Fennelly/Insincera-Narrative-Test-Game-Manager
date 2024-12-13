#pragma once
#include "Area.h"
#include "Interaction.h"
#include <vector>
class GameManager
{
private :
	std::vector<Area*> areas;
	std::vector<Interaction*> interactions;
	Area* currentArea;
	int culmulativeDanger = 0;
	bool isGameRunning = true;


public:
	GameManager();
	GameManager(std::string fileName);
	~GameManager();
	void loadfromJSON(const std::string fileName);

	void addArea(Area* area);
	void addInteraction(Interaction* interaction);

	void displayAreas();
	void displayInteractions();
	void displayCurrentArea();
	void displayConnectedAreas();

	void completeInteraction(std::string interactionName);
	void moveArea(std::string areaName, bool beatTheEnemy = false);
	void moveToCombatArea(std::string areaAfterCombat);
	void addCulmulativeDanger(int danger);
	
	
	Area* findAreaByString(std::string areaName);
	Interaction* findInteractionByName(std::string interactionName);

	bool getIsGameRunning();

	void resetCombatArea();
	void endGame(bool killed, bool quitGame = false);
	

	std::vector<Area*> getAreas() const;
	Area* getCurrentArea() const;
	int getCulmulativeDanger() const;
	
};

