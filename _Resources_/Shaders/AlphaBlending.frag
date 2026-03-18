uniform sampler2D		MyTexture;
uniform sampler2D		ForeignTexture;

void main()
{
	vec4		m_Color				= texture2D(	MyTexture, gl_TexCoord[0].xy			);
	vec4		m_ForeignColor		= texture2D(	ForeignTexture, gl_TexCoord[0].xy		);

	
	float		OriginalOpacity = m_Color.a;
	m_Color.a		= m_Color.rgb;

	//	Clear pixel.
	if (m_Color.rgb == 0.0)
	{
		return;
	}

	//	Blending artifacts.
	//	Premultiplied alpha: (m_Color.rgb * m_Color.a) + (m_ForeignColor.rgb * (1.0 - m_Color.a))
	if (	m_Color.a == 1.0	)
	{
		m_Color.rgb		=	m_Color.rgb + 0.75;
	}
	else
	{	
		if (	OriginalOpacity >= 0.01	)
		{
			m_Color.rgb		=	m_Color + m_ForeignColor;
			//	m_Color.rgb		=	(m_Color.rgb * 0.85) + 0.1;
			m_Color.a		=	OriginalOpacity;
		}
	}

	gl_FragColor	= m_Color;
}