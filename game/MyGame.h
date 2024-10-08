#pragma once

#include <string>

#include "Tree.h"
#include "Worker.h"
#include "Pathfinding.h"

const string REPOSITORY = "C:/Users/julie/source/repos/ai-assignement";

#define GROUND(col, row, x, y) new CSprite(x * 64.f + 32.f, y * 64.f + 32.f, new CGraphics(REPOSITORY + "/game/images/assets/Terrain/Ground/Tilemap_Flat.png", 10, 4, col, row), 0)
#define ELEVATION(col, row, x, y) new CSprite(x * 64.f + 32.f, y * 64.f + 32.f, new CGraphics(REPOSITORY + "/game/images/assets/Terrain/Ground/Tilemap_Elevation.png", 4, 8, col, row), 0)
#define SHADOW(x, y) new CSprite(x * 64.f + 32.f, y * 64.f + 32.f, new CGraphics(REPOSITORY + "/game/images/assets/Terrain/Ground/Shadows.png"), 0)
enum TileType {
	NO_T,
	G,
	T_G,
	TR_G,
	TL_G,
	L_G,
	R_G,
	BL_G,
	BR_G,
	B_G,
	S_E,
	S_G,
	S_EG,
	S,
};

enum BuildingType {
	NO_B,
	HOUSE,
};

enum ResourceType {
	NO_R,
	TREE,
};

class CMyGame : public CGame
{
	string m_tileLayout[10][10];
	BuildingType m_buildingLayout[10][10];
	ResourceType m_resourceLayout[10][10];
	bool m_obstacleLayout[10][10];

	CSpriteList m_tiles;
	CSpriteList m_buildings;
	CTreeList m_trees;
	CWorkerList m_workers;
	CSpriteList m_ui;

	Pathfinding m_pathfinder;
	list<CVector> m_waypoints;//[1]

	int m_money;

	string m_testing;
	int m_cnt;

public:
	CMyGame(void);
	~CMyGame(void);

	// Utils
	vector<string> split(string& s, const string& delimiter);
	TileType stringcodeToTileType(string const& inString);

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
