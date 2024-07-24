//========================================================
// 
// �E�C���h�E�̐����� (camera.h)
// Author ���{����
// 
//========================================================
#include "minimap_camera.h"
#include "manager.h"
#include "input.h"
#include "game.h"

//========================================================
// �R���X�g���N�^
//========================================================
CMinimap_Camera::CMinimap_Camera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_viewport.Width = 180;
	m_viewport.Height = 180;
	m_viewport.X = 80;
	m_viewport.Y = 30;
	m_viewport.MaxZ = 0.1f;
	m_viewport.MinZ = 0.0f;

	// �Ίp���̒������Z�o
	m_Distance = sqrtf(0.0f * 0.0f + 0.0f * 0.0f);

	// �Ίp���̊p�x���Z�o
	m_Angle = atan2f(0.0f, 0.0f);

	m_type = TYPE_NONE;
}

//========================================================
// �f�X�g���N�^
//========================================================
CMinimap_Camera::~CMinimap_Camera()
{

}

//========================================================
// �J�����̏�����
//========================================================
HRESULT CMinimap_Camera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �Ίp���̒������Z�o
	m_Distance = sqrtf(0.0f * 0.0f + 0.0f * 0.0f);

	// �Ίp���̊p�x���Z�o
	m_Angle = atan2f(0.0f, 0.0f);

	return S_OK;
}

//========================================================
// �J�����̏I��
//========================================================
void CMinimap_Camera::Uninit(void)
{

}

//========================================================
// �J�����̍X�V
//========================================================
void CMinimap_Camera::Update(void)
{

}

//========================================================
// �J�����̐ݒ�
//========================================================
void CMinimap_Camera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 
	pDevice->SetViewport(&m_viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)m_viewport.Width / (float)m_viewport.Height,
		10.0f,
		5000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//========================================================
// �J�����̈ʒu
//========================================================
void CMinimap_Camera::SetPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_posV = posV;
	m_posR = posR;

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//========================================================
// �J�����̈ʒu
//========================================================
void CMinimap_Camera::SetPosGame(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_posV = D3DXVECTOR3(posV.x, posV.y + 90.0f, posV.z - 200.0f);
	m_posR = D3DXVECTOR3(posR.x, posR.y + 40.0f, posR.z);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �Ίp���̒������Z�o
	// m_Distance = sqrtf(m_posV.y * m_posV.y + m_posV.z * m_posV.z);

	m_Distance = -m_posV.z;

	// �Ίp���̊p�x���Z�o
	m_Angle = atan2f(m_posV.y, -(m_posV.z - m_posR.z));

	m_rot.x = m_Angle;
}

//========================================================
// �J�����̐ݒ�
//========================================================
D3DXVECTOR3 CMinimap_Camera::GetRot(void)
{
	return m_rot;
}