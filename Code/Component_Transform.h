/*==================================================================================================
	��ԏ��N���X

	��ҁF���@�v��

	�����F
	
	��ԏ��N���X���`����

	XMFLOAT3 �^�͂R�c�p�x�N�g��
	Vec2�^�͂Q�c�p�x�N�g��	//�����ł͎g��Ȃ��A�Q�c�p�I�u�W�F�N�g�͂R�c��Z�l�������Ďg��
	sys_Macro.h���Ŏg���v���b�g�t�H�[���ɂ���Ē�`���Ă���
	posOld�͂����Œ�`���Ȃ��A�g���I�u�W�F�N�g���Œ�`���ׂ�
==================================================================================================*/
/*==================================================================================================
	��d�C���N���[�h�K�[�h
==================================================================================================*/
#pragma once

/*==================================================================================================
	�C���N���[�h
==================================================================================================*/
#include <DirectXMath.h>

/*==================================================================================================
	�N���X�錾
==================================================================================================*/
namespace KtLib
{
	class Transform
	{
	public:

		Transform() : m_pParent(NULL), m_pos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)), m_scale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)), m_needUpdate(true) { XMStoreFloat4(&m_rotate, DirectX::XMQuaternionIdentity()); }

		//�ݒ�n�A�ړ��A��]�A�g��
		void Reset();	//��{�l�����ASetTrans();�Ɠ���
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

		//���Όn�A�ړ��A��]�A�g��
		void Move(float deltaX, float deltaY, float deltaZ);
		void Move(DirectX::XMFLOAT3 delta);
		void Rotate(float deltaX, float deltaY, float deltaZ);
		void Rotate(DirectX::XMFLOAT3 delta);
		void Scale(float deltaX, float deltaY, float deltaZ);
		void Scale(DirectX::XMFLOAT3 delta);

		//�e�ݒ�
		void ParentTo(Transform& parent);
		void Unparent();

		//���[���h�l�擾�A�e�̏�񂪍l�������
		DirectX::XMFLOAT3		GetWorldPos();			//���[���h�ʒu�擾�i����+�e�j
		DirectX::XMFLOAT4		GetWorldRotate();		//���[���h��]�擾�i����+�e�j
		DirectX::XMFLOAT3		GetWorldScale();		//���[���h�g��擾�i����+�e�j
		DirectX::XMMATRIX		GetWorldMatrix();		//���[���h�}�g���N�X�擾

		//�}�g���N�X�ݒ�i�`��p�j
		//void SetMtxWorld();

		//�����o�[�ϐ�
	private:
		DirectX::XMFLOAT3		m_pos;		//�ʒu���W
		DirectX::XMFLOAT4		m_rotate;	//��]�p�x
		DirectX::XMFLOAT3		m_scale;	//�g��l
		Transform*				m_pParent;	//�e�i�Ȃ��̏ꍇ��NULL�j

		DirectX::XMMATRIX		m_mtxCurrent;	//���̋�ԏ�ԃ}�g���N�X

		bool			m_needUpdate;	//�X�V�K�v�t���O
	};


}	//namespace KtLib