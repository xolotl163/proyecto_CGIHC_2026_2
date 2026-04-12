#version 330 core

in vec2 TexCoord;
in vec3 ourColor;
out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture; //se usa para decidir si usar textura o solo los colores del modelo

void main()
{
    vec4 finalColor;

    if(useTexture){
        finalColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
    }else{
        finalColor = vec4(ourColor, 1.0);
    }

    if(finalColor.a < 0.1)
        discard;

    FragColor = finalColor;
}