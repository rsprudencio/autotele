#include "injection.h"
#include "D2Intercepts.h"

DWORD dwCount;
HANDLE TeleThread = NULL;
/*
todo:
linking
*/

//waypoints:
//ACT 1 || 119 == cold plains wp etc
//      || 157 == cata, jail wp
//ACT 2 || 156 == act 2 wilderniss, dry hills etc
//      || 323 == sewer wp
//      || 288 == cellar wp
//      || 402 == canyon of the magi, arcane
//ACT 3 || 324 == durance of hate 2
//      || 237 == all other a3 wp's
//ACT 4 || 238 == a4 river, city of the dead
//      || 398 == a4 town
//ACT 5 || 496 == a5 wilderniss
//      || 511 == frozen wp's(glacial trail etc)
//      || 494 == baal wp
int waypoints[] = {119, 157, 156, 323, 288, 402, 324, 237, 238, 398, 496, 511, 494};

/* 
   #{Type, Id, Id2, Area}
	{EXIT, MAP_A1_STONY_FIELD},			# NEXT
	{EXIT, MAP_A1_BURIAL_GROUNDS},		# OTHER
	{UNIT_OBJECT, 119},					# WAYPOINT
	{EXIT, MAP_A1_BLOOD_MOOR},			# PREV
*/

Vector vVector[] = {
	{0}, {0}, {0}, {0}, //0x0

	// MAP_A1_ROGUE_ENCAMPMENT					0x01
	{0},
	{0},
	{0},
	{0},

	// MAP_A1_BLOOD_MOOR						0x02
	{EXIT, MAP_A1_COLD_PLAINS},
	{EXIT, MAP_A1_DEN_OF_EVIL},
	{0},
	{EXIT, MAP_A1_ROGUE_ENCAMPMENT},

	// MAP_A1_COLD_PLAINS						0x03
	{EXIT, MAP_A1_STONY_FIELD},
	{EXIT, MAP_A1_BURIAL_GROUNDS},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_BLOOD_MOOR},

	// MAP_A1_STONY_FIELD						0x04
	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1},
	{UNIT_OBJECT, 61},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_COLD_PLAINS},

	// MAP_A1_DARK_WOOD							0x05
	{EXIT, MAP_A1_BLACK_MARSH},
	{UNIT_OBJECT, 30},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1},

	// MAP_A1_BLACK_MARSH						0x06
	{EXIT, MAP_A1_TAMOE_HIGHLAND},
	{EXIT, MAP_A1_FORGOTTEN_TOWER, 0x19, MAP_A1_TOWER_CELLAR_LEVEL_5},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_DARK_WOOD},

	// MAP_A1_TAMOE_HIGHLAND					0x07
	{EXIT, MAP_A1_MONASTERY_GATE},
	{EXIT, MAP_A1_PIT_LEVEL_1},
	{0},
	{EXIT, MAP_A1_BLACK_MARSH},

	// MAP_A1_DEN_OF_EVIL						0x08
	{0},
	{0},
	{0},
	{EXIT, MAP_A1_BLOOD_MOOR},

	// MAP_A1_CAVE_LEVEL_1						0x09 (Cave in Cold plains)
	{EXIT, MAP_A1_CAVE_LEVEL_2},
	{UNIT_MONSTER, 736},
	{0},
	{EXIT, MAP_A1_COLD_PLAINS},

	// MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1		0x0a
	{EXIT, MAP_A1_DARK_WOOD}, //0xa
	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_2},
	{0}, // {UNIT_OBJECT, 157}, < doesn't make sense as there is no waypoint there
	{EXIT, MAP_A1_STONY_FIELD},

	// MAP_A1_HOLE_LEVEL_1						0x0b
	{EXIT, MAP_A1_HOLE_LEVEL_2}, //0xb
	{EXIT, MAP_A1_HOLE_LEVEL_2},
	{0},
	{EXIT, MAP_A1_BLACK_MARSH},

	// MAP_A1_PIT_LEVEL_1						0x0c
	{EXIT, MAP_A1_PIT_LEVEL_2}, //0xc
	{EXIT, MAP_A1_PIT_LEVEL_2},
	{0},
	{EXIT, MAP_A1_TAMOE_HIGHLAND},

	// MAP_A1_CAVE_LEVEL_2						0x0d (Cave in Cold plains)
	{UNIT_OBJECT, 397}, //0xd
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_CAVE_LEVEL_1},

	// MAP_A1_UNDERGROUND_PASSAGE_LEVEL_2		0x0e
	{UNIT_OBJECT, 397},
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1},

	// MAP_A1_HOLE_LEVEL_2						0x0f
	{UNIT_OBJECT, 397},
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_HOLE_LEVEL_1},

	// MAP_A1_PIT_LEVEL_2						0x10
	{UNIT_OBJECT, 397}, //0x10
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_PIT_LEVEL_1},

	// MAP_A1_BURIAL_GROUNDS					0x11
	{EXIT, MAP_A1_MAUSOLEUM}, //0x11
	{UNIT_MONSTER, 805},
	{0},
	{EXIT, MAP_A1_COLD_PLAINS},

	// MAP_A1_CRYPT								0x12
	{0},
	{0},
	{0},
	{0},

	// MAP_A1_MAUSOLEUM							0x13
	{0},
	{0},
	{0},
	{EXIT, MAP_A1_BURIAL_GROUNDS},

	// MAP_A1_FORGOTTEN_TOWER					0x14
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_1},
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_1, 0x19, MAP_A1_TOWER_CELLAR_LEVEL_5},
	{0},
	{EXIT, MAP_A1_BLACK_MARSH},

	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_2}, //0x15
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_2, 0x19, MAP_A1_TOWER_CELLAR_LEVEL_5},
	{0},
	{EXIT, MAP_A1_FORGOTTEN_TOWER},

	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_3}, //0x16
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_3, 0x19, MAP_A1_TOWER_CELLAR_LEVEL_5},
	{0},
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_1},

	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_4}, //0x17
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_4, 0x19, MAP_A1_TOWER_CELLAR_LEVEL_5},
	{0},
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_2},

	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_5}, //0x18
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_5, 0x19, MAP_A1_TOWER_CELLAR_LEVEL_5},
	{0},
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_3},

	{UNIT_MONSTER, 740}, //0x19
	{UNIT_MONSTER, 740},
	{0},
	{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_4},

	{EXIT, MAP_A1_OUTER_CLOISTER}, //0x1a
	{EXIT, MAP_A1_OUTER_CLOISTER},
	{0},
	{EXIT, MAP_A1_TAMOE_HIGHLAND},

	{EXIT, MAP_A1_BARRACKS}, //0x1b
	{EXIT, MAP_A1_BARRACKS},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_MONASTERY_GATE},

	{EXIT, MAP_A1_JAIL_LEVEL_1}, //0x1c
	{UNIT_OBJECT, 108},
	{0},
	{EXIT, MAP_A1_OUTER_CLOISTER},

	{EXIT, MAP_A1_JAIL_LEVEL_2}, //0x1d
	{EXIT, MAP_A1_JAIL_LEVEL_2},
	{UNIT_OBJECT, 157},
	{EXIT, MAP_A1_BARRACKS},

	{EXIT, MAP_A1_JAIL_LEVEL_3}, //0x1e
	{EXIT, MAP_A1_JAIL_LEVEL_3},
	{0},
	{EXIT, MAP_A1_JAIL_LEVEL_1},

	{EXIT, MAP_A1_INNER_CLOISTER}, //0x1f
	{EXIT, MAP_A1_INNER_CLOISTER},
	{0},
	{EXIT, MAP_A1_JAIL_LEVEL_2},

	{EXIT, MAP_A1_CATHEDRAL}, //0x20
	{EXIT, MAP_A1_CATHEDRAL},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_JAIL_LEVEL_3},

	{EXIT, MAP_A1_CATACOMBS_LEVEL_1}, //0x21
	{EXIT, MAP_A1_CATACOMBS_LEVEL_1, 0x25, MAP_A1_CATACOMBS_LEVEL_4},
	{0},
	{EXIT, MAP_A1_INNER_CLOISTER},

	{EXIT, MAP_A1_CATACOMBS_LEVEL_2}, //0x22
	{EXIT, MAP_A1_CATACOMBS_LEVEL_2, 0x25, MAP_A1_CATACOMBS_LEVEL_4},
	{0},
	{EXIT, MAP_A1_CATHEDRAL},

	{EXIT, MAP_A1_CATACOMBS_LEVEL_3}, //0x23
	{EXIT, MAP_A1_CATACOMBS_LEVEL_3, 0x25, MAP_A1_CATACOMBS_LEVEL_4},
	{UNIT_OBJECT, 157},
	{EXIT, MAP_A1_CATACOMBS_LEVEL_1},

	{EXIT, MAP_A1_CATACOMBS_LEVEL_4}, //0x24
	{EXIT, MAP_A1_CATACOMBS_LEVEL_4, 0x25, MAP_A1_CATACOMBS_LEVEL_4},
	{0},
	{EXIT, MAP_A1_CATACOMBS_LEVEL_2},

	{XY, 22533, 9556}, //0x25
	{XY, 22533, 9556},
	{0},
	{EXIT, MAP_A1_CATACOMBS_LEVEL_3},

	{UNIT_OBJECT, 268}, //0x26 -> tristram
	{UNIT_OBJECT, 268},
	{0},
	{XY, 25173, 5083},

	{0}, //0x27 -> cow lvl
	{0},
	{0},
	{0},

	////////////////////////////////////////////////////////////////////
	// Act 2
	////////////////////////////////////////////////////////////////////

	{0}, //0x28 -> lut gholein
	{0},
	{0},
	{0},

	{EXIT, MAP_A2_DRY_HILLS}, //0x29
	{EXIT, MAP_A2_DRY_HILLS},
	{0},
	{EXIT, MAP_A2_LUT_GHOLEIN},

	{EXIT, MAP_A2_FAR_OASIS}, //0x2a
	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_1},
	{UNIT_OBJECT, 156},
	{EXIT, MAP_A2_ROCKY_WASTE},

	{EXIT, MAP_A2_LOST_CITY}, //0x2b
	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_1, 0x40, MAP_A2_MAGGOT_LAIR_LEVEL_3},
	{UNIT_OBJECT, 156},
	{EXIT, MAP_A2_DRY_HILLS},

	{EXIT, MAP_A2_VALLEY_OF_SNAKES}, //0x2c
	{EXIT, MAP_A2_ANCIENT_TUNNELS},
	{UNIT_OBJECT, 156},
	{EXIT, MAP_A2_FAR_OASIS},

	{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_1}, //0x2d
	{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_1},
	{0},
	{EXIT, MAP_A2_LOST_CITY},

	{0}, //0x2e -> canyon of the magi
	{0},
	{UNIT_OBJECT, 402},
	{UNIT_OBJECT, 402}, //EXIT, GetLevel(MAP_A2_CANYON_OF_THE_MAGI)->pMisc->dwStaffTombLevel

	{EXIT, MAP_A2_SEWERS_LEVEL_2}, //0x2f
	{EXIT, MAP_A2_SEWERS_LEVEL_2},
	{0},
	{EXIT, MAP_A2_LUT_GHOLEIN},

	{EXIT, MAP_A2_SEWERS_LEVEL_3}, //0x30
	{EXIT, MAP_A2_SEWERS_LEVEL_3},
	{UNIT_OBJECT, 323},
	{EXIT, MAP_A2_SEWERS_LEVEL_1},

	{UNIT_OBJECT, 355}, //0x31
	{UNIT_OBJECT, 355},
	{0},
	{EXIT, MAP_A2_SEWERS_LEVEL_2},

	{UNIT_TILE, 29}, //0x32
	{UNIT_TILE, 29},
	{0},
	{EXIT, MAP_A2_LUT_GHOLEIN},

	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_1}, //0x33
	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_1},
	{0},
	{EXIT, MAP_A2_HAREM_LEVEL_1},

	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_2}, //0x34
	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_2},
	{UNIT_OBJECT, 288},
	{EXIT, MAP_A2_HAREM_LEVEL_2},

	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_3}, //0x35
	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_3},
	{0},
	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_1},

	{UNIT_OBJECT, 298}, //0x36
	{UNIT_OBJECT, 298},
	{0},
	{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_2},

	{0},
	{0},
	{0},
	{0}, //0x37 -> stony tomb

	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_2}, //0x38
	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_2},
	{0},
	{EXIT, MAP_A2_DRY_HILLS},

	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_3}, //0x39
	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_3},
	{UNIT_OBJECT, 156},
	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_1},

	{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_2}, //0x3a
	{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_2},
	{0},
	{EXIT, MAP_A2_VALLEY_OF_SNAKES},

	{0},
	{0},
	{0},
	{0}, //0x3b -> stony tomb lvl 2

	{UNIT_OBJECT, 354}, //0x3c
	{UNIT_OBJECT, 354},
	{0},
	{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_2},

	{UNIT_OBJECT, 149}, //0x3d
	{UNIT_OBJECT, 149},
	{0},
	{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_2},

	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_2}, //0x3e
	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_2, 0x40, MAP_A2_MAGGOT_LAIR_LEVEL_3},
	{0},
	{EXIT, MAP_A2_FAR_OASIS},

	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_3}, //0x3f
	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_3, 0x40, MAP_A2_MAGGOT_LAIR_LEVEL_3},
	{0},
	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_1},

	{UNIT_OBJECT, 356}, //0x40
	{UNIT_OBJECT, 356},
	{0},
	{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_2},

	{UNIT_OBJECT, 397}, //0x41 ancient tunnels
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A2_LOST_CITY},

	{UNIT_OBJECT, 152}, //0x42
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	{UNIT_OBJECT, 152}, //0x43
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	{UNIT_OBJECT, 152}, //0x44
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	{UNIT_OBJECT, 152}, //0x45
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	{UNIT_OBJECT, 152}, //0x46
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	{UNIT_OBJECT, 152}, //0x47
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	{UNIT_OBJECT, 152}, //0x48
	{UNIT_OBJECT, 152},
	{0},
	{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	{0},
	{0},
	{0},
	{0}, //0x49 -> tal chamber

	{UNIT_OBJECT, 357}, //0x4a
	{UNIT_OBJECT, 357},
	{UNIT_OBJECT, 402},
	{UNIT_OBJECT, 298},

	////////////////////////////////////////////////////////////////////
	// Act 3
	////////////////////////////////////////////////////////////////////

	{0},
	{0},
	{0},
	{0}, //0x4b -> kurast docks

	{EXIT, MAP_A3_GREAT_MARSH}, //0x4c
	{EXIT, MAP_A3_SPIDER_CAVERN},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_KURAST_DOCKS},

	{EXIT, MAP_A3_FLAYER_JUNGLE}, //0x4d
	{EXIT, MAP_A3_FLAYER_JUNGLE},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_SPIDER_FOREST},

	{EXIT, MAP_A3_LOWER_KURAST}, //0x4e
	{UNIT_OBJECT, 252},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_GREAT_MARSH},

	{EXIT, MAP_A3_KURAST_BAZAAR}, //0x4f
	{EXIT, MAP_A3_KURAST_BAZAAR},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_FLAYER_JUNGLE},

	{EXIT, MAP_A3_UPPER_KURAST}, //0x50
	{EXIT, MAP_A3_RUINED_TEMPLE},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_LOWER_KURAST},

	{EXIT, MAP_A3_KURAST_CAUSEWAY}, //0x51
	{EXIT, MAP_A3_KURAST_CAUSEWAY},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_KURAST_BAZAAR},

	{EXIT, MAP_A3_TRAVINCAL}, //0x52
	{EXIT, MAP_A3_TRAVINCAL},
	{0},
	{EXIT, MAP_A3_UPPER_KURAST},

	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_1}, //0x53
	{UNIT_OBJECT, 404},						//4531, 1810},
	{UNIT_OBJECT, 237},
	{EXIT, MAP_A3_KURAST_CAUSEWAY},

	{0},
	{0},
	{0},
	{0}, //0x54 -> arachnid lair
	{0},
	{0},
	{0},
	{0}, //0x55 -> spider cavern
	{0},
	{0},
	{0},
	{0}, //0x56 -> swampy pit lvl 1
	{0},
	{0},
	{0},
	{0}, //0x57 -> swampy pit lvl 2
	{0},
	{0},
	{0},
	{0}, //0x58 -> flayer dungeon lvl 1
	{0},
	{0},
	{0},
	{0}, //0x59 -> flayer dungeon lvl 2
	{0},
	{0},
	{0},
	{0}, //0x5a -> swampy pit lvl 3
	{0},
	{0},
	{0},
	{0}, //0x5b -> flayer dungeon lvl 3
	{0},
	{0},
	{0},
	{0}, //0x5c -> sewer lvl 1
	{0},
	{0},
	{0},
	{0}, //0x5d -> sewer lvl 2
	{0},
	{0},
	{0},
	{0}, //0x5e -> ruined temple
	{0},
	{0},
	{0},
	{0}, //0x5f -> disused fane
	{0},
	{0},
	{0},
	{0}, //0x60 -> forgotten reliquary
	{0},
	{0},
	{0},
	{0}, //0x61 -> forgotton temple
	{0},
	{0},
	{0},
	{0}, //0x62 -> ruined fane
	{0},
	{0},
	{0},
	{0}, //0x63 -> disused reliquary

	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_2}, //0x64
	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_2, 0x66, MAP_A3_DURANCE_OF_HATE_LEVEL_3},
	{0},
	{EXIT, MAP_A3_TRAVINCAL},

	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_3}, //0x65
	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_3, 0x66, MAP_A3_DURANCE_OF_HATE_LEVEL_3},
	{UNIT_OBJECT, 324},
	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_1},

	{XY, 17591, 8069}, //0x66
	{XY, 17591, 8069},
	{0},
	{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_2},

	////////////////////////////////////////////////////////////////////
	// Act 4
	////////////////////////////////////////////////////////////////////

	{0},
	{0},
	{0},
	{0}, //0x67 pandemonium fortress

	{EXIT, MAP_A4_PLAINS_OF_DESPAIR}, //0x68
	{EXIT, MAP_A4_PLAINS_OF_DESPAIR},
	{0},
	{EXIT, MAP_A4_THE_PANDEMONIUM_FORTRESS},

	{EXIT, MAP_A4_CITY_OF_THE_DAMNED}, //0x69
	{UNIT_MONSTER, 256},
	{UNIT_OBJECT, 238},
	{EXIT, MAP_A4_OUTER_STEPPES},

	{EXIT, MAP_A4_RIVER_OF_FLAME}, //0x6a
	{EXIT, MAP_A4_RIVER_OF_FLAME, 0x6c, MAP_A4_THE_CHAOS_SANCTUARY},
	{UNIT_OBJECT, 238},
	{EXIT, MAP_A4_PLAINS_OF_DESPAIR},

	{EXIT, MAP_A4_THE_CHAOS_SANCTUARY, 0x6c, MAP_A4_THE_CHAOS_SANCTUARY}, //0x6b
	{UNIT_OBJECT, 376},
	{UNIT_OBJECT, 238},
	{EXIT, MAP_A4_CITY_OF_THE_DAMNED},

	{UNIT_OBJECT, 255}, //0x6c
	{UNIT_OBJECT, 255},
	{0},
	{EXIT, MAP_A4_RIVER_OF_FLAME},

	////////////////////////////////////////////////////////////////////
	// Act 5
	////////////////////////////////////////////////////////////////////

	{0},
	{0},
	{0},
	{0}, //0x6d

	{EXIT, MAP_A5_FRIGID_HIGHLANDS}, //0x6e
	{UNIT_MONSTER, 776},
	{0},
	{EXIT, MAP_A5_HARROGATH},

	{EXIT, MAP_A5_ARREAT_PLATEAU}, //0x6f
	{EXIT, MAP_A5_ARREAT_PLATEAU},
	{UNIT_OBJECT, 496},
	{EXIT, MAP_A5_THE_BLOODY_FOOTHILLS},

	{EXIT, MAP_A5_CRYSTALLINE_PASSAGE}, //0x70
	{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},
	{UNIT_OBJECT, 496},
	{EXIT, MAP_A5_FRIGID_HIGHLANDS},

	{EXIT, MAP_A5_GLACIAL_TRAIL}, //0x71
	{EXIT, MAP_A5_FROZEN_RIVER, 0x72, MAP_A5_FROZEN_RIVER},
	{UNIT_OBJECT, 511},
	{EXIT, MAP_A5_ARREAT_PLATEAU},

	{UNIT_OBJECT, 460}, //0x72
	{UNIT_OBJECT, 460},
	{0},
	{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},

	{EXIT, MAP_A5_FROZEN_TUNDRA}, //0x73
	{EXIT, MAP_A5_FROZEN_TUNDRA},
	{UNIT_OBJECT, 511},
	{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},

	{0},
	{0},
	{0},
	{0}, //0x74 -> drifter cavern

	{EXIT, MAP_A5_THE_ANCIENTS_WAY}, //0x75
	{EXIT, MAP_A5_THE_ANCIENTS_WAY},
	{UNIT_OBJECT, 496},
	{EXIT, MAP_A5_ARREAT_PLATEAU},

	{EXIT, MAP_A5_ARREAT_SUMMIT}, //0x76
	{EXIT, MAP_A5_ARREAT_SUMMIT},
	{UNIT_OBJECT, 511},
	{EXIT, MAP_A5_FROZEN_TUNDRA},

	{0},
	{0},
	{0},
	{0}, //0x77 -> icy cellar

	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_1}, //0x78
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_1, 0x83, MAP_A5_THRONE_OF_DESTRUCTION},
	{0},
	{EXIT, MAP_A5_THE_ANCIENTS_WAY},

	{EXIT, MAP_A5_HALLS_OF_ANGUISH}, //0x79
	{EXIT, MAP_A5_HALLS_OF_ANGUISH, 0x7c, MAP_A5_HALLS_OF_VAUGHT},
	{0},
	{0},

	{EXIT, MAP_A5_HALLS_OF_PAIN}, //0x7a
	{EXIT, MAP_A5_HALLS_OF_PAIN, 0x7c, MAP_A5_HALLS_OF_VAUGHT},
	{0},
	{EXIT, MAP_A5_NIHLATHAKS_TEMPLE},

	{EXIT, MAP_A5_HALLS_OF_VAUGHT}, //0x7b
	{EXIT, MAP_A5_HALLS_OF_VAUGHT, 0x7c, MAP_A5_HALLS_OF_VAUGHT},
	{UNIT_OBJECT, 496},
	{EXIT, MAP_A5_HALLS_OF_ANGUISH},

	{UNIT_OBJECT, 462}, //0x7c
	{UNIT_OBJECT, 462},
	{0},
	{EXIT, MAP_A5_HALLS_OF_PAIN},

	{0},
	{0},
	{0},
	{0}, //0x7d -> abaddon
	{0},
	{0},
	{0},
	{0}, //0x7e -> pit of acheron
	{0},
	{0},
	{0},
	{0}, //0x7f -> infernal pit

	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_2}, //0x80
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_2, 0x83, MAP_A5_THRONE_OF_DESTRUCTION},
	{0},
	{EXIT, MAP_A5_ARREAT_PLATEAU},

	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_3}, //0x81
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_3, 0x83, MAP_A5_THRONE_OF_DESTRUCTION},
	{UNIT_OBJECT, 494},
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_1},

	{EXIT, MAP_A5_THRONE_OF_DESTRUCTION}, //0x82
	{EXIT, MAP_A5_THRONE_OF_DESTRUCTION, 0x83, MAP_A5_THRONE_OF_DESTRUCTION},
	{0},
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_2},

	{XY, 15114, 5069}, //0x83
	{XY, 15091, 5006},
	{0},
	{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_3},

	{0},
	{0},
	{0},
	{0}, //0x84 -> worldstone keep

	{UNIT_OBJECT, 397}, //0x85
	{UNIT_OBJECT, 397},
	{0},
	{0},

	{0},
	{0},
	{0},
	{0}, //0x86 -> forgotton sands

	{UNIT_OBJECT, 397}, //0x87
	{UNIT_OBJECT, 397},
	{0},
	{0}};

DWORD GetUnitByXY(DWORD X, DWORD Y, Room2 *pRoom)
{
	UnitAny *pUnit;

	if (!VALIDPTR(pRoom))
		return 1;

	if (!VALIDPTR(pRoom->pRoom1))
		return 2;

	if (!VALIDPTR(pRoom->pRoom1->pUnitFirst))
		return 3;

	pUnit = pRoom->pRoom1->pUnitFirst;

	if (!VALIDPTR(pUnit))
		return 4;

	if (!VALIDPTR(pUnit->pObjectPath))
		return 5;

	while (pUnit)
	{
		if (pUnit->dwType != UNIT_PLAYER)
		{
			//PrintText(FONTCOLOR_GREY, "pUnit  x:%d   y:%d   dwUnitId: %d", pUnit->pObjectPath->dwPosX, pUnit->pObjectPath->dwPosY, pUnit->dwUnitId);
			if (X == pUnit->pObjectPath->dwPosX)
				if (Y == pUnit->pObjectPath->dwPosY)
					return pUnit->dwUnitId;
		}
		pUnit = pUnit->pListNext;
	}
	return 6;
}

// 0x88

void wait_for_load(DWORD area)
{
	// PrintText(FONTCOLOR_WHITE, "Entered wait_for_load");
	while (!GameReady())
		Sleep(30);

	while (GetPlayerArea() != area)
		Sleep(30);

	// PrintText(FONTCOLOR_WHITE, "Left wait_for_load");
}

bool TelePath(POINT *tPath, DWORD dwCount, DWORD InteractType, Room2 *InteractRoom)
{
	DWORD Time = 0;
	DWORD Try = 0;
	DWORD cur = 0;

	if (cDrawHook)
		for (DWORD i = 0; i < dwCount; i++)
			DrawPath.Add(tPath[i], 1);

	if (GameReady())
	{
		if (!SetSkill(D2S_TELEPORT, 0))
		{
			PrintText(FONTCOLOR_RED, "AutoTele: Failed to set teleport!");
			return 1;
		}

		for (int i = 0; i < 25; i++)
		{
			if (GameReady() && D2CLIENT_GetPlayerUnit())
			{
				if (D2CLIENT_GetPlayerUnit()->pInfo->pRightSkill->pSkillInfo->wSkillId == D2S_TELEPORT)
					break;
				else if (i > 23)
				{
					PrintText(FONTCOLOR_RED, "AutoTele: Failed to set teleport skill. Ping: %d", D2CLIENT_Ping);
					return 1;
				}
			}
			else
			{

				return 1;
			}
			Sleep(40);
		}

		while (cur < dwCount && GameReady())
		{
			if (Time == 0)
			{
				if (!TeleOnMap(static_cast<WORD>(tPath[cur].x), static_cast<WORD>(tPath[cur].y), false))
				{
					return 1;
				}
			}
			else if (Time >= 50)
			{
				Time = 0;
				if (Try >= 5)
				{
					PrintText(FONTCOLOR_RED, "�c4AutoTele:�c1 Failed to teleport after 5 tries");
					return false;
				}
				else
				{
					Try++;
					continue;
				}
			}

			if (GameReady())
			{
				if (GetDistanceSquared(D2CLIENT_GetUnitX(D2CLIENT_PlayerUnit), D2CLIENT_GetUnitY(D2CLIENT_PlayerUnit), tPath[cur].x, tPath[cur].y) <= 5)
				{
					DrawPath.RemoveAt(0, 1);
					cur++;
					Time = 0;
					continue;
				}
				else
				{
					Time++;
					Sleep(10);
				}
			}
		}

		if (InteractRoom)
		{
			Sleep(100);
			//PrintText(FONTCOLOR_GREY, "Interacting with %d %d  UnitId: %d  InteractRoom: %x", p.y, p.y, UnitId, p.InteractRoom);
			Interact(GetUnitByXY(tPath[dwCount - 1].x, tPath[dwCount - 1].y, InteractRoom), InteractType);
		}
	}

	return 0;
}

int MakePath(int x, int y, DWORD current_area, bool MoveThrough, DWORD InteractType, Room2 *InteractRoom)
{
	CCollisionMap g_collisionMap; //init the collisionmap
	DWORD dwCount;
	POINT tPath[255];

	if (!g_collisionMap.CreateMap(current_area))
	{
		debug("MakePath: CreateMap failed");
		return false;
	}

	POINT ptStart = {D2CLIENT_GetPlayerUnit()->pPath->xPos, D2CLIENT_GetPlayerUnit()->pPath->yPos};
	POINT ptEnd = {x, y};

	if (!g_collisionMap.IsValidAbsLocation(ptStart.x, ptStart.y))
	{
		debug("MakePath: IsValidAbsLocation failed  ptStart.x:%d  ptStart.y: %d", ptStart.x, ptStart.y);
		return false;
	}

	if (!g_collisionMap.IsValidAbsLocation(ptEnd.x, ptEnd.y))
	{
		debug("MakePath: IsValidAbsLocation failed  ptEnd.x:%d  ptEnd.y: %d", ptEnd.x, ptEnd.y);
		return false;
	}

	g_collisionMap.AbsToRelative(ptStart);
	g_collisionMap.AbsToRelative(ptEnd);

	WordMatrix matrix;

	if (!g_collisionMap.CopyMapData(matrix))
	{
		debug("MakePath: CopyMapData failed");
		return false;
	}

	CTeleportPath tf(matrix.GetData(), matrix.GetCX(), matrix.GetCY());
	dwCount = tf.FindTeleportPath(ptStart, ptEnd, tPath, 255);

	if (dwCount == 0)
	{
		debug("MakePath: dwCount == 0, bailing out");
		return false;
	}

	for (DWORD i = 0; i < dwCount; i++)
	{
		g_collisionMap.RelativeToAbs(tPath[i]);
	}

	if (MoveThrough)
	{
		if (tPath[dwCount - 1].x > tPath[dwCount - 2].x)
			tPath[dwCount].x = tPath[dwCount - 1].x + 2;
		else
			tPath[dwCount].x = tPath[dwCount - 1].x - 2;
		if (tPath[dwCount - 1].y > tPath[dwCount - 2].y)
			tPath[dwCount].y = tPath[dwCount - 1].y + 2;
		else
			tPath[dwCount].y = tPath[dwCount - 1].y - 2;

		dwCount++;

		if (GetDistanceSquared(tPath[dwCount - 1].x, tPath[dwCount - 1].y, tPath[dwCount - 3].x, tPath[dwCount - 3].y) <= 30)
		{
			tPath[dwCount - 2] = tPath[dwCount - 1];
			tPath[dwCount - 1].x = 0;
			tPath[dwCount - 1].y = 0;
			dwCount--;
		}
	}

	TelePath(tPath, dwCount, InteractType, InteractRoom);
	if (DrawPath.GetSize())
		DrawPath.RemoveAll();

	return dwCount;
}

void MakePathExit(Vector T)
{
	DWORD InteractType = -1;
	Room2 *InteractRoom = NULL;
	bool is_chain = false;
	DWORD chain_size = 0;
	DWORD chain_cur = 0;

	if (T.Area && T.Id != T.Area)
	{ // CONTINUAR COM CASO O PROX ANDAR JAH SEJA IGUAL O ULTIMO ANDAR DO CHAIN
		if (T.Id > T.Area)
		{
			PrintText(FONTCOLOR_RED, "Path chaining is not possible: T.Id %d   T.Area %x", T.Id, T.Area);
			return;
		}
		is_chain = true;
		chain_size = T.Area - T.Id;
	}

	do
	{
		// PrintText(FONTCOLOR_WHITE, "Path chaining - cur: %d/%d   LastArea: %x", chain_cur, chain_size, T.Area);
		DWORD current_area = GetPlayerArea();
		CCollisionMap g_collisionMap; //init the collisionmap
		LPLevelExit ExitArray[0x40];  //declare an array of exits to store the exits in later

		if (!g_collisionMap.CreateMap(current_area)) //create a cmap for the current area
		{
			PrintText(FONTCOLOR_RED, "createmap failed");
			return;
		}

		int ExitCount = g_collisionMap.GetLevelExits(ExitArray); //getlevelexits returns the exitcount

		if (!ExitCount)
		{ //if there are 0 tele positions we can stop here :p
			//PrintText(FONTCOLOR_GOLD, "Saindo pq ExitCount = 0");
			return;
		}

		for (int i = 0; i < ExitCount; i++) //loop over evey exit to see if it matches our target
		{
			//char buffer2[64];
			//sprintf(buffer2, "targetlvl: %x, %d, %d", ExitArray[i]->dwTargetLevel, ExitArray[i]->ptPos.x, ExitArray[i]->ptPos.y);
			//PrintText(buffer2, 4);
			//PrintText(FONTCOLOR_RED, "Comparing dwTargetLevel(%x) and T.Id+cur(%x)", ExitArray[i]->dwTargetLevel, (T.Id + chain_cur));
			if (ExitArray[i]->dwTargetLevel == (T.Id + chain_cur))
			{
				//PrintText(FONTCOLOR_WHITE, "ACHOU");
				LevelTxt *lvltxt = D2COMMON_GetLevelTxt(T.Id + chain_cur);
				PrintText(FONTCOLOR_GREY, "AutoTele: Going to %s", lvltxt->szName);
				if (ExitArray[i]->dwType == EXIT_TILE)
				{
					InteractType = UNIT_TILE;
					InteractRoom = ExitArray[i]->pRoom;
					//PrintText(FONTCOLOR_RED, "UPDATING Interact from MakePath: %d %x", InteractType, InteractRoom);
				}

				MakePath(ExitArray[i]->ptPos.x, ExitArray[i]->ptPos.y, current_area, ExitArray[i]->dwType == EXIT_LEVEL ? 1 : 0, InteractType, InteractRoom);
				break;
			}
			else
			{
				LevelTxt *lvltxt = D2COMMON_GetLevelTxt(ExitArray[i]->dwTargetLevel);
				//PrintText(FONTCOLOR_RED, "Achei saida para %s(%d)", lvltxt->szName, ExitArray[i]->dwTargetLevel);
			}
		}

		wait_for_load(T.Id + chain_cur);
		chain_cur++;
	} while (is_chain && chain_cur <= chain_size);

	// Check if there is a monster/object to teleport to
	if (T.Id2)
	{
		Vector obj = vVector[T.Id2 * 4];
		if (obj.dwType == XY)
			MakePath(obj.Id, obj.Id2, GetPlayerArea(), false, -1, NULL);
		else
			MakePathObject(obj.dwType, obj.Id, obj.Id2, GetPlayerArea());
	}

	return;
}

void MakePathObject(DWORD dwType, DWORD dwTxtFileNo, DWORD dwTxtFileNo2, DWORD Area)
{
	DWORD InteractType = -1;
	Room2 *InteractRoom = NULL;
	Level *pLevel = GetLevel(Area);
	POINT pUnit2;

	// PrintText(FONTCOLOR_WHITE, "MakePathObject: dwType %d   dwTxtFileNo %d   dwTxtFileNo2 %d   Area %x", dwType, dwTxtFileNo, dwTxtFileNo2, Area);

	pUnit2.x = 0;
	pUnit2.y = 0;

	if (!VALIDPTR(pLevel))
		return;

	bool bAddedRoom = false;
	bool stoploop = false;
	for (Room2 *pRoom = pLevel->pRoom2First; pRoom; pRoom = pRoom->pRoom2Next)
	{
		bAddedRoom = false;
		if (!VALIDPTR(pRoom->pPreset) && !VALIDPTR(pRoom->pRoomTiles) && !VALIDPTR(pRoom->pRoom1))
		{
			D2COMMON_AddRoomData(D2CLIENT_GetPlayerUnit()->pAct, pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, D2CLIENT_GetPlayerUnit()->pPath->pRoom1);
			bAddedRoom = true;
		}

		for (PresetUnit *pUnit = pRoom->pPreset; pUnit; pUnit = pUnit->pPresetNext)
		{
			//PrintText(FONTCOLOR_WHITE, "X: %d, Y: %d, TxtFileNo: %d, Type: %d", pUnit->dwPosX, pUnit->dwPosY, pUnit->dwTxtFileNo, pUnit->dwType);
			if (((dwType == NULL) || (dwType == pUnit->dwType)) && (dwTxtFileNo == pUnit->dwTxtFileNo))
			{
				if (dwType == UNIT_TILE || (dwType == UNIT_OBJECT && dwTxtFileNo == 298))
				{
					InteractRoom = pRoom;
					InteractType = dwType;
				}

				if (dwType == UNIT_OBJECT)
				{
					for (int i = 0; i <= ArraySize(waypoints); i++)
					{
						if (waypoints[i] == dwTxtFileNo)
						{
							InteractRoom = pRoom;
							InteractType = dwType;
							stoploop = 1; //stop looping over the rooms
							break;
						}
					}
				}

				pUnit2.x = (pUnit->dwPosX) + (pRoom->dwPosX * 5);
				pUnit2.y = (pUnit->dwPosY) + (pRoom->dwPosY * 5);

				if (dwType == UNIT_OBJECT)
				{
					ObjectTxt *ObjTxt = D2COMMON_GetObjectTxt(dwTxtFileNo);
					PrintText(FONTCOLOR_GREY, "AutoTele: Going to %s", ObjTxt->szName);
				}

				stoploop = 1; //stop looping over the rooms
				break;
			}
		}

		if (bAddedRoom)
		{
			D2COMMON_RemoveRoomData(D2CLIENT_GetPlayerUnit()->pAct, pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, D2CLIENT_GetPlayerUnit()->pPath->pRoom1);
			bAddedRoom = false;
		}
		if (stoploop)
		{
			stoploop = 0;
			break;
		}
	}

	if (pUnit2.x != 0 && pUnit2.y != 0)
		MakePath(pUnit2.x, pUnit2.y, Area, false, InteractType, InteractRoom);
	else
		PrintText(FONTCOLOR_RED, "AutoTele: Can't find object/monster");

	return;
}

/*
T.Id
0-5 = units
6 = exit
7 = x/y
Id is lvl id or dwtxtfileno or x
Id2 can be left 0, if its another value the func will use EITHER id.
Id2 cannot be 0 if type is x/y
*/
DWORD WINAPI ManageTeleThread(LPVOID P)
{
	Vector T = vVector[(DWORD)P];
	DWORD CurArea;

	// PrintText(FONTCOLOR_WHITE, "ManageTele: T. Type[%d]  Id[0x%x]  Id2[%d]  Area[%x]", T.dwType, T.Id, T.Id2, T.Area);

	if (T.Area)
	{
		// PrintText(FONTCOLOR_WHITE, "ManageTele: T.Area[%x] was set for T.Id: %x", T.Area, T.Id);
		//Areas[1] = T.Area;
		//AreaCount = 2;
	}

	CurArea = GetPlayerArea();
	if (CurArea == MAP_A2_CANYON_OF_THE_MAGI)
	{
		if (T.dwType == 0 && T.Id == 0)
		{
			T.dwType = EXIT;
			T.Id = GetLevel(MAP_A2_CANYON_OF_THE_MAGI)->pMisc->dwStaffTombLevel;
			T.Id2 = T.Id;
		}
	}
	else if (CurArea == MAP_A1_COLD_PLAINS)
	{
		if (cColdToCave)
			if (T.Id == MAP_A1_BURIAL_GROUNDS)
				T.Id = MAP_A1_CAVE_LEVEL_1;
	}

	if (!T.Id)
	{
		PrintText(FONTCOLOR_RED, "AutoTele: Invalid destination!");
		return 1;
	}

	if (T.dwType == EXIT)
	{
		MakePathExit(T);
		return 0;
	}

	if (T.dwType == XY)
	{
		if (!T.Id || !T.Id2)
		{
			PrintText(FONTCOLOR_RED, "AutoTele: No X/Y value found");
			return 1;
		}
		MakePath(T.Id, T.Id2, CurArea, false, -1, NULL); /*)*/

		return 0;
	}

	// Tele to Monster/Object
	MakePathObject(T.dwType, T.Id, T.Id2, T.Area ? T.Area : CurArea);

	return 0;
}