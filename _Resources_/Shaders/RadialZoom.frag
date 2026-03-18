uniform sampler2D		MyTexture;

uniform float			_Time_;
uniform vec4			Boundaries;

void main()
{
	vec2		m_TexCoord		= vec2(	(gl_TexCoord[0].x - (Boundaries.r / 2048.0)) * 20.48	,	
										(gl_TexCoord[0].y - (Boundaries.g / 2048.0)) * 20.48	) ;
	

	// Calculate the distance from the center of the sprite
    vec2		Center			= vec2(0.5, 0.5); // Assuming the center is at (0.5, 0.5)
    float		Distance		= distance(m_TexCoord, Center);
    
    // Apply the radial zoom effect
    float		ZoomFactor		= smoothstep(0.0, _Time_ / 95.0, Distance);
    vec2		NewTexCoord		= Center + ((m_TexCoord - Center) * ZoomFactor);



	gl_FragColor	=	texture2D(	MyTexture, vec2(	(NewTexCoord.x / 20.48) + (Boundaries.r / 2048.0)	, 
														(NewTexCoord.y / 20.48) + (Boundaries.g / 2048.0)	)	);
}