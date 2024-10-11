#include <cstdlib>

#include "stdafx.h"
#include "MyGame.h"

#pragma warning(disable:4244)

CMyGame::CMyGame(void) :

// Each cell can contain several layers. (Exemple : G SH E represents the superposition of 1 shadow, 1 ground and 1 elevation in a single cell)
m_tileLayout
	{
		{"W", "W", "W", "W", "W", "W", "W", "W", "W", "W"},
		{"W", "F BL_G", "F L_G", "F L_G", "F L_S DU", "F L_S", "F L_S", "F L_S", "F TL_S", "W"},
		{"W", "F B_G", "G", "G", "G SH L_E GR", "SH BL_EG BL_G", "L_EG L_G", "S TL_G", "F T_S", "W"},
		{"W", "F B_G", "G", "G SH SOLE_ST", "BL_EG BL_S", "G DU", "G SH L_E", "G SOLEL_EG SOLEL_G", "F T_S", "W"},
		{"W", "F B_G", "G SH L_E GR", "BL_EG BL_S", "S", "G SH L_E DU", "BL_EG BL_G", "G T_G", "F T_S", "W"},
		{"W", "F B_G", "G SH L_E GR", "B_EG B_S", "S SH L_E", "BL_EG BL_G", "G R_G", "G TR_G", "F T_S", "W"},
		{"W", "F B_G", "G SH E", "B_EG B_S", "G SH SOLE_ST", "G SOLER_EG SOLER_G", "G", "S TR_G", "F T_S", "W"},
		{"W", "F B_G", "G SH SOLE_ST GR", "BR_EG BR_S", "R_EG R_G DU", "R_EG R_G", "S TR_G", "S", "F T_S", "W"},
		{"W", "F BR_G", "F R_S DU", "F R_S", "F R_S", "F R_S", "F R_S", "F R_S", "F TR_S", "W"},
		{"W", "W", "W", "W", "W", "W", "W", "W", "W", "W"},
	},
m_buildingLayout
	{
		{NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
		{NO_B, HOUSE, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B, NO_B , NO_B},
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
		{NO_R, NO_R, NO_R, TREE, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, TREE, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, TREE, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
	},

// The obstacle layout specifies the connections to remove from each cell in the pathfinding graph, the connections are removed anti-clockwise.
// (Exemple : "03" means the first and fourth connections are removed i.e the right and upper-left-diagonal ones)
m_obstacleLayout
	{
		{"01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567"},
		{"01234567", "01234567", "01234567", "134567", "17", "10", "701", "701", "7", "01234567"},
		{"01234567", "01234567", "01234567", "0123567", "01234567", "3457", "13457", "012345", "567", "01234567"},
		{"01234567", "", "713", "014", "375", "137", "01234567", "123457", "567", "01234567"},
		{"01234567", "3", "01234567", "345", "1357", "01234567", "357", "123", "567", "01234567"},
		{"01234567", "", "01234567", "13", "01234567", "1357", "017", "01237", "567", "01234567"},
		{"01234567", "1", "01234567", "7", "0135", "01237", "134567", "0123457", "567", "01234567"},
		{"01234567", "", "0135", "017", "70134", "701345", "701235", "34567", "5", "01234567"},
		{"01234567", "", "34", "345", "345", "345", "345", "5", "", "01234567"},
		{"01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567"},

	}
{
	m_currentTask = 0;
}

CMyGame::~CMyGame(void)
{
}

/////////////////////////////////////////////////////
// Utils

vector<string> CMyGame::split(string& s, const string& delimiter) {
	vector<string> tokens;
	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != string::npos) {
		token = s.substr(0, pos);
		tokens.push_back(token);
		s = s.substr(pos + delimiter.length());
	}
	tokens.push_back(s);

	return tokens;
}

TileType CMyGame::stringcodeToTileType(string const& inString) {
	if (inString == "NO_T") return NO_T;
	if (inString == "G") return G;
	if (inString == "T_G") return T_G;
	if (inString == "TR_G") return TR_G;
	if (inString == "TL_G") return TL_G;
	if (inString == "L_G") return L_G;
	if (inString == "R_G") return R_G;
	if (inString == "BL_G") return BL_G;
	if (inString == "BR_G") return BR_G;
	if (inString == "B_G") return B_G;
	if (inString == "SOLE_G") return SOLE_G;
	if (inString == "SOLEL_G") return SOLEL_G;
	if (inString == "SOLER_G") return SOLER_G;
	if (inString == "S") return S;
	if (inString == "T_S") return T_S;
	if (inString == "TR_S") return TR_S;
	if (inString == "TL_S") return TL_S;
	if (inString == "L_S") return L_S;
	if (inString == "R_S") return R_S;
	if (inString == "BL_S") return BL_S;
	if (inString == "BR_S") return BR_S;
	if (inString == "B_S") return B_S;
	if (inString == "SOLE_S") return SOLE_S;
	if (inString == "E") return E;
	if (inString == "L_E") return L_E;
	if (inString == "R_E") return R_E;
	if (inString == "SOLE_E") return SOLE_E;
	if (inString == "EG") return EG;
	if (inString == "T_EG") return T_EG;
	if (inString == "TR_EG") return TR_EG;
	if (inString == "TL_EG") return TL_EG;
	if (inString == "L_EG") return L_EG;
	if (inString == "R_EG") return R_EG;
	if (inString == "BL_EG") return BL_EG;
	if (inString == "BR_EG") return BR_EG;
	if (inString == "B_EG") return B_EG;
	if (inString == "SOLE_EG") return SOLE_EG;
	if (inString == "SOLEL_EG") return SOLEL_EG;
	if (inString == "SOLER_EG") return SOLER_EG;
	if (inString == "ST") return ST;
	if (inString == "L_ST") return L_ST;
	if (inString == "R_ST") return R_ST;
	if (inString == "SOLE_ST") return SOLE_ST;
	if (inString == "SH") return SH;
	if (inString == "GR") return GR;
	if (inString == "DU") return DU;
	if (inString == "W") return W;
	if (inString == "F") return F;
	return NO_T;
}

/////////////////////////////////////////////////////
// Gameplay

void CMyGame::gameLoop() 
{
	computeWorkerWaypoints();
	workersWaypointing();
}

void CMyGame::computeWorkerWaypoints() {

	// Temporarily hard coded
	CVector house = CVector(32.f + 2 * 64.f, 32.f + 1 * 64.f);
	vector<CVector> trees = { CVector(32.f + 4 * 64.f, 32.f + 7 * 64.f), CVector(32.f + 6 * 64.f, 32.f + 6 * 64.f), CVector(32.f + 1 * 64.f, 32.f + 3 * 64.f) };
	
	// If the worker is idle, adds the necessary waypoints for the next task
	if (m_waypoints.empty()) 
	{
		// Chose the new destination
		CVector destination;
		switch (m_currentTask % 4) 
		{
		case 0:
			destination = trees[0];
			break;
		case 1:
			destination = trees[1];
			break;
		case 2:
			destination = trees[2];
			break;
		case 3:
			destination = house;
			break;
		}
		m_currentTask++;

		// Use Dijkstra algorithm to add the waypoints
		int nFirst = m_pathfinder.findClosestNode(m_workers.front()->GetPos());
		int nLast = m_pathfinder.findClosestNode(destination);
		vector<int> path;
		if (m_pathfinder.dijkstra(nFirst, nLast, path))
		{
			m_pathfinder.addWaypoints(path, m_waypoints);
			m_waypoints.push_back(destination);
		}
	}
}

void CMyGame::workersWaypointing() 
{
	CWorker* pWorker = m_workers.front();

	// NPCs : follow their waypoints
	if (!m_waypoints.empty())
	{
		// If NPC not moving, start moving to the first waypoint
		if (pWorker->GetSpeed() < 1)
		{
			pWorker->SetSpeed(250);

			pWorker->SetDirection(m_waypoints.front() - pWorker->GetPosition());
			if (pWorker->GetDirection() > 10 && pWorker->GetDirection() < 180 - 10)
				pWorker->SetAnimation("walkR");
			else if (pWorker->GetDirection() < -10 && pWorker->GetDirection() > -180 + 10)
				pWorker->SetAnimation("walkL");
		}

		// Passed the waypoint ?
		CVector v = m_waypoints.front() - pWorker->GetPosition();
		if (Dot(pWorker->GetVelocity(), v) < 0)
		{
			// Stop movement
			m_waypoints.pop_front();
			if (m_waypoints.empty()) {
				pWorker->SetAnimation("idleR");
			}
			pWorker->SetVelocity(0, 0);
			pWorker->SetRotation(0);

		}
	}
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();

	gameLoop();

	// Updating sprites
	for (CSprite* pSprite : m_foamTiles)
		pSprite->Update(t);
	for (CTree* pTree : m_trees)
		pTree->Update(t);
	for (CWorker* pWorker : m_workers)
		pWorker->Update(t);
}

void CMyGame::OnDraw(CGraphics* g)
{

	m_waterTiles.for_each(&CSprite::Draw, g);
	m_foamTiles.for_each(&CSprite::Draw, g);
	m_tiles.for_each(&CSprite::Draw, g);

	// Temporary solution for layer bug
	if ((m_workers.front()->GetX() > 4 * 64.f && m_workers.front()->GetY() > 8 * 64.f && m_workers.front()->GetX() < 8 * 64.f && m_workers.front()->GetY() < 9 * 64.f)
		|| (m_workers.front()->GetX() > 7 * 64.f && m_workers.front()->GetY() > 7 * 64.f && m_workers.front()->GetX() < 8 * 64.f && m_workers.front()->GetY() < 8 * 64.f)
		|| (m_workers.front()->GetX() > 4 * 64.f && m_workers.front()->GetY() > 8 * 64.f && m_workers.front()->GetX() < 6 * 64.f && m_workers.front()->GetY() < 9 * 64.f) 
		|| (m_workers.front()->GetX() > 1 * 64.f && m_workers.front()->GetY() > 3 * 64.f && m_workers.front()->GetX() < 2 * 64.f && m_workers.front()->GetY() < 6 * 64.f)
		|| (m_workers.front()->GetX() > 2 * 64.f && m_workers.front()->GetY() > 3 * 64.f && m_workers.front()->GetX() < 3 * 64.f && m_workers.front()->GetY() < 4 * 64.f)
	   )
	{
		m_workers.for_each(&CSprite::Draw, g);
		m_trees.for_each(&CSprite::Draw, g);
	}
	else 
	{
		m_trees.for_each(&CSprite::Draw, g);
		m_workers.for_each(&CSprite::Draw, g);
	}

	m_buildings.for_each(&CSprite::Draw, g);
	m_ui.for_each(&CSprite::Draw, g);

	// Change boolean values here for debugging
	// Draw Dijkstra graph
	if (false) {
		m_pathfinder.draw(g);
	}
	// Draw grid
	if (false) {
		for (int i = 0; i < 10; i++) {
			g->DrawLine(CVector(i * 64.f, 10 * 64.f), CVector(i * 64.f, 0), CColor::Black());
			g->DrawLine(CVector(10 * 64.f, i * 64.f), CVector(0, i * 64.f), CColor::Black());
		}
	}
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
			vector<string> layers = split(m_tileLayout[x][y], " ");
			for (string layer : layers) {
				switch (stringcodeToTileType(layer)) {
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
				case SOLE_G:
					m_tiles.push_back(GROUND(3, 0, x, y));
					break;
				case SOLEL_G:
					m_tiles.push_back(GROUND(0, 0, x, y));
					break;
				case SOLER_G:
					m_tiles.push_back(GROUND(2, 0, x, y));
					break;
				case S:
					m_tiles.push_back(GROUND(6, 2, x, y));
					break;
				case T_S:
					m_tiles.push_back(GROUND(6, 3, x, y));
					break;
				case B_S:
					m_tiles.push_back(GROUND(6, 1, x, y));
					break;
				case L_S:
					m_tiles.push_back(GROUND(5, 2, x, y));
					break;
				case R_S:
					m_tiles.push_back(GROUND(7, 2, x, y));
					break;
				case TL_S:
					m_tiles.push_back(GROUND(5, 3, x, y));
					break;
				case TR_S:
					m_tiles.push_back(GROUND(7, 3, x, y));
					break;
				case BL_S:
					m_tiles.push_back(GROUND(5, 1, x, y));
					break;
				case BR_S:
					m_tiles.push_back(GROUND(7, 1, x, y));
					break;
				case SOLE_S:
					m_tiles.push_back(GROUND(8, 0, x, y));
					break;
				case E:
					m_tiles.push_back(ELEVATION(1, 2, x, y));
					break;
				case L_E:
					m_tiles.push_back(ELEVATION(0, 2, x, y));
					break;
				case R_E:
					m_tiles.push_back(ELEVATION(2, 2, x, y));
					break;
				case SOLE_E:
					m_tiles.push_back(ELEVATION(3, 2, x, y));
					break;
				case EG:
					m_tiles.push_back(ELEVATION(1, 6, x, y));
					break;
				case T_EG:
					m_tiles.push_back(ELEVATION(1, 7, x, y));
					break;
				case B_EG:
					m_tiles.push_back(ELEVATION(1, 5, x, y));
					break;
				case L_EG:
					m_tiles.push_back(ELEVATION(0, 6, x, y));
					break;
				case R_EG:
					m_tiles.push_back(ELEVATION(2, 6, x, y));
					break;
				case TL_EG:
					m_tiles.push_back(ELEVATION(0, 7, x, y));
					break;
				case TR_EG:
					m_tiles.push_back(ELEVATION(2, 7, x, y));
					break;
				case BL_EG:
					m_tiles.push_back(ELEVATION(0, 5, x, y));
					break;
				case BR_EG:
					m_tiles.push_back(ELEVATION(2, 5, x, y));
					break;
				case SOLE_EG:
					m_tiles.push_back(ELEVATION(3, 3, x, y));
					break;
				case SOLEL_EG:
					m_tiles.push_back(ELEVATION(0, 3, x, y));
					break;
				case SOLER_EG:
					m_tiles.push_back(ELEVATION(2, 3, x, y));
					break;
				case ST:
					m_tiles.push_back(ELEVATION(1, 0, x, y));
					break;
				case L_ST:
					m_tiles.push_back(ELEVATION(0, 0, x, y));
					break;
				case R_ST:
					m_tiles.push_back(ELEVATION(2, 0, x, y));
					break;
				case SOLE_ST:
					m_tiles.push_back(ELEVATION(3, 0, x, y));
					break;
				case SH:
					m_tiles.push_back(SHADOW(x, y));
					break;
				case GR:
					m_tiles.push_back(GROUND(4, 3, x, y));
					break;
				case DU:
					m_tiles.push_back(GROUND(9, 3, x, y));
					break;
				case W:
					m_waterTiles.push_back(WATER(x, y));
					break;
				case F:
					{
					CSprite *foamSprite = new CSprite(32.f + x * 64.f, 32.f + y * 64.f, 0, 0, 0);
					foamSprite->LoadAnimation(new CGraphics(REPOSITORY + "/game/images/assets/Terrain/Water/Foam/Foam.png"), "foam", CSprite::Sheet(8, 1).Row(0).From(0).To(7));
					foamSprite->SetAnimation("foam");
					m_foamTiles.push_back(foamSprite);
					}
					break;
				default:
					break;
				}
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
				m_trees.push_back(new CTree(x * 64.f + 64.f, y * 64.f + 81.f, new CGraphics(REPOSITORY + "/game/images/assets/Resources/Trees/Tree.png"), 0));
				break;
			default:
				break;
			}
		}

	// Create a single worker (temporary)
	m_workers.push_back(new CWorker(3 * 64.f + 32.f, 2 * 64.f + 32.f,
		new CGraphics(REPOSITORY + "/game/images/assets/Factions/Knights/Troops/Pawn/Red/Pawn_Red_Left.png"),
		new CGraphics(REPOSITORY + "/game/images/assets/Factions/Knights/Troops/Pawn/Red/Pawn_Red_Right.png"),
		0));

	// Create UI
	// m_ui.push_back(new CSprite(320.f + 64.f - 14.f, 32.f + 6.f, new CGraphics(REPOSITORY + "/game/images/assets/UI/Ribbons/Ribbon_Blue_Connection_Left.png"), 0));
	// m_ui.push_back(new CSprite(320.f, 32.f + 10.f, new CGraphics(REPOSITORY + "/game/images/assets/UI/Buttons/Button_Blue.png"), 0));

	// Pathfinding graph initialization
	m_pathfinder.setObstacles(m_obstacleLayout);
	m_pathfinder.initialize();

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
