#pragma once

namespace KtLib
{
	class KtSceneBase
	{
	public:

		virtual bool Setup()				= 0;
		virtual bool Init()					= 0;
		virtual void Release()				= 0;
		virtual void Update()				= 0;
		virtual void PushToRenderLayer()	= 0;

	private:


	};

	//�@�\�V�[��
	//SceneStageEditor
	//SceneModelViewer
	//SceneTest
	//SceneParticleEditor(EmitEditor + ParticleEditor)
	//ScenePolyLineEditor
	//SceneTerrainEditor
	//SceneGameObjectEditor
	//ScenePathEditor

	//�v���C�V�[��
	//SceneStageLoader
	//SceneUI
	//SceneTitle
	//SceneResult
	//SceneTutorial
	//SceneCutInAnimation...

	class SceneTest : public KtSceneBase
	{
	public:
		bool Setup()override;
		bool Init()override;
		void Release()override;
		void Update()override;
		void PushToRenderLayer()override;

	private:

	};
	/*
	class SceneXXX : public KtSceneBase
	{
	public:
		bool Setup()override;
		bool Init()override;
		void Release()override;
		void Update()override;
		void PushToRenderLayer()override;

	private:

	};
	*/


}	//namespace KtLib
