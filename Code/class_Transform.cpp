/*==================================================================================================
	�C���N���[�h
==================================================================================================*/
#include "class_Transform.h"

using namespace DirectX;
/*==================================================================================================
	�N���X��`
==================================================================================================*/

//�ݒ�n�A�ړ��A��]�A�g��
void CTrans::Reset()
{
	m_needUpdate = true;
	this->SetTrans();
}

void CTrans::SetTrans	(	float posX		, float posY	,float posZ,
							float rotateX	, float rotateY	, float rotateZ,
							float scaleX	, float scaleY	, float scaleZ )
{
	m_needUpdate = true;
	this->SetPos	( posX,		posY,		posZ	);
	this->SetRotate	( rotateX,	rotateY,	rotateZ );
	this->SetScale	( scaleX,	scaleY,		scaleZ	);
}

void CTrans::SetTrans	( XMFLOAT3 m_pos, XMFLOAT3 m_rotate, XMFLOAT3 m_scale )
{
	m_needUpdate = true;
	this->SetPos	( m_pos	 );
	this->SetRotate	( m_rotate );
	this->SetScale	( m_scale	 );
}

void CTrans::SetPos		( float posX	, float posY	, float posZ	)
{
	m_needUpdate = true;
	m_pos.x = posX;
	m_pos.y = posY;
	m_pos.z = posZ;

}
void CTrans::SetRotate	( float rotateX	, float rotateY	, float rotateZ )
{
	
	m_needUpdate = true;
	XMVECTOR temp;

	temp = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(rotateX), XMConvertToRadians(rotateY), XMConvertToRadians(rotateZ) );	
	XMStoreFloat4(&m_rotate, temp);
}
void CTrans::SetScale	( float scaleX	, float scaleY	, float scaleZ	)
{
	m_needUpdate = true;
	m_scale.x = scaleX;
	m_scale.y = scaleY;
	m_scale.z = scaleZ;
}

void CTrans::SetPos		( XMFLOAT3 posVec	 )
{
	m_needUpdate = true;
	m_pos = posVec;
}
void CTrans::SetRotate	( XMFLOAT3 rotateVec )
{
	m_needUpdate = true;
	XMVECTOR temp;
	temp = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(rotateVec.x), XMConvertToRadians(rotateVec.y), XMConvertToRadians(rotateVec.z));
	XMStoreFloat4(&m_rotate, temp);
}
void CTrans::SetRotate	( XMFLOAT4 rotateQuat)
{
	m_needUpdate = true;
	m_rotate = rotateQuat;
}

void CTrans::SetScale	( XMFLOAT3 scaleVec	 )
{
	m_needUpdate = true;
	m_scale = scaleVec;
}

void CTrans::ParentTo(  CTrans& parent )
{
	m_needUpdate = true;
	m_pParent = &parent;
}
void CTrans::Unparent()
{
	m_needUpdate = true;
	m_pParent = NULL;
}

XMFLOAT3 CTrans::GetWorldPos()
{
	//�����������ŏ�w�̏ꍇ
	if( !m_pParent )
	{
		return m_pos;
	}

	XMFLOAT3 result;
	//�����̍��W����
	result = m_pos;

	//�e��Ԃ̃}�g���N�X���擾���Ď����̈ʒu���Z�o
	XMMATRIX parentMtx = m_pParent->GetWorldMatrix();
	
	XMVECTOR temp = XMLoadFloat3(&result);
	temp = XMVector3TransformCoord(temp, parentMtx);

	XMStoreFloat3(&result, temp);

	return result;
}
XMFLOAT4 CTrans::GetWorldRotate()
{
	if( !m_pParent )
	{
		return m_rotate;
	}

	XMFLOAT4 result;
	result = m_pParent->GetWorldRotate();
	XMStoreFloat4( &result, (XMLoadFloat4(&m_rotate), XMLoadFloat4(&result)) );
	return result;
}
XMFLOAT3 CTrans::GetWorldScale()
{
	//�����������ŏ�w�̏ꍇ
	if (!m_pParent)
	{
		return m_scale;
	}

	XMFLOAT3 result;

	//�e��Ԃ̃}�g���N�X���擾���Ď����̊g����Z�o
	XMFLOAT3 parentScale = m_pParent->GetWorldScale();

	result.x = m_scale.x * parentScale.x;
	result.y = m_scale.y * parentScale.y;
	result.z = m_scale.z * parentScale.z;

	return result;


}

XMMATRIX CTrans::GetWorldMatrix()
{
	if (!m_needUpdate)
	{
		return m_mtxCurrent;
	}


//�����̃}�g���N�X�X�V
	//�g��}�g���N�X�쐬
	XMMATRIX mtxScale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	//��]�}�g���N�X�쐬
	XMMATRIX mtxRotate = XMMatrixRotationQuaternion(XMLoadFloat4(&m_rotate));

	//�ړ��}�g���N�X�쐬�i���S����v�Z�܂�)
	XMMATRIX mtxMove = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

	//���[���h�}�g���N�X�쐬
	//�P�ʍs����
	XMMATRIX temp = XMMatrixIdentity();
	//�g���]�ړ�����
	temp = XMMatrixMultiply(temp, mtxScale);
	temp = XMMatrixMultiply(temp, mtxRotate);
	temp = XMMatrixMultiply(temp, mtxMove);
	m_mtxCurrent = temp;

//����
	if (!m_pParent)
	{//�e���Ȃ��ꍇ�����̃}�g���N�X���A��
		m_needUpdate = false;
		return m_mtxCurrent;
	}

//�ċA
	XMMATRIX parentMtx;
	//�e�̃}�g���N�X���擾���Ď����ƍ�������
	parentMtx = m_pParent->GetWorldMatrix();
	parentMtx = XMMatrixMultiply(parentMtx, m_mtxCurrent);

	return parentMtx;
}


//���Όn�A�ړ��iposOld���O���m_pos���L�^�j�A��]�A�g��
void CTrans::Move	( float deltaX	, float deltaY	, float deltaZ	)
{
	m_needUpdate = true;
	m_pos.x += deltaX;
	m_pos.y += deltaY;
	m_pos.z += deltaZ;
}
void CTrans::Rotate	( float deltaX	, float deltaY	, float deltaZ	)
{
	m_needUpdate = true;
	XMVECTOR temp;
	temp = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(deltaX), XMConvertToRadians(deltaY), XMConvertToRadians(deltaZ));
	temp = XMQuaternionMultiply(XMLoadFloat4(&m_rotate), temp);
	XMStoreFloat4(&m_rotate, temp);

}
void CTrans::Scale	( float deltaX	, float deltaY	, float deltaZ	)
{
	m_needUpdate = true;
	m_scale.x += deltaX;
	m_scale.y += deltaY;
	m_scale.z += deltaZ;
}

void CTrans::Move	( XMFLOAT3 delta	)
{
	Move(delta.x, delta.y, delta.z);
	//m_needUpdate = true;
	//XMVECTOR temp;
	//temp = XMLoadFloat3(&m_pos) + XMLoadFloat3(&delta);
	//XMStoreFloat3(&m_pos, temp);
}
void CTrans::Rotate	( XMFLOAT3 delta	)
{
	Rotate(delta.x, delta.y, delta.z);
}
void CTrans::Scale	( XMFLOAT3 delta	)
{
	Scale(delta.x, delta.y, delta.z);
}
