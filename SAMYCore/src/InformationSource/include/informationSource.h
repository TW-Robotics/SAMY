#ifndef INFORMATIONSOURCE_H
#define INFORMATIONSOURCE_H

#include <vector>
#include <string>
#include "namespace_crcl_generated.h"

namespace SAMY {

class InformationSource{
public:
    InformationSource(const std::string& name_, const std::vector<UA_NodeId>& dataTypesNodeIds_);
    std::vector<UA_NodeId> getDataTypesNodeIds();
    std::vector<UA_NodeId> getVariablesNodesIds();
    std::string getName();
    UA_NodeId getObjectNodeId();
    void setObjectNodeId( const UA_NodeId& nodeId );
    void setVariableNodesIds( const std::vector<UA_NodeId>& nodesIds );
private:
    std::string name;
    UA_NodeId objectNodeId;
    std::vector<UA_NodeId> variablesNodeIds;
    std::vector<UA_NodeId> dataTypesNodeIds;
};

}
#endif
