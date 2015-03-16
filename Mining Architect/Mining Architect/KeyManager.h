#pragma once
#ifndef KEYMANAGER_H
#define KEYMANAGER_H
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "SDL.h"
#include "Vector2f.h"
using namespace std;
class KeyManager
{
private:
	///public KeyManager object
	static KeyManager* me;
	///constructor method: creates a new KeyManager object using the information passed in
	KeyManager(void);
	/// used to store the last state the keys were in
	Uint8* lastKeyStates;
	/// used to store the current key state
	const Uint8* _CURRENT_KEY_STATES;
	///used to detect if the player wants to quit the game
	bool QUIT;
	/// stores the length of the key
	int keyLength;
	/// stores the x and y coordinates of the mouse 
	int MouseX,MouseY;
	/// booleans used to detect current and previous mouse clciks 
	bool LeftClick,RightClick,lastLeftClick,lastRightClick;
	/// used to detect the scroll of the mouse wheel 
	float currentScroll;
	/// used to detect the previous mouse scroll
	float lastScroll;
public:
	///enumerations that represent the mouse buttons
	enum mouseButtons
	{
		left,/// left button
		right/// right button
	};
	///detects if a certain key is down
	bool keyDown(SDL_Scancode code);
	///detects if a certain key has been pressed
	bool keyPressed(SDL_Scancode code);
	///detects if a certain key has been released
	bool keyReleased(SDL_Scancode code);
	///detects if a certain key is up
	bool keyUp(SDL_Scancode code);
	///detects if a mouse button is down
	bool mouseDown(mouseButtons mouseButton);
	///detects if a mouse button is up
	bool mouseUp(mouseButtons mouseButton);
	///detects if a mouse button is pressed
	bool mousePressed(mouseButtons mouseButton);
	///detects if a mouse button is released
	bool mouseReleased(mouseButtons mouseButton);
	/// method that detects motion from the mouse wheel 
	float scrollChange();
	///method that stores the amount of which the mouse wheel has changed
	float scrollValue();
	///method that terminates the application
	bool quit(){return QUIT;};
	/// vector that stores the mouse x and y coordinates
	Vector2f mousePosition();
	/// the public keyManager object
	static KeyManager* getManager();
	/// the method used to update the KeyManager
	void Update(SDL_Event eHandler);
	///Destructor method: deletes this object at termination/clean up 
	~KeyManager(void);
};
#endif

