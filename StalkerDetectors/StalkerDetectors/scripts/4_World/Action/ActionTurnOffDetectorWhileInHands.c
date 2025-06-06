class ActionTurnOffDetectorWhileInHands: ActionSingleUseBase
{
	void ActionTurnOffDetectorWhileInHands()
	{
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_CLOSEITEM_ONCE;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "#switch_off";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if ( item.HasEnergyManager()  &&  item.GetCompEM().CanSwitchOff() )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	override void OnExecuteServer( ActionData action_data )
	{
		action_data.m_MainItem.GetCompEM().SwitchOff();
        action_data.m_MainItem.Close();
	}
}