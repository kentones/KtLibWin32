#pragma once

namespace KtLib
{
	class KtRendererBase;
	class KtSceneBase;

	class KtSystem
	{
	public:
		//シングルトン
		static bool			Create();
		static void			Destory();
		static KtSystem*	GetInstance() { return s_pInstance; }

		void Update();
		void Render()const;

		//Windows コントロール関連
		void OnActivated();		//Game is becoming active window
		void OnDeactivated();	//Game is becoming background window
		void OnSuspending();	//Game is being power-suspended (or minimized)
		void OnResuming();		//Game is being power-resumed (or returning from minimize)
		void OnWindowSizeChanged(int width, int height);
		void InitWindowSizeIndependentObjects();	// void Game::CreateDevice()
		void InitWindowSizeDependentObjects();		// void Game::CreateResources()
		void OnDeviceLost();	//Add Direct3D resource cleanup here


		//インスタンス取得関数
		KtRendererBase*	GetRenderer() { return m_pRenderer; }

	private:
		KtSystem() : m_pRenderer(nullptr), m_pCurrentScene(nullptr), m_pUIScene(nullptr) {}
		~KtSystem() {}
		bool Init();
		void Release();

	

		static KtSystem* s_pInstance;

		// Debug

		// Renderer
		KtRendererBase*		m_pRenderer;

		// Time

		// Input Controller

		// Resource

		// Collision

		// GameKeeper

		// Scene
		KtSceneBase*		m_pCurrentScene;
		KtSceneBase*		m_pUIScene;

		// GameObject



	};












}	//namespace KtLib

