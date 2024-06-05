//========================================================
//
//ウインドウの生成等 (score.cpp)
//Author 橋本賢太
//
//========================================================
#include "fade.h"
#include "manager.h"

int CFade::m_nIdxTexture = 0;


//========================================================
//コンストラクタ
//========================================================
CFade::CFade()
{
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pObject2D = NULL;
	m_fade = FADE_NONE;
}

//========================================================
//デストラクタ
//========================================================
CFade::~CFade()
{

}

//========================================================
//初期化処理
//========================================================
HRESULT CFade::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\black_000.jpg" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\black_000.jpg");
	}

	m_pObject2D = new CObject2D(7);

	m_pObject2D->BindTexture(m_nIdxTexture);

	m_pObject2D->Init();

	m_pObject2D->SetVtxFade();

	m_pObject2D->SetColor(m_color);

	m_pObject2D->SetType(CObject::TYPE_FADE);

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CFade::Uninit(void)
{
	m_pObject2D->Uninit();
}

//========================================================
//更新処理
//========================================================
void CFade::Update(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (m_fade != FADE_NONE)
	{
		//フェードイン状態
		if (m_fade == FADE_IN)
		{
			//決定キー(ENTERキー)が押されました
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				CScene::MODE aMode;				//画面のモードの情報

				aMode = CManager::GetInstance()->GetScene()->GetMode();

				//タイトル画面ならフェードをスキップする
				if (aMode == CScene::MODE_TITLE)
				{
					m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				}
			}

			m_color.a -= 0.025f;

			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}

		//フェードアウト状態
		if (m_fade == FADE_OUT)
		{
			m_color.a += 0.025f;

			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;

				// 次の画面へ
				CManager::GetInstance()->SetMode(m_modenext);
				m_fade = FADE_IN;			//フェードイン状態
			}
		}

		m_pObject2D->SetColor(m_color);
	}
}

//========================================================
//描画処理
//========================================================
void CFade::Draw(void)
{
	m_pObject2D->Draw();
}

//========================================================
//位置を返す
//========================================================
void CFade::SetFade(CScene::MODE mode)
{

	if (m_fade == FADE_NONE)
	{// 何もしていないとき

	 // 次のモード設定
		m_modenext = mode;
		m_fade = FADE_OUT;	// フェードアウト状態に設定

									// 色設定
		m_pObject2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
}

//========================================================
//位置を返す
//========================================================
void CFade::SetFadeFirst(CScene::MODE mode)
{
	if (m_fade == FADE_NONE)
	{// 何もしていないとき

	 // 次のモード設定
		m_modenext = mode;
		m_fade = FADE_IN;	// フェードアウト状態に設定

							// 色設定
		m_pObject2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}


//========================================================
//戦意の状態
//========================================================
CFade::FADE CFade::GetState(void)
{
	return m_fade;
}