////////////////////////////////////////////////////////////////////
//DeRap: config.bin
//Produced from mikero's Dos Tools Dll version 9.10
//https://mikero.bytex.digital/Downloads
//'now' is Mon Jun 02 14:15:19 2025 : 'file' last modified on Sat Dec 04 07:58:45 2021
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class Stalker_Anomaly
	{
		units[] = {"Anomaly_Default","Anomaly_Electra_Active","Anomaly_Electra_Idle","Anomaly_Kisel_Active","Anomaly_Kisel_Idle","Anomaly_Jarka_Active","Anomaly_Jarka_Idle","Anomaly_Par_Active","Anomaly_Par_Idle","Anomaly_Teleport_Active","Anomaly_Teleport_Idle","Anomaly_Tramplin_Active","Anomaly_Tramplin_Idle","Anomaly_Voronka_Active","Anomaly_Voronka_Idle","Anomaly_Myasorubka_Active","Anomaly_Myasorubka_Idle"};
		weapons[] = {};
		requiredVersion = 1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgMods
{
	class Stalker_Anomaly
	{
		author = "BI";
		type = "mod";
		dependencies[] = {"Game","World"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"StalkerAnomaly/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"StalkerAnomaly/scripts/4_World"};
			};
		};
	};
};
class CfgVehicles
{
	class HouseNoDestruct;
	class Inventory_Base;
	class Anomaly_Default: HouseNoDestruct
	{
		scope = 2;
		model = "\StalkerAnomaly\emptysphere2.p3d";
	};
	class Anomaly_Electra_Active: Anomaly_Default{};
	class Anomaly_Electra_Idle: Anomaly_Default{};
	class Anomaly_Kisel_Active: Anomaly_Default{};
	class Anomaly_Kisel_Idle: Anomaly_Default{};
	class Anomaly_Jarka_Active: Anomaly_Default{};
	class Anomaly_Jarka_Idle: Anomaly_Default{};
	class Anomaly_Par_Active: Anomaly_Default{};
	class Anomaly_Par_Idle: Anomaly_Default{};
	class Anomaly_Teleport_Active: Anomaly_Default{};
	class Anomaly_Teleport_Idle: Anomaly_Default{};
	class Anomaly_Tramplin_Active: Anomaly_Default{};
	class Anomaly_Tramplin_Idle: Anomaly_Default{};
	class Anomaly_Voronka_Active: Anomaly_Default{};
	class Anomaly_Voronka_Idle: Anomaly_Default{};
	class Anomaly_Myasorubka_Active: Anomaly_Default{};
	class Anomaly_Myasorubka_Idle: Anomaly_Default{};
};
class CfgSounds
{
	class default
	{
		name = "";
		titles[] = {};
	};
	class electra_idle: default
	{
		sound[] = {"\StalkerAnomaly\sounds\electra_idle1",3,1,30};
	};
	class electra_active: default
	{
		sound[] = {"\StalkerAnomaly\sounds\electra_blast1",3,1,50};
	};
	class kisel_idle: default
	{
		sound[] = {"\StalkerAnomaly\sounds\buzz_idle",2,1,30};
	};
	class kisel_active: default
	{
		sound[] = {"\StalkerAnomaly\sounds\buzz_hit",3,1,30};
	};
	class jarka_idle: default
	{
		sound[] = {"\StalkerAnomaly\sounds\fire_idle",3,1,50};
	};
	class jarka_active: default
	{
		sound[] = {"\StalkerAnomaly\sounds\zhar_blow",5,1,50};
	};
	class tramplin_idle: default
	{
		sound[] = {"\StalkerAnomaly\sounds\gravi_rumble1",1,1,50};
	};
	class tramplin_active: default
	{
		sound[] = {"\StalkerAnomaly\sounds\anomaly_gravy_blast1",6,1,50};
	};
	class par_idle: default
	{
		sound[] = {"\StalkerAnomaly\sounds\steam",1,1,50};
	};
	class par_active: default
	{
		sound[] = {"\StalkerAnomaly\sounds\steam_blowout",4,1,50};
	};
	class teleport_idle: default
	{
		sound[] = {"\StalkerAnomaly\sounds\teleport_idle",3,1,30};
	};
	class teleport_active: default
	{
		sound[] = {"\StalkerAnomaly\sounds\teleport_work_2",4,1,50};
	};
	class teleport_active2: default
	{
		sound[] = {"\StalkerAnomaly\sounds\teleport_incoming",4,1,50};
	};
};
