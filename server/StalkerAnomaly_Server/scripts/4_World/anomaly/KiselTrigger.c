class KiselTrigger extends anomalyTrigger
{
	protected ref array<string>	m_HitZones;

	void KiselTrigger()
	{
		m_damageForItem = 15;
		m_HitZones = { "LeftLeg", "LeftFoot", "RightLeg", "RightFoot" };
		m_ExtentMin = "-1.5 -0.5 -1.5";
		m_ExtentMax = "1.5 1 1.5";
		m_isActive = true;
	}

	void ~KiselTrigger()
	{
		if (m_AnomalyObject) GetGame().ObjectDelete(m_AnomalyObject);
		if (m_AnomalyObjectActive) GetGame().ObjectDelete(m_AnomalyObjectActive);
	}
	
	override void OnEnter(Object obj)
	{
		if (!m_isActive)
		{
			m_isActive = true;
			anomalyActivate();
		}
		
		#ifdef DEBUG_ANOMALY
		Print("AnomalyKiselTrigger: " + obj + " entered");
		#endif
	}

	override void OnLeave(Object obj)
	{	
		#ifdef DEBUG_ANOMALY
		Print("AnomalyKiselTrigger: " + obj + " left");
		#endif
	}
		
	void anomalyActivate()
	{
		m_AnomalyObjectActive = SpawnAnomaly("Anomaly_Kisel_Active", m_AnomalyPosition);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.updateInsidersAndSetDamage, 0.3*1000);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.anomalyDeactivate, 1*1000);
		
		#ifdef DEBUG_ANOMALY
		Print("AnomalyKisel: Activated");
		#endif
	}
		
	void anomalyDeactivate()
	{
		if (m_AnomalyObjectActive) GetGame().ObjectDelete(m_AnomalyObjectActive);	
		if (m_insiders.Count() > 0)
		{
			anomalyActivate();
			
			#ifdef DEBUG_ANOMALY
			Print("AnomalyKisel: Reactivate");
			#endif
		}
		else
		{
			m_isActive = false;
			#ifdef DEBUG_ANOMALY
			Print("AnomalyKisel: Deactivated");
			#endif
		}
	}
	
	override void anomalySetDamage(Object obj)
	{
		super.anomalySetDamage(obj);
		obj.ProcessDirectDamage(DT_CUSTOM, this, GetRandomHitZone(m_HitZones), "MeleeDamage", "0.5 0.5 0.5", 4);
	}
	
	override void AddInsider(Object obj)
	{
		if( !obj.IsTransport() ) super.AddInsider(obj);
	}
	
	override void EOnInit(IEntity other, int extra)
	{
		SetExtents(m_ExtentMin, m_ExtentMax);
		m_AnomalyPosition = GetPosition();
		m_AnomalyObject = SpawnAnomaly("Anomaly_Kisel_Idle", m_AnomalyPosition);
		m_isActive = false;
	}
}