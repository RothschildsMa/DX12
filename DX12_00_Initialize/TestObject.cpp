

#include "Main.h"
#include "RenderManager.h"
#include "TestObject.h"

TestObject::TestObject()
{
	m_Model.Load("Asset\\Drill_01_4k.obj");


}

void TestObject::Update()
{

	m_Rotation.y += 0.01f;
}

void TestObject::Draw()
{
	RenderManager* renderManager = RenderManager::GetInstance();


	{
		//マトリクス設定
		XMMATRIX world = XMMatrixIdentity();
		world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		OBJECT_CONSTANT constant{};
		XMStoreFloat4x4(&constant.World, XMMatrixTranspose(world));

		renderManager->SetConstant(RenderManager::CONSTANT_TYPE::OBJECT, &constant, sizeof(constant));

	}

	//パイプライン設定
	//renderManager->SetPipelineState("Unlit");

	m_Model.Draw();
}
