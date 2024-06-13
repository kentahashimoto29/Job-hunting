//========================================================
//
//�E�C���h�E�̐����� (motion.cpp)
//Author ���{����
//
//========================================================
#include "motion.h"
#include "manager.h"

//========================================================
//�R���X�g���N�^
//========================================================
CMotion::CMotion()
{
	m_nKey[15] = {};
	m_nKeyCurrent = 0;
	m_nKeyTarget = 0;
	m_nNumAll = 0;
}

//========================================================
//�R���X�g���N�^
//========================================================
CMotion::~CMotion()
{

}

//========================================================
// ����������
//========================================================
void CMotion::Init(int nType)
{
	m_nType = nType;

	m_nKeyCurrent = 0;
	m_nKeyTarget = 1;

	//�S���f��(�p�[�c)�̏����ݒ�
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_ppModel[nCnt]->SetPos(D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fPosX,
											m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fPosY,
											m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fPosZ));

		m_ppModel[nCnt]->SetRot(D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fRotX,
											m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fRotY,
											m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fRotZ));
	}

	m_aInfo[m_nType].bLoop = true;
}

//========================================================
//
//========================================================
void CMotion::Set(int nType)
{
	m_nType = nType;

	m_nKeyCurrent = 0;
	m_nKeyTarget = 1;

	//�S���f��(�p�[�c)�̏����ݒ�
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_ppModel[nCnt]->SetPos(D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fPosX,
			m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fPosY,
			m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fPosZ));

		m_ppModel[nCnt]->SetRot(D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fRotX,
			m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fRotY,
			m_aInfo[m_nType].aKeyInfo[0].aKey[nCnt].fRotZ));
	}

	m_aInfo[m_nType].bLoop = true;
}

//========================================================
//
//========================================================
void CMotion::Load(void)
{
	char aString[1024];
	int nCntMotion = 0;
	int nCntKey = 0;
	int nCnt = 0;

	FILE *pFile;	//�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen("data\\motion.txt", "r");			//(�t�@�C�������w��,�@���[�h�̎w��hr�h�œǂݍ���)

	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &aString[0]);

		//�������r
		if (strcmp(aString, "SCRIPT") == 0)
		{

			while (1)
			{
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%s", &aString[0]);

				//�������r
				if (strcmp(aString, "MOTIONSET") == 0)
				{

					while (1)
					{

						fscanf(pFile, "%s", &aString[0]);

						//�������r
						if (strcmp(aString, "LOOP") == 0)
						{
							fscanf(pFile, "%s", &aString[0]);
							fscanf(pFile, "%d", &m_bLoop[nCntMotion]);
						}

						//�������r
						else if (strcmp(aString, "NUM_KEY") == 0)
						{
							fscanf(pFile, "%s", &aString[0]);
							fscanf(pFile, "%d", &m_nKey[nCntMotion]);
						}

						//�������r
						else if (strcmp(aString, "KEYSET") == 0)
						{

							while (1)
							{

								fscanf(pFile, "%s", &aString[0]);


								//�������r
								if (strcmp(aString, "FRAME") == 0)
								{
									fscanf(pFile, "%s", &aString[0]);
									fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
								}

								//�������r
								else if (strcmp(aString, "KEY") == 0)
								{
									fscanf(pFile, "%s", &aString[0]);
									fscanf(pFile, "%s", &aString[0]);
									fscanf(pFile, "%s", &aString[0]);
									fscanf(pFile, "%s", &aString[0]);
									fscanf(pFile, "%s", &aString[0]);
									fscanf(pFile, "%s", &aString[0]);

									while (1)
									{

										fscanf(pFile, "%s", &aString[0]);


										//�������r
										if (strcmp(aString, "POS") == 0)
										{
											fscanf(pFile, "%s", &aString[0]);

											fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosX);
											fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosY);
											fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosZ);

											m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosX += m_ppModel[nCnt]->GetPos().x;
											m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosY += m_ppModel[nCnt]->GetPos().y;
											m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fPosZ += m_ppModel[nCnt]->GetPos().z;
										}

										//�������r
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%s", &aString[0]);

											fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotX);
											fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotY);
											fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotZ);

										}

										//�������r
										else if (strcmp(aString, "END_KEY") == 0)
										{
											nCnt++;
											break;
										}
									}
								}

								//�������r
								else if (strcmp(aString, "END_KEYSET") == 0)
								{
									nCnt = 0;
									nCntKey++;
									break;
								}
							}
						}

						//�������r
						else if (strcmp(aString, "END_MOTIONSET") == 0)
						{
							m_aInfo[nCntMotion].nType = (TYPE)nCntMotion;

							nCntKey = 0;
							nCntMotion++;
							m_nNumAll++;
							break;
						}
					}
				}

				//�������r
				else if (strcmp(aString, "END_SCRIPT") == 0)
				{

					nCntMotion = 0;

					//�t�@�C�������
					fclose(pFile);

					break;
				}
			}
		}
	}

	else
	{
		printf("�t�@�C�����J���܂���ł���");
	}
}

//========================================================
//
//========================================================
void CMotion::Updata(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (m_aInfo[m_nType].bLoop == true)
	{
		if (m_nType == 5)
		{
			int a;

			a = 0;
		}


		//�S���f��(�p�[�c)�̏����ݒ�
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			float DiffposX, DiffposY, DiffposZ, DiffrotX, DiffrotY, DiffrotZ;		//����

			DiffposX = m_aInfo[m_nType].aKeyInfo[m_nKeyTarget].aKey[nCnt].fPosX - m_aInfo[m_nTypeOld].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fPosX;
			DiffposY = m_aInfo[m_nType].aKeyInfo[m_nKeyTarget].aKey[nCnt].fPosY - m_aInfo[m_nTypeOld].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fPosY;
			DiffposZ = m_aInfo[m_nType].aKeyInfo[m_nKeyTarget].aKey[nCnt].fPosZ - m_aInfo[m_nTypeOld].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fPosZ;
			DiffrotX = m_aInfo[m_nType].aKeyInfo[m_nKeyTarget].aKey[nCnt].fRotX - m_aInfo[m_nTypeOld].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fRotX;
			DiffrotY = m_aInfo[m_nType].aKeyInfo[m_nKeyTarget].aKey[nCnt].fRotY - m_aInfo[m_nTypeOld].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fRotY;
			DiffrotZ = m_aInfo[m_nType].aKeyInfo[m_nKeyTarget].aKey[nCnt].fRotZ - m_aInfo[m_nTypeOld].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fRotZ;

			m_ppModel[nCnt]->SetPos(D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fPosX + DiffposX * (m_nCounter / m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fPosY + DiffposY * (m_nCounter / m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fPosZ + DiffposZ * (m_nCounter / m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].nFrame)));

			m_ppModel[nCnt]->SetRot(D3DXVECTOR3(m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fRotX + DiffrotX * (m_nCounter / m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fRotY + DiffrotY * (m_nCounter / m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].nFrame),
				m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].aKey[nCnt].fRotZ + DiffrotZ * (m_nCounter / m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].nFrame)));
		}

		m_nCounter++;



		if (m_nCounter > m_aInfo[m_nType].aKeyInfo[m_nKeyCurrent].nFrame)
		{
			m_nCounter = 0;

			m_nKeyCurrent++;
			m_nKeyTarget++;

			/*if (m_nType != m_nTypeOld)
			{
				m_nKeyCurrent = 0;
			}*/

			if (m_nKeyCurrent >= m_nKey[m_nType])
			{
				m_nKeyCurrent = 0;
			}

			if (m_nKeyTarget >= m_nKey[m_nType])
			{
				m_nKeyTarget = 0;

				if (m_bLoop[m_nType] == 0)
				{
					m_aInfo[m_nType].bLoop = false;
				}
			}

		}
	}
	m_nTypeOld = m_nType;

}

//========================================================
//
//========================================================
int CMotion::GetType(void)
{
	return m_nType;
}

//========================================================
//
//========================================================
bool CMotion::IsFinish(void)
{
	return m_bFinish;
}

//========================================================
//
//========================================================
void CMotion::SetInfo(INFO info)
{

}

//========================================================
//
//========================================================
void CMotion::SetType(TYPE nType)
{
	m_nType = nType;
}

//========================================================
//
//========================================================
void CMotion::SetModel(CModel **ppModel, int nNumModel)
{
	m_ppModel = ppModel;
	m_nNumModel = nNumModel;
}