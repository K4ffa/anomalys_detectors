////////////////////////////////////////////////////////////////////
//DeRap: 1static\artefact\config.bin
//Produced from mikero's Dos Tools Dll version 9.10
//https://mikero.bytex.digital/Downloads
//'now' is Mon Jun 02 14:15:32 2025 : 'file' last modified on Fri Dec 03 20:04:21 2021
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class DZ_Gear_Medical
	{
		units[] = {"Medical_DisinfectantSpray","Medical_Antibiotics","Medical_Bandage","Medical_Bloodbag","Medical_Defibrillator","Medical_Epinephrine","Medical_Morphine","Medical_Painkiller"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class DayZRPArts_Base: Inventory_Base
	{
		scope = 0;
		SingleUseActions[] = {};
		rotationFlags = 17;
		canBeSplit = 1;
		itemSize[] = {2,2};
		weight = 1000;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {};
		lootTag[] = {"Medic"};
		lootCategory = "Medical";
		inventorySlot[] = {"ART","ART2","ART3","ART4"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"DZ\gear\medical\data\epipen.rvmat"}},{0.7,{"DZ\gear\medical\data\epipen.rvmat"}},{0.5,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0.3,{"DZ\gear\medical\data\epipen_damage.rvmat"}},{0,{"DZ\gear\medical\data\epipen_destruct.rvmat"}}};
				};
			};
		};
	};
	class ArtTier1: DayZRPArts_Base{};
	class ArtTier2: DayZRPArts_Base{};
	class ArtTier3: DayZRPArts_Base{};
	class DZRP_Artefact_MutadeCompass: ArtTier1
	{
		scope = 2;
		displayName = "MutadeCompass Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\compass.p3d";
	};
	class DZRP_Artefact_Vyvert1: ArtTier2
	{
		scope = 2;
		displayName = "Wrenched Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_baloon_2.p3d";
	};
	class DZRP_Artefact_Blood: ArtTier3
	{
		scope = 2;
		displayName = "StoneBlood Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_blood_2.p3d";
	};
	class DZRP_Artefact_Compas: ArtTier1
	{
		scope = 2;
		displayName = "ArtCompass Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_compass_2.p3d";
	};
	class DZRP_Artefact_Cristall: ArtTier1
	{
		scope = 2;
		displayName = "Crystal Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_cristall_2.p3d";
	};
	class DZRP_Artefact_StoneFlower: ArtTier2
	{
		scope = 2;
		displayName = "StoneFlower Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\artefact_stoneFlower.p3d";
	};
	class DZRP_Artefact_Oasis: ArtTier1
	{
		scope = 2;
		displayName = "theOasis Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_cristall_plant_2.p3d";
	};
	class DZRP_Artefact_Battery: ArtTier2
	{
		scope = 2;
		displayName = "Battery Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_dummy_battery_2.p3d";
	};
	class DZRP_Artefact_Pusto: ArtTier2
	{
		scope = 2;
		displayName = "Shell Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_dummy_dummy_2.p3d";
	};
	class DZRP_Artefact_MamaBus: ArtTier2
	{
		scope = 2;
		displayName = "MamaBeads Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_dummy_glassbeads_2.p3d";
	};
	class DZRP_Artefact_Flash: ArtTier2
	{
		scope = 2;
		displayName = "Flash Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_electra_flash_2.p3d";
	};
	class DZRP_Artefact_MoonLight: ArtTier2
	{
		scope = 2;
		displayName = "Moonlight Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_electra_moonlight_2.p3d";
	};
	class DZRP_Artefact_Sliz: ArtTier2
	{
		scope = 2;
		displayName = "Slime Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_electra_sparkler_2.p3d";
	};
	class DZRP_Artefact_Glaz: ArtTier2
	{
		scope = 2;
		displayName = "Eye Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_eye_2.p3d";
	};
	class DZRP_Artefact_Fire: ArtTier1
	{
		scope = 2;
		displayName = "Flame Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_fire_2.p3d";
	};
	class DZRP_Artefact_FireBall: ArtTier3
	{
		scope = 2;
		displayName = "Fireball Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_fireball.p3d";
	};
	class DZRP_Artefact_Kolobok: ArtTier1
	{
		scope = 2;
		displayName = "Kolobok Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_fuzz_kolobok_2.p3d";
	};
	class DZRP_Artefact_GoldFish: ArtTier1
	{
		scope = 2;
		displayName = "Goldfish Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_gold_fish_2.p3d";
	};
	class DZRP_Artefact_Gravi: ArtTier3
	{
		scope = 2;
		displayName = "Gravi Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_gravi_2.p3d";
	};
	class DZRP_Artefact_Ice: ArtTier2
	{
		scope = 2;
		displayName = "Snowflake Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_ice_2.p3d";
	};
	class DZRP_Artefact_Medusa: ArtTier3
	{
		scope = 2;
		displayName = "Jellyfish Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_medusa_2.p3d";
	};
	class DZRP_Artefact_Meat: ArtTier2
	{
		scope = 2;
		displayName = "MeatChunk Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_mincer_meat_2.p3d";
	};
	class DZRP_Artefact_NightStar: ArtTier1
	{
		scope = 2;
		displayName = "Nightstar Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_ice_2.p3d";
	};
	class DZRP_Artefact_Soul: ArtTier1
	{
		scope = 2;
		displayName = "Soul Artifact";
		descriptionShort = "Little is known about this arifact. They first started appearing in the zone few weeks after the city evacuations.";
		model = "DayZRP\1static\artefact\model\dzrp_soul_2.p3d";
	};
};
