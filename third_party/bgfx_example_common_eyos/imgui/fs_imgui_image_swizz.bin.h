static const uint8_t fs_imgui_image_swizz_glsl[569] =
{
	0x46, 0x53, 0x48, 0x06, 0x6f, 0x1e, 0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x11, 0x75, // FSH.o.><.......u
	0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, // _imageLodEnabled
	0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x09, 0x75, 0x5f, 0x73, 0x77, 0x69, 0x7a, 0x7a, 0x6c, 0x65, // .......u_swizzle
	0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x0a, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, // .......s_texColo
	0x72, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0xed, 0x01, 0x00, 0x00, 0x76, 0x61, 0x72, 0x79, 0x69, // r..........varyi
	0x6e, 0x67, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x76, 0x5f, // ng highp vec2 v_
	0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, // texcoord0;.unifo
	0x72, 0x6d, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x75, 0x5f, // rm highp vec4 u_
	0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, 0x3b, // imageLodEnabled;
	0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, // .uniform highp v
	0x65, 0x63, 0x34, 0x20, 0x75, 0x5f, 0x73, 0x77, 0x69, 0x7a, 0x7a, 0x6c, 0x65, 0x3b, 0x0a, 0x75, // ec4 u_swizzle;.u
	0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, // niform sampler2D
	0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x3b, 0x0a, 0x76, 0x6f, 0x69, //  s_texColor;.voi
	0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x6c, 0x6f, // d main ().{.  lo
	0x77, 0x70, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // wp float tmpvar_
	0x31, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x20, 0x3d, 0x20, // 1;.  tmpvar_1 = 
	0x64, 0x6f, 0x74, 0x20, 0x28, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x44, 0x4c, 0x6f, // dot (texture2DLo
	0x64, 0x20, 0x20, 0x20, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, // d    (s_texColor
	0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x2c, 0x20, 0x75, // , v_texcoord0, u
	0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, // _imageLodEnabled
	0x2e, 0x78, 0x29, 0x2c, 0x20, 0x75, 0x5f, 0x73, 0x77, 0x69, 0x7a, 0x7a, 0x6c, 0x65, 0x29, 0x3b, // .x), u_swizzle);
	0x0a, 0x20, 0x20, 0x6c, 0x6f, 0x77, 0x70, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x74, 0x6d, 0x70, // .  lowp vec3 tmp
	0x76, 0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // var_2;.  tmpvar_
	0x32, 0x2e, 0x78, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, 0x0a, // 2.x = tmpvar_1;.
	0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x2e, 0x79, 0x20, 0x3d, 0x20, 0x74, //   tmpvar_2.y = t
	0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // mpvar_1;.  tmpva
	0x72, 0x5f, 0x32, 0x2e, 0x7a, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, // r_2.z = tmpvar_1
	0x3b, 0x0a, 0x20, 0x20, 0x6d, 0x65, 0x64, 0x69, 0x75, 0x6d, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, // ;.  mediump vec4
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, //  tmpvar_3;.  tmp
	0x76, 0x61, 0x72, 0x5f, 0x33, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, // var_3.xyz = tmpv
	0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, // ar_2;.  tmpvar_3
	0x2e, 0x77, 0x20, 0x3d, 0x20, 0x28, 0x30, 0x2e, 0x32, 0x20, 0x2b, 0x20, 0x28, 0x30, 0x2e, 0x38, // .w = (0.2 + (0.8
	0x20, 0x2a, 0x20, 0x75, 0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, //  * u_imageLodEna
	0x62, 0x6c, 0x65, 0x64, 0x2e, 0x79, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, // bled.y));.  gl_F
	0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // ragColor = tmpva
	0x72, 0x5f, 0x33, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                           // r_3;.}...
};
static const uint8_t fs_imgui_image_swizz_spv[1379] =
{
	0x46, 0x53, 0x48, 0x06, 0x6f, 0x1e, 0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x11, 0x75, // FSH.o.><.......u
	0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, // _imageLodEnabled
	0x12, 0x01, 0x00, 0x00, 0x01, 0x00, 0x09, 0x75, 0x5f, 0x73, 0x77, 0x69, 0x7a, 0x7a, 0x6c, 0x65, // .......u_swizzle
	0x12, 0x01, 0x10, 0x00, 0x01, 0x00, 0x0a, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, // .......s_texColo
	0x72, 0x10, 0x00, 0x40, 0x00, 0x50, 0x00, 0x14, 0x05, 0x00, 0x00, 0x03, 0x02, 0x23, 0x07, 0x00, // r..@.P.......#..
	0x00, 0x01, 0x00, 0x07, 0x00, 0x08, 0x00, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, // ................
	0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, // ...............G
	0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30, 0x00, 0x00, 0x00, 0x00, 0x0e, // LSL.std.450.....
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x07, 0x00, 0x04, // ................
	0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x73, // .......main....s
	0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, // ...|............
	0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x05, 0x00, 0x00, 0x00, 0xf4, 0x01, 0x00, 0x00, 0x05, // ................
	0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x05, // .......main.....
	0x00, 0x07, 0x00, 0x27, 0x00, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, // ...'...s_texColo
	0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x00, 0x00, 0x00, 0x05, 0x00, 0x07, 0x00, 0x2a, // rSampler.......*
	0x00, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x54, 0x65, 0x78, // ...s_texColorTex
	0x74, 0x75, 0x72, 0x65, 0x00, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x24, // ture.......O...$
	0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x00, 0x06, 0x00, 0x08, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x00, // Global.....O....
	0x00, 0x00, 0x00, 0x75, 0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, // ...u_imageLodEna
	0x62, 0x6c, 0x65, 0x64, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x01, // bled.......O....
	0x00, 0x00, 0x00, 0x75, 0x5f, 0x73, 0x77, 0x69, 0x7a, 0x7a, 0x6c, 0x65, 0x00, 0x00, 0x00, 0x05, // ...u_swizzle....
	0x00, 0x03, 0x00, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x73, // ...Q...........s
	0x00, 0x00, 0x00, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x00, 0x05, // ...v_texcoord0..
	0x00, 0x06, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, // ...|...bgfx_Frag
	0x44, 0x61, 0x74, 0x61, 0x30, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x27, 0x00, 0x00, 0x00, 0x22, // Data0..G...'..."
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x27, 0x00, 0x00, 0x00, 0x21, // .......G...'...!
	0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x22, // ...P...G...*..."
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x21, // .......G...*...!
	0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x00, // ...@...H...O....
	0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0x4f, // ...#.......H...O
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x47, // .......#.......G
	0x00, 0x03, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x51, // ...O.......G...Q
	0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x51, // ...".......G...Q
	0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x73, // ...!...0...G...s
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x7c, // ...........G...|
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x02, // ................
	0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1a, // ...!............
	0x00, 0x02, 0x00, 0x06, 0x00, 0x00, 0x00, 0x16, 0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x00, 0x20, // ............... 
	0x00, 0x00, 0x00, 0x19, 0x00, 0x09, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x01, // ................
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // ................
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x07, // ................
	0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x07, // ................
	0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x26, 0x00, 0x00, 0x00, 0x00, // ....... ...&....
	0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x26, 0x00, 0x00, 0x00, 0x27, // .......;...&...'
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, // ....... ...)....
	0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2a, // .......;...)...*
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x20, // ...........-... 
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x2e, // .......+...-....
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x32, // .......+...-...2
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x03, 0x00, 0x36, 0x00, 0x00, 0x00, 0x08, // ...........6....
	0x00, 0x00, 0x00, 0x1e, 0x00, 0x04, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0e, // .......O........
	0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x50, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x4f, // ... ...P.......O
	0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x50, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 0x02, // ...;...P...Q....
	0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 0x57, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, // .......W... ....
	0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x57, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x00, // ...+...W...X....
	0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x59, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x07, // ... ...Y........
	0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0e, // ... ...]........
	0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0xcd, // ...+.......b....
	0xcc, 0x4c, 0x3e, 0x2b, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0xcd, // .L>+.......c....
	0xcc, 0x4c, 0x3f, 0x2b, 0x00, 0x04, 0x00, 0x57, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x01, // .L?+...W...d....
	0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x72, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0b, // ... ...r........
	0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x72, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x01, // ...;...r...s....
	0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x7b, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0e, // ... ...{........
	0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x7b, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x03, // ...;...{...|....
	0x00, 0x00, 0x00, 0x36, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, // ...6............
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 0x3d, // ...............=
	0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x3d, // .......(...'...=
	0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x3d, // .......+...*...=
	0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x41, // .......t...s...A
	0x00, 0x06, 0x00, 0x59, 0x00, 0x00, 0x00, 0x9b, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 0x32, // ...Y.......Q...2
	0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x9c, // ...X...=........
	0x00, 0x00, 0x00, 0x9b, 0x00, 0x00, 0x00, 0x56, 0x00, 0x05, 0x00, 0x36, 0x00, 0x00, 0x00, 0xb7, // .......V...6....
	0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x58, 0x00, 0x07, 0x00, 0x0e, // ...+...(...X....
	0x00, 0x00, 0x00, 0xba, 0x00, 0x00, 0x00, 0xb7, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x02, // ...........t....
	0x00, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x9e, // .......A...]....
	0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x0e, // ...Q.......=....
	0x00, 0x00, 0x00, 0x9f, 0x00, 0x00, 0x00, 0x9e, 0x00, 0x00, 0x00, 0x94, 0x00, 0x05, 0x00, 0x07, // ................
	0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0xba, 0x00, 0x00, 0x00, 0x9f, 0x00, 0x00, 0x00, 0x41, // ...............A
	0x00, 0x06, 0x00, 0x59, 0x00, 0x00, 0x00, 0xa1, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x00, 0x32, // ...Y.......Q...2
	0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0xa2, // ...d...=........
	0x00, 0x00, 0x00, 0xa1, 0x00, 0x00, 0x00, 0x85, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0xa3, // ................
	0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0xa2, 0x00, 0x00, 0x00, 0x81, 0x00, 0x05, 0x00, 0x07, // ...c............
	0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0xa3, 0x00, 0x00, 0x00, 0x50, // .......b.......P
	0x00, 0x07, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xab, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0xa0, // ................
	0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x7c, // ...........>...|
	0x00, 0x00, 0x00, 0xab, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00, 0x00, // ...........8....
	0x00, 0x20, 0x00,                                                                               // . .
};
static const uint8_t fs_imgui_image_swizz_dx9[456] =
{
	0x46, 0x53, 0x48, 0x06, 0x6f, 0x1e, 0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x0a, 0x73, // FSH.o.><.......s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x01, 0x00, 0x00, 0x01, 0x00, 0x11, // _texColor0......
	0x75, 0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, // u_imageLodEnable
	0x64, 0x12, 0x01, 0x00, 0x00, 0x01, 0x00, 0x09, 0x75, 0x5f, 0x73, 0x77, 0x69, 0x7a, 0x7a, 0x6c, // d.......u_swizzl
	0x65, 0x12, 0x01, 0x01, 0x00, 0x01, 0x00, 0x7c, 0x01, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, // e......|........
	0xff, 0x36, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, 0x00, 0x00, 0x00, 0xa9, 0x00, 0x00, 0x00, 0x00, // .6.CTAB.........
	0x03, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0xa2, // ................
	0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x64, // ...X...........d
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, // .......t........
	0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x02, // ................
	0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, // ...............s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0xab, 0x04, 0x00, 0x0c, 0x00, 0x01, // _texColor.......
	0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x5f, 0x69, 0x6d, 0x61, // ...........u_ima
	0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, 0x00, 0xab, 0xab, 0x01, // geLodEnabled....
	0x00, 0x03, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, // ...............u
	0x5f, 0x73, 0x77, 0x69, 0x7a, 0x7a, 0x6c, 0x65, 0x00, 0x70, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, // _swizzle.ps_3_0.
	0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, // Microsoft (R) HL
	0x53, 0x4c, 0x20, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, // SL Shader Compil
	0x65, 0x72, 0x20, 0x31, 0x30, 0x2e, 0x31, 0x00, 0xab, 0xab, 0xab, 0x51, 0x00, 0x00, 0x05, 0x02, // er 10.1....Q....
	0x00, 0x0f, 0xa0, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xcd, 0xcc, 0x4c, 0x3f, 0xcd, // ......?......L?.
	0xcc, 0x4c, 0x3e, 0x1f, 0x00, 0x00, 0x02, 0x05, 0x00, 0x00, 0x80, 0x00, 0x00, 0x03, 0x90, 0x1f, // .L>.............
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x90, 0x00, 0x08, 0x0f, 0xa0, 0x05, 0x00, 0x00, 0x03, 0x00, // ................
	0x00, 0x07, 0x80, 0x02, 0x00, 0xd0, 0xa0, 0x00, 0x00, 0xc4, 0x90, 0x01, 0x00, 0x00, 0x02, 0x00, // ................
	0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0xa0, 0x5f, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, 0x00, // ......._........
	0x00, 0xe4, 0x80, 0x00, 0x08, 0xe4, 0xa0, 0x09, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x80, 0x00, // ................
	0x00, 0xe4, 0x80, 0x01, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0c, 0x80, 0x02, // ................
	0x00, 0xe4, 0xa0, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x55, 0xa0, 0x00, // .............U..
	0x00, 0xaa, 0x80, 0x00, 0x00, 0xff, 0x80, 0x01, 0x00, 0x00, 0x02, 0x00, 0x08, 0x0f, 0x80, 0x00, // ................
	0x00, 0x40, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00,                                                 // .@......
};
static const uint8_t fs_imgui_image_swizz_dx11[499] =
{
	0x46, 0x53, 0x48, 0x06, 0x6f, 0x1e, 0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x11, 0x75, // FSH.o.><.......u
	0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, // _imageLodEnabled
	0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x09, 0x75, 0x5f, 0x73, 0x77, 0x69, 0x7a, 0x7a, 0x6c, 0x65, // .......u_swizzle
	0x12, 0x00, 0x10, 0x00, 0x01, 0x00, 0x0a, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, // .......s_texColo
	0x72, 0x30, 0x01, 0x00, 0x00, 0x01, 0x00, 0xa4, 0x01, 0x00, 0x00, 0x44, 0x58, 0x42, 0x43, 0x82, // r0.........DXBC.
	0x53, 0x75, 0xc2, 0x4f, 0x7e, 0x06, 0x0a, 0x49, 0x27, 0x42, 0x29, 0x01, 0x0a, 0x6a, 0x92, 0x01, // Su.O~..I'B)..j..
	0x00, 0x00, 0x00, 0xa4, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x84, // ...........,....
	0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x4e, 0x50, 0x00, 0x00, 0x00, 0x02, // .......ISGNP....
	0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // .......8........
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x44, // ...............D
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, // ................
	0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, // .......SV_POSITI
	0x4f, 0x4e, 0x00, 0x54, 0x45, 0x58, 0x43, 0x4f, 0x4f, 0x52, 0x44, 0x00, 0xab, 0xab, 0xab, 0x4f, // ON.TEXCOORD....O
	0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, // SGN,........... 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, // ................
	0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x54, 0x41, 0x52, 0x47, 0x45, 0x54, // .......SV_TARGET
	0x00, 0xab, 0xab, 0x53, 0x48, 0x44, 0x52, 0xe4, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x39, // ...SHDR....@...9
	0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x04, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // ...Y...F. ......
	0x00, 0x00, 0x00, 0x5a, 0x00, 0x00, 0x03, 0x00, 0x60, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, // ...Z....`......X
	0x18, 0x00, 0x04, 0x00, 0x70, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x62, // ....p......UU..b
	0x10, 0x00, 0x03, 0x32, 0x10, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, // ...2.......e....
	0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x48, //  ......h.......H
	0x00, 0x00, 0x0c, 0xf2, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x10, 0x10, 0x00, 0x01, // ...........F....
	0x00, 0x00, 0x00, 0x46, 0x7e, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x10, 0x00, 0x00, // ...F~.......`...
	0x00, 0x00, 0x00, 0x0a, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, // ..... ..........
	0x00, 0x00, 0x08, 0x12, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x0e, 0x10, 0x00, 0x00, // ...........F....
	0x00, 0x00, 0x00, 0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x32, // ...F. .........2
	0x00, 0x00, 0x0a, 0x22, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x80, 0x20, 0x00, 0x00, // ..."......... ..
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0xcd, 0xcc, 0x4c, 0x3f, 0x01, // ........@....L?.
	0x40, 0x00, 0x00, 0xcd, 0xcc, 0x4c, 0x3e, 0x36, 0x00, 0x00, 0x05, 0xf2, 0x20, 0x10, 0x00, 0x00, // @....L>6.... ...
	0x00, 0x00, 0x00, 0x06, 0x04, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x01, 0x00, // ...........>....
	0x00, 0x20, 0x00,                                                                               // . .
};
static const uint8_t fs_imgui_image_swizz_mtl[877] =
{
	0x46, 0x53, 0x48, 0x06, 0x6f, 0x1e, 0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x11, 0x75, // FSH.o.><.......u
	0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, // _imageLodEnabled
	0x12, 0x01, 0x00, 0x00, 0x01, 0x00, 0x09, 0x75, 0x5f, 0x73, 0x77, 0x69, 0x7a, 0x7a, 0x6c, 0x65, // .......u_swizzle
	0x12, 0x01, 0x10, 0x00, 0x01, 0x00, 0x0a, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, // .......s_texColo
	0x72, 0x10, 0x00, 0x40, 0x00, 0x50, 0x00, 0x1e, 0x03, 0x00, 0x00, 0x23, 0x69, 0x6e, 0x63, 0x6c, // r..@.P.....#incl
	0x75, 0x64, 0x65, 0x20, 0x3c, 0x6d, 0x65, 0x74, 0x61, 0x6c, 0x5f, 0x73, 0x74, 0x64, 0x6c, 0x69, // ude <metal_stdli
	0x62, 0x3e, 0x0a, 0x23, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65, 0x20, 0x3c, 0x73, 0x69, 0x6d, // b>.#include <sim
	0x64, 0x2f, 0x73, 0x69, 0x6d, 0x64, 0x2e, 0x68, 0x3e, 0x0a, 0x0a, 0x75, 0x73, 0x69, 0x6e, 0x67, // d/simd.h>..using
	0x20, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65, 0x20, 0x6d, 0x65, 0x74, 0x61, 0x6c, //  namespace metal
	0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x5f, 0x47, 0x6c, 0x6f, 0x62, 0x61, // ;..struct _Globa
	0x6c, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x75, // l.{.    float4 u
	0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, // _imageLodEnabled
	0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, 0x73, // ;.    float4 u_s
	0x77, 0x69, 0x7a, 0x7a, 0x6c, 0x65, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x73, 0x74, 0x72, 0x75, // wizzle;.};..stru
	0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, // ct xlatMtlMain_o
	0x75, 0x74, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x20, // ut.{.    float4 
	0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x20, 0x5b, // bgfx_FragData0 [
	0x5b, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x3b, 0x0a, 0x7d, 0x3b, 0x0a, // [color(0)]];.};.
	0x0a, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x20, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, // .struct xlatMtlM
	0x61, 0x69, 0x6e, 0x5f, 0x69, 0x6e, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, // ain_in.{.    flo
	0x61, 0x74, 0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x20, // at2 v_texcoord0 
	0x5b, 0x5b, 0x75, 0x73, 0x65, 0x72, 0x28, 0x6c, 0x6f, 0x63, 0x6e, 0x30, 0x29, 0x5d, 0x5d, 0x3b, // [[user(locn0)]];
	0x0a, 0x7d, 0x3b, 0x0a, 0x0a, 0x66, 0x72, 0x61, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x78, 0x6c, // .};..fragment xl
	0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x78, 0x6c, // atMtlMain_out xl
	0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x28, 0x78, 0x6c, 0x61, 0x74, 0x4d, 0x74, // atMtlMain(xlatMt
	0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x69, 0x6e, 0x20, 0x69, 0x6e, 0x20, 0x5b, 0x5b, 0x73, 0x74, // lMain_in in [[st
	0x61, 0x67, 0x65, 0x5f, 0x69, 0x6e, 0x5d, 0x5d, 0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61, // age_in]], consta
	0x6e, 0x74, 0x20, 0x5f, 0x47, 0x6c, 0x6f, 0x62, 0x61, 0x6c, 0x26, 0x20, 0x5f, 0x6d, 0x74, 0x6c, // nt _Global& _mtl
	0x5f, 0x75, 0x20, 0x5b, 0x5b, 0x62, 0x75, 0x66, 0x66, 0x65, 0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, // _u [[buffer(0)]]
	0x2c, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x32, 0x64, 0x3c, 0x66, 0x6c, 0x6f, 0x61, // , texture2d<floa
	0x74, 0x3e, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x5b, 0x5b, // t> s_texColor [[
	0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x2c, 0x20, 0x73, 0x61, // texture(0)]], sa
	0x6d, 0x70, 0x6c, 0x65, 0x72, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, // mpler s_texColor
	0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x20, 0x5b, 0x5b, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, // Sampler [[sample
	0x72, 0x28, 0x30, 0x29, 0x5d, 0x5d, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x78, 0x6c, // r(0)]]).{.    xl
	0x61, 0x74, 0x4d, 0x74, 0x6c, 0x4d, 0x61, 0x69, 0x6e, 0x5f, 0x6f, 0x75, 0x74, 0x20, 0x6f, 0x75, // atMtlMain_out ou
	0x74, 0x20, 0x3d, 0x20, 0x7b, 0x7d, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x6c, 0x6f, 0x61, // t = {};.    floa
	0x74, 0x20, 0x5f, 0x31, 0x36, 0x30, 0x20, 0x3d, 0x20, 0x64, 0x6f, 0x74, 0x28, 0x73, 0x5f, 0x74, // t _160 = dot(s_t
	0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2e, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x28, 0x73, // exColor.sample(s
	0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x53, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, // _texColorSampler
	0x2c, 0x20, 0x69, 0x6e, 0x2e, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, // , in.v_texcoord0
	0x2c, 0x20, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x28, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x75, // , level(_mtl_u.u
	0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, // _imageLodEnabled
	0x2e, 0x78, 0x29, 0x29, 0x2c, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x75, 0x5f, 0x73, // .x)), _mtl_u.u_s
	0x77, 0x69, 0x7a, 0x7a, 0x6c, 0x65, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x75, 0x74, // wizzle);.    out
	0x2e, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x44, 0x61, 0x74, 0x61, 0x30, 0x20, // .bgfx_FragData0 
	0x3d, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x34, 0x28, 0x5f, 0x31, 0x36, 0x30, 0x2c, 0x20, 0x5f, // = float4(_160, _
	0x31, 0x36, 0x30, 0x2c, 0x20, 0x5f, 0x31, 0x36, 0x30, 0x2c, 0x20, 0x30, 0x2e, 0x32, 0x30, 0x30, // 160, _160, 0.200
	0x30, 0x30, 0x30, 0x30, 0x30, 0x32, 0x39, 0x38, 0x30, 0x32, 0x33, 0x32, 0x32, 0x33, 0x38, 0x37, // 0000029802322387
	0x36, 0x39, 0x35, 0x33, 0x31, 0x32, 0x35, 0x20, 0x2b, 0x20, 0x28, 0x30, 0x2e, 0x38, 0x30, 0x30, // 6953125 + (0.800
	0x30, 0x30, 0x30, 0x30, 0x31, 0x31, 0x39, 0x32, 0x30, 0x39, 0x32, 0x38, 0x39, 0x35, 0x35, 0x30, // 0000119209289550
	0x37, 0x38, 0x31, 0x32, 0x35, 0x20, 0x2a, 0x20, 0x5f, 0x6d, 0x74, 0x6c, 0x5f, 0x75, 0x2e, 0x75, // 78125 * _mtl_u.u
	0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, // _imageLodEnabled
	0x2e, 0x79, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, // .y));.    return
	0x20, 0x6f, 0x75, 0x74, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00, 0x00, 0x20, 0x00,                   //  out;.}.... .
};
extern const uint8_t* fs_imgui_image_swizz_pssl;
extern const uint32_t fs_imgui_image_swizz_pssl_size;
