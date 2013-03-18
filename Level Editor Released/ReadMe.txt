Read Me for RobotSplit editor

	*File Handling information*
		*Saving/Loading folders*
All Loadable levels should be in the Load folder.
By default the Saved levels are saved in the Saved folder
		*Save/Load in different folders*
If you want to load or save a different folder, you have to do it relatively 
to the current folder. Entering ../ lets you go up in the file hierarcy so 
entering "../Default", would load the "Default.xml" file from the folder 
"Level Editor Released".

	*Unit handling*
		*Left button*
Clicking on a Unit with the left mouse button will select it and allow you to move
it around. Clicking the left mouse button again will put it in the position it is
and let you modify it with the Toolbar. If that position is within another unit while
both units are solid, the unit will be returned to its original position. If the Unit
doesn't have any earlier position, it will be deleted.
		*Right button*
Clicking on a Unit with the right mouse button will delete the unit currently under
the mouse pointer. Clicking the right mouse button while having a Unit selected will
delete it.

	*Toolbar/Levelbar usage*
		*Item Selction*
Clicking an Item with a mouse button in the Toolbar will select it. Selecting a button
will cause a  certain event to happen and then deselect it. Selecting a textbox will
allow you to enter text into it. Selecting a dropmenu will allow you to select a option
from it. Selecting a UnitMenu will allow you to create a new Unit.
		*Pressing the Return key*
Pressing the ReturnKey will update the options in the toolbar to the Unit's Values.
		*Deselecting the Toolbar*
When pressing anywhere that is not the Toolbar (the minimap is part of the Toolbar)
all the values NOT updated will be reverted to the Unit's values.

	*Manipulating the LevelView*
While not having any of the bar selected:
	Pressing and releaseing the add button (+) will zoom in on the level.
	Pressing and releaseing the subtraction button (-) will zoom out on the level.
	Pressing and releaseing the directionkeys will move the view in that direction.
	
	*Loading a new background*
Entering the Name of the background will load all it's segment into a line, making up
the level's size.