#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <open62541/plugin/log_stdout.h>
/* Files namespace_foo_flt_generated.h and namespace_foo_flt_generated.c are created from FooFlt.NodeSet2.xml in the
 * /src_generated directory by CMake */
#include "namespace_crcl_generated.h"
#include <signal.h>
#include <stdlib.h>

#include <open62541/plugin/pubsub_udp.h>
#include <open62541/types_generated.h>

#include "ua_pubsub.h"
#include "ua_network_pubsub_mqtt.h"

#ifdef UA_ENABLE_PUBSUB_ETH_UADP
#include <open62541/plugin/pubsub_ethernet.h>
#endif

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define PUBLISHER_METADATAUPDATETIME 0

#ifdef AAA
typedef struct {
    UA_UInt32 numericID;
    UA_String name;
    UA_UInt16 publishingInterval;
    UA_UInt32 keyFrameCount;
    UA_NetworkAddressUrlDataType networkAddressUrl;
    UA_NodeId SAMYRobotVariableNodeID;
    UA_PubSubConnectionConfig connectionConfig;
    UA_WriterGroupConfig writerGroupConfig;
    UA_DataSetWriterConfig dataSetWriterConfig;
    UA_PublishedDataSetConfig publishedDataSetConfig;
    UA_DataSetFieldConfig dataSetFieldConfig;
    UA_NodeId connectionIdent, publishedDataSetIdent, writerGroupIdent, dataSetWriterIdent, dataSetFieldIdent;
//Custom Callback Function For Publishing So Robot Information Can Be Updated Automatically
} Publisher_UADP;

void setPublisherUADP_PubSubConnection(Publisher_UADP* publisher);
UA_StatusCode addPublisherUADP_PubSubConnectionToServer(UA_Server *server, Publisher_UADP* publisher);
void setPublisherUADP_PublishedDataSet(Publisher_UADP* publisher);
UA_StatusCode addPublisherUADP_PublishedDataSetToServer(UA_Server *server, Publisher_UADP* publisher);
void setPublisherUADP_DataSetField(Publisher_UADP* publisher);
UA_StatusCode addPublisherUADP_DataSetFieldToServer(UA_Server *server, Publisher_UADP* publisher);
void setPublisherUADP_WriterGroup(Publisher_UADP* publisher);
UA_StatusCode addPublisherUADP_WriterGroupToServer(UA_Server* server, Publisher_UADP* publisher);
void setPublisherUADP_DataSetWriter(Publisher_UADP* publisher);
UA_StatusCode addPublisherUADP_DataSetWriterToServer(UA_Server *server, Publisher_UADP* publisher);

void configurePublisherUADP(Publisher_UADP* publisher, UA_UInt32 numericID_, UA_String name_,
                            UA_UInt16 publishingInterval_, UA_UInt32 keyFrameCount_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_, UA_NodeId SAMYRobotVariableNodeID_);
UA_StatusCode addPublisherUADP_ToServer(UA_Server* server, Publisher_UADP* publisher);

typedef struct {
    UA_UInt32 numericID;
    UA_String name;
    UA_UInt16 publishingInterval;
    UA_UInt32 keyFrameCount;
    UA_NodeId SAMYRobotVariableNodeID;
    UA_Boolean MQTTLogin;
    #ifdef UA_ENABLE_JSON_ENCODING
    UA_Boolean JSONEncoding;
    #endif
    UA_NetworkAddressUrlDataType networkAddressUrl;
    UA_PubSubConnectionConfig connectionConfig;
    UA_WriterGroupConfig writerGroupConfig;
    UA_DataSetWriterConfig dataSetWriterConfig;
    UA_PublishedDataSetConfig publishedDataSetConfig;
    UA_DataSetFieldConfig dataSetFieldConfig;
    UA_NodeId connectionIdent, publishedDataSetIdent,
                    writerGroupIdent, dataSetWriterIdent, dataSetFieldIdent;
//Custom Callback Function For Publishing So Robot Information Can Be Updated Automatically
} Publisher_MQTT;

typedef struct {
    UA_String USERNAME_OPTION_NAME;
    UA_String PASSWORD_OPTION_NAME;
    UA_String MQTT_USERNAME;
    UA_String MQTT_PASSWORD;
} MQTT_LoginData;

void setPublisherMQTT_PubSubConnectionWithLogin(Publisher_MQTT* publisher, MQTT_LoginData loginData_);
void setPublisherMQTT_PubSubConnectionWithoutLogin(Publisher_MQTT* publisher);
UA_StatusCode addPublisherMQTT_PubSubConnectionToServer(UA_Server* server, Publisher_MQTT* publisher);
void setPublisherMQTT_PublishedDataSet(Publisher_MQTT* publisher);
UA_StatusCode addPublisherMQTT_PublishedDataSetToServer(UA_Server* server, Publisher_MQTT* publisher);
void setPublisherMQTT_DataSetField(Publisher_MQTT* publisher);
UA_StatusCode addPublisherMQTT_DataSetFieldToServer(UA_Server* server, Publisher_MQTT* publisher);
void setPublisherMQTT_WriterGroup(Publisher_MQTT* publisher);
UA_StatusCode addPublisherMQTT_WriterGroupToServer(UA_Server* server, Publisher_MQTT* publisher);
void setPublisherMQTT_DataSetWriter(Publisher_MQTT* publisher);
UA_StatusCode addPublisherMQTT_DataSetWriterToServer(UA_Server* server, Publisher_MQTT* publisher);

#ifdef UA_ENABLE_JSON_ENCODING
void configurePublisherMQTT_WithLogin(Publisher_MQTT* publisher, UA_UInt32 numericID_, UA_String name_,
                            UA_UInt16 publishingInterval_, UA_UInt32 keyFrameCount_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_, UA_NodeId SAMYRobotVariableNodeID_,
                                    UA_Boolean JSONEncoding_, MQTT_LoginData login_);
void configurePublisherMQTT_WithoutLogin(Publisher_MQTT* publisher, UA_UInt32 numericID_, UA_String name_,
                            UA_UInt16 publishingInterval_, UA_UInt32 keyFrameCount_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_, UA_NodeId SAMYRobotVariableNodeID_,
                                    UA_Boolean JSONEncoding_);
#else
void configurePublisherMQTT_WithLogin(Publisher_MQTT* publisher, UA_UInt32 numericID_, UA_String name_,
                            UA_UInt16 publishingInterval_, UA_UInt32 keyFrameCount_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_, UA_NodeId SAMYRobotVariableNodeID_,
                                    MQTT_LoginData login_);
void configurePublisherMQTT_WithoutLogin(Publisher_MQTT* publisher, UA_UInt32 numericID_, UA_String name_,
                            UA_UInt16 publishingInterval_, UA_UInt32 keyFrameCount_,
                                UA_NetworkAddressUrlDataType networkAddressUrl_, UA_NodeId SAMYRobotVariableNodeID_);
#endif
UA_StatusCode addPublisherMQTT_ToServer(UA_Server* server, Publisher_MQTT* publisher);


typedef enum {
    PublisherTypeSwitch_NONE = 0,
    PublisherTypeSwitch_PUBLISHER_UADP = 1,
    PublisherTypeSwitch_PUBLISHER_MQTT = 2
} PublisherTypeSwitch;

typedef struct {
    PublisherTypeSwitch switchField;
    union {
        Publisher_UADP publisherUADP;
        Publisher_MQTT publisherMQTT;
    } publishers;
} Publisher;

#endif /*PUBLISHER_H*/

#endif
