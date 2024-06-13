//========================================================
//
//ウインドウの生成等 (motion.cpp)
//Author 橋本賢太
//
//========================================================
#include "motion.h"
#include "manager.h"

//========================================================
//コンストラクタ
//========================================================
CMotion::CMotion()
{
	m_nKey[15] = {};
	m_nKeyCurrent = 0;
	m_nKeyTarget = 0;
	m_nNumAll = 0;
}

//========================================================
//コンストラクタ
//========================================================
CMotion::~CMotion()
{

}

//========================================================
// 初期化処理
//========================================================
void CMotion::Init(int nType)
{
	m_nType = nType;

	m_nKeyCurrent = 0;
	m_nKeyTarget = 1;

	//全モデル(パーツ)の初期設定
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

	//全モデル(パーツ)の初期設定
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

	FILE *pFile;	//ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("data\\motion.txt", "r");			//(ファイル名を指定,　モードの指定”r”で読み込み)

	//NULLチェック
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &aString[0]);

		//文字列比較
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

				//文字列比較
				if (strcmp(aString, "MOTIONSET") == 0)
				{

					while (1)
					{

						fscanf(pFile, "%s", &aString[0]);

						//文字列比較
						if (strcmp(aString, "LOOP") == 0)
						{
							fscanf(pFile, "%s", &aString[0]);
							fscanf(pFile, "%d", &m_bLoop[nCntMotion]);
						}

						//文字列比較
						else if (strcmp(aString, "NUM_KEY") == 0)
						{
							fscanf(pFile, "%s", &aString[0]);
							fscanf(pFile, "%d", &m_nKey[nCntMotion]);
						}

						//文字列比較
						else if (strcmp(aString, "KEYSET") == 0)
						{

							while (1)
							{

								fscanf(pFile, "%s", &aString[0]);


								//文字列比較
								if (strcmp(aString, "FRAME") == 0)
								{
									fscanf(pFile, "%s", &aString[0]);
									fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
								}

								//文字列比較
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


										//文字列比較
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

										//文字列比較
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%s", &aString[0]);

											fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotX);
											fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotY);
											fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCnt].fRotZ);

										}

										//文字列比較
										else if (strcmp(aString, "END_KEY") == 0)
										{
											nCnt++;
											break;
										}
									}
								}

								//文字列比較
								else if (strcmp(aString, "END_KEYSET") == 0)
								{
									nCnt = 0;
									nCntKey++;
									break;
								}
							}
						}

						//文字列比較
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

				//文字列比較
				else if (strcmp(aString, "END_SCRIPT") == 0)
				{

					nCntMotion = 0;

					//ファイルを閉じる
					fclose(pFile);

					break;
				}
			}
		}
	}

	else
	{
		printf("ファイルが開けませんでした");
	}
}

//========================================================
//
//========================================================
void CMotion::Updata(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (m_aInfo[m_nType].bLoop == true)
	{
		if (m_nType == 5)
		{
			int a;

			a = 0;
		}


		//全モデル(パーツ)の初期設定
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			float DiffposX, DiffposY, DiffposZ, DiffrotX, DiffrotY, DiffrotZ;		//差分

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