//========================================================
//
//ウインドウの生成等 (goal.h)
//Author 橋本賢太
//
//========================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "manager.h"
#include "player3D.h"
#include "enemymanager.h"
#include "block3D.h"
#include "death_block.h"
#include "through_block.h"
#include "time.h"
#include "score.h"
#include "field.h"
#include "wall.h"
#include "item_manager.h"
class CSkill_UI;
class CWallObjManager;

//===================================
//ゲームのクラス
//===================================
class CGame : public CScene
{
public:
	CGame();								//コンストラクタ
	~CGame();								//デストラクタ

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	D3DXVECTOR3 m_pos;						//オブジェクトの位置;

	static CPlayer3D *GetPlayer3D();			//プレイヤー3Dのポインタを返す関数
	static CBlock3D *GetBlock3D();				//ブロック3Dのポインタを返す関数
	static CDeathBlock *GetDeathBlock();		//即死ブロックのポインタを返す関数
	static CThroughBlock *GetThroughBlock();	//通り抜けれるブロックのポインタを返す関数
	static CTime *GetTime();					//タイムのポインタを返す関数
	static CScore *GetScore();					//スコアのポインタを返す関数
	static CEnemyManager *GetEnemyManager();	//敵マネージャーのポインタを返す関数
	static CWallObjManager *GetWallManager();	//敵マネージャーのポインタを返す関数
	static CItemManager *GetItemManager();		//アイテムマネージャーのポインタを返す関数
	static CSkill_UI *GetSkillUI();				//アイテムマネージャーのポインタを返す関数
	CField *GetField();							//フィールドのポインタを返す関数
	CWall *GetWall();							//壁のポインタを返す関数

	static float GetInitPos();
	static int GetGameScore();
	static void SetScore(int nScore);
	static void AddScore();

private:

	static CPlayer3D *m_pPlayer3D;				//プレイヤー3Dのポインタ
	static CBlock3D *m_pBlock3D;				//ブロック3Dのポインタ
	static CDeathBlock *m_pDeathBlock;			//即死ブロックのポインタ
	static CThroughBlock *m_pThroughBlock;		//通り抜けれるブロックのポインタ
	static CTime *m_pTime;						//タイムのポインタ
	static CScore *m_pScore;					//スコアのポインタ
	static CEnemyManager *m_pEnemyManager;		//エネミー3Dのポインタ
	static CWallObjManager *m_pWallManager;		//エネミー3Dのポインタ
	static CItemManager *m_pItemManager;		//アイテムマネージャーのポインタ
	static CSkill_UI *m_pSkillUI;				//アイテムマネージャーのポインタ
	CField *m_pField[256];						//フィールドのポインタ
	CWall *m_pWall[256];						//壁のポインタ

	static float m_nInitPos;

	bool b;
	static int m_nScore;
};

#endif