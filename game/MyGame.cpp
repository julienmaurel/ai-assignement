#include <cstdlib>

#include "stdafx.h"
#include "MyGame.h"

#pragma warning(disable:4244)

CMyGame::CMyGame(void) :
	m_tileLayout 
	{
		{BL_G, L_G, L_G, L_G, L_G, L_G, L_G, L_G, L_G, TL_G},
		{B_G, G, G, G, G, G, G, G, G, T_G},
		{B_G, G, G, G, G, G, G, G, G, T_G},
		{B_G, G, G, G, G, G, G, G, G, T_G},
		{B_G, G, G, G, G, G, G, G, G, T_G},
		{B_G, G, G, G, G, G, G, G, G, T_G},
		{B_G, G, G, G, G, G, G, G, G, T_G},
		{B_G, G, G, G, G, G, G, G, G, T_G},
		{B_G, G, G, G, G, G, G, G, G, T_G},
		{BR_G, R_G, R_G, R_G, R_G, R_G, R_G, R_G, R_G, TR_G}
	},
	m_buildingLayout
	{
		{HOUSE, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
		{NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
		{NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
		{NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
		{NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
		{NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
		{NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
		{NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
		{NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
		{NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B}
	},
	m_resourceLayout
	{
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, TREE, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
	},
	m_obstacleLayout
	{
		{true, true, true, false, false, false, false, false, false, false},
		{true, true, true, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, true, true, true},
		{false, false, false, false, false, false, false, true, true, true},
		{false, false, false, false, false, false, false, true, true, true},
	}
{
}

CMyGame::~CMyGame(void)
{
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();
	for (CTree* pTree : m_trees)
		pTree->Update(t);
}

void CMyGame::OnDraw(CGraphics* g)
{
	m_tiles.for_each(&CSprite::Draw, g);
	m_buildings.for_each(&CSprite::Draw, g);
	m_trees.for_each(&CSprite::Draw, g);
	m_ui.for_each(&CSprite::Draw, g);

	// *g << font("ANCIENT.ttf", 40) << color(CColor::White()) << xy(355.f, 30.f) << m_money << endl;
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
	// Create Tiles
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			switch (m_tileLayout[x][y]) {
				case G:
					m_tiles.push_back(GROUND(1, 2, x, y));
					break;
				case T_G:
					m_tiles.push_back(GROUND(1, 3, x, y));
					break;
				case B_G:
					m_tiles.push_back(GROUND(1, 1, x, y));
					break;
				case L_G:
					m_tiles.push_back(GROUND(0, 2, x, y));
					break;
				case R_G:
					m_tiles.push_back(GROUND(2, 2, x, y));
					break;
				case TL_G:
					m_tiles.push_back(GROUND(0, 3, x, y));
					break;
				case TR_G:
					m_tiles.push_back(GROUND(2, 3, x, y));
					break;
				case BL_G:
					m_tiles.push_back(GROUND(0, 1, x, y));
					break;
				case BR_G:
					m_tiles.push_back(GROUND(2, 1, x, y));
					break;
				default:
					break;
			}
		}

	// Create buildings
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			switch (m_buildingLayout[x][y]) {
			case HOUSE:
				m_buildings.push_back(new CSprite(x * 64.f + 64.f, y * 64.f + 81.f, new CGraphics(REPOSITORY + "/game/images/assets/Factions/Knights/Buildings/House/House_Red.png"), 0));
				break;
			default:
				break;
			}
		}
	
	// Create resources
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			switch (m_resourceLayout[x][y]) {
			case TREE:
				m_trees.push_back(new CTree(x * 64.f + 81.f, y * 64.f + 81.f, new CGraphics(REPOSITORY + "/game/images/assets/Resources/Trees/Tree.png"), 0));
				break;
			default:
				break;
			}
		}

	// Create UI
	// m_ui.push_back(new CSprite(320.f + 64.f - 14.f, 32.f + 6.f, new CGraphics(REPOSITORY + "/game/images/assets/UI/Ribbons/Ribbon_Blue_Connection_Left.png"), 0));
	// m_ui.push_back(new CSprite(320.f, 32.f + 10.f, new CGraphics(REPOSITORY + "/game/images/assets/UI/Buttons/Button_Blue.png"), 0));
	
	// Core values
	// m_money = 10;
}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{
	StartGame();	// exits the menu mode and starts the game mode
}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

// called when the game is over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}

/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
