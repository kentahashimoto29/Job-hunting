//========================================================
//
//�E�C���h�E�̐����� (camera.h)
//Author ���{����
//
//========================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "game.h"
#include "title.h"

//========================================================
//�R���X�g���N�^
//========================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�Ίp���̒������Z�o
	m_Distance = sqrtf(0.0f * 0.0f + 0.0f * 0.0f);

	//�Ίp���̊p�x���Z�o
	m_Angle = atan2f(0.0f, 0.0f);

	m_type = TYPE_NONE;

	x = 0.0f;
	y = 0.0f;
}

//========================================================
//�f�X�g���N�^
//========================================================
CCamera::~CCamera()
{

}

//========================================================
//�J�����̏�����
//========================================================
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�Ίp���̒������Z�o
	m_Distance = sqrtf(0.0f * 0.0f + 0.0f * 0.0f);

	//�Ίp���̊p�x���Z�o
	m_Angle = atan2f(0.0f, 0.0f);

	return S_OK;
}

//========================================================
//�J�����̏I��
//========================================================
void CCamera::Uninit(void)
{

}

//========================================================
//�J�����̍X�V
//========================================================
void CCamera::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�}�E�X�̎擾
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	//�v���C���[3D�̎擾
	CPlayer3D *pPlayer3D = CGame::GetPlayer3D();

	switch (CManager::GetInstance()->GetScene()->GetMode())
	{
	case CScene::MODE_GAME:

		/*m_posR.x += pPlayer3D->GetMove().x;
		m_posV.x += pPlayer3D->GetMove().x;*/
		if (pInputMouse->GetPress(pInputMouse->TYPE_LEFT) == true)
		{
			x += pInputMouse->GetMouseMove().x / 300;
			y += pInputMouse->GetMouseMove().y / 300;

			if (x > D3DX_PI)
			{
				x = -D3DX_PI;
			}

			else if (x < -D3DX_PI)
			{
				x = D3DX_PI;
			}

			if (y > D3DX_PI / 2)
			{
				y = D3DX_PI / 2;
			}

			else if (y < -D3DX_PI / 2)
			{
				y = -D3DX_PI / 2;
			}

			float xy = 0.0f;

			m_rot.y = x;

			float f = sinf(m_rot.y + D3DX_PI) * m_Distance;
			float ff = cosf(m_rot.y + D3DX_PI + m_rot.x) * m_Distance;

			m_posV.x = m_posR.x + sinf(m_rot.y + D3DX_PI) * m_Distance;
			m_posV.z = m_posR.z + cosf(m_rot.y + D3DX_PI) * m_Distance;
		}

		m_posR.x += pPlayer3D->GetMove().x;
		m_posR.z += pPlayer3D->GetMove().z;
		m_posV.x += pPlayer3D->GetMove().x;
		m_posV.z += pPlayer3D->GetMove().z;

		break;
	}

	

	//�J�����̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}

	else if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}
}

//========================================================
//�J�����̐ݒ�
//========================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//========================================================
//�J�����̈ʒu
//========================================================
void CCamera::SetPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_posV = posV;
	m_posR = posR;
}

//========================================================
//�J�����̈ʒu
//========================================================
void CCamera::SetPosGame(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_posV = D3DXVECTOR3(posV.x, posV.y + 90.0f, posV.z - 200.0f);
	m_posR = D3DXVECTOR3(posR.x, posR.y + 40.0f, posR.z);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�Ίp���̒������Z�o
	//m_Distance = sqrtf(m_posV.y * m_posV.y + m_posV.z * m_posV.z);

	m_Distance = -m_posV.z;

	//�Ίp���̊p�x���Z�o
	m_Angle = atan2f(m_posV.y, -(m_posV.z - m_posR.z));

	m_rot.x = m_Angle;

	x = 0.0f;
	y = 0.0f;

	y = m_rot.x;
}

//========================================================
//�J�����̈ʒu
//========================================================
void CCamera::SetPosTitle()
{


	m_posV = D3DXVECTOR3(2000.0f, 500.0f, 2000.0f);
	m_posR = D3DXVECTOR3((1600.0f / 2) - 50.0f, 0.0f, (1600.0f / 2) - 50.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�Ίp���̒������Z�o
	//m_Distance = sqrtf(m_posV.y * m_posV.y + m_posV.z * m_posV.z);

	m_Distance = -m_posV.z;

	//�Ίp���̊p�x���Z�o
	m_Angle = atan2f(m_posV.y, -(m_posV.z - m_posR.z));

	m_rot.x = m_Angle;

	y = m_rot.x;
}

//========================================================
//�J�����̐ݒ�
//========================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}