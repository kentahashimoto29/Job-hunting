//========================================================
//
//�E�C���h�E�̐����� (model.h)
//Author ���{����
//
//========================================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"

//===================================
//���f���̃N���X
//===================================
class CModel
{
public:
	CModel();						//�R���X�g���N�^
	CModel(D3DXVECTOR3 pos);		//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CModel();						//�f�X�g���N�^

	static CModel *Create(const char *pFilename, D3DXVECTOR3 pos);		//��������
	void SetParent(CModel *pModel);										//�e���f���̐ݒ�
	D3DXVECTOR3 GetPos(void);											//�ʒu��Ԃ�
	D3DXVECTOR3 GetRot(void);											//������Ԃ�
	D3DXMATRIX GetMtxWorld(void);										//�}�g���b�N�X��Ԃ�

	void SetPos(D3DXVECTOR3 pos);										//�ʒu��ݒ�
	void SetRot(D3DXVECTOR3 rot);										//������ݒ�

	HRESULT Init(const char *pFilename);								//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��

private:
	int m_IdxTexture[64];				//�e�N�X�`���̔ԍ�

	LPD3DXMESH m_pMesh;				//���b�V���ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;				//�}�e���A���̐�

	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_rot;				//����
	D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X
	CModel *m_pModel;				//�e���f���ւ̃|�C���^
};
#endif