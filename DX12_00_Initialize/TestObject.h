#pragma once


#include "Model.h"


class TestObject
{
private:

	XMFLOAT3 m_Position{ 0.0f,0.0f,0.0f };
	XMFLOAT3 m_Rotation{ 0.0f, 0.0f, 0.0f };
	XMFLOAT3 m_Scale{ 10.0f,10.0f,10.0f };

	Model m_Model;

public:

	TestObject();

	void Update();
	void Draw();

};


