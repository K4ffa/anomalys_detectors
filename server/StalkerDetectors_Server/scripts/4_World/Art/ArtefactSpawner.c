class ArtefactSpawner
{
	static protected ref TVectorArray		m_positionQueue	= new TVectorArray;
	static protected ref TParam2ArrayMap	m_artefactData	= new TParam2ArrayMap;
	static protected float m_SpawnDistance_Min = 3;
	static protected float m_SpawnDistance_Max = 7;
	
	static void Initialization()
	{
		m_artefactData = AnomalySquareSystem.getArtefactData();
		
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(ArtSpawner, 100, true);
	}
	
	static void InsertArtefactForSpawn(vector pos)
	{
		m_positionQueue.Insert(pos);
	}
	
	static private void ArtSpawner()
	{
		if( m_positionQueue.Count() > 0 )
		{
			vector m_position = m_positionQueue.Get(0);
			string m_square = AnMath.getSquareName(m_position);
			
			ref TParam2Array m_artefactArray;
			m_artefactData.Find(m_square, m_artefactArray);
	
			if (m_artefactArray)
			{
				for(int i = 0; i < m_artefactArray.Count(); i++)
				{
					Param2<string, vector> m_data = m_artefactArray.Get(i);
					if (m_data.param2 == m_position)
					{
						m_artefactArray.Remove(i);
						SpawnArtefact(m_data.param1, m_data.param2);
						break;
					}	
				}
			}
			
			//Remove zero index
			m_positionQueue.Remove(0);
		}
	}
	
	static private void SpawnArtefact(string name, vector pos)
	{			
		vector m_position = AnomalySpawner.getRandomPositionInCircleMinMaxRange(pos, m_SpawnDistance_Min, m_SpawnDistance_Max);
		AnomalySpawner.createObject(name, m_position);
	}
}