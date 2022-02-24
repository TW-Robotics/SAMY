#ifndef OPCUASERVER_H
#define OPCUASERVER_H

#include <open62541/server.h>

#include <spdlog/logger.h>

#include "synchronized.hpp"
#include <samycoreConfig.h>

// use recursive mutex to allow multiple locks within the same thread, but not between different threads
typedef locked_ptr<UA_Server, std::recursive_mutex> LockedServer;
typedef synchronized<UA_Server> MutexedServer;

namespace SAMY {
    namespace OPCUA {

        class OpcUaServer{
        private:
            const std::string clientAppUri;
            const std::string clientAppName;
            UA_UInt64 periodicCallbackId = 0;

        protected:
            std::shared_ptr<spdlog::logger> logger;
            std::shared_ptr<spdlog::logger> loggerUaServer;

            UA_Server* server = nullptr;

            UA_ServerConfig* serverConfig = nullptr;
        public:
            explicit OpcUaServer(
                    const SAMYCoreConfig& parsedServerConfig,
                    std::shared_ptr<spdlog::logger> logger
            );

            explicit OpcUaServer(
                    const SAMYCoreConfig& parsedServerConfig,
                    std::shared_ptr<spdlog::logger> loggerApp,
                    std::shared_ptr<spdlog::logger> loggerUaServer,
                    UA_ServerConfig* uaServerConfig
            );

            virtual ~OpcUaServer();

            UA_ServerConfig* getServerConfig();

            void iterate(bool waitInternal = false);

            LockedServer getLocked();

            UA_StatusCode init();
        };
    }
}


#endif //OPCUASERVER_H
