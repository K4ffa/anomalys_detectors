////////////////////////////////////////////////////////////////////
//DeRap: 1static\artefact\Box\config.bin
//Produced from mikero's Dos Tools Dll version 9.10
//https://mikero.bytex.digital/Downloads
//'now' is Mon Jun 02 14:15:32 2025 : 'file' last modified on Fri Dec 03 20:04:04 2021
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class DZ_Gear_Containers
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgSlots
{
	class Slot_ART
	{
		name = "ART";
		displayName = "Artefact";
		selection = "";
		ghostIcon = "Filter";
	};
	class Slot_ART2
	{
		name = "ART2";
		displayName = "Artefact";
		selection = "";
		ghostIcon = "Filter";
	};
	class Slot_ART3
	{
		name = "ART3";
		displayName = "Artefact";
		selection = "";
		ghostIcon = "Filter";
	};
	class Slot_ART4
	{
		name = "ART4";
		displayName = "Artefact";
		selection = "";
		ghostIcon = "Filter";
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class SmallProtectorCase;
	class WorldContainer_Base;
	class dzrp_ArtefactCase: SmallProtectorCase
	{
		scope = 2;
		displayName = "Artifact Сontainment";
		descriptionShort = "A containment system designed for artifacts found in the Zone";
		model = "DayZRP\1static\artefact\Box\Box.p3d";
		rotationFlags = 17;
		weight = 2000;
		itemSize[] = {2,4};
		itemsCargoSize[] = {0,0};
		canBeDigged = 1;
		isMeleeWeapon = 1;
		allowOwnedCargoManipulation = 1;
		randomQuantity = 2;
		lootTag[] = {"Medic","Work","Camping"};
		attachments[] = {"ART","ART2","ART3","ART4"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"DZ\gear\containers\data\Protector_Case.rvmat"}},{0.7,{"DZ\gear\containers\data\Protector_Case.rvmat"}},{0.5,{"DZ\gear\containers\data\Protector_Case_damage.rvmat"}},{0.3,{"DZ\gear\containers\data\Protector_Case_damage.rvmat"}},{0,{"DZ\gear\containers\data\Protector_Case_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet = "smallprotectorcase_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "smallprotectorcase_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
	class dzrp_ArtefactCase_1: SmallProtectorCase
	{
		scope = 2;
		displayName = "Artifact Сontainment 1";
		descriptionShort = "A containment system designed for artifacts found in the Zone";
		model = "DayZRP\1static\artefact\Box\Box1.p3d";
		rotationFlags = 17;
		weight = 2000;
		itemSize[] = {2,1};
		itemsCargoSize[] = {0,0};
		canBeDigged = 1;
		isMeleeWeapon = 1;
		allowOwnedCargoManipulation = 1;
		randomQuantity = 2;
		lootTag[] = {"Medic","Work","Camping"};
		attachments[] = {"ART"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"DZ\gear\containers\data\Protector_Case.rvmat"}},{0.7,{"DZ\gear\containers\data\Protector_Case.rvmat"}},{0.5,{"DZ\gear\containers\data\Protector_Case_damage.rvmat"}},{0.3,{"DZ\gear\containers\data\Protector_Case_damage.rvmat"}},{0,{"DZ\gear\containers\data\Protector_Case_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet = "smallprotectorcase_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "smallprotectorcase_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
	class dzrp_ArtefactCase_2: SmallProtectorCase
	{
		scope = 2;
		displayName = "Artifact Сontainment 2";
		descriptionShort = "A containment system designed for artifacts found in the Zone";
		model = "DayZRP\1static\artefact\Box\Box2.p3d";
		rotationFlags = 17;
		weight = 2000;
		itemSize[] = {2,2};
		itemsCargoSize[] = {0,0};
		canBeDigged = 1;
		isMeleeWeapon = 1;
		allowOwnedCargoManipulation = 1;
		randomQuantity = 2;
		lootTag[] = {"Medic","Work","Camping"};
		attachments[] = {"ART","ART2"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"DZ\gear\containers\data\Protector_Case.rvmat"}},{0.7,{"DZ\gear\containers\data\Protector_Case.rvmat"}},{0.5,{"DZ\gear\containers\data\Protector_Case_damage.rvmat"}},{0.3,{"DZ\gear\containers\data\Protector_Case_damage.rvmat"}},{0,{"DZ\gear\containers\data\Protector_Case_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet = "smallprotectorcase_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "smallprotectorcase_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
	class dzrp_ArtefactCase_3: SmallProtectorCase
	{
		scope = 2;
		displayName = "Artifact Сontainment 3";
		descriptionShort = "A containment system designed for artifacts found in the Zone";
		model = "DayZRP\1static\artefact\Box\Box3.p3d";
		rotationFlags = 17;
		weight = 2000;
		itemSize[] = {2,3};
		itemsCargoSize[] = {0,0};
		canBeDigged = 1;
		isMeleeWeapon = 1;
		allowOwnedCargoManipulation = 1;
		randomQuantity = 2;
		lootTag[] = {"Medic","Work","Camping"};
		attachments[] = {"ART","ART2","ART3"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"DZ\gear\containers\data\Protector_Case.rvmat"}},{0.7,{"DZ\gear\containers\data\Protector_Case.rvmat"}},{0.5,{"DZ\gear\containers\data\Protector_Case_damage.rvmat"}},{0.3,{"DZ\gear\containers\data\Protector_Case_damage.rvmat"}},{0,{"DZ\gear\containers\data\Protector_Case_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet = "smallprotectorcase_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "smallprotectorcase_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
};
