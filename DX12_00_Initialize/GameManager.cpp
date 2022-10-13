

#include "Main.h"
#include "GameManager.h"




GameManager* GameManager::m_Instance = nullptr;





GameManager::GameManager()
{
	m_Instance = this;

	
}




GameManager::~GameManager()
{
	
	m_RenderManger.WaitGPU();
}





void GameManager::Update()
{
	m_Camera.Update();
	m_Field.Update();
	m_Obj.Update();
	m_Polygon.Update();
}




void GameManager::Draw()
{

	m_RenderManger.DrawBegin();

	m_Camera.Draw();
	m_Field.Draw();
	m_Obj.Draw();
	//m_Polygon.Draw();
	
	

	m_RenderManger.DrawEnd();

}


