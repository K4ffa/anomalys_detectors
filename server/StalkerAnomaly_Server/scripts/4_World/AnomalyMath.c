class AnMath
{
	static protected int AS_WorldSizeX = 15360;
	static protected int AS_WorldSizeY = 15360;
	static protected int AS_SquareSize = 25;
	static protected int AS_SquaresCountX = 614;
	static protected int AS_SquaresCountY = 614;
	
	static void InitializeMath(int x, int y)
	{
		Print("InitializeMath");
		
		AS_WorldSizeX = x;
		AS_WorldSizeY = y;
		
		AS_SquaresCountX = Math.Floor(AS_WorldSizeX / AS_SquareSize);
		AS_SquaresCountY = Math.Floor(AS_WorldSizeY / AS_SquareSize);
	}

	static int getSquareIndex(vector pos)
	{
		float posX = pos[0];
		float posY = pos[2];
		int m_SquareX;
		int m_SquareY;
		
		m_SquareX = Math.Floor(posX / AS_SquareSize);
		m_SquareY = Math.Floor(posY / AS_SquareSize);
		
		if (m_SquareX == 0)
		{
			return m_SquareY;
		}
		else
		{
			int m_curSquare = (m_SquareX * AS_SquaresCountY) + m_SquareY;
			return m_curSquare;
		}
	}
	
	static string getSquareName(vector pos)
	{
		float posX = pos[0];
		float posY = pos[2];
		int m_SquareX;
		int m_SquareY;
		
		m_SquareX = Math.Floor(posX / AS_SquareSize);
		m_SquareY = Math.Floor(posY / AS_SquareSize);
		
		return ("" + m_SquareX + ":" + m_SquareY);
	}
	
	static TStringArray getNearSquares(vector pos, int radius)
	{
		float posX = pos[0];
		float posY = pos[2];
		
		int m_nddSquares = Math.Round((radius - AS_SquareSize) / AS_SquareSize) / 2;
		int m_SquareX = Math.Floor(posX / AS_SquareSize);
		int m_SquareY = Math.Floor(posY / AS_SquareSize);
		
		int m_toLeftX = m_nddSquares;
		if(m_SquareX < m_toLeftX)
			m_toLeftX = m_SquareX;
		
		int m_toRightX = m_nddSquares;
		if((m_SquareX + m_nddSquares) > AS_SquaresCountX)
			m_toRightX = (AS_SquaresCountX - m_SquareX);
		
		int m_toUpY = m_nddSquares;
		if(m_SquareY < m_toUpY)
			m_toUpY = m_SquareY;
		
		int m_toDownY = m_nddSquares;
		if((m_SquareY + m_nddSquares) > AS_SquaresCountY)
			m_toDownY = (AS_SquaresCountY - m_SquareY);
		
		TStringArray m_squaresArray = new TStringArray;
		int m_startY = m_SquareY - m_toUpY;
		int m_stepsY = m_toUpY + m_toDownY + 1;
		for(int i = 0; i < m_stepsY; i++)
        {
			int m_startX = m_SquareX - m_toLeftX;
			int m_stepsX = m_toLeftX + m_toRightX + 1;
			for(int n = 0; n < m_stepsX; n++)
        	{
				m_squaresArray.Insert( "" + (m_startX + n) + ":" + (m_startY + i) );
			}
        }
		return m_squaresArray;
	}
	
	static TStringArray GetNearSquaresOffset(vector pos, int offset)
	{
		float posX = pos[0];
		float posY = pos[2];
		
		int m_SquareX = Math.Floor(posX / AS_SquareSize);
		int m_SquareY = Math.Floor(posY / AS_SquareSize);
		
		int m_toLeftX = offset;
		if(m_SquareX < m_toLeftX)
			m_toLeftX = m_SquareX;
		
		int m_toRightX = offset;
		if((m_SquareX + offset) > AS_SquaresCountX)
			m_toRightX = (AS_SquaresCountX - m_SquareX);
		
		int m_toUpY = offset;
		if(m_SquareY < m_toUpY)
			m_toUpY = m_SquareY;
		
		int m_toDownY = offset;
		if((m_SquareY + offset) > AS_SquaresCountY)
			m_toDownY = (AS_SquaresCountY - m_SquareY);
		
		TStringArray m_squaresArray = new TStringArray;
		int m_startY = m_SquareY - m_toUpY;
		int m_stepsY = m_toUpY + m_toDownY + 1;
		for(int i = 0; i < m_stepsY; i++)
        {
			int m_startX = m_SquareX - m_toLeftX;
			int m_stepsX = m_toLeftX + m_toRightX + 1;
			for(int n = 0; n < m_stepsX; n++)
        	{
				m_squaresArray.Insert( "" + (m_startX + n) + ":" + (m_startY + i) );
			}
        }
		return m_squaresArray;
	}
	
	static TStringArray pushBackUnique(TStringArray arr, string value)
	{
		TStringArray m_tempArray = arr;
		if (arr.Find(value) == -1) m_tempArray.Insert(value);
		return m_tempArray;
	}
	
	static vector SnapToGround(vector pos)
	{
		pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
		return pos;
	}
	
	//get; set;
	static int getWorldSizeX()
	{
		return AS_WorldSizeX;
	}
	
	static int getWorldSizeY()
	{
		return AS_WorldSizeY;
	}
	
	static int getSquareSize()
	{
		return AS_SquareSize;
	}
}