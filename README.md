# NewEditorMode
How to create a new editor mode and show custom variables and execute functions from a editor mode plugin

This is a kind of extension for the video created by Michael Noland from Epic Games.

https://www.youtube.com/watch?v=zg_VstBxDi8

This did not translate directly to an editor mode so it took me some research into the 
Landscape Editor Mode to get the mode working with custom properties and functions.

I just hope this code can help other programmers understand extending the editor better and get up to speed with it faster.

Don't forget to add the Plugin to your .uproject file:

	"Plugins": [
		{
			"Name": "NewEditorMode",
			"Enabled": true
		},
	]
  
When opening unreal engine, you can find the new editor mode here:

![image](https://user-images.githubusercontent.com/7476375/135280857-c3bcdd22-f8b4-40b6-9e68-1ed0fbf8fb9e.png)
