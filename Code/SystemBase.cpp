#include "pch.h"

#include "SystemBase.h"
#include "common_Template.h"
#include "RendererBase.h"
#include "Renderer_DirectX11.h"

namespace KtLib
{
	//============================================================================
	//	Public
	//============================================================================
	KtSystem* KtSystem::s_pInstance = nullptr;

	//シングルトン作成かつ初期化
	bool KtSystem::Create(HWND window, int width, int height)
	{
		if (s_pInstance)
		{
			s_pInstance->Release();
			delete s_pInstance;
			s_pInstance = nullptr;
		}
		s_pInstance = new KtSystem;
		if (!s_pInstance)	{	return false;	}

		return s_pInstance->Init(window, width, height);
	}

	//シングルトン消滅
	void KtSystem::Destory()
	{
		if (s_pInstance)
		{
			s_pInstance->Release();
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}

	void KtSystem::Update(float elapsedTime)
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
		//Scene描画するGameObjectをRendererに登録する
		/*
		if (m_pCurrentScene)
		{
			m_pCurrentScene->PushToRenderStack();
		}
		if (m_pUIScene)
		{
			m_pUIScene->PushToRenderStack();
		}
		*/
		//描画する
		if(m_pRenderer)
		{
			m_pRenderer->Render();
		}
	}

	void KtSystem::OnActivated()
	{
		if (m_pRenderer)
			m_pRenderer->OnActivated();
	}
	void KtSystem::OnDeactivated()
	{
		if (m_pRenderer)
			m_pRenderer->OnDeactivated();
	}
	void KtSystem::OnSuspending()
	{
		if (m_pRenderer)
			m_pRenderer->OnSuspending();
	}
	void KtSystem::OnResuming()
	{
		if (m_pRenderer)
			m_pRenderer->OnResuming();
	}
	void KtSystem::OnWindowSizeChanged(int width, int height)
	{
		if (m_pRenderer)
			m_pRenderer->OnWindowSizeChanged(width, height);
	}

	//============================================================================
	//	Private
	//============================================================================

	bool KtSystem::Init(HWND window, int width, int height)
	{
		bool isSuccess = false;

		//Renderer
		//二重作成防止
		SafeReleaseDelete(m_pRenderer);

		//インスタンス作成
		m_pRenderer = new RendererDirectX11;
		if (!m_pRenderer)
		{
			//Alert("failed new Renderer!");
			return false;
		}
		//インスタンス初期化
		isSuccess = m_pRenderer->Init(window, width, height);
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
