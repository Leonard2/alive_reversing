#pragma once

#include "FunctionFwd.hpp"
#include "../AliveLibCommon/SwitchStates_common.hpp"


void SwitchStates_ForceLink();

namespace NamedSwitchIDs
{
	constexpr SwitchId Min =							{2};
	constexpr SwitchId GameEnder_GoodEndingTrap =		{100};
	constexpr SwitchId Feeco_BonewerkzToSoulstorm =		{250};
	constexpr SwitchId Feeco_SligsToSoulstorm =			{251};
	constexpr SwitchId Feeco_FeecoEnderToSoulstorm =	{253};
	constexpr SwitchId Feeco_SligsToFeecoEnder =		{254};
	constexpr SwitchId Feeco_BonewerkzToFeecoEnder =	{255};
}

ALIVE_VAR_EXTERN(SwitchStates, sSwitchStates_5C1A28);
