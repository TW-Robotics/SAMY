#include <OpcUaServer.h>

#include <open62541/types.h>

#include "helper.hpp"
#include <utility>
#include "logging.h"
#include <iostream>

namespace SAMY {
namespace OPCUA {

    OpcUaServer::OpcUaServer(
            const SAMYCoreConfig& parsedServerConfig,
            std::shared_ptr<spdlog::logger> logger
    ) :
        logger(logger)
    {
        loggerUaServer = logger->clone(logger->name() + "-ua-server");

        SAMY::Logging::LoggerFactory::setLoggerLevel(loggerUaServer, parsedServerConfig.serverLoggingLevel);

        serverConfig = (UA_ServerConfig*) UA_malloc(sizeof(UA_ServerConfig));
        if (!serverConfig)
        {
            logger->error("Can not create server config");
            throw std::runtime_error("Cannot create server config");
        }

        if (SAMY::OPCUA::initServerConfig(
                loggerUaServer,
                serverConfig,
                parsedServerConfig.appUri,
                parsedServerConfig.appName,
                (UA_UInt16) parsedServerConfig.serverPort,
                parsedServerConfig.encryption,
                parsedServerConfig.anonymous,
                parsedServerConfig.certificatesPath) != UA_STATUSCODE_GOOD)
        {
            throw std::runtime_error("Cannot initialize server config");
        }

        server = UA_Server_newWithConfig(serverConfig);

        if (!server){
            logger->error("Can not create server instance");
            throw std::runtime_error("Cannot create server instance");
        }
    }

    OpcUaServer::OpcUaServer(const SAMYCoreConfig &parsedServerConfig,
            std::shared_ptr<spdlog::logger> loggerApp,
            std::shared_ptr<spdlog::logger> loggerUaServer,
            UA_ServerConfig* uaServerConfig
    ) :
            logger(std::move(loggerApp)),
            loggerUaServer(std::move(loggerUaServer))
    {
        // this is not a deep copy, therefore the server config needs to persist outside of this method
        serverConfig = uaServerConfig;

        server = UA_Server_newWithConfig(serverConfig);
        if (!server){
            logger->error("Can not create server instance");
            throw std::runtime_error("Cannot create server instance");
        }
    }

    OpcUaServer::~OpcUaServer()
    {
        std::lock_guard<std::recursive_mutex> lc(SAMY::OPCUA::serverMutex);
        if (server){
            UA_Server_run_shutdown(server);
            UA_Server_delete(server);
        }
        UA_free(serverConfig);
    }

    UA_ServerConfig* OpcUaServer::getServerConfig()
    {
        // no need to lock here, the server config cannot be changed after Server is running
        return UA_Server_getConfig(server);
    }

    void OpcUaServer::iterate(bool waitInternal)
    {
        std::lock_guard<std::recursive_mutex> lc(SAMY::OPCUA::serverMutex);
        UA_Server_run_iterate(server, waitInternal);
    }

    LockedServer OpcUaServer::getLocked()
    {
        return LockedServer{server, SAMY::OPCUA::serverMutex};
    }

    UA_StatusCode OpcUaServer::init( ) {

        UA_StatusCode retval = UA_Server_run_startup(server);
        if (retval != UA_STATUSCODE_GOOD) {
            logger->error("Starting up the server failed with " + std::string(UA_StatusCode_name(retval)));
            return retval;
        }

        std::string endpoint;

        UA_ServerConfig* conf = UA_Server_getConfig(server);
        for (size_t i = 0; i < conf->networkLayersSize; i++) {
            if (!endpoint.empty())
                endpoint += ", ";
            endpoint += std::string((char*) conf->networkLayers[i].discoveryUrl.data, conf->networkLayers[i].discoveryUrl.length);
        }

        logger->info("OPC UA Server initialized: {}", endpoint);

        return UA_STATUSCODE_GOOD;
    }
}
}
