class Anomaly_Par_Idle extends House  
{
	Particle					m_AnomalyParticle;
	SoundOnVehicle				m_AnomalySound;
	
	void Anomaly_Par_Idle()
	{
		if ( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
			m_AnomalySound = PlaySoundLoop("par_idle", 30);
			m_AnomalyParticle = Particle.PlayOnObject(ParticleList.ANOMALY_PAR_IDLE, this);
		}
	}
	
	void ~Anomaly_Par_Idle()
	{
		if (m_AnomalyParticle) m_AnomalyParticle.Stop();
		if (m_AnomalySound) GetGame().ObjectDelete(m_AnomalySound);
 	}
}