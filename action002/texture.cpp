//========================================================
//
//�E�C���h�E�̐����� (score.cpp)
//Author ���{����
//
//========================================================
#include "texture.h"
#include "manager.h"

int CTexture::m_nNumAll = -1;

//========================================================
//�R���X�g���N�^
//========================================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		m_apTexture[nCnt] = NULL;
		m_aFilename[nCnt] = {};
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

	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_nNumAll++;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		pFilename,
		&m_apTexture[m_nNumAll]);

	m_aFilename[m_nNumAll] = pFilename;

	return m_nNumAll;
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
	return m_aFilename[nIdx];
}