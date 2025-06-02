class CfgPatches
{
	class StalkerDetectors_Server
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class StalkerDetectors_Server
	{
		author="BI";
		type = "mod";
		dependencies[]={ "Game", "World", "Mission" };

		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]={"StalkerDetectors_Server/scripts/3_Game"};
			};
			
			class worldScriptModule
			{
				value="";
				files[]={"StalkerDetectors_Server/scripts/4_World"};
			};
			
			class missionScriptModule
			{
				value="";
				files[]={"StalkerDetectors_Server/scripts/5_Mission"};
			};
		};
	};
};