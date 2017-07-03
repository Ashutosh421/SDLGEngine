#include <Utils\Texture.h>
#include <Utils\SpriteAnimation.h>
#include <Utils\Input.h>

using namespace AREngine;

class PlaneController
{
private:
	

public:
	AREngine::SpriteAnimation* sprite;

	PlaneController(std::string , SDL_Renderer* mainRenderer);
	~PlaneController();

	void Update(SDL_Renderer* mainRenderer );
};
