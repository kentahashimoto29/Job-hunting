//========================================================
//
//ウインドウの生成等 (Object.cpp)
//Author 橋本賢太
//
//========================================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"

//マクロ定義
#define MAX_PLAYER							(2)			//プレイヤーの最大数

CObject *CObject::m_pTop[8] = {};
CObject *CObject::m_pCur[8] = {};

//========================================================
//コンストラクタ
//========================================================
CObject::CObject(int nPriority)
{
	if (nPriority < 0 || nPriority >= 8)
	{// 範囲外だったら

		return;
	}

	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;				//自分自身を代入
		m_pCur[nPriority] = m_pTop[nPriority];			//自分自身を代入
	}

	else if (m_pTop[nPriority] != NULL)
	{
		CObject *obj = m_pCur[nPriority];

		m_pCur[nPriority]->m_pNext = this;
		m_pCur[nPriority] = m_pCur[nPriority]->m_pNext;
		m_pCur[nPriority]->m_pPrev = obj;
		m_pCur[nPriority]->m_pNext = NULL;
	}

	m_nPriority = nPriority;	// 優先順位

	m_type = TYPE_NONE;				//
	m_bflag = false;
}

//========================================================
//デストラクタ
//========================================================
CObject::~CObject()
{

}

//========================================================
//初期化終了処理
//========================================================
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < 8; nCntPriority++)
	{
		CObject *pObject = m_pTop[nCntPriority];

		while (pObject != NULL)
		{
			CObject *pObjectNext = pObject->m_pNext;

			pObject->Uninit();

			pObject = pObjectNext;
		}
	}
}

//========================================================
//オブジェクトの更新処理
//========================================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < 8; nCntPriority++)
	{

		CObject *pObject = m_pTop[nCntPriority];

		while (pObject != NULL)
		{
			CObject *pObjectNext = pObject->m_pNext;

			pObject->Update();

			pObject = pObjectNext;
		}


		for (int nCntPriorityDeath = 0; nCntPriorityDeath < 8; nCntPriorityDeath++)
		{
			// 先頭を保存
			pObject = m_pTop[nCntPriorityDeath];

			while (pObject != NULL)
			{// NULLが来るまで無限ループ

			 // 次のオブジェクトを一時保存
				CObject *pObjNext = pObject->m_pNext;

				if (pObject->m_bflag == true)
				{// 死亡フラグが立っていたら

				 // 完全死亡処理
					pObject->Death();
				}

				// 次のオブジェクトを代入
				pObject = pObjNext;
			}
		}
	}
}

//========================================================
//オブジェクトの描画処理
//========================================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	//カメラの設定
	pCamera->SetCamera();

	for (int nCntPriority = 0; nCntPriority < 8; nCntPriority++)
	{
		CObject *pObject = m_pTop[nCntPriority];

		while (pObject != NULL)
		{
			CObject *pObjectNext = pObject->m_pNext;

			pObject->Draw();

			pObject = pObjectNext;
		}
	}
}

//========================================================
//n番目の初期化終了処理
//========================================================
void CObject::Release(void)
{
	m_bflag = true;
}

//========================================================
//
//========================================================
void CObject::Death(void)
{
	// 今回の番号保存
	int nPriority = m_nPriority;

	CObject *pObject = this;

	CObject *pObjectNext = pObject->m_pNext;
	CObject *pObjectPrev = pObject->m_pPrev;


	//this使う (delete this;)
	//繋げ直しはNextのNextまで使う
	if (pObject != m_pCur[nPriority])
	{
		pObjectNext->m_pPrev = pObjectPrev;

		if (pObject != m_pTop[nPriority])
		{
			pObjectPrev->m_pNext = pObjectNext;
		}

		else
		{
			m_pTop[nPriority] = pObjectNext;
		}
	}

	else
	{
		if (pObject != m_pTop[nPriority])
		{
			pObjectPrev->m_pNext = NULL;
			m_pCur[nPriority] = pObjectPrev;
		}

		else
		{
			m_pTop[nPriority] = NULL;
		}
	}

	delete pObject;

	pObject = NULL;
}

//========================================================
//オブジェクトの最初を返す
//========================================================
CObject *CObject::GetTop(int nPriority)
{
	return m_pTop[nPriority];
}

//========================================================
//次のオブジェクトを返す
//========================================================
CObject *CObject::GetNext(void)
{
	return m_pNext;
}

//========================================================
//オブジェクトの種類を設定
//========================================================
void CObject::SetType(TYPE type)
{
	m_type = type;
}

//========================================================
//オブジェクトの種類を返す関数
//========================================================
CObject::TYPE CObject::GetType(void)
{
	return m_type;
}

//========================================================
//オブジェクトを返す関数
//========================================================
CObject *CObject::GetObject()
{
	return this;
}