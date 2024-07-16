//========================================================
// 
// �E�C���h�E�̐����� (object2D.cpp)
// Author ���{����
// 
//========================================================
#include "object2D.h"
#include "manager.h"
#include "player.h"
#include "block.h"

#define RANKING_INTERVAL_Y		(100.0f)
#define RANKING_INTERVAL_X		(160.0f)
#define RANKINGSCORE_INTERVAL_X	(60.0f)
#define RANKING_WIDTH			(80.0f)
#define RANKING_HEIGHT			(100.0f)
#define TIME_INTERVAL			(1.5f)
#define SCORE_INTERVAL			(1.5f)

//========================================================
// �R���X�g���N�^
//========================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_nTexture = 0;
	m_aVerBuff = NULL;
}

//========================================================
// �R���X�g���N�^
//========================================================
CObject2D::CObject2D(D3DXVECTOR3 Pos, int nPriority) : CObject(nPriority)
{
	m_nTexture = 0;
	m_aVerBuff = NULL;
	m_pos = Pos;
}

//========================================================
// �f�X�g���N�^
//========================================================
CObject2D::~CObject2D()
{

}

//========================================================
// ����������
//========================================================
HRESULT CObject2D::Init(void)
{
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_aVerBuff,
		NULL);

	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();

	return S_OK;
}

//========================================================
// �I������
//========================================================
void CObject2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_aVerBuff != NULL)
	{
		m_aVerBuff->Release();
		m_aVerBuff = NULL;
	}

	Release();
}

//========================================================
// �X�V����
//========================================================
void CObject2D::Update(void)
{

}

//========================================================
// �`�揈��
//========================================================
void CObject2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, m_aVerBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	if (m_nTexture != -1)
	{
		pDevice->SetTexture(0, CManager::GetInstance()->GetTexture()->GetAddress(m_nTexture));
	}

	else
	{
		pDevice->SetTexture(0, NULL);
	}


	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// �`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,				// �v���~�e�B�u�̎��
		0,									// �ŏ��̒��_�C���f�b�N�X
		2);									// �v���~�e�B�u��

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//========================================================
// �e�N�X�`���̔ԍ������蓖�Ă�
//========================================================
void CObject2D::BindTexture(int nTexture)
{
	m_nTexture = nTexture;
}

//========================================================
// ���_���W��ݒ�
//========================================================
void CObject2D::SetVtx(D3DXVECTOR3 pos, float sizeX, float sizeY)
{
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

								// ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - sizeX, pos.y - sizeY, pos.z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + sizeX, pos.y - sizeY, pos.z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - sizeX, pos.y + sizeY, pos.z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + sizeX, pos.y + sizeY, pos.z);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �w�i�̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxBG(float aTexV)
{
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, aTexV);
	pVtx[1].tex = D3DXVECTOR2(1.0f, aTexV);
	pVtx[2].tex = D3DXVECTOR2(0.0f, aTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, aTexV + 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �X�R�A�̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxScore(int aTexU, int nCnt)
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(nCnt * (m_sizeX * SCORE_INTERVAL) + m_pos.x - m_sizeX, m_pos.y - m_sizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(nCnt * (m_sizeX * SCORE_INTERVAL) + m_pos.x + m_sizeX, m_pos.y - m_sizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(nCnt * (m_sizeX * SCORE_INTERVAL) + m_pos.x - m_sizeX, m_pos.y + m_sizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(nCnt * (m_sizeX * SCORE_INTERVAL) + m_pos.x + m_sizeX, m_pos.y + m_sizeY, 0.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(aTexU * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aTexU * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �u���b�N�̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxBlock(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + BLOCK_WIDTH, pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + BLOCK_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + BLOCK_WIDTH, pos.y + BLOCK_HEIGHT, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �^�C�g���̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxTitleStart()
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

							 // ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-140.0f + m_pos.x, -40.0f + m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(140.0f + m_pos.x, -40.0f + m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-140.0f + m_pos.x, 40.0f + m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(140.0f + m_pos.x, 40.0f + m_pos.y, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �^�C�g���̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxTitle()
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

							 // ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 400.0f, m_pos.y - 80.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 400.0f, m_pos.y - 80.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 400.0f, m_pos.y + 80.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 400.0f, m_pos.y + 80.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// ���U���g�̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxResult()
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

							 // ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �^�C���̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxTime(int aTexU, int nCnt)
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

							 // ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(nCnt * (m_sizeX * TIME_INTERVAL) + m_pos.x - m_sizeX, m_pos.y - m_sizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(nCnt * (m_sizeX * TIME_INTERVAL) + m_pos.x + m_sizeX, m_pos.y - m_sizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(nCnt * (m_sizeX * TIME_INTERVAL) + m_pos.x - m_sizeX, m_pos.y + m_sizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(nCnt * (m_sizeX * TIME_INTERVAL) + m_pos.x + m_sizeX, m_pos.y + m_sizeY, 0.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(aTexU * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aTexU * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �����L���O�̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxRankingScore(int aTexU, int nCnt, int nCnt2)
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

							 // ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(nCnt * RANKINGSCORE_INTERVAL_X + m_pos.x, nCnt2 * RANKING_INTERVAL_Y + m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(nCnt * RANKINGSCORE_INTERVAL_X + m_pos.x + RANKING_WIDTH, nCnt2 * RANKING_INTERVAL_Y + m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(nCnt * RANKINGSCORE_INTERVAL_X + m_pos.x, nCnt2 * RANKING_INTERVAL_Y + m_pos.y + RANKING_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(nCnt * RANKINGSCORE_INTERVAL_X + m_pos.x + RANKING_WIDTH, nCnt2 * RANKING_INTERVAL_Y + m_pos.y + RANKING_HEIGHT, 0.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(aTexU * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aTexU * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �����L���O�̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxRanking(int aTexU, int nCnt)
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

							 // ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - RANKING_INTERVAL_X, nCnt * RANKING_INTERVAL_Y + m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - RANKING_INTERVAL_X + RANKING_WIDTH, nCnt * RANKING_INTERVAL_Y + m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - RANKING_INTERVAL_X, nCnt * RANKING_INTERVAL_Y + m_pos.y + RANKING_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - RANKING_INTERVAL_X + RANKING_WIDTH, nCnt * RANKING_INTERVAL_Y + m_pos.y + RANKING_HEIGHT, 0.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(aTexU * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aTexU * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(aTexU * 0.1f + 0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �X�L��UI�̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxSkillUI(void)
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

							 // ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 80.0f, m_pos.y - 80.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 80.0f, m_pos.y, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �Q�[�WUI�̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxGaugeUI(void)
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

							 // ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - 100.0f * (m_nGauge / m_nGaugeMax), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 40.0f,  m_pos.y - 100.0f * (m_nGauge / m_nGaugeMax), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 40.0f, m_pos.y, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �u���b�N�̒��_���W��ݒ�
//========================================================
void CObject2D::SetVtxFade()
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

							 // ���_�o�b�t�@�����b�N����
	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//==========================================================================
// �F�ݒ�
//==========================================================================
void CObject2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;         // ���_���ւ̃|�C���^

	m_aVerBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// ���_�o�b�t�@���A�����b�N����
	m_aVerBuff->Unlock();
}

//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CObject2D::GetPos(void)
{
	return m_pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================================================
// �ʒu��Ԃ�
//========================================================
int CObject2D::SetTex(const char TexName[64])
{
	if (TexName == NULL)
	{
		return -1;
	}

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	int nIdxTexture = 0;
	bool bTexture = false;

	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if (TexName == pTexture->GetName(nCnt))
		{
			nIdxTexture = nCnt;
			bTexture = true;
			break;
		}
	}

	if (bTexture == false)
	{
		nIdxTexture = pTexture->Regist(TexName);
	}

	return nIdxTexture;
}

//========================================================
// �A���t�@�e�X�g��L���ɂ���
//========================================================
void CObject2D::AlphaTestValid()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	CManager::GetInstance()->GetRenderer()->SetDevice(pDevice);
}

//========================================================
// �A���t�@�e�X�g�𖳌��ɂ���
//========================================================
void CObject2D::AlphaTestInvalid()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	CManager::GetInstance()->GetRenderer()->SetDevice(pDevice);
}

//========================================================
// ���u�����f�B���O�����Z�����ɐݒ�
//========================================================
void CObject2D::AlphaBlendValid()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

//========================================================
// ���u�����f�B���O�����Z�����ɐݒ�
//========================================================
void CObject2D::AlphaBlendInvalid()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
