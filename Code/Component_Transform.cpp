/*==================================================================================================
	インクルード
==================================================================================================*/
#include "pch.h"
#include "Component_Transform.h"

using namespace DirectX;
/*==================================================================================================
	クラス定義
==================================================================================================*/
namespace KtLib
{

	//設定系、移動、回転、拡大
	void Transform::Reset()
	{
		m_needUpdate = true;
		this->SetTrans();
	}

	void Transform::SetTrans(float posX, float posY, float posZ,
		float rotateX, float rotateY, float rotateZ,
		float scaleX, float scaleY, float scaleZ)
	{
		m_needUpdate = true;
		this->SetPos(posX, posY, posZ);
		this->SetRotate(rotateX, rotateY, rotateZ);
		this->SetScale(scaleX, scaleY, scaleZ);
	}

	void Transform::SetTrans(XMFLOAT3 m_pos, XMFLOAT3 m_rotate, XMFLOAT3 m_scale)
	{
		m_needUpdate = true;
		this->SetPos(m_pos);
		this->SetRotate(m_rotate);
		this->SetScale(m_scale);
	}

	void Transform::SetPos(float posX, float posY, float posZ)
	{
		m_needUpdate = true;
		m_pos.x = posX;
		m_pos.y = posY;
		m_pos.z = posZ;

	}
	void Transform::SetRotate(float rotateX, float rotateY, float rotateZ)
	{

		m_needUpdate = true;
		XMVECTOR temp;

		temp = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(rotateX), XMConvertToRadians(rotateY), XMConvertToRadians(rotateZ));
		XMStoreFloat4(&m_rotate, temp);
	}
	void Transform::SetScale(float scaleX, float scaleY, float scaleZ)
	{
		m_needUpdate = true;
		m_scale.x = scaleX;
		m_scale.y = scaleY;
		m_scale.z = scaleZ;
	}

	void Transform::SetPos(XMFLOAT3 posVec)
	{
		m_needUpdate = true;
		m_pos = posVec;
	}
	void Transform::SetRotate(XMFLOAT3 rotateVec)
	{
		m_needUpdate = true;
		XMVECTOR temp;
		temp = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(rotateVec.x), XMConvertToRadians(rotateVec.y), XMConvertToRadians(rotateVec.z));
		XMStoreFloat4(&m_rotate, temp);
	}
	void Transform::SetRotate(XMFLOAT4 rotateQuat)
	{
		m_needUpdate = true;
		m_rotate = rotateQuat;
	}

	void Transform::SetScale(XMFLOAT3 scaleVec)
	{
		m_needUpdate = true;
		m_scale = scaleVec;
	}

	void Transform::ParentTo(Transform& parent)
	{
		m_needUpdate = true;
		m_pParent = &parent;
	}
	void Transform::Unparent()
	{
		m_needUpdate = true;
		m_pParent = NULL;
	}

	XMFLOAT3 Transform::GetWorldPos()
	{
		//もし自分が最上層の場合
		if (!m_pParent)
		{
			return m_pos;
		}

		XMFLOAT3 result;
		//自分の座標を代入
		result = m_pos;

		//親空間のマトリクスを取得して自分の位置を算出
		XMMATRIX parentMtx = m_pParent->GetWorldMatrix();

		XMVECTOR temp = XMLoadFloat3(&result);
		temp = XMVector3TransformCoord(temp, parentMtx);

		XMStoreFloat3(&result, temp);

		return result;
	}
	XMFLOAT4 Transform::GetWorldRotate()
	{
		if (!m_pParent)
		{
			return m_rotate;
		}

		XMFLOAT4 result;
		result = m_pParent->GetWorldRotate();
		XMStoreFloat4(&result, (XMLoadFloat4(&m_rotate), XMLoadFloat4(&result)));
		return result;
	}
	XMFLOAT3 Transform::GetWorldScale()
	{
		//もし自分が最上層の場合
		if (!m_pParent)
		{
			return m_scale;
		}

		XMFLOAT3 result;

		//親空間のマトリクスを取得して自分の拡大を算出
		XMFLOAT3 parentScale = m_pParent->GetWorldScale();

		result.x = m_scale.x * parentScale.x;
		result.y = m_scale.y * parentScale.y;
		result.z = m_scale.z * parentScale.z;

		return result;


	}

	XMMATRIX Transform::GetWorldMatrix()
	{
		if (!m_needUpdate)
		{
			return m_mtxCurrent;
		}


		//自分のマトリクス更新
			//拡大マトリクス作成
		XMMATRIX mtxScale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		//回転マトリクス作成
		XMMATRIX mtxRotate = XMMatrixRotationQuaternion(XMLoadFloat4(&m_rotate));

		//移動マトリクス作成（中心ずれ計算含む)
		XMMATRIX mtxMove = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

		//ワールドマトリクス作成
		//単位行列代入
		XMMATRIX temp = XMMatrixIdentity();
		//拡大回転移動合成
		temp = XMMatrixMultiply(temp, mtxScale);
		temp = XMMatrixMultiply(temp, mtxRotate);
		temp = XMMatrixMultiply(temp, mtxMove);
		m_mtxCurrent = temp;

		//結果
		if (!m_pParent)
		{//親がない場合自分のマトリクスを帰す
			m_needUpdate = false;
			return m_mtxCurrent;
		}

		//再帰
		XMMATRIX parentMtx;
		//親のマトリクスを取得して自分と合成する
		parentMtx = m_pParent->GetWorldMatrix();
		parentMtx = XMMatrixMultiply(parentMtx, m_mtxCurrent);

		return parentMtx;
	}


	//相対系、移動（posOldが前回のm_posを記録）、回転、拡大
	void Transform::Move(float deltaX, float deltaY, float deltaZ)
	{
		m_needUpdate = true;
		m_pos.x += deltaX;
		m_pos.y += deltaY;
		m_pos.z += deltaZ;
	}
	void Transform::Rotate(float deltaX, float deltaY, float deltaZ)
	{
		m_needUpdate = true;
		XMVECTOR temp;
		temp = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(deltaX), XMConvertToRadians(deltaY), XMConvertToRadians(deltaZ));
		temp = XMQuaternionMultiply(XMLoadFloat4(&m_rotate), temp);
		XMStoreFloat4(&m_rotate, temp);

	}
	void Transform::Scale(float deltaX, float deltaY, float deltaZ)
	{
		m_needUpdate = true;
		m_scale.x += deltaX;
		m_scale.y += deltaY;
		m_scale.z += deltaZ;
	}

	void Transform::Move(XMFLOAT3 delta)
	{
		Move(delta.x, delta.y, delta.z);
		//m_needUpdate = true;
		//XMVECTOR temp;
		//temp = XMLoadFloat3(&m_pos) + XMLoadFloat3(&delta);
		//XMStoreFloat3(&m_pos, temp);
	}
	void Transform::Rotate(XMFLOAT3 delta)
	{
		Rotate(delta.x, delta.y, delta.z);
	}
	void Transform::Scale(XMFLOAT3 delta)
	{
		Scale(delta.x, delta.y, delta.z);
	}

}	//namespace KtLib