#include "KCClient.h"
#define pf [](KCClient *client, const QVariant &data)
typedef KCClient C;

const std::map<QString, C::processFunc> C::processFuncs = {
	{ "/kcsapi/api_req_member/get_incentive", 0 }, // Login

	// Global info -------------------------------------------------------------
	{ "/kcsapi/api_get_master/ship", // Ships
		pf {
			modelizeResponse(data, client->masterShips, client);
			emit client->receivedMasterShips();
		}
	},
	{ "/kcsapi/api_get_master/stype", 0 }, // Ship types
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
	{ "/kcsapi/api_get_member/ship",
		pf {
			modelizeResponse(data, client->ships, client);
			emit client->receivedPlayerShips();
		}
	},
	{ "/kcsapi/api_get_member/ship2",
	  pf {
			for(QVariant item : data.toList()) {
				QVariantMap itemMap = item.toMap();
				KCShip **ship = &client->ships[itemMap.value("api_id").toInt()];

				if(!*ship)
					*ship = new KCShip(itemMap, client, true);
				else
					(*ship)->loadFrom2(itemMap);
			}
			emit client->receivedPlayerShips();

			// TODO: handle the weird api_data_deck
		}
	},
	{ "/kcsapi/api_get_member/ship3",
	  pf {
			QVariantMap map = data.toMap();
			QVariantList shipData = map["api_ship_data"].toList();
			QVariantList fleetData = map["api_fleet_data"].toList();
			for(QVariant item : shipData) {
				QVariantMap itemMap = item.toMap();
				KCShip **ship = &client->ships[itemMap.value("api_id").toInt()];

				if(!*ship)
					*ship = new KCShip(itemMap, client, true);
				else
					(*ship)->loadFrom2(itemMap);
			}
			for(QVariant item : fleetData) {
				QVariantMap itemMap = item.toMap();
				KCFleet **fleet = &client->fleets[itemMap.value("api_id").toInt()];

				if(!*fleet)
					*fleet = new KCFleet(itemMap, client);
				else
					(*fleet)->loadFrom(itemMap);
			}
			emit client->receivedPlayerShips();
			emit client->receivedPlayerFleets();
		}
	}, // TODO
	{ "/kcsapi/api_get_member/material", 0 }, // Resources
	//  Various statuses
	{ "/kcsapi/api_get_member/deck", // Fleets
		pf {
			modelizeResponse(data, client->fleets, client);
			emit client->receivedPlayerFleets();
		}
	},
	{ "/kcsapi/api_get_member/ndock", // Dock (repair)
		pf {
			modelizeResponse(data, client->repairDocks, client);
			emit client->receivedPlayerRepairs();
		}
	},
	{ "/kcsapi/api_get_member/kdock", // Construction
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
