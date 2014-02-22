#include "KCClient.h"
#define pf [](KCClient *client, const QVariant &data)
typedef KCClient C;

const std::map<QString, C::processFunc> C::processFuncs = {
	// Global info -------------------------------------------------------------
	{ // Ships
		"/kcsapi/api_get_master/ship",
		pf {
			modelizeResponse(data, client->masterShips, client);
			emit client->receivedMasterShips();
		}
	},
	{ "/kcsapi/api_get_master/slotitem", 0 },	// Items
	{ "/kcsapi/api_get_master/furniture", 0 }, // Furniture
	{ "/kcsapi/api_get_master/mission", 0 }, // Expeditions
	//  Sortie maps
	{ "/kcsapi/api_get_master/mapinfo", 0 },
	{ "/kcsapi/api_get_master/mapcell", 0 },
	// ???
	{ "/kcsapi/api_get_master/maparea", 0 },

	// Member info -------------------------------------------------------------
	{ "/kcsapi/api_get_member/basic", 0 },
	{ "/kcsapi/api_get_member/record", 0 },
	//  Items
	{ "/kcsapi/api_get_member/slotitem", 0 }, // Current items
	{ "/kcsapi/api_get_member/unsetslot", 0 }, // Remove item
	{ "/kcsapi/api_get_member/useitem", 0 },
	//  Ships
	{
		"/kcsapi/api_get_member/ship",
		pf {
			modelizeResponse(data, client->ships, client);
			emit client->receivedPlayerShips();
		}
	},
	{ "/kcsapi/api_get_member/ship2", 0 }, // TODO
	{ "/kcsapi/api_get_member/ship3", 0 }, // TODO
	{ "/kcsapi/api_get_member/material", 0 }, // Resources
	//  Various statuses
	{ // Fleets
		"/kcsapi/api_get_member/deck",
		pf {
			modelizeResponse(data, client->fleets, client);
			emit client->receivedPlayerFleets();
		}
	},
	{ // Dock (repair)
		"/kcsapi/api_get_member/ndock",
		pf {
			modelizeResponse(data, client->repairDocks, client);
			emit client->receivedPlayerRepairs();
		}
	},
	{ // Construction
		"/kcsapi/api_get_member/kdock",
		pf {
			modelizeResponse(data, client->constructionDocks, client);
			emit client->receivedPlayerConstructions();
		}
	},
	//  Quests
	{ "/kcsapi/api_get_member/questlist", 0 },
	{ "/kcsapi/api_req_quest/start", 0 }, // Start tracking
	{ "/kcsapi/api_req_quest/stop", 0 }, // Stop tracking
	{ "/kcsapi/api_req_quest/clearitemget", 0 }, // Finish quest
	//  Actions
	{ "/kcsapi/api_req_kaisou/powerup", 0 }, // Modernization
	{ "/kcsapi/api_req_kaisou/remodeling", 0 },
	{ "/kcsapi/api_req_hokyu/charge", 0 }, // TODO (Resupplying)
	{ "/kcsapi/api_req_hensei/change", 0 }, // Swap out ships
	{ "/kcsapi/api_req_nyukyo/start", 0 }, // Start a bath
	{ "/kcsapi/api_req_nyukyo/speedchange", 0 }, // Buckets are cool
	{ "/kcsapi/api_req_kousyou/createship", 0 },
	{ "/kcsapi/api_req_kousyou/createship_speedchange", 0 }, // FLAME
	{ "/kcsapi/api_req_kousyou/getship", 0 }, // Finish construction
	{ "/kcsapi/api_req_kousyou/destroyship", 0 },
	{ "/kcsapi/api_req_kousyou/createitem", 0 },
	{ "/kcsapi/api_req_kousyou/destroyitem2", 0 },
	{ "/kcsapi/api_get_member/actionlog", 0 },
	//  Furniture
	{ "/kcsapi/api_req_furniture/change", 0 },
	{ "/kcsapi/api_get_member/furniture", 0 },
	//  Store
	{ "/kcsapi/api_get_master/payitem", 0 }, // Load the pay shop
	{ "/kcsapi/api_req_furniture/buy", 0 },
	// ???
	{ "/kcsapi/api_get_member/deck_port", 0 },
	{ "/kcsapi/api_get_master/useitem", 0 },

	// Battle info -------------------------------------------------------------
	//  Expeditions
	{ "/kcsapi/api_req_mission/start", 0 },
	{ "/kcsapi/api_req_mission/result", 0 },
	//  Sorties
	{ "/kcsapi/api_req_map/start", 0 }, // Start a sortie
	{ "/kcsapi/api_req_map/next", 0 }, // Next cell to go to
	{ "/kcsapi/api_req_sortie/battle", 0 },
	{ "/kcsapi/api_req_battle_midnight/battle", 0 },
	{ "/kcsapi/api_req_sortie/battleresult", 0 },
	//  Practice
	{ "/kcsapi/api_get_member/practice", 0 },
	{ "/kcsapi/api_req_member/getothersdeck", 0 },
	{ "/kcsapi/api_req_practice/battle", 0 },
	{ "/kcsapi/api_req_practice/midnight_battle", 0 },
	{ "/kcsapi/api_req_practice/battle_result", 0 },

	// Miscellaneous ------------------------------------------------------------
	{ "/kcsapi/api_auth_member/logincheck", 0 },
};
