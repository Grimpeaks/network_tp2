#include "linking_context.hpp"

// Question 3 et 5, lors de l'appel de la fonction, si on pr�cise le param�tre i, on le stock dans la map en tant que networkId. Sinon on en cr�� un nouveau
void LinkingContext::AddTo_Context(gameObjt gm, networkID i)
{
	if(i == -1)
	{
		i = indice + 1;
		this->indice += 1;

		while (idToObjptr.find(i) != idToObjptr.end())
		{
			i += 1;			
		}
	}
	idToObjptr.insert(std::pair<networkID, gameObjt>(i, gm));
	objptrToId.insert(std::pair<gameObjt, networkID>(gm, i));
	}
 
void LinkingContext::SupprFrom_List(gameObjt gm)
{
	idToObjptr.erase(objptrToId.at(gm));
	objptrToId.erase(gm);
	this->indice -= 1;
}

std::optional<networkID> LinkingContext::GetNetworkId(gameObjt inGameObject)
{
	auto res = objptrToId.find(inGameObject);

	if (res != objptrToId.end()) 
	{ 
		return res->second; 
	}
	return {};
}

	
std::optional<gameObjt> LinkingContext::GetGameObject(networkID inNetworkId)
{
	auto res = idToObjptr.find(inNetworkId);

	if (res != idToObjptr.end())
	{
		return res->second;
	}

	return {};	
}