//========================================================
// 
// ミニマップカメラ (minimap_camera.h)
// Author 橋本賢太
// 
//========================================================
#ifndef _MINIMAP_CAMERA_H_
#define _MINIMAP_CAMERA_H_
#include "main.h"

//===================================
// ミニマップカメラのクラス
//===================================
class CMinimap_Camera
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_SCOPE,
		TYPE_MAX
	}TYPE;

	CMinimap_Camera();									// コンストラクタ
	~CMinimap_Camera();									// デストラクタ

	HRESULT Init(void);									// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void SetCamera(void);								// カメラの設定処理
	void SetPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR);	// 位置の設定処理
	void SetPosGame(D3DXVECTOR3 posV, D3DXVECTOR3 posR);// 位置の設定処理

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }		// 向きを設定
	D3DXVECTOR3 GetRot(void);							// 向きを返す

private:
	D3DXVECTOR3 m_posV;						// 視点
	D3DXVECTOR3 m_posR;						// 注視点
	D3DXVECTOR3 m_keepPosV;					// 保存用視点
	D3DXVECTOR3 m_keepPosR;					// 保存用注視点
	D3DXVECTOR3 m_vecU;						// 上方向のベクトル
	D3DXVECTOR3 m_rot;						// 向き
	D3DXMATRIX m_mtxProjection;				// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;					// ビューマトリックス

	D3DVIEWPORT9 m_viewport;

	float m_Distance;           // 視点と注視点の距離
	float m_Angle;              // 視点と注視点の角度
	D3DXVECTOR3 m_Angle2;
	TYPE m_type;
};

#endif