#include "Input.h"

namespace AREngine {
	std::unordered_map<SDL_Scancode, bool> Input::keys;
	std::unordered_map<SDL_Scancode, bool>::const_iterator Input::keysIterator;

	std::unordered_map<SDL_Scancode, bool> Input::keysState_SaverUP;
	std::unordered_map<SDL_Scancode, bool> Input::keysState_SaverDown;

	std::unordered_map<MOUSE_BUTTON, bool> Input::mouseButtons;
	std::unordered_map<MOUSE_BUTTON, bool>::const_iterator Input::mouseButtoniterator;

	std::unordered_map<MOUSE_BUTTON, bool> Input::mouseButton_SaverUp;
	std::unordered_map<MOUSE_BUTTON, bool> Input::mouseButton_SaverDown;


	bool Input::IsKeyDown(SDL_Scancode keyCode) {
		keysIterator = keys.find(keyCode);
		if (keysIterator == keys.end())
		{
			return false;
		}
		else if (keysIterator->second)
		{
			keysIterator = keysState_SaverDown.find(keyCode);
			if (keysIterator == keysState_SaverDown.end())
			{
				return false;
			}
			else {
				if (keysIterator->second)
				{
					keysState_SaverDown.at(keyCode) = false;
					return true;
				}
			}
		}
		return false;
	}

	bool Input::IsKeyDown_Repeat(SDL_Scancode keyCode) {
		keysIterator = keys.find(keyCode);
		if (keysIterator == keys.end())
		{
			return false;
		}
		else {
			return keysIterator->second;
		}
		return false;
	}

	bool Input::IsKeyUp(SDL_Scancode keyCode) {
		keysIterator = keys.find(keyCode);
		if (keysIterator == keys.end())
		{
			return false;
		}
		else if (!keysIterator->second)
		{
			keysIterator = keysState_SaverUP.find(keyCode);
			if (keysIterator == keysState_SaverUP.end())
			{
				return false;
			}
			else {
				if (keysIterator->second)
				{
					keysState_SaverUP.at(keyCode) = false;
					return true;
				}
			}
		}
		return false;
	}

	bool Input::IsMouseButtonDown(MOUSE_BUTTON buttonType) {
		mouseButtoniterator = mouseButton_SaverDown.find(buttonType);
		if (mouseButtoniterator == mouseButton_SaverDown.end())
		{
			return false;
		}
		else {
			if (mouseButtoniterator->second)
			{
				mouseButton_SaverDown.at(buttonType) = false;
				return true;
			}
		}
		return false;
	}

	bool Input::IsMouseButtonUp(MOUSE_BUTTON buttonType) {
		mouseButtoniterator = mouseButton_SaverUp.find(buttonType);
		if (mouseButtoniterator == mouseButton_SaverUp.end())
		{
			return false;
		}
		else {
			if (mouseButtoniterator->second)
			{
				mouseButton_SaverUp.at(buttonType) = false;
				return true;
			}
		}
		return false;
	}

	bool Input::IsMouseButton_Repeat(MOUSE_BUTTON buttonType) {
		mouseButtoniterator = mouseButtons.find(buttonType);
		if (mouseButtoniterator == mouseButtons.end())
		{
			return false;
		}
		else {
			return mouseButtoniterator->second;
		}
		return false;
	}

	void Input::HandleInput(SDL_Event sdlEvent) {
		if (sdlEvent.type == SDL_KEYDOWN)
		{
			keysIterator = keys.find(sdlEvent.key.keysym.scancode);
			if (keysIterator == keys.end())
			{
				keys.insert(std::make_pair(sdlEvent.key.keysym.scancode, true));
				keysState_SaverDown.insert(std::make_pair(sdlEvent.key.keysym.scancode, true)); //Never Put this in the else condition ever 
				keysState_SaverUP.insert(std::make_pair(sdlEvent.key.keysym.scancode, true)); //Never Put this in the else condition ever 
			}
			else {
				keys.at(sdlEvent.key.keysym.scancode) = true;
			}
		}
		if (sdlEvent.type == SDL_KEYUP)
		{
			keys.at(sdlEvent.key.keysym.scancode) = false;
			keysState_SaverDown.at(sdlEvent.key.keysym.scancode) = true;
			keysState_SaverUP.at(sdlEvent.key.keysym.scancode) = true;
		}
		if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			if (sdlEvent.button.button == SDL_BUTTON_LEFT)
			{
				//	std::cout << "You clicked on Left Button " << std::endl;
				mouseButtoniterator = mouseButtons.find(MOUSE_BUTTON::LEFT);
				if (mouseButtoniterator == mouseButtons.end())
				{
					mouseButtons.insert(std::make_pair(MOUSE_BUTTON::LEFT, true));
					mouseButton_SaverDown.insert(std::make_pair(MOUSE_BUTTON::LEFT, true));
					mouseButton_SaverUp.insert(std::make_pair(MOUSE_BUTTON::LEFT, false));
				}
				else {
					mouseButtons.at(MOUSE_BUTTON::LEFT) = true;
					mouseButton_SaverDown.at(MOUSE_BUTTON::LEFT) = true;
				}
			}
			else if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
			{
				//std::cout << "You clicke on Right Button " << std::endl;
				mouseButtoniterator = mouseButtons.find(MOUSE_BUTTON::RIGHT);
				if (mouseButtoniterator == mouseButtons.end())
				{
					mouseButtons.insert(std::make_pair(MOUSE_BUTTON::RIGHT, true));
					mouseButton_SaverDown.insert(std::make_pair(MOUSE_BUTTON::RIGHT, true));
					mouseButton_SaverUp.insert(std::make_pair(MOUSE_BUTTON::RIGHT, false));
				}
				else {
					mouseButtons.at(MOUSE_BUTTON::RIGHT) = true;
					mouseButton_SaverDown.at(MOUSE_BUTTON::RIGHT) = true;
				}
			}
			else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE)
			{
				//std::cout << "You clicked on Middle Button " << std::endl;
				mouseButtoniterator = mouseButtons.find(MOUSE_BUTTON::MIDDLE);
				if (mouseButtoniterator == mouseButtons.end())
				{
					mouseButtons.insert(std::make_pair(MOUSE_BUTTON::MIDDLE, true));
					mouseButton_SaverDown.insert(std::make_pair(MOUSE_BUTTON::MIDDLE, true));
					mouseButton_SaverUp.insert(std::make_pair(MOUSE_BUTTON::MIDDLE, false));
				}
				else {
					mouseButtons.at(MOUSE_BUTTON::MIDDLE) = true;
					mouseButton_SaverDown.at(MOUSE_BUTTON::MIDDLE) = true;
				}
			}
		}
		if (sdlEvent.type == SDL_MOUSEBUTTONUP)
		{
			if (sdlEvent.button.button == SDL_BUTTON_LEFT)
			{
				//	std::cout << "You clicked on Left Button " << std::endl;
				mouseButtons.at(MOUSE_BUTTON::LEFT) = false;
				mouseButton_SaverUp.at(MOUSE_BUTTON::LEFT) = true;
			}
			else if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
			{
				//std::cout << "You clicke on Right Button " << std::endl;
				mouseButtons.at(MOUSE_BUTTON::RIGHT) = false;
				mouseButton_SaverUp.at(MOUSE_BUTTON::RIGHT) = true;
			}
			else if (sdlEvent.button.button == SDL_BUTTON_MIDDLE)
			{
				//	std::cout << "You clicked on Middle Button " << std::endl;
				mouseButtons.at(MOUSE_BUTTON::MIDDLE) = false;
				mouseButton_SaverUp.at(MOUSE_BUTTON::MIDDLE) = true;
			}
		}
	}
}
