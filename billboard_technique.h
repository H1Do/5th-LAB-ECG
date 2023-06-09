/*
        Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BILLBOARD_TECHNIQUE_H
#define	BILLBOARD_TECHNIQUE_H

#include "technique.h"
#include "technique.cpp"
#include "math_3d.h"
#include "math_3d.cpp"

class BillboardTechnique : public Technique 
{
public:
    
    BillboardTechnique();
 
    virtual bool Init();
    
    void SetVP(const Matrix4f& VP);
    void SetCameraPosition(const Vector3f& Pos);
    void SetColorTextureUnit(unsigned int TextureUnit);
    void SetBillboardSize(float BillboardSize);
    
private:

    GLuint m_VPLocation;
    GLuint m_cameraPosLocation;
    GLuint m_colorMapLocation;
    GLuint m_billboardSizeLocation;

    const char* pVS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
layout (location = 0) in vec3 Position;                                             \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = vec4(Position, 1.0);                                              \n\
}                                                                                   \n\
";


   const char* pGS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
layout(points) in;                                                                  \n\
layout(triangle_strip) out;                                                         \n\
layout(max_vertices = 4) out;                                                       \n\
                                                                                    \n\
uniform mat4 gVP;                                                                   \n\
uniform vec3 gCameraPos;                                                            \n\
uniform float gBillboardSize;                                                       \n\
                                                                                    \n\
out vec2 TexCoord;                                                                  \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    vec3 Pos = gl_in[0].gl_Position.xyz;                                            \n\
    vec3 toCamera = normalize(gCameraPos - Pos);                                    \n\
    vec3 up = vec3(0.0, 1.0, 0.0);                                                  \n\
    vec3 right = cross(toCamera, up) * gBillboardSize;                              \n\
                                                                                    \n\
    Pos -= right;                                                                   \n\
    gl_Position = gVP * vec4(Pos, 1.0);                                             \n\
    TexCoord = vec2(0.0, 0.0);                                                      \n\
    EmitVertex();                                                                   \n\
                                                                                    \n\
    Pos.y += gBillboardSize;                                                        \n\
    gl_Position = gVP * vec4(Pos, 1.0);                                             \n\
    TexCoord = vec2(0.0, 1.0);                                                      \n\
    EmitVertex();                                                                   \n\
                                                                                    \n\
    Pos.y -= gBillboardSize;                                                        \n\
    Pos += right;                                                                   \n\
    gl_Position = gVP * vec4(Pos, 1.0);                                             \n\
    TexCoord = vec2(1.0, 0.0);                                                      \n\
    EmitVertex();                                                                   \n\
                                                                                    \n\
    Pos.y += gBillboardSize;                                                        \n\
    gl_Position = gVP * vec4(Pos, 1.0);                                             \n\
    TexCoord = vec2(1.0, 1.0);                                                      \n\
    EmitVertex();                                                                   \n\
                                                                                    \n\
    EndPrimitive();                                                                 \n\
}                                                                                   \n\
";

    const char* pFS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
uniform sampler2D gColorMap;                                                        \n\
                                                                                    \n\
in vec2 TexCoord;                                                                   \n\
out vec4 FragColor;                                                                 \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    FragColor = texture2D(gColorMap, TexCoord);                                     \n\
                                                                                    \n\
    if (FragColor.r >= 0.9 && FragColor.g >= 0.9 && FragColor.b >= 0.9) {           \n\
        discard;                                                                    \n\
    }                                                                               \n\
}";
};

#endif	/* BILLBOARD_TECHNIQUE_H */

