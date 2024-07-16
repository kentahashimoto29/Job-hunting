//========================================================
//
//ウインドウの生成等 (enemymanager.cpp)
//Author 橋本賢太
//
//========================================================
#include "enemymanager.h"
#include "game.h"
#include "fade.h"

#include <time.h>

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
	//SetEnemy(D3DXVECTOR3(-200.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//SetEnemy(D3DXVECTOR3(250.0f, 0.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(200.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	srand((unsigned int)time(NULL));

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CEnemyManager::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 512; nCntEnemy++)
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

	if (m_nCreCnt >= 60 * 0.1f)
	{
		if (CManager::GetInstance()->GetFade()->GetState() == CFade::FADE_NONE)
		{
			SectionSpawn();
		}

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

	if (m_nNum <= 0)
	{
		int i = 0;
	}

	CGame::AddScore();
}

//==========================================================================
// 破棄
//==========================================================================
void CEnemyManager::Kill(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 512; nCntEnemy++)
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
	CEnemy3D *pEnemy[512];
	memset(&pEnemy[0], NULL, sizeof(pEnemy));

		for (int nCnt = 0; nCnt < 512; nCnt++)
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

//==========================================================================
// 敵のスポーン位置を設定
//==========================================================================
void CEnemyManager::SectionSpawn()
{
	float rotY = (float)((rand() % 628 + 0) / 100) - D3DX_PI;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float MaxPosX = 0.0f;
	float MinPosX = 0.0f;
	float MaxPosZ = 0.0f;
	float MinPosZ = 0.0f;


	while (1)
	{
		int n = rand() % 8 + 1;

		switch (n)
		{
		case 1: // 区画1
			pos.x = (float)(rand() % 11000 + 0) / 10;
			pos.z = (float)(rand() % 3000 + 0) / 10;

			MaxPosX = 1150.0f;
			MinPosX = -50.0f;
			MaxPosZ = 350.0f;
			MinPosZ = -50.0f;

			break;

		case 2: // 区画2
			pos.x = (float)(rand() % 11000 + 0) / 10;
			pos.z = (float)(rand() % 2000 + 4000) / 10;

			MaxPosX = 1150.0f;
			MinPosX = -50.0f;
			MaxPosZ = 650.0f;
			MinPosZ = 350.0f;

			break;

		case 3: // 区画3
			pos.x = (float)(rand() % 11000 + 0) / 10;
			pos.z = (float)(rand() % 2000 + 7000) / 10;

			MaxPosX = 1150.0f;
			MinPosX = -50.0f;
			MaxPosZ = 950.0f;
			MinPosZ = 650.0f;

			break;

		case 4: // 区画4
			pos.x = (float)(rand() % 3000 + 12000) / 10;
			pos.z = (float)(rand() % 9000 + 0) / 10;

			MaxPosX = 1550.0f;
			MinPosX = 1150.0f;
			MaxPosZ = 950.0f;
			MinPosZ = -50.0f;

			break;

		case 5: // 区画5
			pos.x = (float)(rand() % 9000 + 6000) / 10;
			pos.z = (float)(rand() % 5000 + 10000) / 10;

			MaxPosX = 1550.0f;
			MinPosX = 550.0f;
			MaxPosZ = 1550.0f;
			MinPosZ = 950.0f;

			break;

		case 6: // 区画6
			pos.x = (float)(rand() % 1000 + 0) / 10;
			pos.z = (float)(rand() % 5000 + 10000) / 10;

			MaxPosX = 150.0f;
			MinPosX = -50.0f;
			MaxPosZ = 1550.0f;
			MinPosZ = 950.0f;

			break;

		case 7: // 区画7
			pos.x = (float)(rand() % 5000 + 0) / 10;
			pos.z = (float)(rand() % 1000 + 14000) / 10;

			MaxPosX = 550.0f;
			MinPosX = -50.0f;
			MaxPosZ = 1550.0f;
			MinPosZ = 1350.0f;

			break;

		default:
			break;
		}

		D3DXVECTOR3 CompPos = CGame::GetPlayer3D()->GetPos();

		if ((CGame::GetPlayer3D()->GetPos().x >= MinPosX &&
			CGame::GetPlayer3D()->GetPos().x <= MaxPosX &&
			CGame::GetPlayer3D()->GetPos().z >= MinPosZ &&
			CGame::GetPlayer3D()->GetPos().z <= MaxPosZ) == false &&
			pos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			break;
		}
	}

	SetEnemy(pos, D3DXVECTOR3(0.0f, rotY, 0.0f));
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