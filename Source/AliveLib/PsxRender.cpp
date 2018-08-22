#include "stdafx.h"
#include "PsxRender.hpp"
#include "Function.hpp"
#include "Psx.hpp"
#include "Midi.hpp"
#include "Primitives.hpp"
#include <gmock/gmock.h>


struct OtUnknown
{
    int** field_0_pOtStart;
    int** field_4;
    int** field_8_pOt_End;
};

ALIVE_ARY(1, 0xBD0D88, OtUnknown, 32, sOt_Stack_BD0D88, {});
ALIVE_VAR(1, 0xBD0C08, int, sOtIdxRollOver_BD0C08, 0);

ALIVE_VAR(1, 0xC2D03C, int, dword_C2D03C, 0);


ALIVE_VAR(1, 0x578318, short, sActiveTPage_578318, -1);
ALIVE_VAR(1, 0xbd0f0c, DWORD, sTexture_page_x_BD0F0C, 0);
ALIVE_VAR(1, 0xbd0f10, DWORD, sTexture_page_y_BD0F10, 0);
ALIVE_VAR(1, 0xbd0f14, DWORD, sTexture_page_idx_BD0F14, 0);
ALIVE_VAR(1, 0x57831c, DWORD, dword_57831C, 10);
ALIVE_VAR(1, 0xBD0F18, DWORD, sTexture_page_abr_BD0F18, 0);
ALIVE_VAR(1, 0xbd0f1c, WORD *, sTPage_src_ptr_BD0F1C, nullptr);

EXPORT int CC PSX_EMU_Render_Polys_2_51CCA0(int /*a1*/, int /*a2*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT int* CC PSX_EMU_Render_Polys_2_51E140(int /*a1*/, int /*a2*/)
{
    NOT_IMPLEMENTED();
    return nullptr;
}

EXPORT int CC PSX_EMU_Render_Polys_2_51D890(int /*a1*/, int /*a2*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT unsigned int CC PSX_EMU_Render_Polys_2_51C4C0(int /*a2*/, int /*a3*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT int CC PSX_EMU_Render_Polys_2_51C6E0(int /*a1*/, int /*a2*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT int* CC PSX_EMU_Render_Polys_2_51D2B0(int /*a1*/, int /*a2*/)
{
    NOT_IMPLEMENTED();
    return nullptr;
}

EXPORT int* CC PSX_EMU_Render_Polys_2_51E890(int /*a1*/, int /*a2*/)
{
    NOT_IMPLEMENTED();
    return nullptr;
}

EXPORT int CC PSX_EMU_Render_Polys_2_51DC90(int /*a1*/, int /*a2*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT int CC PSX_EMU_Render_Polys_2_51C590(int /*a1*/, int /*a2*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT int* CC PSX_EMU_Render_Polys_2_51C8D0(int /*a1*/, int /*size*/)
{
    NOT_IMPLEMENTED();
    return nullptr;
}

ALIVE_VAR(1, 0xC2D04C, decltype(&PSX_EMU_Render_51EF90), pPSX_EMU_Render_51EF90_C2D04C, nullptr);
ALIVE_VAR(1, 0xBD3364, decltype(&PSX_EMU_Render_Polys_2_51CCA0), pPSX_EMU_51CCA0_BD3364, nullptr);
ALIVE_VAR(1, 0xBD328C, decltype(&PSX_EMU_Render_Polys_2_51E140), pPSX_EMU_51E140_BD328C, nullptr);
ALIVE_VAR(1, 0xBD3360, decltype(&PSX_EMU_Render_Polys_2_51D890), pPSX_EMU_51D890_BD3360, nullptr);
ALIVE_VAR(1, 0xBD32D4, decltype(&PSX_EMU_Render_Polys_2_51C4C0), pPSX_EMU_51C4C0_BD32D4, nullptr);
ALIVE_VAR(1, 0xBD32D0, decltype(&PSX_EMU_Render_Polys_2_51C6E0), pPSX_EMU_51C6E0_BD32D0, nullptr);
ALIVE_VAR(1, 0xBD327C, decltype(&PSX_EMU_Render_Polys_2_51D2B0), pPSX_EMU_51D2B0_BD327C, nullptr);
ALIVE_VAR(1, 0xBD326C, decltype(&PSX_EMU_Render_Polys_2_51E890), pPSX_EMU_51E890_BD326C, nullptr);
ALIVE_VAR(1, 0xBD3274, decltype(&PSX_EMU_Render_Polys_2_51DC90), pPSX_EMU_51DC90_BD3274, nullptr);
ALIVE_VAR(1, 0xBD3354, decltype(&PSX_EMU_Render_Polys_2_51C590), pPSX_EMU_51C590_BD3354, nullptr);
ALIVE_VAR(1, 0xBD335C, decltype(&PSX_EMU_Render_Polys_2_51C8D0), pPSX_EMU_51C8D0_BD335C, nullptr);

ALIVE_VAR(1, 0xc215c0, DWORD, sSemiTransShift_C215C0, 0);
ALIVE_VAR(1, 0xc215c4, DWORD, sRedShift_C215C4, 0);
ALIVE_VAR(1, 0xc1d180, DWORD, sGreenShift_C1D180, 0);
ALIVE_VAR(1, 0xc19140, DWORD, sBlueShift_C19140, 0);

EXPORT int CC PSX_EMU_SetDispType_4F9960(int dispType)
{
    NOT_IMPLEMENTED();

    // HACK / enough impl to allow standalone to boot
    sVGA_DisplayType_BD1468 = dispType;

    sRedShift_C215C4 = 11;
    sGreenShift_C1D180 = 6;
    sBlueShift_C19140 = 0;
    sSemiTransShift_C215C0 = 5;

    pPSX_EMU_Render_51EF90_C2D04C = PSX_EMU_Render_51EF90;
    pPSX_EMU_51CCA0_BD3364 = PSX_EMU_Render_Polys_2_51CCA0;
    pPSX_EMU_51E140_BD328C = PSX_EMU_Render_Polys_2_51E140;
    pPSX_EMU_51D890_BD3360 = PSX_EMU_Render_Polys_2_51D890;
    pPSX_EMU_51C4C0_BD32D4 = PSX_EMU_Render_Polys_2_51C4C0;
    pPSX_EMU_51C6E0_BD32D0 = PSX_EMU_Render_Polys_2_51C6E0;
    pPSX_EMU_51D2B0_BD327C = PSX_EMU_Render_Polys_2_51D2B0;
    pPSX_EMU_51E890_BD326C = PSX_EMU_Render_Polys_2_51E890;
    pPSX_EMU_51DC90_BD3274 = PSX_EMU_Render_Polys_2_51DC90;
    pPSX_EMU_51C590_BD3354 = PSX_EMU_Render_Polys_2_51C590;
    pPSX_EMU_51C8D0_BD335C = PSX_EMU_Render_Polys_2_51C8D0;

    /*
    dword_BD3290 = (int)PSX_EMU_nullsub_20;
    dword_BD3280 = (int)PSX_EMU_nullsub_22;
    dword_BD3288 = (int)PSX_EMU_nullsub_24;
    dword_BD3268 = (int)PSX_EMU_nullsub_21;
    dword_BD3284 = (int)PSX_EMU_nullsub_23;
    dword_BD3278 = (int)PSX_EMU_nullsub_25;
    */

    return 0;
}


template <typename T>
T clip(const T& n, const T& lower, const T& upper) 
{
    return max(lower, min(n, upper));
}

EXPORT signed int CC PSX_ClearImage_4F5BD0(PSX_RECT* pRect, unsigned __int8 r, unsigned __int8 g, unsigned __int8 b)
{
    if (!BMP_Lock_4F1FF0(&sPsxVram_C1D160))
    {
        return 0;
    }

    // Max bound check
    if (pRect->x >= 1024 || pRect->y >= 512)
    {
        return 0;
    }

    // Min bound check
    if (pRect->w + pRect->x - 1 < 0 || pRect->h + pRect->y - 1 < 0)
    {
        return 0;
    }

    int rect_x1 = pRect->x;
    int rect_y1 = pRect->y;
    int rect_right = pRect->w + rect_x1 - 1;
    int rect_bottom = pRect->h + rect_y1 - 1;

    rect_x1 = clip(rect_x1, 0, 1023);

    if (rect_right > 1023)
    {
        rect_right = 1023;
    }

    rect_y1 = clip(rect_y1, 0, 511);

    if (rect_bottom > 511)
    {
        rect_bottom = 511;
    }

    WORD colour_value = 
        ((1 << sSemiTransShift_C215C0) // TODO: Might be something else
        | (static_cast<unsigned int>(r) >> 3 << sRedShift_C215C4)
        | (static_cast<unsigned int>(g) >> 3 << sGreenShift_C1D180)
        | (static_cast<unsigned int>(b) >> 3 << sBlueShift_C19140));

    WORD* pVram = reinterpret_cast<WORD*>(sPsxVram_C1D160.field_4_pLockedPixels) + sizeof(WORD) * (rect_x1 + rect_y1 * (sPsxVram_C1D160.field_10_locked_pitch / sizeof(WORD)));

    const int rect_h = rect_bottom - rect_y1 + 1;
    const int rect_w = rect_right - rect_x1 + 1;
    if (rect_h - 1 >= 0)
    {
        const int pitch_words =  sPsxVram_C1D160.field_10_locked_pitch / sizeof(WORD);
        for (int y=0; y<rect_h; y++)
        {
            for (int x = 0; x < rect_w; x++)
            {
                pVram[x] = colour_value;
            }
            pVram += pitch_words;
        }
    }
    BMP_unlock_4F2100(&sPsxVram_C1D160);
    return 1;
}

EXPORT void CC PSX_ClearOTag_4F6290(int** otBuffer, int otBufferSize)
{
    PSX_OrderingTable_4F62C0(otBuffer, otBufferSize);

    // Set each element to point to the next
    int i = 0;
    for (i = 0; i < otBufferSize - 1; i++)
    {
        otBuffer[i] = reinterpret_cast<int*>(&otBuffer[i + 1]);
    }

    // Terminate the list
    otBuffer[i] = reinterpret_cast<int*>(0xFFFFFFFF);
}

EXPORT void CC PSX_OrderingTable_4F62C0(int** otBuffer, int otBufferSize)
{
    int otIdx = 0;
    for (otIdx = 0; otIdx < 32; otIdx++)
    {
        if (otBuffer == sOt_Stack_BD0D88[otIdx].field_0_pOtStart)
        {
            break;
        }
    }

    if (otIdx == 32)
    {
        sOtIdxRollOver_BD0C08 = (sOtIdxRollOver_BD0C08 & 31);
        otIdx = sOtIdxRollOver_BD0C08;
    }

    sOt_Stack_BD0D88[otIdx].field_0_pOtStart = otBuffer;
    sOt_Stack_BD0D88[otIdx].field_4 = otBuffer;
    sOt_Stack_BD0D88[otIdx].field_8_pOt_End = &otBuffer[otBufferSize];
}

EXPORT signed int __cdecl PSX_OT_Idx_From_Ptr_4F6A40(unsigned int /*ot*/)
{
    NOT_IMPLEMENTED();
    return 0;
}


EXPORT void __cdecl PSX_2_4F6A70(PSX_RECT* /*pRect*/, void* /*pPrim*/)
{
    NOT_IMPLEMENTED();
}

EXPORT unsigned __int8* CC PSX_Render_Polys_1_4F7110(void* /*a1*/, int /*a2*/, int /*a3*/)
{
    NOT_IMPLEMENTED();
    return nullptr;
}

EXPORT void __cdecl PSX_Render_Polys_2_4F7960(unsigned __int8* /*a1*/, int /*a2*/, int /*a3*/)
{
    NOT_IMPLEMENTED();
}

ALIVE_VAR(1, 0xbd30e4, int, sScreenXOffSet_BD30E4, 0);
ALIVE_VAR(1, 0xbd30a4, int, sScreenYOffset_BD30A4, 0);

EXPORT void CC PSX_Render_Line_Prim_4F7D90(void* /*pOtPrim*/, int /*offX*/, int /*offY*/)
{
    NOT_IMPLEMENTED();
}

EXPORT void CC PSX_84_4F7B80(int /*a1*/, int /*a2*/, int /*a3*/, int /*a4*/, int /*a5*/)
{
    NOT_IMPLEMENTED();
}

static void DrawOTag_Render_SPRT(PrimAny& any, __int16 drawEnv_of0, __int16 drawEnv_of1, short width, short height)
{
    BYTE b = 0;
    BYTE g = 0;
    BYTE r = 0;

    // Blending disabled bit
    if (any.mPrimHeader->rgb_code.code_or_pad & 1)
    {
        r = 128;
        g = 128;
        b = 128;
    }
    else
    {
        r = any.mPrimHeader->rgb_code.r;
        g = any.mPrimHeader->rgb_code.g;
        b = any.mPrimHeader->rgb_code.b;
    }

    const short x0 = drawEnv_of0 + any.mSprt->mBase.vert.x;
    const short y0 = drawEnv_of1 + any.mSprt->mBase.vert.y;
    const short u0 = any.mSprt->mUv.u;
    const short v0 = any.mSprt->mUv.v;

    // Render flat or textured rectangle
    pPSX_EMU_Render_51EF90_C2D04C(
        x0, y0,
        u0, v0,
        r,
        g,
        b,
        width,
        height,
        any.mSprt->mUv.tpage_clut_pad,
        any.mPrimHeader->rgb_code.code_or_pad & 2); // Semi transparency bit
}

static void DrawOTag_Render_TILE(PrimAny& any, short x, short y, short w, short h)
{
    PSX_RECT rect = { x,y,w,h };
    PSX_2_4F6A70(&rect, any.mVoid);
}

static void DrawOTag_HandlePrimRendering(PrimAny& any, __int16 drawEnv_of0, __int16 drawEnv_of1)
{
    switch (PSX_Prim_Code_Without_Blending_Or_SemiTransparency(any.mPrimHeader->rgb_code.code_or_pad))
    {
    case PrimTypeCodes::eSprt:
        DrawOTag_Render_SPRT(any, drawEnv_of0, drawEnv_of1, any.mSprt->field_14_w, any.mSprt->field_16_h);
        break;

    case PrimTypeCodes::eSprt8:
        DrawOTag_Render_SPRT(any, drawEnv_of0, drawEnv_of1, 8, 8);
        break;

    case PrimTypeCodes::eSprt16:
        DrawOTag_Render_SPRT(any, drawEnv_of0, drawEnv_of1, 16, 16);
        break;

    case PrimTypeCodes::eTile:
        DrawOTag_Render_TILE(any, drawEnv_of0 + any.mSprt->mBase.vert.x, drawEnv_of1 + any.mSprt->mBase.vert.y, any.mTile->field_14_w, any.mTile->field_16_h);
        break;

    case PrimTypeCodes::eTile1:
        DrawOTag_Render_TILE(any, drawEnv_of0 + any.mSprt->mBase.vert.x, drawEnv_of1 + any.mSprt->mBase.vert.y, 1, 1);
        break;

    case PrimTypeCodes::eTile8:
        DrawOTag_Render_TILE(any, drawEnv_of0 + any.mSprt->mBase.vert.x, drawEnv_of1 + any.mSprt->mBase.vert.y, 8, 8);
        break;

    case PrimTypeCodes::eTile16:
        DrawOTag_Render_TILE(any, drawEnv_of0 + any.mSprt->mBase.vert.x, drawEnv_of1 + any.mSprt->mBase.vert.y, 16, 16);
        break;

    case PrimTypeCodes::eLineF2:
    case PrimTypeCodes::eLineF3:
    case PrimTypeCodes::eLineF4:
    case PrimTypeCodes::eLineG2:
    case PrimTypeCodes::eLineG3:
    case PrimTypeCodes::eLineG4:
        PSX_Render_Line_Prim_4F7D90(any.mVoid, drawEnv_of0, drawEnv_of1);
        break;

    case PrimTypeCodes::ePolyF3:
    case PrimTypeCodes::ePolyFT3:
    case PrimTypeCodes::ePolyG3:
    case PrimTypeCodes::ePolyGT3:
    case PrimTypeCodes::ePolyF4:
    case PrimTypeCodes::ePolyFT4:
    case PrimTypeCodes::ePolyG4:
    case PrimTypeCodes::ePolyGT4:
        {
            // I think this works by func 1 populating some data structure and then func 2 does the actual rendering
            unsigned __int8* pPolyBuffer = PSX_Render_Polys_1_4F7110(any.mVoid, drawEnv_of0, drawEnv_of1);
            if (pPolyBuffer)
            {
                PSX_Render_Polys_2_4F7960(pPolyBuffer, drawEnv_of0, drawEnv_of1);
            }
        }
        break;
    }
}

static bool DrawOTagImpl(int** pOT, __int16 drawEnv_of0, __int16 drawEnv_of1)
{
    sScreenXOffSet_BD30E4 = 0;
    sScreenYOffset_BD30A4 = 0;
    sActiveTPage_578318 = -1;

    int otIdx = PSX_OT_Idx_From_Ptr_4F6A40((unsigned int)pOT);
    if (otIdx < 0)
    {
        return false;
    }

    int** pLastOtItem = sOt_Stack_BD0D88[otIdx].field_4;
    int** pOtEnd = sOt_Stack_BD0D88[otIdx].field_8_pOt_End;
    int** pOtItem = pOT;
    while (pOtItem)
    {
        if (pOtItem == (int **)-1)
        {
            break;
        }

        MIDI_UpdatePlayer_4FDC80();

        PrimAny any;
        any.mVoid = pOtItem;

        if (pOtItem < pLastOtItem || pOtItem >= pOtEnd) // Must actually be start otherwise check makes no sense ??
        {
            int itemToDrawType = any.mPrimHeader->rgb_code.code_or_pad;
            switch (itemToDrawType)
            {
            case 2: // TODO: unknown
                PSX_2_4F6A70(nullptr, any.mVoid);
                break;

            case PrimTypeCodes::eSetTPage:
                PSX_TPage_Change_4F6430(static_cast<short>(any.mSetTPage->field_C_tpage));
                break;

            case PrimTypeCodes::ePrimClipper:
                sPSX_EMU_DrawEnvState_C3D080.field_0_clip.x = any.mPrimClipper->field_C_x;
                sPSX_EMU_DrawEnvState_C3D080.field_0_clip.y = any.mPrimClipper->field_E_y;
                sPSX_EMU_DrawEnvState_C3D080.field_0_clip.w = any.mPrimHeader->header.mRect.w;
                sPSX_EMU_DrawEnvState_C3D080.field_0_clip.h = any.mPrimHeader->header.mRect.h;

                PSX_SetDrawEnv_Impl_4FE420(
                    16 * any.mPrimClipper->field_C_x,
                    16 * any.mPrimClipper->field_E_y,
                    (16 * (any.mPrimClipper->field_C_x + any.mPrimHeader->header.mRect.w)) - 16,
                    (16 * (any.mPrimClipper->field_E_y + any.mPrimHeader->header.mRect.h)) - 16,
                    1000 / 2,
                    nullptr);
                break;
            case PrimTypeCodes::eScreenOffset:
                // NOTE: Conditional on dword_55EF94 removed as it is constant 1
                sScreenXOffSet_BD30E4 = any.mScreenOffset->field_C_xoff * 2;
                sScreenYOffset_BD30A4 = any.mScreenOffset->field_E_yoff;
                break;

            case 0x83: // TODO: unknown
                // Unlock because move image will lock + unlock again
                BMP_unlock_4F2100(&sPsxVram_C1D160);
                PSX_MoveImage_4F5D50((PSX_RECT *)(pOtItem + 5), (int)pOtItem[3], (int)pOtItem[4]);

                // Hence lock again after move image
                if (BMP_Lock_4F1FF0(&sPsxVram_C1D160))
                {
                    break;
                }

                if (sPsxEmu_EndFrameFnPtr_C1D17C)
                {
                    sPsxEmu_EndFrameFnPtr_C1D17C(1);
                }
                return true;

            case 0x84: // TODO: unknown
                // Appears for gas..
                PSX_84_4F7B80((int)pOtItem[3], (int)pOtItem[4], (int)pOtItem[5], (int)pOtItem[6], (int)pOtItem[7]);
                break;
            default:
                DrawOTag_HandlePrimRendering(any, drawEnv_of0, drawEnv_of1);
                break;
            }
        }

        // To the next item
        pOtItem = (int **)any.mPrimHeader->tag;
    }

    return false;
}

EXPORT void CC PSX_DrawOTag_4F6540(int** pOT)
{
    if (!sPsxEmu_EndFrameFnPtr_C1D17C || !sPsxEmu_EndFrameFnPtr_C1D17C(0))
    {
        if (byte_BD0F20 || !BMP_Lock_4F1FF0(&sPsxVram_C1D160))
        {
            if (sPsxEmu_EndFrameFnPtr_C1D17C)
            {
                sPsxEmu_EndFrameFnPtr_C1D17C(1);
            }
            return;
        }

        __int16 drawEnv_of0 = 0;
        __int16 drawEnv_of1 = 0;

        if (bDontUseXYOffsetInRender_BD1464)
        {
            if (!BMP_Lock_4F1FF0(&stru_C1D1A0))
            {
                BMP_unlock_4F2100(&sPsxVram_C1D160);
                if (sPsxEmu_EndFrameFnPtr_C1D17C)
                {
                    sPsxEmu_EndFrameFnPtr_C1D17C(1);
                }
                return;
            }
            spBitmap_C2D038 = &stru_C1D1A0;
            drawEnv_of1 = 0;
            drawEnv_of0 = 0;
        }
        else
        {
            spBitmap_C2D038 = &sPsxVram_C1D160;
            drawEnv_of0 = sPSX_EMU_DrawEnvState_C3D080.field_8_ofs[0];
            drawEnv_of1 = sPSX_EMU_DrawEnvState_C3D080.field_8_ofs[1];
        }

        if (DrawOTagImpl(pOT, drawEnv_of0, drawEnv_of1))
        {
            return;
        }

        if (bDontUseXYOffsetInRender_BD1464)
        {
            BMP_unlock_4F2100(&stru_C1D1A0);
        }

        BMP_unlock_4F2100(&sPsxVram_C1D160);
        if (sPsxEmu_EndFrameFnPtr_C1D17C)
        {
            sPsxEmu_EndFrameFnPtr_C1D17C(1);
        }
        return;
    }
}

EXPORT void CC PSX_TPage_Change_4F6430(__int16 tPage)
{
    if (sActiveTPage_578318 != tPage)
    {
        sActiveTPage_578318 = tPage;

        // NOTE: Branch guarded by PSX_Ret_0_4F60D0 removed

        // Extract parts of the tpage
        sTexture_page_x_BD0F0C = (tPage & 0xF) << 6;
        sTexture_page_y_BD0F10 = 16 * (tPage & 0x10) + (((unsigned int)tPage >> 2) & 0x200);

        sTexture_page_idx_BD0F14 = ((unsigned int)tPage >> 7) & 3;
        sTexture_page_abr_BD0F18 = ((unsigned int)tPage >> 5) & 3;

        // TODO: Figure out why page 3 is forced to 2
        if (sTexture_page_idx_BD0F14 == 3)
        {
            sTexture_page_idx_BD0F14 = 2;
        }

        // NOTE: Branch guarded by dword_BD2250[tPage & 31] removed as it is never written

        dword_57831C = 10;
        sTPage_src_ptr_BD0F1C = reinterpret_cast<WORD*>(sPsxVram_C1D160.field_4_pLockedPixels) + (sTexture_page_x_BD0F0C + (sTexture_page_y_BD0F10 * 1024));
    }
}

EXPORT bool CC PSX_Rects_intersect_point_4FA100(const PSX_RECT* pScreen, const PSX_RECT* pToRender, PSX_RECT* pOverlapRect, int* uStart, int* vStart)
{
    const bool bOverlaps = PSX_Rects_overlap_4FA0B0(pScreen, pToRender) ? true : false;
    if (bOverlaps)
    {
        int biggestRight = pToRender->x + pToRender->w;
        if (biggestRight > pScreen->x + pScreen->w)
        {
            biggestRight = pScreen->x + pScreen->w;
        }

        const __int16 overlap_w = static_cast<short>(biggestRight - pToRender->x);
        pOverlapRect->w = overlap_w;
        if (pToRender->x >= pScreen->x)
        {
            pOverlapRect->x = pToRender->x;
        }
        else
        {
            pOverlapRect->x = pScreen->x;
            pOverlapRect->w = pToRender->x + overlap_w - pScreen->x;
            *uStart += pScreen->x - pToRender->x;
        }


        int biggestBottom = pToRender->y + pToRender->h;
        if (biggestBottom > pScreen->y + pScreen->h)
        {
            biggestBottom = pScreen->y + pScreen->h;
        }

        const __int16 overlap_h = static_cast<short>(biggestBottom - pToRender->y);
        pOverlapRect->h = overlap_h;
        if (pToRender->y >= pScreen->y)
        {
            pOverlapRect->y = pToRender->y;
        }
        else
        {
            pOverlapRect->y = pScreen->y;
            pOverlapRect->h = pToRender->y + overlap_h - pScreen->y;
            *vStart += pScreen->y - pToRender->y;
        }
    }
    return bOverlaps;
}

EXPORT void CC PSX_EMU_Render_TPage_0_51F0E0(PSX_RECT* /*a1*/, int /*a2*/, int /*a3*/, unsigned __int8 /*a4*/, unsigned __int8 /*a5*/, unsigned __int8 /*a6*/, unsigned __int16 /*a7*/, char /*a8*/)
{
    NOT_IMPLEMENTED();
}

EXPORT void CC PSX_EMU_Render_TPage_1_51F660(PSX_RECT* /*pRect*/, int /*tpagex_off*/, int /*tpagey_off*/, unsigned __int8 /*r*/, unsigned __int8 /*g*/, unsigned __int8 /*b*/, unsigned __int16 /*a7*/, char /*a8*/)
{
    NOT_IMPLEMENTED();
}

EXPORT void CC PSX_EMU_Background_Render_51C490(BYTE *pVram, BYTE *pSrc, unsigned int amount)
{
    for (unsigned int i = 0; i < amount; i++)
    {
        pVram[i] = pSrc[i];
    }
}

EXPORT void CC PSX_EMU_Render_TPage_2_51FA30(PSX_RECT* /*pRect*/, int /*tpageX*/, int /*tpageY*/, unsigned __int8 /*r*/, unsigned __int8 /*g*/, unsigned __int8 /*b*/, int /*a7*/, char /*a8*/)
{
    NOT_IMPLEMENTED();
}

EXPORT void CC PSX_EMU_Render_51EF90(__int16 x, __int16 y, int u, int v, BYTE r, BYTE g, BYTE b, __int16 w, __int16 h, WORD clut, int semiTrans)
{
    // Get the screen rect
    PSX_RECT screenRect  = {};
    if (bDontUseXYOffsetInRender_BD1464)
    {
        screenRect.y = 0;
        screenRect.x = 0;
        screenRect.w = sPSX_EMU_DrawEnvState_C3D080.field_0_clip.w;
        screenRect.h = sPSX_EMU_DrawEnvState_C3D080.field_0_clip.h;
    }
    else
    {
        screenRect = sPSX_EMU_DrawEnvState_C3D080.field_0_clip;
    }

    // Check for overlap
    const PSX_RECT toRenderRect = { x , y, w, h };
    PSX_RECT overlapRect = {};
    if (PSX_Rects_intersect_point_4FA100(&screenRect, &toRenderRect, &overlapRect, &u, &v))
    {
        // Render
        if (sTexture_page_idx_BD0F14 == 0)
        {
            PSX_EMU_Render_TPage_0_51F0E0(&overlapRect, u, v, r, g, b, clut, static_cast<char>(semiTrans));
        }
        else if (sTexture_page_idx_BD0F14 == 1)
        {
            PSX_EMU_Render_TPage_1_51F660(&overlapRect, u, v, r, g, b, clut, static_cast<char>(semiTrans));
        }
        else if (sTexture_page_idx_BD0F14 == 2)
        {
            PSX_EMU_Render_TPage_2_51FA30(&overlapRect, u, v, r, g, b, clut, static_cast<char>(semiTrans));
        }
    }
}

namespace Test
{
    static void Test_PSX_Rects_intersect_point_4FA100()
    {
        PSX_RECT r1 = { 0,0, 300, 150 };
        PSX_RECT r2 = { 10, 10, 50, 200 };
        PSX_RECT ro = {};
        int px = 0;
        int py = 0;
        ASSERT_EQ(1, PSX_Rects_intersect_point_4FA100(&r1, &r2, &ro, &px, &py));

        ASSERT_EQ(px, 0);

    }

    static void Test_PSX_TPage_Change_4F6430()
    {
        sActiveTPage_578318 = 0;
        sTexture_page_x_BD0F0C = 0;
        sTexture_page_y_BD0F10 = 0;
        sTexture_page_idx_BD0F14 = 0;
        dword_57831C = 0;

        for (DWORD i = 0; i < 3; i++)
        {
            int tpage = PSX_getTPage_4F60E0(static_cast<char>(i), static_cast<char>(3 - i), 64 * i, (i == 0u) ? 0u : 256u);
            PSX_TPage_Change_4F6430(static_cast<short>(tpage));

            ASSERT_EQ(sActiveTPage_578318, tpage);
            ASSERT_EQ(sTexture_page_x_BD0F0C, 64u * i);
            ASSERT_EQ(sTexture_page_y_BD0F10, (i == 0) ? 0u : 256u);
            ASSERT_EQ(sTexture_page_idx_BD0F14, i);
            ASSERT_EQ(sTexture_page_abr_BD0F18, 3 - i);
            ASSERT_EQ(dword_57831C, 10u);
        }
    }

    void PsxRenderTests()
    {
        Test_PSX_TPage_Change_4F6430();
        Test_PSX_Rects_intersect_point_4FA100();
    }
}
