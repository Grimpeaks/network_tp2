#include "linking_context.hpp"


void LinkingContext::AddTo_Context(gameObjt)
{

}

void LinkingContext::SupprFrom_List(gameObjt)
{

}

void LinkingContext::AddTo_List(gameObjt g) {
	int i = indice;
	//bool trouve = false;
	//idToObjptr[i] = g;

	//if (idToObjptr::iterator it = idToObjptr.find(g) {
	idToObjptr.insert(std::pair<int, gameObjt>(i, g));
	objptrToId.insert(std::pair<gameObjt, int>(g, i));

	//}
	
}

	
