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
#include <DirectXMath.h>

/*==================================================================================================
	クラス宣言
==================================================================================================*/
namespace KtLib
{
	class Transform
	{
	public:

		Transform() : m_pParent(NULL), m_pos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)), m_scale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)), m_needUpdate(true) { XMStoreFloat4(&m_rotate, DirectX::XMQuaternionIdentity()); }

		//設定系、移動、回転、拡大
		void Reset();	//基本値を代入、SetTrans();と同じ
		void SetTrans(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f,
			float rotateX = 0.0f, float rotateY = 0.0f, float rotateZ = 0.0f,
			float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f);

		void SetTrans(DirectX::XMFLOAT3 m_pos, DirectX::XMFLOAT3 m_rotate, DirectX::XMFLOAT3 m_scale);

		void SetPos(float posX, float posY, float posZ);
		void SetPos(DirectX::XMFLOAT3 posVec);
		void SetRotate(float rotateX, float rotateY, float rotateZ);
		void SetRotate(DirectX::XMFLOAT3 rotateVec);
		void SetRotate(DirectX::XMFLOAT4 rotateQuat);

		void SetScale(float scaleX, float scaleY, float scaleZ);
		void SetScale(DirectX::XMFLOAT3 scaleVec);

		//相対系、移動、回転、拡大
		void Move(float deltaX, float deltaY, float deltaZ);
		void Move(DirectX::XMFLOAT3 delta);
		void Rotate(float deltaX, float deltaY, float deltaZ);
		void Rotate(DirectX::XMFLOAT3 delta);
		void Scale(float deltaX, float deltaY, float deltaZ);
		void Scale(DirectX::XMFLOAT3 delta);

		//親設定
		void ParentTo(Transform& parent);
		void Unparent();

		//ワールド値取得、親の情報が考慮される
		DirectX::XMFLOAT3		GetWorldPos();			//ワールド位置取得（自分+親）
		DirectX::XMFLOAT4		GetWorldRotate();		//ワールド回転取得（自分+親）
		DirectX::XMFLOAT3		GetWorldScale();		//ワールド拡大取得（自分+親）
		DirectX::XMMATRIX		GetWorldMatrix();		//ワールドマトリクス取得

		//マトリクス設定（描画用）
		//void SetMtxWorld();

		//メンバー変数
	private:
		DirectX::XMFLOAT3		m_pos;		//位置座標
		DirectX::XMFLOAT4		m_rotate;	//回転角度
		DirectX::XMFLOAT3		m_scale;	//拡大値
		Transform*				m_pParent;	//親（ないの場合はNULL）

		DirectX::XMMATRIX		m_mtxCurrent;	//今の空間状態マトリクス

		bool			m_needUpdate;	//更新必要フラグ
	};


}	//namespace KtLib