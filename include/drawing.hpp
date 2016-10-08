#pragma once

#include <stddef.h>
#include <string>
#include <glew.h>

namespace frag {

class VertexArray {
public:
    VertexArray(GLfloat* vertices, size_t length);

    void delete_buffers();

    GLuint upload(GLenum usage);

public:
    GLuint vbo;

private:
    GLfloat* vertices;
    size_t length;
};

/// Create a shader with chosen type and attempt to compile
///
/// type - Type of shader (e.g. GL_VERTEX_SHADER)
/// source - Shader source code string
/// log - Compile log, can be left NULL
GLuint create_shader(GLenum type, std::string source);

GLuint create_shader_from_file(GLenum type, std::string file);

/// Combine given shaders into a program.
GLuint create_shader_program(int shader_count, ...);

};
