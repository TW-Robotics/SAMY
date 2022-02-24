#ifndef PROGRAMTRANSITION_H
#define PROGRAMTRANSITION_H

#include <string>
#include <map>
#include <memory>
#include <open62541/types.h>
#include <vector>

#include <ProgramState.h>

namespace SAMY{
        enum class ProgramTransitionNumber {
            HALTED_TO_READY = 1,
            READY_TO_RUNNING = 2,
            RUNNING_TO_HALTED = 3,
            RUNNING_TO_READY = 4,
            RUNNING_TO_SUSPENDED = 5,
            SUSPENDED_TO_RUNNING = 6,
            SUSPENDED_TO_HALTED = 7,
            SUSPENDED_TO_READY = 8,
            READY_TO_HALTED = 9,
        };

        class ProgramTransition{
        public:
            explicit ProgramTransition(
                    const ProgramTransitionNumber number,
                    std::shared_ptr<UA_NodeId> id,
                    const UA_LocalizedText name,
                    ProgramStateNumber from,
                    ProgramStateNumber to
            ) : number(number),
                id(std::move(id)),
                name(name),
                from(from), to(to) {}

            const UA_LocalizedText getName() const { return name; }

            const UA_NodeId* getId() const { return id.get(); }

            const ProgramTransitionNumber getNumber() const { return number; }

            const ProgramStateNumber getFrom() const { return from; }

            const ProgramStateNumber getTo() const { return to; }

        private:
            ProgramTransitionNumber number;
            std::shared_ptr<UA_NodeId> id;
            UA_LocalizedText name;
            ProgramStateNumber from;
            ProgramStateNumber to;
        };
}

#endif
