
#include "Main.h"
#include "RenderManager.h"

#include "Field.h"

Field::Field()
{
	RenderManager* renderManager = RenderManager::GetInstance();

	//テクスチャ読み込み
	m_Texture[0] = renderManager->LoadTexture("Asset\\fd.dds");
	m_Texture[1] = renderManager->LoadTexture("Asset\\fd.dds");

	m_VertexBuffer = renderManager->CreateVertexBuffer(sizeof(VERTEX_3D), 4);

	//頂点データの書き込み
	VERTEX_3D* buffer{};
	HRESULT hr = m_VertexBuffer->Resource->Map(0, nullptr, (void**)&buffer);
	assert(SUCCEEDED(hr));

	buffer[0].Position = { -10.0f, 0.0f, -10.0f };
	buffer[1].Position = { -10.0f, 0.0f,  10.0f };
	buffer[2].Position = { 10.0f, 0.0f,  -10.0f };
	buffer[3].Position = { 10.0f, 0.0f,  10.0f };

	buffer[0].Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	buffer[1].Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	buffer[2].Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	buffer[3].Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	buffer[0].Normal = { 0.0f, 1.0f, 0.0f };
	buffer[1].Normal = { 0.0f, 1.0f, 0.0f };
	buffer[2].Normal = { 0.0f, 1.0f, 0.0f };
	buffer[3].Normal = { 0.0f, 1.0f, 0.0f };

	buffer[0].TexCoord = { 0.0f, 0.0f };
	buffer[1].TexCoord = { 1.0f, 0.0f };
	buffer[2].TexCoord = { 0.0f, 1.0f };
	buffer[3].TexCoord = { 1.0f, 1.0f };

	m_VertexBuffer->Resource->Unmap(0, nullptr);

	Texture_index = 0;


}

void Field::Update()
{

}

void Field::Draw()
{
	RenderManager* renderManager = RenderManager::GetInstance();

	//imGUI
	{
		ImGui::Begin("Field");
		//ImGui::Begin("Light");

		ImGui::SliderFloat("RotationX", &m_LightRotation.x, 0.0f, XM_2PI, "%.2f");
		ImGui::SliderFloat("RotationY", &m_LightRotation.y, 0.0f, XM_PIDIV2, "%.2f");

		ImGui::ColorPicker3("Color", (float*)&m_LightColor, ImGuiColorEditFlags_PickerHueWheel);
		ImGui::SliderFloat("Intencity", &m_LightIntensity, 0.0f, 10.0f, "%.2f");


		if (ImGui::Button("GreenGrass", ImVec2(100, 100))) Texture_index = 0; ImGui::SameLine();
		if (ImGui::Button("YellowGrass", ImVec2(100, 100))) Texture_index = 1;

		ImGui::End();
	}

	{
		ENV_CONSTANT constant;
		constant.LightDirection.x = sinf(m_LightRotation.y) * cosf(m_LightRotation.x);
		constant.LightDirection.z = sinf(m_LightRotation.y) * sinf(m_LightRotation.x);
		constant.LightDirection.y = cosf(m_LightRotation.y);

		constant.LightColor.x = m_LightColor.x * m_LightIntensity;
		constant.LightColor.y = m_LightColor.y * m_LightIntensity;
		constant.LightColor.z = m_LightColor.z * m_LightIntensity;

		RenderManager::GetInstance()->SetConstant(
			RenderManager::CONSTANT_TYPE::ENV, &constant,
			sizeof(constant));

	}

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

	//頂点バッファ設定
	renderManager->SetVertexBuffer(m_VertexBuffer.get());

	//テクスチャ設定
	renderManager->SetTexture(RenderManager::TEXTURE_TYPE::BASE_COLOR, m_Texture[Texture_index].get());

	//トボロジ設定
	renderManager->GetGraphicsCommandList()->IASetPrimitiveTopology(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//パイプライン設定
	//renderManager->SetPipelineState("Unlit");

	//描画
	renderManager->GetGraphicsCommandList()->DrawInstanced(4, 1, 0, 0);



}
