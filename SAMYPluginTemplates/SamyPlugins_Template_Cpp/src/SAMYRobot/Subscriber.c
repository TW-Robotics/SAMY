#include "Subscriber.h"


#if pubsub
/* Publisher_UADP functions begin*/
/*Setting PublisherUADP PubSubConnection and adding it to the server*/
void setSubscriberUADP_PubSubConnection(Subscriber_UADP* subscriber){
    memset(&(subscriber->connectionConfig), 0, sizeof(subscriber->connectionConfig));
    subscriber->connectionConfig.name = subscriber->name;
    subscriber->connectionConfig.transportProfileUri = UA_STRING("http://opcfoundation.org/UA-Profile/Transport/pubsub-udp-uadp");
    subscriber->connectionConfig.enabled = UA_TRUE;

    UA_Variant_setScalar(&(subscriber->connectionConfig.address), &(subscriber->networkAddressUrl),
                            &UA_TYPES[UA_TYPES_NETWORKADDRESSURLDATATYPE]);
    //REVISAAAR!!!!
    //subscriber->connectionConfig.publisherId.numeric = subscriber->numericID;
    subscriber->connectionConfig.publisherId.numeric = UA_UInt32_random ();
}

UA_StatusCode addSubscriberUADP_PubSubConnectionToServer(UA_Server *server, Subscriber_UADP* subscriber){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;

    retval |= UA_Server_addPubSubConnection(server, &(subscriber->connectionConfig), &(subscriber->connectionIdent));

    if (retval != UA_STATUSCODE_GOOD) {
        return retval;
    }

    retval |= UA_PubSubConnection_regist(server, &(subscriber->connectionIdent));

    if (retval != UA_STATUSCODE_GOOD) {
         printf ("\n ERROR \n");
        return retval;
    }
    return retval;
}

void setSubscriberUADP_ReaderGroup(Subscriber_UADP* subscriber){
    memset (&(subscriber->readerGroupConfig), 0, sizeof(UA_ReaderGroupConfig));
    subscriber->readerGroupConfig.name = subscriber->name;
}

UA_StatusCode addSubscriberUADP_ReaderGroupToServer(UA_Server *server, Subscriber_UADP* subscriber) {
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval |= UA_Server_addReaderGroup(server, subscriber->connectionIdent, &(subscriber->readerGroupConfig),
                                       &(subscriber->readerGroupIdent));

    UA_Server_setReaderGroupOperational(server, subscriber->readerGroupIdent);

    return retval;
}

/* Add DataSetReader to the ReaderGroup */
void setSubscriberUADP_DataSetReader(Subscriber_UADP* subscriber) {
    memset (&(subscriber->dataSetReaderConfig), 0, sizeof(UA_DataSetReaderConfig));

    subscriber->dataSetReaderConfig.name = subscriber->name;
    /* Parameters to filter which DataSetMessage has to be processed
     * by the DataSetReader */
    subscriber->dataSetReaderConfig.publisherId.type = &UA_TYPES[UA_TYPES_UINT16];
    subscriber->dataSetReaderConfig.publisherId.data = &(subscriber->numericID);
    subscriber->dataSetReaderConfig.writerGroupId    = subscriber->numericID;
    subscriber->dataSetReaderConfig.dataSetWriterId  = subscriber->numericID;

    /* Setting up Meta data configuration in DataSetReader */
    setDataSetMetaData(&(subscriber->dataSetReaderConfig.dataSetMetaData), subscriber->name);
}
UA_StatusCode addSubscriberUADP_DataSetReaderToServer(UA_Server* server, Subscriber_UADP* subscriber) {
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    /* Setting up Meta data configuration in DataSetReader */
    retval |= UA_Server_addDataSetReader(server, subscriber->readerGroupIdent, &(subscriber->dataSetReaderConfig),
                                            &(subscriber->readerIdent));
    return retval;
}

/* Set SubscribedDataSet type to TargetVariables data type
 * Add subscribedvariables to the DataSetReader */
UA_StatusCode addSubscriberUADP_SubscribedVariablesToServer(UA_Server* server, Subscriber_UADP* subscriber) {
    if(server == NULL)
        return UA_STATUSCODE_BADINTERNALERROR;

    UA_StatusCode retval = UA_STATUSCODE_GOOD;

    /* Create the TargetVariables with respect to DataSetMetaData fields */
    UA_FieldTargetVariable *targetVars = (UA_FieldTargetVariable *)
            UA_calloc(subscriber->dataSetReaderConfig.dataSetMetaData.fieldsSize, sizeof(UA_FieldTargetVariable));
    for(size_t i = 0; i < subscriber->dataSetReaderConfig.dataSetMetaData.fieldsSize; i++) {
        /* Variable to subscribe data */
        UA_VariableAttributes vAttr = UA_VariableAttributes_default;
        UA_LocalizedText_copy(&(subscriber->dataSetReaderConfig.dataSetMetaData.fields[i].description),
                              &vAttr.description);
        vAttr.displayName.locale = UA_STRING("en-US");
        vAttr.displayName.text = subscriber->dataSetReaderConfig.dataSetMetaData.fields[i].name;
        vAttr.dataType = subscriber->dataSetReaderConfig.dataSetMetaData.fields[i].dataType;

        UA_NodeId newNode;
        retval |= UA_Server_addVariableNode(server, UA_NODEID_NUMERIC(1, (UA_UInt32)i + 50000),
                                           UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                           UA_QUALIFIEDNAME(1, (char *)subscriber->dataSetReaderConfig.dataSetMetaData.fields[i].name.data),
                                           UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                           vAttr, NULL, &newNode);

        /* For creating Targetvariables */
        UA_FieldTargetDataType_init(&targetVars[i].targetVariable);
        targetVars[i].targetVariable.attributeId  = UA_ATTRIBUTEID_VALUE;
        targetVars[i].targetVariable.targetNodeId = newNode;
    }

    retval = UA_Server_DataSetReader_createTargetVariables(server, subscriber->dataSetReaderIdent,
                                                           subscriber->dataSetReaderConfig.dataSetMetaData.fieldsSize, targetVars);
    for(size_t i = 0; i < subscriber->dataSetReaderConfig.dataSetMetaData.fieldsSize; i++)
        UA_FieldTargetDataType_clear(&targetVars[i].targetVariable);

    UA_free(targetVars);
    //I do not think I have to free this! REVIEW!!
    UA_free(subscriber->dataSetReaderConfig.dataSetMetaData.fields);
    return retval;
}

/* Define MetaData for TargetVariables */
void setDataSetMetaData(UA_DataSetMetaDataType *pMetaData, UA_String name) {
    if(pMetaData == NULL) {
        return;
    }

    UA_DataSetMetaDataType_init (pMetaData);
    pMetaData->name = name;

    pMetaData->fieldsSize = 1;
    pMetaData->fields = (UA_FieldMetaData*)UA_Array_new (pMetaData->fieldsSize,
                         &UA_TYPES[UA_TYPES_FIELDMETADATA]);

    /* CRCL Vector DataType for test purposes */
    UA_FieldMetaData_init (&pMetaData->fields[0]);
    UA_NodeId_copy(&UA_TYPES_CRCL[UA_TYPES_CRCLSAMYROBOTDATATYPE].typeId,
                    &pMetaData->fields[0].dataType);
    pMetaData->fields[0].builtInType = UA_NS0ID_STRUCTURE;
    pMetaData->fields[0].name =  name;
    pMetaData->fields[0].valueRank = UA_VALUERANK_SCALAR;
}

void configureSubscriberUADP(Subscriber_UADP* subscriber, UA_UInt16 numericID_, UA_String name_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_ ){
    subscriber->numericID = numericID_;
    subscriber->name = name_;
    subscriber->networkAddressUrl = networkAddressUrl_;
    setSubscriberUADP_PubSubConnection(subscriber);
    setSubscriberUADP_ReaderGroup(subscriber);
    setSubscriberUADP_DataSetReader(subscriber);
}

UA_StatusCode addSubscriberUADP_ToServer(UA_Server* server, Subscriber_UADP* subscriber){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval |= addSubscriberUADP_PubSubConnectionToServer(server, subscriber);
    retval |= addSubscriberUADP_ReaderGroupToServer(server, subscriber);
    retval |= addSubscriberUADP_DataSetReaderToServer(server, subscriber);
    retval |= addSubscriberUADP_SubscribedVariablesToServer(server, subscriber);
    return retval;
}

/*
void addCustomCallback( Subscriber_UADP* subscriber ){
     subscriber->readerGroupConfig
}

UA_StatusCode robotRequestedSkillUpdate(UA_Server *server, UA_NodeId identifier,
                                        UA_ServerCallback callback,
                                        void *data, UA_Double interval_ms, UA_UInt64 *callbackId){

}
UA_StatusCode (*addCustomCallback)(UA_Server *server, UA_NodeId identifier,
                                   UA_ServerCallback callback,
                                   void *data, UA_Double interval_ms, UA_UInt64 *callbackId);
*/















#if 0 /* The MQTT subscriber type is not yet implemented in open62541 */

/* Subscriber_MQTT functions begin*/
/*Setting Subscriber_MQTT PubSubConnection and adding it to the server*/
void setSubscriberMQTT_PubSubConnection(Subscriber_MQTT* subscriber){
    memset(&(subscriber->connectionConfig), 0, sizeof(subscriber->connectionConfig));
    subscriber->connectionConfig.name = subscriber->name;
    subscriber->connectionConfig.transportProfileUri = UA_STRING("http://opcfoundation.org/UA-Profile/Transport/pubsub-mqtt");
    subscriber->connectionConfig.enabled = UA_TRUE;

    UA_Variant_setScalar(&(subscriber->connectionConfig.address), &(subscriber->networkAddressUrl),
                         &UA_TYPES[UA_TYPES_NETWORKADDRESSURLDATATYPE]);
    subscriber->connectionConfig.publisherId.numeric = subscriber->numericID;
}
UA_StatusCode addSubscriberMQTT_PubSubConnectionToServer(UA_Server *server, Subscriber_MQTT* subscriber){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;

    retval |= UA_Server_addPubSubConnection(server, &(subscriber->connectionConfig), &(subscriber->connectionIdent));

    if (retval != UA_STATUSCODE_GOOD) {
        return retval;
    }

  /*  retval |= UA_PubSubConnection_regist(server, &(subscriber->connectionIdent));

    if (retval != UA_STATUSCODE_GOOD) {
         printf ("\n ERROR \n");
        return retval;
    }*/
    return retval;
}

void setSubscriberMQTT_ReaderGroup(Subscriber_MQTT* subscriber){
    memset (&(subscriber->readerGroupConfig), 0, sizeof(UA_ReaderGroupConfig));
    subscriber->readerGroupConfig.name = subscriber->name;
}
UA_StatusCode addSubscriberMQTT_ReaderGroupToServer(UA_Server *server, Subscriber_MQTT* subscriber) {
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval |= UA_Server_addReaderGroup(server, subscriber->connectionIdent, &(subscriber->readerGroupConfig),
                                       &(subscriber->connectionIdent));
    return retval;
}

/* Add DataSetReader to the ReaderGroup */
void setSubscriberMQTT_DataSetReader(Subscriber_MQTT* subscriber) {
    memset (&(subscriber->dataSetReaderConfig), 0, sizeof(UA_DataSetReaderConfig));

    subscriber->dataSetReaderConfig.name = subscriber->name;
    /* Parameters to filter which DataSetMessage has to be processed
     * by the DataSetReader */
    subscriber->dataSetReaderConfig.publisherId.type = &UA_TYPES[UA_TYPES_UINT16];
    subscriber->dataSetReaderConfig.publisherId.data = &(subscriber->numericID);
    subscriber->dataSetReaderConfig.writerGroupId    = subscriber->numericID;
    subscriber->dataSetReaderConfig.dataSetWriterId  = subscriber->numericID;

    /* Setting up Meta data configuration in DataSetReader */
    setDataSetMetaData(&(subscriber->dataSetReaderConfig.dataSetMetaData), subscriber->name);
}
UA_StatusCode addSubscriberMQTT_DataSetReaderToServer(UA_Server* server, Subscriber_MQTT* subscriber) {
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    /* Setting up Meta data configuration in DataSetReader */
    retval |= UA_Server_addDataSetReader(server, subscriber->readerGroupIdent, &(subscriber->dataSetReaderConfig),
                                            &(subscriber->dataSetReaderIdent));
    return retval;
}

/* Set SubscribedDataSet type to TargetVariables data type
 * Add subscribedvariables to the DataSetReader */
UA_StatusCode addSubscriberMQTT_SubscribedVariablesToServer(UA_Server* server, Subscriber_MQTT* subscriber) {
    if(server == NULL)
        return UA_STATUSCODE_BADINTERNALERROR;

    UA_StatusCode retval = UA_STATUSCODE_GOOD;

    /* Create the TargetVariables with respect to DataSetMetaData fields */
    UA_FieldTargetVariable *targetVars = (UA_FieldTargetVariable *)
            UA_calloc(subscriber->dataSetReaderConfig.dataSetMetaData.fieldsSize, sizeof(UA_FieldTargetVariable));
    for(size_t i = 0; i < subscriber->dataSetReaderConfig.dataSetMetaData.fieldsSize; i++) {
        /* Variable to subscribe data */
        UA_VariableAttributes vAttr = UA_VariableAttributes_default;
        UA_LocalizedText_copy(&(subscriber->dataSetReaderConfig.dataSetMetaData.fields[i].description),
                              &vAttr.description);
        vAttr.displayName.locale = UA_STRING("en-US");
        vAttr.displayName.text = subscriber->dataSetReaderConfig.dataSetMetaData.fields[i].name;
        vAttr.dataType = subscriber->dataSetReaderConfig.dataSetMetaData.fields[i].dataType;

        UA_NodeId newNode;
        retval |= UA_Server_addVariableNode(server, UA_NODEID_NUMERIC(1, (UA_UInt32)i + 50000),
                                           UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                           UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                           UA_QUALIFIEDNAME(1, (char *)subscriber->dataSetReaderConfig.dataSetMetaData.fields[i].name.data),
                                           UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                           vAttr, NULL, &newNode);

        /* For creating Targetvariables */
        UA_FieldTargetDataType_init(&targetVars[i].targetVariable);
        targetVars[i].targetVariable.attributeId  = UA_ATTRIBUTEID_VALUE;
        targetVars[i].targetVariable.targetNodeId = newNode;
    }

    retval = UA_Server_DataSetReader_createTargetVariables(server, subscriber->dataSetReaderIdent,
                                                           subscriber->dataSetReaderConfig.dataSetMetaData.fieldsSize, targetVars);
    for(size_t i = 0; i < subscriber->dataSetReaderConfig.dataSetMetaData.fieldsSize; i++)
        UA_FieldTargetDataType_clear(&targetVars[i].targetVariable);

    UA_free(targetVars);
    UA_free(subscriber->dataSetReaderConfig.dataSetMetaData.fields);
    return retval;
}

void configureSubscriberMQTT(Subscriber_MQTT* subscriber, UA_UInt32 numericID_, UA_String name_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_ ){
    subscriber->numericID = numericID_;
    subscriber->name = name_;
    subscriber->networkAddressUrl = networkAddressUrl_;
    setSubscriberMQTT_PubSubConnection(subscriber);
    setSubscriberMQTT_ReaderGroup(subscriber);
    setSubscriberMQTT_DataSetReader(subscriber);
}

UA_StatusCode addSubscriberMQTT_ToServer(UA_Server* server, Subscriber_MQTT* subscriber){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval |= addSubscriberMQTT_PubSubConnectionToServer(server, subscriber);
    retval |= addSubscriberMQTT_ReaderGroupToServer(server, subscriber);
    retval |= addSubscriberMQTT_DataSetReaderToServer(server, subscriber);
    retval |= addSubscriberMQTT_SubscribedVariablesToServer(server, subscriber);
    return retval;
}

#endif


#endif
