
#pragma once
#include <iostream>
#include <unordered_set>
#include "game_object.hpp"
#include "linking_context.hpp"

using gameObjt = std::shared_ptr<GameObject>;
class ReplicationManager
{
public:
	void Replicate(MemoryStream memo, std::vector<gameObjt> list_goptr);
	void Replicate(MemoryStream memo);

private:
	std::unordered_set<gameObjt> m_set;
};