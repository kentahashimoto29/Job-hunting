//========================================================
//
//ウインドウの生成等 (camera.h)
//Author 橋本賢太
//
//========================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "game.h"
#include "title.h"

//========================================================
//コンストラクタ
//========================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//対角線の長さを算出
	m_Distance = sqrtf(0.0f * 0.0f + 0.0f * 0.0f);

	//対角線の角度を算出
	m_Angle = atan2f(0.0f, 0.0f);

	m_type = TYPE_NONE;

	x = 0.0f;
	y = 0.0f;
}

//========================================================
//デストラクタ
//========================================================
CCamera::~CCamera()
{

}

//========================================================
//カメラの初期化
//========================================================
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//対角線の長さを算出
	m_Distance = sqrtf(0.0f * 0.0f + 0.0f * 0.0f);

	//対角線の角度を算出
	m_Angle = atan2f(0.0f, 0.0f);

	return S_OK;
}

//========================================================
//カメラの終了
//========================================================
void CCamera::Uninit(void)
{

}

//========================================================
//カメラの更新
//========================================================
void CCamera::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//マウスの取得
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	//プレイヤー3Dの取得
	CPlayer3D *pPlayer3D = CGame::GetPlayer3D();

	switch (CManager::GetInstance()->GetScene()->GetMode())
	{
	case CScene::MODE_GAME:

		/*m_posR.x += pPlayer3D->GetMove().x;
		m_posV.x += pPlayer3D->GetMove().x;*/
		if (pInputMouse->GetPress(pInputMouse->TYPE_LEFT) == true)
		{
			x += pInputMouse->GetMouseMove().x / 300;
			y += pInputMouse->GetMouseMove().y / 300;

			if (x > D3DX_PI)
			{
				x = -D3DX_PI;
			}

			else if (x < -D3DX_PI)
			{
				x = D3DX_PI;
			}

			if (y > D3DX_PI / 2)
			{
				y = D3DX_PI / 2;
			}

			else if (y < -D3DX_PI / 2)
			{
				y = -D3DX_PI / 2;
			}

			float xy = 0.0f;

			m_rot.y = x;

			float f = sinf(m_rot.y + D3DX_PI) * m_Distance;
			float ff = cosf(m_rot.y + D3DX_PI + m_rot.x) * m_Distance;

			m_posV.x = m_posR.x + sinf(m_rot.y + D3DX_PI) * m_Distance;
			m_posV.z = m_posR.z + cosf(m_rot.y + D3DX_PI) * m_Distance;
		}

		m_posR.x += pPlayer3D->GetMove().x;
		m_posR.z += pPlayer3D->GetMove().z;
		m_posV.x += pPlayer3D->GetMove().x;
		m_posV.z += pPlayer3D->GetMove().z;

		break;
	}

	

	//カメラの補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}

	else if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}
}

//========================================================
//カメラの設定
//========================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//========================================================
//カメラの位置
//========================================================
void CCamera::SetPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_posV = posV;
	m_posR = posR;
}

//========================================================
//カメラの位置
//========================================================
void CCamera::SetPosGame(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_posV = D3DXVECTOR3(posV.x, posV.y + 90.0f, posV.z - 200.0f);
	m_posR = D3DXVECTOR3(posR.x, posR.y + 40.0f, posR.z);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//対角線の長さを算出
	//m_Distance = sqrtf(m_posV.y * m_posV.y + m_posV.z * m_posV.z);

	m_Distance = -m_posV.z;

	//対角線の角度を算出
	m_Angle = atan2f(m_posV.y, -(m_posV.z - m_posR.z));

	m_rot.x = m_Angle;

	x = 0.0f;
	y = 0.0f;

	y = m_rot.x;
}

//========================================================
//カメラの位置
//========================================================
void CCamera::SetPosTitle()
{


	m_posV = D3DXVECTOR3(2000.0f, 500.0f, 2000.0f);
	m_posR = D3DXVECTOR3((1600.0f / 2) - 50.0f, 0.0f, (1600.0f / 2) - 50.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//対角線の長さを算出
	//m_Distance = sqrtf(m_posV.y * m_posV.y + m_posV.z * m_posV.z);

	m_Distance = -m_posV.z;

	//対角線の角度を算出
	m_Angle = atan2f(m_posV.y, -(m_posV.z - m_posR.z));

	m_rot.x = m_Angle;

	y = m_rot.x;
}

//========================================================
//カメラの設定
//========================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}