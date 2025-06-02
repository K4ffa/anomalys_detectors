class TramplinTrigger extends anomalyTrigger
{
	protected ref array<string>	m_HitZones;

	void TramplinTrigger()
	{
		m_HitZones = { "Head","Torso" };
		m_ExtentMin = "-2 -0.5 -2";
		m_ExtentMax = "2 2 2";
		m_isActive = true;
	}

	void ~TramplinTrigger()
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
		Print("AnomalyTramplinTrigger: " + obj + " entered");
		#endif
	}

	override void OnLeave(Object obj)
	{	
		#ifdef DEBUG_ANOMALY
		Print("AnomalyTramplinTrigger: " + obj + " left");
		#endif
	}
		
	void anomalyActivate()
	{
		if (m_AnomalyObject) GetGame().ObjectDelete(m_AnomalyObject);	
		m_AnomalyObject = SpawnAnomaly("Anomaly_Tramplin_Active", m_AnomalyPosition);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.updateInsidersAndSetDamage, 0.3*1000);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.anomalyDeactivate, 3*1000);
		
		#ifdef DEBUG_ANOMALY
		Print("AnomalyTramplin: Activated");
		#endif
	}
		
	void anomalyDeactivate()
	{
		if (m_insiders.Count() > 0)
		{
			anomalyActivate();
			
			#ifdef DEBUG_ANOMALY
			Print("AnomalyTramplin: Reactivate");
			#endif
		}
		else
		{
			if (m_AnomalyObject) GetGame().ObjectDelete(m_AnomalyObject);	
			m_AnomalyObject = SpawnAnomaly("Anomaly_Tramplin_Idle", m_AnomalyPosition);
			m_isActive = false;
			
			#ifdef DEBUG_ANOMALY
			Print("AnomalyTramplin: Deactivated");
			#endif
		}
	}
	
	override void anomalySetDamage(Object obj)
	{
		//super.anomalySetDamage(obj);
		obj.ProcessDirectDamage(DT_CUSTOM, this, GetRandomHitZone(m_HitZones), "MeleeDamage", "0 0 0", 4);
	}
	
	override void AddInsider(Object obj)
	{
		if( !obj.IsTransport() ) super.AddInsider(obj);
	}
	
	override void EOnInit(IEntity other, int extra)
	{
		SetExtents(m_ExtentMin, m_ExtentMax);
		m_AnomalyPosition = GetPosition();
		m_AnomalyObject = SpawnAnomaly("Anomaly_Tramplin_Idle", m_AnomalyPosition);
		m_isActive = false;
	}
}