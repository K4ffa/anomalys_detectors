class CfgPatches
{
	class StalkerAnomaly_Server
	{
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class StalkerAnomaly_Server
	{
		author="BI";
		type = "mod";
		dependencies[]={ "World", "Mission" };

		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]={"StalkerAnomaly_Server/scripts/4_World"};
			};

			class missionScriptModule
			{
				value="";
				files[]={"StalkerAnomaly_Server/scripts/5_Mission"};
			};
		};
	};
};