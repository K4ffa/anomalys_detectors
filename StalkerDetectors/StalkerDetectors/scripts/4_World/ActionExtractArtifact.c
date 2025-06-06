override void CreateConditionComponents()
{
    m_ConditionItem = new CCINonRuined;
    m_ConditionTarget = new CCTNone;
}

override string GetText()
{
    return "Extract Artifact";
}

override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
{
    return item.IsKindOf("SA_Detector_Base") && item.IsOpen() && item.GetCompEM().IsWorking();
}

override void OnFinishProgressServer(ActionData action_data)
{
    GetGame().RPCSingleParam(action_data.m_Player, StalkerDetectors.ExtractArtifact, NULL, true, action_data.m_Player.GetIdentity());
}