#version 120

// Input from vertex shader
varying vec3 v_fragPos;
varying vec3 v_normal;
varying vec2 v_texCoord;

// Material properties
uniform vec3 u_materialAmbient;
uniform vec3 u_materialDiffuse;
uniform vec3 u_materialSpecular;
uniform float u_materialShininess;

// Shading model
uniform int u_shadingModel; // 0=Lambert, 1=Gouraud, 2=Phong, 3=Blinn-Phong, 4=PBR, 5=Flat

// Lights (up to 4)
uniform int u_numLights;

// Light uniforms (same as before)
uniform int u_light0Type;
uniform vec3 u_light0Color;
uniform float u_light0Intensity;
uniform vec3 u_light0Position;
uniform vec3 u_light0Direction;
uniform float u_light0ConstantAtt;
uniform float u_light0LinearAtt;
uniform float u_light0QuadraticAtt;
uniform float u_light0SpotCutoff;
uniform float u_light0SpotExponent;

uniform int u_light1Type;
uniform vec3 u_light1Color;
uniform float u_light1Intensity;
uniform vec3 u_light1Position;
uniform vec3 u_light1Direction;
uniform float u_light1ConstantAtt;
uniform float u_light1LinearAtt;
uniform float u_light1QuadraticAtt;
uniform float u_light1SpotCutoff;
uniform float u_light1SpotExponent;

uniform int u_light2Type;
uniform vec3 u_light2Color;
uniform float u_light2Intensity;
uniform vec3 u_light2Position;
uniform vec3 u_light2Direction;
uniform float u_light2ConstantAtt;
uniform float u_light2LinearAtt;
uniform float u_light2QuadraticAtt;
uniform float u_light2SpotCutoff;
uniform float u_light2SpotExponent;

uniform int u_light3Type;
uniform vec3 u_light3Color;
uniform float u_light3Intensity;
uniform vec3 u_light3Position;
uniform vec3 u_light3Direction;
uniform float u_light3ConstantAtt;
uniform float u_light3LinearAtt;
uniform float u_light3QuadraticAtt;
uniform float u_light3SpotCutoff;
uniform float u_light3SpotExponent;

// Global settings
uniform vec3 u_viewPos;
uniform vec3 u_globalAmbient;

// Tone mapping
uniform float u_exposure;
uniform float u_contrast;

// ========== LIGHTING CALCULATIONS ==========

vec3 calculateDiffuseLambert(vec3 normal, vec3 lightDir, vec3 lightColor, float intensity) {
    float diff = max(dot(normal, lightDir), 0.0);
    return u_materialDiffuse * lightColor * diff * intensity;
}

vec3 calculateSpecularPhong(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 lightColor, float intensity) {
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_materialShininess);
    return u_materialSpecular * lightColor * spec * intensity;
}

vec3 calculateSpecularBlinnPhong(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 lightColor, float intensity) {
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), u_materialShininess);
    return u_materialSpecular * lightColor * spec * intensity;
}

float calculateAttenuation(float dist, float constant, float linear, float quadratic) {
    return 1.0 / (constant + linear * dist + quadratic * (dist * dist));
}

float calculateSpotEffect(vec3 lightDir, vec3 spotDir, float cutoff, float exponent) {
    float spotCos = dot(lightDir, -spotDir);
    float cutoffCos = cos(radians(cutoff));
    
    if (spotCos > cutoffCos) {
        return pow(spotCos, exponent);
    }
    return 0.0;
}

vec3 processLight(
    int lightType,
    vec3 lightColor,
    float lightIntensity,
    vec3 lightPosition,
    vec3 lightDirection,
    float constAtt,
    float linearAtt,
    float quadAtt,
    float spotCutoff,
    float spotExponent,
    vec3 normal,
    vec3 viewDir
) {
    vec3 result = vec3(0.0);
    
    // DIRECTIONAL LIGHT
    if (lightType == 1) {
        vec3 lightDir = normalize(-lightDirection);
        
        // Diffuse
        result += calculateDiffuseLambert(normal, lightDir, lightColor, lightIntensity);
        
        // Specular
        if (u_shadingModel == 2 || u_shadingModel == 4) { // Phong or PBR
            result += calculateSpecularPhong(normal, lightDir, viewDir, lightColor, lightIntensity);
        } else if (u_shadingModel == 3) { // Blinn-Phong
            result += calculateSpecularBlinnPhong(normal, lightDir, viewDir, lightColor, lightIntensity);
        }
    }
    // POINT LIGHT
    else if (lightType == 2) {
        vec3 lightDir = normalize(lightPosition - v_fragPos);
        float distance = length(lightPosition - v_fragPos);
        float attenuation = calculateAttenuation(distance, constAtt, linearAtt, quadAtt);
        
        // Diffuse
        result += calculateDiffuseLambert(normal, lightDir, lightColor, lightIntensity) * attenuation;
        
        // Specular
        if (u_shadingModel == 2 || u_shadingModel == 4) {
            result += calculateSpecularPhong(normal, lightDir, viewDir, lightColor, lightIntensity) * attenuation;
        } else if (u_shadingModel == 3) {
            result += calculateSpecularBlinnPhong(normal, lightDir, viewDir, lightColor, lightIntensity) * attenuation;
        }
    }
    // SPOT LIGHT
    else if (lightType == 3) {
        vec3 lightDir = normalize(lightPosition - v_fragPos);
        float distance = length(lightPosition - v_fragPos);
        float attenuation = calculateAttenuation(distance, constAtt, linearAtt, quadAtt);
        float spotEffect = calculateSpotEffect(lightDir, normalize(lightDirection), spotCutoff, spotExponent);
        
        // Diffuse
        result += calculateDiffuseLambert(normal, lightDir, lightColor, lightIntensity) * attenuation * spotEffect;
        
        // Specular
        if (u_shadingModel == 2 || u_shadingModel == 4) {
            result += calculateSpecularPhong(normal, lightDir, viewDir, lightColor, lightIntensity) * attenuation * spotEffect;
        } else if (u_shadingModel == 3) {
            result += calculateSpecularBlinnPhong(normal, lightDir, viewDir, lightColor, lightIntensity) * attenuation * spotEffect;
        }
    }
    
    return result;
}

// ========== NON-REALISTIC SHADING ==========

vec3 celShading(vec3 color, vec3 normal, vec3 viewDir) {
    // Get main light direction (use first light if available, else default)
    vec3 lightDir = normalize(vec3(1.0, -1.0, 0.5));
    if (u_numLights > 0 && u_light0Type == 1) {
        lightDir = normalize(-u_light0Direction);
    }
    
    float intensity = max(dot(normal, lightDir), 0.0);
    
    // Quantize to discrete levels (default 4 levels)
    int levels = 4;
    intensity = floor(intensity * float(levels)) / float(levels);
    
    // Add edge detection for outlines
    float edge = max(0.0, dot(normal, viewDir));
    if (edge < 0.3) {
        return vec3(0.0); // Black outline
    }
    
    return color * max(intensity, 0.2); // Minimum 20% brightness
}

vec3 goochShading(vec3 normal) {
    // Get main light direction
    vec3 lightDir = normalize(vec3(1.0, -1.0, 0.5));
    if (u_numLights > 0 && u_light0Type == 1) {
        lightDir = normalize(-u_light0Direction);
    }
    
    float t = (dot(normal, lightDir) + 1.0) * 0.5;
    
    // Warm color (lit areas) and cool color (shadow areas)
    vec3 warmColor = vec3(1.0, 0.8, 0.4);  // Warm yellow-orange
    vec3 coolColor = vec3(0.2, 0.3, 0.7);  // Cool blue
    
    return mix(coolColor, warmColor, t);
}

void main() {
    vec3 normal = normalize(v_normal);
    vec3 viewDir = normalize(u_viewPos - v_fragPos);
    
    // ✅ FIX: Start with globalAmbient directly (not multiplied by materialAmbient)
    vec3 finalColor = u_globalAmbient / 255.0;  // Convert from 0-255 to 0-1
    
    // ========== FLAT SHADING ==========
    if (u_shadingModel == 5) {
        // Just use material diffuse color with ambient
        finalColor = finalColor + u_materialDiffuse;
    }
    // ========== CEL/TOON SHADING (7.5) ==========
    else if (u_shadingModel == 6) {
        finalColor = celShading(u_materialDiffuse, normal, viewDir);
    }
    // ========== GOOCH SHADING (7.5) ==========
    else if (u_shadingModel == 7) {
        finalColor = goochShading(normal);
    }
    // ========== REALISTIC SHADING ==========
    else {
        // Add material ambient contribution
        finalColor = finalColor * u_materialAmbient;
        
        // Process all lights
        if (u_numLights > 0) {
            finalColor += processLight(u_light0Type, u_light0Color, u_light0Intensity, u_light0Position, u_light0Direction,
                                       u_light0ConstantAtt, u_light0LinearAtt, u_light0QuadraticAtt, u_light0SpotCutoff, u_light0SpotExponent,
                                       normal, viewDir);
        }
        if (u_numLights > 1) {
            finalColor += processLight(u_light1Type, u_light1Color, u_light1Intensity, u_light1Position, u_light1Direction,
                                       u_light1ConstantAtt, u_light1LinearAtt, u_light1QuadraticAtt, u_light1SpotCutoff, u_light1SpotExponent,
                                       normal, viewDir);
        }
        if (u_numLights > 2) {
            finalColor += processLight(u_light2Type, u_light2Color, u_light2Intensity, u_light2Position, u_light2Direction,
                                       u_light2ConstantAtt, u_light2LinearAtt, u_light2QuadraticAtt, u_light2SpotCutoff, u_light2SpotExponent,
                                       normal, viewDir);
        }
        if (u_numLights > 3) {
            finalColor += processLight(u_light3Type, u_light3Color, u_light3Intensity, u_light3Position, u_light3Direction,
                                       u_light3ConstantAtt, u_light3LinearAtt, u_light3QuadraticAtt, u_light3SpotCutoff, u_light3SpotExponent,
                                       normal, viewDir);
        }
    }
    
    // Tone mapping
    finalColor = finalColor * u_exposure;
    finalColor = (finalColor - 0.5) * u_contrast + 0.5;
    
    // Clamp
    finalColor = clamp(finalColor, 0.0, 1.0);
    
    gl_FragColor = vec4(finalColor, 1.0);
}
