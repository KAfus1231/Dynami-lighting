#ifdef GL_ES
precision mediump float;
#endif

// uniform-переменные, передаваемые из SFML:
uniform sampler2D texture;  // Твоя текстура, содержащая маску (полигон raycasting)
uniform vec2 resolution;    // Размер текстуры (например, 1000x1000)
uniform vec2 lightPos;      // Позиция фонаря в пикселях (например, в тех же координатах, что gl_FragCoord)

// Параметры для затухания света (настрой под себя)
const float radius = 150.0;  // Радиус, в пределах которого свет максимально яркий
const float falloff = 50.0;  // Зона плавного перехода от яркости к темноте

void main()
{
    // Текущие координаты пикселя
    vec2 fragCoord = gl_FragCoord.xy;
    vec2 correctedLightPos = lightPos;
    // Нормализуем координаты (0..1), если потребуется, но здесь работаем в пикселях
    // vec2 uv = fragCoord / resolution;
    
    // Получаем значение маски из текстуры
    // Предполагается, что в маске в альфа-канале заложена форма света (из raycasting)
    vec4 maskColor = texture2D(texture, fragCoord / resolution);
    float mask = maskColor.a;
    
    // Вычисляем расстояние от текущего пикселя до источника света (фонаря)
    float dist = distance(fragCoord, correctedLightPos);
    
    // Вычисляем ослабление света по расстоянию:
    // Если расстояние меньше radius, intensity=1,
    // если больше (radius+falloff) — intensity=0, а между плавно.
    float intensity = 1.0 - smoothstep(radius, radius + falloff, dist);
    
    // Итоговая альфа — это произведение маски и интенсивности,
    // что означает: если маска не определена (0), свет отсутствует; если маска=1, свет регулируется по расстоянию.
    float finalAlpha = mask * intensity;
    
    // Цвет фонаря: теплый желтоватый свет
    vec3 lightColor = vec3(1.0, 1.0, 0.8);
    
    gl_FragColor = vec4(lightColor, finalAlpha);
}