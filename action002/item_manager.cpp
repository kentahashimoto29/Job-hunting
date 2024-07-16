//========================================================
// 
// ウインドウの生成等 (item_manager.cpp)
// Author 橋本賢太
// 
//========================================================
#include "item_manager.h"
#include "game.h"

int CItemManager::m_nNum = 0;

//========================================================
// コンストラクタ
//========================================================
CItemManager::CItemManager()
{
	memset(&m_pItemThrow[0], NULL, sizeof(m_pItemThrow));		// 
}

//========================================================
// デストラクタ
//========================================================
CItemManager::~CItemManager()
{

}

//========================================================
// 生成処理
//========================================================
CItemManager *CItemManager::Create()
{
	CItemManager *pEnemyManager = NULL;

	// 2Dオブジェクトの生成
	pEnemyManager = new CItemManager;

	// 初期化処理
	pEnemyManager->Init();

	return pEnemyManager;
}

//========================================================
// 初期化処理
//========================================================
HRESULT CItemManager::Init(void)
{
	return S_OK;
}

//========================================================
// 終了処理
//========================================================
void CItemManager::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pItemThrow[nCntEnemy] != NULL)
		{
			m_pItemThrow[nCntEnemy]->Uninit();
			m_pItemThrow[nCntEnemy] = NULL;

			// 総数減算
			m_nNum--;
		}
	}
}

//========================================================
// 更新処理
//========================================================
void CItemManager::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// Wキーを押したとき
	if (pInputKeyboard->GetTrigger(DIK_V) == true)
	{
		SetItemThrow(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//==========================================================================
// 破棄
//==========================================================================
void CItemManager::Release(int nIdx)
{
	if (m_pItemThrow[nIdx] != NULL)
	{
		m_pItemThrow[nIdx] = NULL;
	}

	// 総数減算
	m_nNum--;

	CGame::AddScore();
}

//==========================================================================
// 破棄
//==========================================================================
void CItemManager::Kill(void)
{
	for (int nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pItemThrow[nCntEnemy] != NULL)
		{
			m_pItemThrow[nCntEnemy]->Uninit();
			m_pItemThrow[nCntEnemy] = NULL;
		}
	}
}

//==========================================================================
// 敵配置
//==========================================================================
CItemThrow **CItemManager::SetItemThrow(D3DXVECTOR3 pos)
{
	CItemThrow *pEnemy[16];
	memset(&pEnemy[0], NULL, sizeof(pEnemy));

	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		if (m_pItemThrow[nCnt] != NULL)
		{// 情報が入ってたら
			continue;
		}



		// 敵の生成
		m_pItemThrow[nCnt] = CItemThrow::Create(pos, nCnt);			// 種類

		if (m_pItemThrow[nCnt] == NULL)
		{// 失敗していたら

			delete m_pItemThrow[nCnt];
			m_pItemThrow[nCnt] = NULL;
			break;
		}

		// ポインタコピー
		pEnemy[nCnt] = m_pItemThrow[nCnt];

		// 総数加算
		m_nNum++;
		break;
	}

	return &pEnemy[0];
}

//========================================================
// 位置を返す
//========================================================
int CItemManager::GetNum(void)
{
	return m_nNum;
}

//==========================================================================
// 敵取得
//==========================================================================
CItemThrow **CItemManager::GetItemThrow(void)
{
	return &m_pItemThrow[0];
}