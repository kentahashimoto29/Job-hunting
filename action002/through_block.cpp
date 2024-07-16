//========================================================
// 
// �E�C���h�E�̐����� (through_block.cpp)
// Author ���{����
// 
//========================================================
#include "through_block.h"
#include "manager.h"
#include "player3D.h"
#include "game.h"

int CThroughBlock::m_nIdxTexture = 0;

//========================================================
// �R���X�g���N�^
//========================================================
CThroughBlock::CThroughBlock(int nPriority) : CObjectX(nPriority)
{

}

//========================================================
// �I�[�o�[���C�h���ꂽ�R���X�g���N�^
//========================================================
CThroughBlock::CThroughBlock(D3DXVECTOR3 pos, int nPriority) : CObjectX(nPriority)
{
	m_pos = pos;
}

//========================================================
// �f�X�g���N�^
//========================================================
CThroughBlock::~CThroughBlock()
{

}

//========================================================
// ��������
//========================================================
CThroughBlock *CThroughBlock::Create(D3DXVECTOR3 pos)
{
	CThroughBlock *pPlayer3D;

	// 2D�I�u�W�F�N�g�̐���
	pPlayer3D = new CThroughBlock(pos);

	// ����������
	pPlayer3D->Init();

	return pPlayer3D;
}

//========================================================
// ����������
//========================================================
HRESULT CThroughBlock::Init(void)
{
	int nNumVtx;				// ���_��
	DWORD dwSizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^

								// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\through_box000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	// ���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());


	// ���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;					// ���_���W�̑��

		if (m_VtxMin.x > vtx.x)
		{
			m_VtxMin.x = vtx.x;
		}

		else if (m_VtxMax.x < vtx.x)
		{
			m_VtxMax.x = vtx.x;
		}

		if (m_VtxMin.y > vtx.y)
		{
			m_VtxMin.y = vtx.y;
		}

		else if (m_VtxMax.y < vtx.y)
		{
			m_VtxMax.y = vtx.y;
		}

		if (m_VtxMin.z > vtx.z)
		{
			m_VtxMin.z = vtx.z;
		}

		else if (m_VtxMax.z < vtx.z)
		{
			m_VtxMax.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;					// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	CObject::SetType(TYPE_BLOCK_THROUGH);

	CObjectX::Init();

	return S_OK;
}

//========================================================
// �I������
//========================================================
void CThroughBlock::Uninit(void)
{
	Release();
}

//========================================================
// �X�V����
//========================================================
void CThroughBlock::Update(void)
{
	CGame::GetPlayer3D()->Collision(&m_pos, m_VtxMax, m_VtxMin, CObject::GetType());
}

//========================================================
// �`�揈��
//========================================================
void CThroughBlock::Draw(void)
{
	CObjectX::Draw();
}

//========================================================
// �ʒu��Ԃ�
//========================================================
D3DXVECTOR3 CThroughBlock::GetPos(void)
{
	return m_pos;
}