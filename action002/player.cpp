//========================================================
//
//ウインドウの生成等 (player.cpp)
//Author 橋本賢太
//
//========================================================
#include "player.h"
#include "manager.h"
#include "input.h"

int CPlayer::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CPlayer::CPlayer()
{

}

//========================================================
//オーバーライドされたコンストラクタ
//========================================================
CPlayer::CPlayer(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nPtnAnim = 0;
	m_nPtnAnim2 = 0;
}

//========================================================
//デストラクタ
//========================================================
CPlayer::~CPlayer()
{

}

//========================================================
//生成処理
//========================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer;

	//2Dオブジェクトの生成
	pPlayer = new CPlayer(pos);

	//初期化処理
	pPlayer->Init();

	pPlayer->BindTexture(m_nIdxTexture);

	return pPlayer;
}

//========================================================
//初期化処理
//========================================================
HRESULT CPlayer::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\runningman100.png" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\runningman100.png");
	}

	CObject2D::Init();

	//種類の設定
	CObject::SetType(TYPE_PLATER);

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CPlayer::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//更新処理
//========================================================
void CPlayer::Update(void)
{
	CInputKeyboard *pInputKeyboard;

	//キーボードの取得
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	m_pos += m_move;
	GravityCnt++;

	

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == TRUE)
	{
		//CBullet::Create(m_pos);
	}

	m_nCntAnim++;               //カウンターを加算する

	if ((m_nCntAnim % 30) == 0)
	{
		m_nCntAnim = 0;         //カウンターを初期値に戻す
		m_nPtnAnim++;           //パターンNo.を実行する

		if (m_nPtnAnim > 4)
		{
			m_nPtnAnim = 0;     //パターンNo.を初期値に戻す
			m_nPtnAnim2++;

			if (m_nPtnAnim2 > 1)
			{
				m_nPtnAnim2 = 0;     //パターンNo.を初期値に戻す
			}
		}
	}

	//重力設定
	if (GravityCnt >= 2)
	{
		m_move.y += 2.0f;
		GravityCnt = 0;
	}

	if (m_pos.y >= SCREEN_HEIGHT - 200.0f)
	{
		m_pos.y -= m_move.y;
		m_move.y = 0.0f;
	}

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックする
	CObject2D::m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 150.0f, m_pos.y - 200.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 150.0f, m_pos.y - 200.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 150.0f, m_pos.y + 200.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 150.0f, m_pos.y + 200.0f, 0.0f);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_nPtnAnim * 0.2f, 0.0f + m_nPtnAnim2 * 0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.2f + m_nPtnAnim * 0.2f, 0.0f + m_nPtnAnim2 * 0.5f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_nPtnAnim * 0.2f, 0.5f + m_nPtnAnim2 * 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.2f + m_nPtnAnim * 0.2f, 0.5f + m_nPtnAnim2 * 0.5f);

	//頂点バッファをアンロックする
	CObject2D::m_aVerBuff->Unlock();
}

//========================================================
//描画処理
//========================================================
void CPlayer::Draw(void)
{
	CObject2D::Draw();
}

//========================================================
//ブロックとの当たり判定
//========================================================
bool CPlayer::CollisionBlock(void)
{
	bool bLand;

	bLand = true;

	return bLand;
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}