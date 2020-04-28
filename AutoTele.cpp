#include "injection.h"
DWORD dwCount;
POINT pu;
void DoTele(int VECTOR);
bool DoInteract = 0;
DWORD InteractType;
Room2* InteractRoom = {0};
HANDLE TELEHANDLE;
HANDLE hStopEvent;
CArrayEx <POINT, POINT> Path;
POINT aPath[255];
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
int waypoints[] = {119,157,156,323,288,402,324,237,238,398,496,511,494};

Vector vVector[] = {
	{0}, {0}, {0}, {0},										//0x0
	{0}, {0}, {0}, {0},										//0x01

	{EXIT, MAP_A1_COLD_PLAINS}, 
	{EXIT, MAP_A1_DEN_OF_EVIL}, 
	{0}, 
	{EXIT, MAP_A1_ROGUE_ENCAMPMENT},						//0x02

	{EXIT, MAP_A1_STONY_FIELD},								//0x3
	{EXIT, MAP_A1_BURIAL_GROUNDS},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_BLOOD_MOOR},

	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1},
	{UNIT_OBJECT, 22},										//0x4
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_COLD_PLAINS},

	{EXIT, MAP_A1_BLACK_MARSH},								//0x5
	{UNIT_OBJECT, 30},										
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1},

	{EXIT, MAP_A1_TAMOE_HIGHLAND},							//0x6
	{EXIT, MAP_A1_FORGOTTEN_TOWER},
	{UNIT_OBJECT, 119},
	{EXIT, MAP_A1_DARK_WOOD},

	{EXIT, MAP_A1_MONASTERY_GATE},							//0x7
	{EXIT, MAP_A1_PIT_LEVEL_1},
	{0},
	{EXIT, MAP_A1_BLACK_MARSH},

	{0},													//0x08
	{0}, 
	{0}, 
	{EXIT, MAP_A1_BLOOD_MOOR},								

	{EXIT, MAP_A1_CAVE_LEVEL_2},							//0x9
	{UNIT_MONSTER, 736},
	{0},
	{EXIT, MAP_A1_COLD_PLAINS},

	{EXIT, MAP_A1_DARK_WOOD},								//0xa
	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_2},
	{UNIT_OBJECT, 157},
	{EXIT, MAP_A1_STONY_FIELD},

	{EXIT, MAP_A1_HOLE_LEVEL_2},							//0xb
	{EXIT, MAP_A1_HOLE_LEVEL_2},
	{0},
	{EXIT, MAP_A1_BLACK_MARSH},

	{EXIT, MAP_A1_PIT_LEVEL_2},								//0xc
	{EXIT, MAP_A1_PIT_LEVEL_2},
	{0},
	{EXIT, MAP_A1_TAMOE_HIGHLAND},

	{UNIT_OBJECT, 397},										//0xd
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_CAVE_LEVEL_1},

	{UNIT_OBJECT, 397},										//0xe
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_UNDERGROUND_PASSAGE_LEVEL_1},

	
	{UNIT_OBJECT, 397},										//0xf
	{UNIT_OBJECT, 397},
	{0},
	{EXIT, MAP_A1_HOLE_LEVEL_1},
				
		{UNIT_OBJECT, 397},										//0x10
		{UNIT_OBJECT, 397},
		{0},
		{EXIT, MAP_A1_PIT_LEVEL_1},

		{0}, {0}, {0}, {0},										//0x11
		{0}, {0}, {0}, {0},										//0x12
		{0}, {0}, {0}, {0},										//0x13

		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_1},					//0x14
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_1},
		{0},
		{EXIT, MAP_A1_BLACK_MARSH},

		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_2},					//0x15
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_2},
		{0},
		{EXIT, MAP_A1_FORGOTTEN_TOWER},

	
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_3},					//0x16
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_3},
		{0},
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_1},

	
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_4},					//0x17
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_4},
		{0},
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_2},

	
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_5},					//0x18
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_5},
		{0},
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_3},

	
		{UNIT_MONSTER, 740},									//0x19
		{UNIT_MONSTER, 740},
		{0},
		{EXIT, MAP_A1_TOWER_CELLAR_LEVEL_4},
							
		{EXIT, MAP_A1_OUTER_CLOISTER},							//0x1a
		{EXIT, MAP_A1_OUTER_CLOISTER},
		{0},
		{EXIT, MAP_A1_TAMOE_HIGHLAND},

	
		{EXIT, MAP_A1_BARRACKS},						//0x1b
		{EXIT, MAP_A1_BARRACKS},
		{UNIT_OBJECT, 119},
		{EXIT, MAP_A1_MONASTERY_GATE},

	
		{EXIT, MAP_A1_JAIL_LEVEL_1},							//0x1c
		{UNIT_OBJECT, 108},
		{0},
		{EXIT, MAP_A1_OUTER_CLOISTER},

	
		{EXIT, MAP_A1_JAIL_LEVEL_2},							//0x1d
		{EXIT, MAP_A1_JAIL_LEVEL_2},
		{UNIT_OBJECT, 157},
		{EXIT, MAP_A1_BARRACKS},

	
		{EXIT, MAP_A1_JAIL_LEVEL_3},							//0x1e
		{EXIT, MAP_A1_JAIL_LEVEL_3},
		{0},
		{EXIT, MAP_A1_JAIL_LEVEL_1},

	
		{EXIT, MAP_A1_INNER_CLOISTER},							//0x1f
		{EXIT, MAP_A1_INNER_CLOISTER},
		{0},
		{EXIT, MAP_A1_JAIL_LEVEL_2},

	
		{EXIT, MAP_A1_CATHEDRAL},								//0x20
		{EXIT, MAP_A1_CATHEDRAL},
		{UNIT_OBJECT, 119},
		{EXIT, MAP_A1_JAIL_LEVEL_3},

	
		{EXIT, MAP_A1_CATACOMBS_LEVEL_1},						//0x21
		{EXIT, MAP_A1_CATACOMBS_LEVEL_1},
		{0},
		{EXIT, MAP_A1_INNER_CLOISTER},

	
		{EXIT, MAP_A1_CATACOMBS_LEVEL_2},						//0x22
		{EXIT, MAP_A1_CATACOMBS_LEVEL_2},
		{0},
		{EXIT, MAP_A1_CATHEDRAL},

	
		{EXIT, MAP_A1_CATACOMBS_LEVEL_3},						//0x23
		{EXIT, MAP_A1_CATACOMBS_LEVEL_3},
		{UNIT_OBJECT, 157},
		{EXIT, MAP_A1_CATACOMBS_LEVEL_1},

	
		{EXIT, MAP_A1_CATACOMBS_LEVEL_4},						//0x24
		{EXIT, MAP_A1_CATACOMBS_LEVEL_4},
		{0},
		{EXIT, MAP_A1_CATACOMBS_LEVEL_2},

	
		{XY, 22533, 9556},										//0x25
		{XY, 22533, 9556},
		{0},
		{EXIT, MAP_A1_CATACOMBS_LEVEL_3},

		{0}, {0}, {0}, {0},										//0x26 -> tristram
		{0}, {0}, {0}, {0},										//0x27 -> cow lvl


	////////////////////////////////////////////////////////////////////
	// Act 2
	////////////////////////////////////////////////////////////////////

		{0}, {0}, {0}, {0},										//0x28 -> lut gholein

		{EXIT, MAP_A2_DRY_HILLS},								//0x29
		{EXIT, MAP_A2_DRY_HILLS},
		{0},
		{EXIT, MAP_A2_LUT_GHOLEIN},

		{EXIT, MAP_A2_FAR_OASIS},								//0x2a
		{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_1},
		{UNIT_OBJECT, 156},
		{EXIT, MAP_A2_ROCKY_WASTE},

		{EXIT, MAP_A2_LOST_CITY},								//0x2b
		{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_1},
		{UNIT_OBJECT, 156},
		{EXIT, MAP_A2_DRY_HILLS},

		{EXIT, MAP_A2_VALLEY_OF_SNAKES},						//0x2c
		{EXIT, MAP_A2_ANCIENT_TUNNELS},
		{UNIT_OBJECT, 156},
		{EXIT, MAP_A2_FAR_OASIS},

		{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_1},				//0x2d
		{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_1},
		{0},
		{EXIT, MAP_A2_LOST_CITY},

		{0},													//0x2e -> canyon of the magi
		{0},
		{UNIT_OBJECT, 402},										
		{UNIT_OBJECT, 402},//EXIT, GetLevel(MAP_A2_CANYON_OF_THE_MAGI)->pMisc->dwStaffTombLevel


		{EXIT, MAP_A2_SEWERS_LEVEL_2},							//0x2f
		{EXIT, MAP_A2_SEWERS_LEVEL_2},
		{0},
		{EXIT, MAP_A2_LUT_GHOLEIN},

		{EXIT, MAP_A2_SEWERS_LEVEL_3},							//0x30
		{EXIT, MAP_A2_SEWERS_LEVEL_3},
		{UNIT_OBJECT, 323},
		{EXIT, MAP_A2_SEWERS_LEVEL_1},
	
		{UNIT_OBJECT, 355},										//0x31
		{UNIT_OBJECT, 355},
		{0},
		{EXIT, MAP_A2_SEWERS_LEVEL_2},
	
		{UNIT_TILE, 29},										//0x32
		{UNIT_TILE, 29},
		{0},
		{EXIT, MAP_A2_LUT_GHOLEIN},
	
		{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_1},					//0x33
		{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_1},
		{0},
		{EXIT, MAP_A2_HAREM_LEVEL_1},
	
		{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_2},					//0x34
		{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_2},
		{UNIT_OBJECT, 288},
		{EXIT, MAP_A2_HAREM_LEVEL_2},
	
		{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_3},					//0x35
		{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_3},
		{0},
		{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_1},
	
		{UNIT_OBJECT, 298},										//0x36
		{UNIT_OBJECT, 298},
		{0},
		{EXIT, MAP_A2_PALACE_CELLAR_LEVEL_2},

		{0}, {0}, {0}, {0},										//0x37 -> stony tomb
		
		{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_2},				//0x38
		{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_2},
		{0},
		{EXIT, MAP_A2_DRY_HILLS},
					
		{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_3},				//0x39
		{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_3},
		{UNIT_OBJECT, 156},
		{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_1},

		{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_2},				//0x3a
		{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_2},
		{0},
		{EXIT, MAP_A2_VALLEY_OF_SNAKES},

		{0}, {0}, {0}, {0},										//0x3b -> stony tomb lvl 2

		{UNIT_OBJECT, 354},										//0x3c
		{UNIT_OBJECT, 354},
		{0},
		{EXIT, MAP_A2_HALLS_OF_THE_DEAD_LEVEL_2},

		{UNIT_OBJECT, 149},										//0x3d
		{UNIT_OBJECT, 149},
		{0},
		{EXIT, MAP_A2_CLAW_VIPER_TEMPLE_LEVEL_2},
	
		{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_2},						//0x3e
		{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_2},
		{0},
		{EXIT, MAP_A2_FAR_OASIS},
	
		{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_3},						//0x3f
		{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_3},
		{0},
		{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_1},
	
		{UNIT_OBJECT, 356},										//0x40
		{UNIT_OBJECT, 356},
		{0},
		{EXIT, MAP_A2_MAGGOT_LAIR_LEVEL_2},
	
		{0}, {0}, {0}, {0},										//0x41 ancient tunnels
	
		{UNIT_OBJECT, 152},										//0x42
		{UNIT_OBJECT, 152},
		{0},
		{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	
		{UNIT_OBJECT, 152},										//0x43
		{UNIT_OBJECT, 152},
		{0},
		{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	
		{UNIT_OBJECT, 152},										//0x44
		{UNIT_OBJECT, 152},
		{0},
		{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	
		{UNIT_OBJECT, 152},										//0x45
		{UNIT_OBJECT, 152},
		{0},
		{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	
		{UNIT_OBJECT, 152},										//0x46
		{UNIT_OBJECT, 152},
		{0},
		{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	
		{UNIT_OBJECT, 152},										//0x47
		{UNIT_OBJECT, 152},
		{0},
		{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

	
		{UNIT_OBJECT, 152},										//0x48										
		{UNIT_OBJECT, 152},
		{0},
		{EXIT, MAP_A2_CANYON_OF_THE_MAGI},

		{0}, {0}, {0}, {0},										//0x49 -> tal chambre

		{UNIT_OBJECT, 357},										//0x4a
		{UNIT_OBJECT, 357},
		{UNIT_OBJECT, 402},
		{UNIT_OBJECT, 298},

	////////////////////////////////////////////////////////////////////
	// Act 3
	////////////////////////////////////////////////////////////////////

		{0}, {0}, {0}, {0},										//0x4b -> kurast docks

	
		{EXIT, MAP_A3_GREAT_MARSH},								//0x4c
		{EXIT, MAP_A3_SPIDER_CAVERN},
		{UNIT_OBJECT, 237},
		{EXIT, MAP_A3_KURAST_DOCKS},

	
		{EXIT, MAP_A3_FLAYER_JUNGLE},							//0x4d
		{EXIT, MAP_A3_FLAYER_JUNGLE},
		{UNIT_OBJECT, 237},
		{EXIT, MAP_A3_SPIDER_FOREST},

	
		{EXIT, MAP_A3_LOWER_KURAST},							//0x4e
		{UNIT_OBJECT, 252},
		{UNIT_OBJECT, 237},
		{EXIT, MAP_A3_GREAT_MARSH},

	
		{EXIT, MAP_A3_KURAST_BAZAAR},							//0x4f
		{EXIT, MAP_A3_KURAST_BAZAAR},
		{UNIT_OBJECT, 237},
		{EXIT, MAP_A3_FLAYER_JUNGLE},

	
		{EXIT, MAP_A3_UPPER_KURAST},							//0x50
		{EXIT, MAP_A3_RUINED_TEMPLE},
		{UNIT_OBJECT, 237},
		{EXIT, MAP_A3_LOWER_KURAST},

	
		{EXIT, MAP_A3_KURAST_CAUSEWAY},							//0x51
		{EXIT, MAP_A3_KURAST_CAUSEWAY},
		{UNIT_OBJECT, 237},
		{EXIT, MAP_A3_KURAST_BAZAAR},

	
		{EXIT, MAP_A3_TRAVINCAL},								//0x52
		{EXIT, MAP_A3_TRAVINCAL},
		{0},
		{EXIT, MAP_A3_UPPER_KURAST},

	
		{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_1},					//0x53
		{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_1},
		{UNIT_OBJECT, 237},
		{EXIT, MAP_A3_KURAST_CAUSEWAY},

		{0}, {0}, {0}, {0},										//0x54 -> arachnid lair
		{0}, {0}, {0}, {0},										//0x55 -> spider cavern
		{0}, {0}, {0}, {0},										//0x56 -> swampy pit lvl 1
		{0}, {0}, {0}, {0},										//0x57 -> swampy pit lvl 2
		{0}, {0}, {0}, {0},										//0x58 -> flayer dungeon lvl 1
		{0}, {0}, {0}, {0},										//0x59 -> flayer dungeon lvl 2
		{0}, {0}, {0}, {0},										//0x5a -> swampy pit lvl 3
		{0}, {0}, {0}, {0},										//0x5b -> flayer dungeon lvl 3
		{0}, {0}, {0}, {0},										//0x5c -> sewer lvl 1
		{0}, {0}, {0}, {0},										//0x5d -> sewer lvl 2
		{0}, {0}, {0}, {0},										//0x5e -> ruined temple
		{0}, {0}, {0}, {0},										//0x5f -> disused fane
		{0}, {0}, {0}, {0},										//0x60 -> forgotten reliquary
		{0}, {0}, {0}, {0},										//0x61 -> forgotton temple
		{0}, {0}, {0}, {0},										//0x62 -> ruined fane
		{0}, {0}, {0}, {0},										//0x63 -> disused reliquary
	
		{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_2},					//0x64
		{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_2},
		{0},
		{EXIT, MAP_A3_TRAVINCAL},
	
		{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_3},					//0x65
		{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_3},
		{UNIT_OBJECT, 324},
		{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_1},
	
		{XY, 17591, 8069},										//0x66
		{XY, 17591, 8069},
		{0},
		{EXIT, MAP_A3_DURANCE_OF_HATE_LEVEL_2},


	////////////////////////////////////////////////////////////////////
	// Act 4
	////////////////////////////////////////////////////////////////////

		{0}, {0}, {0}, {0},										//0x67 pandemonium fortress

	
		{EXIT, MAP_A4_PLAINS_OF_DESPAIR},						//0x68
		{EXIT, MAP_A4_PLAINS_OF_DESPAIR},
		{0},
		{EXIT, MAP_A4_THE_PANDEMONIUM_FORTRESS},

	
		{EXIT, MAP_A4_CITY_OF_THE_DAMNED},						//0x69
		{UNIT_MONSTER, 256},
		{UNIT_OBJECT, 238},
		{EXIT, MAP_A4_OUTER_STEPPES},

	
		{EXIT, MAP_A4_RIVER_OF_FLAME},							//0x6a
		{EXIT, MAP_A4_RIVER_OF_FLAME},
		{UNIT_OBJECT, 238},
		{EXIT, MAP_A4_PLAINS_OF_DESPAIR},

	
		{UNIT_OBJECT, 255, NULL, MAP_A4_THE_CHAOS_SANCTUARY},	//0x6b
		{UNIT_OBJECT, 376},
		{UNIT_OBJECT, 238},
		{EXIT, MAP_A4_CITY_OF_THE_DAMNED},

	
		{UNIT_OBJECT, 255},										//0x6c
		{UNIT_OBJECT, 255},
		{0},
		{EXIT, MAP_A4_RIVER_OF_FLAME},


	////////////////////////////////////////////////////////////////////
	// Act 5
	////////////////////////////////////////////////////////////////////

		{0}, {0}, {0}, {0},										//0x6d
	
		{EXIT, MAP_A5_FRIGID_HIGHLANDS},						//0x6e
		{UNIT_MONSTER, 776},
		{0},
		{EXIT, MAP_A5_HARROGATH},

		{EXIT, MAP_A5_ARREAT_PLATEAU},							//0x6f
		{EXIT, MAP_A5_ARREAT_PLATEAU},
		{UNIT_OBJECT, 496},
		{EXIT, MAP_A5_THE_BLOODY_FOOTHILLS},
	
		{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},						//0x70
		{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},
		{UNIT_OBJECT, 496},
		{EXIT, MAP_A5_FRIGID_HIGHLANDS},
	
		{EXIT, MAP_A5_GLACIAL_TRAIL},							//0x71
		{EXIT, MAP_A5_FROZEN_RIVER},
		{UNIT_OBJECT, 511},
		{EXIT, MAP_A5_ARREAT_PLATEAU},
	
		{UNIT_OBJECT, 460},										//0x72
		{UNIT_OBJECT, 460},
		{0},
		{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},
	
		{EXIT, MAP_A5_FROZEN_TUNDRA},							//0x73
		{EXIT, MAP_A5_FROZEN_TUNDRA},
		{UNIT_OBJECT, 511},
		{EXIT, MAP_A5_CRYSTALLINE_PASSAGE},

		{0}, {0}, {0}, {0},										//0x74 -> drifter cavern
	
		{EXIT, MAP_A5_THE_ANCIENTS_WAY},						//0x75
		{EXIT, MAP_A5_THE_ANCIENTS_WAY},
		{UNIT_OBJECT, 496},
		{EXIT, MAP_A5_ARREAT_PLATEAU},

		{EXIT, MAP_A5_ARREAT_SUMMIT},							//0x76
		{EXIT, MAP_A5_ARREAT_SUMMIT},
		{UNIT_OBJECT, 511},
		{EXIT, MAP_A5_FROZEN_TUNDRA},

		{0}, {0}, {0}, {0},										//0x77 -> icy cellar
	
		{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_1},					//0x78
		{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_1},
		{0},
		{EXIT, MAP_A5_THE_ANCIENTS_WAY},
	
		{EXIT, MAP_A5_HALLS_OF_ANGUISH},						//0x79
		{EXIT, MAP_A5_HALLS_OF_ANGUISH},
		{0},
		{0},
	
		{EXIT, MAP_A5_HALLS_OF_PAIN},							//0x7a
		{EXIT, MAP_A5_HALLS_OF_PAIN},
		{0},
		{EXIT, MAP_A5_NIHLATHAKS_TEMPLE},
	
		{EXIT, MAP_A5_HALLS_OF_VAUGHT},							//0x7b
		{EXIT, MAP_A5_HALLS_OF_VAUGHT},
		{UNIT_OBJECT, 496},
		{EXIT, MAP_A5_HALLS_OF_ANGUISH},
	
		{UNIT_OBJECT, 462},										//0x7c
		{UNIT_OBJECT, 462},
		{0},
		{EXIT, MAP_A5_HALLS_OF_PAIN},

		{0}, {0}, {0}, {0},										//0x7d -> abaddon
		{0}, {0}, {0}, {0},										//0x7e -> pit of acheron
		{0}, {0}, {0}, {0},										//0x7f -> infernal pit
	
		{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_2},					//0x80
		{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_2},
		{0},
		{EXIT, MAP_A5_ARREAT_PLATEAU},
	
		{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_3},					//0x81
		{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_3},
		{UNIT_OBJECT, 494},
		{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_1},
	
		{EXIT, MAP_A5_THRONE_OF_DESTRUCTION},					//0x82
		{EXIT, MAP_A5_THRONE_OF_DESTRUCTION},
		{0},
		{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_2},
	
		{XY, 15091, 5006},										//0x83
		{XY, 15114, 5069},
		{0},
		{EXIT, MAP_A5_WORLDSTONE_KEEP_LEVEL_3},

		{0}, {0}, {0}, {0},										//0x84 -> worldstone keep

		{UNIT_OBJECT, 397},										//0x85
		{UNIT_OBJECT, 397},
		{0},
		{0},

		{0}, {0}, {0}, {0},										//0x86 -> forgotton sands
	
		{UNIT_OBJECT, 397},										//0x87
		{UNIT_OBJECT, 397},
		{0},
		{0}
};

void ManageTele(Vector T)
{
/*
ManageTele func:
0-5 = units
6 = exit
7 = x/y
Id is lvl id or dwtxtfileno or x
Id2 can be left 0, if its another value the func will use EITHER id.
Id2 cannot be 0 if type is x/y
*/
	if(!T.Id)
		return;

	DWORD Areas[2];
	DWORD AreaCount = 1;

	Areas[0] = GetPlayerArea();

	if(T.Area)
	{
		Areas[1] = T.Area;
		AreaCount = 2;
	}
	if(Areas[0] == MAP_A2_CANYON_OF_THE_MAGI)
	{
		if(T.dwType == 0 && T.Id == 0)
		{
			T.dwType = EXIT;
			T.Id = GetLevel(Areas[0])->pMisc->dwStaffTombLevel;
		}
	}
	else if(Areas[0] == MAP_A1_COLD_PLAINS)
	{
		if(cColdToCave)
			if(T.Id == MAP_A1_BURIAL_GROUNDS)
				T.Id = MAP_A1_CAVE_LEVEL_1;
	}


	if(T.dwType == EXIT)
	{
		CCollisionMap g_collisionMap; //init the collisionmap

		if(!g_collisionMap.CreateMap(Areas, AreaCount))//create a cmap for the current area
		{
			PrintText(FONTCOLOR_GOLD, "createmap failed");
			return;
		}

		LPLevelExit ExitArray[0x40];//declare an array of exits to store the exits in later

		int ExitCount = g_collisionMap.GetLevelExits(ExitArray); //getlevelexits returns the exitcount

		//char buffer[32];
		//sprintf(buffer, "exitcount: %d", ExitCount);
		//PrintText(buffer, 4);
		//int LevelCount = 0;
		//LevelCount = GetExits(Exits);

		if(!ExitCount)//if there are 0 tele positions we can stop here :p
			return;

		for(int i = 0;i<ExitCount;i++)//loop over evey exit to see if it matches our target
		{
			//char buffer2[64];
			//sprintf(buffer2, "targetlvl: %x, %d, %d", ExitArray[i]->dwTargetLevel, ExitArray[i]->ptPos.x, ExitArray[i]->ptPos.y);
			//PrintText(buffer2, 4);
			if(ExitArray[i]->dwTargetLevel == T.Id)
			{
				LevelTxt * lvltxt =  D2COMMON_GetLevelTxt(T.Id);
				PrintText(FONTCOLOR_RED, "ÿc4AutoTele:ÿc1 Going to %s", lvltxt->szName);
				DoInteract = 0;
				if(ExitArray[i]->dwType == EXIT_TILE)
				{
					DoInteract = 1;
					InteractType = UNIT_TILE;
					InteractRoom = ExitArray[i]->pRoom;
				}
				else DoInteract = 0;

				MakePath(ExitArray[i]->ptPos.x, ExitArray[i]->ptPos.y, Areas, AreaCount, ExitArray[i]->dwType == EXIT_LEVEL ? 1: 0);
				break;
			}
		}
		return;			
	}

	if(T.dwType == XY)
	{
		DoInteract = 0;
		if(!T.Id || !T.Id2)
		{
			PrintText(FONTCOLOR_RED, "ÿc4AutoTele:ÿc1 No X/Y value found");
			return;
		}
		MakePath(T.Id, T.Id2, Areas, AreaCount, 0);/*)*/
			
	return;
	}
	if(AreaCount == 2)
		pu = FindPresetUnitXY(T.dwType, T.Id, T.Id2, Areas[1]);
	else
		pu = FindPresetUnitXY(T.dwType, T.Id, T.Id2, Areas[0]);
	if(pu.x != 0 && pu.y != 0)
	{
		//char buffer[64];
		//sprintf(buffer, "AutoTele:ÿc1 Unit: %d, x = %d, y = %d", pu->dwTxtFileNo, pu->dwPosX, pu->dwPosY);
		//PrintText(buffer, FONTCOLOR_GOLD);
		if(MakePath(pu.x,pu.y, Areas, AreaCount, 0))
		{
			//DoInteract = Interact;
			InteractType = T.dwType;
				
			/*if(TELEHANDLE && TELEHANDLE != INVALID_HANDLE_VALUE)
			{
				TerminateThread(TELEHANDLE, 0);
				CloseHandle(TELEHANDLE);
			}

			if((TELEHANDLE = CreateThread(0,0,TeleportThread,0,0,0)) == INVALID_HANDLE_VALUE)
			{
				PrintText(FONTCOLOR_RED, "ÿc4AutoTele:ÿc1 Failed to start teleport thread");
				return;
			}*/
		}
		else return;
	}
	else
	{
		PrintText(FONTCOLOR_RED, "ÿc4AutoTele:ÿc1 Can't find object");
		return;
	}
}

POINT FindPresetUnitXY(DWORD dwType, DWORD dwTxtFileNo, DWORD dwTxtFileNo2, DWORD Area)
{
	Level* pLevel = GetLevel(Area);

	//PrintText(4,"current lvl: %d", pLevel->dwLevelNo);
	
	POINT pUnit2;
	pUnit2.x = 0;
	pUnit2.y = 0;
	DoInteract = 0;

	if(!VALIDPTR(pLevel))
		return pUnit2;

	bool bAddedRoom = false;
	bool stoploop = false;
	for(Room2 *pRoom = pLevel->pRoom2First; pRoom; pRoom = pRoom->pRoom2Next)
	{
		bAddedRoom = false;
		if(!VALIDPTR(pRoom->pPreset) && !VALIDPTR(pRoom->pRoomTiles) && !VALIDPTR(pRoom->pRoom1))
		{
			D2COMMON_AddRoomData(D2CLIENT_GetPlayerUnit()->pAct, pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, D2CLIENT_GetPlayerUnit()->pPath->pRoom1);
			bAddedRoom = true;
		}
		
		for(PresetUnit* pUnit = pRoom->pPreset; pUnit; pUnit = pUnit->pPresetNext)
		{
			//PrintText(4, "X: %d, Y: %d, TxtFileNo: %d, Type: %d", pUnit->dwPosX, pUnit->dwPosY, pUnit->dwTxtFileNo, pUnit->dwType);
			if(((dwType == NULL) || (dwType == pUnit->dwType)) && (dwTxtFileNo == pUnit->dwTxtFileNo))
			{
				if(dwType == UNIT_TILE || (dwType == UNIT_OBJECT && dwTxtFileNo == 298))
				{
					InteractRoom = pRoom;
					InteractType = dwType;
					DoInteract = 1;
				}

				if(dwType == UNIT_OBJECT)
				{
					for(int i = 0;i <= ArraySize(waypoints);i++)
					{
						if(waypoints[i] == dwTxtFileNo)
						{
							InteractRoom = pRoom;
							InteractType = dwType;
							DoInteract = 1;
							stoploop = 1;//stop looping over the rooms
							break;
						}
					}
				}

				pUnit2.x = (pUnit->dwPosX) + (pRoom->dwPosX * 5);
				pUnit2.y = (pUnit->dwPosY) + (pRoom->dwPosY * 5);
				
				if(dwType == UNIT_OBJECT)
				{
					ObjectTxt * ObjTxt = D2COMMON_GetObjectTxt(dwTxtFileNo);
					PrintText(FONTCOLOR_RED, "ÿc4AutoTele:ÿc1 Going to %s", ObjTxt->szName);
				}

				stoploop = 1;//stop looping over the rooms
				break;
			}
		}

		if(bAddedRoom)
		{
			D2COMMON_RemoveRoomData(D2CLIENT_GetPlayerUnit()->pAct, pLevel->dwLevelNo, pRoom->dwPosX, pRoom->dwPosY, D2CLIENT_GetPlayerUnit()->pPath->pRoom1);
			bAddedRoom = false;
		}
		if(stoploop)
		{
			stoploop = 0;
			break;
		}
	}

	return pUnit2;
}

int MakePath(int x, int y, DWORD Areas[], DWORD count, bool MoveThrough)
{
	CCollisionMap g_collisionMap; //init the collisionmap
	DWORD dwCount;
	POINT aPath[255];

	if(!g_collisionMap.CreateMap(Areas, count))
		return false;

	POINT ptStart = {D2CLIENT_GetPlayerUnit()->pPath->xPos, D2CLIENT_GetPlayerUnit()->pPath->yPos};
	POINT ptEnd = {x, y};

	if(!g_collisionMap.IsValidAbsLocation(ptStart.x, ptStart.y))
		return false;

	if(!g_collisionMap.IsValidAbsLocation(ptEnd.x, ptEnd.y))
		return false;

	g_collisionMap.AbsToRelative(ptStart);
	g_collisionMap.AbsToRelative(ptEnd);

	WordMatrix matrix;

	if(!g_collisionMap.CopyMapData(matrix))
		return false;

	CTeleportPath tf(matrix.GetData(), matrix.GetCX(), matrix.GetCY());
	dwCount = tf.FindTeleportPath(ptStart, ptEnd, aPath, 255);

	if(dwCount == 0)
		return false;

	for(DWORD i = 0;i < dwCount;i++) {
		g_collisionMap.RelativeToAbs(aPath[i]);
	}

	if(MoveThrough) {
		if(aPath[dwCount-1].x > aPath[dwCount-2].x)
			aPath[dwCount].x = aPath[dwCount-1].x + 2;
		else
			aPath[dwCount].x = aPath[dwCount-1].x - 2;
		if(aPath[dwCount-1].y > aPath[dwCount-2].y)
			aPath[dwCount].y = aPath[dwCount-1].y + 2;
		else
			aPath[dwCount].y = aPath[dwCount-1].y - 2;

		dwCount++;

		if(GetDistanceSquared(aPath[dwCount-1].x, aPath[dwCount-1].y, aPath[dwCount-3].x, aPath[dwCount-3].y) <= 30) {
			aPath[dwCount-2] = aPath[dwCount-1];
			aPath[dwCount-1].x = 0;
			aPath[dwCount-1].y = 0;
			dwCount--;
		}
	}


	Path.RemoveAll();
	for(DWORD i = 0;i<dwCount;i++)
		Path.Add(aPath[i], 1);

	return dwCount;
}

DWORD WINAPI TeleportThread(LPVOID P)
{
	POINT ptEND;
	DWORD Time = 0;
	DWORD Try = 0;

	while(1)
	{
		Sleep(40);
		if(Path.GetSize() && GameReady())
		{
			ptEND = Path.GetLast();

			if(!SetSkill(D2S_TELEPORT, 0))
			{
				Path.RemoveAll();
				PrintText(FONTCOLOR_RED, "ÿc4AutoTele:ÿc1 Failed to set teleport!");
			}

			for(int i = 0; i < 25 ; i++)
			{
				if(GameReady() && D2CLIENT_GetPlayerUnit())
				{
					if(D2CLIENT_GetPlayerUnit()->pInfo->pRightSkill->pSkillInfo->wSkillId == D2S_TELEPORT)
						break;
					else if (i > 23)
					{
						Path.RemoveAll();
						PrintText(FONTCOLOR_RED, "ÿc4AutoTele:ÿc1 Failed to set teleport skill. Ping: %d", D2CLIENT_Ping);
						break;
					}
				}
				else 
				{
					Path.RemoveAll();
					break;
				}
				Sleep(40);
			}

			while(Path.GetSize() && GameReady())
			{
				if(Time == 0)
				{
					if(!TeleOnMap(static_cast<WORD>(Path.ElementAt(0).x),static_cast<WORD>(Path.ElementAt(0).y), false))
					{
						Path.RemoveAll();
						break;
					}
				}
				else if(Time >= 50) 
				{
					Time = 0;
					if(Try >= 5)
					{
						PrintText(FONTCOLOR_RED, "ÿc4AutoTele:ÿc1 Failed to teleport after 5 tries");
						Path.RemoveAll();
						Try = 0;
						DoInteract = 0;
						break;
					}
					else
					{
						Try++;
						continue;
					}
				}
				if(GameReady())
				{
					if(GetDistanceSquared(D2CLIENT_GetUnitX(D2CLIENT_PlayerUnit),D2CLIENT_GetUnitY(D2CLIENT_PlayerUnit),Path.ElementAt(0).x,Path.ElementAt(0).y) <= 5) {
						Path.RemoveAt(0,1);
						Time = 0;
						continue;
					}
					else
					{
						Time ++;
						Sleep(10);
					}
				}
			}

			if(DoInteract)
			{
				Sleep(100);
				Interact(GetUnitByXY(ptEND.x, ptEND.y, InteractRoom), InteractType);
			}
		}
	}
	return 0;
}
/*
	DWORD Time = 0;
	DWORD Try = 0;
Start:
	//PrintText("ÿc4AutoTele:ÿc1 Starting teleport", FONTCOLOR_RED);
	Path.RemoveAll();
	for(DWORD i = 0;i<dwCount;i++)
		Path.Add(aPath[i], 1);
	
	//PrintText(1, "size: %d", Path.GetSize());

	if(Path.GetSize() == 0)
	{
		PrintText(1, "ÿc4AutoTele:ÿc1 Missing path, aborting.");
		return false;
	}

	POINT ptEND = Path.GetLast();

	if(!SetSkill(D2S_TELEPORT, 0))
	{
		Path.RemoveAll();
		return false;
	}

	for(int i = 0; i < 25 ; i++)
	{
		Sleep(40);
		if(D2CLIENT_GetPlayerUnit())
			if(D2CLIENT_GetPlayerUnit()->pInfo->pRightSkill->pSkillInfo->wSkillId == D2S_TELEPORT)
				break;
			else if (i > 23)
			{
				Path.RemoveAll();
				PrintText(FONTCOLOR_RED, "ÿc4AutoTele:ÿc1 Failed to set teleport skill. Ping: %d", D2CLIENT_Ping);
				return false;
			}
	}*/

	/*PrintText(1, "me: [%d][%d]", D2CLIENT_GetUnitX(D2CLIENT_PlayerUnit),D2CLIENT_GetUnitY(D2CLIENT_PlayerUnit));
	for(int i = 0;i<Path.GetSize();i++)
	{
		PrintText(1, "[%d][%d]", Path.ElementAt(i).x, Path.ElementAt(i).y);
	}*/

	// Going throught every PathList
		
	/*while(Path.GetSize()) 
	{
		if(Time == 0)
		{
			if(!TeleOnMap(static_cast<WORD>(Path.ElementAt(0).x),static_cast<WORD>(Path.ElementAt(0).y), false))
			{
				Path.RemoveAll();
				return 0;
			}
		}
		else if(Time >= 50) {
			Time = 0;
			if(Try >= 3)
			{
				PrintText(FONTCOLOR_RED, "ÿc4AutoTele:ÿc1 Failed to teleport after 3 tries");
				Path.RemoveAll();
				DWORD Areas[1];
				Areas[0] = GetPlayerArea();
				TeleFunc(static_cast<int>(ptEND.x), static_cast<int>(ptEND.y), Areas, 1);
				Try = 0;
				goto Start;
			}
			else
			{
				Try++;
				continue;
			}
		}
		if(GetDistanceSquared(D2CLIENT_GetUnitX(D2CLIENT_PlayerUnit),D2CLIENT_GetUnitY(D2CLIENT_PlayerUnit),Path.ElementAt(0).x,Path.ElementAt(0).y) <= 5) {
			Path.RemoveAt(0,1);
			Time = 0;
			continue;
		}
		Time ++;
		Sleep(10);
	}
	Sleep(100);

	if(DoInteract)
	{
		Interact(GetUnitByXY(ptEND.x, ptEND.y, InteractRoom), InteractType);
	}
	Path.RemoveAll();
	return TRUE;
}*/

DWORD GetUnitByXY(DWORD X, DWORD Y, Room2* pRoom)
{
	UnitAny* pUnit;
	

	if(!VALIDPTR(pRoom))
		return 0;

	if(!VALIDPTR(pRoom->pRoom1))
		return 0;

	if(!VALIDPTR(pRoom->pRoom1->pUnitFirst))
		return 0;
	
	pUnit = pRoom->pRoom1->pUnitFirst;

	if(!VALIDPTR(pUnit))
		return 0;

	if(!VALIDPTR(pUnit->pObjectPath))
		return 0;

	while(pUnit)
	{
		if(pUnit->dwType != UNIT_PLAYER)
			if(X == pUnit->pObjectPath->dwPosX)
				if(Y == pUnit->pObjectPath->dwPosY)
					return pUnit->dwUnitId;
		pUnit=pUnit->pListNext;
	}
	return 0;
}