//========================================================
//
//ウインドウの生成等 (bullet.cpp)
//Author 橋本賢太
//
//========================================================
#include <time.h>
#include "enemymanager.h"
#include "game.h"

int CEnemyManager::m_nNum = 0;

//========================================================
//コンストラクタ
//========================================================
CEnemyManager::CEnemyManager()
{
	memset(&m_pEnemy3D[0], NULL, sizeof(m_pEnemy3D));		// 
	m_nCreCnt = 0;
}

//========================================================
//デストラクタ
//========================================================
CEnemyManager::~CEnemyManager()
{

}

//========================================================
//生成処理
//========================================================
CEnemyManager *CEnemyManager::Create()
{
	CEnemyManager *pEnemyManager = NULL;

	//2Dオブジェクトの生成
	pEnemyManager = new CEnemyManager;

	//初期化処理
	pEnemyManager->Init();

	return pEnemyManager;
}

//========================================================
//初期化処理
//========================================================
HRESULT CEnemyManager::Init(void)
{
	SetEnemy(D3DXVECTOR3(-200.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(200.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	srand((unsigned int)time(NULL));

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CEnemyManager::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pEnemy3D[nCntEnemy] != NULL)
		{
			m_pEnemy3D[nCntEnemy]->Uninit();
			m_pEnemy3D[nCntEnemy] = NULL;

			// 総数減算
			m_nNum--;
		}
	}
}

//========================================================
//更新処理
//========================================================
void CEnemyManager::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	m_nCreCnt++;

	//Nキーを押したとき
	if (pInputKeyboard->GetTrigger(DIK_N) == true)
	{
		SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	if (m_nCreCnt >= 60 * 2)
	{
		float f = (float)((rand() % 628 + 0) / 100) - D3DX_PI;

		SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, f, 0.0f));

		//スポーンはマップを４つの区画に分けてプレイヤーのいない区画に湧くようにする

		m_nCreCnt = 0;
	}
}

//==========================================================================
// 破棄
//==========================================================================
void CEnemyManager::Release(int nIdx)
{
	if (m_pEnemy3D[nIdx] != NULL)
	{
		m_pEnemy3D[nIdx] = NULL;
	}

	// 総数減算
	m_nNum--;

	CGame::AddScore();
}

//==========================================================================
// 破棄
//==========================================================================
void CEnemyManager::Kill(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pEnemy3D[nCntEnemy] != NULL)
		{
			m_pEnemy3D[nCntEnemy]->Uninit();
			m_pEnemy3D[nCntEnemy] = NULL;
		}
	}
}

//==========================================================================
// 敵配置
//==========================================================================
CEnemy3D **CEnemyManager::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy3D *pEnemy[16];
	memset(&pEnemy[0], NULL, sizeof(pEnemy));

		for (int nCnt = 0; nCnt < 16; nCnt++)
		{
			if (m_pEnemy3D[nCnt] != NULL)
			{// 情報が入ってたら
				continue;
			}



			// 敵の生成
			m_pEnemy3D[nCnt] = CEnemy3D::Create(pos, rot, nCnt);			// 種類

			if (m_pEnemy3D[nCnt] == NULL)
			{// 失敗していたら

				delete m_pEnemy3D[nCnt];
				m_pEnemy3D[nCnt] = NULL;
				break;
			}

			// ポインタコピー
			pEnemy[nCnt] = m_pEnemy3D[nCnt];

			// 総数加算
			m_nNum++;
			break;
		}

	return &pEnemy[0];
}

//========================================================
//位置を返す
//========================================================
int CEnemyManager::GetNum(void)
{
	return m_nNum;
}

//==========================================================================
// 敵取得
//==========================================================================
CEnemy3D **CEnemyManager::GetEnemy(void)
{
	return &m_pEnemy3D[0];
}