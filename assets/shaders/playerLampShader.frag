// lightShader.frag
uniform sampler2D texture;
uniform vec2 resolution;

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution;
    
    // Простейшее размытие: берем среднее значение из ближайших пикселей
    vec4 color = vec4(0.0);
    float total = 0.0;
    float offset = 1.0 / resolution.x; // можно добавить разные смещения для x и y

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            vec2 samplePos = uv + vec2(x, y) * offset;
            vec4 sample = texture2D(texture, samplePos);
            float weight = 1.0;
            color += sample * weight;
            total += weight;
        }
    }
    
    color /= total;
    gl_FragColor = color;
}