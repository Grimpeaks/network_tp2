#pragma once
#include <iostream>
#include <map>
#include "game_object.hpp"

template < typename T >
class ClassRegistry
{
public:
	static ClassRegistry get_Class_Registry();
	GameObject Create(ReplicationClassID);
	void RegistreClasse(T);
private:
	static ClassRegistry m_classregistry ;
	ClassRegistry();
	std::map <ReplicationClassID, std::function<GameObject()> > m_map_id_TO_ptrfunction;
	
	
};