modded class MissionServer
{
    void MissionServer()
    {
		if(ASController.enableSpawnArtefacts())
        {
			SA_Detector_Base.SetArtefactData(AnomalySquareSystem.getArtefactData());

            //Artefact for Detectors
            TStringArray m_artefactsOtklik = ASController.GetArtefactsOtklik();
            TStringArray m_artefactsBear = ASController.GetArtefactsBear();
            if (m_artefactsOtklik.Count() > 0) SA_Detector_Otklik.SetAllowedArtefact(m_artefactsOtklik);
            if (m_artefactsBear.Count() > 0) SA_Detector_Bear.SetAllowedArtefact(m_artefactsBear);
			
			ArtefactSpawner.Initialization();
        }
    }
}