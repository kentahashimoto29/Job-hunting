//========================================================
// 
// ウインドウの生成等 (camera.h)
// Author 橋本賢太
// 
//========================================================
#include "minimap_camera.h"
#include "manager.h"
#include "input.h"
#include "game.h"

//========================================================
// コンストラクタ
//========================================================
CMinimap_Camera::CMinimap_Camera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_viewport.Width = 180;
	m_viewport.Height = 180;
	m_viewport.X = 80;
	m_viewport.Y = 30;
	m_viewport.MaxZ = 0.1f;
	m_viewport.MinZ = 0.0f;

	// 対角線の長さを算出
	m_Distance = sqrtf(0.0f * 0.0f + 0.0f * 0.0f);

	// 対角線の角度を算出
	m_Angle = atan2f(0.0f, 0.0f);

	m_type = TYPE_NONE;
}

//========================================================
// デストラクタ
//========================================================
CMinimap_Camera::~CMinimap_Camera()
{

}

//========================================================
// カメラの初期化
//========================================================
HRESULT CMinimap_Camera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 対角線の長さを算出
	m_Distance = sqrtf(0.0f * 0.0f + 0.0f * 0.0f);

	// 対角線の角度を算出
	m_Angle = atan2f(0.0f, 0.0f);

	return S_OK;
}

//========================================================
// カメラの終了
//========================================================
void CMinimap_Camera::Uninit(void)
{

}

//========================================================
// カメラの更新
//========================================================
void CMinimap_Camera::Update(void)
{

}

//========================================================
// カメラの設定
//========================================================
void CMinimap_Camera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 
	pDevice->SetViewport(&m_viewport);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)m_viewport.Width / (float)m_viewport.Height,
		10.0f,
		5000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//========================================================
// カメラの位置
//========================================================
void CMinimap_Camera::SetPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_posV = posV;
	m_posR = posR;

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//========================================================
// カメラの位置
//========================================================
void CMinimap_Camera::SetPosGame(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_posV = D3DXVECTOR3(posV.x, posV.y + 90.0f, posV.z - 200.0f);
	m_posR = D3DXVECTOR3(posR.x, posR.y + 40.0f, posR.z);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 対角線の長さを算出
	// m_Distance = sqrtf(m_posV.y * m_posV.y + m_posV.z * m_posV.z);

	m_Distance = -m_posV.z;

	// 対角線の角度を算出
	m_Angle = atan2f(m_posV.y, -(m_posV.z - m_posR.z));

	m_rot.x = m_Angle;
}

//========================================================
// カメラの設定
//========================================================
D3DXVECTOR3 CMinimap_Camera::GetRot(void)
{
	return m_rot;
}