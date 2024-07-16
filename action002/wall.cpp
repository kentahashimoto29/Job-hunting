//========================================================
// 
// ウインドウの生成等 (wall.cpp)
// Author 橋本賢太
// 
//========================================================
#include "wall.h"
#include "manager.h"

int CWall::m_nIdxTexture = 0;

//========================================================
// コンストラクタ
//========================================================
CWall::CWall()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aVerBuff = NULL;
}

//========================================================
// コンストラクタ
//========================================================
CWall::CWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
	m_aVerBuff = NULL;
}

//========================================================
// デストラクタ
//========================================================
CWall::~CWall()
{

}

//========================================================
// 生成処理
//========================================================
CWall *CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CWall *pWall;

	// 2Dオブジェクトの生成
	pWall = new CWall(pos, rot);

	// 初期化処理
	pWall->Init();

	return pWall;
}

//========================================================
// ポリゴンの初期化処理
//========================================================
HRESULT CWall::Init()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\block000.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			m_nIdxTexture = nCnt;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\block000.jpg");
	}

	BindTexture(m_nIdxTexture);

	CObject3D::Init();

	SetVtxWall();

	SetType(TYPE_WALL);

	return S_OK;
}

//========================================================
// ポリゴンの終了処理
//========================================================
void CWall::Uninit(void)
{
	CObject3D::Uninit();
}

//========================================================
// ポリゴンの更新処理
//========================================================
void CWall::Update(void)
{

}

//========================================================
// ポリゴンの描画処理
//========================================================
void CWall::Draw(void)
{
	CObject3D::Draw();
}

//========================================================
// 位置を返す
//========================================================
D3DXVECTOR3 CWall::GetPos(void)
{
	return m_pos;
}

//========================================================
// インデックスバッファのポインタを返す
//========================================================
LPDIRECT3DINDEXBUFFER9 CWall::GetIdxBuff(void)
{
	return m_pIdxBuff;
}