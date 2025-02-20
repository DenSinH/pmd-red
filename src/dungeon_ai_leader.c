#include "global.h"
#include "dungeon_ai_leader.h"

#include "constants/status.h"
#include "constants/targeting.h"
#include "dungeon_ai_targeting.h"
#include "dungeon_leader.h"
#include "dungeon_visibility.h"
#include "pokemon_3.h"

bool8 TargetLeader(struct Entity *pokemon)
{
    if (pokemon->info->isNotTeamMember)
    {
        return FALSE;
    }
    return TacticsTargetLeader(pokemon->info->tactic);
}

struct Entity* GetLeaderIfVisible(struct Entity *pokemon)
{
    if (!pokemon->info->isNotTeamMember)
    {
        struct Entity *leader = GetLeader();
        if (leader &&
            leader->info->waitingStatus != STATUS_DECOY &&
            CanTarget(pokemon, leader, FALSE, FALSE) == TARGET_CAPABILITY_CANNOT_ATTACK &&
            CanTargetEntity(pokemon, leader))
        {
            return leader;
        }
    }
    return NULL;
}
