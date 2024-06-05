//========================================================
//
//ウインドウの生成等 (score.cpp)
//Author 橋本賢太
//
//========================================================
#include "time.h"
#include "manager.h"

int CTime::m_nIdxTexture = 0;

//========================================================
//コンストラクタ
//========================================================
CTime::CTime(int nPriority) : CObject(nPriority)
{
	m_nTime = 100;
	m_nInitTime = m_nTime;
}

//========================================================
//デストラクタ
//========================================================
CTime::~CTime()
{

}

//========================================================
//生成処理
//========================================================
CTime *CTime::Create()
{
	CTime *pTime;

	//2Dオブジェクトの生成
	pTime = new CTime();

	//初期化処理
	pTime->Init();

	return pTime;
}

//========================================================
//初期化処理
//========================================================
HRESULT CTime::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if ("data\\TEXTURE\\number000.png" == pTexture->GetName(nCnt))
		{
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\number000.png");
	}

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = new CObject2D();

		m_apObject2D[nCnt]->Init();

		m_apObject2D[nCnt]->BindTexture(m_nIdxTexture);
	}

	SetType(CObject::TYPE_TIME);

	SetTime(m_nTime);

	return S_OK;
}

//========================================================
//終了処理
//========================================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Uninit();
	}

	Release();
}

//========================================================
//更新処理
//========================================================
void CTime::Update(void)
{

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		SetTime(m_nTime);
	}

	m_nSecondCount++;

	if (m_nSecondCount >= 60)
	{
		m_nSecondCount = 0;

		m_nTime--;

		if (m_nTime <= 0)
		{
			m_nTime = 0;
		}
	}
}

//========================================================
//描画処理
//========================================================
void CTime::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//========================================================
//設定処理
//========================================================
void CTime::SetTime(int nTime)
{
	m_aTexU[0] = nTime % 1000 / 100;
	m_aTexU[1] = nTime % 100 / 10;
	m_aTexU[2] = nTime % 10;

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->SetVtxTime(m_aTexU[nCnt], nCnt);
	}
}

//========================================================
//設定処理
//========================================================
int CTime::GetTime(void)
{
	return m_nTime;
}

//========================================================
//設定処理
//========================================================
int CTime::GetInitTime(void)
{
	return m_nInitTime;
}

//========================================================
//位置を返す
//========================================================
D3DXVECTOR3 CTime::GetPos(void)
{
	return m_pos;
}


//========================================================
//位置を返す
//========================================================
void CTime::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//========================================================
//位置を返す
//========================================================
void CTime::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}