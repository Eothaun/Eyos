$input v_pos, v_view, v_normal, v_color0

/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

vec4 lit(float _ndotl, float _rdotv, float _m)
{
	float diff = max(0.0, _ndotl);
	float spec = step(0.0, _ndotl) * max(0.0, _rdotv * _m);
	return vec4(1.0, diff, spec, 1.0);
}

void main()
{
	vec3 lightDir0 = -normalize(vec3(0.0, -1.0, -1.0));
	float light0Intensity = 0.7;
	vec3 lightDir1 = -normalize(vec3(-1.0, -0.1, 1.0));
	float light1Intensity = 0.3;
	float ambientLight = 0.2;

	float nDotl0 = max(0, dot(v_normal, lightDir0));
	float nDotl1 = max(0, dot(v_normal, lightDir1));

	gl_FragColor.rgb = v_color0.rgb * (ambientLight + nDotl0 * light0Intensity + nDotl1 * light1Intensity);
	gl_FragColor.a = 1.0;
}
