class Anomaly_Kisel_Idle extends House  
{
	ANOMALY_KISEL_IDLE_LIGHT		m_Light;
	Particle						m_AnomalyParticle;
	SoundOnVehicle					m_AnomalySound;
	
	void Anomaly_Kisel_Idle()
	{
		if ( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
			m_Light = ANOMALY_KISEL_IDLE_LIGHT.Cast( ScriptedLightBase.CreateLight(ANOMALY_KISEL_IDLE_LIGHT, "0 1 0", 0.5) );
			m_Light.AttachOnObject(this, "0 1 0", "0 0 0");
			m_AnomalySound = PlaySoundLoop("kisel_idle", 20);
			m_AnomalyParticle = Particle.PlayOnObject(ParticleList.ANOMALY_KISEL_IDLE, this);
		}
	}
	
	void ~Anomaly_Kisel_Idle()
	{
		if (m_AnomalyParticle) m_AnomalyParticle.Stop();
		if (m_Light) m_Light.FadeOut();
		if (m_AnomalySound) GetGame().ObjectDelete( m_AnomalySound );
 	}
}

class ANOMALY_KISEL_IDLE_LIGHT extends PointLightBase
{		
	void ANOMALY_KISEL_IDLE_LIGHT()
	{
		SetVisibleDuringDaylight(true);
		SetRadiusTo(6);
		SetBrightnessTo(1.0);
		SetCastShadow(false);
		SetFadeOutTime(3);
		SetDiffuseColor(0.0, 0.8, 0.1);
		SetAmbientColor(0.0, 0.8, 0.1);
		SetFlareVisible(false);
	}
}