#pragma once

#include "BaseGameObject.hpp"
#include "Path.hpp"
#include "FunctionFwd.hpp"
#include "SwitchStates.hpp"


struct Path_MultiSwitchController final : public Path_TLV
{
    SwitchId field_10_id;
    SwitchOp field_12_operation;
    u16 field_14_delay;
    SwitchId field_16_id1;
    SwitchId field_18_id2;
    SwitchId field_1A_id3;
    SwitchId field_1C_id4;
    SwitchId field_1E_id5;
    SwitchId field_20_id6;
    s16 field_22_pad;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_MultiSwitchController, 0x24);

class MultiSwitchController final : public BaseGameObject
{
public:
    virtual BaseGameObject* VDestructor(s32 flags) override;
    virtual void VUpdate() override;
    virtual void VScreenChanged() override;
    EXPORT MultiSwitchController* ctor_4D60E0(Path_MultiSwitchController* pTlv, u32 tlvInfo);

private:
    EXPORT MultiSwitchController* vdtor_4D61A0(s32 flags);
    EXPORT void dtor_4D61D0();
    EXPORT void vScreenChanged_4D6860();
    EXPORT void vUpdate_4D6250();
    EXPORT void WaitingForAllOn_4D6290();
    EXPORT void WaitingForAllOff_4D65B0();

private:
    SwitchId field_20_id1;
    SwitchId field_22_id2;
    SwitchId field_24_id3;
    SwitchId field_26_id4;
    SwitchId field_28_id5;
    SwitchId field_2A_id6;
    SwitchId field_2C_id;
    SwitchOp field_2E_operation;
    s32 field_30_tlvInfo;
    s32 field_34_last_switch_on_time;
    s32 field_38_all_switches_on_or_off_time;
    s32 field_3C_delay;
    enum Flags_40
    {
        eBit1_is_on = 0x1,
    };
    BitField16<Flags_40> field_40_flags;
    //s16 field_42; // pad
};
ALIVE_ASSERT_SIZEOF(MultiSwitchController, 0x44);
