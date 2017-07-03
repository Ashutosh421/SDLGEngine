#include "PlaneController.h"

PlaneController::PlaneController(std::string , SDL_Renderer* mainRenderer)
{
	sprite = new AREngine::SpriteAnimation("Assets/Images/TappyPlane/planes.png", mainRenderer);
}

PlaneController::~PlaneController()
{
	delete sprite;
}

void PlaneController::Update(SDL_Renderer* mainRenderer) {
	sprite->Update(mainRenderer);

	if (Input::IsMouseButton_Repeat(MOUSE_BUTTON::LEFT))
	{
		
	}

}

