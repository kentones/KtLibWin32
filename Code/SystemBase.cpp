#include "SystemBase.h"
#include "common_Template.h"

//#include "Renderer.h"

namespace KtLib
{
	//============================================================================
	//	Public
	//============================================================================

	//シングルトン作成かつ初期化
	bool KtSystem::Create()
	{
		SafeReleaseDelete(s_pInstance);

		s_pInstance = new KtSystem;
		if (!s_pInstance)	{	return false;	}

		return s_pInstance->Init();
	}

	//シングルトン消滅
	void KtSystem::Destory()
	{
		SafeReleaseDelete(s_pInstance);
	}

	void KtSystem::Update()
	{
		//タイマー更新

		//入力更新

		//前処理

		//シーン更新
		/*
		if (m_pCurrentScene)
		{
		m_pCurrentScene->Update();
		}
		if (m_pUIScene)
		{
		m_pUIScene->Update();
		}
		*/

		//後処理
		//衝突判定更新？
		//衝突応答？

		//シーン遷移チェック

	}

	void KtSystem::Render()const
	{
		//シーン描画
		/*
		if (m_pCurrentScene)
		{
		m_pCurrentScene->PushToRenderStack();
		}
		if (m_pUIScene)
		{
		m_pUIScene->PushToRenderStack();
		}
		if(m_pRenderer)
		{
		m_pRenderer->Render();
		}
		*/
	}


	//============================================================================
	//	Private
	//============================================================================

	bool KtSystem::Init()
	{
		bool isSuccess = false;

		//Renderer
		//二重作成防止
		SafeReleaseDelete(m_pRenderer);

		//インスタンス作成
		m_pRenderer = new ConsoleRenderer;
		if (!m_pRenderer)
		{
			//Alert("failed new Renderer!");
			return false;
		}
		//インスタンス初期化
		isSuccess = m_pRenderer->Init();
		if (!isSuccess)
		{
			SafeReleaseDelete(m_pRenderer);
		}

		//UI Scene

		//Current Scene

		return true;
	}

	void KtSystem::Release()
	{
		////Current Scene
		//if (m_pCurrentScene)
		//{
		//	m_pCurrentScene->Release();
		//	delete m_pCurrentScene;
		//	m_pCurrentScene = nullptr;
		//}

		////UI Scene
		//if (m_pUIScene)
		//{
		//	m_pUIScene->Release();
		//	delete m_pUIScene;
		//	m_pUIScene = nullptr;
		//}

		//Renderer
		SafeReleaseDelete(m_pRenderer);

	}




}	//namespace KtLib
