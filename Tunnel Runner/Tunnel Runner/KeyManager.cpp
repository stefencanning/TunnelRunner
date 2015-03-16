#include "KeyManager.h"

KeyManager* KeyManager::me;

KeyManager* KeyManager::getManager()
{
	if(!me)
	{
		me=new KeyManager();
	}
	return me;
}

KeyManager::KeyManager(void)
{
	_CURRENT_KEY_STATES = SDL_GetKeyboardState(&keyLength);
	lastKeyStates = new Uint8[keyLength];
	memcpy(lastKeyStates, _CURRENT_KEY_STATES, keyLength);
	LeftClick=false;
	RightClick=false;
	lastLeftClick=false;
	lastRightClick=false;
	currentScroll=0;
	lastScroll=0;
	QUIT=false;
}

KeyManager::~KeyManager(void)
{
	delete lastKeyStates;
}

void KeyManager::Update(SDL_Event eHandler)
{
	delete lastKeyStates;
	lastKeyStates = new Uint8[keyLength];
	memcpy(lastKeyStates, _CURRENT_KEY_STATES, keyLength);
	_CURRENT_KEY_STATES = SDL_GetKeyboardState(&keyLength);
	SDL_GetMouseState( &MouseX, &MouseY );
	lastScroll = currentScroll;
	lastLeftClick = LeftClick;
	lastRightClick = RightClick;
	while(SDL_PollEvent(&eHandler) != 0)
	{
		if(eHandler.type == SDL_MOUSEBUTTONDOWN)
		{	
			if( eHandler.button.button == SDL_BUTTON_LEFT )
			{
				LeftClick = true;
			}
			if( eHandler.button.button == SDL_BUTTON_RIGHT )
			{
				RightClick = true;
			}
		}
		if( eHandler.type == SDL_MOUSEBUTTONUP )
		{
			if( eHandler.button.button == SDL_BUTTON_LEFT )
			{
				LeftClick = false;
			}
			if( eHandler.button.button == SDL_BUTTON_RIGHT )
			{
				RightClick = false;
			}
		}
		if(eHandler.type == SDL_MOUSEWHEEL)
		{
			currentScroll+=eHandler.button.x;
		}
		if(eHandler.type == SDL_QUIT)
		{
			QUIT=true;
		}
	}
}

bool KeyManager::keyPressed(SDL_Scancode code)
{
	bool pressed=false;
	if(lastKeyStates)
	{
		if(lastKeyStates[code])
		{
			pressed=true;
		}
	}
	if(!pressed&&_CURRENT_KEY_STATES[code])
	{
		return true;
	}
	return false;
}

bool KeyManager::keyDown(SDL_Scancode code)
{
	if(_CURRENT_KEY_STATES[code])
	{
		return true;
	}
	return false;
}

bool KeyManager::keyReleased(SDL_Scancode code)
{
	bool pressed=false;
	if(lastKeyStates)
	{
		if(lastKeyStates[code]==1)
		{
			pressed=true;
		}
	}
	if(pressed&&!_CURRENT_KEY_STATES[code])
	{
		return true;
	}
	return false;
}

bool KeyManager::keyUp(SDL_Scancode code)
{
	if(_CURRENT_KEY_STATES[code])
	{
		return true;
	}
	return false;
}

float KeyManager::scrollChange()
{
	return currentScroll-lastScroll;
}

float KeyManager::scrollValue()
{
	return currentScroll;
}

Vector2f KeyManager::mousePosition()
{
	return Vector2f(MouseX,MouseY);
}

bool KeyManager::mouseDown(mouseButtons mouseButton)
{
	if(mouseButton == mouseButtons::left)
	{
		return LeftClick;
	}
	else
	{
		return RightClick;
	}
}

bool KeyManager::mouseUp(mouseButtons mouseButton)
{
	if(mouseButton == mouseButtons::left)
	{
		return !LeftClick;
	}
	else
	{
		return !RightClick;
	}
}

bool KeyManager::mousePressed(mouseButtons mouseButton)
{
	if(mouseButton == mouseButtons::left)
	{
		if(!lastLeftClick)
		{
			return LeftClick;
		}
	}
	else if(mouseButton == mouseButtons::right)
	{
		if(!lastRightClick)
		{
			return RightClick;
		}
	}
	return false;
}

bool KeyManager::mouseReleased(mouseButtons mouseButton)
{
	if(mouseButton == mouseButtons::left)
	{
		if(lastLeftClick)
		{
			return !LeftClick;
		}
	}
	else
	{
		if(lastRightClick)
		{
			return !RightClick;
		}
	}
}

