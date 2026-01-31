////////////////////////////////////////////////////////////////////////////
//	Module 		: ai_debug.h
//	Created 	: 02.10.2001
//  Modified 	: 11.11.2003
//	Author		: Oles Shihkovtsov, Dmitriy Iassenev
//	Description : Debug functions
////////////////////////////////////////////////////////////////////////////

#pragma once

extern Flags32 psAI_Flags;

enum psAI_Flags : u32
{
#ifdef DEBUG
    aiDebug = (1 << 0),
    aiBrain = (1 << 1),
    aiMotion = (1 << 2),
    aiFrustum = (1 << 3),
    aiFuncs = (1 << 4),
    aiALife = (1 << 5),
    aiLua = (1 << 6),
    aiGOAP = (1 << 7),
    aiCover = (1 << 8),
    aiAnimation = (1 << 9),
    aiVision = (1 << 10),
    aiMonsterDebug = (1 << 11),
    aiStats = (1 << 12),
    aiDestroy = (1 << 13),
    aiSerialize = (1 << 14),
    aiDialogs = (1 << 15),
    aiInfoPortion = (1 << 16),
    aiGOAPScript = (1 << 17),
    aiGOAPObject = (1 << 18),
    aiStalker = (1 << 19),
    aiDrawGameGraph = (1 << 20),
    aiDrawGameGraphStalkers = (1 << 21),
    aiDrawGameGraphObjects = (1 << 22),
    aiNilObjectAccess = (1 << 23),
    aiDrawVisibilityRays = (1 << 24),
    aiAnimationStats = (1 << 25),
#endif // DEBUG
    aiIgnoreActor = (1 << 26),
};