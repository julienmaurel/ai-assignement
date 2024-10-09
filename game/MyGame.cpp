#include <cstdlib>

#include "stdafx.h"
#include "MyGame.h"

#pragma warning(disable:4244)

CMyGame::CMyGame(void) :

// Each cell can contain several layers. (Exemple : S G S_E represents the superposition of 1 shadow, 1 ground and 1 elevation in a single cell)
m_tileLayout
	{
		{"BL_G", "L_G", "L_G", "L_G", "L_G", "L_G", "L_G", "L_G", "L_G", "TL_G"},
		{"B_G", "G", "G", "G", "G", "G", "G", "G", "G", "T_G"},
		{"B_G", "G", "G", "G", "G", "G", "G", "G", "G", "T_G"},
		{"B_G", "G", "G", "G", "G", "G", "G", "G", "G", "T_G"},
		{"B_G", "G", "G", "G", "G", "G", "G", "G", "G", "T_G"},
		{"B_G", "G", "G", "G", "S G S_E", "G S_EG", "G", "G", "G", "T_G"},
		{"B_G", "G", "G", "G", "G", "G", "G", "G", "G", "T_G"},
		{"B_G", "G", "G", "G", "G", "G", "G", "G", "G", "T_G"},
		{"B_G", "G", "G", "G", "G", "G", "G", "G", "G", "T_G"},
		{"BR_G", "R_G", "R_G", "R_G", "R_G", "R_G", "R_G", "R_G", "R_G", "TR_G"}
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
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, TREE, NO_R, NO_R},
		{NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R, NO_R},
	},

// The obstacle layout specifies the connections to remove from each cell in the pathfinding graph, the connections are removed anti-clockwise.
// (Exemple : "03" means the first and fourth connections are removed i.e the right and upper-left-diagonal ones)
m_obstacleLayout
	{
		{"01234567", "01234567", "01234567", "67", "", "", "", "", "", ""},
		{"01234567", "01234567", "01234567", "56", "", "", "", "", "", ""},
		{"34", "345", "45", "5", "", "", "", "", "", ""},
		{"", "", "", "", "", "", "", "", "", ""},
		{"", "", "", "1", "01", "07", "7", "", "", ""},
		{"", "", "", "2", "01234567", "01234567", "6", "", "", ""},
		{"", "", "", "3", "34", "45", "5", "", "", ""},
		{"", "", "", "", "", "", "", "", "", ""},
		{"", "", "", "", "", "", "", "", "", ""},
		{"", "", "", "", "", "", "", "", "", ""},
	}
{
}

CMyGame::~CMyGame(void)
{
	m_cnt = 0;
	m_money = 10;
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
	if (inString == "S_E") return S_E;
	if (inString == "S_G") return S_G;
	if (inString == "S_EG") return S_EG;
	if (inString == "S") return S;
	return NO_T;
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();

	// NPCs : follow their waypoints
	for (CWorker* pWorker : m_workers) {
		if (!m_waypoints.empty())
		{
			// If NPC not moving, start moving to the first waypoint
			if (pWorker->GetSpeed() < 1)
			{
				pWorker->SetSpeed(250);
				
				pWorker->SetDirection(m_waypoints.front() - pWorker->GetPosition());
				if ((pWorker->GetDirection() > 0 && pWorker->GetDirection() < 90) || (pWorker->GetDirection() < 0) && (pWorker->GetDirection() > -90))
					pWorker->SetAnimation("walkR");
				else
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

	for (CTree* pTree : m_trees)
		pTree->Update(t);
	for (CWorker* pWorker : m_workers)
		pWorker->Update(t);
}

void CMyGame::OnDraw(CGraphics* g)
{
	m_tiles.for_each(&CSprite::Draw, g);
	m_workers.for_each(&CSprite::Draw, g);
	m_buildings.for_each(&CSprite::Draw, g);
	m_trees.for_each(&CSprite::Draw, g);
	m_ui.for_each(&CSprite::Draw, g);

	// Change boolean values here for debugging
	// Draw Dijkstra graph
	if (true) {
		m_pathfinder.draw(g);
	}
	// Draw grid
	if (true) {
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
				case S_G:
					m_tiles.push_back(GROUND(3, 0, x, y));
					break;
				case S_E:
					m_tiles.push_back(ELEVATION(3, 2, x, y));
					break;
				case S_EG:
					m_tiles.push_back(ELEVATION(3, 3, x, y));
					break;
				case S:
					m_tiles.push_back(SHADOW(x, y));
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
	m_workers.push_back(new CWorker(2 * 64.f + 32.f, 1 * 64.f + 32.f,
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
	if (sym == SDLK_SPACE) {
		// PauseGame();

		vector<NODE> graph = m_pathfinder.m_graph;
		m_cnt++;
		CVector destination;
		if (m_cnt % 2 == 1) 
		{
			destination = CVector(32.f + 8 * 64.f, 32.f + 7 * 64.f);
		}
		else {
			destination = CVector(32.f + 2 * 64.f, 32.f + 1 * 64.f);
		}
		
		// Find the first node : the closest to the NPC
		vector<NODE>::iterator iFirst =
			min_element(graph.begin(), graph.end(), [this](NODE& n1, NODE& n2) -> bool {
				return Distance(n1.pos, m_workers.front()->GetPos()) < Distance(n2.pos, m_workers.front()->GetPos());
			});
		int nFirst = iFirst - graph.begin();

		// Find the last node : the closest to the destination
		vector<NODE>::iterator iLast =
			min_element(graph.begin(), graph.end(), [destination](NODE& n1, NODE& n2) -> bool {
				return Distance(n1.pos, destination) < Distance(n2.pos, destination);
			});
		int nLast = iLast - graph.begin();

		// call the path finding algorithm to complete the waypoints
		vector<int> path;
		if (m_pathfinder.dijkstra(nFirst, nLast, path)) 
		{
			for (int i : path)
				m_waypoints.push_back(m_pathfinder.m_graph[i].pos);
			m_waypoints.push_back(destination);
		}
	}
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
