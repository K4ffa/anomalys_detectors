class Anomaly_Jarka_Idle extends House  
{
	ANOMALY_JARKA_IDLE_LIGHT	m_Light;
	Particle					m_AnomalyParticle;
	SoundOnVehicle				m_AnomalySound;
	
	void Anomaly_Jarka_Idle()
	{
		if ( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
			m_Light = ANOMALY_JARKA_IDLE_LIGHT.Cast( ScriptedLightBase.CreateLight(ANOMALY_JARKA_IDLE_LIGHT, "0 1 0", 0.5) );
			m_Light.AttachOnObject(this, "0 1 0", "0 0 0");
			m_AnomalySound = PlaySoundLoop("jarka_idle", 30);
			m_AnomalyParticle = Particle.PlayOnObject(ParticleList.ANOMALY_JARKA_IDLE, this);
		}
	}
	
	void ~Anomaly_Jarka_Idle()
	{
		if (m_AnomalyParticle) m_AnomalyParticle.Stop();
		if (m_Light) m_Light.FadeOut();
		if (m_AnomalySound) GetGame().ObjectDelete(m_AnomalySound);
 	}
}

class ANOMALY_JARKA_IDLE_LIGHT extends PointLightBase
{		
	void ANOMALY_JARKA_IDLE_LIGHT()
	{
		SetVisibleDuringDaylight(true);
		SetRadiusTo(6);
		SetBrightnessTo(0.4);
		SetCastShadow(false);
		SetFadeOutTime(3);
		SetDiffuseColor(0.9, 0.5, 0.3);
		SetAmbientColor(0.9, 0.5, 0.3);
		SetFlareVisible(false);
		SetFlickerAmplitude(0.7);
		SetFlickerSpeed(4.0);
		SetDancingShadowsMovementSpeed(0.4);
		SetDancingShadowsAmplitude(0.5);
	}
}