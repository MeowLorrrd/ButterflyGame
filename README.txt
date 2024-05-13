# ButterflyGame


Your goal: collect butterflies! There isn't a whole lot to do currently, but try something like collecting a full stack (30!) of Golden Butterflies!
Collectable butterflies:
	Monarch, an orange-yellow butterfly that commenly shows up
	Nebula, a bright purple butterfly
	Glasswing, a see-through butterfly
	Golden, the rarest of them all!
	
Control your frog-guy:
	'A' to move left
	'D' to move right
	'Space' to jump
	'Left mouse button' to use an item
		If you have a butterfly selected, it will summon it instead
	'1-9' to navigate your hotbar
	'E' to view your full inventory
	'Esc' to exit the game
	While debugging:
		Pressing a key on the numpad or F1-F4 will set an item in the inventory
		It will override any existing item!



Items:
	Basic Bug net, swing it around to catch butterflies
	Net bomb, it currently does nothing (and is unobtainable), but throwing it should catch butterflies in an area
	Butterflies, you can collect them or release them into the world

Building the game:
	Open the *.sln file and build through Visual Studio.
	Libaries should automatically be copied over into the build directory
	If not:
		Copy files for the debugging build. They have -d- in their filename
		Paste them in x64\Debug
		Copy files for the release build. They have no -d- in their filename
		Paste them in x64\Release
	
	Assets should automatically be copied into the build directory on build
	If not, copy and paste Assets\ to the build dir