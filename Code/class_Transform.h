/*==================================================================================================
	空間情報クラス

	作者：呉　致緯

	説明：
	
	空間情報クラスを定義する

	XMFLOAT3 型は３Ｄ用ベクトル
	Vec2型は２Ｄ用ベクトル	//ここでは使わない、２Ｄ用オブジェクトは３ＤのZ値を除いて使う
	sys_Macro.h内で使うプラットフォームによって定義している
	posOldはここで定義しない、使うオブジェクト内で定義すべき
==================================================================================================*/
/*==================================================================================================
	二重インクルードガード
==================================================================================================*/
#pragma once

/*==================================================================================================
	インクルード
==================================================================================================*/
#include "sys_Type.h"
#include <DirectXMath.h>

using namespace DirectX;
/*==================================================================================================
	クラス宣言
==================================================================================================*/
class CTrans
{
public:
	
	CTrans() : m_pParent(NULL), m_pos(XMFLOAT3(0.0f, 0.0f, 0.0f)), m_scale(XMFLOAT3(1.0f, 1.0f, 1.0f)), m_needUpdate(true) { XMStoreFloat4(&m_rotate, XMQuaternionIdentity()); }

	//設定系、移動、回転、拡大
	void Reset();	//基本値を代入、SetTrans();と同じ
	void SetTrans	(	float posX		= 0.0f, float posY		= 0.0f ,float posZ		= 0.0f,
						float rotateX	= 0.0f, float rotateY	= 0.0f, float rotateZ	= 0.0f,
						float scaleX	= 1.0f, float scaleY	= 1.0f, float scaleZ	= 1.0f );

	void SetTrans	( XMFLOAT3 m_pos, XMFLOAT3 m_rotate, XMFLOAT3 m_scale );

	void SetPos		( float posX	, float posY	, float posZ	);
	void SetPos		( XMFLOAT3 posVec	 );
	void SetRotate	( float rotateX	, float rotateY	, float rotateZ );
	void SetRotate	( XMFLOAT3 rotateVec );
	void SetRotate	( XMFLOAT4 rotateQuat);

	void SetScale	( float scaleX	, float scaleY	, float scaleZ	);
	void SetScale	( XMFLOAT3 scaleVec	 );

	//相対系、移動、回転、拡大
	void Move	( float deltaX	, float deltaY	, float deltaZ	);
	void Move	( XMFLOAT3 delta	);
	void Rotate	( float deltaX	, float deltaY	, float deltaZ	);
	void Rotate	( XMFLOAT3 delta	);
	void Scale	( float deltaX	, float deltaY	, float deltaZ	);
	void Scale	( XMFLOAT3 delta	);

	//親設定
	void ParentTo( CTrans& parent );
	void Unparent();

	//ワールド値取得、親の情報が考慮される
	XMFLOAT3		GetWorldPos();			//ワールド位置取得（自分+親）
	XMFLOAT4		GetWorldRotate();		//ワールド回転取得（自分+親）
	XMFLOAT3		GetWorldScale();		//ワールド拡大取得（自分+親）
	XMMATRIX		GetWorldMatrix();		//ワールドマトリクス取得

	//マトリクス設定（描画用）
	//void SetMtxWorld();

	//メンバー変数
private:
	XMFLOAT3		m_pos;		//位置座標
	XMFLOAT4		m_rotate;	//回転角度
	XMFLOAT3		m_scale;	//拡大値
	CTrans*			m_pParent;	//親（ないの場合はNULL）

	XMMATRIX		m_mtxCurrent;	//今の空間状態マトリクス

	bool			m_needUpdate;	//更新必要フラグ
};


