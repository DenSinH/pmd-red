#include "global.h"
#include "constants/mailbox.h"
#include "code_800D090.h"
#include "input.h"
#include "memory.h"
#include "text.h"
#include "pokemon_mail.h"
#include "wonder_mail.h"
#include "code_802C39C.h"

bool8 IsMailSlotEmpty(u8);
extern void sub_8013984(void *);
extern void sub_8013848(u32 *, s32, u32, u32);
extern s32 sub_802C474(void);
extern void sub_8012D34(struct UnkTextStruct2 *, u32);
extern void sub_802C328(void);
extern void sub_802C39C(void);
extern void PlayMenuSoundEffect(u32);
extern void sub_8013660(u32 *);
extern s32 GetKeyPress(u32 *);
extern bool8 sub_80138B8(u32 *, u32);
extern void AddMenuCursorSprite(u32 *);
extern u8 sub_802C4A4(void);
extern void sub_8008C54(u32);
extern void sub_80073B8(u32);
extern void sub_80073E0(u32);

extern s32 sub_8013800(u32 *, s32);
extern struct WonderMail *GetPelipperBoardSlotInfo(u32);
extern void sub_803B35C(struct WonderMail *, u32 *);
extern u8 gBulletinBoardText[];
extern bool8 IsMailinJobSlot(struct WonderMail *);
extern void CreateRescueTitle(void *);
extern void xxx_call_draw_string(s32, s32, u8 *, s32, s32);
extern void sub_8012BC4(s32, s32, s32, s32 ,s32 ,s32);


struct unkStruct_203B2D8
{
    // size: 0xA4
    u8 unk0[4];
    u32 unk4;
    u8 fill8[0x1C - 0x8];
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 fill24;
    /* 0x26 */ s16 emptyMailSlots;
    u8 fill28[0x38 - 0x28];
    u32 unk38;
    struct UnkTextStruct2 *unk3C;
    struct UnkTextStruct2 unk40[4];
    u8 unkA0[4];
};


extern struct unkStruct_203B2D8 *gUnknown_203B2D8;

struct unkStruct_203B2E0
{
    // size: 0xA8
    u8 unk0[0x8];
    u32 unk8;
    u8 unkC[0x20 - 0xC];
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    u8 fill22[0x3C - 0x2C];
    s32 unk3C;
    struct UnkTextStruct2 *unk40;
    struct UnkTextStruct2 unk44[4];
    u8 unkA4[4];
};
extern struct unkStruct_203B2E0 *gUnknown_203B2E0;

extern struct UnkTextStruct2 gUnknown_80DFCB4;
extern struct UnkTextStruct2 gUnknown_80DFC9C;

extern u16 gUnknown_203B2E4;

extern struct WonderMail *GetMailboxSlotInfo(u8);
extern void CreateRescueTitle(void *);
extern struct PokemonStruct *GetPlayerPokemonStruct(void);
extern u8 gMailboxText[];
extern u8 gAvailablePokemonNames[];
extern void PrintPokeNameToBuffer(u8 *buffer, struct PokemonStruct *pokemon);
extern void sub_803B6B0(u32, u32, u32, u32);

void CreateMailMenu(void)
{
  struct WonderMail *mail;
  s32 y;
  s32 index;
  struct unkStruct_802C39C local;
  u8 buffer [128];
  
  sub_8008C54(gUnknown_203B2D8->unk38);
  sub_80073B8(gUnknown_203B2D8->unk38);
  xxx_call_draw_string(gUnknown_203B2D8->unk22 * 8 + 10,0,gMailboxText,gUnknown_203B2D8->unk38,0);
  index = 0;
  if (index < gUnknown_203B2D8->unk1E) {
    do {
      mail = GetMailboxSlotInfo(gUnknown_203B2D8->unk0[(gUnknown_203B2D8->unk22 * gUnknown_203B2D8->unk20) + index]);
      local.unk0[0] = gUnknown_203B2D8->unk38;
      local.y = sub_8013800(&gUnknown_203B2D8->unk4, index);
      if (mail->mailType == 1) {
        y = sub_8013800(&gUnknown_203B2D8->unk4, index);
        sub_803B6B0(10,y,6,gUnknown_203B2D8->unk38);
        PrintPokeNameToBuffer(gAvailablePokemonNames, GetPlayerPokemonStruct());
        sprintfStatic(buffer, GetPokemonMailHeadline(mail->dungeon.floor), gAvailablePokemonNames);
        xxx_call_draw_string(0x15,y,buffer,gUnknown_203B2D8->unk38,0);
      }
      else {
       sub_803B35C(mail,local.unk0);
        if (IsMailinJobSlot(mail)) {
          local.unk43 = 2;
        }
        CreateRescueTitle(&local);
      }
      index++;
    } while (index < gUnknown_203B2D8->unk1E);
  }
  sub_80073E0(gUnknown_203B2D8->unk38);
}

s32 CountEmptyMailSlots(void)
{
    s32 mailSlots;
    s32 index;

    mailSlots = 0;
    for(index = 0; index < NUM_MAILBOX_SLOTS; index++)
    {
        if(!IsMailSlotEmpty(index))
        {
            gUnknown_203B2D8->unk0[mailSlots] = index;
            mailSlots++;
        }
    }
    return mailSlots;
}

bool8 HasNoMailinMailbox(void)
{
    s32 index;
    for(index = 0; index < NUM_MAILBOX_SLOTS; index++)
    {
        if(!IsMailSlotEmpty(index))
            return FALSE;
    }
    return TRUE;
}


bool8 sub_802C10C(s32 param_1,struct UnkTextStruct2_sub *param_2,s32 param_3)
{
  if (sub_802C4A4() != 0) {
      return FALSE;
  }
  else
  {
    if (gUnknown_203B2E0 == NULL) {
      gUnknown_203B2E0 = MemoryAlloc(sizeof(struct unkStruct_203B2E0),8);
    }
    gUnknown_203B2E0->unk3C = param_1;
    gUnknown_203B2E0->unk40 = &gUnknown_203B2E0->unk44[param_1];
    sub_8006518(gUnknown_203B2E0->unk44);

    gUnknown_203B2E0->unk44[gUnknown_203B2E0->unk3C] = gUnknown_80DFCB4;
    gUnknown_203B2E0->unk40->unk14 = gUnknown_203B2E0->unkA4;
    if (param_2 != NULL) {
      gUnknown_203B2E0->unk44[gUnknown_203B2E0->unk3C].unk08 = *param_2;
    }
    sub_8012D34(gUnknown_203B2E0->unk40,param_3);
    ResetUnusedInputStruct();
    sub_800641C(gUnknown_203B2E0->unk44,1,1);
    sub_8013848(&gUnknown_203B2E0->unk8,sub_802C474(),param_3,param_1);
    gUnknown_203B2E0->unk20 = gUnknown_203B2E4;
    sub_8013984(&gUnknown_203B2E0->unk8);
    sub_802C328();
    sub_802C39C();
    return TRUE;
  }
}

u32 sub_802C1E4(u8 param_1)
{
  if (param_1 == '\0') {
    sub_8013660(&gUnknown_203B2E0->unk8);
    return 0;
  }
  else {
    switch(GetKeyPress(&gUnknown_203B2E0->unk8))
    {
        case 2:
            PlayMenuSoundEffect(1);
            return 2;
        case 1:
            PlayMenuSoundEffect(0);
            return 3;
        case 4:
            PlayMenuSoundEffect(4);
            return 4;
        default:
            if (sub_80138B8(&gUnknown_203B2E0->unk8,1)) {
                sub_802C328();
                sub_802C39C();
                return 1;
            }
            else {
                return 0;
            }
    }
  }
}

u8 sub_802C26C(void)
{
    return gUnknown_203B2E0->unk0[(gUnknown_203B2E0->unk26 * gUnknown_203B2E0->unk24) + gUnknown_203B2E0->unk20];
}

void sub_802C28C(u8 r0)
{
    ResetUnusedInputStruct();
    sub_800641C(gUnknown_203B2E0->unk44, 0, 0);
    gUnknown_203B2E0->unk2A = sub_802C474();
    sub_8013984(&gUnknown_203B2E0->unk8);
    sub_802C328();
    sub_802C39C();
    if(r0)
        AddMenuCursorSprite(&gUnknown_203B2E0->unk8);
}

void sub_802C2D4(void)
{
    if(gUnknown_203B2E0 != NULL)
    {
        gUnknown_203B2E4 = gUnknown_203B2E0->unk20;
        gUnknown_203B2E0->unk44[gUnknown_203B2E0->unk3C] = gUnknown_80DFC9C;
        ResetUnusedInputStruct();
        sub_800641C(gUnknown_203B2E0->unk44, 1, 1);
        MemoryFree(gUnknown_203B2E0);
        gUnknown_203B2E0 = NULL;
    }
}

NAKED
void sub_802C328(void)
{
    asm_unified(
	"\tpush {r4,lr}\n"
	"\tldr r4, _0802C398\n"
	"\tldr r0, [r4]\n"
	"\tldrh r1, [r0, 0x28]\n"
	"\tadds r0, 0xA4\n"
	"\tmovs r2, 0\n"
	"\tstrb r1, [r0]\n"
	"\tldr r0, [r4]\n"
	"\tldrh r1, [r0, 0x26]\n"
	"\tadds r0, 0xA5\n"
	"\tstrb r1, [r0]\n"
	"\tldr r0, [r4]\n"
	"\tadds r0, 0xA6\n"
	"\tmovs r1, 0xC\n"
	"\tstrb r1, [r0]\n"
	"\tldr r0, [r4]\n"
	"\tadds r0, 0xA7\n"
	"\tstrb r2, [r0]\n"
	"\tldr r0, [r4]\n"
	"\tmovs r1, 0x22\n"
	"\tldrsh r0, [r0, r1]\n"
	"\tmovs r1, 0x18\n"
	"\tbl sub_8009614\n"
	"\tadds r0, 0x2\n"
	"\tlsls r0, 16\n"
	"\tldr r2, [r4]\n"
	"\tldr r3, [r2, 0x3C]\n"
	"\tlsls r1, r3, 1\n"
	"\tadds r1, r3\n"
	"\tlsls r1, 3\n"
	"\tadds r1, r2, r1\n"
	"\tadds r1, 0x52\n"
	"\tasrs r3, r0, 16\n"
	"\tlsrs r0, 16\n"
	"\tstrh r0, [r1]\n"
	"\tldr r1, [r2, 0x3C]\n"
	"\tlsls r0, r1, 1\n"
	"\tadds r0, r1\n"
	"\tlsls r0, 3\n"
	"\tadds r2, r0\n"
	"\tadds r3, 0x2\n"
	"\tadds r2, 0x54\n"
	"\tstrh r3, [r2]\n"
	"\tbl ResetUnusedInputStruct\n"
	"\tldr r0, [r4]\n"
	"\tadds r0, 0x44\n"
	"\tmovs r1, 0x1\n"
	"\tmovs r2, 0x1\n"
	"\tbl sub_800641C\n"
	"\tpop {r4}\n"
	"\tpop {r0}\n"
	"\tbx r0\n"
	"\t.align 2, 0\n"
"_0802C398: .4byte gUnknown_203B2E0");
}

void sub_802C39C(void)
{
  u32 slotIndex;
  struct WonderMail *mail;
  s32 iVar4;
  s32 x;
  s32 index;
  struct unkStruct_802C39C local;
  
  sub_8008C54(gUnknown_203B2E0->unk3C);
  sub_80073B8(gUnknown_203B2E0->unk3C);
  iVar4 = gUnknown_203B2E0->unk26 * 8;
  x = iVar4;
  x += 10;
  xxx_call_draw_string(x,0,gBulletinBoardText,gUnknown_203B2E0->unk3C,0);
  iVar4 += 4;
  x = iVar4 + gUnknown_203B2E0->unkA4[2] * 8;
  sub_8012BC4(x,0,gUnknown_203B2E0->unk26 + 1,2,7,gUnknown_203B2E0->unk3C);

  index = 0;
  if(index < gUnknown_203B2E0->unk22)
    do 
    {
        slotIndex = (gUnknown_203B2E0->unk0[gUnknown_203B2E0->unk26 * gUnknown_203B2E0->unk24 + index]);
        mail = GetPelipperBoardSlotInfo(slotIndex);
        local.unk0[0] = gUnknown_203B2E0->unk3C;
        local.y = sub_8013800(&gUnknown_203B2E0->unk8,index);
        sub_803B35C(mail,local.unk0);
        if (IsMailinJobSlot(GetPelipperBoardSlotInfo(slotIndex))) {
            local.unk43 = 2;
        }
        CreateRescueTitle(&local);
        index++;
    } while (index < gUnknown_203B2E0->unk22);
  sub_80073E0(gUnknown_203B2E0->unk3C);
}
