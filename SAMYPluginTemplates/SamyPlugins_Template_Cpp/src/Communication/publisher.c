#include "Publisher.h"

/* Publisher_UADP functions begin*/
/*Setting PublisherUADP PubSubConnection and adding it to the server*/

#ifdef AAA
void setPublisherUADP_PubSubConnection(Publisher_UADP* publisher){
    memset(&(publisher->connectionConfig), 0, sizeof(publisher->connectionConfig));
    publisher->connectionConfig.name = publisher->name;
    publisher->connectionConfig.transportProfileUri = UA_STRING("http://opcfoundation.org/UA-Profile/Transport/pubsub-udp-uadp");
    publisher->connectionConfig.enabled = UA_TRUE;
    UA_Variant_setScalar(&(publisher->connectionConfig.address), &(publisher->networkAddressUrl),
                            &UA_TYPES[UA_TYPES_NETWORKADDRESSURLDATATYPE]);
    publisher->connectionConfig.publisherId.numeric = publisher->numericID;
}
UA_StatusCode addPublisherUADP_PubSubConnectionToServer(UA_Server *server, Publisher_UADP* publisher){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval |= UA_Server_addPubSubConnection(server, &(publisher->connectionConfig), &(publisher->connectionIdent));
    return retval;
}

/*Setting PublisherUADP PublishedDataSet and adding it to the server*/
void setPublisherUADP_PublishedDataSet(Publisher_UADP* publisher) {
    memset(&(publisher->publishedDataSetConfig), 0, sizeof(UA_PublishedDataSetConfig));
    publisher->publishedDataSetConfig.publishedDataSetType = UA_PUBSUB_DATASET_PUBLISHEDITEMS;
    publisher->publishedDataSetConfig.name = publisher->name;
}
UA_StatusCode addPublisherUADP_PublishedDataSetToServer(UA_Server *server, Publisher_UADP* publisher) {
    UA_AddPublishedDataSetResult retval;

    retval = UA_Server_addPublishedDataSet(server, &(publisher->publishedDataSetConfig), &(publisher->publishedDataSetIdent));
    return retval.addResult;
}

/*Setting PublisherUADP DataSetField and adding it to the server*/
void setPublisherUADP_DataSetField(Publisher_UADP* publisher) {
    memset(&(publisher->dataSetFieldConfig), 0, sizeof(UA_DataSetFieldConfig));
    publisher->dataSetFieldConfig.dataSetFieldType = UA_PUBSUB_DATASETFIELD_VARIABLE;
    publisher->dataSetFieldConfig.field.variable.fieldNameAlias = publisher->name;
    publisher->dataSetFieldConfig.field.variable.promotedField = UA_FALSE;
    publisher->dataSetFieldConfig.field.variable.publishParameters.publishedVariable = publisher->SAMYRobotVariableNodeID;
    publisher->dataSetFieldConfig.field.variable.publishParameters.attributeId = UA_ATTRIBUTEID_VALUE;
}
UA_StatusCode addPublisherUADP_DataSetFieldToServer(UA_Server *server, Publisher_UADP* publisher) {
    UA_DataSetFieldResult retval;

    retval = UA_Server_addDataSetField(server, publisher->publishedDataSetIdent,
                              &(publisher->dataSetFieldConfig), &(publisher->dataSetFieldIdent));
    return retval.result;
}

/*Setting PublisherUADP WriterGroup and adding it to the server*/
void setPublisherUADP_WriterGroup(Publisher_UADP* publisher) {
    memset(&(publisher->writerGroupConfig), 0, sizeof(UA_WriterGroupConfig));
    publisher->writerGroupConfig.name = publisher->name;
    publisher->writerGroupConfig.publishingInterval = publisher->publishingInterval;
    publisher->writerGroupConfig.enabled = UA_FALSE;
    publisher->writerGroupConfig.writerGroupId = publisher->numericID;
    publisher->writerGroupConfig.encodingMimeType = UA_PUBSUB_ENCODING_UADP;
    publisher->writerGroupConfig.messageSettings.encoding             = UA_EXTENSIONOBJECT_DECODED;
    publisher->writerGroupConfig.messageSettings.content.decoded.type = &UA_TYPES[UA_TYPES_UADPWRITERGROUPMESSAGEDATATYPE];
}
UA_StatusCode addPublisherUADP_WriterGroupToServer(UA_Server* server, Publisher_UADP* publisher) {
    UA_StatusCode retval = UA_STATUSCODE_GOOD;

    UA_UadpWriterGroupMessageDataType *writerGroupMessage  = UA_UadpWriterGroupMessageDataType_new();
    writerGroupMessage->networkMessageContentMask          = (UA_UadpNetworkMessageContentMask)(UA_UADPNETWORKMESSAGECONTENTMASK_PUBLISHERID |
                                                              (UA_UadpNetworkMessageContentMask)UA_UADPNETWORKMESSAGECONTENTMASK_GROUPHEADER |
                                                              (UA_UadpNetworkMessageContentMask)UA_UADPNETWORKMESSAGECONTENTMASK_WRITERGROUPID |
                                                              (UA_UadpNetworkMessageContentMask)UA_UADPNETWORKMESSAGECONTENTMASK_PAYLOADHEADER);
    publisher->writerGroupConfig.messageSettings.content.decoded.data = writerGroupMessage;
    retval |= UA_Server_addWriterGroup(server, publisher->connectionIdent, &(publisher->writerGroupConfig), &(publisher->writerGroupIdent));
    retval |= UA_Server_setWriterGroupOperational(server, publisher->writerGroupIdent);
    UA_UadpWriterGroupMessageDataType_delete(writerGroupMessage);
    return retval;
}

/*Setting PublisherUADP DataSetWriter and adding it to the server*/
void setPublisherUADP_DataSetWriter(Publisher_UADP* publisher) {
    memset(&(publisher->dataSetWriterConfig), 0, sizeof(UA_DataSetWriterConfig));
    publisher->dataSetWriterConfig.name = publisher->name;
    publisher->dataSetWriterConfig.dataSetWriterId = publisher->numericID;
    publisher->dataSetWriterConfig.keyFrameCount = publisher->keyFrameCount;
}
UA_StatusCode addPublisherUADP_DataSetWriterToServer(UA_Server *server, Publisher_UADP* publisher) {
    UA_StatusCode retval;
    retval = UA_Server_addDataSetWriter(server, publisher->writerGroupIdent, publisher->publishedDataSetIdent,
                                    &(publisher->dataSetWriterConfig), &(publisher->dataSetWriterIdent));
    return retval;
}

/*Setting PublisherUADP*/
void configurePublisherUADP(Publisher_UADP* publisher, UA_UInt32 numericID_, UA_String name_,
                            UA_UInt16 publishingInterval_, UA_UInt32 keyFrameCount_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_, UA_NodeId SAMYRobotVariableNodeID_){
    publisher->numericID = numericID_;
    publisher->name = name_;
    publisher->publishingInterval = publishingInterval_;
    publisher->keyFrameCount = keyFrameCount_;
    publisher->networkAddressUrl = networkAddressUrl_;
    publisher->SAMYRobotVariableNodeID = SAMYRobotVariableNodeID_;
    setPublisherUADP_PubSubConnection(publisher);
    setPublisherUADP_PublishedDataSet(publisher);
    setPublisherUADP_DataSetField(publisher);
    setPublisherUADP_WriterGroup(publisher);
    setPublisherUADP_DataSetWriter(publisher);
}
/*Adding PublisherUADP to the server*/
UA_StatusCode addPublisherUADP_ToServer(UA_Server* server, Publisher_UADP* publisher){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval |= addPublisherUADP_PubSubConnectionToServer(server, publisher);
    retval |= addPublisherUADP_PublishedDataSetToServer(server, publisher);
    retval |= addPublisherUADP_DataSetFieldToServer(server, publisher);
    retval |= addPublisherUADP_WriterGroupToServer(server, publisher);
    retval |= addPublisherUADP_DataSetWriterToServer(server, publisher);
    return retval;
}
/* Publisher_UADP functions end*/

/* Publisher_MQTT functions begin*/

/*Setting PublisherMQTT PubSubConnection and adding it to the server. Two options for the MQTT connection, with and without Login*/
void setPublisherMQTT_PubSubConnectionWithoutLogin(Publisher_MQTT* publisher){
    memset(&(publisher->connectionConfig), 0, sizeof(publisher->connectionConfig));
    publisher->connectionConfig.name = publisher->name;
    publisher->connectionConfig.transportProfileUri = UA_STRING("http://opcfoundation.org/UA-Profile/Transport/pubsub-mqtt");
    publisher->connectionConfig.enabled = UA_TRUE;

    UA_Variant_setScalar(&(publisher->connectionConfig.address), &(publisher->networkAddressUrl),
                            &UA_TYPES[UA_TYPES_NETWORKADDRESSURLDATATYPE]);

    publisher->connectionConfig.publisherId.numeric = publisher->numericID;

    UA_PubSubConnectionConfig* connectionConfig = &(publisher->connectionConfig);
    memset(&(connectionConfig->connectionProperties), 0, sizeof(UA_KeyValuePair));
    UA_KeyValuePair connectionOptions[1];

    connectionOptions[0].key = UA_QUALIFIEDNAME(0, "publisher->name.data");

    UA_String mqttClientId = publisher->name;

    connectionConfig->connectionProperties = connectionOptions;
    UA_Variant_setScalar(&(connectionOptions[0].value),
                                &mqttClientId, &UA_TYPES[UA_TYPES_STRING]);

    UA_Array_copy(&connectionOptions, 1, (void**)&connectionConfig->connectionProperties, &UA_TYPES[UA_TYPES_KEYVALUEPAIR]);

    publisher->connectionConfig.connectionPropertiesSize = 1;
}
void setPublisherMQTT_PubSubConnectionWithLogin(Publisher_MQTT* publisher, MQTT_LoginData loginData){
    memset(&(publisher->connectionConfig), 0, sizeof(publisher->connectionConfig));
    publisher->connectionConfig.name = publisher->name;
    publisher->connectionConfig.transportProfileUri = UA_STRING("http://opcfoundation.org/UA-Profile/Transport/pubsub-mqtt");
    publisher->connectionConfig.enabled = UA_TRUE;

    UA_Variant_setScalar(&(publisher->connectionConfig.address), &(publisher->networkAddressUrl),
                         &UA_TYPES[UA_TYPES_NETWORKADDRESSURLDATATYPE]);

    publisher->connectionConfig.publisherId.numeric = publisher->numericID;

    UA_PubSubConnectionConfig* connectionConfig = &(publisher->connectionConfig);
    memset(&(connectionConfig->connectionProperties), 0, 3*sizeof(UA_KeyValuePair));
    UA_KeyValuePair connectionOptions[3];

    size_t connectionOptionIndex = 0;
    connectionOptions[connectionOptionIndex].key = UA_QUALIFIEDNAME(0, "publisher->name.data");
    UA_String mqttClientId = publisher->name;
    UA_Variant_setScalar(&(connectionOptions[connectionOptionIndex++].value),
                                &mqttClientId, &UA_TYPES[UA_TYPES_STRING]);

    connectionOptions[connectionOptionIndex].key = UA_QUALIFIEDNAME(0, "loginData.USERNAME_OPTION_NAME.data");
    UA_String mqttUsername = loginData.MQTT_USERNAME;
    UA_Variant_setScalar(&connectionOptions[connectionOptionIndex++].value, &mqttUsername, &UA_TYPES[UA_TYPES_STRING]);

    connectionOptions[connectionOptionIndex].key = UA_QUALIFIEDNAME(0, "loginData.PASSWORD_OPTION_NAME.data");
    UA_String mqttPassword = loginData.MQTT_PASSWORD;
    UA_Variant_setScalar(&(connectionOptions[connectionOptionIndex++].value),
                                &mqttPassword, &UA_TYPES[UA_TYPES_STRING]);

    UA_Array_copy(&connectionOptions, 3, (void**)&connectionConfig->connectionProperties, &UA_TYPES[UA_TYPES_KEYVALUEPAIR]);

    publisher->connectionConfig.connectionPropertiesSize = connectionOptionIndex;
}
UA_StatusCode addPublisherMQTT_PubSubConnectionToServer(UA_Server *server, Publisher_MQTT* publisher) {
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval |= UA_Server_addPubSubConnection(server, &(publisher->connectionConfig), &(publisher->connectionIdent));
    return retval;
}

/*Setting PublisherMQTT PublishedDataSet and adding it to the server*/
void setPublisherMQTT_PublishedDataSet(Publisher_MQTT* publisher) {
    memset(&(publisher->publishedDataSetConfig), 0, sizeof(UA_PublishedDataSetConfig));
    publisher->publishedDataSetConfig.publishedDataSetType = UA_PUBSUB_DATASET_PUBLISHEDITEMS;
    publisher->publishedDataSetConfig.name = publisher->name;
}
UA_StatusCode addPublisherMQTT_PublishedDataSetToServer(UA_Server* server, Publisher_MQTT* publisher) {
    UA_AddPublishedDataSetResult retval;
    retval = UA_Server_addPublishedDataSet(server, &(publisher->publishedDataSetConfig), &(publisher->publishedDataSetIdent));
    return retval.addResult;
}

/*Setting PublisherMQTT DataSetField and adding it to the server*/
void setPublisherMQTT_DataSetField(Publisher_MQTT* publisher) {
    memset(&(publisher->dataSetFieldConfig), 0, sizeof(UA_DataSetFieldConfig));
    publisher->dataSetFieldConfig.dataSetFieldType = UA_PUBSUB_DATASETFIELD_VARIABLE;

    publisher->dataSetFieldConfig.field.variable.fieldNameAlias = publisher->name;
    publisher->dataSetFieldConfig.field.variable.promotedField = UA_FALSE;
    publisher->dataSetFieldConfig.field.variable.publishParameters.publishedVariable = publisher->SAMYRobotVariableNodeID;
    publisher->dataSetFieldConfig.field.variable.publishParameters.attributeId = UA_ATTRIBUTEID_VALUE;
}
UA_StatusCode addPublisherMQTT_DataSetFieldToServer(UA_Server *server, Publisher_MQTT* publisher) {
    UA_DataSetFieldResult retval;
    retval = UA_Server_addDataSetField(server, publisher->publishedDataSetIdent, &(publisher->dataSetFieldConfig), NULL);
    return retval.result;
}

/*Setting PublisherMQTT WriterGroup and adding it to the server*/
void setPublisherMQTT_WriterGroup(Publisher_MQTT* publisher) {
    UA_StatusCode retval = UA_STATUSCODE_GOOD;

    UA_WriterGroupConfig writerGroupConfig;
    memset(&(publisher->writerGroupConfig), 0, sizeof(UA_WriterGroupConfig));
    publisher->writerGroupConfig.name = publisher->name;
    publisher->writerGroupConfig.publishingInterval = publisher->publishingInterval;
    publisher->writerGroupConfig.enabled = UA_FALSE;
    publisher->writerGroupConfig.writerGroupId = publisher->numericID;
}
UA_StatusCode addPublisherMQTT_WriterGroupToServer(UA_Server* server, Publisher_MQTT* publisher) {
    UA_StatusCode retval = UA_STATUSCODE_GOOD;

    UA_UadpWriterGroupMessageDataType *writerGroupMessage;

    /* decide whether to use JSON or UADP encoding*/
    #ifdef UA_ENABLE_JSON_ENCODING
    UA_JsonWriterGroupMessageDataType *Json_writerGroupMessage;

    if( publisher->JSONEncoding == UA_TRUE ) {
        publisher->writerGroupConfig.encodingMimeType = UA_PUBSUB_ENCODING_JSON;
        publisher->writerGroupConfig.messageSettings.encoding             = UA_EXTENSIONOBJECT_DECODED;

        publisher->writerGroupConfig.messageSettings.content.decoded.type = &UA_TYPES[UA_TYPES_JSONWRITERGROUPMESSAGEDATATYPE];
        Json_writerGroupMessage = UA_JsonWriterGroupMessageDataType_new();
        Json_writerGroupMessage->networkMessageContentMask =
            (UA_JsonNetworkMessageContentMask)(UA_JSONNETWORKMESSAGECONTENTMASK_NETWORKMESSAGEHEADER |
            (UA_JsonNetworkMessageContentMask)UA_JSONNETWORKMESSAGECONTENTMASK_DATASETMESSAGEHEADER |
            (UA_JsonNetworkMessageContentMask)UA_JSONNETWORKMESSAGECONTENTMASK_SINGLEDATASETMESSAGE |
            (UA_JsonNetworkMessageContentMask)UA_JSONNETWORKMESSAGECONTENTMASK_PUBLISHERID |
            (UA_JsonNetworkMessageContentMask)UA_JSONNETWORKMESSAGECONTENTMASK_DATASETCLASSID);
        publisher->writerGroupConfig.messageSettings.content.decoded.data = Json_writerGroupMessage;
    }
    else
    #endif
    {
        publisher->writerGroupConfig.encodingMimeType = UA_PUBSUB_ENCODING_UADP;
        publisher->writerGroupConfig.messageSettings.encoding             = UA_EXTENSIONOBJECT_DECODED;
        publisher->writerGroupConfig.messageSettings.content.decoded.type = &UA_TYPES[UA_TYPES_UADPWRITERGROUPMESSAGEDATATYPE];
        writerGroupMessage  = UA_UadpWriterGroupMessageDataType_new();
        writerGroupMessage->networkMessageContentMask =
            (UA_UadpNetworkMessageContentMask)(UA_UADPNETWORKMESSAGECONTENTMASK_PUBLISHERID |
            (UA_UadpNetworkMessageContentMask)UA_UADPNETWORKMESSAGECONTENTMASK_GROUPHEADER |
            (UA_UadpNetworkMessageContentMask)UA_UADPNETWORKMESSAGECONTENTMASK_WRITERGROUPID |
            (UA_UadpNetworkMessageContentMask)UA_UADPNETWORKMESSAGECONTENTMASK_PAYLOADHEADER);
        publisher->writerGroupConfig.messageSettings.content.decoded.data = writerGroupMessage;
    }

    /* configure the mqtt publish topic */
    UA_BrokerWriterGroupTransportDataType brokerTransportSettings;
    memset(&brokerTransportSettings, 0, sizeof(UA_BrokerWriterGroupTransportDataType));
    /* Assign the Topic at which MQTT publish should happen */
    /*ToDo: Pass the topic as argument from the writer group */
    brokerTransportSettings.queueName = publisher->name;
    brokerTransportSettings.resourceUri = UA_STRING_NULL;
    brokerTransportSettings.authenticationProfileUri = UA_STRING_NULL;

    /* Choose the QOS Level for MQTT */
    brokerTransportSettings.requestedDeliveryGuarantee = UA_BROKERTRANSPORTQUALITYOFSERVICE_BESTEFFORT;

    /* Encapsulate config in transportSettings */
    UA_ExtensionObject transportSettings;
    memset(&transportSettings, 0, sizeof(UA_ExtensionObject));
    transportSettings.encoding = UA_EXTENSIONOBJECT_DECODED;
    transportSettings.content.decoded.type = &UA_TYPES[UA_TYPES_BROKERWRITERGROUPTRANSPORTDATATYPE];
    transportSettings.content.decoded.data = &brokerTransportSettings;

    publisher->writerGroupConfig.transportSettings = transportSettings;
    retval = UA_Server_addWriterGroup(server, publisher->connectionIdent, &(publisher->writerGroupConfig),
                                                    &(publisher->writerGroupIdent));

    if (retval == UA_STATUSCODE_GOOD)
        UA_Server_setWriterGroupOperational(server, publisher->writerGroupIdent);
    #ifdef UA_ENABLE_JSON_ENCODING
    if (publisher->JSONEncoding == UA_TRUE) {
        UA_JsonWriterGroupMessageDataType_delete(Json_writerGroupMessage);
    }
    #endif

    if ( (publisher->JSONEncoding == UA_FALSE) && writerGroupMessage) {
        UA_UadpWriterGroupMessageDataType_delete(writerGroupMessage);
    }

    return retval;
}

/*Setting PublisherMQTT DataSetWriter and adding it to the server*/
void setPublisherMQTT_DataSetWriter(Publisher_MQTT* publisher) {
    memset(&(publisher->dataSetWriterConfig), 0, sizeof(UA_DataSetWriterConfig));
    publisher->dataSetWriterConfig.name = publisher->name;
    publisher->dataSetWriterConfig.dataSetWriterId = publisher->numericID;
    publisher->dataSetWriterConfig.keyFrameCount = publisher->keyFrameCount;

#ifdef UA_ENABLE_JSON_ENCODING
    UA_JsonDataSetWriterMessageDataType jsonDswMd;
    UA_ExtensionObject messageSettings;
    if(publisher->JSONEncoding == UA_TRUE) {
        /* JSON config for the dataSetWriter */
        jsonDswMd.dataSetMessageContentMask = (UA_JsonDataSetMessageContentMask)
            (UA_JSONDATASETMESSAGECONTENTMASK_DATASETWRITERID |
             UA_JSONDATASETMESSAGECONTENTMASK_SEQUENCENUMBER |
             UA_JSONDATASETMESSAGECONTENTMASK_STATUS |
             UA_JSONDATASETMESSAGECONTENTMASK_METADATAVERSION |
             UA_JSONDATASETMESSAGECONTENTMASK_TIMESTAMP);

        messageSettings.encoding = UA_EXTENSIONOBJECT_DECODED;
        messageSettings.content.decoded.type = &UA_TYPES[UA_TYPES_JSONDATASETWRITERMESSAGEDATATYPE];
        messageSettings.content.decoded.data = &jsonDswMd;

        publisher->dataSetWriterConfig.messageSettings = messageSettings;
    }
#endif
    /*TODO: Modify MQTT send to add DataSetWriters broker transport settings */
    /*TODO: Pass the topic as argument from the writer group */
    /*TODO: Publish Metadata to metaDataQueueName */
    /* configure the mqtt publish topic */
    UA_BrokerDataSetWriterTransportDataType brokerTransportSettings;
    memset(&brokerTransportSettings, 0, sizeof(UA_BrokerDataSetWriterTransportDataType));

    /* Assign the Topic at which MQTT publish should happen */
    brokerTransportSettings.queueName = publisher->name;
    brokerTransportSettings.resourceUri = UA_STRING_NULL;
    brokerTransportSettings.authenticationProfileUri = UA_STRING_NULL;
    brokerTransportSettings.metaDataQueueName = publisher->name;
    brokerTransportSettings.metaDataUpdateTime = PUBLISHER_METADATAUPDATETIME;

    /* Choose the QOS Level for MQTT */
    brokerTransportSettings.requestedDeliveryGuarantee = UA_BROKERTRANSPORTQUALITYOFSERVICE_BESTEFFORT;

    /* Encapsulate config in transportSettings */
    UA_ExtensionObject transportSettings;
    memset(&transportSettings, 0, sizeof(UA_ExtensionObject));
    transportSettings.encoding = UA_EXTENSIONOBJECT_DECODED;
    transportSettings.content.decoded.type = &UA_TYPES[UA_TYPES_BROKERDATASETWRITERTRANSPORTDATATYPE];
    transportSettings.content.decoded.data = &brokerTransportSettings;

    publisher->dataSetWriterConfig.transportSettings = transportSettings;
}
UA_StatusCode addPublisherMQTT_DataSetWriterToServer(UA_Server* server, Publisher_MQTT* publisher){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval |= UA_Server_addDataSetWriter(server, publisher->writerGroupIdent, publisher->publishedDataSetIdent,
                               &(publisher->dataSetWriterConfig), &(publisher->dataSetWriterIdent));
    return retval;
}

/*Setting PublisherMQTT with and without MQTT LogIn*/
#ifdef UA_ENABLE_JSON_ENCODING
void configurePublisherMQTT_WithLogin(Publisher_MQTT* publisher, UA_UInt32 numericID_, UA_String name_,
                            UA_UInt16 publishingInterval_, UA_UInt32 keyFrameCount_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_, UA_NodeId SAMYRobotVariableNodeID_,
                                    UA_Boolean JSONEncoding_, MQTT_LoginData login_){
    publisher->numericID = numericID_;
    publisher->name = name_;
    publisher->publishingInterval = publishingInterval_;
    publisher->keyFrameCount = keyFrameCount_;
    publisher->networkAddressUrl = networkAddressUrl_;
    publisher->SAMYRobotVariableNodeID = SAMYRobotVariableNodeID_;
    publisher->MQTTLogin = UA_TRUE;
    publisher->JSONEncoding = JSONEncoding_;
    setPublisherMQTT_PubSubConnectionWithLogin(publisher, login_);
    setPublisherMQTT_PublishedDataSet(publisher);
    setPublisherMQTT_DataSetField(publisher);
    setPublisherMQTT_WriterGroup(publisher);
    setPublisherMQTT_DataSetWriter(publisher);
}
void configurePublisherMQTT_WithoutLogin(Publisher_MQTT* publisher, UA_UInt32 numericID_, UA_String name_,
                            UA_UInt16 publishingInterval_, UA_UInt32 keyFrameCount_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_, UA_NodeId SAMYRobotVariableNodeID_,
                                    UA_Boolean JSONEncoding_){
    publisher->numericID = numericID_;
    publisher->name = name_;
    publisher->publishingInterval = publishingInterval_;
    publisher->keyFrameCount = keyFrameCount_;
    publisher->networkAddressUrl = networkAddressUrl_;
    publisher->SAMYRobotVariableNodeID = SAMYRobotVariableNodeID_;
    publisher->MQTTLogin = UA_FALSE;
    publisher->JSONEncoding = JSONEncoding_;
    setPublisherMQTT_PubSubConnectionWithoutLogin(publisher);
    setPublisherMQTT_PublishedDataSet(publisher);
    setPublisherMQTT_DataSetField(publisher);
    setPublisherMQTT_WriterGroup(publisher);
    setPublisherMQTT_DataSetWriter(publisher);
}
#else
void configurePublisherMQTT_WithLogin(Publisher_MQTT* publisher, UA_UInt32 numericID_, UA_String name_,
                            UA_UInt16 publishingInterval_, UA_UInt32 keyFrameCount_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_, UA_NodeId SAMYRobotVariableNodeID_,
                                    MQTT_LoginData login_){
    publisher->numericID = numericID_;
    publisher->name = name_;
    publisher->publishingInterval = publishingInterval_;
    publisher->keyFrameCount = keyFrameCount_;
    publisher->networkAddressUrl = networkAddressUrl_;
    publisher->SAMYRobotVariableNodeID = SAMYRobotVariableNodeID_;
    publisher->MQTTLogin = UA_TRUE;
    setPublisherMQTT_PubSubConnectionWithLogin(publisher, login_);
    setPublisherMQTT_PublishedDataSet(publisher);
    setPublisherMQTT_DataSetField(publisher);
    setPublisherMQTT_WriterGroup(publisher);
    setPublisherMQTT_DataSetWriter(publisher);
}
void configurePublisherMQTT_WithoutLogin(Publisher_MQTT* publisher, UA_UInt32 numericID_, UA_String name_,
                            UA_UInt16 publishingInterval_, UA_UInt32 keyFrameCount_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_, UA_NodeId SAMYRobotVariableNodeID_){
    printf("\n AQUI conf -----------------   0");

    printf("\n AQUI conf -----------------   1");
    publisher->numericID = numericID_;
    publisher->name = name_;
    publisher->publishingInterval = publishingInterval_;
    publisher->keyFrameCount = keyFrameCount_;
    publisher->networkAddressUrl = networkAddressUrl_;
    publisher->SAMYRobotVariableNodeID = SAMYRobotVariableNodeID_;
    publisher->MQTTLogin = UA_FALSE;
    publisher->JSONEncoding = JSONEncoding_;
    setPublisherMQTT_PubSubConnectionWithoutLogin(publisher);
    setPublisherMQTT_PublishedDataSet(publisher);
    setPublisherMQTT_DataSetField(publisher);
    setPublisherMQTT_WriterGroup(publisher);
    setPublisherMQTT_DataSetWriter(publisher);
}
#endif

/*Adding PublisherMQTT to the server*/
UA_StatusCode addPublisherMQTT_ToServer(UA_Server* server, Publisher_MQTT* publisher){
    if((server == NULL) || (&(publisher->connectionConfig.transportProfileUri) == NULL) ||
        (&(publisher->networkAddressUrl) == NULL)) {
        return UA_STATUSCODE_BADINTERNALERROR;
    }
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval |= addPublisherMQTT_PubSubConnectionToServer(server, publisher);
    retval |= addPublisherMQTT_PublishedDataSetToServer(server, publisher);
    retval |= addPublisherMQTT_DataSetFieldToServer(server, publisher);
    retval |= addPublisherMQTT_WriterGroupToServer(server, publisher);
    retval |= addPublisherMQTT_DataSetWriterToServer(server, publisher);
    return retval;
}

/* Publisher_MQTT functions end*/

#endif


