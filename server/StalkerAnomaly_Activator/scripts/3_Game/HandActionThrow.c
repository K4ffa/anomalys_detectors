modded class HandActionThrow
{
	override void Action (HandEventBase e)
	{
		hndDebugPrint("[hndfsm] " + Object.GetDebugName(e.m_Player) + " STS=" + e.m_Player.GetSimulationTimeStamp() + " action=throw");
		HandEventThrow throwEvent = HandEventThrow.Cast(e);

		GameInventory.LocationSyncMoveEntity(e.GetSrc(), e.GetDst());

		DayZPlayer player = DayZPlayer.Cast(e.m_Player);
		if ( player.GetInstanceType() != DayZPlayerInstanceType.INSTANCETYPE_REMOTE )
		{
			InventoryItem item = InventoryItem.Cast(e.GetSrcEntity());
			if( item )
            {
                //if ( item.IsKindOf("My_Item_Name") || item.IsKindOf("My_Item_Name2") )
                //{
					Object m_AnomalyActivator = GetGame().CreateObjectEx("AnomalyActivator", item.GetPosition(), ECE_LOCAL);
					item.AddChild(m_AnomalyActivator, -1, true);
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(item.RemoveChild, 5*1000, false, m_AnomalyActivator);
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, 6*1000, false, m_AnomalyActivator);
                //}
				item.ThrowPhysically(player, throwEvent.GetForce());
            }
			else
				Error("[hndfsm] HandActionThrow - src entity null!");
		}
		player.OnItemInHandsChanged();
	}
};