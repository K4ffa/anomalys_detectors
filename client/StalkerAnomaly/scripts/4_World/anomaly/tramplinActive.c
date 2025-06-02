class Anomaly_Tramplin_Active extends House  
{
	Particle					m_AnomalyParticle;
	SoundOnVehicle				m_AnomalySound;
	
	void Anomaly_Tramplin_Active()
	{
		if ( GetGame().IsClient()  ||  !GetGame().IsMultiplayer() )
		{
			m_AnomalySound = PlaySound("tramplin_active", 100);
			m_AnomalyParticle = Particle.PlayOnObject(ParticleList.ANOMALY_TRAMPLIN_ACTIVE, this);
		}
	}
	
	void ~Anomaly_Tramplin_Active()
	{
		if (m_AnomalyParticle) m_AnomalyParticle.Stop();
		if (m_AnomalySound) GetGame().ObjectDelete(m_AnomalySound);
 	}
}