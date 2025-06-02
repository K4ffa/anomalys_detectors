class Anomaly_Teleport_Idle extends House  
{
	ANOMALY_TELEPORT_IDLE_LIGHT	m_Light;
	Particle					m_AnomalyParticle;
	SoundOnVehicle				m_AnomalySound;
	
	void Anomaly_Teleport_Idle()
	{
		if ( GetGame().IsClient()  ||  !GetGame().IsMultiplayer() )
		{
			m_Light = ANOMALY_TELEPORT_IDLE_LIGHT.Cast( ScriptedLightBase.CreateLight(ANOMALY_TELEPORT_IDLE_LIGHT, "0 1 0", 0.5) );
			m_Light.AttachOnObject(this, "0 1 0", "0 0 0");
			m_AnomalySound = PlaySoundLoop("teleport_idle", 30);
			m_AnomalyParticle = Particle.PlayOnObject(ParticleList.ANOMALY_TELEPORT_IDLE, this);
		}
	}
	
	void ~Anomaly_Teleport_Idle()
	{
		if (m_AnomalyParticle) m_AnomalyParticle.Stop();
		if (m_Light) m_Light.FadeOut();
		if (m_AnomalySound) GetGame().ObjectDelete(m_AnomalySound);
 	}
}

class ANOMALY_TELEPORT_IDLE_LIGHT extends PointLightBase
{		
	void ANOMALY_TELEPORT_IDLE_LIGHT()
	{
		SetVisibleDuringDaylight(true);
		SetRadiusTo(6);
		SetBrightnessTo(50);
		SetCastShadow(false);
		SetFadeOutTime(3);
		SetDiffuseColor(0.2, 0.5, 1.0);
		SetAmbientColor(0.2, 0.5, 1.0);
		SetFlareVisible(false);
		SetFlickerAmplitude(0.2);
		SetFlickerSpeed(10.0);
		SetDancingShadowsMovementSpeed(0.4);
		SetDancingShadowsAmplitude(0.5);
	}
}