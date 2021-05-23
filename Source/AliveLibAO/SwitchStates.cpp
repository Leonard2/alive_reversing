#include "stdafx_ao.h"
#include "SwitchStates.hpp"
#include "Function.hpp"


namespace AO {

ALIVE_VAR(1, 0x505568, SwitchStates, sSwitchStates_505568, {});

EXPORT void CC SwitchStates_Do_Operation_436A10(SwitchId idx, SwitchOp operation)
{   // Intentionally not declared in the header.
    sSwitchStates_505568.Operation(idx , operation);
}

} // namespace AO
