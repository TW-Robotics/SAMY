#include <samycoreInterfaceGenerator.h>

namespace SAMY{

    /* Add CRCLBasedSkill abstract type (the rest of the skills inherit from this one) i=CRCLSKILLS_NODE_ID */
    UA_StatusCode SAMYCoreInterfaceGenerator::addCRCLBasedSkillTypeNode( UA_Server *server ){
        UA_Int16 fortissDiNS = UA_Server_addNamespace( server, "https://fortiss.org/UA/DI/");
        UA_Int16 nsSkills = UA_Server_addNamespace( server, "http://SAMY.org/SAMYSkills" );

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        UA_ObjectTypeAttributes attr = UA_ObjectTypeAttributes_default;
        attr.isAbstract = true;
        attr.displayName = UA_LOCALIZEDTEXT("", "CRCLBasedSkill");
        #ifdef UA_ENABLE_NODESET_COMPILER_DESCRIPTIONS
        attr.description = UA_LOCALIZEDTEXT("", "CRCLBased Skill. The rest of skills inherit from this abstract type.");
        #endif
        retVal |= UA_Server_addNode_begin(server, UA_NODECLASS_OBJECTTYPE,
        UA_NODEID_NUMERIC(nsSkills, CRCLSKILLS_NODE_ID),
        UA_NODEID_NUMERIC(fortissDiNS, 15034LU),
        UA_NODEID_NUMERIC(0, 45LU),
        UA_QUALIFIEDNAME(nsSkills, "CRCLBasedSkill"),
         UA_NODEID_NULL,
        (const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_OBJECTTYPEATTRIBUTES],NULL, NULL);

        retVal |= UA_Server_addNode_finish(server, UA_NODEID_NUMERIC(nsSkills, CRCLSKILLS_NODE_ID));

        return retVal;
    }

    UA_StatusCode SAMYCoreInterfaceGenerator::addBasicSkillType( UA_Server* server, SAMYSkill* skill ){
        UA_Int16 nsSkills = UA_Server_addNamespace( server, "http://SAMY.org/SAMYSkills" );

        UA_NodeId nodeNumber;

        std::stringstream msg1;
        msg1 << "Adding Skill Type node";
        logger->debug( msg1.str() );

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        UA_ObjectTypeAttributes attr = UA_ObjectTypeAttributes_default;
        attr.isAbstract = false;
        attr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>(skill->getSkillName().c_str()));
        #ifdef UA_ENABLE_NODESET_COMPILER_DESCRIPTIONS
        attr.description = UA_LOCALIZEDTEXT("", "");
        #endif
        retVal |= UA_Server_addNode_begin( server, UA_NODECLASS_OBJECTTYPE,
        UA_NODEID_NUMERIC(nsSkills, 0),
        UA_NODEID_NUMERIC(nsSkills, CRCLSKILLS_NODE_ID),
        UA_NODEID_NUMERIC(0, 45LU),
        UA_QUALIFIEDNAME(nsSkills, const_cast<char*>(skill->getSkillName().c_str())), UA_NODEID_NULL,
        (const UA_NodeAttributes*)&attr,
        &UA_TYPES[UA_TYPES_OBJECTTYPEATTRIBUTES], NULL, &nodeNumber);

        retVal |= UA_Server_addNode_finish( server, nodeNumber);

        skill->setSkillTypeNodeId( std::move( nodeNumber ) );
        return retVal;
    }

    UA_StatusCode SAMYCoreInterfaceGenerator::addParameterSetObjectToSkillType( UA_Server* server, SAMYSkill* skill ){
        UA_Int16 diNS = UA_Server_addNamespace( server, "http://opcfoundation.org/UA/DI/");
        UA_Int16 nsSkills = UA_Server_addNamespace( server, "http://SAMY.org/SAMYSkills" );

        UA_NodeId nodeNumber;

        UA_NodeId skillTypeNodeId = findSkillType( server, skill->getSkillName().c_str() );
        skill->setSkillTypeNodeId( std::move( skillTypeNodeId ) );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        UA_ObjectAttributes attr = UA_ObjectAttributes_default;
        attr.displayName = UA_LOCALIZEDTEXT("", "ParameterSet");

        retVal |= UA_Server_addNode_begin( server, UA_NODECLASS_OBJECT,
        UA_NODEID_NUMERIC(nsSkills, 0),
        skillTypeNodeId,
        UA_NODEID_NUMERIC(0, 47LU),
        UA_QUALIFIEDNAME(diNS, "ParameterSet"),
        UA_NODEID_NUMERIC(0, 58LU), (const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_OBJECTATTRIBUTES],
        NULL, &nodeNumber);

        retVal |= UA_Server_addReference( server, nodeNumber,
                UA_NODEID_NUMERIC(0, 37LU), UA_EXPANDEDNODEID_NUMERIC(0, 78LU), true);

        return retVal;
    }

    UA_StatusCode SAMYCoreInterfaceGenerator::addParameterSetRealTimeObjectToSkillType( UA_Server* server, SAMYSkill* skill ){
        UA_Int16 diNS = UA_Server_addNamespace( server, "http://opcfoundation.org/UA/DI/");
        UA_Int16 nsSkills = UA_Server_addNamespace( server, "http://SAMY.org/SAMYSkills" );

        UA_NodeId nodeNumber;
        UA_NodeId skillTypeNodeId = findSkillType( server, skill->getSkillName().c_str() );
       // UA_NodeId skillTypeNodeId = std::move( skill->getSkillTypeNodeId() );
        skill->setSkillTypeNodeId( std::move( skillTypeNodeId ) );

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        UA_ObjectAttributes attr = UA_ObjectAttributes_default;
        attr.displayName = UA_LOCALIZEDTEXT("", "ParameterSetRealTime");

        retVal |= UA_Server_addNode_begin( server, UA_NODECLASS_OBJECT,
        UA_NODEID_NUMERIC(nsSkills, 0),
        skillTypeNodeId,
        UA_NODEID_NUMERIC(0, 47LU),
        UA_QUALIFIEDNAME(nsSkills, "ParameterSetRealTime"),
        UA_NODEID_NUMERIC(0, 58LU), (const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_OBJECTATTRIBUTES],
        NULL, &nodeNumber);

        retVal |= UA_Server_addReference( server, nodeNumber,
                UA_NODEID_NUMERIC(0, 37LU), UA_EXPANDEDNODEID_NUMERIC(0, 78LU), true);

        return retVal;
    }

    UA_StatusCode SAMYCoreInterfaceGenerator::addParametersToSkillType( UA_Server* server, const SAMYSkill *skill ){
        std::vector<UA_CRCLCommandsUnionDataType> com = skill->getSkillCommands();

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        AdderParameterNodesToSkillType adder( skill->getSkillName() , -1, server );

        for(int i=0; i < com.size(); i++){
            auto it = crclCommandSwitchfield_ParameterType_Map.find(com[i].switchField);
            if( it != crclCommandSwitchfield_ParameterType_Map.end()){
                CRCLCommandsParametersVariant param = it->second;
                adder.numberOfCommandInSkill = i;
                retVal |= std::visit( adder, param );
            }
            else{
                throw "PAMETER FOR SKILL COMMAND NOT FOUND";
            }
        }
        return retVal;
    }

    UA_StatusCode SAMYCoreInterfaceGenerator::addSkillTypeToServer(UA_Server* server, SAMYSkill *skill ){
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        std::stringstream msg1;
        msg1 << "Processing skill: " << skill->getSkillName();
        logger->info( msg1.str() );

        retVal |= addBasicSkillType( server, skill );
        logOfNodesAdditionToServer( "Basic Skill", retVal );

        retVal |= addParameterSetObjectToSkillType( server, skill );
        logOfNodesAdditionToServer( "ParameterSetObject", retVal );

        retVal |= addParameterSetRealTimeObjectToSkillType( server, skill );
        logOfNodesAdditionToServer( "ParameterSetRealTimeObject", retVal );

        retVal |= addParametersToSkillType( server, skill );
        logOfNodesAdditionToServer( "Parameters of Skill", retVal );

        std::stringstream msg;
        msg << "Finished processing skill: " << skill->getSkillName() << std::endl << std::endl;
        logger->info( msg.str() );

        return retVal;
    }

    UA_StatusCode SAMYCoreInterfaceGenerator::addSkillTypesToServer( UA_Server* server, std::vector<SAMYSkill> *skills ){
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        std::stringstream msg1;
        msg1 << "Adding Skill Types nodes to SAMYCore Server " << std::endl << std::endl;
        logger->info( msg1.str() );

        retVal |= addCRCLBasedSkillTypeNode( server );

        for( int i = 0; i < skills->size(); i++ ){
            retVal |= addSkillTypeToServer( server, &(*skills)[i] );
        }

        return retVal;
    }

} /*SAMY*/
