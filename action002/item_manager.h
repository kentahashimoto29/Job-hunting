//========================================================
//
//ウインドウの生成等 (item_manager.h)
//Author 橋本賢太
//
//========================================================
#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_
#include "main.h"
#include "item_throw.h"

//===================================
//アイテムマネージャーのクラス
//===================================
class CItemManager
{
public:
	CItemManager();									//コンストラクタ
	~CItemManager();								//デストラクタ

	static CItemManager *Create();				//敵の生成

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理

	void Release(int nIdx);
	void Kill(void);
	CItemThrow **CItemManager::SetItemThrow(D3DXVECTOR3 pos);

	static int GetNum(void);					//総数を返す
	CItemThrow **GetItemThrow(void);			// 敵取得

private:

	CItemThrow *m_pItemThrow[16];				//投げアイテムのポインタ
	static int m_nNum;							//アイテム総数
};

#endif#pragma once
