class AnomalySpawner_anomalyData
{
	string			anomalyName;
	int				anomalyCount;
	ref ArtefactsWithoutDetectorDynamic	ArtefactsWithoutDetector;
	ref ArtefactsWithDetectorDynamic	ArtefactsWithDetector;
}
class AnomalySpawner_teleportAnomaly
{
	vector			anomalyPosition;
	bool			teleportType;
	TVectorArray	teleportToPositions;
	ref ArtefactsWithoutDetectorDynamic	ArtefactsWithoutDetector;
	ref ArtefactsWithDetectorDynamic	ArtefactsWithDetector;
}
class AnomalySpawner_staticAnomaly
{
	string			anomalyName;
	TVectorArray	anomalyPosition;
	ref ArtefactsWithoutDetectorDynamic	ArtefactsWithoutDetector;
	ref ArtefactsWithDetectorDynamic	ArtefactsWithDetector;
}
class AnomalySpawner_dynamicAnomaly
{
	string					zoneType;
	vector					zonePosition;
	int						zoneRadius;
	int						distanceBTWAnomaly;
	int						checkGeometry;
	ref array<ref AnomalySpawner_anomalyData>		anomalyData;
}
//Artefacts Static
class ArtefactsDataStatic
{
	string	ArtefactClassName;
	int		ArtefactSpawnChancePercent;
}
class ArtefactsSpawnDataStatic
{
	string	AnomalyName;
	float	SpawnChancePercent;
	ref array<ref ArtefactsDataStatic>	ArtefactsData;
}
//Artefacts Dynamic Without Detector
class ArtefactsWithoutDetectorDynamic_Data
{
	string	ArtefactClassName;
	int		ArtefactSpawnChancePercent;
}
class ArtefactsWithoutDetectorDynamic
{
	float	SpawnChancePercent;
	float	SpawnDistance_Min;
	float	SpawnDistance_Max;
	ref array<ref ArtefactsWithoutDetectorDynamic_Data> ArtefactsData;
}
//Artefacts Dynamic With Detector
class ArtefactsWithDetectorDynamic_Data
{
	string	ArtefactClassName;
	int		ArtefactSpawnChancePercent;
}
class ArtefactsWithDetectorDynamic
{
	float	SpawnChancePercent;
	ref array<ref ArtefactsWithDetectorDynamic_Data> ArtefactsData;
}
