//#define DEBUG_ANOMALY
class anomalyTrigger extends Trigger
{
	protected vector			m_ExtentMin;
	protected vector			m_ExtentMax;
	protected Object 			m_AnomalyObject;
	protected Object			m_AnomalyObjectActive;
	protected vector 			m_AnomalyPosition;
	protected bool 				m_isActive;
	protected bool				m_IsDebugTrigger;
    protected float             m_updateRange;
	protected float             m_damageForItem;
	
	void anomalyTrigger()
	{
		m_updateRange = 0.2;
		m_damageForItem = 100;
	}
	
	bool isNotInside(vector pos)
	{
		//min
		float minX = (m_ExtentMin[0] - m_updateRange);
		float minY = (m_ExtentMin[1] - m_updateRange);
		float minZ = (m_ExtentMin[2] - m_updateRange);
		//max
		float maxX = (m_ExtentMax[0] + m_updateRange);
		float maxY = (m_ExtentMax[1] + m_updateRange);
		float maxZ = (m_ExtentMax[2] + m_updateRange);
		//pos
		float posX = m_AnomalyPosition[0];
		float posY = m_AnomalyPosition[1];
		float posZ = m_AnomalyPosition[2];
		
		if (pos[0] > (posX + maxX) || pos[0] < (posX + minX)) return true;
		if (pos[2] > (posZ + maxZ) || pos[2] < (posZ + minZ)) return true;
		if (pos[1] > (posY + maxY) || pos[1] < (posY + minY)) return true;
		return false;
	}
	
	Object SpawnAnomaly( string type, vector position )
	{
	    Object obj = GetGame().CreateObjectEx( type, position, ECE_PLACE_ON_SURFACE);
	    obj.SetFlags( EntityFlags.STATIC, false );
	    obj.SetPosition( position );
		obj.SetOrientation(GetOrientation());
	    obj.Update();
		
		return obj;
	}
		
	protected string GetRandomHitZone(array<string> hitzones)
	{
		Math.Randomize(-1);
		int idx = Math.RandomInt( 0, 100 ) % hitzones.Count();

		return hitzones[idx];
	}
	
	void anomalySetDamage(Object obj)
	{
		if( obj && obj.IsKindOf("AnomalyActivator") )
		{
			ItemBase item = ItemBase.Cast(obj.GetParent());
			item.DecreaseHealth("","", m_damageForItem);
			#ifdef DEBUG_ANOMALY
			Print("DamageItem:" + m_damageForItem);
			Print(item);
			#endif
		}
	}
	
	void updateRotation()
	{
		m_AnomalyObject.SetOrientation(GetOrientation());
	}
	
	void updateInsidersAndSetDamage()
	{
		for(int n = 0; n < m_insiders.Count(); n++)
		{
			TriggerInsider ins = m_insiders.Get(n);
			Object insObj = ins.GetObject();
			if( ins.insider == null )
			{
				m_insiders.Remove(n);
				continue;
			}
			
			if( insObj && isNotInside(insObj.GetPosition()) )
			{
				OnLeave(ins.insider.Ptr());
				m_insiders.Remove(n);
				continue;
			}
			
			anomalySetDamage(insObj);
		}
	}
		
	override protected void UpdateInsiders(int timeout)
	{
		for(int n = 0; n < m_insiders.Count(); n++)
		{
			TriggerInsider ins = m_insiders.Get(n);
			Object insObj = ins.GetObject();
			if( ins.insider == null || !insObj.IsAlive() )
			{
				//object has been deleted/killed. Remove it
				m_insiders.Remove(n);
				continue;
			}

			if( insObj && isNotInside(insObj.GetPosition()) )
			{
				if(g_Game.GetTime() - ins.timeStamp > 700)
				{
					//object left. Remove it
					OnLeave(ins.insider.Ptr());
					m_insiders.Remove(n);
					continue;
				}
			}
		}
	}
	
	override void AddInsider(Object obj)
	{
		TriggerInsider ins;
		for(int n = 0; n < m_insiders.Count(); n++)
		{
			ins = m_insiders.Get(n);
			if( obj && ins.GetObject() == obj )
			{
				ins.timeStamp = g_Game.GetTime();
				return;
			}
		}

		ins = new TriggerInsider(obj);
		ins.timeStamp = g_Game.GetTime();
		m_insiders.Insert(ins);
		OnEnter(obj);
	}
	
	override void EOnTouch(IEntity other, int extra)
	{
		Object obj;
		if (Class.CastTo(obj, other))
		{
			if (obj.IsAlive())
			{
				AddInsider(obj);
			}
		}
	}
	
	override void SetExtents(vector mins, vector maxs)
	{
		SetCollisionBox(mins, maxs);
		#ifdef DEBUG_ANOMALY
		vector mat[4];
		GetTransform(mat);
		if(shape)
		{
			shape.Destroy();
			shape = NULL;
		}
		
		shape = Shape.Create(ShapeType.BBOX, 0x1fF7CA76, ShapeFlags.TRANSP|ShapeFlags.NOZWRITE, mins, maxs);
		
		if (shape)
		{
			shape.SetMatrix(mat);
		}
		#endif
	}
}