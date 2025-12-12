#version 120

// Input attributes
attribute vec3 position;
attribute vec3 normal;
attribute vec2 texcoord;

// Uniforms
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

// Output to fragment shader
varying vec3 v_fragPos;
varying vec3 v_normal;
varying vec2 v_texCoord;

void main() {
    // Transform position
    gl_Position = modelViewProjectionMatrix * vec4(position, 1.0);
    
    // Pass world-space position to fragment shader
    v_fragPos = vec3(modelViewMatrix * vec4(position, 1.0));
    
    // Transform normal to world space
    v_normal = normalMatrix * normal;
    
    // Pass texture coordinates
    v_texCoord = texcoord;
}
