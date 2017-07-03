#include <Maths\Vector.h>
#include <Utils\Texture.h>

class PlatformManager
{
public:
	AREngine::Texture* *platforms;
	int m_platformsSize;
	unsigned short m_padding;
	int m_boundaryWidth;
	int m_boundaryHeight;

	PlatformManager();
	
	~PlatformManager();

public:
	void SetPlatforms(AREngine::Texture* *platforms, const int& size);
	void SetBoundaries(int width,int height);
	void RearrangePlatforms(float);

	inline void SetPadding(unsigned short padding) {
		this->m_padding = padding;
	}
};