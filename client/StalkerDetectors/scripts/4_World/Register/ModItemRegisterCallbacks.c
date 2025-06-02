/*
class ModItemRegisterCallbacks
{
	void RegisterEmptyHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior);

    void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior);

    void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior);

    void RegisterRestrained(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior);

    void RegisterSurrender(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior);

    void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior);

    void RegisterPistol(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior);

    void RegisterFireArms(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior);

    void RegisterArcheryItem(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior);

    void RegisterLauncher(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior);

	void RegisterCustom(DayZPlayerType pType);

	void CustomBoneRemapping(DayZPlayerType pType);
}
*/
modded class ModItemRegisterCallbacks
{
    override void RegisterOneHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
    {
        super.RegisterOneHanded( pType, pBehavior );
        pType.AddItemInHandsProfileIK("SA_Detector_Base", "dz/anims/workspaces/player/player_main/props/player_main_1h_compass.asi", pBehavior, "dz/anims/anm/player/ik/gear/compass.anm");
    }
};