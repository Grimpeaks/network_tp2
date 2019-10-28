#pragma once
#include <iostream>
#include <map>
#include "game_object.hpp"

class Classregistry
{
public:
	Classregistry() = default;
	static Classregistry* get_Instance();
	GameObject* Create(ReplicationClassID id);

	template < typename T >
	void RegisterClasse()
	{
		this->m_map_id_TO_ptrfunction.insert(std::pair<ReplicationClassID, std::function<GameObject * ()>>(T::mClassID, T::CreateInstance));
	}

private:
	static Classregistry* m_registre;
	std::map <ReplicationClassID, std::function<GameObject * ()>> m_map_id_TO_ptrfunction;
};
