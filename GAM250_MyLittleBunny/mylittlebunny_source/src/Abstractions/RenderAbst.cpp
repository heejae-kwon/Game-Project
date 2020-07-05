/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      RenderAbst.cpp
Purpose:        The abstraction for the rendering api we use (in this case OpenGl)
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski, Wonjae Jung
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Abstractions/RenderAbst.hpp>
#include <Abstractions/WindowAbst.hpp>
#include <Utilities/BagOfGoodies.hh>
#include <Core/Debugger.hpp>

#include <SOIL/SOIL.h>

#include <sstream>
#include <cassert>

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>\n"
"out vec2 TexCoords;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"uniform mat4 spriteCoord;\n"
"uniform int vertMode; // 1 for nothing 2 for textured coord\n"
"void main()\n"
"{\n"
"if (vertMode == 1) {\n"
//"TexCoords = vertex.zw;\n"
"} else if (vertMode == 2) {"
"vec4 TexCoordsTmp = spriteCoord * vec4(vertex.zw, 0.0, 1.0);\n"
"TexCoords = vec2(TexCoordsTmp.x, TexCoordsTmp.y);\n"
"}\n"
"gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);\n"
"}\0";


const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec2 TexCoords;\n"
"out vec4 color;\n"
"uniform sampler2D image;\n"
"uniform vec4 spriteColor;\n"
"uniform int fragMode; // 1 for color only 2 for textured mode\n"
"void main()\n"
"{\n"
"if (fragMode == 1) {\n"
"color = spriteColor;\n"
"} else if (fragMode == 2) {\n"
"color = spriteColor * texture(image, TexCoords);\n"
"}\n"
"}\0";


BE::RenderAbst::RenderAbst() :
    viewport{1280, 720}
{
    WindowAbst::instance()->createWindow(); // We make sure that a window has already been created
    _screenSize = &WindowAbst::instance()->_windowSize;
}

BE::RenderAbst::~RenderAbst()
{
    glDeleteVertexArrays(1, &_quadVAO);
}

void
BE::RenderAbst::createOpenGlContext()
{
    if (gl3wInit())
    {
        BoG::emergencyMessageLogger("failed to initialize OpenGL");
        assert(1 == 0);
    }
    if (!gl3wIsSupported(3, 2)) {
        BoG::emergencyMessageLogger("OpenGL 3.2 not supported");
        assert(1 == 0);
    }

    // OpenGL configuration
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    initShader();
    setViewport();
    initRenderData();
}

void BE::RenderAbst::initShader()
{
    _spriteShader.Compile(vertexShaderSource, fragmentShaderSource, nullptr);

//    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(_screenSize->x), 0.f, static_cast<GLfloat>(_screenSize->y), -10.0f, 10.0f);
    _spriteShader.Use();
    _spriteShader.SetInteger("image", 0);
//    _spriteShader.SetMatrix4("projection", projection);
}

void BE::RenderAbst::initRenderData()
{
    initQuad();
    initCircle(0.f, 0.f, 1, 120);
}

void BE::RenderAbst::initQuad()
{
    // Configure VAO/VBO
    GLfloat vertices[] = {
        // Pos      // Tex
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f,

        1.0f, 1.0f, 1.0f, -1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f
    };

    glGenVertexArrays(1, &_quadVAO);
    glGenBuffers(1, &_quadVBO);

    glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(_quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void BE::RenderAbst::initCircle(float cx, float cy, float r, int num_segments)
{
    std::vector<GLfloat> vertices;
    float theta = 2.f * 3.1415926f / float(num_segments);
    float tangetial_factor = tanf(theta);//calculate the tangential factor 

    float radial_factor = cosf(theta);//calculate the radial factor 

    float x = r;//we start at angle = 0 

    float y = 0;

    for (int ii = 0; ii <= num_segments; ii++)
    {
        vertices.push_back(x + cx);
        vertices.push_back(y + cy);
                                    //calculate the tangential vector 
                                   //remember, the radial vector is (x, y) 
                                   //to get the tangential vector we flip those coordinates and negate one of them 

        float tx = -y;
        float ty = x;

        //add the tangential vector 

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        //correct using the radial factor 

        x *= radial_factor;
        y *= radial_factor;
    }

    glGenVertexArrays(1, &_circVAO);
    glGenBuffers(1, &_circVBO);

    glBindBuffer(GL_ARRAY_BUFFER, _circVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(_circVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    nbrIndex = static_cast<int>(vertices.size()) / 2;
}


void
BE::RenderAbst::setViewport()
{
    // Let's start by clearing the whole screen with black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // This is your target virtual resolution for the game, the size you built your game to
    int virtual_width = viewport.x;
    int virtual_height = viewport.y;

    float targetAspectRatio = static_cast<float>(virtual_width) / static_cast<float>(virtual_height);

    // figure out the largest area that fits in this resolution at the desired aspect ratio
    int width = _screenSize->x;
    int height = (int)(width / targetAspectRatio + 0.5f);

    if (height > _screenSize->y)
    {
        //It doesn't fit our height, we must switch to pillarbox then
        height = _screenSize->y;
        width = (int)(height * targetAspectRatio + 0.5f);
    }

    // set up the new viewport centered in the backbuffer
    int vp_x = (_screenSize->x / 2) - (width / 2);
    int vp_y = (_screenSize->y / 2) - (height / 2);

    glViewport(vp_x, vp_y, width, height);
}

void BE::RenderAbst::setView(glm::vec2 cameraPos, float zoom)
{
    float _screenWidth = static_cast<GLfloat>(viewport.x);
    float _screenHeight = static_cast<GLfloat>(viewport.y);
    glm::mat4 projection = glm::ortho(-(_screenWidth / 2) * zoom, (_screenWidth / 2) * zoom, -(_screenHeight / 2) * zoom, (_screenHeight / 2) * zoom, -10.0f, 10.0f);
    _spriteShader.SetMatrix4("projection", projection);

    // Prepare transformations
    glm::mat4 view{};
    view = glm::translate(view, glm::vec3(cameraPos.x, cameraPos.y, 0.f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    _spriteShader.SetMatrix4("view", view);
}

void
BE::RenderAbst::clearWindowBuffer(glm::vec3 clearCol_)
{
    glClearColor(clearCol_.r, clearCol_.g, clearCol_.b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

BE::Texture*
BE::RenderAbst::createTexture(const GLchar* fileName_, GLboolean alpha_)
{
    // Create Texture object
    Texture* texture = new Texture();
    if (alpha_)
    {
        texture->Internal_Format = GL_RGBA;
        texture->Image_Format = GL_RGBA;
    }
    // Load image
    int width, height;
    unsigned char* image = SOIL_load_image(fileName_, &width, &height, 0, texture->Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

    if (image == 0)
    {
        Core::Debugger::instance()->AddLog("[ERROR][RenderAbst] Failed to load texture: %s\n", fileName_);
        return nullptr;
    }

    // Now generate texture
    texture->Generate(width, height, image);
    // And finally free image data
    SOIL_free_image_data(image);
    return texture;
}

void BE::RenderAbst::drawSprite(Texture& texture_, glm::vec3 position, glm::vec2 size, GLfloat rotate, glm::vec4 color)
{
    // Prepare transformations
    glm::mat4 model;
    position.x -= size.x / 2;
    position.y -= size.y / 2;

    model = glm::translate(model, position);  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    glm::mat4 model2; // Used to draw specific parts of the texture

    model2 = glm::translate(model2, glm::vec3(texture_.spriteCoord, 0));
    model2 = glm::scale(model2, glm::vec3(texture_.spriteSize, 0));

    _spriteShader.SetMatrix4("model", model);
    _spriteShader.SetMatrix4("spriteCoord", model2);
    _spriteShader.SetVector4f("spriteColor", color);
    _spriteShader.SetInteger("vertMode", 2);
    _spriteShader.SetInteger("fragMode", 2);

    glActiveTexture(GL_TEXTURE0);
    texture_.Bind();

    glBindVertexArray(_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void
BE::RenderAbst::drawShape(glm::vec3 position, glm::vec2 size, GLfloat rotate, glm::vec4 color)
{
    // Prepare transformations
    glm::mat4 model;
    position.x -= size.x / 2;
    position.y -= size.y / 2;
    model = glm::translate(model, position);  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    glm::mat4 model2; // Used to draw specific parts of the texture

    _spriteShader.SetMatrix4("model", model);
    _spriteShader.SetVector4f("spriteColor", color);
    _spriteShader.SetInteger("vertMode", 1);
    _spriteShader.SetInteger("fragMode", 1);

    glBindVertexArray(_quadVAO);
    glDrawArrays(GL_LINE_STRIP, 0, 5);
    glBindVertexArray(0);
}

void
BE::RenderAbst::drawCircle(glm::vec3 position, glm::vec2 size, glm::vec4 color)
{
    // Prepare transformations
    glm::mat4 model;
    model = glm::translate(model, position);  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    _spriteShader.SetMatrix4("model", model);
    _spriteShader.SetVector4f("spriteColor", color);
    _spriteShader.SetInteger("vertMode", 1);
    _spriteShader.SetInteger("fragMode", 1);

    glBindVertexArray(_circVAO);
    glDrawArrays(GL_LINE_STRIP, 0, nbrIndex);
    glBindVertexArray(0);
}

void BE::RenderAbst::drawRect(glm::vec3 position, glm::vec2 size, glm::vec4 color)
{
    // Prepare transformations
    glm::mat4 model;
    position.x -= size.x / 2;
    position.y -= size.y / 2;
    model = glm::translate(model, position);  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    glm::mat4 model2; // Used to draw specific parts of the texture

    _spriteShader.SetMatrix4("model", model);
    _spriteShader.SetVector4f("spriteColor", color);
    _spriteShader.SetInteger("vertMode", 1);
    _spriteShader.SetInteger("fragMode", 1);

    glBindVertexArray(_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
