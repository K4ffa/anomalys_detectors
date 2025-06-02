class Anomaly_Teleport_Active extends House  
{
	ANOMALY_TELEPORT_ACTIVE_LIGHT	m_Light;
	Particle					m_AnomalyParticle;
	SoundOnVehicle				m_AnomalySound;
	
	void Anomaly_Teleport_Active()
	{
		if ( GetGame().IsClient()  ||  !GetGame().IsMultiplayer() )
		{
			m_Light = ANOMALY_TELEPORT_ACTIVE_LIGHT.Cast( ScriptedLightBase.CreateLight(ANOMALY_TELEPORT_ACTIVE_LIGHT, "0 1 0", 0.5) );
			m_Light.AttachOnObject(this, "0 1 0", "0 0 0");
			m_AnomalySound = PlaySoundLoop("teleport_active2", 50);
			m_AnomalyParticle = Particle.PlayOnObject(ParticleList.ANOMALY_TELEPORT_ACTIVE, this);
		}
	}
	
	void ~Anomaly_Teleport_Active()
	{
		if (m_AnomalyParticle) m_AnomalyParticle.Stop();
		if (m_Light) m_Light.FadeOut();
		if (m_AnomalySound) GetGame().ObjectDelete(m_AnomalySound);
 	}
}

class ANOMALY_TELEPORT_ACTIVE_LIGHT extends PointLightBase
{		
	void ANOMALY_TELEPORT_ACTIVE_LIGHT()
	{
		SetVisibleDuringDaylight(true);
		SetRadiusTo(25);
		SetLifetime(5);
		SetBrightnessTo(100);
		SetCastShadow(false);
		SetFadeOutTime(0.2);
		SetDiffuseColor(0.2, 0.5, 1.0);
		SetAmbientColor(0.2, 0.5, 1.0);
		SetFlareVisible(false);
		SetFlickerAmplitude(0.2);
		SetFlickerSpeed(10.0);
		SetDancingShadowsMovementSpeed(0.4);
		SetDancingShadowsAmplitude(0.5);
	}
}