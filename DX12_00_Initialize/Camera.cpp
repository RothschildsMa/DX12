

#include "Main.h"
#include "RenderManager.h"
#include "Camera.h"

Camera::Camera()
{
	m_Position = { 0.0f,1.0f,-3.5f };
	m_Target = { 0.0f,0.0f,0.0f };

}


void Camera::Update()
{

}

void Camera::Draw()
{
	RenderManager* renderManager = RenderManager::GetInstance();

	//Imgui
	{
		ImGui::Begin("Camera");
		ImGui::DragFloat3("Position", (float*)&m_Position, 0.1f);

		ImGui::End();

	}

	//マトリクス設定
	{

		XMMATRIX view;
		XMFLOAT3 up{ 0.0f,1.0f,0.0f };
		view = XMMatrixLookAtLH(XMLoadFloat3(&m_Position),
			XMLoadFloat3(&m_Target),
			XMLoadFloat3(&up));

		XMMATRIX projection;
		float aspect = (float)renderManager->GetBackBufferWidth() / renderManager->GetBackBufferHeight();
		projection = XMMatrixPerspectiveFovLH(1.0f, aspect, 0.1f, 100.0f);

		CAMERA_CONSTANT constant{};
		XMStoreFloat4x4(&constant.View, XMMatrixTranspose(view));
		XMStoreFloat4x4(&constant.Projection, XMMatrixTranspose(projection));
		constant.Position = { m_Position.x,m_Position.y,m_Position.z,0.0f };

		renderManager->SetConstant(RenderManager::CONSTANT_TYPE::CAMERA, &constant, sizeof(constant));

	}

}
