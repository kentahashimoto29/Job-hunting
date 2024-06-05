//========================================================
//
//ウインドウの生成等 (score.cpp)
//Author 橋本賢太
//
//========================================================
#include "texture.h"
#include "manager.h"

int CTexture::m_nNumAll = -1;

//========================================================
//コンストラクタ
//========================================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		CTexture::m_apTexture[nCnt] = NULL;
	}
}

//========================================================
//デストラクタ
//========================================================
CTexture::~CTexture()
{

}

//========================================================
//テクスチャの読み込み
//========================================================
HRESULT CTexture::Load(void)
{
	return S_OK;
}

//========================================================
//テクスチャの破棄
//========================================================
void CTexture::Unload(void)
{
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//========================================================
//指定テクスチャの読み込み
//========================================================
int CTexture::Regist(const char *pFilename)
{
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_nNumAll++;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		pFilename,
		&m_apTexture[m_nNumAll]);

	m_aFilename[m_nNumAll] = pFilename;

	return m_nNumAll;
}

//========================================================
//指定のテクスチャを返す
//========================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_apTexture[nIdx];
}

//========================================================
//指定のテクスチャの名前を返す
//========================================================
const char *CTexture::GetName(int nIdx)
{
	return m_aFilename[nIdx];
}