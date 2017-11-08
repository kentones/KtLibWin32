//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include "Code\SystemBase.h"

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;


// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    

	// ‰Šú‰»
	KtLib::KtSystem::Create(window, width, height);
}

// KtSystemƒVƒ“ƒOƒ‹ƒgƒ“íœ
void Game::DestoryKtSystem()
{
	KtLib::KtSystem::Destory();
}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
	KtLib::KtSystem::GetInstance()->Update(elapsedTime);

}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    // TODO: Add your rendering code here.
	KtLib::KtSystem::GetInstance()->Render();

}



// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
	KtLib::KtSystem::GetInstance()->OnActivated();

}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
	KtLib::KtSystem::GetInstance()->OnDeactivated();
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
	KtLib::KtSystem::GetInstance()->OnSuspending();
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
	KtLib::KtSystem::GetInstance()->OnResuming();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    // TODO: Game window is being resized.
	KtLib::KtSystem::GetInstance()->OnWindowSizeChanged(width, height);
}

