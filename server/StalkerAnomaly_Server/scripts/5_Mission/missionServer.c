modded class MissionServer
{
    void MissionServer()
    {
        AnomalySpawner m_AnomalySpawner = new AnomalySpawner;
        delete m_AnomalySpawner;
        
        if(ASController.enableAnomalyOptimization())
        {
            AnomalyOptimizationSystem m_AnomalyOptimizationSystem = new AnomalyOptimizationSystem;
			m_AnomalyOptimizationSystem.enableAnomalyOptimizationSystem();
        }
    }
}