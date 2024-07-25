//========================================================
// 
// 影の処理 (shadow.cpp)
// Author 橋本賢太
// 
//========================================================
#include "shadow.h"
#include "manager.h"
#include "game.h"

int CShadow::m_nIdxTexture = 0;

//========================================================
// コンストラクタ
//========================================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
}

//========================================================
// コンストラクタ
//========================================================
CShadow::CShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority) : CObject3D(nPriority)
{
	m_pos = pos;
	m_rot = rot;
	m_aVerBuff = NULL;
}

//========================================================
// デストラクタ
//========================================================
CShadow::~CShadow()
{

}

//========================================================
// 生成処理
//========================================================
CShadow *CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CShadow *pField;

	// 2Dオブジェクトの生成
	pField = new CShadow(pos, rot);

	// 初期化処理
	pField->Init();

	return pField;
}

//========================================================
// ポリゴンの初期化処理
//========================================================
HRESULT CShadow::Init(void)
{
	m_nIdxTexture = SetTex("data\\TEXTURE\\shadow000.jpg");
	BindTexture(m_nIdxTexture);
	CObject3D::Init();
	SetVtxShadow();
	SetType(TYPE_SHADOW);

	return S_OK;
}

//========================================================
// ポリゴンの終了処理
//========================================================
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//========================================================
// ポリゴンの更新処理
//========================================================
void CShadow::Update(void)
{
	CObject3D::Update();
}

//========================================================
// ポリゴンの描画処理
//========================================================
void CShadow::Draw(void)
{
	CObject3D::Draw();
}