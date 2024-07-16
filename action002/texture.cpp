//========================================================
//
//�E�C���h�E�̐����� (score.cpp)
//Author ���{����
//
//========================================================
#include "texture.h"
#include "manager.h"

int CTexture::m_nNumAll = 0;
char CTexture::m_aFilename[TEXTURE_MAX][64] = {};

//========================================================
//�R���X�g���N�^
//========================================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		m_apTexture[nCnt] = NULL;
	}
}

//========================================================
//�f�X�g���N�^
//========================================================
CTexture::~CTexture()
{

}

//========================================================
//�e�N�X�`���̓ǂݍ���
//========================================================
HRESULT CTexture::Load(void)
{
	return S_OK;
}

//========================================================
//�e�N�X�`���̔j��
//========================================================
void CTexture::Unload(void)
{
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//========================================================
//�w��e�N�X�`���̓ǂݍ���
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

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		pFilename,
		&m_apTexture[m_nNumAll]);

	strcpy(&m_aFilename[m_nNumAll][0], pFilename);

	m_nNumAll++;

	return m_nNumAll - 1;
}

//========================================================
//�w��̃e�N�X�`����Ԃ�
//========================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_apTexture[nIdx];
}

//========================================================
//�w��̃e�N�X�`���̖��O��Ԃ�
//========================================================
const char *CTexture::GetName(int nIdx)
{
	return &m_aFilename[nIdx][0];
}