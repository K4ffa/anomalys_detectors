#define DETECTOR_RPC_MODE
modded class SA_Detector_Otklik extends SA_Detector_Base
{
    const string LIGHT_LED = "StalkerDetectors\\data\\green_light.rvmat";
    const string LIGHT_LAMP = "StalkerDetectors\\data\\blue_light.rvmat";
    protected static ref TStringArray m_allowedArtefacts = new TStringArray;
    const float m_detectorRange = 12.5;
    const float m_workAngle = 30;
    protected bool m_lampState = false;
    
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
        bool m_enableLamp = false;
        float m_beepTime = 0;
        
        TStringArray m_squaresNear = AnMath.GetNearSquaresOffset(m_detectorPosition, 1);
        TVectorArray m_targetPos = GetArtefactPositions(m_squaresNear, m_allowedArtefacts);
        
        if (m_targetPos.Count() > 0)
        {
            vector m_nearestPosition = NearestPositionAhead(m_targetPos, m_detectorPosition, m_detectorDirection);
            float m_distanceBetween = vector.Distance(m_nearestPosition, m_detectorPosition);
            
            if (m_nearestPosition != vector.Zero)
            {
                if (m_distanceBetween <= m_artSpawnRange)
                {
                    PlayBeepArtSoundRPC();
                    ArtefactSpawner.InsertArtefactForSpawn(m_nearestPosition);
                }
                else
                {
                    m_beepTime = SetBeepTime(m_distanceBetween);
                }
                
                m_enableLamp = true;
            }
        }
        
        SoundControllerServer(m_beepTime);    
        EnableLamp(m_enableLamp);
    }
    
    override void OnWorkStart()
    {
        SetLightOn();
    }
    
    override void OnWorkStop()
    {
        SetLightOff();
        EnableLamp(false);
        SoundControllerServer(0);
    }
    
    vector NearestPositionAhead(TVectorArray arr, vector toPos, float dir)
    {
        vector m_postition = vector.Zero;
        float m_minDist = m_detectorRange;
        
        for(int i = 0; i < arr.Count(); i++)
        {
            vector m_curPosition = arr.Get(i);
            float m_distanceBetween = vector.Distance(m_curPosition, toPos);
            
            if (m_distanceBetween <= m_detectorRange && m_distanceBetween < m_minDist)
            {
                float m_directionToTarget = AngleBetween(toPos, m_curPosition);
                float m_diffAngle = Math.DiffAngle(dir, m_directionToTarget);
                if (m_diffAngle <= m_workAngle && m_diffAngle >= -m_workAngle)
                {
                    m_minDist = m_distanceBetween;
                    m_postition = m_curPosition;
                }
            }
        }
        return m_postition;
    }
    
    static void SetAllowedArtefact(TStringArray arr)
    {
        m_allowedArtefacts = arr;
    }
    
    private void EnableLamp(bool state)
    {
        if (state && !m_lampState)
        {
            SetLampOn();
            m_lampState = true;
        }
        else if (!state && m_lampState)
        {
            SetLampOff();
            m_lampState = false;
        }
    }
    
    private void SetLampOn()
    {
        SetObjectMaterial(1, LIGHT_LAMP);
    }
    
    private void SetLampOff()
    {
        SetObjectMaterial(1, "");
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
        float m_beepTime = 1;
        if (dist <= 11 && dist >= 10)
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