//========================================================
// 
// �e�̏��� (shadow.h)
// Author ���{����
// 
//========================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"
#include "object3D.h"

//===================================
// �t�B�[���h�̃N���X
//===================================
class CShadow : public CObject3D
{
public:
	CShadow(int nPriority = 8);										// �R���X�g���N�^
	CShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority = 8);	// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CShadow();									// �f�X�g���N�^

	HRESULT Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	static CShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// ��������
	D3DXVECTOR3 GetPos() { return m_pos; }							// �ʒu��Ԃ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }					// �ʒu��ݒ�
	D3DXVECTOR3 GetRot() { return m_rot; }							// �ʒu��Ԃ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					// �ʒu��ݒ�
	LPDIRECT3DINDEXBUFFER9 GetIdxBuff() { return m_pIdxBuff; }		// �C���f�b�N�X�o�b�t�@�̃|�C���^��Ԃ�

private:
	static int m_nIdxTexture;					// �e�N�X�`���̔ԍ�
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			// �C���f�b�N�X�o�b�t�@�̃|�C���^
};

#endif