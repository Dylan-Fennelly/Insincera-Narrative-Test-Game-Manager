#include "MenuManager.h"

MenuManager::MenuManager(GameManager* gameManager) :gameManager(gameManager)
{

}

MenuManager::~MenuManager()
{
	delete gameManager;
}
