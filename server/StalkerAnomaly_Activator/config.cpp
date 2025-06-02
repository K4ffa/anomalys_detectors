class CfgPatches
{
	class StalkerAnomaly_Activator
	{
		requiredAddons[]=
		{
			"DZ_Animals",
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class StalkerAnomaly_Activator
	{
		author="BI";
		type = "mod";
		dependencies[]={ "Game", "World" };

		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]={"StalkerAnomaly_Activator/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value="";
				files[]={"StalkerAnomaly_Activator/scripts/4_World"};
			};
		};
	};
};

class CfgVehicles
{
	class AnimalBase;
	class AnomalyActivator: AnimalBase
	{
		simulation="dayzanimal";
		scope=2;
		model="\dz\gear\consumables\spraycan.p3d";
		displayName="AnomalyActivator";
		descriptionShort="AnomalyActivator";
		aiAgentTemplate="AmbientLife";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1;
					healthLabels[]={0,0,0,0,0};
				};
			};
		};
		class Skinning{};
		class enfanimsys
		{
			meshObject="dz\animals\gallus_gallus_domesticus\data\gallus_gallus_domesticus.xob";
			graphname="dz\animals\animations\!graph_files\AmbientLife\AmbientLife_Graph.agr";
			defaultinstance="dz\animals\animations\!graph_files\AmbientLife\GallusGallus_skeleton_AnimInstance.asi";
			startnode="Master_SM";
			skeletonName="gallus_gallus_domesticus.xob";
		};
		class AnimEvents{};
		class CommandLookAtSettings
		{
			lookAtFilterTimeout=0;
			lookAtFilterSpeed=0;
		};
		class CommandMoveSettings
		{
			useSpeedMapping=0;
			movementSpeedMapping[]={0,0,0,0};
		};
	};
};