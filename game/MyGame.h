#pragma once

#include <string>

#include "Tree.h"
#include "Worker.h"
#include "Pathfinding.h"

const string REPOSITORY = "C:/Users/julie/source/repos/ai-assignement";

// TODO : Add rocks and bridges
#define GROUND(col, row, x, y) new CSprite(x * 64.f + 32.f, y * 64.f + 32.f, new CGraphics(REPOSITORY + "/game/images/assets/Terrain/Ground/Tilemap_Flat.png", 10, 4, col, row), 0)
#define ELEVATION(col, row, x, y) new CSprite(x * 64.f + 32.f, y * 64.f + 32.f, new CGraphics(REPOSITORY + "/game/images/assets/Terrain/Ground/Tilemap_Elevation.png", 4, 8, col, row), 0)
#define SHADOW(x, y) new CSprite(x * 64.f + 32.f, y * 64.f + 32.f, new CGraphics(REPOSITORY + "/game/images/assets/Terrain/Ground/Shadows.png"), 0)
#define WATER(x, y) new CSprite(x * 64.f + 32.f, y * 64.f + 32.f, new CGraphics(REPOSITORY + "/game/images/assets/Terrain/Water/Water.png"), 0)
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
	SOLE_G,
	SOLEL_G,
	SOLER_G,
	S,
	T_S,
	TR_S,
	TL_S,
	L_S,
	R_S,
	BL_S,
	BR_S,
	B_S,
	SOLE_S,
	E,
	L_E,
	R_E,
	SOLE_E,
	EG,
	T_EG,
	TR_EG,
	TL_EG,
	L_EG,
	R_EG,
	BL_EG,
	BR_EG,
	B_EG,
	SOLE_EG,
	SOLEL_EG,
	SOLER_EG,
	ST,
	L_ST,
	R_ST,
	SOLE_ST,
	SH,
	GR,
	DU,
	W,
	F
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
	float m_accessibilityLayout[10][10];
	string m_obstacleLayout[10][10];

	CSpriteList m_tiles;
	CSpriteList m_waterTiles;
	CSpriteList m_foamTiles;
	CSpriteList m_buildings;
	CTreeList m_trees;
	CWorkerList m_workers;
	CSpriteList m_ui;

	Pathfinding m_pathfinder;
	list<CVector> m_waypoints;

	int m_currentTask;

public:
	CMyGame(void);
	~CMyGame(void);

	// Utils
	vector<string> split(string& s, const string& delimiter);
	TileType stringcodeToTileType(string const& inString);

	// Gameplay
	void gameLoop();
	void computeWorkerWaypoints();
	void workersWaypointing();

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
