#include "pch.h"

#include "RendererBase.h"

namespace KtLib
{
	void KtRendererBase::PushToRenderLayer(KtRenderableBase* pRenderable, eRenderLayer eLayer)
	{
		m_RenderLayer[eLayer].PushBack(pRenderable);
	}


}	//namespace KtLib