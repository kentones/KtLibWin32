#pragma once
#include <windef.h>

namespace KtLib
{
	class KtRendererBase;
	class KtSceneBase;

	class KtSystem
	{
	public:
		//シングルトン
		static bool			Create(HWND window, int width, int height);
		static void			Destory();
		static KtSystem*	GetInstance() { return s_pInstance; }

		void Update(float elapsedTime);
		void Render()const;

		//Windows コントロール関連
		void OnActivated();		//Game is becoming active window
		void OnDeactivated();	//Game is becoming background window
		void OnSuspending();	//Game is being power-suspended (or minimized)
		void OnResuming();		//Game is being power-resumed (or returning from minimize)
		void OnWindowSizeChanged(int width, int height);


		//インスタンス取得関数
		KtRendererBase*	GetRenderer() { return m_pRenderer; }

	private:
		KtSystem() : m_pRenderer(nullptr), m_pCurrentScene(nullptr), m_pUtilityScene(nullptr) {}
		~KtSystem() {}
		bool Init(HWND window, int width, int height);
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
		KtSceneBase*		m_pUtilityScene;

		// GameObject



	};












}	//namespace KtLib

