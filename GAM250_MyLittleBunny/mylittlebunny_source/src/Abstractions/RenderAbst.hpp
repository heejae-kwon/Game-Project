/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      RenderAbst.hpp
Purpose:        The abstraction for the rendering api we use (in this case OpenGl)
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <WIP/Texture.hpp>
#include <WIP/Shader.hpp>

#include <sdl/SDL.h>
#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace BE
{

    //!  RenderAbst(raction) class. 
    /*!
     RenderAbst is our rendering abstraction class.
     It serves as an interface of sorts between our engine and our rendering API (OpenGL in this case).
     This keeps things nice and seperate and makes it easier if we ever want to change the graphics API that we are using.
     This class is used to interact with "low level" OpenGL code.
    */
    class RenderAbst
    {
        // All type redefinitions go here
    protected:
        using RenderAbstSmartPtr = std::unique_ptr<RenderAbst>;

    public:
        static RenderAbst*  instance() //!< Returns an instance of the class
        {
            static RenderAbstSmartPtr instance(new RenderAbst());
            return instance.get();
        }
        ~RenderAbst();

        void        createOpenGlContext();  //!< Initializes OpenGl and at the moment loads and compiles a vertex and fragment shader.
        void        initShader();
        void        initRenderData();

        void        setViewport();

        void        setView(glm::vec2 cameraPos, float zoom);
        void        clearWindowBuffer(glm::vec3 clearCol_); //!< Clears the window buffer.

        Texture*    createTexture(const GLchar* fileName_, GLboolean alpha_);        //!< Loads an image file and creates a texture from it.

        void        drawSprite(Texture& texture_, glm::vec3 position, glm::vec2 size, GLfloat rotate, glm::vec4 color);
        void        drawShape(glm::vec3 position, glm::vec2 size, GLfloat rotate, glm::vec4 color);  //!< Draws the outline of a quad.
        void        drawCircle(glm::vec3 position, glm::vec2 size, glm::vec4 color); //!< Draws a circles on screen, used for debugging physics
        void        drawRect(glm::vec3 position, glm::vec2 size, glm::vec4 color); //!< Draws a rectangle on screen, used for background color
    protected:
        //
    private:
        RenderAbst();   //!< ImGuiAbst's constructor is private as it is a Singleton and should only be accessed through the instance() function.

        void initQuad();
        void initCircle(float cx, float cy, float r, int num_segments);

    public:
        glm::ivec2*  _screenSize;
        glm::ivec2  viewport;
    protected:
        //
    private:
        Shader _spriteShader;  /*!< The sprite render shader*/

        GLuint _quadVBO, _quadVAO;   /*!< VAO and VBO for the quad used for most texture rendering*/
        GLuint _circVBO, _circVAO, nbrIndex;   /*!< VAO and VBO for the quad used for most texture rendering*/
    };
}