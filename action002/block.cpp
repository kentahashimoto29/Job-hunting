//========================================================
//
//ウインドウの生成等 (block.cpp)
//Author 橋本賢太
//
//========================================================
#include "block.h"
#include "manager.h"

int CBlock::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CBlock::CBlock()
{

}

//========================================================
//コンストラクタ
//========================================================
CBlock::CBlock(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//デストラクタ
//========================================================
CBlock::~CBlock()
{

}

//========================================================
//生成処理
//========================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock *pBlock;

	//ブロックの生成
	pBlock = new CBlock(pos);

	//初期化処理
	pBlock->Init();

	pBlock->BindTexture(m_nIdxTexture);

	return pBlock;
}

//========================================================
//初期化処理
//========================================================
HRESULT CBlock::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\block000.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\block000.jpg");
	}

	CObject2D::Init();

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CBlock::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//更新処理
//========================================================
void CBlock::Update(void)
{
	CObject2D::SetVtxBlock(m_pos);
}

//========================================================
//描画処理
//========================================================
void CBlock::Draw(void)
{
	CObject2D::Draw();
}