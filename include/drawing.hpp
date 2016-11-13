/// @file
/// @brief Various drawing/OpenGL related functions & types/classes

#pragma once

#include <stddef.h>
#include <string>
#include <stack>
#include <glew.h>
#include <glm.hpp>

namespace frag {

/// Struct representing a vertex attribute.
struct VertexAttribute {
    std::string name;
    GLenum type;
    size_t length_bytes;
    size_t length_elements;
};

using Matrix = glm::mat4;
using MatrixStack = std::stack<Matrix>;

MatrixStack* matrix_stack = new MatrixStack();

/// A vertex array. Instances of VertexArray store a VBO, VAO and EBO reference.
class VertexArray {
public:
    /// Create a new VertexArray
    ///
    /// vertices - Pointer to the vertex data.
    ///
    /// length - Length of vertex data array in bytes.
    ///
    /// element_order - Pointer to elements array data.
    ///
    /// order_length - Length of elements array data in bytes.
    VertexArray(GLfloat* vertices, size_t length, GLuint shaderprogram,
                GLuint* element_order = nullptr, size_t order_length = 0);

    /// Free all used up memory, including vertex buffer/array objects.
    void delete_data();

    /// Bind this VertexArray's VBO/VAO.
    void bind();

    /// Upload the vertex data of this VertexArray.
    GLuint upload(GLenum usage);

    /// Set the layout of the vertex attributes in the vertex array.
    void set_layout(VertexAttribute* layout, size_t len);

public:
    GLuint vbo = 0; // Vertex Buffer Object
    GLuint vao = 0; // Vertex Array Object
    GLuint ebo = 0; // Element Buffer Object

private:
    GLfloat* vertices = nullptr;
    GLuint* order = nullptr;
    GLuint shader_program = 0;
    size_t length = 0;
    size_t order_length = 0;
};

/// Create a shader with chosen type and attempt to compile
///
/// type - Type of shader (e.g. GL_VERTEX_SHADER)
///
/// source - Shader source code string
///
/// log - Compile log, can be left NULL
GLuint create_shader(GLenum type, std::string source);

GLuint create_shader_from_file(GLenum type, std::string file);

/// Combine given shaders into a program.
///
/// shader_count - Amount of shaders. After this argument you can specify an
/// indefinite amount of shaders.
GLuint create_shader_program(std::string colattr, int shader_count, ...);

/// Preserve a matrix on the engine's matrix stack.
const void push_matrix(Matrix mat, GLint attr_ref);

/// Pop topmost matrix.
const Matrix pop_matrix(GLint attr_ref);

};
