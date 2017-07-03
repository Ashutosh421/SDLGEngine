#include "PlatformManager.h"

PlatformManager::PlatformManager():m_platformsSize(0),m_boundaryWidth(0),m_boundaryHeight(0){}

void PlatformManager::SetPlatforms(AREngine::Texture* *platforms, const int& size){
	this->platforms = platforms;
	this->m_platformsSize = size;

	std::cout << "Platforms Received " << m_platformsSize << std::endl;
}

void PlatformManager::SetBoundaries(int width , int height) {
	this->m_boundaryWidth = width;
	this->m_boundaryHeight = height;
}

void PlatformManager::RearrangePlatforms(float panSpeed) {
	for (int i = 0; i < m_platformsSize; i++) {
		platforms[i]->SetPosition(AREngine::CoolMath::Vector2(platforms[i]->GetPosition().x - panSpeed , platforms[i]->GetPosition().y));

		if (platforms[i]->GetPosition().x + platforms[i]->GetSize().x <= 0)
		{
			int newIndex = i - 1;
			if (i == 0)
			{
				newIndex = m_platformsSize - 1;
			}
			platforms[i]->SetPosition(AREngine::CoolMath::Vector2(platforms[newIndex]->GetPosition().x + platforms[newIndex]->GetSize().x + m_padding , platforms[i]->GetPosition().y));
			std::cout << "Shifted Platform Number " << i << std::endl;
		}
	}
}

PlatformManager::~PlatformManager(){

}