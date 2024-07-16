//========================================================
//
//ウインドウの生成等 (score.cpp)
//Author 橋本賢太
//
//========================================================
#include "texture.h"
#include "manager.h"

int CTexture::m_nNumAll = 0;
char CTexture::m_aFilename[TEXTURE_MAX][64] = {};

//========================================================
//コンストラクタ
//========================================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		m_apTexture[nCnt] = NULL;
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
	if (pFilename == NULL)
	{
		return -1;
	}

	for (int nCntTex = 0; nCntTex < m_nNumAll; nCntTex++)
	{
		if (strcmp(&m_aFilename[nCntTex][0], pFilename) == 0)
		{
			return nCntTex;
		}
	}

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		pFilename,
		&m_apTexture[m_nNumAll]);

	strcpy(&m_aFilename[m_nNumAll][0], pFilename);

	m_nNumAll++;

	return m_nNumAll - 1;
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
	return &m_aFilename[nIdx][0];
}