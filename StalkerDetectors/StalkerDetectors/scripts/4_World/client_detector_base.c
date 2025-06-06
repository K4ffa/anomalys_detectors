#define DETECTOR_RPC_MODE_CLIENT

enum StalkerDetectors
{
    BeepArtSound = 12360,
    SendPosDir,
    ExtractArtifact
}

class SA_Detector_Base extends ItemBase
{
    protected ref OpenableBehaviour m_Openable;
    protected float m_soundTime;
    protected float m_curSoundTime;
    protected EffectSound m_BeepSound;
    protected EffectSound m_BeepArtSound;

    void SA_Detector_Base()
    {
        m_Openable = new OpenableBehaviour(false);
        RegisterNetSyncVariableBool("m_Openable.m_IsOpened");
        RegisterNetSyncVariableFloat("m_soundTime");
        UpdateVisualState();
    }
    
    override void OnWork(float consumed_energy)
    {
        if (GetGame().IsClient() || !GetGame().IsMultiplayer())
        {
            if (!IsOpen() || !GetCompEM().IsWorking())
                return;
            
            array<ref Param> m_params = new array<ref Param>;
            Param1<vector> p1 = new Param1<vector>(GetPosition());
            Param1<float> p2 = new Param1<float>(GetOrientation()[0]);
            m_params.Insert(p1);
            m_params.Insert(p2);
            
            GetGame().RPC(this, StalkerDetectors.SendPosDir, m_params, true);
        }
    }
    
    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        UpdateVisualState();
        
        if (GetGame().IsClient() || !GetGame().IsMultiplayer())
        {
            if (m_soundTime != m_curSoundTime)
                SoundController(m_soundTime);
        }
    }

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);
        switch(rpc_type)
        {
            case StalkerDetectors.BeepArtSound:
                BeepArtSound();
            break;
            case StalkerDetectors.ExtractArtifact:
                break;
        }
    }
    
    void SoundController(float time)
    {
        DisableBeepSound();
        if (time != 0)
            EnableBeepSound(time);
    }
    
    void EnableBeepSound(float time)
    {
        DisableBeepSound();
        if (time > 0)
        {
            if (m_soundTime > 0)
                PlaySoundSet(m_BeepArtSound, "Detector_Beep_Art_SoundSet", 0.1, 0.1, time * 1000);
            else
                PlaySoundSet(m_BeepSound, "Detector_Beep_SoundSet", 0.1, 0.1, time * 1000);
            m_curSoundTime = time;
        }
    }
    
    void DisableBeepSound()
    {
        if (m_BeepSound)
        {
            StopSoundSet(m_BeepSound);
            m_BeepSound = null;
        }
        if (m_BeepArtSound)
        {
            StopSoundSet(m_BeepArtSound);
            m_BeepArtSound = null;
        }
        m_curSoundTime = 0;
    }
    
    void BeepSound()
    {
        if (!m_BeepSound)
            PlaySoundSet(m_BeepSound, "Detector_Beep_SoundSet", 0.1, 0.1);
    }
    
    void BeepArtSound()
    {
        if (!m_BeepArtSound)
            PlaySoundSet(m_BeepArtSound, "Detector_Beep_Art_SoundSet", 0.1, 0.1);
    }
    
    override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner)
    {
        super.OnItemLocationChanged(old_owner, new_owner);
        if (GetCompEM().IsWorking())
            GetCompEM().SwitchOff();
        if (IsOpen())
            Close();
    }

    override void Open()
    {
        m_Openable.Open();
        SetSynchDirty();
        UpdateVisualState();
    }

    override void Close()
    {
        m_Openable.Close();
        SetSynchDirty();
        UpdateVisualState();
    }
    
    override bool IsOpen()
    {
        return m_Openable.IsOpened();
    }

    protected void UpdateVisualState()
    {
        SetAnimationPhase("cover", IsOpen() ? 1.0 : 0.0);
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionTurnOnDetectorWhileInHands);
        AddAction(ActionTurnOffDetectorWhileInHands);
        AddAction(ActionExtractArtifact);
    }
}