# Notes for writting the Json
* Don't modify the Combat area
* Don't modify the leave facility interaction - make sure it is present in any areas where the player is able to leave the facility 
* Make sure that areas are linked to all of their connected areas - both foward and back 
* Ignore the exitDectionchance as it is unused 
* Any interaction that cancels out another needs to be added to the "exclusiveInteractions" - this must be the exact same string to make all of this work
