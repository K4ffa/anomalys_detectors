class Anomaly_Electra_Active extends House  
{
	ANOMALY_ELECTRA_ACTIVE_LIGHT	m_Light;
	Particle						m_AnomalyParticle;
	SoundOnVehicle					m_AnomalySound;
	
	void Anomaly_Electra_Active()
	{
		if ( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
			m_Light = ANOMALY_ELECTRA_ACTIVE_LIGHT.Cast( ScriptedLightBase.CreateLight(ANOMALY_ELECTRA_ACTIVE_LIGHT, "0 1 0", 0) );
			m_Light.AttachOnObject(this, "0 1 0", "0 0 0");
			m_AnomalySound = PlaySound("electra_active", 100);
			m_AnomalyParticle = Particle.PlayOnObject(ParticleList.ANOMALY_ELECTRA_ACTIVE, this);
		}
	}
	
	void ~Anomaly_Electra_Active()
	{
		if (m_AnomalyParticle) m_AnomalyParticle.Stop();
		if (m_Light) m_Light.FadeOut();
		if (m_AnomalySound) GetGame().ObjectDelete( m_AnomalySound );
 	}
}

class ANOMALY_ELECTRA_ACTIVE_LIGHT extends PointLightBase
{
	void ANOMALY_ELECTRA_ACTIVE_LIGHT()
	{
		SetVisibleDuringDaylight(true);
		SetRadiusTo(150);
		SetBrightnessTo(500);
		SetFlareVisible(false);
		SetAmbientColor(0.2, 0.2, 1.0);
		SetDiffuseColor(0.2, 0.2, 1.0);
		SetFadeOutTime(0.15);
		SetLifetime(0.4);
		SetDisableShadowsWithinRadius(-1);
	}
}