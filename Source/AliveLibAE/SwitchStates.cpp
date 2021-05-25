#include "stdafx.h"
#include "SwitchStates.hpp"
#include "Function.hpp"


ALIVE_VAR(1, 0x5c1a28, SwitchStates, sSwitchStates_5C1A28, {});

void SwitchStates_ForceLink()
{ }

// These are intentionally not declared in the header.
EXPORT void CC SwitchStates_SetRange_465FA0(SwitchId start, SwitchId end)
{
    sSwitchStates_5C1A28.ClearRange(start, end);
}

EXPORT void CC SwitchStates_Set_465FF0(SwitchId idx, s8 value)
{
    sSwitchStates_5C1A28.Set(idx, value);
}

EXPORT s32 CC SwitchStates_Get_466020(SwitchId idx)
{
    return sSwitchStates_5C1A28.Get(idx);
}

EXPORT void CC SwitchStates_Add_466060(SwitchId idx, s8 value)
{
    sSwitchStates_5C1A28.Add(idx, value);
}

EXPORT void CC SwitchStates_Do_Operation_465F00(SwitchId idx, SwitchOp operation)
{
    sSwitchStates_5C1A28.Operation(idx, operation);
}
