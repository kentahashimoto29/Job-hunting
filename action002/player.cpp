//========================================================
//
//�E�C���h�E�̐����� (player.cpp)
//Author ���{����
//
//========================================================
#include "player.h"
#include "manager.h"
#include "input.h"

int CPlayer::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CPlayer::CPlayer()
{

}

//========================================================
//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
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
//�f�X�g���N�^
//========================================================
CPlayer::~CPlayer()
{

}

//========================================================
//��������
//========================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer;

	//2D�I�u�W�F�N�g�̐���
	pPlayer = new CPlayer(pos);

	//����������
	pPlayer->Init();

	pPlayer->BindTexture(m_nIdxTexture);

	return pPlayer;
}

//========================================================
//����������
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

	//��ނ̐ݒ�
	CObject::SetType(TYPE_PLATER);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CPlayer::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================
//�X�V����
//========================================================
void CPlayer::Update(void)
{
	CInputKeyboard *pInputKeyboard;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	m_pos += m_move;
	GravityCnt++;

	

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == TRUE)
	{
		//CBullet::Create(m_pos);
	}

	m_nCntAnim++;               //�J�E���^�[�����Z����

	if ((m_nCntAnim % 30) == 0)
	{
		m_nCntAnim = 0;         //�J�E���^�[�������l�ɖ߂�
		m_nPtnAnim++;           //�p�^�[��No.�����s����

		if (m_nPtnAnim > 4)
		{
			m_nPtnAnim = 0;     //�p�^�[��No.�������l�ɖ߂�
			m_nPtnAnim2++;

			if (m_nPtnAnim2 > 1)
			{
				m_nPtnAnim2 = 0;     //�p�^�[��No.�������l�ɖ߂�
			}
		}
	}

	//�d�͐ݒ�
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

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N����
	CObject2D::m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 150.0f, m_pos.y - 200.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 150.0f, m_pos.y - 200.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 150.0f, m_pos.y + 200.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 150.0f, m_pos.y + 200.0f, 0.0f);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_nPtnAnim * 0.2f, 0.0f + m_nPtnAnim2 * 0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.2f + m_nPtnAnim * 0.2f, 0.0f + m_nPtnAnim2 * 0.5f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_nPtnAnim * 0.2f, 0.5f + m_nPtnAnim2 * 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.2f + m_nPtnAnim * 0.2f, 0.5f + m_nPtnAnim2 * 0.5f);

	//���_�o�b�t�@���A�����b�N����
	CObject2D::m_aVerBuff->Unlock();
}

//========================================================
//�`�揈��
//========================================================
void CPlayer::Draw(void)
{
	CObject2D::Draw();
}

//========================================================
//�u���b�N�Ƃ̓����蔻��
//========================================================
bool CPlayer::CollisionBlock(void)
{
	bool bLand;

	bLand = true;

	return bLand;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}