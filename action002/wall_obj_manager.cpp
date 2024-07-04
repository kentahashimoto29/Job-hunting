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
HRESULT CWallObjManager::Init()
{
	ReadWall();

	for (int nCntWall = 0; nCntWall < m_nCreateNum; nCntWall++)
	{
		SetWall(m_nReadPos[nCntWall], m_nReadRot[nCntWall]);
	}

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CWallObjManager::Uninit()
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
void CWallObjManager::Update()
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
void CWallObjManager::Kill()
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
int CWallObjManager::GetNum()
{
	return m_nNum;
}

//==========================================================================
// 敵取得
//==========================================================================
CWallObj **CWallObjManager::GetWall()
{
	return &m_pWall[0];
}

//==========================================================================
// 敵取得
//==========================================================================
void CWallObjManager::ReadWall()
{
	int nCnt = 0;
	char aString[1024];
	FILE *pFile;	//ファイルポインタを宣言

					//ファイルを開く
	pFile = fopen("data\\TEXT\\wall.txt", "r");			//(ファイル名を指定,　モードの指定”r”で読み込み)

	//NULLチェック
	if (pFile == NULL)
	{
		fclose(pFile);
		return;
	}

	while (1)
	{
		fscanf(pFile, "%s", &aString[0]);

		//文字列比較
		if (strcmp(aString, "POS") == 0)
		{
			fscanf(pFile, "%s", &aString[0]);

			fscanf(pFile, "%f", &m_nReadPos[nCnt].x);
			fscanf(pFile, "%f", &m_nReadPos[nCnt].y);
			fscanf(pFile, "%f", &m_nReadPos[nCnt].z);
		}

		//文字列比較
		if (strcmp(aString, "ROT") == 0)
		{
			fscanf(pFile, "%s", &aString[0]);

			fscanf(pFile, "%f", &m_nReadRot[nCnt].x);
			fscanf(pFile, "%f", &m_nReadRot[nCnt].y);
			fscanf(pFile, "%f", &m_nReadRot[nCnt].z);

			nCnt++;
		}

		if (strcmp(aString, "END") == 0)
		{
			m_nCreateNum = nCnt;
			break;
		}
	}

	fclose(pFile);
}