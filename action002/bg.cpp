//========================================================
//
//ウインドウの生成等 (bg.cpp)
//Author 橋本賢太
//
//========================================================
#include "bg.h"
#include "manager.h"

//マクロ定義
#define BG_MAX									(3)		//背景の最大数

int CBG::m_nIdxTexture[BG_MAX] = {};

//========================================================
//コンストラクタ
//========================================================
CBG::CBG()
{
	
}

//========================================================
//デストラクタ
//========================================================
CBG::~CBG()
{

}

//========================================================
//生成処理
//========================================================
CBG *CBG::Create()
{
	CBG *pBG;

	//2Dオブジェクトの生成
	pBG = new CBG();

	//初期化処理
	pBG->Init();

	return pBG;
}

//========================================================
//初期化処理
//========================================================
HRESULT CBG::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_nIdxTexture[0] = pTexture->Regist("data\\TEXTURE\\bg100.png");
	m_nIdxTexture[1] = pTexture->Regist("data\\TEXTURE\\bg101.png");
	m_nIdxTexture[2] = pTexture->Regist("data\\TEXTURE\\bg102.png");

	for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = new CObject2D;

		m_apObject2D[nCnt]->Init();

		m_apObject2D[nCnt]->BindTexture(m_nIdxTexture[nCnt]);

		m_aTexV[nCnt] = 0.0f;

		switch (nCnt)
		{
		case 0:
			m_type[nCnt] = TYPE_BG000;
			break;

		case 1:
			m_type[nCnt] = TYPE_BG001;
			break;

		case 2:
			m_type[nCnt] = TYPE_BG002;
			break;

		default:
			break;
		}
	}

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CBG::Uninit(void)
{
	for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Uninit();
	}
}

//========================================================
//更新処理
//========================================================
void CBG::Update(void)
{
	for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
	{
		switch (m_type[nCnt])
		{
		case TYPE_BG000:
			m_aTexV[nCnt] += 0.9992f;
			break;

		case TYPE_BG001:
			m_aTexV[nCnt] += 0.9986f;
			break;

		case TYPE_BG002:
			m_aTexV[nCnt] += 0.998f;
			break;

		default:
			break;
		}

		m_apObject2D[nCnt]->SetVtxBG(m_aTexV[nCnt]);
	}
}

//========================================================
//描画処理
//========================================================
void CBG::Draw(void)
{
	for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}
}

//========================================================
//
//========================================================
D3DXVECTOR3 CBG::GetPos(void)
{
	return m_pos;
}


//========================================================
//位置を返す
//========================================================
void CBG::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//位置を返す
//========================================================
void CBG::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}