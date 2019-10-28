#include "replication_manager.hpp"

void ReplicationManager::Replicate(OutputStream& stream, std::vector<ptrGameObjt> list_goptr) {
	stream.Write<ProtocoleID>(this->m_protocolID);
	PacketType type = PacketType::Sync;
	stream.Write<PacketType>(type);
	for (auto game_objt : list_goptr) {
		auto objectID = m_linkingContext.GetNetworkId(game_objt);
		if (!objectID.has_value()) {
			m_linkingContext.AddTo_Context(reinterpret_cast<GameObject*>(game_objt));
			objectID = m_linkingContext.GetNetworkId(game_objt);
		}
		stream.Write<networkID>(objectID.value());
		auto classID = game_objt->ClassID();
		stream.Write<ReplicationClassID>(classID);
		game_objt->Write(stream);
	}
}

void ReplicationManager::Replicate(InputStream& stream) {
	std::unordered_set<ptrGameObjt> set_StreamObjs;
	ProtocoleID protocol = stream.Read<ProtocoleID>();
	if (protocol == this->m_protocolID) {
		PacketType type = stream.Read<PacketType>();
		if (type == PacketType::Sync)
		{
			while (stream.RemainingSize() > 0) {
				networkID objectID = stream.Read<networkID>();
				ReplicationClassID classID = stream.Read<ReplicationClassID>();
				const auto gameO = m_linkingContext.GetGameObject(objectID);
				if (!gameO.has_value()) {
					GameObject* game_object = m_classRegistry->Create(classID);
					m_linkingContext.AddTo_Context(game_object, objectID);
					game_object->Read(stream);
					m_set.insert(game_object);
					set_StreamObjs.insert(game_object);
				}
				else {
					gameO.value()->Read(stream);
					set_StreamObjs.insert(gameO.value());
				}
			}

			std::vector<ptrGameObjt> removedObjects(set_StreamObjs.size());
			std::remove_copy_if(m_set.begin(), m_set.end(), removedObjects.begin(),
				[set_StreamObjs](ptrGameObjt objPtr)
				{
					const auto pos = std::find_if(
						set_StreamObjs.begin(),
						set_StreamObjs.end(),
						[objPtr](GameObject* vecObj) -> bool { return vecObj == objPtr; }
					);
					return (pos != set_StreamObjs.end());
				});

			std::for_each(removedObjects.begin(), removedObjects.end(),
				[this](ptrGameObjt objPtr)
				{
					if (objPtr != nullptr)
					{
						m_set.erase(objPtr);
						m_linkingContext.SupprFrom_List(objPtr);
						objPtr->Destroy();
						delete objPtr;
					}
				});
		}
	}
}