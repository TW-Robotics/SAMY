#ifndef PROGRAMSTATE_H
#define PROGRAMSTATE_H
#include <open62541/types.h>
#include <string>
#include <map>
#include <memory>

namespace SAMY {

    enum class ProgramStateNumber : UA_UInt32 {
        INVALID = 0,
        HALTED = 11,
        READY = 12,
        RUNNING = 13,
        SUSPENDED = 14
    };

    const std::map<ProgramStateNumber, std::string> ProgramStateName = {
            {ProgramStateNumber::INVALID,   "INVALID"},
            {ProgramStateNumber::HALTED,    "HALTED"},
            {ProgramStateNumber::READY,     "READY"},
            {ProgramStateNumber::RUNNING,   "RUNNING"},
            {ProgramStateNumber::SUSPENDED, "SUSPENDED"}
    };

    class ProgramState {
    public:
        ProgramState() = delete;

        explicit ProgramState(
                const ProgramStateNumber number,
                std::shared_ptr<UA_NodeId> id,
                const UA_LocalizedText name
        )
                : number(number), id(std::move(id)), name(name) {
        }

        const UA_LocalizedText getName() const { return name; }

        const UA_NodeId* getId() const { return id.get(); }

        const ProgramStateNumber getNumber() const { return number; }

    private:
        ProgramStateNumber number;
        std::shared_ptr<UA_NodeId> id;
        UA_LocalizedText name;
    };

}

#endif
