class AnomalySpawner
{
	//Json Settings
	protected bool			enableAnomalyOptimization;
	protected int			worldSizeX;
	protected int			worldSizeY;
	protected int			spawnDistanceNearPlayer;
	protected int			updateTime;
	protected bool			enableDebugLog;
	protected bool			enableAnomalyOrientation;
	protected bool			enableSpawnArtefacts;
	protected int			spawnArtefactsType;
	protected TStringArray	Artefacts_Otklik;
	protected TStringArray	Artefacts_Bear;
	protected ref array<ref AnomalySpawner_teleportAnomaly>	teleportAnomaly;
	protected ref array<ref AnomalySpawner_staticAnomaly>	staticAnomaly;
	protected ref array<ref AnomalySpawner_dynamicAnomaly>	dynamicAnomaly;
	protected ref array<ref ArtefactsSpawnDataStatic>		ArtefactsSpawnData;
	//Start
	const protected string m_ProfilePath = "$profile:";
	const protected string m_ConfigFolderName = "AnomalySpawner";
	const protected string m_ConfigName = "anomalySpawnerConfig.json";
	const protected ref TStringArray m_AnomalyList = { "Jarka", "Electra", "Kisel", "Tramplin", "Par" };
	
	void AnomalySpawner()
	{
		bool m_isConfigLoaded = loadConfig();
        if (m_isConfigLoaded)
        {
			setupParametersToController();
			
            Print("[AnomalySpawner] Anomalies Spawn Started");
            if (enableDebugLog) float m_debugTime = GetGame().GetTickTime();
			AnMath.InitializeMath(worldSizeX, worldSizeY);
            createStaticAnomalies();
            createDynamicAnomalies();
            createTeleportAnomalies();
            if (enableDebugLog)
            {
                float m_debugTimeEnd = GetGame().GetTickTime();
                PrintFormat("[AnomalySpawner] Time spent spawn: %1. Start: %2 End: %3", (m_debugTimeEnd - m_debugTime), m_debugTime, m_debugTimeEnd);
            }
            Print("[AnomalySpawner] All anomalies spawned.");
        }
	}
	
	private bool loadConfig()
	{		
		if (FileExist(m_ProfilePath + m_ConfigFolderName + "/" + m_ConfigName))
        {
            JsonFileLoader<AnomalySpawner>.JsonLoadFile(m_ProfilePath + m_ConfigFolderName + "/" + m_ConfigName, this);
			if (enableDebugLog)	Print("[AnomalySpawner] Json Initialized");
            return true;
        }
        else
        {
            Print("[AnomalySpawner] Json does not exist.");
            Print("[AnomalySpawner] Please put the config on the path: DayZServer\profiles\AnomalySpawner\anomalySpawnerConfig.json");
            return false;
        }
	}
	
	private void setupParametersToController()
	{
		ASController.setDebugLog(enableDebugLog);
		ASController.setAnomalyOrientation(enableAnomalyOrientation);
		ASController.setAnomalyOptimization(enableAnomalyOptimization);
		ASController.setSpawnDistanceNearPlayer(spawnDistanceNearPlayer);
		ASController.setAnomalyOptimizationUpdateTime(updateTime);
		ASController.setSpawnArtefacts(enableSpawnArtefacts);
		ASController.SetArtefactsOtklik(Artefacts_Otklik);
		ASController.SetArtefactsBear(Artefacts_Bear);
	}
	
	private void createStaticAnomalies()
	{
        if (staticAnomaly.Count() > 0)
        {
            for(int n = 0; n < staticAnomaly.Count(); n++)
            {
                AnomalySpawner_staticAnomaly m_currentArray = staticAnomaly.Get(n);
                string m_anomalyName = m_currentArray.anomalyName;
                TVectorArray m_positionArray = m_currentArray.anomalyPosition;
                if (m_AnomalyList.Find(m_anomalyName) != -1)
                {
                    for(int i = 0; i < m_positionArray.Count(); i++)
                    {
                        vector m_anomalyPosition = m_positionArray.Get(i);
                        spawnAnomaly(m_anomalyPosition, m_anomalyName);
						
						//Artefact Creator
						if (enableSpawnArtefacts)
						{
							artefactCreator(m_anomalyName, m_anomalyPosition, m_currentArray.ArtefactsWithoutDetector, m_currentArray.ArtefactsWithDetector);
						}
                    }
                }
                else
                {
                    Print("[AnomalySpawner] Error: Bad Anomaly Name: " + m_anomalyName);
                }
            }
        }
	}
	
	private void createDynamicAnomalies()
	{
        if (dynamicAnomaly.Count() > 0)
        {
            for(int n = 0; n < dynamicAnomaly.Count(); n++)
            {
                AnomalySpawner_dynamicAnomaly		m_currentArray 	= dynamicAnomaly.Get(n);
                array<ref AnomalySpawner_anomalyData>	m_anomalyData 	= m_currentArray.anomalyData;
                TVectorArray m_spawnPositions = new TVectorArray;
                TStringArray m_anomalyList = new TStringArray;
                
                for(int i = 0; i < m_anomalyData.Count(); i++)
                {
                    AnomalySpawner_anomalyData m_curentAnomalyData = m_anomalyData.Get(i);
                    string 	m_anomalyName = m_curentAnomalyData.anomalyName;
                    int 	m_anomalyCount = m_curentAnomalyData.anomalyCount;
                    
                    if (m_AnomalyList.Find(m_anomalyName) != -1)
                    {
                        string	m_zoneType = 			m_currentArray.zoneType;
                        vector	m_zonePosition = 		m_currentArray.zonePosition;
                        int		m_zoneRadius = 			m_currentArray.zoneRadius;
                        int		m_distanceBTWAnomaly =	m_currentArray.distanceBTWAnomaly;
                        bool	m_checkGeometry = 		m_currentArray.checkGeometry;
                        
                        //Create Spawn Positions
                        createSpawnPositions(m_zonePosition, m_zoneRadius, m_anomalyCount, m_zoneType, m_distanceBTWAnomaly, m_spawnPositions, m_checkGeometry);
                        
                        //Fill Array
                        for(int k = 0; k < m_anomalyCount; k++)
                        {
                            m_anomalyList.Insert(m_anomalyName);
                        }
                    }
                    else
                    {
                        Print("[AnomalySpawner] Error: Bad Anomaly Name: " + m_anomalyName);
                    }
                }
                
                if(m_spawnPositions.Count() > 0)
                {
                    for(int c = 0; c < m_spawnPositions.Count(); c++)
                    {
                        vector m_anomalyPosition = m_spawnPositions.Get(c);
                        int m_index = m_anomalyList.GetRandomIndex();
                        string m_randomAnomaly = m_anomalyList.Get(m_index);
                        m_anomalyList.Remove(m_index);
                        spawnAnomaly(m_anomalyPosition, m_randomAnomaly);
						
						//Artefact Creator
						if (enableSpawnArtefacts)
						{
							for(int a = 0; a < m_anomalyData.Count(); a++)
			                {
			                    AnomalySpawner_anomalyData m_curentAnomalyDataArt = m_anomalyData.Get(a);
			                    string 	m_anomalyNameArt = m_curentAnomalyDataArt.anomalyName;
			                    
			                    if (m_randomAnomaly == m_anomalyNameArt)
			                    {
			                        artefactCreator(m_randomAnomaly, m_anomalyPosition, m_curentAnomalyDataArt.ArtefactsWithoutDetector, m_curentAnomalyDataArt.ArtefactsWithDetector);
									break;
			                    }
			                }
						}
                    }
                }
            }
        }
	}
	
	private void createTeleportAnomalies()
	{
        if (teleportAnomaly.Count() > 0)
        {
            for(int n = 0; n < teleportAnomaly.Count(); n++)
            {
                AnomalySpawner_teleportAnomaly m_currentArray = teleportAnomaly.Get(n);
                vector m_anomalyPosition = m_currentArray.anomalyPosition;
                bool m_teleportType = m_currentArray.teleportType;
                TVectorArray m_positionArray = m_currentArray.teleportToPositions;
                
                TeleportTrigger m_anomalyObject = TeleportTrigger.Cast(GetGame().CreateObject( "TeleportTrigger", m_anomalyPosition, true, false, false));
				if (m_anomalyObject)
				{
	                if (m_teleportType)
	                {
	                    vector m_tempPosition = m_positionArray.GetRandomElement();
	                    m_positionArray.Clear();
	                    m_positionArray.Insert(m_tempPosition);
	                }
	                m_anomalyObject.setTeleportPosition(m_positionArray);
					
					//Artefact Creator
					if (enableSpawnArtefacts)
					{
						artefactCreator("Teleport", m_anomalyPosition, m_currentArray.ArtefactsWithoutDetector, m_currentArray.ArtefactsWithDetector);
					}
	
	                if (enableDebugLog)	Print("[AnomalySpawner] Teleport Anomaly spawned on position: " + m_anomalyPosition);
				}
            }
        }
	}
	
	
	private void spawnAnomaly(vector position, string name)
	{
		bool m_isOutside = false;
		float m_posX = position[0];
		float m_posY = position[2];
		if (m_posX < 0 || m_posY < 0) m_isOutside = true;
		if (m_posX > worldSizeX || m_posY > worldSizeY) m_isOutside = true;
		
		if (!enableAnomalyOptimization || m_isOutside)
		{
			createAnomalyTrigger(position, name);
		}
		
		if (!m_isOutside)
		{
			AnomalySquareSystem.InsertAnomaly(name, position);
		}
	}
	
	private void createAnomalyTrigger(vector position, string name)
	{
		anomalyTrigger m_anomalyObject = anomalyTrigger.Cast(GetGame().CreateObject( name + "Trigger", position, true, false, false));		
		if (m_anomalyObject && enableAnomalyOrientation)
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
		
		if (enableDebugLog)	Print("[AnomalySpawner] Anomaly: " + name + " Spawned on position: " + position);
	}
	
	//Artefacts
	private void createArtefactWithDetectorStatic(string anomalyName, vector pos)
	{
		//Artefacts With Detector Static
		for(int i = 0; i < ArtefactsSpawnData.Count(); i++)
		{
			ArtefactsSpawnDataStatic m_currentArray = ArtefactsSpawnData.Get(i);
			if (m_currentArray.AnomalyName == anomalyName)
			{
				float m_spawnChance = m_currentArray.SpawnChancePercent;
				float m_random = Math.RandomFloat(0, 100);
				if (m_random <= m_spawnChance)
				{
					array<ref ArtefactsDataStatic> m_artefactsata = m_currentArray.ArtefactsData;
					TStringArray m_artefacts = new TStringArray;
					for(int a = 0; a < m_artefactsata.Count(); a++)
					{
						ArtefactsDataStatic m_artefactData = m_artefactsata.Get(a);
						int m_artChance = m_artefactData.ArtefactSpawnChancePercent;
						string m_artName = m_artefactData.ArtefactClassName;
						for(int b = 0; b < m_artChance; b++)
						{
							m_artefacts.Insert(m_artName);
						}
					}
					
					int m_randomSelectr = Math.RandomInt(0, (m_artefacts.Count() - 1));
					string m_selectArt = m_artefacts.Get(m_randomSelectr);
					
					//Insert Artefact to Square System
					if (m_selectArt.Trim() != "")
					{
						AnomalySquareSystem.InsertArtefact(m_selectArt, pos);
						if (enableDebugLog) Print("[ArtefactsSpawner] Artefact was created! ClassName: " + m_selectArt + " Position: " + pos);
					}
				}
			}
		}
	}
	
	private void createArtefactWithDetectorDynamic(vector pos, ArtefactsWithDetectorDynamic m_artefactsWithDetector)
	{
		//Artefacts With Detector Dynamic
		float m_chance = m_artefactsWithDetector.SpawnChancePercent;
		float m_random = Math.RandomFloat(0, 100);
		if (m_random <= m_chance)
		{
			array<ref ArtefactsWithDetectorDynamic_Data> m_artefactsata = m_artefactsWithDetector.ArtefactsData;
			TStringArray m_artefacts = new TStringArray;
			for(int i = 0; i < m_artefactsata.Count(); i++)
			{
				ArtefactsWithDetectorDynamic_Data m_artefactData = m_artefactsata.Get(i);
				int m_artChance = m_artefactData.ArtefactSpawnChancePercent;
				string m_artName = m_artefactData.ArtefactClassName;
				for(int a = 0; a < m_artChance; a++)
				{
					m_artefacts.Insert(m_artName);
				}
			}
			
			int m_randomSelect = Math.RandomInt(0, (m_artefacts.Count() - 1));
			string m_selectArt = m_artefacts.Get(m_randomSelect);
			
			//Insert Artefact to Square System
			if (m_selectArt.Trim() != "")
			{
				AnomalySquareSystem.InsertArtefact(m_selectArt, pos);
				if(enableDebugLog) Print("[ArtefactsSpawner] Artefact was created! ClassName: " + m_selectArt + " Position: " + pos);
			}
		}
	}
	
	private void createArtefactWithoutDetector(vector pos, ArtefactsWithoutDetectorDynamic m_artefactsWithoutDetector)
	{
		float m_spawnChancePercent = m_artefactsWithoutDetector.SpawnChancePercent;
		if (m_spawnChancePercent > 0)
		{
			float m_random = Math.RandomFloat(0, 100);
			if (m_random <= m_spawnChancePercent)
			{
				array<ref ArtefactsWithoutDetectorDynamic_Data> m_artefactsata = m_artefactsWithoutDetector.ArtefactsData;
				TStringArray m_artefacts = new TStringArray;
				for(int i = 0; i < m_artefactsata.Count(); i++)
				{
					ArtefactsWithoutDetectorDynamic_Data m_artefactData = m_artefactsata.Get(i);
					int m_artChance = m_artefactData.ArtefactSpawnChancePercent;
					string m_artName = m_artefactData.ArtefactClassName;
					for(int a = 0; a < m_artChance; a++)
					{
						m_artefacts.Insert(m_artName);
					}
				}
				
				int m_randomSelect = Math.RandomInt(0, (m_artefacts.Count() - 1));
				string m_selectArt = m_artefacts.Get(m_randomSelect);
				
				//Spawn Artefact
				if (m_selectArt.Trim() != "")
				{
					float m_spawnDistance_Min = m_artefactsWithoutDetector.SpawnDistance_Min;
					float m_spawnDistance_Max = m_artefactsWithoutDetector.SpawnDistance_Max;
					
					vector m_position = getRandomPositionInCircleMinMaxRange(pos, m_spawnDistance_Min, m_spawnDistance_Max);
					Object m_artefactObject = createObject(m_selectArt, m_position);
					
					if(enableDebugLog) Print("[ArtefactsSpawner] Artefact was spawned! ClassName: " + m_selectArt + " Position: " + m_position);
				}
			}
		}
	}
	
	private void artefactCreator(string anomalyName, vector pos, ArtefactsWithoutDetectorDynamic m_artefactsWithoutDetector, ArtefactsWithDetectorDynamic m_artefactsWithDetector)
	{
		float m_withDetectorSCP = m_artefactsWithDetector.SpawnChancePercent;
		
		if (spawnArtefactsType == 0 || ( spawnArtefactsType == 2 && m_withDetectorSCP == 0 ) )
		{
			//Artefacts With Detector Static
			createArtefactWithDetectorStatic(anomalyName, pos);
		}
		
		if (spawnArtefactsType == 1 || (spawnArtefactsType == 2 && m_withDetectorSCP > 0 ) )
		{
			//Artefacts With Detector Dynamic
			createArtefactWithDetectorDynamic(pos, m_artefactsWithDetector);
		}
		
		//Artefacts Without Detector
		createArtefactWithoutDetector(pos, m_artefactsWithoutDetector);
	}
	
	
	//Helper methods
	static Object createObject(string type, vector position)
	{
		Object obj = GetGame().CreateObject( type, position);
		if (obj)
		{
		    obj.SetPosition( position );
			obj.PlaceOnSurface();
			obj.SetOrientation(obj.GetOrientation());
		    obj.Update();
		}
		else
		{
			Print("[ArtefactSpawner] Artefact with Classname <" + type + "> does not exist.");
		}
		
		return obj;
	}
	
	private void createSpawnPositions(vector position, int radius, int count, string type, int dist, TVectorArray m_spawnPositions, bool geomCheck)
	{
		int m_maxTry;
		for(int n = 0; n < count;)
		{
			vector m_foundPosition;
			bool m_validPosition = true;
			
			if (type == "Box") m_foundPosition = getRandomPositionInBox(position, radius);
			if (type != "Box") m_foundPosition = getRandomPositionInCircle(position, radius);
			
			//Geometry Check
			//if (geomCheck) if (IsCollidingBox(m_foundPosition)) m_validPosition = false;
			if (geomCheck) if (RayCastCheck(m_foundPosition)) m_validPosition = false;
			
			//Water Check
			if (isWaterSurface(m_foundPosition)) m_validPosition = false;
			
			if (m_validPosition)
			{
				for(int i = 0; i < m_spawnPositions.Count(); i++)
				{
					vector	m_curPosition = m_spawnPositions.Get(i);
					float	m_betweenDistance = vector.Distance(m_curPosition, m_foundPosition);
					if ( m_betweenDistance < dist )
					{
						m_validPosition = false;
						break;
					}
				}
			}
			
			if (m_validPosition)
			{
				m_spawnPositions.Insert(m_foundPosition);
				m_maxTry = 0;
				n++;
			}
			
			if (m_maxTry > 1000)
			{
				Print("[AnomalySpawner] Search interval exceeded");
				break;
			}
			m_maxTry++;
		}
	}
	
	static bool isWaterSurface(vector pos)
	{
		if( GetGame().SurfaceIsSea( pos[0], pos[2] ) )
		{
			return true;
		}
		else if( GetGame().SurfaceIsPond( pos[0], pos[2] ) )
		{
			return true;
		}
		return false;
	}
	
	private bool RayCastCheck(vector pos)
	{
		float m_height = pos[1] + 1;
		vector m_startPos = pos;
		vector m_endPos = Vector(pos[0], (pos[1] + 30), pos[2]);
		vector m_ray1 = Vector((pos[0] - 1.5), m_height, (pos[2] - 1.5));
		vector m_ray2 = Vector((pos[0] + 1.5), m_height, (pos[2] + 1.5));
		vector m_ray3 = Vector((pos[0] + 1.5), m_height, (pos[2] - 1.5));
		vector m_ray4 = Vector((pos[0] - 1.5), m_height, (pos[2] + 1.5));
		vector contactPos;
		vector contactDir;
		int contactComponent;
		set<Object> results0 = new set<Object>;
		set<Object> results1 = new set<Object>;
		set<Object> results2 = new set<Object>;
		set<Object> results3 = new set<Object>;
		set<Object> results4 = new set<Object>;
		set<Object> results5 = new set<Object>;
		
		//Center
		if (DayZPhysics.RaycastRV(m_startPos, m_endPos, contactPos, contactDir, contactComponent, results0) && results0.Count() && !results0[0].IsTree() && !results0[0].IsBush()) return true;
		if (DayZPhysics.RaycastRV(m_endPos, pos, contactPos, contactDir, contactComponent, results1) && results1.Count() && !results1[0].IsTree() && !results1[0].IsBush()) return true;
		//Edge
		if (DayZPhysics.RaycastRV(m_ray1, m_ray3, contactPos, contactDir, contactComponent, results2) && results2.Count() && !results2[0].IsTree() && !results2[0].IsRock() && !results2[0].IsBush()) return true;
		if (DayZPhysics.RaycastRV(m_ray1, m_ray4, contactPos, contactDir, contactComponent, results3) && results3.Count() && !results3[0].IsTree() && !results3[0].IsRock() && !results3[0].IsBush()) return true;
		if (DayZPhysics.RaycastRV(m_ray4, m_ray2, contactPos, contactDir, contactComponent, results4) && results4.Count() && !results4[0].IsTree() && !results4[0].IsRock() && !results4[0].IsBush()) return true;
		if (DayZPhysics.RaycastRV(m_ray2, m_ray3, contactPos, contactDir, contactComponent, results5) && results5.Count() && !results5[0].IsTree() && !results5[0].IsRock() && !results5[0].IsBush()) return true;
		
		return false;
	}
	
	private vector GetCollisionBoxSize( vector min_max[2] )
	{
		vector box_size = Vector(1,1,1);
		
		box_size[0] = min_max[1][0] - min_max[0][0];
		box_size[2] = min_max[1][2] - min_max[0][2];
		box_size[1] = min_max[1][1] - min_max[0][1];
		
		return box_size;
	}
	
	private bool IsCollidingBox(vector pos)
	{
		vector center;
		vector relative_ofset; //we need to lift BBox, because it is calculated from the bottom of projection, and not from the middle
		vector orientation = "0 0 -0";
		vector edge_length;
		vector min_max[2];
		ref array<Object> excluded_objects = new array<Object>;
		ref array<Object> collided_objects = new array<Object>;
		
		min_max[0] = "-2 -0.2 2";
		min_max[1] = "2 2 2";
		relative_ofset[1] = ( min_max[1][1] - min_max[0][1] ) / 2;
		center = pos + relative_ofset;
		edge_length = GetCollisionBoxSize( min_max );

		bool isTrue = GetGame().IsBoxColliding( center, orientation, edge_length, excluded_objects, collided_objects );
		if (isTrue)
		{
			for(int i = 0; i < collided_objects.Count(); i++)
			{
				if (collided_objects.Get(i).IsBuilding()) return true;
			}
		}
		return false;
	}
	
	static vector getRandomPositionInCircle(vector position, int radius)
    {
        float m_varA = Math.RandomFloatInclusive(0,1) * 2 * Math.PI;
        float m_varR = radius * Math.Sqrt(Math.RandomFloatInclusive(0, 1));
        float m_offsetX = m_varR * Math.Cos(m_varA);
        float m_offsetY = m_varR * Math.Sin(m_varA);
        vector m_randomPosition = Vector(position[0] + m_offsetX, 0, position[2] + m_offsetY);
        m_randomPosition[1] = GetGame().SurfaceY(m_randomPosition[0], m_randomPosition[2]);
        return m_randomPosition;
    }
    
    static vector getRandomPositionInCircleMinMaxRange(vector position, int min, int max)
    {
        float m_varA = Math.RandomFloatInclusive(0,1) * 2 * Math.PI;
        float m_varR = Math.RandomFloatInclusive(min, max);
        float m_offsetX = m_varR * Math.Cos(m_varA);
        float m_offsetY = m_varR * Math.Sin(m_varA);
        vector m_randomPosition = Vector(position[0] + m_offsetX, 0, position[2] + m_offsetY);
        m_randomPosition[1] = GetGame().SurfaceY(m_randomPosition[0], m_randomPosition[2]);
        return m_randomPosition;
    }
    
    static vector getRandomPositionInBox(vector position, int radius)
    {
        float m_min = -radius;
        float m_max = radius;
        float m_offsetX = position[0] + Math.RandomFloatInclusive(m_min, m_max);
        float m_offsetY = position[2] + Math.RandomFloatInclusive(m_min, m_max);
        vector m_randomPosition = Vector(m_offsetX, 0, m_offsetY);
        m_randomPosition[1] = GetGame().SurfaceY(m_randomPosition[0], m_randomPosition[2]);
        return m_randomPosition;
    }
}