#define DETECTOR_RPC_MODE

class SA_Detector_Otklik; // Forward-Deklaration
class SA_Detector_Bear;   // Forward-Deklaration

modded class SA_Detector_Base
{
    const int COLOR = 0x1fF7CA78;
    protected static ref TParam2ArrayMap m_artefactData = new TParam2ArrayMap;
    
    TVectorArray GetArtefactPositions(TStringArray squaresNear, TStringArray allowedArtefacts)
    {
        TVectorArray m_targetPos = new TVectorArray;
        
        for(int i = 0; i < squaresNear.Count(); i++)
        {
            string m_square = squaresNear.Get(i);
            
            TParam2Array m_artefactsFromData;
            m_artefactData.Find(m_square, m_artefactsFromData);
            if (m_artefactsFromData)
            {
                for(int a = 0; a < m_artefactsFromData.Count(); a++)
                {
                    Param2<string, vector> m_curArtefactData = m_artefactsFromData.Get(a);
                    
                    string m_artefactName = m_curArtefactData.param1;
                    vector m_artefactPosition = m_curArtefactData.param2;
                    
                    if (allowedArtefacts.Find(m_artefactName) != -1)
                    {
                        m_targetPos.Insert(m_artefactPosition);
                    }
                }
            }
        }
        
        return m_targetPos;
    }
    
    float AngleBetween(vector vector1, vector vector2)
    {
        float m_angle = Math.Atan2(vector2[0] - vector1[0], vector2[2] - vector1[2]) * (180 / Math.PI);
        return Math.NormalizeAngle(m_angle);
    }
    
    static void SetArtefactData(TParam2ArrayMap arr)
    {
        m_artefactData = arr;
    }
    
    void SoundControllerServer(float time)
    {
        if (time != m_curSoundTime)
        {
            m_soundTime = time;
            m_curSoundTime = time;
            SetSynchDirty();
        }
    }

    void PlayBeepArtSoundRPC()
    {
        GetGame().RPCSingleParam(this, StalkerDetectors.BeepArtSound, NULL, true);
    }

    void OnWorkServer(vector position, float orientation) {}

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) 
    {
        super.OnRPC(sender, rpc_type, ctx);
        if (rpc_type == StalkerDetectors.SendPosDir)
        {
            vector m_positionRPC = GetPosition();
            float m_orientationRPC = GetOrientation()[0];
            Param1<vector> p1 = new Param1<vector>(m_positionRPC);
            Param1<float> p2 = new Param1<float>(m_orientationRPC);
                    
            if (ctx.Read(p1))
            {
                m_positionRPC = p1.param1;
            }
            if (ctx.Read(p2))
            {
                m_orientationRPC = p2.param1;
            }
            OnWorkServer(m_positionRPC, m_orientationRPC);
        }
    }
}