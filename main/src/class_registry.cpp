#include "class_registry.hpp"
Classregistry* Classregistry::m_registre = nullptr;

Classregistry* Classregistry::get_Instance()
{
	if (m_registre == nullptr) {
		m_registre = new Classregistry();
	}
	return m_registre;
}

GameObject* Classregistry::Create(ReplicationClassID id)
{
	std::function<GameObject * ()> fct = this->m_map_id_TO_ptrfunction.at(id);
	GameObject* obj = fct();
	return obj;
}