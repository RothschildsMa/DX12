#pragma once

class Camera
{
private:
	XMFLOAT3 m_Position{ 0.0f,0.0f,0.0f };
	XMFLOAT3 m_Target{ 0.0f,0.0f,0.0f };
	
public:

	Camera();

	void Update();
	void Draw();


};


