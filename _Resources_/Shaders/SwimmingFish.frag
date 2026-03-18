uniform sampler2D		MyTexture;

uniform vec4			Boundaries;
uniform float			_Time_;


float	power(float _Val)
{
	return (_Val * _Val);
}

void main()
{
	//	Don't forget to normalize the coordinates.
	vec2		m_TexCoord		= vec2(	(gl_TexCoord[0].x - (Boundaries.r / 2048.0)) * 20.48	,	
										(gl_TexCoord[0].y - (Boundaries.g / 2048.0)) * 20.48	) ;
	vec2		_FinalCoord_;

	

	//	_Coord_ calculation.
	float		_Coord_;

	if (m_TexCoord.x <= 0.5)
	{
		if (m_TexCoord.x <= 0.2)
		{
			_Coord_ = power(-0.3) * cos(_Time_ / 3.0) * 0.95;
		}
		else
		{
			_Coord_ = power(m_TexCoord.x - 0.5) * cos(_Time_ / 3.0) * 0.95;
		}
	}
	else
	{
		_Coord_ = power(m_TexCoord.x - 0.5) * cos(_Time_ / 3.0) * 0.15;
	}

	//	_FinalCoord_ verification.
	if (	((m_TexCoord.y + _Coord_) < 0.0)	||
			((m_TexCoord.y + _Coord_) > 1.0)	)
	{
		gl_FragColor	=	vec4(0.0, 0.0, 0.0, 0.0);
	}
	else
	{
		gl_FragColor	=	texture2D(	MyTexture, vec2(	(m_TexCoord.x / 20.48) + (Boundaries.r / 2048.0)				, 
															((m_TexCoord.y + _Coord_) / 20.48) + (Boundaries.g / 2048.0)	)	);
	}
}