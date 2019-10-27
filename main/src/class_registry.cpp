#include "class_registry.hpp"
Classregistry* Classregistry::m_registre = 0;

Classregistry* Classregistry::get_Instance()
{
	if (m_registre == 0) {
		m_registre = new Classregistry();
	}
	return m_registre;
}

GameObject* Classregistry::Create(ReplicationClassID id)
{
	std::function<GameObject*()> fct = this->m_map_id_TO_ptrfunction.at(id);
	GameObject* obj = fct();
	return obj;
}

template < typename T >
void Classregistry::RegistreClasse(T theClass)
{
	this->m_map_id_TO_ptrfunction.insert(std::pair<theClass::mClassID, theClass::CreateInstance()>);
}

Classregistry::Classregistry() {

}