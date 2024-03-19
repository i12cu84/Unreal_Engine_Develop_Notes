# Add-Tag-plugins-for-Unreal-Engine

[中文说明](https://github.com/i12cu84/Add-Tag-plugins-for-Unreal-Engine-Cpp/blob/main/README(chin).md)

Unreal Engine version 5.2 

Place the file in the project directory Plugins

This plugin will generate 14 buttons in the "Build project" column

The button functions are, in order

0: 

	Adds a Tags to the selected target:
	Action_Pullout
	Action_Insert

1:

	Adds a Tags to the selected target:
	Action_Screwout
	Action_Screwin

2:

	Adds a Tags to the selected target:
	Action_Fade
	Action_Display

3:

	Record your selected model UAID and apply it to the next two buttons
	(if you select "A" and "B" model and button down)

4:

	Add the Tag of the UAID of the previous button-pressed model to the selected model:
	Constraint+[A model UAID;B model UAID]

5:

	Attach the '3' button to the selected model by pressing the Tag of the model's UAID:
	Select Mode Had Tag:
	Constraint+[C model UAID]
	This Tag will be:
	Constraint+[A model UAID;B model UAID;C model UAID]

6:

	After pressing, a window will pop up. 
	Enter the contents of '1','2','3','4' respectively and press Enter. 
	The selected model will be labeled:
	UnloadStep^[1]+[2]+[3]+[4]

7:

	Same as above, but the format will become
	LoadedStep^[1]+[2]+[3]+[4]

8:

	Same as above, but the format will become
	ChangeStep^[1]+[2]+[3]+[4]

9:

	Adds a Tags to the selected target:
	Name_xxx
	Tip_xxx
	Durab_xxx

10:

	After pressing, an input box will pop up. 
	After entering the content, press Enter, 
	and the selected model will add the tag entered in the input box

11:

	Export the tag of the selected model to the root directory of the ue project
	The format of the export is: 
	name in the outline - UAID of the model - tag of the model
	The exported files will be partially named by time, so you don't have to worry about overwriting files

12:

	Export the labels of all models in the scenario to the ue project root
	The format of export is the same as above
	The exported files will be partially named by time, so you don't have to worry about overwriting files

13:

	Import tags for all models in the ue project from the root directory of the ue project "input.csv"
	Simply replace the tag of the model that exists in the csv; if it doesn't exist, nothing will change
