#include <iostream>
#include "Area.h"
#include "Interaction.h"
int main()
{
	Area area("Area1", 10, 20, 30, 40, "Area1 Description");
	Interaction interaction("Interaction1", 10, 20, 30, "Interaction1 Description");
	area.addInteraction(&interaction);
	area.displayInteractions();
    std::cout << "Hello World!\n";
}


