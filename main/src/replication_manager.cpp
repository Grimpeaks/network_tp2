#include "replication_manager.hpp"

void ReplicationManager::Replicate(OutputStream& stream, std::vector<ptrGameObjt> list_goptr) {
	stream.Write(this->m_protocolID);
	auto type = to_integral(PacketType::Sync);
	stream.Write(type);
	for (auto game_objt : list_goptr) {
		auto objectID = m_linkingContext.GetNetworkId(game_objt);
		if (objectID.has_value()) {
			continue;
		}
		stream.Write(*objectID);
		auto classID = game_objt->ClassID();
		stream.Write(classID);
		game_objt->Write(stream);
	}
}

void ReplicationManager::Replicate(InputStream& stream) {
	std::unordered_set<ptrGameObjt> set_tmp;
	ProtocoleID protocol = stream.Read<uint32_t>();
	if (protocol == this->m_protocolID) {
		PacketType type = stream.Read<PacketType>();
		if (type==PacketType::Sync)
		{
			while (stream.RemainingSize() > 0) {
				networkID objectID = stream.Read<networkID>();
				ReplicationClassID classID = stream.Read<ReplicationClassID>();
				const auto gameO = m_linkingContext.GetGameObject(objectID);
				if (gameO.has_value()) {
					GameObject* game_object = m_classRegistry->Create(classID);
					m_set.insert(game_object);
					set_tmp.insert(game_object);
				}
				else {
					gameO.value()->Read(stream);
					set_tmp.insert(gameO.value());
				}

			}
			for (ptrGameObjt ga : m_set) {
				if (set_tmp.find<ptrGameObjt>(ga) == set_tmp.end()) {
					m_set.erase(ga);
					m_linkingContext.SupprFrom_List(ga);
					ga->Destroy();
				}
			}
		}
	}
}