//========================================================
// 
// �E�C���h�E�̐����� (light.cpp)
// Author ���{����
// 
//========================================================
#include "light.h"
#include "manager.h"

#define LIGHT_MAX	(4)

//========================================================
// �R���X�g���N�^
//========================================================
CLight::CLight()
{

}

//========================================================
// �f�X�g���N�^
//========================================================
CLight::~CLight()
{

}

//========================================================
// ���C�g�̏�����
//========================================================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;              // �ݒ�p�����x�N�g��

	// ���C�g�̏����N���A����
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	for (int nCnt = 0; nCnt < LIGHT_MAX; nCnt++)
	{
		m_Light[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		m_Light[nCnt].Diffuse = D3DXCOLOR(0.36f, 0.32f, 0.37f, 1.0f);
	}

	// ���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.0f, -0.2f, 0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             // �x�N�g���𐳋K������
	m_Light[0].Direction = vecDir;

	// ���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(-0.1f, -0.2f, -0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             // �x�N�g���𐳋K������hj
	m_Light[1].Direction = vecDir;

	// ���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.1f, -0.2f, -0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             // �x�N�g���𐳋K������
	m_Light[2].Direction = vecDir;

	// ���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.1f, 0.2f, 0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             // �x�N�g���𐳋K������
	m_Light[3].Direction = vecDir;

	for (int nCnt = 0; nCnt < LIGHT_MAX; nCnt++)
	{
		// ���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_Light[nCnt]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//========================================================
// ���C�g�̏I��
//========================================================
void CLight::Uninit(void)
{

}

//========================================================
// ���C�g�̍X�V
//========================================================
void CLight::Update(void)
{

}