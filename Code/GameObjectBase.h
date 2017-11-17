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




	//Bullet（弾、始点と終点があって、当たり判定存在、飛び方もいろいろ設定できる）
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
		//飛び方設定フラグ
		//発射処理
		//当たった処理
		//当たってない処理
		//Target Position
	};


	//Breakable
	//Visual	（表示用、当たり判定は使用しない)
	


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
