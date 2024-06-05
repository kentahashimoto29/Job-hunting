//========================================================
//
//ウインドウの生成等 (block3D.cpp)
//Author 橋本賢太
//
//========================================================
#include "block3D.h"
#include "manager.h"
#include "player3D.h"
#include "game.h"

int CBlock3D::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CBlock3D::CBlock3D(int nPriority) : CObjectX(nPriority)
{

}

//========================================================
//オーバーライドされたコンストラクタ
//========================================================
CBlock3D::CBlock3D(D3DXVECTOR3 pos, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
}

//========================================================
//デストラクタ
//========================================================
CBlock3D::~CBlock3D()
{

}

//========================================================
//生成処理
//========================================================
CBlock3D *CBlock3D::Create(D3DXVECTOR3 pos)
{
	CBlock3D *pPlayer3D;

	//2Dオブジェクトの生成
	pPlayer3D = new CBlock3D(pos);

	//初期化処理
	pPlayer3D->Init();

	return pPlayer3D;
}

//========================================================
//初期化処理
//========================================================
HRESULT CBlock3D::Init(void)
{
	int nNumVtx;				//頂点数
	DWORD dwSizeFVF;			//頂点フォーマットのサイズ
	BYTE *pVtxBuff;				//頂点バッファへのポインタ

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\box001.x",
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
	
	CObject::SetType(TYPE_BLOCK_3D);

	CObjectX::Init();

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CBlock3D::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================================
//更新処理
//========================================================
void CBlock3D::Update(void)
{
	CGame::GetPlayer3D()->Collision(&m_pos, m_VtxMax, m_VtxMin, CObject::GetType());
}

//========================================================
//描画処理
//========================================================
void CBlock3D::Draw(void)
{
	CObjectX::Draw();
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CBlock3D::GetPos(void)
{
	return m_pos;
}

//=======================================
//モデルの当たり判定
//=======================================
bool CBlock3D::Collisionbool(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pmove, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	bool bland = true;

	//プレイヤーがブロックにめり込む
	if (m_pos.x + m_VtxMin.x < pPos->x + vtxMax.x &&
		m_pos.x + m_VtxMax.x > pPos->x + vtxMin.x &&
		m_pos.y + m_VtxMin.y < pPos->y + vtxMax.y &&
		m_pos.y + m_VtxMax.y > pPos->y + vtxMin.y &&
		m_pos.z + m_VtxMin.z < pPos->z + vtxMax.z &&
		m_pos.z + m_VtxMax.z > pPos->z + vtxMin.z)
	{
		//============================
		//下
		//============================
		if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
			m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
		{
			//左からぶつかった
			if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			//右からぶつかった
			else  if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			//正面からぶつかった
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->y = m_pos.y + m_VtxMin.y + vtxMin.y;
			}
		}

		//================================
		//上
		//================================
		else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
			m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
		{
			//左からぶつかった
			if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			//右からぶつかった
			else  if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			//正面からぶつかった
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				bland = false;
				pPos->y = m_pos.y + m_VtxMin.y + vtxMax.y;
				pmove->y = 0.0f;
			}
		}

		//============================
		//右
		//============================
		else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
			m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
		{
			//下からぶつかった
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			//上からぶつかった
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			//正面からぶつかった
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x + m_VtxMax.x + vtxMax.x;
				pmove->x = 0.0f;
			}
		}

		//============================
		//左
		//============================
		else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
			m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
		{
			//下からぶつかった
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			//上からぶつかった
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			//正面からぶつかった
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x + m_VtxMin.x + vtxMin.x;
				pmove->x = 0.0f;
			}
		}

		//============================
		//正面
		//============================
		else if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
			m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
		{
			//下からぶつかった
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			//上からぶつかった
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			//右からぶつかった
			else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			//左からぶつかった
			else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z + m_VtxMin.z + vtxMin.z;
				pmove->z = 0.0f;
			}
		}

		//============================
		//裏
		//============================
		else if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
			m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
		{
			//下からぶつかった
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			//上からぶつかった
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			//右からぶつかった
			else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			//左からぶつかった
			else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z + m_VtxMax.z + vtxMax.z;
				pmove->z = 0.0f;
			}
		}
	}

	return bland;
}

//=======================================
//モデルの当たり判定
//=======================================
void CBlock3D::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pmove, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	//プレイヤーがブロックにめり込む
	if (m_pos.x + m_VtxMin.x < pPos->x + vtxMax.x &&
		m_pos.x + m_VtxMax.x > pPos->x + vtxMin.x &&
		m_pos.y + m_VtxMin.y < pPos->y + vtxMax.y &&
		m_pos.y + m_VtxMax.y > pPos->y + vtxMin.y &&
		m_pos.z + m_VtxMin.z < pPos->z + vtxMax.z &&
		m_pos.z + m_VtxMax.z > pPos->z + vtxMin.z)
	{
		//============================
		//下
		//============================
		if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
			m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
		{
			//左からぶつかった
			if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			//右からぶつかった
			else  if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			//正面からぶつかった
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->y = m_pos.y + m_VtxMin.y + vtxMin.y;
			}
		}

		//================================
		//上
		//================================
		else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
			m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
		{
			//左からぶつかった
			if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			//右からぶつかった
			else  if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			//正面からぶつかった
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->y = m_pos.y + m_VtxMin.y + vtxMax.y;
				pmove->y = 0.0f;
			}
		}

		//============================
		//右
		//============================
		else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
			m_pos.x + m_VtxMax.x < pPosOld->x + vtxMin.x)
		{
			//下からぶつかった
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			//上からぶつかった
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			//正面からぶつかった
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x + m_VtxMax.x + vtxMax.x;
				pmove->x = 0.0f;
			}
		}

		//============================
		//左
		//============================
		else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
			m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
		{
			//下からぶつかった
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			//上からぶつかった
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			//正面からぶつかった
			else  if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
				m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
			{
			}

			//裏からぶつかった
			else  if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
				m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
			{
			}

			else
			{
				pPos->x = m_pos.x + m_VtxMin.x + vtxMin.x;
				pmove->x = 0.0f;
			}
		}

		//============================
		//正面
		//============================
		else if (m_pos.z + m_VtxMin.z <= pPos->z + vtxMax.z &&
			m_pos.z + m_VtxMin.z >= pPosOld->z + vtxMax.z)
		{
			//下からぶつかった
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			//上からぶつかった
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			//右からぶつかった
			else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			//左からぶつかった
			else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z + m_VtxMin.z + vtxMin.z;
				pmove->z = 0.0f;
			}
		}

		//============================
		//裏
		//============================
		else if (m_pos.z + m_VtxMax.z >= pPos->z + vtxMin.z &&
			m_pos.z + m_VtxMax.z <= pPosOld->z + vtxMin.z)
		{
			//下からぶつかった
			if (m_pos.y + m_VtxMin.y <= pPos->y + vtxMax.y &&
				m_pos.y + m_VtxMin.y >= pPosOld->y + vtxMax.y)
			{
			}

			//上からぶつかった
			else if (m_pos.y + m_VtxMax.y >= pPos->y + vtxMin.y &&
				m_pos.y + m_VtxMax.y <= pPosOld->y + vtxMin.y)
			{
			}

			//右からぶつかった
			else if (m_pos.x + m_VtxMax.x >= pPos->x + vtxMin.x &&
				m_pos.x + m_VtxMax.x <= pPosOld->x + vtxMin.x)
			{
			}

			//左からぶつかった
			else if (m_pos.x + m_VtxMin.x <= pPos->x + vtxMax.x &&
				m_pos.x + m_VtxMin.x >= pPosOld->x + vtxMax.x)
			{
			}

			else
			{
				pPos->z = m_pos.z + m_VtxMax.z + vtxMax.z;
				pmove->z = 0.0f;
			}
		}
	}
}