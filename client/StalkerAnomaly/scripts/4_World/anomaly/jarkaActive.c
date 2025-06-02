class Anomaly_Jarka_Active extends House  
{
	ANOMALY_JARKA_ACTIVE_LIGHT	m_Light;
	Particle					m_AnomalyParticle;
	SoundOnVehicle				m_AnomalySound;
	
	void Anomaly_Jarka_Active()
	{
		if ( GetGame().IsClient()  ||  !GetGame().IsMultiplayer() )
		{
			m_Light = ANOMALY_JARKA_ACTIVE_LIGHT.Cast( ScriptedLightBase.CreateLight(ANOMALY_JARKA_ACTIVE_LIGHT, "0 2 0", 0.5) );
			m_Light.AttachOnObject(this, "0 2 0", "0 0 0");
			m_AnomalySound = PlaySound("jarka_active", 100);
			m_AnomalyParticle = Particle.PlayOnObject(ParticleList.ANOMALY_JARKA_ACTIVE, this);
		}
	}
	
	void ~Anomaly_Jarka_Active()
	{
		if (m_AnomalyParticle) m_AnomalyParticle.Stop();
		if (m_Light) m_Light.FadeOut();
		if (m_AnomalySound) GetGame().ObjectDelete(m_AnomalySound);
 	}
}

class ANOMALY_JARKA_ACTIVE_LIGHT extends PointLightBase
{
	void ANOMALY_JARKA_ACTIVE_LIGHT()
	{
		SetVisibleDuringDaylight(true);
		SetRadiusTo(20);
		SetBrightnessTo(100);
		SetFlareVisible(false);
		SetAmbientColor(0.9, 0.5, 0.3);
		SetDiffuseColor(0.9, 0.5, 0.3);
		SetFadeOutTime(1);
		SetLifetime(11);
		SetDisableShadowsWithinRadius(-1);
		SetDancingShadowsMovementSpeed(0.4);
		SetDancingShadowsAmplitude(0.5);
		SetFlickerAmplitude(0.5);
		SetFlickerSpeed(4.0);
	}
}