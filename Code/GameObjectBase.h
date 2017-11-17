#pragma once

#include <string>

namespace KtLib
{
	class KtGameObjectBase
	{
	public:
		virtual bool Setup() = 0;
		virtual bool Init() = 0;
		virtual void Release() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

	private:
		//std::list< BehaviorBase*> m_CB;

	};

	//class Player : public CharacterBase
	//{
	//	KtRenderableBase* m_pRenderable;
	//};






	//ControllableCharacter
	class GOControllable : KtGameObjectBase
	{
	public:
		bool Setup()override;
		bool Init()override;
		void Release()override;
		void Update()override;
		void Render()override;



	private:

	};




	//Bullet�i�e�A�n�_�ƏI�_�������āA�����蔻�葶�݁A��ѕ������낢��ݒ�ł���j
	class GOBullet : KtGameObjectBase
	{
	public:
		bool Setup()override;
		bool Init()override;
		void Release()override;
		void Update()override;
		void Render()override;

	private:
		//Damage
		//Life
		//��ѕ��ݒ�t���O
		//���ˏ���
		//������������
		//�������ĂȂ�����
		//Target Position
	};


	//Breakable
	//Visual	�i�\���p�A�����蔻��͎g�p���Ȃ�)
	


	//Terrain
	class KtGameObjectTerrain : public KtGameObjectBase
	{
	public:
		virtual bool Setup() = 0;
		virtual bool Init() = 0;
		virtual void Release() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

	private:

	};






}	//namespace KtLib
