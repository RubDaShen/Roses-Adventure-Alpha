//	I grabed this shader from shadertoy.com, and other sources.
//	I'm not the owner, creator, or anything.
//	I'm just amazed by the shader.



uniform sampler2D		MyTexture;
uniform float			Time;


void main()
{
	vec2		m_TexCoord		= vec2(	gl_TexCoord[0].x, gl_TexCoord[0].y );
	vec4		m_MyColor		= texture2D(MyTexture, m_TexCoord);
	


	//	Apply sepia.
	float	VntOne		= dot(m_MyColor.rgb, vec3(0.4, 0.769, 0.189));
	float	VntTwo		= dot(m_MyColor.rgb, vec3(0.4, 0.686, 0.168));
	float	VntThree	= dot(m_MyColor.rgb, vec3(0.4, 0.534, 0.131));

	m_MyColor.r		= mix(m_MyColor.rgb, vec3(VntOne), Time * 0.8).r;
	m_MyColor.g		= mix(m_MyColor.rgb, vec3(VntTwo), Time * 0.8).g;
	m_MyColor.b		= mix(m_MyColor.rgb, vec3(VntThree), Time * 0.8).b;
	
	// Apply vignette
	float		Vignette = 1.0 - (	pow(length(m_TexCoord - vec2(0.5)), 1.5) * Time		);



	gl_FragColor	= vec4(m_MyColor.rgb * Vignette, 1.0);
}