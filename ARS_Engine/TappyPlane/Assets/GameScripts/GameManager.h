#pragma once
class GameManager
{

	static GameManager *m_instance;

public:

	static GameManager *GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new GameManager;
		}
		return m_instance;
	}

};

