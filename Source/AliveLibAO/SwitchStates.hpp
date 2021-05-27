#pragma once

#include "SwitchStates_common.hpp"
#include "FunctionFwd.hpp"


namespace NamedSwitchIDs
{
	constexpr SwitchId AO_GameBeaten =			{70};
	constexpr SwitchId Forest_ElumWell =		{120};
	constexpr SwitchId OneShotIDSetter_Init =	{236};
}

namespace AO {

struct SwitchStates final : public ::SwitchStates
{
	static constexpr s8* GetAOBeaten(SwitchStates *ptr) { return &ptr->mData[NamedSwitchIDs::AO_GameBeaten.mId]; }
};
ALIVE_ASSERT_SIZEOF_ALWAYS(SwitchStates, 256);

ALIVE_VAR_EXTERN(SwitchStates, sSwitchStates_505568);

} // namespace AO
