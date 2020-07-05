/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Draw.cpp
Purpose:        Draw is the core in charge of rendering
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski, Wonjae Jung
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Core/Draw.hpp>
#include <Core/Debugger.hpp>
#include <Abstractions/RenderAbst.hpp>
#include <Abstractions/WindowAbst.hpp>
#include <Components\Components.hh>

BE::Core::Draw::Draw()
    : BaseCore(), _clearBufferCol(0.f)
{
    BaseCore::_coreStringId = "Draw";

    RenderAbst::instance()->createOpenGlContext();  // we need to make sure that OpenGl has been initialized before we can initialize Dear Imgui
}

void
BE::Core::Draw::startNewFrame()
{
    BaseCore::startNewFrame();  // You should ALWAYSE call the Core's base functions as we are extending the base functions
    {
        RenderAbst::instance()->clearWindowBuffer(_clearBufferCol);
        {
            RenderAbst::instance()->setView(glm::vec2(0.f, 0.f), 1.f);
            BE::RenderAbst::instance()->drawRect(glm::vec3(0.f, 0.f, 0.f), glm::vec2(1280.f, 720.f), glm::vec4(24.f / 255.f, 24.f / 255.f, 48.f / 255.f, 1.f));

            Component::Transform* cameraPos = getCurrentCamera()->getComponent<Component::Transform>();
            Component::Camera* cameraParam = getCurrentCamera()->getComponent<Component::Camera>();

            RenderAbst::instance()->setView(cameraPos->position, cameraParam->zoom);
        }
    }
    BaseCore::updateExecTime();
}

void
BE::Core::Draw::update(float dt_)
{
    BaseCore::update();  // You should ALWAYSE call the Core's base functions as we are extending the base functions
    {
        for (uint32_t i = _actorOffset.top(); i < _actorVec.size(); ++i)
        {
            if (_actorVec[i]->_isActive || _actorVec[i]->_isSelected)
            {
                if (!_actorVec[i]->_isActive) // If the actor is selected but inactive don't update the animation
                {
                    dt_ = 0.f;
                }
                if (isOnScreen(_actorVec[i]))
                {
                    Component::Transform* transformComponent = _actorVec[i]->getComponent<Component::Transform>();
                    Component::Display* displayComponent = getComponent(_actorVec[i]);

                    Prop::Image::imageData image = displayComponent->getTexture(dt_);
                    glm::vec3 position = transformComponent->position + image.posOffest;
                    glm::vec2 scale = transformComponent->scale + image.scaleOffest;

                    if (displayComponent->drawType == Component::Display::DrawType::SPRITE) // If it's a sprite then we take the Camera's position in consideration
                    {
                        // Setting camera view
                        {
                            Component::Transform* cameraPos = getCurrentCamera()->getComponent<Component::Transform>();
                            Component::Camera* cameraParam = getCurrentCamera()->getComponent<Component::Camera>();

                            if (position.z <= -2.f)
                            {
                                glm::vec2 newPosition(cameraPos->position);
                                newPosition.x /= position.z * position.z;
                                newPosition.y /= position.z * position.z;
                                RenderAbst::instance()->setView(newPosition, cameraParam->zoom);
                            }
                            else
                            {
                                RenderAbst::instance()->setView(cameraPos->position, cameraParam->zoom);
                            }
                        }

                        // Adding zOffset to z position
                        // This is a sneaky little trick to stop 2 quad to be drawn exactly on top of each other
                        position.z += displayComponent->zOffset;
                    }
                    else if (displayComponent->drawType == Component::Display::DrawType::HUD)
                    {
                        RenderAbst::instance()->setView(glm::vec2(0.f), 1.f);
                    }

                    if (_actorVec[i]->_isActive)
                    {
                        RenderAbst::instance()->drawSprite(*image.texture, position, image.spriteSize * scale, glm::radians(static_cast<float>(transformComponent->rotation + image.rotation)), image.color);
                    }
                    if (_actorVec[i]->_isSelected)
                    {
                        RenderAbst::instance()->drawShape(position, image.spriteSize * scale, glm::radians(static_cast<float>(transformComponent->rotation)), glm::vec4(1.f, 1.f, 1.f, 1.f));
                    }
                }
            }
        }
    }

    // Setting camera view
    {
        Component::Transform* cameraPos = getCurrentCamera()->getComponent<Component::Transform>();
        Component::Camera* cameraParam = getCurrentCamera()->getComponent<Component::Camera>();

        RenderAbst::instance()->setView(cameraPos->position, cameraParam->zoom);
    }

    BaseCore::updateExecTime();
}

void
BE::Core::Draw::endOfFrame()
{
    BaseCore::endOfFrame();  // You should ALWAYSE call the Core's base functions as we are extending the base functions
    {
        WindowAbst::instance()->flipWindowBuffer();
    }
    BaseCore::updateExecTime();
    BaseCore::flushExecTimeLog();
}

void BE::Core::Draw::registerActor(Actor * actor_)
{
    BaseCore::registerActor(actor_);

    // This was to sort the sprites back to front but I'm going to gave to do it with lists I think
    for (uint32_t i = _actorOffset.top(); i < _actorVec.size(); ++i)
    {
        if (i != _actorOffset.top())
        {
            Component::Transform* transformPrev = _actorVec[i - 1]->getComponent<Component::Transform>();
            Component::Transform* transformCurr = _actorVec[i]->getComponent<Component::Transform>();
            if (transformCurr->position.z < transformPrev->position.z)
            {
                std::swap(_actorVec[i - 1], _actorVec[i]);
                i = _actorOffset.top();
            }
        }
    }
}

void
BE::Core::Draw::addCamera(Actor * actor_)
{
    _cameraStack.push(actor_);
}

BE::Actor*
BE::Core::Draw::getCurrentCamera()
{
    if (_cameraStack.size() <= 0)
    {
        // Adding a default camera
        {
            BE::Actor* defaultActor = Actor::createActor("defaultCamera", false);
            defaultActor->addComponent<Component::Camera>();
        }
    }
    return _cameraStack.top();
}

void
BE::Core::Draw::removeCurrentCamera()
{
    if (_cameraStack.size() > 0)
    {
        _cameraStack.pop();
    }
    else
    {
        Core::Debugger::instance()->AddLog("[WARNING][Draw::%s] Trying to remove a camera when none have been registered", __func__);
    }
}

void
BE::Core::Draw::setClearBufferColor(glm::vec3 color_)
{
    return;
    _clearBufferCol = color_;
}

BE::Actor*
BE::Core::Draw::checkSpriteOverlap(glm::vec4 point_)
{
    glm::vec2 screen;
    glm::vec2 camera;

    screen.x = point_[0];
    screen.y = point_[1];
    camera.x = point_[2];
    camera.y = point_[3];

    Actor* retVal = nullptr;
    for (uint32_t i = _actorOffset.top(); i < _actorVec.size(); ++i)
    {
        if (_actorVec[i]->_isActive || _actorVec[i]->_isSelected)
        {
            if (isOnScreen(_actorVec[i]))
            {
                Component::Transform* transform = _actorVec[i]->getComponent<Component::Transform>();
                Component::Display* display = getComponent(_actorVec[i]);

                glm::vec3 actorPos = transform->position;
                glm::vec2 actorScale = transform->scale;
                glm::vec2 spriteSize = display->getTexture(0.f).spriteSize * actorScale;

                if (display->drawType == Component::Display::HUD)
                {
                    if (actorPos.x - (spriteSize.x / 2) < screen.x && actorPos.x + (spriteSize.x / 2) > screen.x &&
                        actorPos.y - (spriteSize.y / 2) < screen.y && actorPos.y + (spriteSize.y / 2) > screen.y)
                    {
                        if (retVal == nullptr || transform->position.z > retVal->getComponent<Component::Transform>()->position.z)
                        {
                            retVal = _actorVec[i];
                        }
                    }
                }
                else if (display->drawType == Component::Display::SPRITE)
                {

                    if (actorPos.x - (spriteSize.x / 2) < camera.x && actorPos.x + (spriteSize.x / 2) > camera.x &&
                        actorPos.y - (spriteSize.y / 2) < camera.y && actorPos.y + (spriteSize.y / 2) > camera.y)
                    {
                        if (retVal == nullptr || transform->position.z > retVal->getComponent<Component::Transform>()->position.z)
                        {
                            retVal = _actorVec[i];
                        }
                    }
                }
            }
        }
    }
    return retVal;
}

void
BE::Core::Draw::updateSort()
{
    for (uint32_t i = _actorOffset.top(); i < _actorVec.size(); ++i)
    {
        if (i != _actorOffset.top())
        {
            Component::Transform*   transformPrev = _actorVec[i - 1]->getComponent<Component::Transform>();
            Component::Display*     displayPrev = getComponent(_actorVec[i - 1]);
            Component::Transform*   transformCurr = _actorVec[i]->getComponent<Component::Transform>();
            Component::Display*     displayCurr = getComponent(_actorVec[i]);

            if (transformCurr->position.z + displayCurr->zOffset < transformPrev->position.z + displayPrev->zOffset)
            {
                std::swap(_actorVec[i - 1], _actorVec[i]);
                i = _actorOffset.top();
            }
            else if (transformCurr->position.z + displayCurr->zOffset == transformPrev->position.z + displayPrev->zOffset)
            {
                displayCurr->zOffset += .0001f;
            }
        }
    }
}

BE::Component::Display *
BE::Core::Draw::getComponent(Actor *actor_)
{
    Component::Display *display = actor_->getComponent<Component::Display>();
    if (display == nullptr)
    {
        display = &actor_->getComponent<Component::ParticleEmitter>()->_texture;
    }
    return display;
}

bool
BE::Core::Draw::isOnScreen(Actor *actor_)
{
    Component::Display *display = getComponent(actor_);

    glm::vec2 cameraPosition = getCurrentCamera()->getComponent<Component::Transform>()->position;
    float cameraZoom = getCurrentCamera()->getComponent<Component::Camera>()->zoom;
    glm::vec2 viewportRangeX = { 0, 1280 };
    glm::vec2 viewportRangeY = { 0, 720 };

    if (display->drawType == Component::Display::HUD)
    {
        cameraPosition = glm::vec2(0.f, 0.f);
    }

    viewportRangeX -= viewportRangeX[1] / 2;
    viewportRangeY -= viewportRangeY[1] / 2;
    viewportRangeX *= cameraZoom;
    viewportRangeY *= cameraZoom;
    viewportRangeX -= cameraPosition.x;
    viewportRangeY -= cameraPosition.y;

    if (actor_->getComponent<Component::Transform>()->position.z <= -2.f) // This is a filthy filthy hack
        return true;
    glm::vec2 actorPos = actor_->getComponent<Component::Transform>()->position;
    glm::vec2 actorScale = actor_->getComponent<Component::Transform>()->scale;
    glm::vec2 spriteSize = getComponent(actor_)->getTexture(0.f).spriteSize * actorScale;
    float sizeDiff = spriteSize.x - spriteSize.y;
    if (sizeDiff > 0)
    {
        spriteSize.y = spriteSize.x;
    }
    else if (sizeDiff < 0)
    {
        spriteSize.x = spriteSize.y;
    }
    glm::vec2 spriteRangeX = { actorPos.x - (spriteSize.x / 2), actorPos.x + (spriteSize.x / 2) };
    glm::vec2 spriteRangeY = { actorPos.y - (spriteSize.y / 2), actorPos.y + (spriteSize.y / 2) };

    if ((spriteRangeX[1] > viewportRangeX[0] && spriteRangeX[0] < viewportRangeX[1]) &&
        (spriteRangeY[1] > viewportRangeY[0] && spriteRangeY[0] < viewportRangeY[1]))
    {
        return true;
    }
    return false;
}

void BE::Core::Draw::resetSelected()
{
    for (uint32_t i = 0; i < _actorVec.size(); ++i)
    {
        _actorVec[i]->_isSelected = false;
    }
}
