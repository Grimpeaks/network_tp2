#pragma once

#include <iostream>
#include <map>
#include <iterator>
#include "game_object.hpp"


using networkID = uint32_t;
using gameObjt = std::shared_ptr<GameObject>;

class LinkingContext
{
public:
	void AddTo_Context(gameObjt gm, networkID i = -1);

	void SupprFrom_List(gameObjt gm);

	std::optional<networkID> GetNetworkId(gameObjt inGameObject);

	std::optional<gameObjt> GetGameObject(networkID inNetworkId);
	
private:

	std::map<networkID, gameObjt> idToObjptr;
	std::map<gameObjt, networkID> objptrToId;
	
	int indice = 0;
	

	
	

};
