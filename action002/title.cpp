//========================================================
//
//ウインドウの生成等 (title.cpp)
//Author 橋本賢太
//
//========================================================
#include "title.h"
#include "title_obj2D.h"
#include "object2D.h"
#include "fade.h"

#define FEILD_WIDTH_NUM							(16)
#define FEILD_HEIGHT_NUM						(16)
#define WALL_WIDTH_NUM							(16)
#define WALL_HEIGHT_NUM							(2)
#define WALL_NUM								(4)
#define FEILD_WIDTH								(100.0f)
#define FEILD_HEIGHT							(100.0f)
#define WALL_WIDTH								(100.0f)
#define WALL_HEIGHT								(100.0f)


//========================================================
//静的メンバ変数
//========================================================
CTitle_Obj2D *CTitle::m_apTitleObj = NULL;
CWallObjManager *CTitle::m_pWallManager = NULL;
int CTitle::m_nIdxTexture = 0;
float CTitle::m_nInitPos = 0.0f;

//========================================================
//コンストラクタ
//========================================================
CTitle::CTitle()
{
	b = false;
}

//========================================================
//デストラクタ
//========================================================
CTitle::~CTitle()
{

}

//========================================================
//初期化処理
//========================================================
HRESULT CTitle::Init(void)
{
	m_pWallManager = CWallObjManager::Create();

	m_apTitleObj = CTitle_Obj2D::Create();

	for (int nCntHeight = 0; nCntHeight < FEILD_HEIGHT_NUM; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < FEILD_WIDTH_NUM; nCntWidth++)
		{
			m_pField[nCntWidth + nCntHeight * FEILD_WIDTH_NUM] =
				CField::Create(D3DXVECTOR3(FEILD_WIDTH * nCntWidth, 0.0f, FEILD_HEIGHT * nCntHeight), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	m_nInitPos = ((100.0f * WALL_WIDTH_NUM) - 50.0f);


	for (int nCntHeight = 0; nCntHeight < WALL_HEIGHT_NUM; nCntHeight++)
	{
		for (int nCntNum = 0; nCntNum < WALL_NUM; nCntNum++)
		{
			for (int nCntWidth = 0; nCntWidth < WALL_WIDTH_NUM; nCntWidth++)
			{
				switch (nCntNum)
				{
				case 0:
					m_pWall[nCntWidth + nCntNum * WALL_WIDTH_NUM + nCntHeight * WALL_NUM * WALL_WIDTH_NUM] =
						CWall::Create(D3DXVECTOR3(-50.0f, 50.0f + WALL_HEIGHT * nCntHeight, WALL_WIDTH * nCntWidth), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));
					break;


				case 1:
					m_pWall[nCntWidth + nCntNum * WALL_WIDTH_NUM + nCntHeight * WALL_NUM * WALL_WIDTH_NUM] =
						CWall::Create(D3DXVECTOR3(WALL_WIDTH * nCntWidth, 50.0f + WALL_HEIGHT * nCntHeight, m_nInitPos), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					break;


				case 2:
					m_pWall[nCntWidth + nCntNum * WALL_WIDTH_NUM + nCntHeight * WALL_NUM * WALL_WIDTH_NUM] =
						CWall::Create(D3DXVECTOR3(m_nInitPos, 50.0f + WALL_HEIGHT * nCntHeight, (m_nInitPos - 50.0f) - WALL_WIDTH * nCntWidth), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
					break;


				case 3:
					m_pWall[nCntWidth + nCntNum * WALL_WIDTH_NUM + nCntHeight * WALL_NUM * WALL_WIDTH_NUM] =
						CWall::Create(D3DXVECTOR3(-WALL_WIDTH * nCntWidth + (m_nInitPos - 50.0f), 50.0f + WALL_HEIGHT * nCntHeight, -50.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
					break;


				default:
					break;
				}
			}
		}
	}

	CManager::GetInstance()->GetCamera()->SetPosTitle();

	b = false;

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CTitle::Uninit(void)
{
	//NULLチェック
	if (m_apTitleObj != NULL)
	{
		//終了処理
		m_apTitleObj->Uninit();
		m_apTitleObj = NULL;
	}

	//NULLチェック
	if (m_pWallManager != NULL)
	{
		//終了処理
		m_pWallManager->Uninit();
		m_pWallManager = NULL;
	}

	for (int nCntField = 0; nCntField < FEILD_WIDTH_NUM * FEILD_HEIGHT_NUM; nCntField++)
	{
		//NULLチェック
		if (m_pField[nCntField] != NULL)
		{
			m_pField[nCntField]->Uninit();
			m_pField[nCntField] = NULL;
		}
	}

	for (int nCntWall = 0; nCntWall < WALL_WIDTH_NUM * WALL_HEIGHT_NUM * WALL_NUM; nCntWall++)
	{
		//NULLチェック
		if (m_pWall[nCntWall] != NULL)
		{
			m_pWall[nCntWall]->Uninit();
			m_pWall[nCntWall] = NULL;
		}
	}

	CScene::Uninit();
}

//========================================================
//更新処理
//========================================================
void CTitle::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//マウスの取得
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	if (CTitle_Obj2D::GetBlinkingCnt() >= 60 * 2)
	{
		if (b != true)
		{
			if (CManager::GetInstance()->GetFade()->GetState() == CFade::FADE_NONE)
			{
				CManager::GetInstance()->GetFade()->SetFade(CManager::GetInstance()->GetScene()->MODE_GAME);
				b = true;
			}
		}
	}
}

//========================================================
//描画処理
//========================================================
void CTitle::Draw(void)
{
	m_apTitleObj->Draw();
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CTitle::GetPos(void)
{
	return m_pos;
}

//========================================================
//位置を返す
//========================================================
void CTitle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//位置を返す
//========================================================
void CTitle::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}