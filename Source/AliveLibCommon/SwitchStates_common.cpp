#include "SwitchStates_common.hpp"
#include <cstring> // memset, memcpy


s8 SwitchStates::Get(SwitchId id)
{
	if (id.mId == 0)
		return 0;
	else if (id.mId == 1)
		return 1;
	else
		return mData[id.mId];
}

void SwitchStates::Set(SwitchId id, s8 val)
{
	mData[id.mId] = val;
}

void SwitchStates::Operation(SwitchId id, SwitchOp op)
{
    if (id.mId >= 2)
    {
        switch (op)
        {
        case SwitchOp::eSetTrue_0:
            Set(id, 1);
            break;

        case SwitchOp::eSetFalse_1:
            Set(id, 0);
            break;

        case SwitchOp::eToggle_2:
            if (Get(id) != 0)
                Set(id, 0);
            else
                Set(id, 1);
            break;

        case SwitchOp::eIncrement_3:
            mData[id.mId]++;
            break;

        case SwitchOp::eDecrement_4:
            mData[id.mId]--;
            break;
        }
    }
}

void SwitchStates::Clear()
{
    *this = { };
}

void SwitchStates::ClearRange(SwitchId start, SwitchId end)
{
    if (start.mId <= end.mId)
    {
        memset(&mData[start.mId], 0, end.mId - start.mId + 1);
    }
}

void SwitchStates::Save(u8* to)
{
    memcpy(to, &mData[0], sizeof(mData));
}

void SwitchStates::Load(const u8* from)
{
    memcpy(&mData[0], from, sizeof(mData));
}
