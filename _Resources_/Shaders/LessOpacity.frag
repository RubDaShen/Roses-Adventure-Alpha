uniform sampler2D		MyTexture;

void main()
{
	vec4		m_Color				= texture2D(	MyTexture, gl_TexCoord[0].xy	);


	m_Color.rgb		= m_Color.rgb - 0.025;
	m_Color.a		= m_Color.a - 0.01;

	gl_FragColor	= m_Color;
}