class Anomaly_Kisel_Active extends House  
{
	ANOMALY_KISEL_ACTIVE_LIGHT	m_Light;
 	SoundOnVehicle				m_AnomalySound;
	
	void Anomaly_Kisel_Active()
	{
		if ( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
			m_Light = ANOMALY_KISEL_ACTIVE_LIGHT.Cast( ScriptedLightBase.CreateLight(ANOMALY_KISEL_ACTIVE_LIGHT, "0 2 0", 0) );
			m_Light.AttachOnObject(this, "0 2 0", "0 0 0");
			m_AnomalySound = PlaySound("kisel_active", 100);
		}
	}
	
	void ~Anomaly_Kisel_Active()
	{
		if (m_Light) m_Light.FadeOut();
		if (m_AnomalySound) GetGame().ObjectDelete(m_AnomalySound);
 	}
}

class ANOMALY_KISEL_ACTIVE_LIGHT extends PointLightBase
{
	void ANOMALY_KISEL_ACTIVE_LIGHT()
	{
		SetVisibleDuringDaylight(true);
		SetRadiusTo(10);
		SetBrightnessTo(15);
		SetFlareVisible(false);
		SetAmbientColor(0.2, 1.0, 0.2);
		SetDiffuseColor(0.2, 1.0, 0.2);
		SetFadeOutTime(0.5);
		SetLifetime(1.0);
		SetDisableShadowsWithinRadius(-1);
	}
}