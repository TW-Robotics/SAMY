#include <samycore.h>

UA_Boolean running = true;
static void stopHandler(int sign){
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

int main(int argc, char** argv){

    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    if (argc != 2) return -1;

    SAMY::SAMYCore core{argv[1]};
    core.run( running );

    return 0;
}
