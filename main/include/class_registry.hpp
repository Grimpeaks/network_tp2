#pragma once
#include <iostream>
#include <map>
#include "game_object.hpp"

class Classregistry
{
public:
	static Classregistry* get_Instance();
	GameObject* Create(ReplicationClassID id);
	template < typename T >
	void RegistreClasse(T theClass);
private:
	static Classregistry* m_registre;
	Classregistry();
	std::map <ReplicationClassID, std::function<GameObject*()> > m_map_id_TO_ptrfunction;
};
