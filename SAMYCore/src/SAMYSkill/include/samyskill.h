#ifndef SAMYSKILL_H
#define SAMYSKILL_H

#include <vector>
#include "crcl_nodeids.h"
#include <namespace_crcl_generated.h>
#include <types_crcl_generated_handling.h>
#include <namespace_fortiss_di_generated.h>
#include <fortiss_di_nodeids.h>

#include <variant>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <iostream>
#include <map>
#include <mutex>

#include <ProgramState.h>
#include <ProgramTransition.h>
#include <helpers.h>
#include <logging.h>
#include <helper.hpp>

namespace SAMY{

   class SAMYSkill
   {
   public:
       SAMYSkill( const std::string& name,
                       const std::vector<UA_CRCLCommandsUnionDataType>& commands_,
                           const UA_NodeId& id, std::shared_ptr<spdlog::logger> logger_ );
       SAMYSkill(const std::string& name, std::vector<SAMYSkill>& skills, const UA_NodeId &id,
                                                                        std::shared_ptr<spdlog::logger> logger_ );
       /* Getters */
       std::string getSkillName() const;
       std::vector<UA_CRCLCommandsUnionDataType> getSkillCommands() const;
       UA_NodeId getSkillTypeNodeId() const;
       UA_NodeId getSkillNodeID() const;
       UA_NodeId getSkillCurrentStateNodeId() const;
       UA_NodeId getSkillLastTransitionNodeId() const;
       UA_NodeId getSkillParameterSetNodeId( ) const;
       UA_NodeId getSkillParameterSetRealTimeNodeId( ) const;
       std::vector<UA_NodeId> getSkillParametersNodesIds() const;
       std::vector<UA_NodeId> getSkillParametersRealTimeNodesIds() const;
       const ProgramState* getSkillCurrentState() const;
       const ProgramTransition* getSkillLastTransition() const;
       std::shared_ptr<spdlog::logger> getLogger();
       /* Setters */
       void setSkillTypeNodeId( const UA_NodeId& nodeId );
       void setSkillNodeID( const UA_NodeId& nodeId);
       /* From a ParameterSet/RealTimeParameterSet Object, it stores the NodeIds of the components of these objects
        * (which are the nodes of skill parameters) */
       UA_StatusCode setSkillParametersFromObjectComponentNodes(UA_Server *server,
                                                                           const UA_NodeId& startNode,
                                                                                    std::vector<UA_NodeId>& nodes );
       /* Other methods*/
       void addNormalParameterNodeToSkill( const UA_NodeId& node);
       void addRealTimeParameterNodeToSkill( const UA_NodeId& node);
       bool createSkillInstance(UA_Server *server, UA_CRCLSkillDataType *opcuaSkill);
       std::vector<UA_CRCLCommandsUnionDataType> skillToCRCLCommands( std::vector<SAMYSkill>& skills );
       bool transition( UA_Server* server, ProgramStateNumber nextState);
       UA_StatusCode initializeSkill( UA_Server* server );
       bool isTransitionAllowed( ProgramStateNumber from, ProgramStateNumber to, bool log = false );
   private:
       bool transition( UA_Server* server, ProgramStateNumber nextState, const UA_NodeId& eventType );
       bool transition( UA_Server* server, const ProgramState& from, ProgramStateNumber nextState, const UA_NodeId& eventType );
       UA_StatusCode triggerTransitionEvent( UA_Server* server, const ProgramState& fromState, const UA_NodeId& eventType )const;
       void fillTransitionEventBase( UA_Server* server, const UA_NodeId& eventId, const ProgramState& fromState )const;
       void setSkillCurrentStateNodeId( const UA_NodeId& nodeId );
       void setSkillLastTransitionNodeId( const UA_NodeId& nodeId );
       void setSkillParametersSetNodeId( const UA_NodeId& nodeId );
       void setSkillParametersSetRealTimeNodeId( const UA_NodeId& nodeId );
       UA_StatusCode setSkillNormalParameterNodes( UA_Server* server );
       UA_StatusCode setSkillRealTimeParameterNodes( UA_Server* server );
       void setskillTransitionEventTypeNodeId( const UA_NodeId& nodeId );
       void setTransitions( UA_Server* server );
       void setStates( UA_Server* server );
  //     UA_StatusCode addDataSources( UA_Server* server );

       std::string skillName;
       std::vector<UA_CRCLCommandsUnionDataType> commands;
       UA_NodeId skillTypeNodeId;
       UA_NodeId skillNodeID;
       UA_NodeId currentStateNodeId;
       UA_NodeId lastTransitionNodeId;
       UA_NodeId parametersSetNodeId;
       UA_NodeId parametersSetRealTimeNodeId;
       UA_NodeId skillTransitionEventTypeNodeId;
       std::vector<UA_NodeId> normalParameterNodes;
       std::vector<UA_NodeId> realTimeParameterNodes;

       ProgramState const * currentState = nullptr;
       ProgramTransition const * lastTransition = nullptr;
       std::vector<ProgramState> states;
       std::vector<ProgramTransition> transitions;
       std::shared_ptr<spdlog::logger> logger = nullptr;
  //     std::mutex skillInstantiationMutex;
   };
}  /* namespace SAMY */
#endif // SAMYSKILL_H
