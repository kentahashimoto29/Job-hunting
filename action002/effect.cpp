//========================================================
//
//ウインドウの生成等 (effect.cpp)
//Author 橋本賢太
//
//========================================================
#include "effect.h"
#include "manager.h"
#include "input.h"

int CEffect::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CEffect::CEffect()
{
	AlphaData = 1.0f;
}

//========================================================
//コンストラクタ
//========================================================
CEffect::CEffect(D3DXVECTOR3 pos)
{
	AlphaData = 1.0f;
	m_pos = pos;
}

//========================================================
//デストラクタ
//========================================================
CEffect::~CEffect()
{

}

//========================================================
//生成処理
//========================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect *pEffect;

	//2Dオブジェクトの生成
	pEffect = new CEffect(pos);

	//初期化処理
	pEffect->Init();

	pEffect->BindTexture(m_nIdxTexture);

	return pEffect;
}

//========================================================
//初期化処理
//========================================================
HRESULT CEffect::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\effect000.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");
	}

	CObject2D::Init();

	//種類の設定
	CObject::SetType(TYPE_EFFECT);

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CEffect::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//更新処理
//========================================================
void CEffect::Update(void)
{
	AlphaData -= 0.05f;

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックする
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y - 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y - 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 20.0f, 0.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f * AlphaData);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f * AlphaData);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f * AlphaData);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f * AlphaData);

	//頂点バッファをアンロックする
	m_aVerBuff->Unlock();

	if (AlphaData <= 0.0f)
	{
		Release();
	}
}

//========================================================
//描画処理
//========================================================
void CEffect::Draw(void)
{
	CObject2D::Draw();
}