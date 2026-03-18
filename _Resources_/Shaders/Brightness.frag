uniform sampler2D		MyTexture;

uniform float			_Brightness_;
uniform float			_Alpha_;

void main()
{
	vec2		m_TexCoord		= vec2(		gl_TexCoord[0].x	,	
											gl_TexCoord[0].y	) ;

	vec4		m_Color			= texture2D(	MyTexture, gl_TexCoord[0].xy	);
	m_Color.rgb					= m_Color.rgb + _Brightness_;
	m_Color.rgb					= clamp(		m_Color.rgb, 0.0, 1.0			);
	m_Color.rgba				= m_Color.rgba * _Alpha_;

	gl_FragColor	= m_Color;
	
}