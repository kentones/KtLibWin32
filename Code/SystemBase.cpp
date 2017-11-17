#include "pch.h"

#include "SystemBase.h"
#include "SceneBase.h"
#include "common_Template.h"
#include "Renderer_DirectX11.h"

namespace KtLib
{
	//============================================================================
	//	Public
	//============================================================================
	KtSystem* KtSystem::s_pInstance = nullptr;

	//�V���O���g���쐬��������
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

	//�V���O���g������
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
		//�^�C�}�[�X�V

		//���͍X�V

		//�O����

		//�V�[���X�V
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

		//�㏈��
		//�Փ˔���X�V�H
		//�Փˉ����H

		//�V�[���J�ڃ`�F�b�N

	}

	void KtSystem::Render()const
	{
		//Scene�`�悷��GameObject��Renderer�ɓo�^����
		
		//if (m_pCurrentScene)
		//{
		//	m_pCurrentScene->PushToRenderLayer();
		//}
		//if (m_pUtilityScene)
		//{
		//	m_pUtilityScene->PushToRenderLayer();
		//}
		
		//�`�悷��
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
		//��d�쐬�h�~
		SafeReleaseDelete(m_pRenderer);

		//�C���X�^���X�쐬
		m_pRenderer = new KtRenderer;
		if (!m_pRenderer)
		{
			//Alert("failed new Renderer!");
			return false;
		}
		//�C���X�^���X������
		isSuccess = m_pRenderer->Init(window, width, height);
		if (!isSuccess)
		{
			SafeReleaseDelete(m_pRenderer);
		}

		//Utility Scene
		SafeReleaseDelete(m_pUtilityScene);

		//Current Scene
		SafeReleaseDelete(m_pCurrentScene);

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
