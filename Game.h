//
// Game.h
//

#pragma once

#include "StepTimer.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    // Initialization and management
    void Initialize(HWND window, int width, int height);
	void DestoryKtSystem();

    // Basic game loop
    void Tick();

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowSizeChanged(int width, int height);


private:

    void Update(DX::StepTimer const& timer);
    void Render();

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;
};