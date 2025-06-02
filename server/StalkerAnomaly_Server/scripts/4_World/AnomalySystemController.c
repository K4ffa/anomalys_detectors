class ASController
{
	//////////////////////////////////////////////////
	// Default Anomaly Parameters
	//////////////////////////////////////////////////
	
	// Enable Orientation
	static protected bool m_enableAnomalyOrientation;
	
	static bool enableAnomalyOrientation()
	{
		return m_enableAnomalyOrientation;
	}
	
	static void setAnomalyOrientation(bool state)
	{
		m_enableAnomalyOrientation = state;
	}
	
	
	// Debug Log
	static protected bool m_enableDebugLog;
	
	static bool enableDebugLog()
	{
		return m_enableDebugLog;
	}
	
	static void setDebugLog(bool state)
	{
		m_enableDebugLog = state;
	}
	
	// Anomaly Optimization
	static protected bool m_enableAnomalyOptimization;
	
	static bool enableAnomalyOptimization()
	{
		return m_enableAnomalyOptimization;
	}
	
	static void setAnomalyOptimization(bool state)
	{
		m_enableAnomalyOptimization = state;
	}
	
	// Anomaly Optimization
	static protected int m_spawnDistanceNearPlayer;
	
	static int spawnDistanceNearPlayer()
	{
		return m_spawnDistanceNearPlayer;
	}
	
	static void setSpawnDistanceNearPlayer(int value)
	{
		m_spawnDistanceNearPlayer = value;
	}
	
	// Anomaly Optimization Update Time
	static protected int m_anomalyOptimizationUpdateTime;
	
	static int anomalyOptimizationUpdateTime()
	{
		return m_anomalyOptimizationUpdateTime;
	}
	
	static void setAnomalyOptimizationUpdateTime(int value)
	{
		m_anomalyOptimizationUpdateTime = value;
	}
	
	//////////////////////////////////////////////////
	// Default Artefacts Parameters
	//////////////////////////////////////////////////
	
	// Anomaly Optimization Update Time
	static protected bool m_enableSpawnArtefacts;
	
	static bool enableSpawnArtefacts()
	{
		return m_enableSpawnArtefacts;
	}
	
	static void setSpawnArtefacts(bool state)
	{
		m_enableSpawnArtefacts = state;
	}
	
	//Artefacts Otklik
	static protected TStringArray m_artefactsOtklik;
	
	static TStringArray GetArtefactsOtklik()
	{
		return m_artefactsOtklik;
	}
	
	static void SetArtefactsOtklik(TStringArray artefacts)
	{
		m_artefactsOtklik = artefacts;
	}
	
	//Artefacts Bear
	static protected TStringArray m_artefactsBear;
	
	static TStringArray GetArtefactsBear()
	{
		return m_artefactsBear;
	}
	
	static void SetArtefactsBear(TStringArray artefacts)
	{
		m_artefactsBear = artefacts;
	}
}