//#define DEBUG_AOS
class AnomalyOptimizationSystem
{
	static private ref TStringClassArrayMap	m_activeAnomaly			= new TStringClassArrayMap;
	static private ref TStringArray			m_activesSuaresArray	= new TStringArray;
	
	static private ref TParam2ArrayMap		m_anomalyData;
	
	static private int		m_spawnDistanceNearPlayer;
	static private bool		m_enableAnomalyOrientation;
	static private int		m_updateTime;
	
	static void enableAnomalyOptimizationSystem()
    {
		if (ASController.enableDebugLog()) Print("[AnomalyOptimizationSystem] Started");
		
		m_spawnDistanceNearPlayer = ASController.spawnDistanceNearPlayer();
		m_enableAnomalyOrientation = ASController.enableAnomalyOrientation();
		m_updateTime =	ASController.anomalyOptimizationUpdateTime();
		
		m_anomalyData = AnomalySquareSystem.getAnomalyData();
		
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(AnomalyUpdate, m_updateTime*1000, true);
    }
	
	static private void AnomalyUpdate()
    {
		#ifdef DEBUG_AOS
		Print("[AnomalyOptimizationSystem] Updated");
		#endif
		
		TManArray m_players = new TManArray;
        GetGame().GetPlayers(m_players);
		TStringArray m_squaresArray = new TStringArray;
		
		if (m_players.Count() != 0)
		{
			//Get squares near players
			int m_playersCount = m_players.Count();
			for(int i = 0; i < m_playersCount; i++)
			{
				Man m_currentPlayer = m_players.Get(i);
				if (m_currentPlayer)
				{
					vector m_position = m_currentPlayer.GetPosition();
					TStringArray m_curSquaresArray = AnMath.getNearSquares(m_position, m_spawnDistanceNearPlayer);
					
					for(int n = 0; n < m_curSquaresArray.Count(); n++)
					{
						string m_value = m_curSquaresArray.Get(n);
						if (m_squaresArray.Find(m_value) == -1) m_squaresArray.Insert(m_value);
					}
				}
			}
			
			//Delete Anomaly
			if (m_activeAnomaly.Count() > 0)
			{
				for(int c = 0; c < m_activeAnomaly.Count(); c++)
				{
					string m_key = m_activeAnomaly.GetKey(c);
					if (m_squaresArray.Find(m_key) == -1)
					{
						TClassArray m_anomalyArray = m_activeAnomaly.GetElement(c);
						int m_anomalyCount = m_anomalyArray.Count();
						for(int d = 0; d < m_anomalyCount; d++)
						{
							Object m_anomalyObject = Object.Cast(m_anomalyArray.Get(d));
							GetGame().ObjectDelete(m_anomalyObject);
						}
						m_activeAnomaly.RemoveElement(c);
						c--;
					}
				}
			}
			
			int m_squaresCount = m_squaresArray.Count();
			if (m_squaresCount > 0)
			{
				for(int a = 0; a < m_squaresCount; a++)
				{
					string m_square = m_squaresArray.Get(a);
					if (m_activesSuaresArray.Find(m_square) == -1)
					{
						TParam2Array m_anomalyFromData;
						m_anomalyData.Find(m_square, m_anomalyFromData);
						if (m_anomalyFromData)
						{
							TClassArray m_anomalyObjects = new TClassArray;
							int m_afdCount = m_anomalyFromData.Count();
							for(int e = 0; e < m_afdCount; e++)
							{
								Param2<string, vector> m_curAnomalyData = m_anomalyFromData.Get(e);
								string m_anomalyName = m_curAnomalyData.param1;
								vector m_anomalyPosition = m_curAnomalyData.param2;
								
								anomalyTrigger m_createdAnomaly = createAnomalyTrigger(m_anomalyPosition, m_anomalyName);
								m_anomalyObjects.Insert(m_createdAnomaly);
							}
							m_activeAnomaly.Insert(m_square, m_anomalyObjects);
						}
					}
				}
			}
			
			//set
			m_activesSuaresArray = m_squaresArray;
		}
    }
	
	static private anomalyTrigger createAnomalyTrigger(vector position, string name)
	{
		anomalyTrigger m_anomalyObject = anomalyTrigger.Cast(GetGame().CreateObject( name + "Trigger", position, true, false, false));		
		if (m_enableAnomalyOrientation)
		{
			float m_height = GetGame().SurfaceY(position[0], position[2]);
			float m_diff = position[1] - m_height;
			if (m_diff < 0.1)
			{
				vector m_surfaceOrientation = GetGame().GetSurfaceOrientation(position[0], position[2]);
				m_anomalyObject.SetOrientation(m_surfaceOrientation);
				m_anomalyObject.updateRotation();
			}
		}
		
		return m_anomalyObject;
	}
}