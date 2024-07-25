//========================================================
// 
// ウインドウの生成等 (player3D.h)
// Author 橋本賢太
// 
//========================================================
#ifndef _PLAYER3D_H_
#define _PLAYER3D_H_
#include "main.h"
#include "object.h"
#include "model.h"
#include "motion.h"
class CShadow;

//===================================
// プレイヤーのクラス
//===================================
class CPlayer3D : public CObject
{
public:

	// モーションの種類
	typedef enum
	{
		MOTION_NEUTRAL = 0,		// 待機
		MOTION_MOVE,			// 移動
		MOTION_JUMP,			// ジャンプ
		MOTION_LANDING,			// 着地
		MOTION_MAX,
	}MOTIONTYPE;

	// 
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_ACCEL,			// 加速
		TYPE_DELAY,			// 遅延
		TYPE_MAX,
	}SKILL;

	CPlayer3D(int nPriority = 6);									// コンストラクタ
	CPlayer3D(D3DXVECTOR3 pos, int nPriority = 6);					// オーバーライドされたコンストラクタ
	~CPlayer3D();									// デストラクタ

	static CPlayer3D *Create(D3DXVECTOR3 pos);		// 生成処理

	HRESULT Init(void);							// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	D3DXMATRIX GetMtxWorld(void);				// マトリックスを返す
	D3DXVECTOR3 GetPos(void);					// 位置を返す
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);

	D3DXVECTOR3 GetRot(void);					// 向きを返す
	D3DXVECTOR3 GetMove(void);					// 移動量を返す

	CModel *GetModel(int nIdx);					// モデルのポインタを返す

	void Respawn();

	void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, TYPE type);
	bool Collisionbool(D3DXVECTOR3 *pPos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, TYPE type);
	bool CollisionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin);

private:
	static int m_nIdxTexture;					// テクスチャの番号

	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_Oldpos;			// 前フレーム位置
	D3DXVECTOR3 m_revivalpos;		// 復活位置
	D3DXVECTOR3 m_rot;				// 向き
	D3DXVECTOR3 m_revivalrot;		// 復活向き
	D3DXVECTOR3 m_move;				// 移動量
	D3DXVECTOR3 m_keepmove;				// 移動量
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3 m_Destrot;			// 
	D3DXVECTOR3 m_Diffrot;			// 

	D3DXVECTOR3 m_VtxMax;			// 
	D3DXVECTOR3 m_VtxMin;			// 

	MOTIONTYPE m_nType;				// 
	MOTIONTYPE m_nOldType;				// 
	SKILL m_nSkill;

	CModel *m_apModel[32];			// モデルへのポインタ
	int m_nNumModel;				// モデルの総数

	CMotion *m_pMotion;				// モーションのポインタ

	int m_nSkillTime;
	int m_nCnt;

	int m_nSkillCoolTime;

	bool m_bJump;
	bool m_bGoal;
	bool m_bWalk;

	CShadow *m_pShadow;
};

#endif