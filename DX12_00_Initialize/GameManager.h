#pragma once


#include "RenderManager.h"
#include "Camera.h"
#include "Polygon2D.h"
#include "Field.h"
#include "TestObject.h"

class GameManager
{
private:

	static GameManager* m_Instance;

	RenderManager	m_RenderManger;

	Camera m_Camera;
	Field m_Field;
	TestObject m_Obj;

	Polygon2D m_Polygon;
	



public:
	static GameManager* GetInstance() { return m_Instance; }

	GameManager();
	~GameManager();



	void Update();
	void Draw();


};

