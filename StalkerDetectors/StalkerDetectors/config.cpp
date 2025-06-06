class CfgPatches
{
    class StalkerDetectors
    {
        units[] = {"SA_Detector_Otklik","SA_Detector_Bear"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data"};
    };
};
class CfgMods
{
    class StalkerDetectors
    {
        author = "BI";
        type = "mod";
        dependencies[] = {"Game","World"};
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"StalkerDetectors/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"StalkerDetectors/scripts/4_World"};
            };
        };
    };
};
class CfgVehicles
{
    class Inventory_Base;
    class SA_Detector_Base: Inventory_Base
    {
        scope = 0;
        displayName = "Detector Base";
        descriptionShort = "Detector Base";
        itemSize[] = {1,2};
        weight = 210;
        attachments[] = {"BatteryD"};
        class EnergyManager
        {
            hasIcon = 1;
            autoSwitchOffWhenInCargo = 1;
            energyUsagePerSecond = 0.01;
            plugType = 1;
            attachmentAction = 1;
            updateInterval = 0.5;
        };
        class AnimationSources
        {
            class cover
            {
                source = "user";
                animPeriod = 0.5;
                initPhase = 0;
            };
            class radar
            {
                source = "user";
                animPeriod = 0.001;
                initPhase = 0;
            };
        };
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 70;
                    healthLevels[] = {{1,{"DZ\gear\tools\data\flashlight_old.rvmat"}},{0.7,{"DZ\gear\tools\data\flashlight_old.rvmat"}},{0.5,{"DZ\gear\tools\data\flashlight_old_damage.rvmat"}},{0.3,{"DZ\gear\tools\data\flashlight_old_damage.rvmat"}},{0,{"DZ\gear\tools\data\flashlight_old_destruct.rvmat"}}};
                };
            };
        };
        class AnimEvents
        {
            class SoundWeapon
            {
                class compass_open
                {
                    soundSet = "compass_open_SoundSet";
                    id = 204;
                };
                class compass_close
                {
                    soundSet = "compass_close_SoundSet";
                    id = 205;
                };
            };
        };
    };
    class SA_Detector_Otklik: SA_Detector_Base
    {
        scope = 2;
        displayName = "Artifact detector 'Echo'";
        descriptionShort = "The most primitive type of anomalous activity detector. With it, you can find only the most common artifacts.";
        model = "\StalkerDetectors\detector_otklik.p3d";
        hiddenSelections[] = {"led","lamp"};
        hiddenSelectionsTextures[] = {"StalkerDetectors\data\green_ca.paa","StalkerDetectors\data\blue_ca.paa"};
    };
    class SA_Detector_Bear: SA_Detector_Base
    {
        scope = 2;
        displayName = "Artifact detector 'Bear'";
        descriptionShort = "A more advanced type of detector than Echo is able to show the direction in which you need to move to find an artifact";
        model = "\StalkerDetectors\detector_bear.p3d";
        weight = 310;
        hiddenSelections[] = {"led","radar"};
        hiddenSelectionsTextures[] = {"StalkerDetectors\data\green_ca.paa","StalkerDetectors\data\detector_bear\radar\radar_empty.paa"};
    };
};
class CfgSoundSets
{
    class Detector_Beep_SoundSet
    {
        soundShaders[] = {"Detector_Beep_SoundShader"};
        volumeFactor = 1.0;
        spatial = 1;
        distanceFilter = "defaultDistanceFilter";
        loop = 0;
    };
    class Detector_Beep_Art_SoundSet
    {
        soundShaders[] = {"Detector_Beep_Art_SoundShader"};
        volumeFactor = 1.0;
        spatial = 1;
        distanceFilter = "defaultDistanceFilter";
        loop = 0;
    };
};
class CfgSoundShaders
{
    class Detector_Beep_SoundShader
    {
        samples[] = {{"\StalkerDetectors\sounds\detector_beep", 1}};
        volume = 1.0;
        range = 10;
    };
    class Detector_Beep_Art_SoundShader
    {
        samples[] = {{"\StalkerDetectors\sounds\detector_beep_art", 1}};
        volume = 1.0;
        range = 10;
    };
};