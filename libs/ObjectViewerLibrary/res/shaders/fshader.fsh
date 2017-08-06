//uniform sampler2D qt_Texture0;
//varying highp vec2 qt_TexCoord0;

//void main(void)
//{
//    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0);
//}


uniform sampler2D u_texture;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower;
uniform highp vec4 u_colorSpecular;

varying highp vec2 v_texcoord;
varying highp vec3 v_normal;
varying highp vec4 v_position;

void main(void)
{
    vec4 resultColor = vec4(0,0,0,0);
    vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0); // позиция - точка,а не вектор
    vec4 diffMatColor = texture2D(u_texture, v_texcoord);
    vec3 eyeVector = normalize(v_position.xyz - eyePosition.xyz);
    vec3 lightVect = normalize(v_position.xyz - u_lightPosition.xyz);
    vec3 reflectLight = normalize(reflect(lightVect, v_normal));
    float len = 10.0; //length(v_position.xyz - eyePosition.xyz); //  расстояние от наблюдателя до рассматриваемой точки
    float specularFactor = 50.0; // обратная величина размеру пятна блика
    float ambientFactor = 0.5; // свечение материала

    // свет источника
    vec4 diffColor = diffMatColor * u_lightPower * max(0.0, dot(v_normal, -lightVect) / (1.0 + 0.25 * pow(len, 2.0) ));
    resultColor += diffColor;

    // свечение материала
    vec4 ambientColor = ambientFactor * diffMatColor;
    resultColor += ambientColor;

    // блики
//    vec4 specularColor = u_colorSpecular * u_lightPower * pow(max(0.0, dot( reflectLight, -eyeVector )), specularFactor) / (1.0 + 0.25 * pow(len, 2.0) );
//    resultColor += specularColor;

    gl_FragColor = resultColor;
//    gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );
//    gl_FragColor = texture2D(u_texture, v_texcoord);
}
