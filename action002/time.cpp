//========================================================
// 
// ウインドウの生成等 (time.cpp)
// Author 橋本賢太
// 
//========================================================
#include "time.h"
#include "manager.h"

int CTime::m_nIdxTexture = 0;

//========================================================
// コンストラクタ
//========================================================
CTime::CTime(int nPriority) : CObject(nPriority)
{
	m_nTime = 30;
	m_nInitTime = m_nTime;
}

//========================================================
// デストラクタ
//========================================================
CTime::~CTime()
{

}

//========================================================
// 生成処理
//========================================================
CTime *CTime::Create()
{
	CTime *pTime;

	// 2Dオブジェクトの生成
	pTime = new CTime();

	// 初期化処理
	pTime->Init();

	return pTime;
}

//========================================================
// 初期化処理
//========================================================
HRESULT CTime::Init(void)
{
	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = new CObject2D();

		m_apObject2D[nCnt]->Init();

		m_apObject2D[nCnt]->SetPos(D3DXVECTOR3(520.0f, 70.0f, 0.0f));

		m_apObject2D[nCnt]->SetSizeX(40.0f);
		m_apObject2D[nCnt]->SetSizeY(50.0f);

		m_nIdxTexture = m_apObject2D[nCnt]->SetTex("data\\TEXTURE\\number_blackclover_07.png");

		m_apObject2D[nCnt]->BindTexture(m_nIdxTexture);
	}

	SetType(CObject::TYPE_TIME);

	SetTime(m_nTime);

	return S_OK;
}

//========================================================
// 終了処理
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
// 更新処理
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
// 描画処理
//========================================================
void CTime::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}
}

//========================================================
// 設定処理
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
// 設定処理
//========================================================
int CTime::GetTime(void)
{
	return m_nTime;
}

//========================================================
// 設定処理
//========================================================
int CTime::GetInitTime(void)
{
	return m_nInitTime;
}

//========================================================
// 位置を返す
//========================================================
D3DXVECTOR3 CTime::GetPos(void)
{
	return m_pos;
}


//========================================================
// 位置を返す
//========================================================
void CTime::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//========================================================
// 位置を返す
//========================================================
void CTime::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}