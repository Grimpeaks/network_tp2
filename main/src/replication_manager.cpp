#include "replication_manager.hpp"

void ReplicationManager::Replicate(OutputStream& stream, std::vector<gameObjt_ptr> list_goptr) {
	stream.Write(this->m_protocolID);
	auto type = to_integral(PacketType::Sync);
	stream.Write(type);
	for (auto game_objt : list_goptr) {
		auto objectID = m_linkingContext.GetNetworkId(game_objt);
		if (!objectID) {
			continue;
		}
		stream.Write(*objectID);
		auto classID = game_objt->ClassID();
		stream.Write(classID);
		game_objt->Write(stream);
	}
}

