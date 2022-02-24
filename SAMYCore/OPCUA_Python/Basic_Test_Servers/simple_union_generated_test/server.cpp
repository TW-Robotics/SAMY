#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
/* Files namespace_foo_flt_generated.h and namespace_foo_flt_generated.c are created from FooFlt.NodeSet2.xml in the
 * /src_generated directory by CMake */

#include <thread>

#include <signal.h>

#include <iostream>

#include <chrono>

#include "namespace_crcl_generated.h"

UA_Boolean running = true;
static void stopHandler(int sign){
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}


UA_StatusCode addUnionVariable( UA_Server* server ){

        UA_Int16 crclNS = UA_Server_addNamespace( server, "https://crcl.org" );

        UA_NodeId paramNodeId = UA_NODEID_NULL;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        UA_VariableAttributes vattr = UA_VariableAttributes_default;
        vattr.description = UA_LOCALIZEDTEXT("","Union test");
        vattr.displayName = UA_LOCALIZEDTEXT("", "Union test");
        vattr.valueRank = UA_VALUERANK_SCALAR;
        vattr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
        vattr.dataType = UA_TYPES_CRCL[UA_TYPES_CRCL_UNI].typeId;

        UA_Uni u;
        u.switchField = UA_UNISWITCH_OPTIONB;
        UA_String str = UA_STRING( "test string" );
        UA_String_copy( &str, &u.fields.optionB );
        //u->switchField = UA_UNISWITCH_OPTIONA;
        //u->fields.optionA = 999;

        UA_Variant_setScalar( &vattr.value, &u, &UA_TYPES_CRCL[UA_TYPES_CRCL_UNI] );

        retVal |= UA_Server_addNode_begin( server, UA_NODECLASS_VARIABLE,
        UA_NODEID_NUMERIC(crclNS, 0),
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, 47LU),
        UA_QUALIFIEDNAME(crclNS, "Union test" ),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), (const UA_NodeAttributes*)&vattr, &UA_TYPES[UA_TYPES_VARIABLEATTRIBUTES],
        NULL, &paramNodeId);
/* HasModellingRule 
        retVal |= UA_Server_addReference( server, paramNodeId,
                UA_NODEID_NUMERIC(0, 37LU), UA_EXPANDEDNODEID_NUMERIC(0, 78LU), true);*/

        retVal |= UA_Server_addNode_finish(server, paramNodeId );

	return retVal;
}

int main(int argc, char** argv){

    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Server* server = UA_Server_new();
    UA_ServerConfig *config = UA_Server_getConfig(server);
    UA_ServerConfig_setMinimal(config, 4841, NULL);

    UA_StatusCode retVal = namespace_crcl_generated( server );
    if( retVal != UA_STATUSCODE_GOOD ){
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the fixed information models nodesets. "
        "Check previous output for any error.");
        retVal = UA_STATUSCODE_BADUNEXPECTEDERROR;
    } else {/*If custom namespaces succesfully added*/
  //      std::thread SAMYCoreOPCUAInterface(UA_Server_run, server, &running);
  //      SAMYCoreOPCUAInterface.detach();

	retVal = addUnionVariable( server );

	if( retVal == UA_STATUSCODE_GOOD )
		UA_Server_run( server, &running );
    }    

    UA_Server_delete( server );

    return retVal == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
