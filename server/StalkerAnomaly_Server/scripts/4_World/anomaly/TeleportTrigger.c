class TeleportTrigger extends anomalyTrigger
{
	protected vector			m_teleportPosition;
	protected ref TVectorArray	m_teleportPositionArray;
	protected Object			m_AnomalyObjectOut;

	void TeleportTrigger()
	{
		m_ExtentMin = "-2 -0.5 -2";
		m_ExtentMax = "2 3 2";
		m_isActive = true;
	}

	void ~TeleportTrigger()
	{
		if (m_AnomalyObject) GetGame().ObjectDelete(m_AnomalyObject);
	}
	
	override void OnEnter(Object obj)
	{
		if (!m_isActive)
		{
			m_isActive = true;
			anomalyActivate();
		}
		
		#ifdef DEBUG_ANOMALY
		Print("AnomalyTeleportTrigger: " + obj + " entered");
		#endif
	}

	override void OnLeave(Object obj)
	{	
		#ifdef DEBUG_ANOMALY
		Print("AnomalyTeleportTrigger: " + obj + " left");
		#endif
	}
		
	void anomalyActivate()
	{
		if (m_AnomalyObject) GetGame().ObjectDelete(m_AnomalyObject);
		m_AnomalyObjectActive = SpawnAnomaly("Anomaly_Teleport_Active", m_AnomalyPosition);
		
		m_teleportPosition = m_teleportPositionArray.GetRandomElement();
		m_AnomalyObjectOut = SpawnAnomaly("Anomaly_Teleport_Active", m_teleportPosition);
		
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.deleteOutEffect, 4.8*1000);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.updateInsidersAndSetDamage, 4.8*1000);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.anomalyDeactivate, 7*1000);
		
		#ifdef DEBUG_ANOMALY
		Print("AnomalyTeleport: Activated");
		#endif
	}
		
	void anomalyDeactivate()
	{
		if (m_AnomalyObjectActive) GetGame().ObjectDelete(m_AnomalyObjectActive);
		if (m_insiders.Count() > 0)
		{
			anomalyActivate();
			
			#ifdef DEBUG_ANOMALY
			Print("AnomalyTeleport: Reactivate");
			#endif
		}
		else
		{
			m_AnomalyObject = SpawnAnomaly("Anomaly_Teleport_Idle", m_AnomalyPosition);
			m_isActive = false;
			
			#ifdef DEBUG_ANOMALY
			Print("AnomalyTeleport: Deactivated");
			#endif
		}
	}
	
	void deleteOutEffect()
	{
		if (m_AnomalyObjectOut) GetGame().ObjectDelete(m_AnomalyObjectOut);
	}
	
	override void anomalySetDamage(Object obj)
	{
		PlayerBase m_Player;
		if (Class.CastTo(m_Player, obj))
		{	
			if (m_Player.IsInVehicle()) return;
		}
		
		//Offset
		vector m_teleportOffset = m_teleportPosition;
		vector m_objectPos = obj.GetPosition();
		m_teleportOffset[0] = m_teleportPosition[0] + (m_AnomalyPosition[0] - m_objectPos[0]);
		m_teleportOffset[2] = m_teleportPosition[2] + (m_AnomalyPosition[2] - m_objectPos[2]);
		
		//Teleport
		obj.SetPosition(m_teleportOffset);
	}
	
	override void AddInsider(Object obj)
	{
		if( !obj.IsTransport() ) super.AddInsider(obj);
	}
	
	void setTeleportPosition(TVectorArray posArr)
	{
		m_teleportPositionArray = posArr;
		
		for (int i = 0; i < m_teleportPositionArray.Count(); i++)
		{
			vector m_tempPos = m_teleportPositionArray.Get(i);
			float m_height = GetGame().SurfaceY(m_tempPos[0], m_tempPos[2]);
			if (m_tempPos[1] < m_height)
			{
				m_tempPos[1] = m_height;
				m_teleportPositionArray.Set(i, m_tempPos);
			}
		}
		m_isActive = false;
	}
	
	override void EOnInit(IEntity other, int extra)
	{
		SetExtents(m_ExtentMin, m_ExtentMax);
		m_AnomalyPosition = GetPosition();
		m_AnomalyObject = SpawnAnomaly("Anomaly_Teleport_Idle", m_AnomalyPosition);
	}
}