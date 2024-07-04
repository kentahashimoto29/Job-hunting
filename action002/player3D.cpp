//========================================================
//
//�E�C���h�E�̐����� (player3D.cpp)
//Author ���{����
//
//========================================================
#include "player3D.h"
#include "manager.h"
#include "input.h"
#include "bullet3D.h"
#include "sound.h"
#include "goal.h"
#include "ranking.h"
#include "game.h"
#include "skill_UI.h"
#include "object2D.h"

#define DASH_DATA								(12.0f)		//�_�b�V�����̑��x
#define DASH_COUNT								(20)		//�_�b�V���̌��ʎ���
#define JUMP_DATA								(7.0f)		//�W�����v�̗�
#define GRAVITY_DATA							(0.24f)		//�d��
#define GRAVITY_MAX								(10.0f)		//�I�[���x
#define WALLRUBBING_MAX							(1.5f)		//�ǎC�莞�̍ő呬�x
#define WALK_DATA								(5.0f)		//
#define AIR_WALK_DATA							(1.0f)		//
#define WALK_MAX								(5.5f)		//

int CPlayer3D::m_nIdxTexture = 0;

//========================================================
//�R���X�g���N�^
//========================================================
CPlayer3D::CPlayer3D(int nPriority) : CObject(nPriority)
{

}

//========================================================
//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
//========================================================
CPlayer3D::CPlayer3D(D3DXVECTOR3 pos, int nPriority) : CObject(nPriority)
{
	m_pos = pos;
	m_revivalpos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f / 2, 0.0f);
	m_revivalrot = m_rot;
	m_Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumModel = 0;
	m_VtxMax = D3DXVECTOR3(20.0f, 60.0f, 20.0f);
	m_VtxMin = D3DXVECTOR3(-20.0f, 0.0f, -20.0f);
	m_nSkill = TYPE_NONE;
	m_nSkillTime = 0;
	m_nSkillCoolTime = 0;
	m_nCnt = 0;
	m_bJump = false;
	m_bGoal = false;
	m_bWalk = false;
}

//========================================================
//�f�X�g���N�^
//========================================================
CPlayer3D::~CPlayer3D()
{

}

//========================================================
//��������
//========================================================
CPlayer3D *CPlayer3D::Create(D3DXVECTOR3 pos)
{
	CPlayer3D *pPlayer3D;

	//2D�I�u�W�F�N�g�̐���
	pPlayer3D = new CPlayer3D(pos);

	//����������
	pPlayer3D->Init();

	return pPlayer3D;
}

//========================================================
//����������
//========================================================
HRESULT CPlayer3D::Init(void)
{
	//���f���̐���
	m_apModel[0] = CModel::Create("data\\MODEL\\Body.x", D3DXVECTOR3(0.0f, 24.7f, 0.0f));					//��
	m_apModel[1] = CModel::Create("data\\MODEL\\Neck.x", D3DXVECTOR3(0.0f, 22.0f, 0.0f));					//��
	m_apModel[2] = CModel::Create("data\\MODEL\\Head.x", D3DXVECTOR3(0.0f, 3.0f, 0.0f));					//��
	m_apModel[3] = CModel::Create("data\\MODEL\\Up_Left_arm.x", D3DXVECTOR3(7.0f, 20.0f, 0.0f));			//����r
	m_apModel[4] = CModel::Create("data\\MODEL\\Under_Left_arm.x", D3DXVECTOR3(10.0f, 0.0f, 0.0f));			//���O�r
	m_apModel[5] = CModel::Create("data\\MODEL\\Left_Hand.x", D3DXVECTOR3(10.0f, 0.0f, 0.0f));				//����
	m_apModel[6] = CModel::Create("data\\MODEL\\Up_Right_arm.x", D3DXVECTOR3(-7.0f, 20.0f, 0.0f));			//�E��r
	m_apModel[7] = CModel::Create("data\\MODEL\\Under_Right_arm.x", D3DXVECTOR3(-10.0f, 0.0f, 0.0f));		//�E�O�r
	m_apModel[8] = CModel::Create("data\\MODEL\\Right_Hand.x", D3DXVECTOR3(-10.0f, 0.0f, 0.0f));			//�E��
	m_apModel[9] = CModel::Create("data\\MODEL\\Up_Left_Leg.x", D3DXVECTOR3(4.5f, 0.0f, 0.0f));				//����
	m_apModel[10] = CModel::Create("data\\MODEL\\Under_Left_Leg.x", D3DXVECTOR3(0.0f, -11.0f, 0.0f));		//����
	m_apModel[11] = CModel::Create("data\\MODEL\\Left_Shose.x", D3DXVECTOR3(0.0f, -11.0f, 0.0f));			//����
	m_apModel[12] = CModel::Create("data\\MODEL\\Up_Right_Leg.x", D3DXVECTOR3(-4.5f, 0.0f, 0.0f));			//�E��
	m_apModel[13] = CModel::Create("data\\MODEL\\Under_Right_Leg.x", D3DXVECTOR3(0.0f, -11.0f, 0.0f));		//�E��
	m_apModel[14] = CModel::Create("data\\MODEL\\Right_Shose.x", D3DXVECTOR3(0.0f, -11.0f, 0.0f));			//�E��

	//�e���f���̐ݒ�
	m_apModel[0]->SetParent(NULL);
	m_apModel[1]->SetParent(m_apModel[0]);
	m_apModel[2]->SetParent(m_apModel[1]);
	m_apModel[3]->SetParent(m_apModel[0]);
	m_apModel[4]->SetParent(m_apModel[3]);
	m_apModel[5]->SetParent(m_apModel[4]);
	m_apModel[6]->SetParent(m_apModel[0]);
	m_apModel[7]->SetParent(m_apModel[6]);
	m_apModel[8]->SetParent(m_apModel[7]);
	m_apModel[9]->SetParent(m_apModel[0]);
	m_apModel[10]->SetParent(m_apModel[9]);
	m_apModel[11]->SetParent(m_apModel[10]);
	m_apModel[12]->SetParent(m_apModel[0]);
	m_apModel[13]->SetParent(m_apModel[12]);
	m_apModel[14]->SetParent(m_apModel[13]);

	m_nNumModel = 15;

	m_pMotion = new CMotion;

	m_pMotion->SetModel(&m_apModel[0], m_nNumModel);

	m_pMotion->Load();

	m_pMotion->SetType(CMotion::TYPE_MOVE);

	m_pMotion->Init(m_pMotion->TYPE_STAND);

	m_nType = MOTION_NEUTRAL;

	m_nOldType = m_nType;

	CObject::SetType(TYPE_PLAYER_3D);

	return S_OK;
}

//========================================================
//�I������
//========================================================
void CPlayer3D::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt]->Uninit();
	}

	Release();
}

//========================================================
//�X�V����
//========================================================
void CPlayer3D::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�}�E�X�̎擾
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	//�J�����̎擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	//�u���b�N3D�̎擾
	CBlock3D *pBlock = CGame::GetBlock3D();

	m_Oldpos = m_pos;
	m_bWalk = true;


	//W�L�[���������Ƃ�
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		//D�L�[���������Ƃ�
		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_move.z = cosf(D3DX_PI * 0.25f + pCamera->GetRot().y) * WALK_DATA;
			m_move.x = sinf(D3DX_PI * 0.25f + pCamera->GetRot().y) * WALK_DATA;

			m_Destrot.y = D3DX_PI * -0.75f + pCamera->GetRot().y;
		}

		//A�L�[���������Ƃ�
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_move.z = cosf(D3DX_PI * -0.25f + pCamera->GetRot().y) * WALK_DATA;
			m_move.x = sinf(D3DX_PI * -0.25f + pCamera->GetRot().y) * WALK_DATA;

			m_Destrot.y = D3DX_PI * 0.75f + pCamera->GetRot().y;
		}

		else
		{
			m_move.z = cosf(D3DX_PI * 0.0f + pCamera->GetRot().y) * WALK_DATA;
			m_move.x = sinf(D3DX_PI * 0.0f + pCamera->GetRot().y) * WALK_DATA;

			m_Destrot.y = D3DX_PI * 1.0f + pCamera->GetRot().y;
		}

		if (m_bJump == false)
		{
			if (m_nType != MOTION_MOVE)
			{
				m_pMotion->Set(m_pMotion->TYPE_MOVE);
				m_nType = MOTION_MOVE;
			}
		}
	}

	//S�L�[���������Ƃ�
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		//D�L�[���������Ƃ�
		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_move.z = cosf(D3DX_PI * 0.75f + pCamera->GetRot().y) * WALK_DATA;
			m_move.x = sinf(D3DX_PI * 0.75f + pCamera->GetRot().y) * WALK_DATA;

			m_Destrot.y = D3DX_PI * -0.25f + pCamera->GetRot().y;
		}

		//A�L�[���������Ƃ�
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_move.z = cosf(D3DX_PI * -0.75f + pCamera->GetRot().y) * WALK_DATA;
			m_move.x = sinf(D3DX_PI * -0.75f + pCamera->GetRot().y) * WALK_DATA;

			m_Destrot.y = D3DX_PI * 0.25f + pCamera->GetRot().y;
		}

		else
		{
			m_move.z = cosf(D3DX_PI * 1.0f + pCamera->GetRot().y) * WALK_DATA;
			m_move.x = sinf(D3DX_PI * 1.0f + pCamera->GetRot().y) * WALK_DATA;

			m_Destrot.y = D3DX_PI * 0.0f + pCamera->GetRot().y;
		}

		if (m_bJump == false)
		{
			if (m_nType != MOTION_MOVE)
			{
				m_pMotion->Set(m_pMotion->TYPE_MOVE);
				m_nType = MOTION_MOVE;
			}
		}
	}


	//A�L�[���������Ƃ�
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{

		m_Destrot.y = D3DX_PI * 0.5f + pCamera->GetRot().y;



		//�󒆂̎�
		if (m_bJump == false)
		{
			m_move.z = cosf(D3DX_PI * -0.5f + pCamera->GetRot().y) * WALK_DATA;
			m_move.x = sinf(D3DX_PI * -0.5f + pCamera->GetRot().y) * WALK_DATA;
		}

		else
		{
			m_move.z = cosf(D3DX_PI * -0.5f + pCamera->GetRot().y) * WALK_DATA;
			m_move.x = sinf(D3DX_PI * -0.5f + pCamera->GetRot().y) * AIR_WALK_DATA;
		}

		if (m_bJump == false)
		{
			if (m_nType != MOTION_MOVE)
			{
				m_pMotion->Set(m_pMotion->TYPE_MOVE);
				m_nType = MOTION_MOVE;
			}
		}
	}

	//D�L�[���������Ƃ�
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		

			m_Destrot.y = D3DX_PI * -0.5f + pCamera->GetRot().y;


		if (m_bJump == false)
		{
			m_move.z = cosf(D3DX_PI * 0.5f + pCamera->GetRot().y) * WALK_DATA;
			m_move.x = sinf(D3DX_PI * 0.5f + pCamera->GetRot().y) * WALK_DATA;
		}

		else
		{
			m_move.z = cosf(D3DX_PI * 0.5f + pCamera->GetRot().y) * WALK_DATA;
			m_move.x = sinf(D3DX_PI * 0.5f + pCamera->GetRot().y) * AIR_WALK_DATA;
		}

		if (m_bJump == false)
		{
			if (m_nType != MOTION_MOVE)
			{
				m_pMotion->Set(m_pMotion->TYPE_MOVE);
				m_nType = MOTION_MOVE;
			}
		}
	}



	//�ړ��L�[�������Ȃ������Ƃ�
	else
	{
		m_bWalk = false;

		//�󒆂̎�
		if (m_bJump == false)
		{
			m_move.x -= m_move.x * 0.2f;
			m_move.z -= m_move.z * 0.2f;
		}

		else
		{
			m_move.x -= m_move.x * 0.02f;
			m_move.z -= m_move.z * 0.02f;
		}


		
		if (m_nType == MOTION_MOVE)
		{
			m_pMotion->Set(m_pMotion->TYPE_STAND);
			m_nType = MOTION_NEUTRAL;
		}
	}
	

	if (pInputKeyboard->GetPress(DIK_E) == true && m_nSkillCoolTime >= 300)
	{
		m_nSkill = TYPE_ACCEL;
		m_nSkillTime = 3 * 60;
		m_nSkillCoolTime = 0;

		CGame::GetSkillUI()->GetObjectGauge2D()->SetGaugeMax(180);
	}

	float i = CGame::GetSkillUI()->GetObjectGauge2D()->GetGaugeMax();

	switch (m_nSkill)
	{
	case TYPE_ACCEL:
		if (m_bWalk == true)
		{
			m_move.x += m_move.x * 1.2f;
			m_move.z += m_move.z * 1.2f;
		}

		m_nCnt++;

		i = i - (float)m_nCnt;

		CGame::GetSkillUI()->GetObjectGauge2D()->SetGauge(i);

		break;

	case TYPE_NONE:

		if (m_nSkillCoolTime < 300)
		{
			m_nSkillCoolTime++;
		}

		CGame::GetSkillUI()->GetObjectGauge2D()->SetGauge((float)m_nSkillCoolTime);

		break;

	default:
		break;
	}

	//�ʏ펞�̗������x
	m_move.y -= GRAVITY_DATA;



	//�d�͂̍ő�l����
 	if (m_move.y <= -GRAVITY_MAX)
	{
		m_move.y = -GRAVITY_MAX;
	}

	if (m_move.x >= GRAVITY_MAX * 2)
	{
		m_move.x = GRAVITY_MAX;
	}

	if (m_move.z >= GRAVITY_MAX * 2)
	{
		m_move.z = GRAVITY_MAX;
	}


	//���ړ��̍ő�l����
	//if (m_move.x <= -WALK_MAX)
	//{
	//	m_move.x = -WALK_MAX;
	//}

	//else if (m_move.x >= WALK_MAX)
	//{
	//	m_move.x = WALK_MAX;
	//}

	////�c�ړ��̍ő�l����
	//if (m_move.z <= -WALK_MAX)
	//{
	//	m_move.z = -WALK_MAX;
	//}

	//else if (m_move.z >= WALK_MAX)
	//{
	//	m_move.z = WALK_MAX;
	//}

	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		m_move.y = 0;
		m_bJump = false;
	}


	//�W�����v
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		//�ʏ�W�����v
		if (m_bJump == false)
		{
			m_bJump = true;
			m_move.y = JUMP_DATA;

			m_nType = MOTION_JUMP;
			m_pMotion->Set(m_pMotion->TYPE_JUMP);
		}
	}


	m_pos += m_move;

	m_Diffrot.y = m_Destrot.y - m_rot.y;



	//�����̕␳
	if (m_Diffrot.y > D3DX_PI)
	{
		m_Diffrot.y += -D3DX_PI * 2;
	}

	else if (m_Diffrot.y < -D3DX_PI)
	{
		m_Diffrot.y += D3DX_PI * 2;
	}

	m_rot.y += m_Diffrot.y * 0.1f;


	//���f���̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}



	//����Ƃ��̃��[�V����
	if (pInputKeyboard->GetTrigger(DIK_A) == true ||
		pInputKeyboard->GetTrigger(DIK_D) == true ||
		pInputKeyboard->GetTrigger(DIK_W) == true ||
		pInputKeyboard->GetTrigger(DIK_S) == true)
	{
		if (m_bJump == false)
		{
			//m_pMotion->Set(m_pMotion->TYPE_MOVE);
		}
	}


	if (m_nSkillTime <= m_nCnt)
	{
		m_nSkill = TYPE_NONE;
		m_nCnt = 0;
		m_nSkillTime = 0;

		CGame::GetSkillUI()->GetObjectGauge2D()->SetGaugeMax(300);
	}




	if (m_pos.x <= -50.0f + m_VtxMax.z)
	{
		m_pos.x = -50.0f + m_VtxMax.z;
		m_move.x = 0.0f;
	}

	if (m_pos.x >= CGame::GetInitPos() - m_VtxMax.z)
	{
		m_pos.x = CGame::GetInitPos() - m_VtxMax.z;
		m_move.x = 0.0f;
	}

	if (m_pos.z <= -50.0f + m_VtxMax.z)
	{
		m_pos.z = -50.0f + m_VtxMax.z;
		m_move.z = 0.0f;
	}

	if (m_pos.z >= CGame::GetInitPos() - m_VtxMax.z)
	{
		m_pos.z = CGame::GetInitPos() - m_VtxMax.z;
		m_move.z = 0.0f;
	}




	if (m_nType == MOTION_MOVE)
	{
		if (m_nOldType != MOTION_MOVE)
		{
			m_pMotion->Set(m_pMotion->TYPE_MOVE);

			m_pMotion->SetType(m_pMotion->TYPE_MOVE);
		}
	}

	if (m_nType == MOTION_NEUTRAL)
	{
		if (m_nOldType != MOTION_NEUTRAL)
		{
			m_pMotion->SetType(m_pMotion->TYPE_STAND);
		}
	}

	else if (m_nType == MOTION_JUMP)
	{
		if (m_nOldType != MOTION_JUMP)
		{
			m_pMotion->SetType(m_pMotion->TYPE_JUMP);
		}
	}

	else if (m_nType == MOTION_LANDING)
	{
		if (m_nOldType != MOTION_LANDING)
		{
			m_pMotion->SetType(m_pMotion->TYPE_LAND);
		}
	}

	m_pMotion->Updata();

	if (pInputKeyboard->GetTrigger(DIK_K) == true)
	{
		Respawn();
	}

	m_nOldType = m_nType;
}

//========================================================
//�`�揈��
//========================================================
void CPlayer3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

												//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}

//========================================================
//�}�g���b�N�X��Ԃ�
//========================================================
D3DXMATRIX CPlayer3D::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CPlayer3D::GetPos(void)
{
	return m_pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CPlayer3D::GetRot(void)
{
	return m_rot;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CPlayer3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
void CPlayer3D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CPlayer3D::GetMove(void)
{
	return m_move;
}

//========================================================
//�ʒu��Ԃ�
//========================================================
CModel *CPlayer3D::GetModel(int nIdx)
{
	return m_apModel[nIdx];
}

//=======================================
//���f���̓����蔻��
//=======================================
void CPlayer3D::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, TYPE type)
{
	//�v���C���[���u���b�N�ɂ߂荞��
	if (pPos->x + vtxMin.x < m_pos.x + m_VtxMax.x &&
		pPos->x + vtxMax.x > m_pos.x + m_VtxMin.x &&
		pPos->y + vtxMin.y < m_pos.y + m_VtxMax.y &&
		pPos->y + vtxMax.y > m_pos.y + m_VtxMin.y &&
		pPos->z + vtxMin.z < m_pos.z + m_VtxMax.z &&
		pPos->z + vtxMax.z > m_pos.z + m_VtxMin.z)
	{
		//============================
		//��
		//============================
		if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
			pPos->y + vtxMin.y >= m_Oldpos.y + m_VtxMax.y)
		{
			//������Ԃ�����
			if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				pPos->x + vtxMin.x >= m_Oldpos.x + m_VtxMax.x)
			{
			}

			//�E����Ԃ�����
			else  if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				pPos->x + vtxMax.x <= m_Oldpos.x + m_VtxMin.x)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				pPos->z + vtxMin.z >= m_Oldpos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
				pPos->z + vtxMax.z <= m_Oldpos.z + m_VtxMin.z)
			{
			}

			else
			{
				m_move.y = 0.0f;
				m_pos.y = pPos->y + vtxMin.y - m_VtxMax.y;
			}
		}

		//================================
		//��
		//================================
		if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
			pPos->y + vtxMax.y <= m_Oldpos.y + m_VtxMin.y)
		{
			//������Ԃ�����
			if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				pPos->x + vtxMin.x >= m_Oldpos.x + m_VtxMax.x)
			{
			}

			//�E����Ԃ�����
			else  if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				pPos->x + vtxMax.x <= m_Oldpos.x + m_VtxMin.x)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				pPos->z + vtxMin.z >= m_Oldpos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
				pPos->z + vtxMax.z <= m_Oldpos.z + m_VtxMin.z)
			{
			}

			else
			{
				m_bJump = false;

				m_pos.y = pPos->y + vtxMax.y;
				m_move.y = 0.0f;
			}
		}


		//============================
		//�E
		//============================
		if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
			pPos->x + vtxMax.x <= m_Oldpos.x + m_VtxMin.x)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				pPos->y + vtxMin.y >= m_Oldpos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				pPos->y + vtxMax.y <= m_Oldpos.y + m_VtxMin.y)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				pPos->z + vtxMin.z >= m_Oldpos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= pPos->z + m_VtxMin.z &&
				pPos->z + vtxMax.z <= m_Oldpos.z + m_VtxMin.z)
			{
			}

			else
			{
				m_pos.x = pPos->x + vtxMax.x + m_VtxMax.x;
				m_move.x = 0.0f;


			}
		}

		//============================
		//��
		//============================
		if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
			pPos->x + vtxMin.x >= m_Oldpos.x + m_VtxMax.x)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				pPos->y + vtxMin.y >= m_Oldpos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				pPos->y + vtxMax.y <= m_Oldpos.y + m_VtxMin.y)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= pPos->z + m_VtxMax.z &&
				pPos->z + vtxMin.z >= m_Oldpos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= pPos->z + m_VtxMin.z &&
				pPos->z + vtxMax.z <= m_Oldpos.z + m_VtxMin.z)
			{
			}

			else
			{
				m_pos.x = pPos->x + vtxMin.x + m_VtxMin.x;
				m_move.x = 0.0f;

			}
		}

		//============================
		//����
		//============================
		if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
			pPos->z + vtxMin.z >= m_Oldpos.z + m_VtxMax.z)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				pPos->y + vtxMin.y >= m_Oldpos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				pPos->y + vtxMax.y <= m_Oldpos.y + m_VtxMin.y)
			{
			}

			//�E����Ԃ�����
			else if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				pPos->x + vtxMax.x <= m_Oldpos.x + m_VtxMin.x)
			{
			}

			//������Ԃ�����
			else if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				pPos->x + vtxMin.x >= m_Oldpos.x + m_VtxMax.x)
			{
			}

			else
			{
				m_pos.z = pPos->z + vtxMin.z + m_VtxMin.z;
				m_move.z = 0.0f;
			}
		}

		//============================
		//��
		//============================
		if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
			pPos->z + vtxMax.z <= m_Oldpos.z + m_VtxMin.z)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				pPos->y + vtxMin.y >= m_Oldpos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				pPos->y + vtxMax.y <= m_Oldpos.y + m_VtxMin.y)
			{
			}

			//�E����Ԃ�����
			else if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				pPos->x + vtxMax.x <= m_Oldpos.x + m_VtxMin.x)
			{
			}

			//������Ԃ�����
			else if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				pPos->x + vtxMin.x >= m_Oldpos.x + m_VtxMax.x)
			{
			}

			else
			{
				m_pos.z = pPos->z + vtxMax.z + m_VtxMax.z;
				m_move.z = 0.0f;
			}
		}
	}
}


//=======================================
//���f���̓����蔻��
//=======================================
bool CPlayer3D::Collisionbool(D3DXVECTOR3 *pPos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, TYPE type)
{
	bool b = false;

	//�v���C���[���u���b�N�ɂ߂荞��
	if (pPos->x + vtxMin.x < m_pos.x + m_VtxMax.x &&
		pPos->x + vtxMax.x > m_pos.x + m_VtxMin.x &&
		pPos->y + vtxMin.y < m_pos.y + m_VtxMax.y &&
		pPos->y + vtxMax.y > m_pos.y + m_VtxMin.y &&
		pPos->z + vtxMin.z < m_pos.z + m_VtxMax.z &&
		pPos->z + vtxMax.z > m_pos.z + m_VtxMin.z)
	{
		//============================
		//��
		//============================
		if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
			pPos->y + vtxMin.y >= m_Oldpos.y + m_VtxMax.y)
		{
			//������Ԃ�����
			if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				pPos->x + vtxMin.x >= m_Oldpos.x + m_VtxMax.x)
			{
			}

			//�E����Ԃ�����
			else  if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				pPos->x + vtxMax.x <= m_Oldpos.x + m_VtxMin.x)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				pPos->z + vtxMin.z >= m_Oldpos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
				pPos->z + vtxMax.z <= m_Oldpos.z + m_VtxMin.z)
			{
			}

			else
			{
				m_move.y = 0.0f;
				m_pos.y = pPos->y + vtxMin.y - m_VtxMax.y;

				if (type == TYPE_BLOCK_DEATH)
				{
					b = true;
				}
			}
		}

		//================================
		//��
		//================================
		if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
			pPos->y + vtxMax.y <= m_Oldpos.y + m_VtxMin.y)
		{
			//������Ԃ�����
			if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				pPos->x + vtxMin.x >= m_Oldpos.x + m_VtxMax.x)
			{
			}

			//�E����Ԃ�����
			else  if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				pPos->x + vtxMax.x <= m_Oldpos.x + m_VtxMin.x)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				pPos->z + vtxMin.z >= m_Oldpos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
				pPos->z + vtxMax.z <= m_Oldpos.z + m_VtxMin.z)
			{
			}

			else
			{
				m_bJump = false;
				m_move.y = 0.0f;

				m_pos.y = pPos->y + vtxMax.y;

				if (type == TYPE_BLOCK_DEATH)
				{
					b = true;
				}
			}
		}

		//============================
		//�E
		//============================
		if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
			pPos->x + vtxMax.x <= m_Oldpos.x + m_VtxMin.x)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				pPos->y + vtxMin.y >= m_Oldpos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				pPos->y + vtxMax.y <= m_Oldpos.y + m_VtxMin.y)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
				pPos->z + vtxMin.z >= m_Oldpos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= pPos->z + m_VtxMin.z &&
				pPos->z + vtxMax.z <= m_Oldpos.z + m_VtxMin.z)
			{
			}

			else
			{
				m_move.x = 0.0f;
				m_pos.x = pPos->x + vtxMax.x + m_VtxMax.x;

				if (type == TYPE_BLOCK_DEATH)
				{
					b = true;
				}
			}
		}

		//============================
		//��
		//============================
		if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
			pPos->x + vtxMin.x >= m_Oldpos.x + m_VtxMax.x)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				pPos->y + vtxMin.y >= m_Oldpos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				pPos->y + vtxMax.y <= m_Oldpos.y + m_VtxMin.y)
			{
			}

			//���ʂ���Ԃ�����
			else  if (pPos->z + vtxMin.z <= pPos->z + m_VtxMax.z &&
				pPos->z + vtxMin.z >= m_Oldpos.z + m_VtxMax.z)
			{
			}

			//������Ԃ�����
			else  if (pPos->z + vtxMax.z >= pPos->z + m_VtxMin.z &&
				pPos->z + vtxMax.z <= m_Oldpos.z + m_VtxMin.z)
			{
			}

			else
			{
				m_move.x = 0.0f;
				m_pos.x = pPos->x + vtxMin.x + m_VtxMin.x;

				if (type == TYPE_BLOCK_DEATH)
				{
					b = true;
				}
			}
		}

		//============================
		//����
		//============================
		if (pPos->z + vtxMin.z <= m_pos.z + m_VtxMax.z &&
			pPos->z + vtxMin.z >= m_Oldpos.z + m_VtxMax.z)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				pPos->y + vtxMin.y >= m_Oldpos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				pPos->y + vtxMax.y <= m_Oldpos.y + m_VtxMin.y)
			{
			}

			//�E����Ԃ�����
			else if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				pPos->x + vtxMax.x <= m_Oldpos.x + m_VtxMin.x)
			{
			}

			//������Ԃ�����
			else if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				pPos->x + vtxMin.x >= m_Oldpos.x + m_VtxMax.x)
			{
			}

			else
			{
				m_move.z = 0.0f;
				m_pos.z = pPos->z + vtxMin.z + m_VtxMin.z;
			}
		}

		//============================
		//��
		//============================
		if (pPos->z + vtxMax.z >= m_pos.z + m_VtxMin.z &&
			pPos->z + vtxMax.z <= m_Oldpos.z + m_VtxMin.z)
		{
			//������Ԃ�����
			if (pPos->y + vtxMin.y <= m_pos.y + m_VtxMax.y &&
				pPos->y + vtxMin.y >= m_Oldpos.y + m_VtxMax.y)
			{
			}

			//�ォ��Ԃ�����
			else if (pPos->y + vtxMax.y >= m_pos.y + m_VtxMin.y &&
				pPos->y + vtxMax.y <= m_Oldpos.y + m_VtxMin.y)
			{
			}

			//�E����Ԃ�����
			else if (pPos->x + vtxMax.x >= m_pos.x + m_VtxMin.x &&
				pPos->x + vtxMax.x <= m_Oldpos.x + m_VtxMin.x)
			{
			}

			//������Ԃ�����
			else if (pPos->x + vtxMin.x <= m_pos.x + m_VtxMax.x &&
				pPos->x + vtxMin.x >= m_Oldpos.x + m_VtxMax.x)
			{
			}

			else
			{
				m_move.z = 0.0f;
				m_pos.z = pPos->z + vtxMax.z + m_VtxMax.z;
			}
		}
	}


	return b;
}


//========================================================
//�G�ƃv���C���[�Ƃ̓����蔻��
//========================================================
bool CPlayer3D::CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	for (int nCntPriority = 0; nCntPriority < 8; nCntPriority++)
	{
		CObject *pObject = GetTop(nCntPriority);

		TYPE type;

		while (pObject != NULL)
		{
			CObject *pObjectNext = pObject->GetNext();

			//��ނ��擾
			type = pObject->GetType();

			if (type == TYPE_ENEMY)
			{
				if (pos.x + vtxMin.x < m_pos.x + m_VtxMax.x
					&& pos.x + vtxMax.x > m_pos.x + m_VtxMin.x
					&& pos.z + vtxMin.z < m_pos.z + m_VtxMax.z
					&& pos.z + vtxMax.z > m_pos.z + m_VtxMin.z)
				{
					return true;
				}
			}

			pObject = pObjectNext;
		}
	}

	return false;
}

//=======================================
//���X�|�[������
//=======================================
void CPlayer3D::Respawn(void)
{
	m_pos = m_revivalpos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = m_revivalrot;
	m_Destrot = m_revivalrot;
	m_Diffrot = m_revivalrot;
}