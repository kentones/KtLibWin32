#pragma once

namespace KtLib
{
	class CharacterBase;


	class KtBehaviorBase
	{
	public:
		virtual void Setup() = 0;
		virtual void Update() = 0;

	private:



	};
	class CharacterBehavior : public KtBehaviorBase
	{
	public:


	private:
		CharacterBase* m_belong;
		int hp;
		int atk;
		int speed;
	};



}	//namespace KtLib
