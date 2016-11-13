#include "drawing.hpp"

#include "fragengine.hpp"

#include <glew.h>
#include <stdio.h>

#include <fstream>
#include <glm/gtc/type_ptr.hpp>

namespace frag {

VertexArray::VertexArray(GLfloat* v, size_t l,  GLuint shaderprogram,
                         GLuint* element_order, size_t order_len)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    shader_program = shaderprogram;

    vertices = new GLfloat[l];
    length = l;
    memcpy(vertices, v, l * sizeof(GLfloat));

    if (element_order) {
        order = new GLuint[order_len];
        order_length = order_len;
        memcpy(order, element_order, order_len * sizeof(GLuint));
    }
}

void VertexArray::delete_data()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void VertexArray::bind()
{
    glBindVertexArray(vao);
    glUseProgram(shader_program);
}

GLuint VertexArray::upload(GLenum usage)
{
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, length * sizeof(GLfloat), vertices, usage);

    if (order) {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, order_length * sizeof(GLuint),
                     order, usage);
    }

    log(DEVELOPER, "Uploaded %d vertex data bytes, uploaded %d element array "
        "bytes", length * sizeof(GLfloat), order_length * sizeof(GLuint));

    return vbo;
}

void VertexArray::set_layout(VertexAttribute* attrs, size_t len)
{
    bind();

    int i;
    size_t stride = 0;
    size_t offset = 0;
    VertexAttribute va;

    // Calculate "stride"
    for (i = 0; i < len; i++) {
        va = attrs[i];
        stride += va.length_bytes;
    }

    for (i = 0; i < len; i++) {
        va = attrs[i];

        GLint attrib = glGetAttribLocation(shader_program, va.name.c_str());
        glEnableVertexAttribArray(attrib);
        glVertexAttribPointer(attrib, va.length_elements, va.type, GL_FALSE,
                              stride, (void*)(offset));

        offset += va.length_bytes;
    }
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

GLuint create_shader_program(std::string colattr, int shader_count, ...)
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

    glBindFragDataLocation(program, 0, colattr.c_str());
    glLinkProgram(program);
    return program;
}


const void push_matrix(Matrix mat, GLint attr_ref)
{
    matrix_stack->push(mat);
    glUniformMatrix4fv(attr_ref, 1, GL_FALSE, glm::value_ptr(mat));
}


const Matrix pop_matrix(GLint attr_ref)
{
    matrix_stack->pop();
    Matrix ret;
    if (!matrix_stack->size()) {
        ret = glm::mat4();
    } else {
        ret = matrix_stack->top();
    }
    glUniformMatrix4fv(attr_ref, 1, GL_FALSE, glm::value_ptr(ret));
    return ret;
}

}
