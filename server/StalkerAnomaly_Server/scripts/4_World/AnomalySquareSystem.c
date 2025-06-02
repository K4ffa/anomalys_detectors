typedef map<string, ref TParam2Array>		TParam2ArrayMap;
typedef array<ref Param2<string, vector>>	TParam2Array;
typedef map<string, ref TClassArray>		TStringClassArrayMap;
typedef array<Man>							TManArray;

class AnomalySquareSystem
{
	static ref TParam2ArrayMap			m_anomalyData			= new TParam2ArrayMap;
	static ref TParam2ArrayMap			m_artefactData			= new TParam2ArrayMap;
	
	static void InsertAnomaly(string name, vector pos)
	{
		ref TParam2Array m_anomalyArray;
		
		string m_anomalySquare = AnMath.getSquareName(pos);
		m_anomalyData.Find(m_anomalySquare, m_anomalyArray);
		
		if (m_anomalyArray)
		{
			m_anomalyArray.Insert(new Param2<string, vector>(name, pos));
			m_anomalyData.Set(m_anomalySquare, m_anomalyArray);
		}
		else
		{
			m_anomalyArray = new TParam2Array;
			m_anomalyArray.Insert(new Param2<string, vector>(name, pos));
			m_anomalyData.Insert(m_anomalySquare, m_anomalyArray);
		}
	}
	
	static void InsertArtefact(string name, vector pos)
	{
		ref TParam2Array m_artefactArray;
		
		string m_anomalySquare = AnMath.getSquareName(pos);
		m_artefactData.Find(m_anomalySquare, m_artefactArray);
		
		if (m_artefactArray)
		{
			m_artefactArray.Insert(new Param2<string, vector>(name, pos));
			m_artefactData.Set(m_anomalySquare, m_artefactArray);
		}
		else
		{
			m_artefactArray = new TParam2Array;
			m_artefactArray.Insert(new Param2<string, vector>(name, pos));
			m_artefactData.Insert(m_anomalySquare, m_artefactArray);
		}
	}
	
	//get
	static TParam2ArrayMap getAnomalyData()
	{
		return m_anomalyData;
	}
	
	static TParam2ArrayMap getArtefactData()
	{
		return m_artefactData;
	}
}