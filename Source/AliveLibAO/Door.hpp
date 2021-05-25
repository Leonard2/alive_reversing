#pragma once

#include "FunctionFwd.hpp"
#include "PathData.hpp"
#include "Map.hpp"
#include "BaseAnimatedWithPhysicsGameObject.hpp"
#include "Path.hpp"
#include "SwitchStates.hpp"

namespace AO {

enum class LevelIds : s16;

enum class DoorStates : s16
{
    eOpen_0 = 0,
    eClosed_1 = 1,
    eOpening_2 = 2,
    eClosing_3 = 3,
};

struct Path_Door final : public Path_TLV
{
    LevelIds field_18_level;
    s16 field_1A_path;
    s16 field_1C_camera;
    Scale_short field_1E_scale;
    u16 field_20_door_number;
    SwitchId field_22_id;
    s16 field_24_target_door_number;
    DoorStates field_26_start_state;
    Choice_short field_28_door_closed;
    SwitchId field_2A_hub1;
    SwitchId field_2C_hub2;
    SwitchId field_2E_hub3;
    SwitchId field_30_hub4;
    SwitchId field_32_hub5;
    SwitchId field_34_hub6;
    SwitchId field_36_hub7;
    SwitchId field_38_hub8;
    s16 field_3A_wipe_effect;
    s16 field_3C_movie_number;
    s16 field_3E_x_offset;
    s16 field_40_y_offset;
    s16 field_42_wipe_x_org;
    s16 field_44_wipe_y_org;
    XDirection_short field_46_abe_direction;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_Door, 0x48);

class Door final : public BaseAnimatedWithPhysicsGameObject
{
public:
    EXPORT Door* ctor_40E010(Path_Door* pTlv, s32 tlvInfo);

    EXPORT BaseGameObject* dtor_40E710();

    virtual void VScreenChanged() override;

    EXPORT void VScreenChanged_40EDE0();

    virtual BaseGameObject* VDestructor(s32 flags) override;

    EXPORT Door* Vdtor_40EDF0(s32 flags);

    EXPORT BOOL vIsOpen_40E800();

    EXPORT void vOpen_40E810();

    EXPORT void vClose_40E830();

    EXPORT void vSetOpen_40E850();

    EXPORT void vSetClosed_40E860();

    EXPORT void PlaySound_40E780();

    virtual void VUpdate() override;

    EXPORT void VUpdate_40E870();

    s32 field_D4[4];
    s32 field_E4_tlvInfo;
    DoorStates field_E8_start_state;
    s16 field_EA_door_number;
    DoorStates field_EC_current_state;
    Choice_short field_EE_door_closed;
    SwitchId field_F0_switch_id;
    SwitchId field_F2_hubs_ids[8];
    s16 field_102_pad;
};
ALIVE_ASSERT_SIZEOF(Door, 0x104);

} // namespace AO
