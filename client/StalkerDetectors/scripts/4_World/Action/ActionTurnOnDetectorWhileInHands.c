class ActionTurnOnDetectorWhileInHands: ActionSingleUseBase
{
	void ActionTurnOnDetectorWhileInHands()
	{
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM_ONCE;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_OPENITEM_ONCE;
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
		return "#switch_on";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{		
		if ( item.HasEnergyManager()  &&  item.GetCompEM().CanSwitchOn()  &&  item.GetCompEM().CanWork() )
		{
			return true;
		}
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		if ( action_data.m_MainItem.HasEnergyManager() )
		{
			if ( action_data.m_MainItem.GetCompEM().CanWork() )
			{
				action_data.m_MainItem.GetCompEM().SwitchOn();
			}
			else
			{
				InformPlayers(action_data.m_Player,action_data.m_Target,UA_FAILED);
			}
		}
        
		action_data.m_MainItem.Open();
	}
}