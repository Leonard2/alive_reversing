#pragma once

#include "Types.hpp"
#include "FunctionFwd.hpp"


struct SwitchId final
{
    u8 mId;
    u8 padding; // IDs were 16 bits in most used places.
};
ALIVE_ASSERT_SIZEOF_ALWAYS(SwitchId, 2);

enum class SwitchOp : s16
{
    eSetTrue_0 = 0,
    eSetFalse_1 = 1,
    eToggle_2 = 2,
    eIncrement_3 = 3,
    eDecrement_4 = 4,
};

struct SwitchStates
{
public:
    s8 Get(SwitchId id);
    void Set(SwitchId id, s8 value);
    void Add(SwitchId id, s8 value);
    void Operation(SwitchId id, SwitchOp op);

    void Clear();
    void ClearRange(SwitchId start, SwitchId end);

    void Save(u8 *to);
    void Load(const u8 *from);

protected:
    s8 mData[256];
};
ALIVE_ASSERT_SIZEOF_ALWAYS(SwitchStates, 256);
