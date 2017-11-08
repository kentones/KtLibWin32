#include "SystemBase.h"
#include "common_Template.h"

//#include "Renderer.h"

namespace KtLib
{
	//============================================================================
	//	Public
	//============================================================================

	//�V���O���g���쐬��������
	bool KtSystem::Create()
	{
		SafeReleaseDelete(s_pInstance);

		s_pInstance = new KtSystem;
		if (!s_pInstance)	{	return false;	}

		return s_pInstance->Init();
	}

	//�V���O���g������
	void KtSystem::Destory()
	{
		SafeReleaseDelete(s_pInstance);
	}

	void KtSystem::Update()
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
		//�V�[���`��
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
		//��d�쐬�h�~
		SafeReleaseDelete(m_pRenderer);

		//�C���X�^���X�쐬
		m_pRenderer = new ConsoleRenderer;
		if (!m_pRenderer)
		{
			//Alert("failed new Renderer!");
			return false;
		}
		//�C���X�^���X������
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
