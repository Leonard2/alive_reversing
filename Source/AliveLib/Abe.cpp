#include "stdafx.h"
#include "Abe.hpp"
#include "Function.hpp"
#include "Map.hpp"
#include "Midi.hpp"
#include "Sfx.hpp"
#include "DebugHelpers.hpp"
#include "stdlib.hpp"
#include "Shadow.hpp"
#include "ObjectIds.hpp"
#include "Input.hpp"
#include "Events.hpp"
#include "QuikSave.hpp"
#include "MainMenu.hpp"
#include "ThrowableArray.hpp"
#include "MusicController.hpp"
#include "Path.hpp"

using TAbeStateFunction = decltype(&Abe::State_0_Idle_44EEB0);

#define ABE_STATES_ENUM(ENTRY) \
    ENTRY(State_0_Idle_44EEB0) \
    ENTRY(State_1_WalkLoop_44FBA0) \
    ENTRY(State_2_StandingTurn_451830) \
    ENTRY(State_3_Fall_459B60) \
    ENTRY(State_4_WalkEndLeftFoot_44FFC0) \
    ENTRY(State_5_WalkEndRightFoot_00450080) \
    ENTRY(State_6_WalkBegin_44FEE0) \
    ENTRY(State_7_45B140) \
    ENTRY(State_8_45B160) \
    ENTRY(State_9_45B180) \
    ENTRY(State_10_Fart_45B1A0) \
    ENTRY(State_11_Speak_45B0A0) \
    ENTRY(State_12_Null_4569C0) \
    ENTRY(State_13_HoistBegin_452B20) \
    ENTRY(State_14_HoistIdle_452440) \
    ENTRY(State_15_HoistLand_452BA0) \
    ENTRY(State_16_LandSoft_45A360) \
    ENTRY(State_17_CrouchIdle_456BC0) \
    ENTRY(State_18_CrouchToStand_454600) \
    ENTRY(State_19_StandToCrouch_453DC0) \
    ENTRY(State_20_454550) \
    ENTRY(jState_21_4545E0) \
    ENTRY(State_22_RollBegin_4539A0) \
    ENTRY(State_23_RollLoop_453A90) \
    ENTRY(State_24_453D00) \
    ENTRY(State_25_RunSlideStop_451330) \
    ENTRY(State_26_RunTurn_451500) \
    ENTRY(State_27_HopBegin_4521C0) \
    ENTRY(State_28_HopMid_451C50) \
    ENTRY(State_29_HopLand_4523D0) \
    ENTRY(State_30_RunJumpBegin_4532E0) \
    ENTRY(State_31_RunJumpMid_452C10) \
    ENTRY(State_32_RunJumpLand_453460) \
    ENTRY(State_33_RunLoop_4508E0) \
    ENTRY(State_34_DunnoBegin_44ECF0) \
    ENTRY(State_35_DunnoEnd_44ED10) \
    ENTRY(State_36_Null_45BC50) \
    ENTRY(State_37_CrouchTurn_454390) \
    ENTRY(jState_38_RollBegin_453A70) \
    ENTRY(State_39_StandingToRun_450D40) \
    ENTRY(State_40_SneakLoop_450550) \
    ENTRY(State_41_450250) \
    ENTRY(State_42_4503D0) \
    ENTRY(State_43_450380) \
    ENTRY(State_44_450500) \
    ENTRY(State_45_SneakBegin_4507A0) \
    ENTRY(State_46_SneakEnd_450870) \
    ENTRY(jState_47_SneakEnd_4508C0) \
    ENTRY(State_48_4500A0) \
    ENTRY(State_49_450200) \
    ENTRY(State_50_RunToWalk1_450E20) \
    ENTRY(State_51_RunToWalk2_450F50) \
    ENTRY(State_52_451710) \
    ENTRY(State_53_451800) \
    ENTRY(State_54_RunJumpLandRun_4538F0) \
    ENTRY(State_55_RunJumpLandWalk_453970) \
    ENTRY(State_56_4591F0) \
    ENTRY(State_57_Dead_4589A0) \
    ENTRY(State_58_DeadPre_4593E0) \
    ENTRY(State_59_Null_459450) \
    ENTRY(State_60_4A3200) \
    ENTRY(State_61_TurnToRun_456530) \
    ENTRY(State_62_Punch_454750) \
    ENTRY(State_63_Sorry_454670) \
    ENTRY(State_64_454730) \
    ENTRY(State_65_LedgeAscend_4548E0) \
    ENTRY(State_66_LedgeDescend_454970) \
    ENTRY(State_67_LedgeHang_454E20) \
    ENTRY(State_68_454B80) \
    ENTRY(State_69_LedgeHangWobble_454EF0) \
    ENTRY(State_70_RingRopePull_455AF0) \
    ENTRY(State_71_Knockback_455090) \
    ENTRY(State_72_KnockbackGetUp_455340) \
    ENTRY(State_73_PushWall_4553A0) \
    ENTRY(State_74_455290) \
    ENTRY(State_75_45C7B0) \
    ENTRY(State_76_45CA40) \
    ENTRY(State_77_45D130) \
    ENTRY(State_78_WellBegin_45C810) \
    ENTRY(State_79_WellInside_45CA60) \
    ENTRY(State_80_WellShotOut_45D150) \
    ENTRY(jState_81_WellBegin_45C7F0) \
    ENTRY(State_82_45CC80) \
    ENTRY(State_83_45CF70) \
    ENTRY(State_84_FallLandDie_45A420) \
    ENTRY(jState_85_Fall_455070) \
    ENTRY(State_86_HandstoneBegin_45BD00) \
    ENTRY(State_87_HandstoneEnd_45C4F0) \
    ENTRY(State_88_GrenadeMachineUse_45C510) \
    ENTRY(State_89_BrewMachineBegin_4584C0) \
    ENTRY(State_90_BrewMachineEnd_4585B0) \
    ENTRY(State_91_RingRopePullEnd_4557B0) \
    ENTRY(State_92_455800) \
    ENTRY(State_93_FallLedgeBegin_455970) \
    ENTRY(jState_94_FallLedgeBegin_4559A0) \
    ENTRY(jState_95_FallLedgeBegin_4559C0) \
    ENTRY(State_96_4559E0) \
    ENTRY(jState_97_FallLedgeBegin_455A80) \
    ENTRY(jState_98_FallLedgeBegin_455AA0) \
    ENTRY(State_99_LeverUse_455AC0) \
    ENTRY(State_100_455B60) \
    ENTRY(State_101_KnockForward_455420) \
    ENTRY(State_102_455310) \
    ENTRY(jState_103_KnockbackGetUp_455380) \
    ENTRY(State_104_RockThrowStandingHold_455DF0) \
    ENTRY(State_105_RockThrowStandingThrow_456460) \
    ENTRY(State_106_RockThrowStandingEnd_455F20) \
    ENTRY(State_107_RockThrowCrouchingHold_454410) \
    ENTRY(State_108_RockThrowCrouchingThrow_454500) \
    ENTRY(State_109_455550) \
    ENTRY(State_110_455670) \
    ENTRY(State_111_GrabRock_4564A0) \
    ENTRY(State_112_Chant_45B1C0) \
    ENTRY(State_113_ChantEnd_45BBE0) \
    ENTRY(State_114_DoorEnter_459470) \
    ENTRY(State_115_DoorExit_459A40) \
    ENTRY(State_116_MineCarEnter_458780) \
    ENTRY(State_117_4587C0) \
    ENTRY(State_118_MineCarExit_458890) \
    ENTRY(State_119_45A990) \
    ENTRY(State_120_45AB00) \
    ENTRY(State_121_LiftGrabBegin_45A600) \
    ENTRY(State_122_LiftGrabEnd_45A670) \
    ENTRY(State_123_LiftGrabIdle_45A6A0) \
    ENTRY(State_124_LiftUseUp_45A780) \
    ENTRY(State_125_LiftUseDown_45A7B0) \
    ENTRY(State_126_TurnWheelBegin_456700) \
    ENTRY(State_127_TurnWheelLoop_456750) \
    ENTRY(State_128_TurnWheelEnd_4569A0) \
    ENTRY(State_129_PoisonGasDeath_4565C0)

#define MAKE_ENUM(VAR) VAR,
enum eAbeStates 
{
    ABE_STATES_ENUM(MAKE_ENUM)
};

#define MAKE_STRINGS(VAR) #VAR,
const char* const sAbeStateNames[130] =
{
    ABE_STATES_ENUM(MAKE_STRINGS)
};


TAbeStateFunction sAbeStateMachineTable_554910[130] =
{
    &Abe::State_0_Idle_44EEB0,
    &Abe::State_1_WalkLoop_44FBA0,
    &Abe::State_2_StandingTurn_451830,
    &Abe::State_3_Fall_459B60,
    &Abe::State_4_WalkEndLeftFoot_44FFC0,
    &Abe::State_5_WalkEndRightFoot_00450080,
    &Abe::State_6_WalkBegin_44FEE0,
    &Abe::State_7_45B140,
    &Abe::State_8_45B160,
    &Abe::State_9_45B180,
    &Abe::State_10_Fart_45B1A0,
    &Abe::State_11_Speak_45B0A0,
    &Abe::State_12_Null_4569C0,
    &Abe::State_13_HoistBegin_452B20,
    &Abe::State_14_HoistIdle_452440,
    &Abe::State_15_HoistLand_452BA0,
    &Abe::State_16_LandSoft_45A360,
    &Abe::State_17_CrouchIdle_456BC0,
    &Abe::State_18_CrouchToStand_454600,
    &Abe::State_19_StandToCrouch_453DC0,
    &Abe::State_20_454550,
    &Abe::jState_21_4545E0,
    &Abe::State_22_RollBegin_4539A0,
    &Abe::State_23_RollLoop_453A90,
    &Abe::State_24_453D00,
    &Abe::State_25_RunSlideStop_451330,
    &Abe::State_26_RunTurn_451500,
    &Abe::State_27_HopBegin_4521C0,
    &Abe::State_28_HopMid_451C50,
    &Abe::State_29_HopLand_4523D0,
    &Abe::State_30_RunJumpBegin_4532E0,
    &Abe::State_31_RunJumpMid_452C10,
    &Abe::State_32_RunJumpLand_453460,
    &Abe::State_33_RunLoop_4508E0,
    &Abe::State_34_DunnoBegin_44ECF0,
    &Abe::State_35_DunnoEnd_44ED10,
    &Abe::State_36_Null_45BC50,
    &Abe::State_37_CrouchTurn_454390,
    &Abe::jState_38_RollBegin_453A70,
    &Abe::State_39_StandingToRun_450D40,
    &Abe::State_40_SneakLoop_450550,
    &Abe::State_41_450250,
    &Abe::State_42_4503D0,
    &Abe::State_43_450380,
    &Abe::State_44_450500,
    &Abe::State_45_SneakBegin_4507A0,
    &Abe::State_46_SneakEnd_450870,
    &Abe::jState_47_SneakEnd_4508C0,
    &Abe::State_48_4500A0,
    &Abe::State_49_450200,
    &Abe::State_50_RunToWalk1_450E20,
    &Abe::State_51_RunToWalk2_450F50,
    &Abe::State_52_451710,
    &Abe::State_53_451800,
    &Abe::State_54_RunJumpLandRun_4538F0,
    &Abe::State_55_RunJumpLandWalk_453970,
    &Abe::State_56_4591F0,
    &Abe::State_57_Dead_4589A0,
    &Abe::State_58_DeadPre_4593E0,
    &Abe::State_59_Null_459450,
    &Abe::State_60_4A3200,
    &Abe::State_61_TurnToRun_456530,
    &Abe::State_62_Punch_454750,
    &Abe::State_63_Sorry_454670,
    &Abe::State_64_454730,
    &Abe::State_65_LedgeAscend_4548E0,
    &Abe::State_66_LedgeDescend_454970,
    &Abe::State_67_LedgeHang_454E20,
    &Abe::State_68_454B80,
    &Abe::State_69_LedgeHangWobble_454EF0,
    &Abe::State_70_RingRopePull_455AF0,
    &Abe::State_71_Knockback_455090,
    &Abe::State_72_KnockbackGetUp_455340,
    &Abe::State_73_PushWall_4553A0,
    &Abe::State_74_455290,
    &Abe::State_75_45C7B0,
    &Abe::State_76_45CA40,
    &Abe::State_77_45D130,
    &Abe::State_78_WellBegin_45C810,
    &Abe::State_79_WellInside_45CA60,
    &Abe::State_80_WellShotOut_45D150,
    &Abe::jState_81_WellBegin_45C7F0,
    &Abe::State_82_45CC80,
    &Abe::State_83_45CF70,
    &Abe::State_84_FallLandDie_45A420,
    &Abe::jState_85_Fall_455070,
    &Abe::State_86_HandstoneBegin_45BD00,
    &Abe::State_87_HandstoneEnd_45C4F0,
    &Abe::State_88_GrenadeMachineUse_45C510,
    &Abe::State_89_BrewMachineBegin_4584C0,
    &Abe::State_90_BrewMachineEnd_4585B0,
    &Abe::State_91_RingRopePullEnd_4557B0,
    &Abe::State_92_455800,
    &Abe::State_93_FallLedgeBegin_455970,
    &Abe::jState_94_FallLedgeBegin_4559A0,
    &Abe::jState_95_FallLedgeBegin_4559C0,
    &Abe::State_96_4559E0,
    &Abe::jState_97_FallLedgeBegin_455A80,
    &Abe::jState_98_FallLedgeBegin_455AA0,
    &Abe::State_99_LeverUse_455AC0,
    &Abe::State_100_455B60,
    &Abe::State_101_KnockForward_455420,
    &Abe::State_102_455310,
    &Abe::jState_103_KnockbackGetUp_455380,
    &Abe::State_104_RockThrowStandingHold_455DF0,
    &Abe::State_105_RockThrowStandingThrow_456460,
    &Abe::State_106_RockThrowStandingEnd_455F20,
    &Abe::State_107_RockThrowCrouchingHold_454410,
    &Abe::State_108_RockThrowCrouchingThrow_454500,
    &Abe::State_109_455550,
    &Abe::State_110_455670,
    &Abe::State_111_GrabRock_4564A0,
    &Abe::State_112_Chant_45B1C0,
    &Abe::State_113_ChantEnd_45BBE0,
    &Abe::State_114_DoorEnter_459470,
    &Abe::State_115_DoorExit_459A40,
    &Abe::State_116_MineCarEnter_458780,
    &Abe::State_117_4587C0,
    &Abe::State_118_MineCarExit_458890,
    &Abe::State_119_45A990,
    &Abe::State_120_45AB00,
    &Abe::State_121_LiftGrabBegin_45A600,
    &Abe::State_122_LiftGrabEnd_45A670,
    &Abe::State_123_LiftGrabIdle_45A6A0,
    &Abe::State_124_LiftUseUp_45A780,
    &Abe::State_125_LiftUseDown_45A7B0,
    &Abe::State_126_TurnWheelBegin_456700,
    &Abe::State_127_TurnWheelLoop_456750,
    &Abe::State_128_TurnWheelEnd_4569A0,
    &Abe::State_129_PoisonGasDeath_4565C0
};

SfxDefinition sAbeSFXList_555250[41] =
{
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 24u, 60u, 115u, 0, 0 },
    { 0u, 24u, 61u, 110u, 0, 0 },
    { 0u, 24u, 62u, 127u, 0, 0 },
    { 0u, 24u, 63u, 90u, 0, 0 },
    { 0u, 24u, 66u, 127u, 0, 0 },
    { 0u, 24u, 67u, 100u, 0, 0 },
    { 0u, 24u, 56u, 127u, 0, 0 },
    { 0u, 24u, 57u, 100u, 0, 0 },
    { 0u, 23u, 48u, 127u, 0, 0 },
    { 0u, 24u, 59u, 127u, 0, 0 },
    { 0u, 24u, 58u, 127u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 24u, 65u, 127u, 0, 0 },
    { 0u, 24u, 64u, 80u, 0, 0 },
    { 0u, 23u, 60u, 90u, 0, 0 },
    { 0u, 23u, 68u, 127u, 0, 0 },
    { 0u, 23u, 69u, 127u, 0, 0 },
    { 0u, 23u, 70u, 127u, 0, 0 },
    { 0u, 23u, 72u, 127u, 0, 0 },
    { 0u, 23u, 73u, 127u, 0, 0 },
    { 0u, 23u, 58u, 127u, 0, 0 },
    { 0u, 23u, 64u, 127u, 0, 0 },
    { 0u, 23u, 66u, 115u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 23u, 63u, 115u, 0, 0 },
    { 0u, 23u, 62u, 90u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 },
    { 0u, 0u, 0u, 0u, 0, 0 }
};

int sAbeFrameOffsetTable_554B18[130] =
{
    58888, 58808, 59064, 58888, 58788, 58748, 58768, 59028, 58992, 58956, 58920, 
    59112, 270240, 269976, 270024, 269928, 269928, 270092, 270060, 269876, 271080, 
    271120, 269688, 269708, 269764, 270860, 270328, 271004, 271056, 270964, 
    270468, 269804, 270488, 270748, 270180, 270616, 270180, 270428, 270708, 270252, 
    270508, 270688, 270596, 270840, 270728, 270288, 270160, 270308, 270120, 270268, 
    270668, 270820, 270408, 270140, 269784, 269856, 270092, 270092, 270092, 270092, 
    270092, 270944, 271152, 271192, 271248, 57440, 57580, 57540, 57540, 57712, 
    57680, 49740, 49800, 49912, 49856, 20572, 20552, 20552, 20404, 20552, 20552, 20404, 
    20552, 20552, 8104, 5724, 16096, 16040, 16220, 16096, 16040, 32012, 32012, 32040, 
    32068, 32112, 32168, 32152, 32132, 11396, 6520, 17240, 17180, 58888, 31504, 31392, 
    31632, 31576, 31432, 24580, 24628, 6004, 9992, 10040, 19040, 19088, 8540, 8540, 8588, 
    8732, 8772, 22548, 22572, 22464, 22596, 22496, 11856, 11816, 11888, 28824
};

TintEntry sTintTable_Abe_554D20[15] =
{
    { 1, 102u, 102u, 102u },
    { 2, 102u, 102u, 80u },
    { 3, 120u, 90u, 120u },
    { 4, 102u, 70u, 90u },
    { 5, 120u, 102u, 82u },
    { 6, 102u, 102u, 102u },
    { 7, 102u, 70u, 90u },
    { 8, 102u, 102u, 102u },
    { 9, 102u, 102u, 102u },
    { 10, 102u, 102u, 102u },
    { 11, 120u, 90u, 120u },
    { 12, 120u, 102u, 82u },
    { 13, 102u, 102u, 102u },
    { 14, 120u, 90u, 80u },
    { -1, 102u, 102u, 102u }
};

// Frame call backs ??
EXPORT int CC sub_455F40(void*, signed __int16*)
{
    return 1;
}

EXPORT int CC sub_455F60(void*, signed __int16*)
{
    return 1;
}

EXPORT int CC sub_455F80(void*, signed __int16*)
{
    // Does ray casting checks?
    NOT_IMPLEMENTED();
    return 1;
}

EXPORT int CC sub_4561B0(void*, signed __int16*)
{
    // Slurg squish check/particles?
    NOT_IMPLEMENTED();
    return 1;
}

EXPORT int CC sub_434130(void*, signed __int16*)
{
    // ??
    NOT_IMPLEMENTED();
    return 1;
}

using TFrameCallBackType = decltype(&sub_434130);

// TODO: Array is possibly bigger, called by AnimationEx::Invoke_CallBacks_40B7A0
ALIVE_ARY(1, 0x55EF98, TFrameCallBackType, 5, off_55EF98,
{
    sub_455F40,
    sub_455F60,
    sub_455F80,
    sub_4561B0,
    sub_434130
});

enum AbeResources
{
    eAbeBSic = 0,
    eAbeBSic1 = 1,
};

EXPORT int CC GridXMidPos_4498F0(FP scale, int unknown)
{
    if (scale == FP_FromDouble(0.5))
    {
        // 12.5 = half grid size
        return (13 * unknown) - 8;
    }

    if (scale == FP_FromDouble(1.0))
    {
        // 25 = full grid size
        return (25 * unknown) - 13;
    }

    // Default to middle of the screen
    return (374 / 2);
}

Abe* Abe::ctor_44AD10(int frameTableOffset, int /*a3*/, int /*a4*/, int /*a5*/)
{
    const int kResourceArraySize = 28;

    ctor_408240(kResourceArraySize);

    SetVTable(this, 0x5457BC); // gVTbl_Abe_5457BC
    
    field_4_typeId = Types::eType_Abe;

    field_6_flags.Set(BaseGameObject::eBit08);
    field_C_objectId = -65536;

    Init_GameStates_43BF40();

    // Zero out the resource array
    for (int i = 0; i < kResourceArraySize; i++)
    {
        field_10_resources_array.SetAt(i, nullptr);
    }

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbebasicResID, TRUE, FALSE))
    {
        ResourceManager::LoadResourceFile_49C170("ABEBSIC.BAN", nullptr);
        ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbebasicResID, TRUE, FALSE);
    }
    field_10_resources_array.SetAt(AbeResources::eAbeBSic, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbebasicResID, FALSE, FALSE));

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbebsic1ResID, TRUE, FALSE))
    {
        ResourceManager::LoadResourceFile_49C170("ABEBSIC1.BAN", nullptr);
        ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbebsic1ResID, TRUE, FALSE);
    }
    field_10_resources_array.SetAt(AbeResources::eAbeBSic1, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbebsic1ResID, FALSE, FALSE));

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeedgeResID, TRUE, FALSE))
    {
        ResourceManager::LoadResourceFile_49C170("ABEEDGE.BAN", nullptr);
        ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeedgeResID, TRUE, FALSE);
    }

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeknfdResID, TRUE, FALSE))
    {
        ResourceManager::LoadResourceFile_49C170("ABEKNFD.BAN", nullptr);
        ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeknfdResID, TRUE, FALSE);
    }

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeommResID, TRUE, FALSE))
    {
        ResourceManager::LoadResourceFile_49C170("ABEOMM.BAN", nullptr);
        ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeommResID, TRUE, FALSE);
    }

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeknbkResID, TRUE, FALSE))
    {
        ResourceManager::LoadResourceFile_49C170("ABEKNBK.BAN", nullptr);
        ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeknbkResID, TRUE, FALSE);
    }

    ResourceManager::LoadResourceFile_49C170("ABENOELM.BND", nullptr);
    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kAbefallResID);
    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kAbesmashResID);

    ResourceManager::LoadResourceFile_49C170("OMMFLARE.BAN", nullptr);
    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kOmmflareResID);

    ResourceManager::LoadResourceFile_49C170("SQBSMK.BAN", nullptr);
    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kSquibSmokeResID);

    ResourceManager::LoadResourceFile_49C170("DUST.BAN", nullptr);
    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kDustResID);

    ResourceManager::LoadResourceFile_49C170("BLOODROP.BAN", nullptr);
    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kBloodropResID);

    if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kRockShadowResID, FALSE, FALSE))
    {
        ResourceManager::LoadResourceFile_49C170("SHADOW.BAN", nullptr);
    }
    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kRockShadowResID);

    ResourceManager::LoadResourceFile_49C170("DEADFLR.BAN", nullptr);
    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kDeathFlareResID);

    ResourceManager::LoadResourceFile_49C170("DOVBASIC.BAN", nullptr);
    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kDovbasicResID);

    ResourceManager::LoadResourceFile_49C170("SPOTLITE.BAN", nullptr);
    Add_Resource_4DC130(ResourceManager::Resource_Animation, ResourceID::kSpotliteResID);

    field_128.field_10 = 1;

    Animation_Init_424E10(
        frameTableOffset,
        135, // Width
        80,  // Height
        field_10_resources_array.ItemAt(AbeResources::eAbeBSic1),
        1,
        1u);

    field_20_animation.field_1C_fn_ptr_array = off_55EF98;

    PSX_Point point = {};
    gMap_5C3030.GetCurrentCamCoords_480680(&point);

    field_B8_xpos = FP_FromInteger(point.field_0_x + GridXMidPos_4498F0(field_CC_sprite_scale, 4));
    field_BC_ypos = FP_FromInteger(point.field_2_y + 120);

    field_F8 = field_BC_ypos;
    field_128.field_8 = 0;
    field_128.field_C = 0;

    field_C4_velx = FP_FromInteger(0);
    field_C8_vely = FP_FromInteger(0);
    field_100_pCollisionLine = nullptr;
    field_106_animation_num = eAbeStates::State_3_Fall_459B60;
    field_122 = -1;
    field_20_animation.field_C_render_layer = 32;
    field_198_has_evil_fart = 0;
    field_1A2_rock_or_bone_count = 0;
    field_158 = -1;
    field_154 = -1;
    field_150 = -1;
    field_14C = -1;
    field_148 = -1;
    field_1A8 = -1;
    field_164 = -1;
    field_160 = -1;
    field_15C = -1;
    field_1AE &= ~3u;

    field_114_flags.Set(Flags_114::e114_Bit6);

    field_1AC_flags.Raw().all = 0;
    field_1AC_flags.Set(Flags_1AC::e1AC_Bit6);
    field_1AC_flags.Set(Flags_1AC::e1AC_Bit7);

    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit5);
    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit3);
    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit2);
    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit1);


    // Changes Abe's "default" colour depending on the level we are in
    SetTint_425600(&sTintTable_Abe_554D20[0], gMap_5C3030.sCurrentLevelId_5C3030);
    
    field_20_animation.field_4_flags.Set(AnimFlags::eBit15_bSemiTrans);
    field_20_animation.field_B_render_mode = 0;

    field_118 = 0;
    field_F6 = 0;
    field_120_state = 0;
    field_168 = 0;
    field_16E = 0;
    field_170 = 0;
    field_174 = 0;
    field_176 = 0;
    field_178_invisible_effect_id = -1;
    field_124_gnFrame = sGnFrame_5C1B84;
    field_FC_pPathTLV = nullptr;
    field_128.field_12_mood = 0;
    field_128.field_18 = -1;
    field_144 = 0;

    // Set Abe to be the current player controlled object
    sControlledCharacter_5C1B8C = this;

    // Create shadow
    field_E0_176_ptr = alive_new<Shadow>();
    if (field_E0_176_ptr)
    {
        field_E0_176_ptr->ctor_4AC990();
    }

    return this;
}

void Abe::dtor_44B380()
{
    SetVTable(this, 0x5457BC); // gVTbl_Abe_5457BC

    BaseGameObject* pField_148 = sObjectIds_5C1B70.Find_449CF0(field_148);
    BaseGameObject* pField_14C = sObjectIds_5C1B70.Find_449CF0(field_14C);
    BaseGameObject* pField_150 = sObjectIds_5C1B70.Find_449CF0(field_150);
    BaseGameObject* pField_154 = sObjectIds_5C1B70.Find_449CF0(field_154);
    BaseGameObject* pField_158 = sObjectIds_5C1B70.Find_449CF0(field_158);
    BaseGameObject* pField_15C = sObjectIds_5C1B70.Find_449CF0(field_15C);
    BaseGameObject* pField_160 = sObjectIds_5C1B70.Find_449CF0(field_160);
    BaseGameObject* pField_178 = sObjectIds_5C1B70.Find_449CF0(field_178_invisible_effect_id);

    SND_SEQ_Stop_4CAE60(0xAu);

    if (pField_148)
    {
        pField_148->field_6_flags.Set(BaseGameObject::eDead);
        field_148 = -1;
    }

    if (pField_160)
    {
        field_160 = -1;
    }

    if (pField_15C)
    {
        pField_15C->field_6_flags.Set(BaseGameObject::eDead);
        field_15C = -1;
    }

    if (pField_14C)
    {
        pField_14C->field_6_flags.Set(BaseGameObject::eDead);
        field_14C = -1;
    }

    if (pField_150)
    {
        pField_150->field_6_flags.Set(BaseGameObject::eDead);
        field_150 = -1;
    }

    if (pField_154)
    {
        field_154 = -1;
    }

    if (pField_158)
    {
        pField_158->field_6_flags.Set(BaseGameObject::eDead);
        field_158 = -1;
    }

    if (pField_178)
    {
        pField_178->field_6_flags.Set(BaseGameObject::eDead);
        field_178_invisible_effect_id = -1;
    }

    field_164 = -1;

    sActiveHero_5C1B68 = spAbe_554D5C;

    dtor_4080B0();
}

struct Quicksave_Obj_Abe
{
    WORD field_0_id;
    __int16 field_2;
    FP field_4_xpos;
    FP field_8_ypos;
    FP field_c_velx;
    FP field_10_vely;
    WORD field_14_path_number;
    WORD field_16_lvl_number;
    FP field_18_sprite_scale;
    WORD field_1C_scale;
    WORD field_1e_r;
    WORD field_20_g;
    WORD field_22_b;
    WORD word24;
    WORD word26;
    WORD word28;
    WORD word2A;
    char byte2C;
    char byte2D;
    char byte2E;
    char field_2F;
    FP field_30_health;
    WORD field_34_animation_num;
    WORD word36;
    WORD word38;
    WORD field_3a_collision_line_id;
    DWORD dword3C;
    WORD word40;
    WORD word42;
    char field_44_is_abe_controlled;
    char field_45;
    __int16 field_46;
    DWORD dword48;
    DWORD dword4C;
    DWORD dword50;
    DWORD dword54;
    DWORD dword58;
    DWORD dword5C;
    WORD word60;
    WORD word62;
    DWORD dword64;
    DWORD dword68;
    char field_6c_rock_bone_count;
    char byte6D;
    char byte6E;
    char byte6F;
    WORD word70;
    WORD word72;
    WORD word74;
    __int16 field_76;
    DWORD dword78;
    DWORD dword7C;
    DWORD dword80;
    DWORD dword84;
    DWORD dword88;
    DWORD dword8C;
    DWORD dword90;
    DWORD dword94;
    DWORD dword98;
    DWORD dword9C;
    WORD wordA0;
    WORD wordA2;
    char byteA4;
    char field_A5;
    __int16 field_A6;
    DWORD dwordA8;
    WORD wordAC;
    WORD wordAE;
    WORD wordB0;
    WORD wordB2;
    WORD wordB4;
    WORD wordB6;
    WORD wordB8;
    WORD wordBA;
    WORD wordBC;
    WORD wordBE;
    WORD wordC0;
    WORD wordC2;
    WORD wordC4;
    WORD wordC6;
    WORD wordC8;
    char field_ca_throw_direction;
    char field_CB;
    WORD wordCC;
    __int16 field_CE;
    DWORD dwordD0;
    WORD wordD4;
    WORD wordD6;
};
ALIVE_ASSERT_SIZEOF(Quicksave_Obj_Abe, 216);

const char* off_545830[22] =
{
    "ABEBASIC.BAN",
    "ABEBSIC1.BAN",
    "ABEPULL.BAN",
    "ABEPICK.BAN",
    "ABEBOMB.BAN",
    "ABETHROW.BAN",
    "ABESMASH.BAN",
    "ABEFALL.BAN",
    "ABESTONE.BAN",
    "ABEKNBK.BAN",
    "ABEKNFD.BAN",
    "ABEKNOKZ.BAN",
    "ABEHOIST.BAN",
    "ABEEDGE.BAN",
    "ABEDOOR.BAN",
    "ABEWELL.BAN",
    "ABEOMM.BAN",
    "ABELIFT.BAN",
    "ABECAR.BAN",
    "ABEMORPH.BAN",
    "ABEWORK.BAN",
    "ABEGAS.BAN",
};

int sAbeResourceIDTable_554D60[22] =
{
    10,
    55,
    11,
    12,
    13,
    14,
    19,
    20,
    21,
    26,
    27,
    28,
    42,
    43,
    45,
    47,
    48,
    53,
    113,
    117,
    515,
    118,
};

signed int CC Abe::CreateFromSaveState_44D4F0(const BYTE* pData)
{
    NOT_IMPLEMENTED();

    const Quicksave_Obj_Abe* pSaveState = reinterpret_cast<const Quicksave_Obj_Abe*>(pData);

    Abe* pAbe = sActiveHero_5C1B68;
    if (sActiveHero_5C1B68 == spAbe_554D5C)
    {
        pAbe = alive_new<Abe>();
        if (pAbe)
        {
            pAbe->ctor_44AD10(58808, 85, 57, 55);
        }
        sActiveHero_5C1B68 = pAbe;
    }

    if (pSaveState->field_44_is_abe_controlled)
    {
        sControlledCharacter_5C1B8C = pAbe;
    }

    pAbe->field_FC_pPathTLV = nullptr;
    sActiveHero_5C1B68->field_100_pCollisionLine = nullptr;
    sActiveHero_5C1B68->field_B8_xpos = pSaveState->field_4_xpos;
    sActiveHero_5C1B68->field_BC_ypos = pSaveState->field_8_ypos;
    sActiveHero_5C1B68->field_C4_velx = pSaveState->field_c_velx;
    sActiveHero_5C1B68->field_C8_vely = pSaveState->field_10_vely;
    sActiveHero_5C1B68->field_128.field_8 = pSaveState->dword48;
    sActiveHero_5C1B68->field_128.field_C = pSaveState->dword4C;
    sActiveHero_5C1B68->field_C0_path_number = pSaveState->field_14_path_number;
    sActiveHero_5C1B68->field_C2_lvl_number = pSaveState->field_16_lvl_number;
    sActiveHero_5C1B68->field_CC_sprite_scale = pSaveState->field_18_sprite_scale;
    sActiveHero_5C1B68->field_D6_scale = pSaveState->field_1C_scale;

    sActiveHero_5C1B68->field_114_flags.Clear(Flags_114::e114_Bit7);
    if (pSaveState->word40 & 1)
    {
        sActiveHero_5C1B68->field_114_flags.Set(Flags_114::e114_Bit7);
    }

    sActiveHero_5C1B68->field_114_flags.Clear(Flags_114::e114_Bit8);
    if (pSaveState->word42 & 1)
    {
        sActiveHero_5C1B68->field_114_flags.Set(Flags_114::e114_Bit8);
    }

    sActiveHero_5C1B68->field_106_animation_num = pSaveState->word26;
    BYTE** animFromState = sActiveHero_5C1B68->StateToAnimResource_44AAB0(sActiveHero_5C1B68->field_106_animation_num);
    if (!animFromState)
    {
        DWORD id = sAbeResourceIDTable_554D60[sActiveHero_5C1B68->field_128.field_10];
        ResourceManager::LoadResourceFile_49C170(off_545830[sActiveHero_5C1B68->field_128.field_10], 0);
        sActiveHero_5C1B68->field_10_resources_array.SetAt(sActiveHero_5C1B68->field_128.field_10, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, id, TRUE, FALSE));
        animFromState = sActiveHero_5C1B68->field_10_resources_array.ItemAt(sActiveHero_5C1B68->field_128.field_10);
    }

    sActiveHero_5C1B68->field_20_animation.Set_Animation_Data_409C80(sAbeFrameOffsetTable_554B18[sActiveHero_5C1B68->field_106_animation_num], animFromState);
    sActiveHero_5C1B68->field_20_animation.field_92_current_frame = pSaveState->word28;
    sActiveHero_5C1B68->field_20_animation.field_E_frame_change_counter = pSaveState->word2A;

    sActiveHero_5C1B68->field_20_animation.field_4_flags.Clear(AnimFlags::eBit5_FlipX);
    if (pSaveState->word24 & 1)
    {
        sActiveHero_5C1B68->field_20_animation.field_4_flags.Set(AnimFlags::eBit5_FlipX);
    }

    sActiveHero_5C1B68->field_20_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
    if (pSaveState->byte2D & 1)
    {
        sActiveHero_5C1B68->field_20_animation.field_4_flags.Set(AnimFlags::eBit3_Render);
    }

    sActiveHero_5C1B68->field_6_flags.Clear(BaseGameObject::eDrawable);
    if (pSaveState->byte2E & 1)
    {
        sActiveHero_5C1B68->field_6_flags.Set(BaseGameObject::eDrawable);
    }

    sActiveHero_5C1B68->field_20_animation.field_C_render_layer = pSaveState->byte2C;
    
    // TODO
    if (sActiveHero_5C1B68->field_20_animation.field_92_current_frame ==
        *(unsigned __int16 *)&(*sActiveHero_5C1B68->field_20_animation.field_20_ppBlock)[sActiveHero_5C1B68->field_20_animation.field_18_frame_table_offset + 2] - 1)
    {
        sActiveHero_5C1B68->field_20_animation.field_4_flags.Set(AnimFlags::eBit18_IsLastFrame);
    }

    FrameInfoHeader* pFrameHeader = sActiveHero_5C1B68->field_20_animation.Get_FrameHeader_40B730(-1);

    /* TODO
    sActiveHero_5C1B68->field_20_animation.Load_Pal_40A530(
        sActiveHero_5C1B68->field_20_animation.field_20_ppBlock,
        *(DWORD *)&(*sActiveHero_5C1B68->field_20_animation.field_20_ppBlock)[pFrameHeader->field_0_frame_header_offset]);
    */

    sActiveHero_5C1B68->SetTint_425600(sTintTable_Abe_554D20, gMap_5C3030.sCurrentLevelId_5C3030);
    sActiveHero_5C1B68->field_20_animation.field_B_render_mode = 0;
    sActiveHero_5C1B68->field_20_animation.field_4_flags.Set(AnimFlags::eBit15_bSemiTrans);
    sActiveHero_5C1B68->field_20_animation.field_4_flags.Clear(AnimFlags::eBit16_bBlending);
    sActiveHero_5C1B68->field_10C_health = pSaveState->field_30_health;
    sActiveHero_5C1B68->field_106_animation_num = pSaveState->field_34_animation_num;
    sActiveHero_5C1B68->field_108 = pSaveState->word36;
    sActiveHero_5C1B68->field_F8 = FP_FromInteger(pSaveState->word38);
    sActiveHero_5C1B68->field_110 = pSaveState->dword3C;
    sActiveHero_5C1B68->field_120_state = pSaveState->dword50;
    sActiveHero_5C1B68->field_124_gnFrame = pSaveState->dword54;
    sActiveHero_5C1B68->field_128.field_0_gnFrame = pSaveState->dword58;
    sActiveHero_5C1B68->field_128.field_4 = pSaveState->dword5C;
    sActiveHero_5C1B68->field_128.field_12_mood = pSaveState->word60;
    sActiveHero_5C1B68->field_128.field_18 = pSaveState->word62;
    sActiveHero_5C1B68->field_144 = pSaveState->dword64;
    sActiveHero_5C1B68->field_1A2_rock_or_bone_count = pSaveState->field_6c_rock_bone_count;
    sActiveHero_5C1B68->field_168 = pSaveState->dword68;
    sActiveHero_5C1B68->field_16C = pSaveState->byte6E;

    if (sActiveHero_5C1B68->field_168 && sActiveHero_5C1B68->field_16C)
    {
        if (!sActiveHero_5C1B68->field_10_resources_array.ItemAt(25))
        {
            if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbemorphResID, FALSE, FALSE))
            {
                ResourceManager::LoadResourceFile_49C170("SHRYPORT.BND", nullptr);
            }
            if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kSplineResID, FALSE, FALSE))
            {
                ResourceManager::LoadResourceFile_49C170("SPLINE.BAN", nullptr);
            }
            sActiveHero_5C1B68->Get_Shrykull_Resources_45AA20();
        }
    }
    else
    {
        if (sActiveHero_5C1B68->field_10_resources_array.ItemAt(25))
        {
            sActiveHero_5C1B68->Free_Shrykull_Resources_45AA90();
        }
    }

    sActiveHero_5C1B68->field_1AC_flags.Clear(Flags_1AC::e1AC_Bit5);
    if (pSaveState->byte6D & 1)
    {
        sActiveHero_5C1B68->field_1AC_flags.Set(Flags_1AC::e1AC_Bit5);
    }

    sActiveHero_5C1B68->field_16E = pSaveState->byte6F;
    sActiveHero_5C1B68->field_104 = pSaveState->field_3a_collision_line_id;

    sActiveHero_5C1B68->field_114_flags.Set(Flags_114::e114_Bit9);
    sActiveHero_5C1B68->field_118 = InputObject::Command_To_Raw_45EE40(pSaveState->word70);
    sActiveHero_5C1B68->field_11C = InputObject::Command_To_Raw_45EE40(pSaveState->word72);
    sActiveHero_5C1B68->field_122 = pSaveState->word74;
    sActiveHero_5C1B68->field_128.field_14 = sGnFrame_5C1B84 - pSaveState->dword78;
    sActiveHero_5C1B68->field_148 = pSaveState->dword7C;
    sActiveHero_5C1B68->field_14C = pSaveState->dword80;
    sActiveHero_5C1B68->field_150 = pSaveState->dword84;
    sActiveHero_5C1B68->field_154 = pSaveState->dword88;
    sActiveHero_5C1B68->field_158 = pSaveState->dword8C;
    sActiveHero_5C1B68->field_15C = pSaveState->dword90;
    sActiveHero_5C1B68->field_160 = pSaveState->dword94;
    sActiveHero_5C1B68->field_164 = pSaveState->dword98;
    sActiveHero_5C1B68->field_178_invisible_effect_id = -1;
    sActiveHero_5C1B68->field_170 = pSaveState->dword9C;
    sActiveHero_5C1B68->field_174 = pSaveState->wordA0;
    sActiveHero_5C1B68->field_176 = pSaveState->wordA2;
    sActiveHero_5C1B68->field_17C = pSaveState->byteA4;
    sActiveHero_5C1B68->field_180 = pSaveState->dwordA8;
    sActiveHero_5C1B68->field_184 = pSaveState->wordAC;
    sActiveHero_5C1B68->field_186 = pSaveState->wordAE;
    sActiveHero_5C1B68->field_188 = pSaveState->wordB0;
    sActiveHero_5C1B68->field_18A = pSaveState->wordB2;
    sActiveHero_5C1B68->field_18C = pSaveState->wordB4;
    sActiveHero_5C1B68->field_18E = pSaveState->wordB6;
    sActiveHero_5C1B68->field_190 = pSaveState->wordB8;
    sActiveHero_5C1B68->field_192 = pSaveState->wordBA;
    sActiveHero_5C1B68->field_194 = pSaveState->wordBC;
    sActiveHero_5C1B68->field_196 = pSaveState->wordBE;
    sActiveHero_5C1B68->field_198_has_evil_fart = pSaveState->wordC0;
    sActiveHero_5C1B68->field_19A = pSaveState->wordC2;
    sActiveHero_5C1B68->field_19C = pSaveState->wordC4;
    sActiveHero_5C1B68->field_19E = pSaveState->wordC6;
    sActiveHero_5C1B68->field_1A0_door_id = pSaveState->wordC8;
    sActiveHero_5C1B68->field_1A3_throw_direction = pSaveState->field_ca_throw_direction;
    sActiveHero_5C1B68->field_1A4 = pSaveState->wordCC;
    sActiveHero_5C1B68->field_1A8 = pSaveState->dwordD0;
    
    /* TODO: .. only the last one is going to "win" here.. !?
    sActiveHero_5C1B68->field_1AC_flags ^= ((unsigned __int8)sActiveHero_5C1B68->field_1AC_flags ^ LOBYTE(pSaveState->wordD4)) & 1;
    sActiveHero_5C1B68->field_1AC_flags ^= ((unsigned __int8)sActiveHero_5C1B68->field_1AC_flags ^ LOBYTE(pSaveState->wordD4)) & 2;
    sActiveHero_5C1B68->field_1AC_flags ^= ((unsigned __int8)sActiveHero_5C1B68->field_1AC_flags ^ LOBYTE(pSaveState->wordD4)) & 4;
    sActiveHero_5C1B68->field_1AC_flags ^= ((unsigned __int8)sActiveHero_5C1B68->field_1AC_flags ^ LOBYTE(pSaveState->wordD4)) & 8;
    */

    sActiveHero_5C1B68->field_1AC_flags.Clear(Flags_1AC::e1AC_Bit5);
    if (pSaveState->wordD4 & 0x10)
    {
        sActiveHero_5C1B68->field_1AC_flags.Set(Flags_1AC::e1AC_Bit5);
    }

    sActiveHero_5C1B68->field_1AC_flags.Clear(Flags_1AC::e1AC_Bit6);
    if (pSaveState->wordD4 & 0x20)
    {
        sActiveHero_5C1B68->field_1AC_flags.Set(Flags_1AC::e1AC_Bit6);
    }

    sActiveHero_5C1B68->field_1AC_flags.Clear(Flags_1AC::e1AC_Bit7);
    if (pSaveState->wordD4 & 0x40)
    {
        sActiveHero_5C1B68->field_1AC_flags.Set(Flags_1AC::e1AC_Bit7);
    }

    sActiveHero_5C1B68->field_1AC_flags.Clear(Flags_1AC::e1AC_Bit9);
    if (pSaveState->wordD4 & 0x80)
    {
        sActiveHero_5C1B68->field_1AC_flags.Set(Flags_1AC::e1AC_Bit9);
    }

    sActiveHero_5C1B68->field_1AC_flags.Clear(Flags_1AC::e1AC_Bit12);
    if (pSaveState->wordD4 & 0x100)
    {
        sActiveHero_5C1B68->field_1AC_flags.Set(Flags_1AC::e1AC_Bit12);
    }

    sActiveHero_5C1B68->field_1AC_flags.Clear(Flags_1AC::e1AC_eBit13);
    if (pSaveState->wordD4 & 0x200)
    {
        sActiveHero_5C1B68->field_1AC_flags.Set(Flags_1AC::e1AC_eBit13);
    }

    sActiveHero_5C1B68->field_1AC_flags.Clear(Flags_1AC::e1AC_eBit14);
    if (pSaveState->wordD4 & 0x400)
    {
        sActiveHero_5C1B68->field_1AC_flags.Set(Flags_1AC::e1AC_eBit14);
    }

    sActiveHero_5C1B68->field_1AC_flags.Clear(Flags_1AC::e1AC_eBit15);
    if (pSaveState->wordD4 & 0x800)
    {
        sActiveHero_5C1B68->field_1AC_flags.Set(Flags_1AC::e1AC_eBit15);
    }

    sActiveHero_5C1B68->field_1AC_flags.Clear(Flags_1AC::e1AC_eBit16);
    if (pSaveState->wordD4 & 0xE000)
    {
        sActiveHero_5C1B68->field_1AC_flags.Set(Flags_1AC::e1AC_eBit16);
    }

    sActiveHero_5C1B68->field_114_flags.Clear(Flags_114::e114_Bit10);
    if ((pSaveState->wordD4 >> 3) & 0x200)
    {
        sActiveHero_5C1B68->field_114_flags.Set(Flags_114::e114_Bit10);
    }

    sActiveHero_5C1B68->field_1AE &= ~1;
    if ((pSaveState->wordD4 >> 14) & 1)
    {
        sActiveHero_5C1B68->field_1AE |= 1;
    }

    // TODO: Move to shadow object
    sActiveHero_5C1B68->field_E0_176_ptr->field_14_flags &= ~2;
    if ((pSaveState->wordD4 >> 14) & 2)
    {
        sActiveHero_5C1B68->field_E0_176_ptr->field_14_flags |= 2;
    }

    /* TODO: Will wipe out previously set bits ??
    LOWORD(sActiveHero_5C1B68->field_E0_176_ptr->field_14_flags) ^= ((unsigned __int8)LOWORD(sActiveHero_5C1B68->field_E0_176_ptr->field_14_flags) ^ LOBYTE(pSaveState->wordD6)) & 1;
    sActiveHero_5C1B68->field_E0_176_ptr->field_14_flags &= ~1;
    if ((pSaveState->wordD6) & 1)
    {
        sActiveHero_5C1B68->field_E0_176_ptr->field_14_flags |= 1;
    }
    */

    if (sActiveHero_5C1B68->field_198_has_evil_fart)
    {
        if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 6017, FALSE, FALSE))
        {
            ResourceManager::LoadResourceFile_49C170("EVILFART.BAN", nullptr);
        }

        if (!sActiveHero_5C1B68->field_10_resources_array.ItemAt(22))
        {
            sActiveHero_5C1B68->field_10_resources_array.SetAt(22, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, 6017, TRUE, FALSE)); // TODO: ResId
        }

        if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kExplo2ResID, 0, 0))
        {
            ResourceManager::LoadResourceFile_49C170("EXPLO2.BAN", nullptr);
        }

        if (!sActiveHero_5C1B68->field_10_resources_array.ItemAt(24))
        {
            sActiveHero_5C1B68->field_10_resources_array.SetAt(24, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kExplo2ResID, TRUE, FALSE));
        }

        if (!ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeblowResID, 0, 0))
        {
            ResourceManager::LoadResourceFile_49C170("ABEBLOW.BAN", nullptr);
        }

        if (!sActiveHero_5C1B68->field_10_resources_array.ItemAt(23))
        {
            sActiveHero_5C1B68->field_10_resources_array.SetAt(23, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbeblowResID, TRUE, FALSE));
        }
    }

    return sizeof(Quicksave_Obj_Abe);
}

void Abe::VDestructor(signed int flags)
{
    vdtor_44B350(flags);
}

void Abe::VUpdate()
{
    Update_449DC0();
}

void Abe::VRender(int** pOrderingTable)
{
    vRender_44B580(pOrderingTable);
}

void Abe::VScreenChanged()
{
    vScreenChanged_44D240();
}

int Abe::GetSaveState_4DC110(BYTE* pSaveBuffer)
{
    return vGetSaveState_457110(pSaveBuffer);
}

__int16 Abe::Vsub_408730(int arg0)
{
    return vsub_Kill_44BB50(reinterpret_cast<BaseAliveGameObject*>(arg0));
}

__int16 Abe::VOn_TLV_Collision_4087F0(Path_TLV* pTlv)
{
    return vOn_TLV_Collision_44B5D0(pTlv);
}

int Abe::Vsub_408FD0(__int16 a2)
{
    return vsub_44E970(a2);
}

int Abe::Vnull_4081F0()
{
    return reinterpret_cast<int>(vsub_45A570());
}

void Abe::vdtor_44B350(signed int flags)
{
    dtor_44B380();
    if (flags & 1)
    {
        Mem_Free_495540(this);
    }
}

const FP sAbe_xVel_table_545770[8] = 
{
    FP_FromInteger(4),
    FP_FromInteger(4),
    FP_FromInteger(0),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(0),
    FP_FromInteger(4)
};

const FP sAbe_yVel_table_545790[8] =
{
    FP_FromInteger(0),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(-4),
    FP_FromInteger(0),
    FP_FromInteger(4),
    FP_FromInteger(4),
    FP_FromInteger(4)
};

const InputCommands sInputKey_Run_5550E8 = eRun;

ALIVE_VAR(1, 0x5c1bda, short, word_5C1BDA, 0);

EXPORT signed int CC PSX_StoreImage_4F5E90(const PSX_RECT* /*rect*/, WORD* /*pData*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT void CC Pal_Copy_483560(const PSX_Point* pPoint, __int16 w, WORD* pPalData, PSX_RECT* rect)
{
    rect->x = pPoint->field_0_x;
    rect->y = pPoint->field_2_y;
    rect->w = w;
    rect->h = 1;
    PSX_StoreImage_4F5E90(rect, pPalData);
}

class Class_545A60 : public BaseGameObject
{
public:
    EXPORT Class_545A60* ctor_45F280(Abe* pAbe)
    {
        BaseGameObject_ctor_4DBFA0(TRUE, 0);
        SetVTable(this, 0x545A60);

        field_4_typeId = BaseGameObject::Types::eType_75;

        field_44_objId = pAbe->field_8_object_id;

        field_24_pAlloc = reinterpret_cast<WORD*>(malloc_non_zero_4954F0(pAbe->field_20_animation.field_90_pal_depth * sizeof(WORD)));
        Pal_Copy_483560(
            &pAbe->field_20_animation.field_8C_pal_vram_x,
            pAbe->field_20_animation.field_90_pal_depth,
            field_24_pAlloc,
            &field_28);

        field_30_pPalAlloc = reinterpret_cast<WORD*>(malloc_non_zero_4954F0(pAbe->field_20_animation.field_90_pal_depth * sizeof(WORD)));
        Pal_Copy_483560(
            &pAbe->field_20_animation.field_8C_pal_vram_x,
            pAbe->field_20_animation.field_90_pal_depth,
            field_30_pPalAlloc,
            &field_34);

        field_4A_flags = 0;

        if (pAbe->field_20_animation.field_4_flags.Get(AnimFlags::eBit15_bSemiTrans))
        {
            field_4A_flags |= 0x1;
        }
        if (pAbe->field_20_animation.field_4_flags.Get(AnimFlags::eBit16_bBlending))
        {
            field_4A_flags |= 0x2;
        }

        field_4A_flags &= ~4u;
        field_48 = pAbe->field_20_animation.field_B_render_mode;
        field_20_state_or_op = 0;

        return this;
    }

    EXPORT void dtor_45F410()
    {
        SetVTable(this, 0x545A60);

        if (field_24_pAlloc)
        {
            Mem_Free_495560(field_24_pAlloc);
        }

        if (field_30_pPalAlloc)
        {
            Mem_Free_495560(field_30_pPalAlloc);
        }

        BaseGameObject_dtor_4DBEC0();
    }

    EXPORT void sub_45FA00()
    {
        field_4A_flags |= 4u;
        field_1C_update_delay = 1;
        field_20_state_or_op = 1;
    }

    EXPORT void sub_45FA30()
    {
        field_20_state_or_op = 4;
    }

    EXPORT void sub_45FA50()
    {
        field_1C_update_delay = 1;
        field_20_state_or_op = 5;
    }

    EXPORT void sub_45F9E0()
    {
        field_1C_update_delay = 1;
        field_20_state_or_op = 1;
    }

    EXPORT void vUpdate_45F4A0()
    {
        NOT_IMPLEMENTED();
    }

    EXPORT void vdtor_45F3E0(signed int flags)
    {
        dtor_45F410();
        if (flags & 1)
        {
            Mem_Free_495540(this);
        }
    }

    virtual void VDestructor(signed int flags) override
    {
        vdtor_45F3E0(flags);
    }

    virtual void VUpdate() override
    {
        vUpdate_45F4A0();
    }

    virtual void VScreenChanged() override
    {
        // Null @ 45F9C0
    }

private:
    unsigned __int16 field_20_state_or_op;
    __int16 field_22;
    WORD* field_24_pAlloc;
    PSX_RECT field_28;
    WORD* field_30_pPalAlloc;
    PSX_RECT field_34;
    int field_3C;
    int field_40;
    int field_44_objId;
    char field_48;
    char field_49;
    __int16 field_4A_flags;
};
ALIVE_ASSERT_SIZEOF(Class_545A60, 0x4C);

class MusicTrigger : public BaseGameObject
{
public:
    EXPORT void ctor_47FF10(__int16 type, __int16 a3, int /*a4*/, __int16 delay)
    {
        BaseGameObject_ctor_4DBFA0(TRUE, 0);
        SetVTable(this, 0x5463DC);
        Init_47FFB0(type, a3, delay);
        field_2C = 0;
        field_30 = 0;
        field_2E = 0;
        field_32 = 0;
        field_20 = -1;
    }

    EXPORT void Init_47FFB0(__int16 type, __int16 a3, __int16 delay)
    {
        field_24_flags &= ~7u;
        field_4_typeId = BaseGameObject::Types::eMusicTrigger;
        field_28_counter = 0;

        switch (type)
        {
        case 0:
            field_26 = 3;
            field_28_counter = 400;
            break;
        case 1:
            field_26 = 10;
            field_28_counter = 30;
            break;
        case 2:
            field_26 = 13;
            field_28_counter = 30;
            break;
        case 3:
            field_26 = 8;
            field_24_flags |= 4;
            break;
        case 4:
            field_26 = 7;
            field_24_flags |= 4;
            break;
        case 5:
            field_26 = 2;
            field_28_counter = delay;
            break;
        case 6:
            field_26 = 12;
            field_28_counter = 30;
            break;
        default:
            break;
        }

        if (a3)
        {
            if (a3 == 1)
            {
                field_24_flags |= 1u;
            }
        }
        else
        {
            field_1C_update_delay = delay;
        }
    }

    EXPORT void vdtor_47FEE0(signed int flags)
    {
        dtor_4800C0();
        if (flags & 1)
        {
            Mem_Free_495540(this);
        }
    }

    EXPORT void dtor_4800C0()
    {
        SetVTable(this, 0x5463DC);
        if (field_24_flags & 4)
        {
            MusicController::sub_47FD60(0, this, 0, 0);
        }
        BaseGameObject_dtor_4DBEC0();
    }

    EXPORT void vScreenChange_4802A0()
    {
        if (gMap_5C3030.sCurrentLevelId_5C3030 != gMap_5C3030.field_A_5C303A_levelId)
        {
            field_6_flags.Set(BaseGameObject::eDead);
        }
    }

    EXPORT void vUpdate_480140()
    {
        if (Event_Get_422C00(kEventHeroDying))
        {
            field_6_flags.Set(BaseGameObject::eDead);
        }

        if (field_24_flags & 1)
        {
            FP xpos = sControlledCharacter_5C1B8C->field_B8_xpos;
            FP ypos = sControlledCharacter_5C1B8C->field_BC_ypos;

            if (xpos >= FP_FromInteger(field_2C) && xpos <= FP_FromInteger(field_30) &&
               (ypos >= FP_FromInteger(field_2E) && ypos <= FP_FromInteger(field_32)))
            {
                field_24_flags &= ~1;
                MusicController::sub_47FD60(field_26, this, (field_24_flags >> 2) & 1,  1);
                field_24_flags |= 2u;
                if (field_28_counter >= 0)
                {
                    field_28_counter += sGnFrame_5C1B84;
                }
            }            
        }
        else if (field_24_flags & 2)
        {
            if (field_28_counter < 0 || static_cast<int>(sGnFrame_5C1B84) < field_28_counter)
            {
                MusicController::sub_47FD60(field_26, this, (field_24_flags >> 2) & 1, 0);
            }
            else
            {
                field_6_flags.Set(BaseGameObject::eDead);
            }
        }
        else
        {
            MusicController::sub_47FD60(field_26, this, (field_24_flags >> 2) & 1, 1);
            field_24_flags |= 2u;
            field_28_counter += sGnFrame_5C1B84;
        }
    }

    virtual void VDestructor(signed int flags) override
    {
        vdtor_47FEE0(flags);
    }

    virtual void VUpdate() override
    {
        vUpdate_480140();
    }

    virtual void VScreenChanged() override
    {
        vScreenChange_4802A0();
    }

private:
    int field_20;
    __int16 field_24_flags;
    __int16 field_26;
    int field_28_counter;
    __int16 field_2C;
    __int16 field_2E;
    __int16 field_30;
    __int16 field_32;
};
ALIVE_ASSERT_SIZEOF(MusicTrigger, 0x34);

class AbilityRing
{
public:
    EXPORT static BaseGameObject * CC Factory_482F80(int /*xpos*/, int /*ypos*/, int /*type*/, FP /*scale*/)
    {
        NOT_IMPLEMENTED();
        return nullptr;
    }
};

void Abe::Update_449DC0()
{
    NOT_IMPLEMENTED();

    if (word_5C1BDA) // Some flag to reset HP?
    {
        field_114_flags.Clear(Flags_114::e114_Bit7);
        field_10C_health = FP_FromDouble(1.0);
    }

    if (field_114_flags.Get(Flags_114::e114_Bit9))
    {
        field_114_flags.Clear(Flags_114::e114_Bit9);
        if (field_104 != -1)
        {
            sCollisions_DArray_5C1128->Raycast_417A60(
                field_B8_xpos,
                field_BC_ypos - FP_FromInteger(20),
                field_B8_xpos,
                field_BC_ypos + FP_FromInteger(20),
                &field_100_pCollisionLine,
                &field_B8_xpos,
                &field_BC_ypos,
                1 << field_104);

            field_104 = -1;
        }

        field_110 = BaseGameObject::Find_Flags_4DC170(field_110);
        field_148 = BaseGameObject::Find_Flags_4DC170(field_148);
        field_14C = BaseGameObject::Find_Flags_4DC170(field_14C);
        field_1A8 = BaseGameObject::Find_Flags_4DC170(field_1A8);
        field_150 = BaseGameObject::Find_Flags_4DC170(field_150);
        field_154 = BaseGameObject::Find_Flags_4DC170(field_154);
        field_158 = BaseGameObject::Find_Flags_4DC170(field_158);
        field_15C = BaseGameObject::Find_Flags_4DC170(field_15C);
        field_160 = BaseGameObject::Find_Flags_4DC170(field_160);
        field_164 = BaseGameObject::Find_Flags_4DC170(field_164);

        if (!(field_114_flags.Get(Flags_114::e114_Bit8)))
        {
            if (!field_170)
            {
                field_170 = sGnFrame_5C1B84 + 2;
            }

            auto pClass = alive_new<Class_545A60>();
            pClass->ctor_45F280(this);
            field_178_invisible_effect_id = pClass->field_8_object_id;
            pClass->sub_45FA00();
        }
    }

    if (field_1AC_flags.Get(Flags_1AC::e1AC_Bit12))
    {
        return;
    }

    if (word_5C1BDA)
    {
        field_10C_health = FP_FromDouble(1.0);
    }

    if (!Input_IsChanting_45F260())
    {
        field_1AC_flags.Clear(Flags_1AC::e1AC_Bit6);
        field_174 = 1;
    }

    const int totalAliveSavedMuds = sRescuedMudokons_5C1BC2 - sKilledMudokons_5C1BC0;
    if (totalAliveSavedMuds == 0)
    {
        // "Normal" voice
        field_128.field_12_mood = 5;
    }
    else if (totalAliveSavedMuds >= 0)
    {
        // "Happy" voice
        field_128.field_12_mood = 0;
    }
    else if (totalAliveSavedMuds <= 0)
    {
        // "Sad" voice
        field_128.field_12_mood = 3;
    }

    if (!sDDCheat_FlyingEnabled_5C2C08 || sControlledCharacter_5C1B8C != this)
    {
        field_20_animation.field_4_flags.Set(AnimFlags::eBit2_Animate);
    
        short state_idx = field_106_animation_num;

        // Execute the current state
        const FP oldXPos = field_B8_xpos;
        const FP oldYPos = field_BC_ypos;
        (this->*(sAbeStateMachineTable_554910)[state_idx])();

        if (field_114_flags.Get(Flags_114::e114_Bit9) || field_1AC_flags.Get(Flags_1AC::e1AC_Bit6))
        {
            return;
        }

        if (field_100_pCollisionLine)
        {
            // Snap to a whole number so we are "on" the line
            field_BC_ypos = FP_NoFractional(field_BC_ypos);
        }

        // Did position change?
        if (oldXPos != field_B8_xpos || oldYPos != field_BC_ypos)
        {
            // Get the TLV we are on
            field_FC_pPathTLV = sPath_dword_BB47C0->TLV_Get_At_4DB290(
                nullptr,
                field_B8_xpos,
                field_BC_ypos,
                field_B8_xpos,
                field_BC_ypos);
            VOn_TLV_Collision_4087F0(field_FC_pPathTLV);
        }

        if (field_114_flags.Get(Flags_114::e114_Bit1))
        {
            state_idx = field_122;
            Knockback_44E700(1, 1);
            if (state_idx != -1)
            {
                field_106_animation_num = state_idx;
            }

            field_108 = 0;
            field_1AC_flags.Clear(Flags_1AC::e1AC_Bit2);
            field_122 = 0;
            field_114_flags.Clear(Flags_114::e114_Bit1);
            field_114_flags.Set(Flags_114::e114_Bit2);
        }

        if (Event_Get_422C00(kEventScreenShake) && field_10C_health > FP_FromInteger(0))
        {
            if (sub_449D30())
            {
                Knockback_44E700(1, 0);
            }
        }

        if (field_128.field_18 < 0 || static_cast<int>(sGnFrame_5C1B84) < field_144)
        {
LABEL_75:
            if (state_idx != field_106_animation_num || field_114_flags.Get(Flags_114::e114_Bit2))
            {
                field_114_flags.Clear(Flags_114::e114_Bit2);
                if (field_106_animation_num != eAbeStates::State_12_Null_4569C0 && !(field_1AC_flags.Get(Flags_1AC::e1AC_Bit5)))
                {
                    field_20_animation.Set_Animation_Data_409C80(
                        sAbeFrameOffsetTable_554B18[field_106_animation_num],
                        StateToAnimResource_44AAB0(field_106_animation_num));

                    field_128.field_14 = sGnFrame_5C1B84;

                    if (state_idx == eAbeStates::State_12_Null_4569C0 || state_idx == eAbeStates::State_60_4A3200)
                    {
                        field_20_animation.SetFrame_409D50(field_F6);
                    }
                }
            }

            if (field_1AC_flags.Get(Flags_1AC::e1AC_Bit2))
            {
                field_106_animation_num = field_F4;
                field_20_animation.Set_Animation_Data_409C80(
                    sAbeFrameOffsetTable_554B18[field_106_animation_num],
                    StateToAnimResource_44AAB0(field_106_animation_num));

                field_128.field_14 = sGnFrame_5C1B84;
                field_20_animation.SetFrame_409D50(field_F6);
                field_1AC_flags.Clear(Flags_1AC::e1AC_Bit2);
            }

            if (field_128.field_4 <= static_cast<int>(sGnFrame_5C1B84)  && field_10C_health > FP_FromInteger(0))
            {
                field_10C_health = FP_FromDouble(1.0);
            }

            if (field_168)
            {
                if (field_20_animation.field_4_flags.Get(AnimFlags::eBit3_Render))
                {
                    if (gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0))
                    {
                        if (static_cast<int>(sGnFrame_5C1B84) <= field_168)
                        {
                            if (!(sGnFrame_5C1B84 % 32))
                            {
                                int ringType = 0;
                                if (field_16C)
                                {
                                    ringType = 4;
                                }
                                else if (field_16E)
                                {
                                    ringType = 7;
                                }
                                else if (field_1AC_flags.Get(Flags_1AC::e1AC_eBit15))
                                {
                                    ringType = 14;
                                }

                                PSX_RECT rect = {};
                                GetBoundingRect_424FD0(&rect, 1);
                                AbilityRing::Factory_482F80((rect.x + rect.w)/ 2, (rect.y + rect.h) / 2, ringType, field_CC_sprite_scale);

                                SFX_Play_46FBA0(0x11u, 25, 2650, 0x10000);
                            }
                        }
                        else
                        {
                            if (field_168 > 0 && field_16C > 0)
                            {
                                Free_Shrykull_Resources_45AA90();
                            }
                            field_168 = 0;
                        }
                    }
                }
            }

            
            Class_545A60* pObj_field_178 = static_cast<Class_545A60*>(sObjectIds_5C1B70.Find_449CF0(field_178_invisible_effect_id));
            if (pObj_field_178 && field_170 > 0)
            {
                if (static_cast<int>(sGnFrame_5C1B84) > field_170)
                {
                    field_170 = 0;
                    pObj_field_178->sub_45FA30();
                }
            }

            if (field_1AC_flags.Get(Flags_1AC::e1AC_eBit16))
            {
                if (field_1AE & 1)
                {
                    if (gMap_5C3030.sCurrentLevelId_5C3030 == 2)
                    {
                        field_168 = sGnFrame_5C1B84 + 200000;
                        field_16C = 0;
                        field_16E = 0;
                        field_1AE &= ~1;
                        field_1AC_flags.Clear(Flags_1AC::e1AC_eBit16);
                        field_1AC_flags.Set(Flags_1AC::e1AC_eBit15);
                    }
                }
            }

            if (Event_Get_422C00(kEventMudokonDied))
            {
                field_128.field_18 = 14;
                field_144 = sGnFrame_5C1B84 + Math_RandomRange_496AB0(22, 30);

                // Do the death jingle
                alive_new<MusicTrigger>()->ctor_47FF10(1, 0, 90, 0);
            }

            if (Event_Get_422C00(kEventMudokonComfort))
            {
                field_128.field_18 = 8;
                field_144 = sGnFrame_5C1B84 + Math_RandomRange_496AB0(22, 30);
            }

            if (Event_Get_422C00(kEventMudokonComfort | kEventSpeaking))
            {
                field_128.field_18 = 14;
                field_144 = sGnFrame_5C1B84 + Math_RandomRange_496AB0(22, 30);
            }

            if (!(field_1AE & 2))
            {
                return;
            }

          
            field_1AE &= ~2;
            sActiveQuicksaveData_BAF7F8.field_204_world_info.field_A_unknown_1 = static_cast<short>(field_1B0_save_num);
            Quicksave_SaveWorldInfo_4C9310(&sActiveQuicksaveData_BAF7F8.field_244_restart_path_world_info);
            vGetSaveState_457110(reinterpret_cast<BYTE*>(&sActiveQuicksaveData_BAF7F8.field_284_restart_path_abe_state));
            sActiveQuicksaveData_BAF7F8.field_35C_restart_path_switch_states = sSwitchStates_5C1A28;
            Quicksave_4C90D0();
            return;
        }

        if (!gMap_5C3030.Is_Point_In_Current_Camera_4810D0(field_C2_lvl_number, field_C0_path_number, field_B8_xpos, field_BC_ypos, 0)
            || (field_106_animation_num == eAbeStates::State_112_Chant_45B1C0)
            || field_106_animation_num == eAbeStates::State_7_45B140
            || field_106_animation_num == eAbeStates::State_8_45B160
            || field_106_animation_num == eAbeStates::State_9_45B180
            || field_106_animation_num == eAbeStates::State_10_Fart_45B1A0)
        {
LABEL_74:
            field_128.field_18 = -1;
            goto LABEL_75;
        }

        if (field_106_animation_num == eAbeStates::State_0_Idle_44EEB0 || field_106_animation_num == eAbeStates::State_12_Null_4569C0)
        {
            field_114_flags.Set(Flags_114::e114_Bit2);
            switch (field_128.field_18)
            {
            case 14:
                field_106_animation_num = eAbeStates::State_34_DunnoBegin_44ECF0;
                break;
            case 5:
                field_106_animation_num = eAbeStates::State_10_Fart_45B1A0;
                break;
            case 28:
                field_106_animation_num = eAbeStates::State_10_Fart_45B1A0;
                break;
            default:
                field_106_animation_num = eAbeStates::State_9_45B180;
                break;
            }
        }

        if (field_128.field_18 == 5)
        {
            Event_Broadcast_422BC0(kEventMudokonLaugh, sActiveHero_5C1B68);
        }

        if (field_128.field_18 == 28)
        {
            Abe_SFX_457EC0(static_cast<unsigned char>(field_128.field_18), 80, 0, this);
        }
        else
        {
            Abe_SFX_457EC0(static_cast<unsigned char>(field_128.field_18), 0, 0, this);
        }

        goto LABEL_74;
    }

    /*
    // vcall 23
    ((void(__thiscall *)(Abe *))this->field_0_VTbl->VAbe.field_0.field_5C)(this);
    */
    Vnull_4081F0();

    field_F8 = field_BC_ypos;
    field_1AC_flags.Clear(Flags_1AC::e1AC_Bit5);
    field_106_animation_num = eAbeStates::jState_85_Fall_455070;
    field_100_pCollisionLine = nullptr;

    if (sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_0_pressed & (eRight | eLeft | eDown | eUp))
    {
        field_C4_velx = sAbe_xVel_table_545770[(unsigned __int8)sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
        field_C8_vely = sAbe_yVel_table_545790[(unsigned __int8)sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
        
        if (sInputKey_Run_5550E8 & sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_0_pressed)
        {
            field_C4_velx += sAbe_xVel_table_545770[(unsigned __int8)sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
            field_C4_velx += sAbe_xVel_table_545770[(unsigned __int8)sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
            field_C8_vely += sAbe_yVel_table_545790[(unsigned __int8)sInputObject_5BD4E0.field_0_pads[sCurrentControllerIndex_5C1BBE].field_4_dir >> 5];
        }

        field_B8_xpos += field_C4_velx;
        field_BC_ypos += field_C8_vely;

        // Keep within map max min bounds
        if (field_B8_xpos < FP_FromInteger(0))
        {
            field_B8_xpos = FP_FromInteger(0);
        }

        if (field_BC_ypos < FP_FromInteger(0))
        {
            field_BC_ypos = FP_FromInteger(0);
        }

        // Keep within map max bounds
        PSX_Point mapSize = {};
        gMap_5C3030.Get_map_size_480640(&mapSize);

        FP mapWidth = FP_FromInteger(mapSize.field_0_x);
        if (field_B8_xpos >= mapWidth)
        {
            field_B8_xpos = mapWidth - FP_FromDouble(1.0);
        }

        FP mapHeight = FP_FromInteger(mapSize.field_2_y);
        if (field_BC_ypos >= mapHeight)
        {
            field_BC_ypos = mapHeight - FP_FromDouble(1.0);
            sub_408C40();
            return;
        }
    }
    else
    {
        field_C4_velx = FP_FromInteger(0);
        field_C8_vely = FP_FromInteger(0);
    }
    
    sub_408C40();
}

int Abe::vsub_44E970(__int16 /*a2*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

BaseGameObject* Abe::vsub_45A570()
{
    NOT_IMPLEMENTED();
    return nullptr;
}

void Abe::Knockback_44E700(__int16 /*a2*/, __int16 /*a3*/)
{
    NOT_IMPLEMENTED();
}

void Abe::vRender_44B580(int** pOrderingTable)
{
    if (!(field_1AC_flags.Get(Flags_1AC::e1AC_Bit5)))
    {
        field_20_animation.field_14_scale = field_CC_sprite_scale;
    }

    if (field_106_animation_num != eAbeStates::State_79_WellInside_45CA60 && field_106_animation_num != eAbeStates::State_82_45CC80 && field_106_animation_num != eAbeStates::State_76_45CA40)
    {
        Render_424B90(pOrderingTable);
    }
}

void Abe::vScreenChanged_44D240()
{
    if (sControlledCharacter_5C1B8C == this)
    {
        field_C2_lvl_number = gMap_5C3030.field_A_5C303A_levelId;
        field_C0_path_number = gMap_5C3030.field_C_5C303C_pathId;
    }

    // Level has changed?
    if (gMap_5C3030.sCurrentLevelId_5C3030 != gMap_5C3030.field_A_5C303A_levelId)
    {
        if (gMap_5C3030.field_A_5C303A_levelId == 1 && !word_5C1BA0)
        {
            field_128.field_18 = 3;
            field_144 = sGnFrame_5C1B84 + 35;
        }

        // Set the correct tint for this map
        SetTint_425600(sTintTable_Abe_554D20, gMap_5C3030.field_A_5C303A_levelId);

        if (gMap_5C3030.sCurrentLevelId_5C3030)
        {
            if (field_1A2_rock_or_bone_count > 0)
            {
                if (gpThrowableArray_5D1E2C)
                {
                    gpThrowableArray_5D1E2C->Remove_49AA00(field_1A2_rock_or_bone_count);
                }
            }
            
            field_1A2_rock_or_bone_count = 0;
            
            if (field_168 > 0 && field_16C)
            {
                Free_Shrykull_Resources_45AA90();
            }

            field_168 = 0;
        }

        if (gMap_5C3030.field_A_5C303A_levelId == 2)
        {
            if (gMap_5C3030.sCurrentLevelId_5C3030 == 7)
            {
                field_1AC_flags.Set(Flags_1AC::e1AC_eBit16);
            }

            if (gMap_5C3030.sCurrentLevelId_5C3030 == 11)
            {
                field_1AE |= 1u;
            }
        }

        if (gMap_5C3030.field_A_5C303A_levelId == 16 || gMap_5C3030.field_A_5C303A_levelId == 0)
        {
            // Remove Abe for menu/credits levels?
            field_6_flags.Set(BaseGameObject::eDead);
        }
    }

    if (gMap_5C3030.sCurrentLevelId_5C3030 != gMap_5C3030.field_A_5C303A_levelId || gMap_5C3030.sCurrentPathId_5C3032 != gMap_5C3030.field_C_5C303C_pathId)
    {
        field_168 = 0;
        if (gMap_5C3030.sCurrentLevelId_5C3030)
        {
            field_198_has_evil_fart = 0;
        }
    }

    if (gMap_5C3030.sCurrentLevelId_5C3030 != gMap_5C3030.field_A_5C303A_levelId && !(field_114_flags.Get(Flags_114::e114_Bit9)))
    {
        for (BYTE& val : sSavedKilledMudsPerPath_5C1B50.mData)
        {
            val = 0;
        }
        byte_5C1B64 = 0;
    }
}

int Abe::vGetSaveState_457110(BYTE* /*pSaveBuffer*/)
{
    NOT_IMPLEMENTED();
    return 216;
}

bool Abe::vsub_Kill_44BB50(BaseGameObject * /*otherObj*/)
{
    NOT_IMPLEMENTED();
    return false;
}

__int16 Abe::vOn_TLV_Collision_44B5D0(Path_TLV* /*a2a*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

int Abe::sub_44B7B0()
{
#ifdef STUPID_FUN
    // THIS IS A HACK TO MAKE ABE POSSESS ANYTHING :D
    for (int baseObjIdx = 0; baseObjIdx < gBaseGameObject_list_BB47C4->Size(); baseObjIdx++)
    {
        BaseAliveGameObject* pBaseGameObject = reinterpret_cast<BaseAliveGameObject*>(gBaseGameObject_list_BB47C4->ItemAt(baseObjIdx));
        if (!pBaseGameObject)
        {
            break;
        }

        if (pBaseGameObject->field_4_typeId == 83)
        {
            pBaseGameObject->field_6_flags |= 4;
        }

        PSX_Point currentScreenCoords;
        gMap_5C3030.GetCurrentCamCoords_480680(&currentScreenCoords);
        if (pBaseGameObject != sActiveHero_5C1B68 && pBaseGameObject->field_6_flags & BaseGameObject::eIsBaseAliveGameObject &&
            pBaseGameObject->field_B8_xpos.GetExponent() > currentScreenCoords.field_0_x && pBaseGameObject->field_B8_xpos.GetExponent() < currentScreenCoords.field_0_x + 350
            && pBaseGameObject->field_BC_ypos.GetExponent() > currentScreenCoords.field_2_y && pBaseGameObject->field_BC_ypos.GetExponent() < currentScreenCoords.field_2_y + 240)
        {
            return (int)pBaseGameObject;
        }
    }
    return 0;
#else
    NOT_IMPLEMENTED();
#endif
}

void Abe::Load_Basic_Resources_44D460()
{
    NOT_IMPLEMENTED();
}

void Abe::Free_Resources_44D420()
{
    NOT_IMPLEMENTED();
}

EXPORT BOOL Abe::sub_449D30()
{
    NOT_IMPLEMENTED();
    return 0;
}

void Abe::Free_Shrykull_Resources_45AA90()
{
    ResourceManager::FreeResource_49C330(field_10_resources_array.ItemAt(25));
    field_10_resources_array.SetAt(25, nullptr);

    ResourceManager::FreeResource_49C330(field_10_resources_array.ItemAt(26));
    field_10_resources_array.SetAt(26, nullptr);

    ResourceManager::FreeResource_49C330(field_10_resources_array.ItemAt(27));
    field_10_resources_array.SetAt(27, nullptr);
}


BYTE ** Abe::StateToAnimResource_44AAB0(signed int /*state*/)
{
    NOT_IMPLEMENTED();
    return nullptr;
}


void Abe::State_0_Idle_44EEB0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_1_WalkLoop_44FBA0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_2_StandingTurn_451830()
{
    NOT_IMPLEMENTED();
}

void Abe::State_3_Fall_459B60()
{
    NOT_IMPLEMENTED();
}

void Abe::State_4_WalkEndLeftFoot_44FFC0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_5_WalkEndRightFoot_00450080()
{
    NOT_IMPLEMENTED();
}

void Abe::State_6_WalkBegin_44FEE0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_7_45B140()
{
    NOT_IMPLEMENTED();
}

void Abe::State_8_45B160()
{
    NOT_IMPLEMENTED();
}

void Abe::State_9_45B180()
{
    NOT_IMPLEMENTED();
}

void Abe::State_10_Fart_45B1A0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_11_Speak_45B0A0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_12_Null_4569C0()
{

}

void Abe::State_13_HoistBegin_452B20()
{
    NOT_IMPLEMENTED();
}

void Abe::State_14_HoistIdle_452440()
{
    NOT_IMPLEMENTED();
}

void Abe::State_15_HoistLand_452BA0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_16_LandSoft_45A360()
{
    NOT_IMPLEMENTED();
}

void Abe::State_17_CrouchIdle_456BC0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_18_CrouchToStand_454600()
{
    NOT_IMPLEMENTED();
}

void Abe::State_19_StandToCrouch_453DC0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        sub_454090(field_B8_xpos, (field_BC_ypos - FP_FromInteger(5)) / FP_FromDouble(1.0), 1);
        field_106_animation_num = eAbeStates::State_17_CrouchIdle_456BC0;
    }
}

void Abe::State_20_454550()
{
    NOT_IMPLEMENTED();
}

void Abe::jState_21_4545E0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_22_RollBegin_4539A0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_23_RollLoop_453A90()
{
    NOT_IMPLEMENTED();
}

void Abe::State_24_453D00()
{
    NOT_IMPLEMENTED();
}

void Abe::State_25_RunSlideStop_451330()
{
    NOT_IMPLEMENTED();
}

void Abe::State_26_RunTurn_451500()
{
    NOT_IMPLEMENTED();
}

void Abe::State_27_HopBegin_4521C0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_28_HopMid_451C50()
{
    NOT_IMPLEMENTED();
}

void Abe::State_29_HopLand_4523D0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_30_RunJumpBegin_4532E0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_31_RunJumpMid_452C10()
{
    NOT_IMPLEMENTED();
}

void Abe::State_32_RunJumpLand_453460()
{
    NOT_IMPLEMENTED();
}

void Abe::State_33_RunLoop_4508E0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_34_DunnoBegin_44ECF0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_106_animation_num = eAbeStates::State_35_DunnoEnd_44ED10;
    }
}

void Abe::State_35_DunnoEnd_44ED10()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_44E6B0();
    }
}

void Abe::State_36_Null_45BC50()
{

}

void Abe::State_37_CrouchTurn_454390()
{
    NOT_IMPLEMENTED();
}

void Abe::jState_38_RollBegin_453A70()
{
    NOT_IMPLEMENTED();
}

void Abe::State_39_StandingToRun_450D40()
{
    NOT_IMPLEMENTED();
}

void Abe::State_40_SneakLoop_450550()
{
    NOT_IMPLEMENTED();
}

void Abe::State_41_450250()
{
    NOT_IMPLEMENTED();
}

void Abe::State_42_4503D0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_43_450380()
{
    NOT_IMPLEMENTED();
}

void Abe::State_44_450500()
{
    NOT_IMPLEMENTED();
}

void Abe::State_45_SneakBegin_4507A0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_46_SneakEnd_450870()
{
    NOT_IMPLEMENTED();
}

void Abe::jState_47_SneakEnd_4508C0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_48_4500A0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_49_450200()
{
    NOT_IMPLEMENTED();
}

void Abe::State_50_RunToWalk1_450E20()
{
    NOT_IMPLEMENTED();
}

void Abe::State_51_RunToWalk2_450F50()
{
    NOT_IMPLEMENTED();
}

void Abe::State_52_451710()
{
    NOT_IMPLEMENTED();
}

void Abe::State_53_451800()
{
    NOT_IMPLEMENTED();
}

void Abe::State_54_RunJumpLandRun_4538F0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_55_RunJumpLandWalk_453970()
{
    NOT_IMPLEMENTED();
}

void Abe::State_56_4591F0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_57_Dead_4589A0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_58_DeadPre_4593E0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_59_Null_459450()
{

}

void Abe::State_60_4A3200()
{
    NOT_IMPLEMENTED();
}

void Abe::State_61_TurnToRun_456530()
{
    NOT_IMPLEMENTED();
}

void Abe::State_62_Punch_454750()
{
    NOT_IMPLEMENTED();
}

void Abe::State_63_Sorry_454670()
{
    NOT_IMPLEMENTED();
}

void Abe::State_64_454730()
{
    NOT_IMPLEMENTED();
}

void Abe::State_65_LedgeAscend_4548E0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_66_LedgeDescend_454970()
{
    NOT_IMPLEMENTED();
}

void Abe::State_67_LedgeHang_454E20()
{
    NOT_IMPLEMENTED();
}

void Abe::State_68_454B80()
{
    NOT_IMPLEMENTED();
}

void Abe::State_69_LedgeHangWobble_454EF0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_70_RingRopePull_455AF0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_71_Knockback_455090()
{
    NOT_IMPLEMENTED();
}

void Abe::State_72_KnockbackGetUp_455340()
{
    NOT_IMPLEMENTED();
}

void Abe::State_73_PushWall_4553A0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_74_455290()
{
    NOT_IMPLEMENTED();
}

void Abe::State_75_45C7B0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_76_45CA40()
{
    NOT_IMPLEMENTED();
}

void Abe::State_77_45D130()
{
    NOT_IMPLEMENTED();
}

void Abe::State_78_WellBegin_45C810()
{
    NOT_IMPLEMENTED();
}

void Abe::State_79_WellInside_45CA60()
{
    NOT_IMPLEMENTED();
}

void Abe::State_80_WellShotOut_45D150()
{
    NOT_IMPLEMENTED();
}

void Abe::jState_81_WellBegin_45C7F0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_82_45CC80()
{
    NOT_IMPLEMENTED();
}

void Abe::State_83_45CF70()
{
    NOT_IMPLEMENTED();
}

void Abe::State_84_FallLandDie_45A420()
{
    NOT_IMPLEMENTED();
}

void Abe::jState_85_Fall_455070()
{
    NOT_IMPLEMENTED();
}

void Abe::State_86_HandstoneBegin_45BD00()
{
    NOT_IMPLEMENTED();
}

void Abe::State_87_HandstoneEnd_45C4F0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_88_GrenadeMachineUse_45C510()
{
    NOT_IMPLEMENTED();
}

void Abe::State_89_BrewMachineBegin_4584C0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_90_BrewMachineEnd_4585B0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_91_RingRopePullEnd_4557B0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_92_455800()
{
    NOT_IMPLEMENTED();
}

void Abe::State_93_FallLedgeBegin_455970()
{
    NOT_IMPLEMENTED();
}

void Abe::jState_94_FallLedgeBegin_4559A0()
{
    NOT_IMPLEMENTED();
}

void Abe::jState_95_FallLedgeBegin_4559C0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_96_4559E0()
{
    NOT_IMPLEMENTED();
}

void Abe::jState_97_FallLedgeBegin_455A80()
{
    NOT_IMPLEMENTED();
}

void Abe::jState_98_FallLedgeBegin_455AA0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_99_LeverUse_455AC0()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_114_flags.Get(Flags_114::e114_Bit10))
        {
            field_106_animation_num = eAbeStates::State_34_DunnoBegin_44ECF0;
        }
        else
        {
            ToIdle_44E6B0();
        }
    }
}

void Abe::State_100_455B60()
{
    NOT_IMPLEMENTED();
}

void Abe::State_101_KnockForward_455420()
{
    NOT_IMPLEMENTED();
}

void Abe::State_102_455310()
{
    NOT_IMPLEMENTED();
}

void Abe::jState_103_KnockbackGetUp_455380()
{
    NOT_IMPLEMENTED();
}

void Abe::State_104_RockThrowStandingHold_455DF0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_105_RockThrowStandingThrow_456460()
{
    NOT_IMPLEMENTED();
}

void Abe::State_106_RockThrowStandingEnd_455F20()
{
    NOT_IMPLEMENTED();
}

void Abe::State_107_RockThrowCrouchingHold_454410()
{
    NOT_IMPLEMENTED();
}

void Abe::State_108_RockThrowCrouchingThrow_454500()
{
    NOT_IMPLEMENTED();
}

void Abe::State_109_455550()
{
    NOT_IMPLEMENTED();
}

void Abe::State_110_455670()
{
    NOT_IMPLEMENTED();
}

void Abe::State_111_GrabRock_4564A0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_112_Chant_45B1C0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_113_ChantEnd_45BBE0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_114_DoorEnter_459470()
{
    NOT_IMPLEMENTED();
}

void Abe::State_115_DoorExit_459A40()
{
    NOT_IMPLEMENTED();
}

void Abe::State_116_MineCarEnter_458780()
{
    NOT_IMPLEMENTED();
}

void Abe::State_117_4587C0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_118_MineCarExit_458890()
{
    if (field_20_animation.field_4_flags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        field_114_flags.Set(Flags_114::e114_Bit2);
        field_106_animation_num = eAbeStates::State_0_Idle_44EEB0;
        field_124_gnFrame = 1;
    }
}

void Abe::State_119_45A990()
{
    NOT_IMPLEMENTED();
}

void Abe::State_120_45AB00()
{
    NOT_IMPLEMENTED();
}

void Abe::State_121_LiftGrabBegin_45A600()
{
    NOT_IMPLEMENTED();
}

void Abe::State_122_LiftGrabEnd_45A670()
{
    NOT_IMPLEMENTED();
}

void Abe::State_123_LiftGrabIdle_45A6A0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_124_LiftUseUp_45A780()
{
    NOT_IMPLEMENTED();
}

void Abe::State_125_LiftUseDown_45A7B0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_126_TurnWheelBegin_456700()
{
    NOT_IMPLEMENTED();
}

void Abe::State_127_TurnWheelLoop_456750()
{
    NOT_IMPLEMENTED();
}

void Abe::State_128_TurnWheelEnd_4569A0()
{
    NOT_IMPLEMENTED();
}

void Abe::State_129_PoisonGasDeath_4565C0()
{
    NOT_IMPLEMENTED();
}

void Abe::ToDie_4588D0()
{
    field_1AC_flags.Set(Flags_1AC::e1AC_Bit5);
    field_106_animation_num = eAbeStates::State_56_4591F0;
    field_124_gnFrame = 0;
    field_10C_health = FP_FromInteger(0);
    MusicController::sub_47FD60(0, this, 1, 0);
}

void Abe::ToIdle_44E6B0()
{
    field_128.field_8 = 0;
    field_C4_velx = FP_FromInteger(0);
    field_C8_vely = FP_FromInteger(0);
    field_124_gnFrame = sGnFrame_5C1B84;
    field_106_animation_num = eAbeStates::State_0_Idle_44EEB0;
    field_118 = 0;
    field_11C = 0;
    sub_408D10(TRUE);
}

__int16 Abe::sub_454090(FP /*fpX*/, FP /*fpY*/, int /*a4*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

void Abe::Get_Shrykull_Resources_45AA20()
{
    field_10_resources_array.SetAt(25, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kAbemorphResID, TRUE, FALSE));
    field_10_resources_array.SetAt(26, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kShrmorphResID, TRUE, FALSE));
    field_10_resources_array.SetAt(27, ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kSplineResID, TRUE, FALSE));
}

// TODO: Clean up
EXPORT void CC Abe_SFX_457EC0(unsigned __int8 idx, __int16 volume, int pitch, Abe* pHero)
{
    //DEV_CONSOLE_PRINTF("Abe SFX: %i", idx);

    switch (idx)
    {
    case 14u:
        if (pHero && pHero->field_CC_sprite_scale == FP_FromDouble(0.5))
        {
            SND_SEQ_Play_4CAB10(0x10u, 1, 90, 90);
        }
        else
        {
            SND_SEQ_Play_4CAB10(0x10u, 1, 127, 127);
        }
        break;
    case 26u:
        if (pHero && pHero->field_CC_sprite_scale == FP_FromDouble(0.5))
        {
            SND_SEQ_Play_4CAB10(0x12u, 1, 80, 80);
        }
        else
        {
            SND_SEQ_Play_4CAB10(0x12u, 1, 115, 115);
        }
        break;
    case 8u:
        if (pHero == sActiveHero_5C1B68 && gMap_5C3030.sCurrentLevelId_5C3030 == 10)
        {
            idx = 10;
        }
        // Fall through
    default:
        if (!volume)
        {
            volume = sAbeSFXList_555250[idx].field_3_default_volume;
        }

        // OG bug - isn't null checked in other cases before de-ref?
        if (!pHero)
        {
            SFX_SfxDefinition_Play_4CA420(&sAbeSFXList_555250[idx], volume, pitch, pitch);
            return;
        }

        if (pHero->field_CC_sprite_scale == FP_FromDouble(0.5))
        {
            volume = 2 * volume / 3;
        }

        if (pHero == sActiveHero_5C1B68)
        {
            SFX_SfxDefinition_Play_4CA420(&sAbeSFXList_555250[idx], volume, pitch, pitch);
            return;
        }

        switch (gMap_5C3030.sub_4811A0(
            pHero->field_C2_lvl_number,
            pHero->field_C0_path_number,
            pHero->field_B8_xpos,
            pHero->field_BC_ypos))
        {
        case 0:
            SFX_SfxDefinition_Play_4CA420(&sAbeSFXList_555250[idx], volume, pitch, pitch);
            break;
        case 1:
        case 2:
            SFX_SfxDefinition_Play_4CA420(&sAbeSFXList_555250[idx], 2 * volume / 3, pitch, pitch);
            break;
        case 3:
            // TODO: Deoptimise math
            SFX_SfxDefinition_Play_4CA700(
                &sAbeSFXList_555250[idx],
                ((unsigned int)((unsigned __int64)(2863311532i64 * (signed __int16)volume) >> 32) >> 31)
                + ((unsigned __int64)(2863311532i64 * (signed __int16)volume) >> 32),
                2 * (signed __int16)volume / 9,
                pitch,
                pitch);
            break;
        case 4:
            // TODO: Deoptimise math
            SFX_SfxDefinition_Play_4CA700(
                &sAbeSFXList_555250[idx],
                ((unsigned int)((unsigned __int64)(1908874354i64 * (signed __int16)volume) >> 32) >> 31)
                + ((signed int)((unsigned __int64)(1908874354i64 * (signed __int16)volume) >> 32) >> 1),
                2 * (signed __int16)volume / 3,
                pitch,
                pitch);
            break;
        default:
            break;
        }
    }
}