class JarkaTrigger extends anomalyTrigger
{
	protected ref array<string>	m_HitZones;

	void JarkaTrigger()
	{
		m_damageForItem = 15;
		m_HitZones = { "Head","Torso","LeftHand","LeftLeg","LeftFoot","RightHand","RightLeg","RightFoot" };
		m_ExtentMin = "-2 -0.5 -2";
		m_ExtentMax = "2 2 2";
		m_isActive = true;
	}

	void ~JarkaTrigger()
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
		Print("AnomalyJarkaTrigger: " + obj + " entered");
		#endif
	}

	override void OnLeave(Object obj)
	{	
		#ifdef DEBUG_ANOMALY
		Print("AnomalyJarkaTrigger: " + obj + " left");
		#endif
	}
		
	void anomalyActivate()
	{
		if (m_AnomalyObject) GetGame().ObjectDelete(m_AnomalyObject);
		m_AnomalyObject = SpawnAnomaly("Anomaly_Jarka_Active", m_AnomalyPosition);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.updateInsidersAndSetDamage, 0.5*1000, true);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.anomalyDeactivate, 11*1000);
		
		#ifdef DEBUG_ANOMALY
		Print("AnomalyJarka: Activated");
		#endif
	}
		
	void anomalyDeactivate()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.updateInsidersAndSetDamage);
		
		if (m_insiders.Count() > 0)
		{
			anomalyActivate();
			
			#ifdef DEBUG_ANOMALY
			Print("AnomalyJarka: Reactivate");
			#endif
		}
		else
		{
			if (m_AnomalyObject) GetGame().ObjectDelete(m_AnomalyObject);
			m_AnomalyObject = SpawnAnomaly("Anomaly_Jarka_Idle", m_AnomalyPosition);
			m_isActive = false;
			
			#ifdef DEBUG_ANOMALY
			Print("AnomalyJarka: Deactivated");
			#endif
		}
	}
	
	override void anomalySetDamage(Object obj)
	{
		super.anomalySetDamage(obj);
		if(obj.IsTransport()) obj.DecreaseHealth( "", "Health", 10);
		obj.ProcessDirectDamage(DT_CUSTOM, this, GetRandomHitZone(m_HitZones), "FireDamage", "0.5 0.5 0.5", 3);
	}
	
	override void EOnInit(IEntity other, int extra)
	{
		SetExtents(m_ExtentMin, m_ExtentMax);
		m_AnomalyPosition = GetPosition();
		m_AnomalyObject = SpawnAnomaly("Anomaly_Jarka_Idle", m_AnomalyPosition);
		m_isActive = false;
	}
}