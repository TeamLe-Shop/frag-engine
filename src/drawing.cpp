#include "drawing.hpp"

#include "fragengine.hpp"

#include <glew.h>
#include <stdio.h>

#include <fstream>

namespace frag {

VertexArray::VertexArray(GLfloat* v, size_t l)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vertices = new GLfloat[l];
    length = l;
    memcpy(vertices, v, l * sizeof(GLfloat));
}

void VertexArray::delete_data()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void VertexArray::set_as_current()
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

GLuint VertexArray::upload(GLenum usage)
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, length * sizeof(GLfloat), vertices, usage);

    log(DEVELOPER, "Uploaded %d vertex data bytes to graphics card",
        length * sizeof(GLfloat));

    return vbo;
}

GLuint create_shader(GLenum type, std::string source)
{
    GLuint shader = glCreateShader(type);
    const char* source_string_ptr = source.c_str();
    glShaderSource(shader, 1, &source_string_ptr, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_TRUE) {
        log(DEVELOPER, "Shader compiled successfully");
    } else {
        log(DEVELOPER, "Shader failed to compile");
    }

    char buffer[256];
    memset(buffer, 0, 256);
    glGetShaderInfoLog(shader, 256, NULL, buffer);
    log(DEVELOPER, "Compile log: %s", buffer);

    return shader;
}

GLuint create_shader_from_file(GLenum type, std::string file)
{
    std::ifstream shaderFile(file);
    std::string contents((std::istreambuf_iterator<char>(shaderFile)),
                        std::istreambuf_iterator<char>());

    return create_shader(type, contents);
}

GLuint create_shader_program(int shader_count, ...)
{
    int i;
    GLuint program = glCreateProgram();
    va_list args;

    va_start(args, shader_count);

    for (i = 0; i < shader_count; i++) {
        GLuint shader = va_arg(args, GLuint);
        glAttachShader(program, shader);
        log(DEVELOPER, "Attached shader to program");
    }

    va_end(args);

    glBindFragDataLocation(program, 0, "outColor");
    glLinkProgram(program);
    return program;
}

}
