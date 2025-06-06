#define DETECTOR_RPC_MODE
modded class SA_Detector_Bear extends SA_Detector_Base
{
    const string LIGHT_LED = "StalkerDetectors\\data\\green_light.rvmat";
    const string RADAR_TEX = "StalkerDetectors\\data\\detector_bear\\radar\\radar_rotation";
    protected static ref TStringArray m_allowedArtefacts = new TStringArray;
    const int m_angleOffset = 15;
    const int m_animPhaseCount = 23;
    const float m_detectorRange = 25;
    protected bool m_radarState = false;
    
    #ifdef DETECTOR_RPC_MODE
    const float m_directionOffset = 90;
    const float m_artSpawnRange = 3;
    #else
    const float m_directionOffset = 155;
    const float m_artSpawnRange = 5;
    #endif
    
    #ifndef DETECTOR_RPC_MODE
    override void OnWork(float consumed_energy)
    {
        vector m_detectorPosition = GetPosition();
        vector m_detectorOrientation = GetOrientation();
        OnWorkServer(m_detectorPosition, m_detectorOrientation[0]);
    }
    #endif

    override void OnWorkServer(vector position, float orientation)
    {        
        vector m_detectorPosition = position;
        float m_detectorDirection = Math.NormalizeAngle(orientation + m_directionOffset);
        bool m_enableRadar = false;
        float m_beepTime = 0;
        
        TStringArray m_squaresNear = AnMath.GetNearSquaresOffset(m_detectorPosition, 1);
        TVectorArray m_targetPos = GetArtefactPositions(m_squaresNear, m_allowedArtefacts);
        
        if (m_targetPos.Count() > 0)
        {
            vector m_nearestPosition = NearestPosition(m_targetPos, m_detectorPosition);
            float m_distanceBetween = vector.Distance(m_nearestPosition, m_detectorPosition);
            
            if (m_distanceBetween <= m_detectorRange)
            {
                float m_directionToTarget = AngleBetween(m_detectorPosition, m_nearestPosition);
                float m_diffAngle = 360 - Math.NormalizeAngle(Math.DiffAngle(m_detectorDirection, m_directionToTarget));
                int m_angleNumber = Math.Floor(m_diffAngle / m_angleOffset);
                
                m_enableRadar = true;
                SetAnimationPhase("radar", m_angleNumber / m_animPhaseCount);
                
                if (m_distanceBetween <= m_artSpawnRange)
                {
                    PlayBeepArtSoundRPC();
                    ArtefactSpawner.InsertArtefactForSpawn(m_nearestPosition);
                }
                else
                {
                    m_beepTime = SetBeepTime(m_distanceBetween);
                }
            }
        }
        
        SoundControllerServer(m_beepTime);    
        EnableRadar(m_enableRadar);
    }
    
    override void OnWorkStart()
    {
        SetLightOn();
    }
    
    override void OnWorkStop()
    {
        SetLightOff();
        EnableRadar(false);
        SoundControllerServer(0);
    }
    
    vector NearestPosition(TVectorArray arr, vector toPos)
    {
        vector m_postition = vector.Zero;
        float m_minDist = m_detectorRange;
        
        for(int i = 0; i < arr.Count(); i++)
        {
            vector m_curPosition = arr.Get(i);
            float m_distanceBetween = vector.Distance(m_curPosition, toPos);
            
            if (m_distanceBetween <= m_detectorRange && m_distanceBetween < m_minDist)
            {
                m_minDist = m_distanceBetween;
                m_postition = m_curPosition;
            }
        }
        return m_postition;
    }
    
    static void SetAllowedArtefact(TStringArray arr)
    {
        m_allowedArtefacts = arr;
    }
    
    private void EnableRadar(bool state)
    {
        if (state && !m_radarState)
        {
            SetRadarOn();
            m_radarState = true;
        }
        else if (!state && m_radarState)
        {
            SetRadarOff();
            m_radarState = false;
        }
    }
    
    private void SetRadarOn()
    {
        SetObjectTexture(1, RADAR_TEX);
    }
    
    private void SetRadarOff()
    {
        SetObjectTexture(1, "");
    }
    
    private void SetLightOn()
    {
        SetObjectMaterial(0, LIGHT_LED);
    }
    
    private void SetLightOff()
    {
        SetObjectMaterial(0, "");
    }
    
    private float SetBeepTime(float dist)
    {
        float m_beepTime = 1.5;
        if (dist <= 20 && dist >= 15)
            m_beepTime = 1;
        else if (dist <= 15 && dist >= 10)
            m_beepTime = 0.7;
        else if (dist <= 10 && dist >= 7.5)
            m_beepTime = 0.6;
        else if (dist <= 7.5 && dist >= 5)
            m_beepTime = 0.5;
        else if (dist <= 5 && dist >= 4)
            m_beepTime = 0.4;
        else if (dist <= 4 && dist >= 3)
            m_beepTime = 0.3;
        else if (dist <= 3 && dist >= 2)
            m_beepTime = 0.2;
        else if (dist <= 2)
            m_beepTime = 0.1;
        
        return m_beepTime;
    }
}