//========================================================
// 
// ウインドウの生成等 (light.cpp)
// Author 橋本賢太
// 
//========================================================
#include "light.h"
#include "manager.h"

#define LIGHT_MAX	(4)

//========================================================
// コンストラクタ
//========================================================
CLight::CLight()
{

}

//========================================================
// デストラクタ
//========================================================
CLight::~CLight()
{

}

//========================================================
// ライトの初期化
//========================================================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;              // 設定用方向ベクトル

	// ライトの情報をクリアする
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	// ライトの種類を設定
	for (int nCnt = 0; nCnt < LIGHT_MAX; nCnt++)
	{
		m_Light[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		m_Light[nCnt].Diffuse = D3DXCOLOR(0.36f, 0.32f, 0.37f, 1.0f);
	}

	// ライトの方向を設定
	vecDir = D3DXVECTOR3(0.0f, -0.2f, 0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             // ベクトルを正規化する
	m_Light[0].Direction = vecDir;

	// ライトの方向を設定
	vecDir = D3DXVECTOR3(-0.1f, -0.2f, -0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             // ベクトルを正規化するhj
	m_Light[1].Direction = vecDir;

	// ライトの方向を設定
	vecDir = D3DXVECTOR3(0.1f, -0.2f, -0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             // ベクトルを正規化する
	m_Light[2].Direction = vecDir;

	// ライトの方向を設定
	vecDir = D3DXVECTOR3(0.1f, 0.2f, 0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             // ベクトルを正規化する
	m_Light[3].Direction = vecDir;

	for (int nCnt = 0; nCnt < LIGHT_MAX; nCnt++)
	{
		// ライトを設定する
		pDevice->SetLight(nCnt, &m_Light[nCnt]);

		// ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//========================================================
// ライトの終了
//========================================================
void CLight::Uninit(void)
{

}

//========================================================
// ライトの更新
//========================================================
void CLight::Update(void)
{

}