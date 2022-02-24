#include <informationSource.h>

namespace SAMY {

    InformationSource::InformationSource(const std::string& name_, const std::vector<UA_NodeId>& dataTypesNodeIds_):
    name(name_),
    dataTypesNodeIds(dataTypesNodeIds_)
    {}

    void InformationSource::setObjectNodeId( const UA_NodeId& nodeId ){ objectNodeId = nodeId; }
    void InformationSource::setVariableNodesIds( const std::vector<UA_NodeId>& nodesIds ){ variablesNodeIds = nodesIds; }
    std::vector<UA_NodeId> InformationSource::getDataTypesNodeIds(){ return dataTypesNodeIds; }
    std::vector<UA_NodeId> InformationSource::InformationSource::getVariablesNodesIds(){ return variablesNodeIds; }
    std::string InformationSource::InformationSource::getName(){ return name; }
    UA_NodeId InformationSource::InformationSource::getObjectNodeId(){ return objectNodeId; }

}
