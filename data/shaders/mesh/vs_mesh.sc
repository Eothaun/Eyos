$input a_position, a_normal
$output v_pos, v_view, v_normal, v_color0

/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_color0;

void main()
{
	vec3 pos = a_position;

	gl_Position = mul(u_modelViewProj, vec4(pos, 1.0) );
	v_pos = gl_Position.xyz;
	v_view = mul(u_modelView, vec4(pos, 1.0) ).xyz;

	v_normal = normalize(mul(u_model[0], vec4(a_normal, 0.0) ).xyz);

	v_color0 = u_color0;
}
