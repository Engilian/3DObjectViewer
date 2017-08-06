attribute highp vec4 a_position;
attribute highp vec3 a_texcoord;
uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_viewMatrix;
varying highp vec2 v_texcoord;

void main(void)
{
    mat4 viewMatrix = u_viewMatrix;
    viewMatrix[3][0] = 0;
    viewMatrix[3][1] = 0;
    viewMatrix[3][2] = 0;
    gl_Position = u_projectionMatrix *  viewMatrix * a_position;
    v_texcoord = a_texcoord;
}
