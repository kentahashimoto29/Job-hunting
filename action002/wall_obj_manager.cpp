//========================================================
//
//ウインドウの生成等 (bullet.cpp)
//Author 橋本賢太
//
//========================================================
#include <time.h>
#include "wall_obj.h"
#include "wall_obj_manager.h"
#include "game.h"

int CWallObjManager::m_nNum = 0;

//========================================================
//コンストラクタ
//========================================================
CWallObjManager::CWallObjManager()
{
	memset(&m_pWall[0], NULL, sizeof(m_pWall));		// 
	m_nCreCnt = 0;
}

//========================================================
//デストラクタ
//========================================================
CWallObjManager::~CWallObjManager()
{

}

//========================================================
//生成処理
//========================================================
CWallObjManager *CWallObjManager::Create()
{
	CWallObjManager *pEnemyManager = NULL;

	//2Dオブジェクトの生成
	pEnemyManager = new CWallObjManager;

	//初期化処理
	pEnemyManager->Init();

	return pEnemyManager;
}

//========================================================
//初期化処理
//========================================================
HRESULT CWallObjManager::Init(void)
{
	SetWall(D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CWallObjManager::Uninit(void)
{
	for (int nCntWall = 0; nCntWall < 16; nCntWall++)
	{
		if (m_pWall[nCntWall] != NULL)
		{
			m_pWall[nCntWall]->Uninit();
			m_pWall[nCntWall] = NULL;

			// 総数減算
			m_nNum--;
		}
	}
}

//========================================================
//更新処理
//========================================================
void CWallObjManager::Update(void)
{
	
}

//==========================================================================
// 破棄
//==========================================================================
void CWallObjManager::Release(int nIdx)
{
	if (m_pWall[nIdx] != NULL)
	{
		m_pWall[nIdx] = NULL;
	}

	// 総数減算
	m_nNum--;

	CGame::AddScore();
}

//==========================================================================
// 破棄
//==========================================================================
void CWallObjManager::Kill(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pWall[nCntEnemy] != NULL)
		{
			m_pWall[nCntEnemy]->Uninit();
			m_pWall[nCntEnemy] = NULL;
		}
	}
}

//==========================================================================
// 敵配置
//==========================================================================
CWallObj **CWallObjManager::SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CWallObj *pWall[16];
	memset(&pWall[0], NULL, sizeof(pWall));

	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		if (m_pWall[nCnt] != NULL)
		{// 情報が入ってたら
			continue;
		}



		// 敵の生成
		m_pWall[nCnt] = CWallObj::Create(pos, rot, nCnt);			// 種類

		if (m_pWall[nCnt] == NULL)
		{// 失敗していたら

			delete m_pWall[nCnt];
			m_pWall[nCnt] = NULL;
			break;
		}

		// ポインタコピー
		pWall[nCnt] = m_pWall[nCnt];

		// 総数加算
		m_nNum++;
		break;
	}

	return &pWall[0];
}

//========================================================
//位置を返す
//========================================================
int CWallObjManager::GetNum(void)
{
	return m_nNum;
}

//==========================================================================
// 敵取得
//==========================================================================
CWallObj **CWallObjManager::GetWall(void)
{
	return &m_pWall[0];
}