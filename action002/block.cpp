//========================================================
//
//�E�C���h�E�̐����� (block.cpp)
//Author ���{����
//
//========================================================
#include "block.h"
#include "manager.h"

int CBlock::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CBlock::CBlock()
{

}

//========================================================
//�R���X�g���N�^
//========================================================
CBlock::CBlock(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//�f�X�g���N�^
//========================================================
CBlock::~CBlock()
{

}

//========================================================
//��������
//========================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock *pBlock;

	//�u���b�N�̐���
	pBlock = new CBlock(pos);

	//����������
	pBlock->Init();

	pBlock->BindTexture(m_nIdxTexture);

	return pBlock;
}

//========================================================
//����������
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
//�I������
//========================================================
void CBlock::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//�X�V����
//========================================================
void CBlock::Update(void)
{
	CObject2D::SetVtxBlock(m_pos);
}

//========================================================
//�`�揈��
//========================================================
void CBlock::Draw(void)
{
	CObject2D::Draw();
}