/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */

#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>

#include <stdlib.h>

#include "namespace_crcl_generated.h"
#include "types_crcl_generated_handling.h"

#define STRING_BUFFER_SIZE 20

int main(void) {

    UA_DataTypeArray customDataTypes = {NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};

    UA_Client *client = UA_Client_new();
    UA_ClientConfig *cc = UA_Client_getConfig(client);
    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;

    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://192.168.8.103:4841");
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return (int)retval;
    }
    
    UA_Variant value; /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&value);
    
    UA_NodeId nodeId =
        UA_NODEID_NUMERIC(2, 58192);

    retval = UA_Client_readValueAttribute(client, nodeId, &value);

    if(retval == UA_STATUSCODE_GOOD) {
        UA_Uni *u = (UA_Uni *) value.data;
	if( u->switchField == 1 ){
		printf("Union member selection: %i , member content: %i \n", u->switchField, u->fields.optionA);
	}else if( u->switchField == 2){
		char message[STRING_BUFFER_SIZE];
		memcpy(message, u->fields.optionB.data, u->fields.optionB.length);
		message[u->fields.optionB.length] = '\0';
		printf("Union member selection: %i , member content: %s \n", u->switchField, message);
	}
	else{
        	printf("No right value selected for the union");
	}
    }else{
        	printf("Error reading node!");
    }

    /* Clean up */

    UA_Variant_init(&value);

    UA_Uni u;
    UA_Uni_init( &u );
    u.switchField = UA_UNISWITCH_OPTIONB;
    UA_String str = UA_STRING( "test string\n" );
    UA_String_copy( &str, &u.fields.optionB );

    UA_Variant_setScalar( &value, &u, &UA_TYPES_CRCL[UA_TYPES_CRCL_UNI] );

    retval = UA_Client_writeValueAttribute(client, nodeId, &value);
    if(retval == UA_STATUSCODE_GOOD)
	printf("Succesful write!\n");
    else
	printf("Write failed!\n");

    UA_Variant_init(&value);
    retval = UA_Client_readValueAttribute(client, nodeId, &value);
    if(retval == UA_STATUSCODE_GOOD) {
        UA_Uni *u = (UA_Uni *) value.data;
	if( u->switchField == 1 ){
		printf("Union member selection: %i , member content: %i \n", u->switchField, u->fields.optionA);
	}else if( u->switchField == 2){
		char message[STRING_BUFFER_SIZE];
		memcpy(message, u->fields.optionB.data, u->fields.optionB.length);
		message[u->fields.optionB.length] = '\0';
		printf("Union member selection: %i , member content: %s \n", u->switchField, message);
	}
	else{
        	printf("No right value selected for the union");
	}
    }else{
        	printf("Error reading node!");
    }

    UA_Variant_init(&value);
    
    UA_Uni_init( &u );
    u.switchField = UA_UNISWITCH_OPTIONA;
    u.fields.optionA = 987;

    UA_Variant_setScalar( &value, &u, &UA_TYPES_CRCL[UA_TYPES_CRCL_UNI] );

    retval = UA_Client_writeValueAttribute(client, nodeId, &value);
    if(retval == UA_STATUSCODE_GOOD)
	printf("Succesful write!\n");
    else
	printf("Write failed!\n");

    UA_Variant_init(&value);
    retval = UA_Client_readValueAttribute(client, nodeId, &value);
    if(retval == UA_STATUSCODE_GOOD) {
        UA_Uni *u = (UA_Uni *) value.data;
	if( u->switchField == 1 ){
		printf("Union member selection: %i , member content: %i \n", u->switchField, u->fields.optionA);
	}else if( u->switchField == 2){
		char message[STRING_BUFFER_SIZE];
		memcpy(message, u->fields.optionB.data, u->fields.optionB.length);
		message[u->fields.optionB.length] = '\0';
		printf("Union member selection: %i , member content: %s \n", u->switchField, message);
	}
	else{
        	printf("No right value selected for the union");
	}
    }else{
        	printf("Error reading node!");
    }

    UA_Variant_clear( &value );
    UA_Client_delete(client); /* Disconnects the client internally */
    return EXIT_SUCCESS;
}
