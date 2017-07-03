#include <iostream>
#include <vector>
#include <SEngine\Engine.h>
#include <SDL.h>
#include <Utils\Display.h>
#include <Utils\Texture.h>
#include <Utils\TextureResource.h>
#include <Utils\SpriteAnimation.h>
#include <Utils\Time.h>
#include "Assets\GameScripts\PlatformManager.h"
#include "Assets\GameScripts\PlaneController.h"

#define LOG(x) std::cout << x << std::endl;
#define HURDLES_SIZE 4

enum GameState
{
	INIT,
	PLAY,
	EXIT
}_gameState;

struct window
{
	int WIDTH;
	int HEIGHT;
}WINDOW;

void Init();
void InitGameObjects();
void GameLoop();
void Update();
void Close();

#pragma region Variables_HERE
AREngine::Display* mainDisplay;

//Image Assets for the Environment
AREngine::Texture* background;

AREngine::Texture* groundDirt[3];

std::vector<AREngine::Texture*> downHurdles;
std::vector<AREngine::Texture*> upHurdles;
//UI Elements
AREngine::Texture* tapRightButton;
AREngine::Texture* tapLeftButton;
AREngine::SpriteAnimation* tapSpriteAnimation;
#pragma endregion


float pan_Speed = 100.5f;

unsigned short platformsPadding = 0;


PlatformManager platformManager;
PlaneController* planeController;



void Init() 
{
	AREngine::Engine::Init();
	WINDOW.WIDTH = 1024;
	WINDOW.HEIGHT = 768;
	mainDisplay = new AREngine::Display("Tappy Plane" ,  WINDOW.WIDTH , WINDOW.HEIGHT);
	_gameState = GameState::INIT;

	InitGameObjects();
}

void InitGameObjects() {
	AREngine::TextureResource::AddTextureToResource("Assets/Images/TappyPlane/background.png");

	//Ground Textures
	AREngine::TextureResource::AddTextureToResource("Assets/Images/TappyPlane/groundDirt.png");
	AREngine::TextureResource::AddTextureToResource("Assets/Images/TappyPlane/groundGrass.png");
	AREngine::TextureResource::AddTextureToResource("Assets/Images/TappyPlane/groundRock.png");

	AREngine::TextureResource::AddTextureToResource("Assets/Images/TappyPlane/rock.png");
	AREngine::TextureResource::AddTextureToResource("Assets/Images/TappyPlane/rockDown.png");

	AREngine::TextureResource::AddTextureToResource("Assets/Images/TappyPlane/planes.png");
	AREngine::TextureResource::AddTextureToResource("Assets/Images/TappyPlane/UI/tapRight.png");
	AREngine::TextureResource::AddTextureToResource("Assets/Images/TappyPlane/UI/tapLeft.png");

	AREngine::TextureResource::AddTextureToResource("Assets/Images/TappyPlane/UI/TapSpriteSheet.png");

	background = new AREngine::Texture("Assets/Images/TappyPlane/background.png", mainDisplay->m_Renderer);
	background->SetSize(AREngine::CoolMath::Vector2(WINDOW.WIDTH, WINDOW.HEIGHT));
	background->SetPosition(AREngine::CoolMath::Vector2(0, 0));

	for (Uint8 i = 0; i < 3; i++)
	{
		groundDirt[i] = new AREngine::Texture("Assets/Images/TappyPlane/groundDirt.png", mainDisplay->m_Renderer);
		if (i == 0)
		{
			groundDirt[i]->SetPosition(AREngine::CoolMath::Vector2(0, WINDOW.HEIGHT - groundDirt[i]->GetSize().y));
		}
		else {
			groundDirt[i]->SetPosition(AREngine::CoolMath::Vector2(groundDirt[i - 1]->GetPosition().x + groundDirt[i -1]->GetSize().x, WINDOW.HEIGHT - groundDirt[i]->GetSize().y));
		}
	}
	
	for (Uint16 i = 0; i < HURDLES_SIZE; i++) {
		upHurdles.push_back(new AREngine::Texture("Assets/Images/TappyPlane/rock.png", mainDisplay->m_Renderer));
		downHurdles.push_back(new AREngine::Texture("Assets/Images/TappyPlane/rockDown.png", mainDisplay->m_Renderer));
	}


	tapRightButton = new AREngine::Texture("Assets/Images/TappyPlane/UI/tapRight.png", mainDisplay->m_Renderer);
	tapRightButton->SetPivot(AREngine::Pivot::CENTER);

	tapLeftButton = new AREngine::Texture("Assets/Images/TappyPlane/UI/tapLeft.png", mainDisplay->m_Renderer);
	tapLeftButton->SetPivot(AREngine::Pivot::CENTER);

	planeController = new PlaneController("Assets/Images/TappyPlane/planes.png", mainDisplay->m_Renderer);
	//plane = new AREngine::SpriteAnimation("Assets/Images/TappyPlane/planes.png", mainDisplay->m_Renderer);
	planeController->sprite->AddFrame(0, 73.14 * 2, 85.3, 73.14);
	planeController->sprite->AddFrame(0, 73.14 * 3, 85.3, 73.14);
	planeController->sprite->AddFrame(0, 73.14 * 4, 85.3, 73.14);
	planeController->sprite->SetCurrentFrame(0);
	planeController->sprite->SetSize(AREngine::CoolMath::Vector2(85.3, 73.14));
	planeController->sprite->SetPivot(AREngine::Pivot::CENTER);
	planeController->sprite->SetAngle(5);
	planeController->sprite->SetPosition(AREngine::CoolMath::Vector2(WINDOW.WIDTH / 2 - 200, WINDOW.HEIGHT / 2 - 100));
	planeController->sprite->Play(AREngine::SpriteAnimation::Animation_Mode::LOOP);
	planeController->sprite->SetAnimationFrequency(0.001f);
	planeController->sprite->SetMass(100);
	planeController->sprite->SetGravity(9.8);
	
	tapRightButton->SetPosition(AREngine::CoolMath::Vector2(planeController->sprite->GetPosition().x - 150, planeController->sprite->GetPosition().y - 10));
	tapLeftButton->SetPosition(AREngine::CoolMath::Vector2(planeController->sprite->GetPosition().x + 150, planeController->sprite->GetPosition().y - 10));

	tapSpriteAnimation = new AREngine::SpriteAnimation("Assets/Images/TappyPlane/UI/TapSpriteSheet.png", mainDisplay->m_Renderer);
	tapSpriteAnimation->AddFrame(0, 0, 59, 59);
	tapSpriteAnimation->AddFrame(0, 62, 59, 59);
	tapSpriteAnimation->SetCurrentFrame(0);
	tapSpriteAnimation->SetSize(AREngine::CoolMath::Vector2(59, 59));
	tapSpriteAnimation->SetPivot(AREngine::Pivot::CENTER);
	tapSpriteAnimation->SetPosition(AREngine::CoolMath::Vector2(planeController->sprite->GetPosition().x + 50, planeController->sprite->GetPosition().y + 100));
	tapSpriteAnimation->Play(AREngine::SpriteAnimation::Animation_Mode::LOOP);
	tapSpriteAnimation->SetAnimationFrequency(0.25f);
	
	platformManager.SetPlatforms(groundDirt, sizeof(groundDirt) / sizeof(groundDirt[0]));
	platformManager.SetPadding(platformsPadding);
}

void GameLoop() {
	while (AREngine::Engine::engineStatus == AREngine::EngineStatus::RUNNING)
	{
		AREngine::Engine::PollEvents();
		mainDisplay->Clear();
		Update();
		mainDisplay->Update();
	}
}

void Update() 
{
	background->Update(mainDisplay->m_Renderer);
	for (Uint8 i = 0; i < 3; i++)
	{
		groundDirt[i]->Update(mainDisplay->m_Renderer);
	}
	tapSpriteAnimation->Update(mainDisplay->m_Renderer);
	tapRightButton->Update(mainDisplay->m_Renderer);
	tapLeftButton->Update(mainDisplay->m_Renderer);

	planeController->Update(mainDisplay->m_Renderer);

	platformManager.RearrangePlatforms(pan_Speed * AREngine::Time::deltaTime);


	if (Input::IsMouseButtonDown(MOUSE_BUTTON::LEFT))
	{
		tapLeftButton->SetActive(false);
		tapRightButton->SetActive(false);
		tapSpriteAnimation->SetActive(false);

	}
}

int main(int args , char* args2[]) {
	Init();
	GameLoop();
	Close();
	return 0;
}

void Close() 
{	
	AREngine::Engine::Close();
	LOG("Engine Flushed");
}