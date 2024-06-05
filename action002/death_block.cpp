//========================================================
//
//ウインドウの生成等 (block3D.cpp)
//Author 橋本賢太
//
//========================================================
#include "death_block.h"
#include "manager.h"
#include "player3D.h"
#include "game.h"

int CDeathBlock::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CDeathBlock::CDeathBlock(int nPriority) : CObjectX(nPriority)
{

}

//========================================================
//オーバーライドされたコンストラクタ
//========================================================
CDeathBlock::CDeathBlock(D3DXVECTOR3 pos, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
}

//========================================================
//デストラクタ
//========================================================
CDeathBlock::~CDeathBlock()
{

}

//========================================================
//生成処理
//========================================================
CDeathBlock *CDeathBlock::Create(D3DXVECTOR3 pos)
{
	CDeathBlock *pPlayer3D;

	//2Dオブジェクトの生成
	pPlayer3D = new CDeathBlock(pos);

	//初期化処理
	pPlayer3D->Init();

	return pPlayer3D;
}

//========================================================
//初期化処理
//========================================================
HRESULT CDeathBlock::Init(void)
{
	int nNumVtx;				//頂点数
	DWORD dwSizeFVF;			//頂点フォーマットのサイズ
	BYTE *pVtxBuff;				//頂点バッファへのポインタ

								//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\damage_box000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	//頂点数を取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());


	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;					//頂点座標の代入

		if (m_VtxMin.x > vtx.x)
		{
			m_VtxMin.x = vtx.x;
		}

		else if (m_VtxMax.x < vtx.x)
		{
			m_VtxMax.x = vtx.x;
		}

		if (m_VtxMin.y > vtx.y)
		{
			m_VtxMin.y = vtx.y;
		}

		else if (m_VtxMax.y < vtx.y)
		{
			m_VtxMax.y = vtx.y;
		}

		if (m_VtxMin.z > vtx.z)
		{
			m_VtxMin.z = vtx.z;
		}

		else if (m_VtxMax.z < vtx.z)
		{
			m_VtxMax.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;					//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	CObject::SetType(TYPE_BLOCK_DEATH);

	CObjectX::Init();

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CDeathBlock::Uninit(void)
{
	Release();
}

//========================================================
//更新処理
//========================================================
void CDeathBlock::Update(void)
{
	if (bool b = CGame::GetPlayer3D()->Collisionbool(&m_pos, m_VtxMax, m_VtxMin, CObject::GetType()) == true)
	{
		CGame::GetPlayer3D()->Respawn();
	}
}

//========================================================
//描画処理
//========================================================
void CDeathBlock::Draw(void)
{
	CObjectX::Draw();
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CDeathBlock::GetPos(void)
{
	return m_pos;
}