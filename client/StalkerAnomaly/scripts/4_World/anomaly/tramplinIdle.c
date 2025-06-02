class Anomaly_Tramplin_Idle extends House  
{
	Particle					m_AnomalyParticle;
	SoundOnVehicle				m_AnomalySound;
	
	void Anomaly_Tramplin_Idle()
	{
		if ( GetGame().IsClient()  ||  !GetGame().IsMultiplayer() )
		{
			m_AnomalySound = PlaySoundLoop("tramplin_idle", 30);
			m_AnomalyParticle = Particle.PlayOnObject(ParticleList.ANOMALY_TRAMPLIN_IDLE, this);
		}
	}
	
	void ~Anomaly_Tramplin_Idle()
	{
		if (m_AnomalyParticle) m_AnomalyParticle.Stop();
		if (m_AnomalySound) GetGame().ObjectDelete(m_AnomalySound);
 	}
}