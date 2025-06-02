class ElectraTrigger extends anomalyTrigger
{
	void ElectraTrigger()
	{
		m_damageForItem = 100;
		m_ExtentMin = "-2 -0.5 -2";
		m_ExtentMax = "2 2 2";
		m_isActive = true;
	}

	void ~ElectraTrigger()
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
		Print("AnomalyElectraTrigger: " + obj + " entered");
		#endif
	}

	override void OnLeave(Object obj)
	{	
		#ifdef DEBUG_ANOMALY
		Print("AnomalyElectraTrigger: " + obj + " left");
		#endif
	}
		
	void anomalyActivate()
	{
		if (m_AnomalyObject) GetGame().ObjectDelete(m_AnomalyObject);
		m_AnomalyObject = SpawnAnomaly("Anomaly_Electra_Active", m_AnomalyPosition);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.updateInsidersAndSetDamage, 0.3*1000);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.anomalyDeactivate, 3*1000);
		
		#ifdef DEBUG_ANOMALY
		Print("AnomalyElectra: Activated");
		#endif
	}
		
	void anomalyDeactivate()
	{
		if (m_AnomalyObject) GetGame().ObjectDelete(m_AnomalyObject);
		m_AnomalyObject = SpawnAnomaly("Anomaly_Electra_Idle", m_AnomalyPosition);		
		if (m_insiders.Count() > 0)
		{
			anomalyActivate();
			
			#ifdef DEBUG_ANOMALY
			Print("AnomalyElectra: Reactivate");
			#endif
		}
		else
		{
			m_isActive = false;
			
			#ifdef DEBUG_ANOMALY
			Print("AnomalyElectra: Deactivated");
			#endif
		}
	}
	
	override void anomalySetDamage(Object obj)
	{
		super.anomalySetDamage(obj);
		obj.SetHealth("", "Health", 0);
	}
	
	override void EOnInit(IEntity other, int extra)
	{
		SetExtents(m_ExtentMin, m_ExtentMax);
		m_AnomalyPosition = GetPosition();
		m_AnomalyObject = SpawnAnomaly("Anomaly_Electra_Idle", m_AnomalyPosition);
		m_isActive = false;
	}
}