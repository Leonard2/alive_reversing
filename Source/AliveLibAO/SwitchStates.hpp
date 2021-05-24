#pragma once

#include "SwitchStates_common.hpp"
#include "FunctionFwd.hpp"

namespace AO {

struct SwitchStates final : public ::SwitchStates
{
	static constexpr s8* GetAOBeaten(SwitchStates *ptr) { return &ptr->mData[70]; }
};
ALIVE_ASSERT_SIZEOF_ALWAYS(SwitchStates, 256);

ALIVE_VAR_EXTERN(SwitchStates, sSwitchStates_505568);

} // namespace AO
