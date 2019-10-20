#pragma once

#include <iostream>
#include <map>
#include <iterator>
#include "game_object.hpp"


using idObjet = int;
using gameObjt = std::shared_ptr<GameObject>;

class LinkingContext
{
public:
	
	
private:
	std::map<idObjet, gameObjt> idToObjptr;
	std::map<gameObjt, idObjet> objptrToId;
	int indice = idToObjptr.size + 1;

	void AddTo_Context(gameObjt);

	void SupprFrom_List(gameObjt);

	void AddTo_List(gameObjt);
	

};
