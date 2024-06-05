//========================================================
//
//ウインドウの生成等 (item3D.cpp)
//Author 橋本賢太
//
//========================================================
#include "item3D.h"
#include "manager.h"
#include "input.h"
#include "bullet3D.h"

int CItem3D::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CItem3D::CItem3D(int nPriority) : CObjectX(nPriority)
{

}

//========================================================
//オーバーライドされたコンストラクタ
//========================================================
CItem3D::CItem3D(D3DXVECTOR3 pos, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
}

//========================================================
//デストラクタ
//========================================================
CItem3D::~CItem3D()
{

}

//========================================================
//生成処理
//========================================================
CItem3D *CItem3D::Create(D3DXVECTOR3 pos)
{
	CItem3D *pPlayer3D;

	//2Dオブジェクトの生成
	pPlayer3D = new CItem3D(pos);

	//初期化処理
	pPlayer3D->Init();

	return pPlayer3D;
}

//========================================================
//初期化処理void
//========================================================
HRESULT CItem3D::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\voltaction000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	CObjectX::Init();

	//CObject::SetType(TYPE_FACE_X);

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CItem3D::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================================
//更新処理
//========================================================
void CItem3D::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	/*if (pInputKeyboard->GetTrigger(DIK_SPACE) == TRUE)
	{
		CBullet3D::Create(m_pos, m_rot);
	}*/
}

//========================================================
//描画処理
//========================================================
void CItem3D::Draw(void)
{
	CObjectX::Draw();
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CItem3D::GetPos(void)
{
	return m_pos;
}