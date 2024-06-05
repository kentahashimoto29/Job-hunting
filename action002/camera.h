//========================================================
//
//ウインドウの生成等 (camera.h)
//Author 橋本賢太
//
//========================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//===================================
//カメラのクラス
//===================================
class CCamera
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_SCOPE,
		TYPE_MAX
	}TYPE;

	CCamera();											//コンストラクタ
	~CCamera();											//デストラクタ

	HRESULT Init(void);									//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void SetCamera(void);								//カメラの設定処理
	void SetPos(D3DXVECTOR3 posV, D3DXVECTOR3 posR);	//位置の設定処理
	void SetPosGame(D3DXVECTOR3 posV, D3DXVECTOR3 posR);	//位置の設定処理

	D3DXVECTOR3 GetRot(void);							//向きを返す

private:
	D3DXVECTOR3 m_posV;						//視点
	D3DXVECTOR3 m_posR;						//注視点
	D3DXVECTOR3 m_keepPosV;					//保存用視点
	D3DXVECTOR3 m_keepPosR;					//保存用注視点
	D3DXVECTOR3 m_vecU;						//上方向のベクトル
	D3DXVECTOR3 m_rot;						//向き
	D3DXMATRIX m_mtxProjection;				//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;					//ビューマトリックス

	float m_Distance;           //視点と注視点の距離
	float m_Angle;              //視点と注視点の角度
	D3DXVECTOR3 m_Angle2;
	TYPE m_type;

	float x;
	float y;
};

#endif