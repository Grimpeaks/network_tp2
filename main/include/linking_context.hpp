#pragma once

#include <iostream>
#include <map>
#include <iterator>
#include "game_object.hpp"


using networkID = uint32_t;
using ptrGameObjt = std::shared_ptr<GameObject>;

class LinkingContext
{
public:
	void AddTo_Context(ptrGameObjt gm, networkID i = -1);

	void SupprFrom_List(ptrGameObjt gm);

	std::optional<networkID> GetNetworkId(ptrGameObjt inGameObject);

	std::optional<ptrGameObjt> GetGameObject(networkID inNetworkId);
	
private:

	std::map<networkID, ptrGameObjt> idToObjptr;
	std::map<ptrGameObjt, networkID> objptrToId;
	
	int indice = 0;
	
};
