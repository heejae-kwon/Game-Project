/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      DearImguiHelperFunc.cpp
Purpose:        I'm not proud of this one, it got out of hand. These are all the functions for all tools in the game engine
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Utilities/DearImGuiHelperFunc.hh>
#include <Utilities/FileHandler.hh>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>
#include <Utilities/crc32.hh>
#include <BunnyEngine.hpp>
#include <Abstractions/RenderAbst.hpp>
#include <Components\Components.hh>
#include <WIP/PropManager.hpp>

void
BE::DImGuiHelperFunc::ExampleAppLog::Draw(const char* title, bool* p_opened)
{
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
    ImGui::Begin(title, p_opened);
    if (ImGui::Button("Clear")) Clear();
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    ImGui::SameLine();
    Filter.Draw("Filter", -100.0f);
    ImGui::Separator();
    ImGui::BeginChild("scrolling");
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
    if (copy) ImGui::LogToClipboard();

    if (Filter.IsActive())
    {
        const char* buf_begin = Buf.begin();
        const char* line = buf_begin;
        for (int line_no = 0; line != NULL; line_no++)
        {
            const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
            if (Filter.PassFilter(line, line_end))
                ImGui::TextUnformatted(line, line_end);
            line = line_end && line_end[1] ? line_end + 1 : NULL;
        }
    }
    else
    {
        ImGui::TextUnformatted(Buf.begin());
    }

    if (ScrollToBottom)
        ImGui::SetScrollHere(1.0f);
    ScrollToBottom = false;
    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::End();
}

void
BE::DImGuiHelperFunc::FpsTracker::setValue(uint32_t drawTime_, uint32_t eventTime_, uint32_t physicsTime_, uint32_t debugTime_, uint32_t particleTime_)
{
    drawCoreExecTime = drawTime_;
    eventCoreExecTime = eventTime_;
    physicsCoreExecTime = physicsTime_;
    debugCoreExecTime = debugTime_;
    particleCoreExecTime = particleTime_;
}

void
BE::DImGuiHelperFunc::FpsTracker::Draw(const char* title, bool* p_opened)
{
    ImGui::SetNextWindowSize(ImVec2(400, 100), ImGuiSetCond_FirstUseEver);
    ImGui::Begin(title, p_opened);
    ImGui::Text("DrawCore: %d ms/frame", drawCoreExecTime);
    ImGui::Text("EventCore: %d ms/frame", eventCoreExecTime);
    ImGui::Text("PhysicsCore: %d ms/frame", physicsCoreExecTime);
    ImGui::Text("DebuggerCore: %d ms/frame", debugCoreExecTime);
    ImGui::Text("ParticleCore: %d ms/frame", particleCoreExecTime);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

void
BE::DImGuiHelperFunc::ActorViewer::Draw(const char* title, bool* p_opened)
{
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiSetCond_FirstUseEver);
    ImGui::Begin(title, p_opened);
    {
        std::vector<BE::Actor*>& actorVec = BE::Core::Debugger::instance()->getRegisteredActors();
        std::vector<BE::Actor*>::iterator activeActorVec = BE::Core::Debugger::instance()->getActiveRegisteredActors();
        uint32_t activeActorOffset = BE::Core::Debugger::instance()->getActiveActorOffset();

        // left
        {
            static size_t selected = 0;
            if (selected >= actorVec.size() - activeActorOffset)
            {
                selected = 0;
                currentSelectedActor = nullptr;
            }
            else
            {
                currentSelectedActor = activeActorVec[selected];
            }

            // Adding and Removing actors
            ImGui::BeginChild("left pane", ImVec2(280, ImGui::GetWindowHeight() - 30), false);
            {
                // The list of all active actors
                ImGui::BeginChild("left pane", ImVec2(280, ImGui::GetWindowHeight() - 50), true);
                {
                    if (ImGui::CollapsingHeader("Saved Actors", ImGuiTreeNodeFlags_DefaultOpen))
                    {
                        for (size_t i = 0; i < actorVec.size(); ++i)
                        {
                            if (actorVec[i]->_saveActor)
                            {
                                ImGui::PushID(static_cast<int>(i));
                                {
                                    char label[128];
                                    sprintf_s(label, "%s", (actorVec[i])->_name.data());
                                    if (ImGui::Selectable(label, selected == i) || (actorVec[i])->_isSelected)
                                    {
                                        if (!actorVec[i]->_isSelected)
                                        {
                                            Core::Draw::instance()->resetSelected();
                                        }
                                        selected = i;
                                        currentSelectedActor = actorVec[i];
                                        if (currentSelectedActor->getComponent<Component::Display>())
                                        {
                                            currentSelectedActor->_isSelected = true;
                                        }
                                    }
                                }
                                ImGui::PopID();
                            }
                        }
                    }
                    if (ImGui::CollapsingHeader("Temporary Actors", ImGuiTreeNodeFlags_DefaultOpen))
                    {
                        for (size_t i = 0; i < actorVec.size(); ++i)
                        {
                            if (!actorVec[i]->_saveActor)
                            {
                                ImGui::PushID(static_cast<int>(i));
                                {
                                    char label[128];
                                    sprintf_s(label, "%s", (actorVec[i])->_name.data());
                                    if (ImGui::Selectable(label, selected == i) || (actorVec[i])->_isSelected)
                                    {
                                        if (!actorVec[i]->_isSelected)
                                        {
                                            Core::Draw::instance()->resetSelected();
                                        }
                                        selected = i;
                                        currentSelectedActor = actorVec[i];
                                        if (currentSelectedActor->getComponent<Component::Display>())
                                        {
                                            currentSelectedActor->_isSelected = true;
                                        }
                                    }
                                }
                                ImGui::PopID();
                            }
                        }
                    }
                }
                ImGui::EndChild();

                if (ImGui::Button("Add"))
                {
                    if (Engine::BunnyEngine::instance()->getActiveStage() != nullptr)
                    {
                        Actor* newActor = Actor::createActor("newActor", true);
                        newActor->addComponent<Component::Transform>();
                        newActor->_saveActor = true;
                        Engine::BunnyEngine::instance()->getActiveStage()->addActor(newActor);
                    }
                    else
                    {
                        Core::Debugger::instance()->AddLog("[WARNING][ActorViewer::%s] You can only add an actor when a valid scene has been loaded", __func__);
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Remove"))
                {
                    if (currentSelectedActor != nullptr)
                    {
                        std::cout << "Remove !\n";
                        Engine::BunnyEngine::instance()->getActiveStage()->removeActor(currentSelectedActor);
                        currentSelectedActor = nullptr;
                        selected = 0;
                    }
                }
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();

        // right
        {
            if (currentSelectedActor != nullptr)
            {
                float textWidth;
                float buttonSpacing;

                if (ImGui::GetWindowWidth() < 700)
                {
                    textWidth = 300 - (700 - ImGui::GetWindowWidth());
                    buttonSpacing = textWidth + 10;
                }
                else
                {
                    textWidth = 300;
                    buttonSpacing = 310;
                }

                ImGui::BeginGroup();
                {
                    // Actor name + active state
                    {
                        static char buf1[32] = "";
                        ImGui::Text("Actor name: %s\n", currentSelectedActor->_name.c_str());
                        ImGui::PushItemWidth(textWidth);
                        {
                            if (ImGui::InputText("", buf1, 32, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
                            {
                                currentSelectedActor->_name = buf1;
                                buf1[0] = '\0';
                            }
                            ImGui::PopItemWidth();
                        }
                        ImGui::SameLine(buttonSpacing);
                        ImGui::Checkbox("Active", &currentSelectedActor->_isActive);

                    }
                    // Actor component's
                    {
                        currentSelectedActor->drawComponentData();
                    }
                    // Adding and removing components
                    ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing())); // Leave room for 1 line below us
                    {
                        ImGui::Separator();
                        // To add and remove components
                        ImGui::PushItemWidth(120);
                        {
                            ImGui::Combo("Component", &compoSelected, "NONE\0TRANSFORM\0DISPLAY\0CAMERA\0RIGIDBODY\0CIRCLE_COLLIDE\0PARTICLEEMITTER\0GAMEPLAY\0\0");
                        }
                        ImGui::PopItemWidth();
                        ImGui::SameLine();

                        if (ImGui::Button("Add"))
                        {
                            switch (compoSelected)
                            {
                            case 1:
                            {
                                if (currentSelectedActor->getComponent<Component::Transform>() == nullptr)
                                {
                                    Core::Debugger::instance()->AddLog("[WARNING][ActorViewer::%s] Don't do that...", __func__);
                                    //currentSelectedActor->addComponent<Component::Transform>();
                                }
                                break;
                            }
                            case 2:
                            {
                                if (currentSelectedActor->getComponent<Component::Display>() == nullptr)
                                {
                                    currentSelectedActor->addComponent<Component::Display>();
                                }
                                break;
                            }
                            case 3:
                            {
                                if (currentSelectedActor->getComponent<Component::Camera>() == nullptr)
                                {
                                    currentSelectedActor->addComponent<Component::Camera>();
                                }
                                break;
                            }
                            case 4:
                            {
                                if (currentSelectedActor->getComponent<Component::Rigidbody>() == nullptr)
                                {
                                    currentSelectedActor->addComponent<Component::Rigidbody>();
                                }
                                break;
                            }
                            case 5:
                            {
                                if (currentSelectedActor->getComponent<Component::CircleCollider>() == nullptr)
                                {
                                    currentSelectedActor->addComponent<Component::CircleCollider>();
                                }
                                break;
                            }
                            case 6:
                            {
                                if (currentSelectedActor->getComponent<Component::ParticleEmitter>() == nullptr)
                                {
                                    currentSelectedActor->addComponent<Component::ParticleEmitter>();
                                }
                                break;
                            }
                            case 7:
                            {
                                if (currentSelectedActor->getComponent<Component::Gameplay>() == nullptr)
                                {
                                    currentSelectedActor->addComponent<Component::Gameplay>();
                                }
                                break;
                            }
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Remove"))
                        {
                            switch (compoSelected)
                            {
                            case 1:
                            {
                                Core::Debugger::instance()->AddLog("[WARNING][ActorViewer::%s] Don't do that...", __func__);
                                //currentSelectedActor->removeComponent<Component::Transform>();
                                break;
                            }
                            case 2:
                            {
                                currentSelectedActor->removeComponent<Component::Display>();
                                break;
                            }
                            case 3:
                            {
                                currentSelectedActor->removeComponent<Component::Camera>();
                                break;
                            }
                            case 4:
                            {
                                currentSelectedActor->removeComponent<Component::Rigidbody>();
                                break;
                            }
                            case 5:
                            {
                                currentSelectedActor->removeComponent<Component::CircleCollider>();
                                break;
                            }
                            case 6:
                            {
                                currentSelectedActor->removeComponent<Component::ParticleEmitter>();
                                break;
                            }
                            case 7:
                            {
                                currentSelectedActor->removeComponent<Component::Gameplay>();
                                break;
                            }
                            }
                        }
                    }
                    ImGui::EndChild();
                }
                ImGui::EndGroup();
            }
        }
    }
    ImGui::End();
}


void
BE::DImGuiHelperFunc::PropViewer::searchForProps()
{
    std::string filetype = "prop";
    std::vector<std::string> propFiles = BE::getFilesFromDirByType(formatPath("./Data/Props/"), filetype);
    filetype = "png";
    std::vector<std::string> pngFiles = BE::getFilesFromDirByType(formatPath("./Data/Textures/"), filetype);
    filetype = "jpeg";
    std::vector<std::string> jpegFiles = BE::getFilesFromDirByType(formatPath("./Data/Textures/"), filetype);
    filetype = "mp3";
    std::vector<std::string> mp3Files = BE::getFilesFromDirByType(formatPath("./Data/Audio/"), filetype);
    filetype = "wav";
    std::vector<std::string> wavFiles = BE::getFilesFromDirByType(formatPath("./Data/Audio/"), filetype);
    filetype = "ogg";
    std::vector<std::string> oggFiles = BE::getFilesFromDirByType(formatPath("./Data/Audio/"), filetype);



    availableProps.resize(0);
    availableImage.resize(0);
    availableSound.resize(0);

    for (auto fileName : propFiles)
    {
        availableProps.push_back(fileName);
    }
    for (auto fileName : pngFiles)
    {
        availableImage.push_back(fileName);
    }
    for (auto fileName : jpegFiles)
    {
        availableImage.push_back(fileName);
    }
    for (auto fileName : mp3Files)
    {
        availableSound.push_back(fileName);
    }
    for (auto fileName : wavFiles)
    {
        availableSound.push_back(fileName);
    }
	for (auto fileName : oggFiles)
    {
        availableSound.push_back(fileName);
    }


}

void
BE::DImGuiHelperFunc::PropViewer::Draw(const char * title, bool * p_opened)
{
    ImGui::SetNextWindowSize(ImVec2(600, 450), ImGuiSetCond_Once);
    ImGui::Begin(title, p_opened);
    {
        if (createMode == false)
        {
            std::vector<Prop::BaseProp*>& propVec = PropManager::instance()->getProps();
            // left
            {
                static size_t selectedProp = 0;
                if (selectedProp >= propVec.size())
                {
                    selectedProp = 0;
                    currentSelectedProp = nullptr;
                }
                else
                {
                    currentSelectedProp = propVec[selectedProp];
                }
                static size_t fileSelected = 0;
                if (fileSelected >= availableProps.size())
                {
                    fileSelected = 0;
                    currentSelectedFile = nullptr;
                }
                else
                {
                    currentSelectedFile = &availableProps[fileSelected];
                }

                ImGui::BeginChild("Props", ImVec2(ImGui::GetWindowWidth() * .6f, ImGui::GetWindowHeight() - 50), false);
                {
                    ImGui::BeginChild("Props", ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() - 70), true);
                    {
                        if (ImGui::CollapsingHeader("Loaded Props", ImGuiTreeNodeFlags_DefaultOpen))
                        {
                            ImGui::Indent();
                            {
                                for (size_t i = 0; i < propVec.size(); ++i)
                                {
                                    //static constexpr unsigned int errHash = "err"_crc32;
                                    if (propVec[i]->id != "err")
                                    {
                                        ImGui::PushID(static_cast<int>(i));
                                        {
                                            char label[128];
                                            sprintf_s(label, "%s [%s]", (propVec[i])->id.c_str(), (propVec[i])->fileName.c_str());
                                            if (ImGui::Selectable(label, selectedProp == i))
                                            {
                                                selectedProp = i;
                                                currentSelectedProp = propVec[i];
                                            }
                                        }
                                        ImGui::PopID();
                                    }
                                }
                            }
                            ImGui::Unindent();
                            if (ImGui::Button("Remove"))
                            {
                                if (currentSelectedProp != nullptr)
                                {
                                    Engine::BunnyEngine::instance()->getActiveStage()->removeProp(currentSelectedProp);
                                    PropManager::instance()->removeEntry(currentSelectedProp);
                                    currentSelectedProp = nullptr;
                                    selectedProp = 0;
                                }
                            }
                        }
                        if (ImGui::CollapsingHeader("Available Props", ImGuiTreeNodeFlags_DefaultOpen))
                        {
                            static bool propIsSelected = false;

                            if (availableProps.size() < 1)
                            {
                                searchForProps();
                            }
                            ImGui::Indent();
                            {
                                for (size_t i = 0; i < availableProps.size(); ++i)
                                {
                                    ImGui::PushID(static_cast<int>(i));
                                    {
                                        char label[128];
                                        sprintf_s(label, "%s", (availableProps[i].c_str()));
                                        if (!PropManager::instance()->isFileLoaded(availableProps[i]))
                                        {
                                            if (ImGui::Selectable(label, fileSelected == i, ImGuiSelectableFlags_AllowDoubleClick))
                                            {
                                                fileSelected = i;
                                                currentSelectedFile = &(availableProps[i]);
                                            }
                                            if (ImGui::IsMouseDoubleClicked(0))
                                            {
                                                propIsSelected = true;

                                            }
                                        }
                                    }
                                    ImGui::PopID();
                                }
                            }
                            ImGui::Unindent();
                            if (ImGui::Button("Add") || propIsSelected)
                            {
                                if (currentSelectedFile != nullptr)
                                {
                                    propIsSelected = false;
                                    if (Engine::BunnyEngine::instance()->getActiveStage() == nullptr)
                                    {
                                        Core::Debugger::instance()->AddLog("[WARNING][PropViewer::%s] You cannot create a Prop without having a loaded Stage\n", __func__);
                                        Core::Debugger::instance()->AddLog("[ERR][PropViewer::%s] Failed to add prop", __func__);
                                    }
                                    else
                                    {
                                        BE::Prop::BaseProp* tmpPropPtr;
                                        Json::Value data;
                                        if (JsonReader::readFile("./Data/Props/" + *currentSelectedFile, data))
                                        {
                                            if ((tmpPropPtr = PropManager::instance()->createPropFromFile(*currentSelectedFile, data)) != nullptr)
                                            {
                                                Engine::BunnyEngine::instance()->getActiveStage()->addProp(tmpPropPtr);
                                            }
                                        }
                                        else
                                        {
                                            Core::Debugger::instance()->AddLog("[ERR][BaseStage::%s] %s file could not be loaded\n", __func__, currentSelectedFile->c_str());
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                ImGui::EndChild();

                if (ImGui::Button("Refresh"))
                {
                    searchForProps();
                }
                ImGui::NewLine();
                if (ImGui::Button("CREATE NEW >"))
                {
                    createMode = true;
                }


                ImGui::EndChild();
                ImGui::SameLine();
            }
            // right
            {
                if (currentSelectedProp != nullptr)
                {
                    float textWidth = 160;

                    ImGui::BeginGroup();
                    {
                        static char buf1[32] = "";
                        ImGui::Text("Prop Id: %s\n", currentSelectedProp->id.c_str());
                        ImGui::PushItemWidth(textWidth);
                        {
                            if (ImGui::InputText("##prop id", buf1, 32, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
                            {
                                if (std::string(buf1) == "err")
                                {
                                    Core::Debugger::instance()->AddLog("[WARNING][PropViewer::%s] Please don't use the id \"err\" as it is reserved\n", __func__);
                                }
                                else
                                {
                                    currentSelectedProp->id = buf1;
                                    buf1[0] = '\0';
                                    PropManager::instance()->updateEntry(currentSelectedProp);
                                }
                            }
                        }
                        ImGui::PopItemWidth();

                        currentSelectedProp->drawData();

                        ImGui::Separator();

                        if (ImGui::Button("Save"))
                        {
                            if (currentSelectedProp != nullptr)
                            {
                                Json::Value outData;
                                currentSelectedProp->writeData(outData);
                                JsonWriter::write(outData, "./Data/Props/" + currentSelectedProp->fileName);
                                Core::Debugger::instance()->AddLog("[LOG][PropViewer::%s] Saved %s in %s\n", __func__, currentSelectedProp->fileName.c_str(), "./Data/Props/");
                            }
                        }
                    }
                    ImGui::EndGroup();
                }
            }
        }
        else
        {
            if (ImGui::Button("< BACK"))
            {
                createMode = false;
            }

            float textWidth = 160;

            static char buf1[32] = "";
            ImGui::Text("Prop Id: %s\n", buf1);
            ImGui::PushItemWidth(textWidth);
            {
                ImGui::InputText("", buf1, 32, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank);
            }
            ImGui::PopItemWidth();


            // Modify draw type
            ImGui::Combo("Draw Type", &ddType, "Image\0Audio\0Animation\0\0");


            if (ddType == 0) // IMAGE CREATION
            {
                static size_t imageSelected = 0;
                if (imageSelected >= availableImage.size())
                {
                    imageSelected = 0;
                    currentSelectedFile = nullptr;
                }
                else
                {
                    currentSelectedFile = &availableImage[imageSelected];
                }


                if (ImGui::CollapsingHeader("Available Image(s)", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    if (availableImage.size() < 1)
                    {
                        searchForProps();
                    }
                    ImGui::Indent();
                    {
                        for (size_t i = 0; i < availableImage.size(); ++i)
                        {
                            ImGui::PushID(static_cast<int>(i));
                            {
                                char label[128];
                                sprintf_s(label, "%s", (availableImage[i].c_str()));
                                if (!PropManager::instance()->isFileLoaded(availableImage[i] + ".prop") &&
                                    !JsonReader::fileExists("./Data/Props/" + availableImage[i] + ".prop"))
                                {
                                    if (ImGui::Selectable(label, imageSelected == i) || currentSelectedImage == nullptr)
                                    {
                                        imageSelected = i;
                                        currentSelectedImage = &(availableImage[i]);
                                    }
                                }
                            }
                            ImGui::PopID();
                        }
                    }
                    ImGui::Unindent();
                }
                if (ImGui::Button("Create") && currentSelectedImage != nullptr)
                {
                    if (std::string(buf1) == "err")
                    {
                        Core::Debugger::instance()->AddLog("[WARNING][PropViewer::%s] Please don't use the id \"err\" as it is reserved\n", __func__);
                    }
                    else
                    {
                        if (PropManager::instance()->isFileLoaded(*currentSelectedImage + ".prop") ||
                            JsonReader::fileExists("./Data/Props/" + *currentSelectedImage + ".prop"))
                        {
                            Core::Debugger::instance()->AddLog("[WARNING][PropViewer::%s] Please select another Image as this one has already been created\n", __func__);
                        }
                        else
                        {
                            Prop::BaseProp* tmpPropPtr;
                            if ((tmpPropPtr = PropManager::instance()->createProp(*currentSelectedImage + ".prop", Prop::IMAGE, std::string(buf1))) != nullptr)
                            {
                                static_cast<Prop::Image*>(tmpPropPtr)->imageFile = *currentSelectedImage;
                                tmpPropPtr->loadData();
                                if (static_cast<Prop::Image*>(tmpPropPtr)->textureIsLoaded() == false)
                                {
                                    Core::Debugger::instance()->AddLog("[ERR][PropViewer::%s)] Failed to load texture", __func__);
                                    PropManager::instance()->removeEntry(tmpPropPtr);
                                }
                                else
                                {
                                    buf1[0] = '\0';
                                    Engine::BunnyEngine::instance()->getActiveStage()->addProp(tmpPropPtr);

                                    Json::Value outData;
                                    tmpPropPtr->writeData(outData);
                                    JsonWriter::write(outData, "./Data/Props/" + tmpPropPtr->fileName);
                                }
                            }

                        }
                    }
                }
            }
            else if (ddType == 1) // AUDIO CREATION
            {
                static size_t soundSelected = 0;
                if (soundSelected >= availableSound.size())
                {
                    soundSelected = 0;
                    currentSelectedFile = nullptr;
                }
                else
                {
                    currentSelectedFile = &availableSound[soundSelected];
                }


                if (ImGui::CollapsingHeader("Available Sound(s)", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    if (availableSound.size() < 1)
                    {
                        searchForProps();
                    }
                    ImGui::Indent();
                    {
                        for (size_t i = 0; i < availableSound.size(); ++i)
                        {
                            ImGui::PushID(static_cast<int>(i));
                            {
                                char label[128];
                                sprintf_s(label, "%s", (availableSound[i].c_str()));
                                if (!PropManager::instance()->isFileLoaded(availableSound[i] + ".prop") &&
                                    !JsonReader::fileExists("./Data/Props/" + availableSound[i] + ".prop"))
                                {
                                    if (ImGui::Selectable(label, soundSelected == i) || currentSelectedAudio == nullptr)
                                    {
                                        soundSelected = i;
                                        currentSelectedAudio = &(availableSound[i]);
                                    }
                                }
                            }
                            ImGui::PopID();
                        }
                    }
                    ImGui::Unindent();
                }
                if (ImGui::Button("Create") && currentSelectedAudio != nullptr)
                {
                    if (std::string(buf1) == "err")
                    {
                        Core::Debugger::instance()->AddLog("[WARNING][PropViewer::%s] Please don't use the id \"err\" as it is reserved\n", __func__);
                    }
                    else
                    {
                        if (PropManager::instance()->isFileLoaded(*currentSelectedAudio + ".prop") ||
                            JsonReader::fileExists("./Data/Props/" + *currentSelectedAudio + ".prop"))
                        {
                            Core::Debugger::instance()->AddLog("[WARNING][PropViewer::%s] Please select another Image as this one has already been created\n", __func__);
                        }
                        else
                        {
                            Prop::BaseProp* tmpPropPtr;
                            if ((tmpPropPtr = PropManager::instance()->createProp(*currentSelectedAudio + ".prop", Prop::AUDIO, std::string(buf1))) != nullptr)
                            {
                                static_cast<Prop::Audio*>(tmpPropPtr)->audioFile = *currentSelectedAudio;
                                tmpPropPtr->loadData();
                                if (static_cast<Prop::Audio*>(tmpPropPtr)->soundIsLoaded() == false)
                                {
                                    Core::Debugger::instance()->AddLog("[ERR][PropViewer::%s)] Failed to load audio", __func__);
                                    PropManager::instance()->removeEntry(tmpPropPtr);
                                }
                                else
                                {
                                    buf1[0] = '\0';
                                    Engine::BunnyEngine::instance()->getActiveStage()->addProp(tmpPropPtr);

                                    Json::Value outData;
                                    tmpPropPtr->writeData(outData);
                                    JsonWriter::write(outData, "./Data/Props/" + tmpPropPtr->fileName);
                                }
                            }

                        }
                    }
                }
            }
            else if (ddType == 2) // ANIMATION CREATION
            {
                if (ImGui::Button("Create"))
                {
                    if (std::string(buf1) == "err")
                    {
                        Core::Debugger::instance()->AddLog("[WARNING][PropViewer::%s] Please don't use the id \"err\" as it is reserved\n", __func__);
                    }
                    else
                    {
                        if (PropManager::instance()->isFileLoaded(std::string(buf1) + ".prop") ||
                            JsonReader::fileExists("./Data/Props/" + std::string(buf1) + ".prop"))
                        {
                            Core::Debugger::instance()->AddLog("[WARNING][PropViewer::%s] Please select another Id for your animation as this one has already been created\n", __func__);
                        }
                        else
                        {
                            Prop::BaseProp* tmpPropPtr;
                            if ((tmpPropPtr = PropManager::instance()->createProp(std::string(buf1) + ".prop", Prop::ANIMATION, std::string(buf1))) != nullptr)
                            {
                                buf1[0] = '\0';
                                Engine::BunnyEngine::instance()->getActiveStage()->addProp(tmpPropPtr);

                                Json::Value outData;
                                tmpPropPtr->writeData(outData);
                                JsonWriter::write(outData, "./Data/Props/" + tmpPropPtr->fileName);
                            }

                        }
                    }
                }
            }
        }
    }
    ImGui::End();
}

void
BE::DImGuiHelperFunc::PropTableViewer::Draw(const char * title, bool * p_opened)
{
    ImGui::SetNextWindowSize(ImVec2(600, 450), ImGuiSetCond_Once);
    ImGui::Begin(title, p_opened);
    {
        BE::PropManager::propNamePairList& table = PropManager::instance()->getCorresTable();
        std::vector<Prop::BaseProp*>& propVec = PropManager::instance()->getProps();
        // left
        {

            if (ImGui::CollapsingHeader("Prop Table", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Indent();
                {
                    for (size_t i = 0; i < table.size(); ++i)
                    {
                        ImGui::PushID(static_cast<int>(i));
                        {
                            ImGui::Text("#%d %s | %s", i + 1, table[i]->first.c_str(), table[i]->second->id.c_str());
                        }
                        ImGui::PopID();
                    }
                }
                ImGui::Unindent();
            }
            if (ImGui::CollapsingHeader("Prop Vec", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Indent();
                {
                    for (size_t i = 0; i < propVec.size(); ++i)
                    {
                        ImGui::PushID(static_cast<int>(i));
                        {
                            ImGui::Text("#%d %s", i + 1, propVec[i]->id.c_str());
                        }
                        ImGui::PopID();
                    }
                }
                ImGui::Unindent();
            }
        }
    }
    ImGui::End();
}

void
BE::DImGuiHelperFunc::MenuBar::setPointers(windowPointers windowValues_)
{
    winPtr = windowValues_;
    //    winPtr.show_log                     = windowValues_.show_log;
    //    winPtr.show_fps                     = windowValues_.show_fps;
    //    winPtr.show_actor                   = windowValues_.show_actor;
    //    winPtr.show_prop                    = windowValues_.show_prop;
    //    winPtr.show_table                   = windowValues_.show_table;
    //    winPtr.show_load_stage              = windowValues_.show_load_stage;
    //    winPtr.show_save_stage_filename     = windowValues_.show_save_stage_filename;
    //    winPtr.show_config                  = windowValues_.show_config;
}

void
BE::DImGuiHelperFunc::MenuBar::Draw()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            *winPtr.show_save_stage_filename = false;
            if (ImGui::MenuItem("Open Stage"))
            {
                *winPtr.show_load_stage = !(*winPtr.show_load_stage);
            }
            if (ImGui::MenuItem("Save"))
            {
                *winPtr.show_save_stage_filename = !(*winPtr.show_save_stage_filename);
                if (Engine::BunnyEngine::instance()->getActiveStage() != nullptr) // This is to set the default value in the "Save as" field
                {
                    Core::Debugger::instance()->setSaveStagFileName(Engine::BunnyEngine::instance()->getActiveStage()->getStageFileName());
                }
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            *winPtr.show_save_stage_filename = false;
            if (ImGui::MenuItem("Actor"))
            {
                *winPtr.show_actor = !(*winPtr.show_actor);
            }
            if (ImGui::MenuItem("Prop"))
            {
                *winPtr.show_prop = !(*winPtr.show_prop);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Debug"))
        {
            *winPtr.show_save_stage_filename = false;
            if (ImGui::MenuItem("Profiler"))
            {
                *winPtr.show_fps = !(*winPtr.show_fps);
            }
            if (ImGui::MenuItem("Logger"))
            {
                *winPtr.show_log = !(*winPtr.show_log);
            }
            if (ImGui::MenuItem("Correspondance Table"))
            {
                *winPtr.show_table = !(*winPtr.show_table);
            }
            if (ImGui::MenuItem("Physics"))
            {
                *winPtr.show_physics = !(*winPtr.show_physics);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Config"))
        {
            *winPtr.show_save_stage_filename = false;
            if (ImGui::MenuItem("Settings"))
            {
                *winPtr.show_config = !(*winPtr.show_config);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void
BE::DImGuiHelperFunc::StageLoader::Draw(const char* title, bool* p_opened)
{
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiSetCond_FirstUseEver);
    ImGui::Begin(title, p_opened);

    Engine::BunnyEngine::StageVec& availableStages = Engine::BunnyEngine::instance()->_availableStages;

    // left
    {
        static size_t selected = 0;
        static bool stageSelected = false;

        ImGui::BeginChild("left pane", ImVec2(280, 250), true);
        for (size_t i = 0; i < availableStages.size(); ++i)
        {
            if (currentSelectedStage == nullptr)
            {
                currentSelectedStage = availableStages[i].get();
            }
            ImGui::PushID(static_cast<int>(i));
            {
                char label[128];
                sprintf_s(label, "%s", availableStages[i]->getStageFileName().c_str());
                if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_AllowDoubleClick))
                {
                    selected = i;
                    currentSelectedStage = availableStages[i].get();
                    if (ImGui::IsMouseDoubleClicked(0))
                    {
                        stageSelected = true;

                    }
                }
            }
            ImGui::PopID();
        }
        ImGui::EndChild();
        if ((ImGui::Button("Select Stage") || stageSelected) && currentSelectedStage != nullptr)
        {
            Stage::BaseStage* stageCpy = currentSelectedStage->cpy();
            Engine::BunnyEngine::instance()->flushStages();
            Engine::BunnyEngine::instance()->pushActiveStage(stageCpy);
            *p_opened = false;
            stageSelected = false;
        }
        ImGui::SameLine();
    }
    ImGui::End();
}

void
BE::DImGuiHelperFunc::SaveStageFilename::setFileName(std::string fileName_)
{
    buf1[0] = '\0';
    for (size_t i = 0; i < fileName_.length() && i < 63; ++i)
    {
        buf1[i] = fileName_[i];
    }
    buf1[fileName_.length()] = '\0';
}

void
BE::DImGuiHelperFunc::SaveStageFilename::Draw(const char * title, bool * p_opened)
{
    ImGui::SetNextWindowSize(ImVec2(300, 60), ImGuiSetCond_FirstUseEver);
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 60), ImVec2(300, 60));
    ImGui::Begin(title, p_opened);

    if (ImGui::InputText("", buf1, 64, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
    {
        Engine::BunnyEngine::instance()->saveSceneState(std::string(buf1));
        buf1[0] = '\0';
        *p_opened = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        Core::Debugger::instance()->AddLog("[LOG][SaveStageFilename::%s] Saved %s\n", __func__, buf1);

        Engine::BunnyEngine::instance()->saveSceneState(std::string(buf1));
        buf1[0] = '\0';
        *p_opened = false;
    }

    ImGui::End();
}

BE::DImGuiHelperFunc::ConfigWindow::ConfigWindow()
{
    // 3:2
    resolutions["480x320"] = glm::ivec2(480, 320);
    resolutions["1152x768"] = glm::ivec2(1152, 768);
    resolutions["1440x960"] = glm::ivec2(1440, 960);
    // 4:3
    resolutions["320x240"] = glm::ivec2(320, 240);
    resolutions["384x288"] = glm::ivec2(384, 288);
    resolutions["640x480"] = glm::ivec2(640, 480);
    resolutions["768x576"] = glm::ivec2(768, 576);
    resolutions["800x600"] = glm::ivec2(800, 600);
    resolutions["1024x768"] = glm::ivec2(1024, 768);
    resolutions["1152x864"] = glm::ivec2(1152, 864);
    resolutions["1280x960"] = glm::ivec2(1280, 960);
    resolutions["1400x1050"] = glm::ivec2(1400, 1050);
    resolutions["1600x1200"] = glm::ivec2(1600, 1200);
    resolutions["2048x1536"] = glm::ivec2(2048, 1536);
    // 5:3
    resolutions["800x480"] = glm::ivec2(800, 480);
    resolutions["1280x768"] = glm::ivec2(1280, 768);
    // 5:4
    resolutions["1280x1024"] = glm::ivec2(1280, 1024);
    resolutions["2560x2048"] = glm::ivec2(2560, 2048);
    // 8:5
    resolutions["320x200"] = glm::ivec2(320, 200);
    resolutions["1280x800"] = glm::ivec2(1280, 800);
    resolutions["1440x900"] = glm::ivec2(1440, 900);
    resolutions["1680x1050"] = glm::ivec2(1680, 1050);
    resolutions["1920x1200"] = glm::ivec2(1920, 1200);
    resolutions["2560x1600"] = glm::ivec2(2560, 1600);
    // 16:9
    resolutions["854x480"] = glm::ivec2(854, 480);
    resolutions["1024x576"] = glm::ivec2(1024, 576);
    resolutions["1280x720"] = glm::ivec2(1280, 720);
    resolutions["1366x768"] = glm::ivec2(1366, 768);
    resolutions["1600x900"] = glm::ivec2(1600, 900);
    resolutions["1920x1080"] = glm::ivec2(1920, 1080);
    resolutions["2560x1440"] = glm::ivec2(2560, 1440);
    resolutions["3840x2160"] = glm::ivec2(3840, 2160);
    // 17:9
    resolutions["2048x1080"] = glm::ivec2(2048, 1080);
    resolutions["4096x2160"] = glm::ivec2(4096, 2160);
    // 21:9
    resolutions["2560x1080"] = glm::ivec2(2560, 1080);
    resolutions["3440x1440"] = glm::ivec2(3440, 1440);

    std::vector<const char*> _3_2 = { "480x320", "1152x768", "1440x960" };
    resVec.push_back(_3_2);
    std::vector<const char*> _4_3 = { "320x240", "384x288", "640x480", "768x576", "800x600", "1024x768", "1152x864", "1280x960", "1400x1050", "1600x1200", "2048x1536" };
    resVec.push_back(_4_3);
    std::vector<const char*> _5_3 = { "800x480", "1280x768" };
    resVec.push_back(_5_3);
    std::vector<const char*> _5_4 = { "1280x1024", "2560x2048" };
    resVec.push_back(_5_4);
    std::vector<const char*> _8_5 = { "320x200", "1280x800", "1440x900", "1680x1050", "1920x1200", "2560x1600" };
    resVec.push_back(_8_5);
    std::vector<const char*> _16_9 = { "854x480", "1024x576", "1280x720", "1366x768", "1600x900", "1920x1080", "2560x1440", "3840x2160" };
    resVec.push_back(_16_9);
    std::vector<const char*> _17_9 = { "2048x1080", "4096x2160" };
    resVec.push_back(_17_9);
    std::vector<const char*> _21_9 = { "2560x1080", "3440x1440" };
    resVec.push_back(_21_9);

    Json::Value data;
    JsonReader::readFile("engine.conf", data);
    ddRatio = JsonReader::getFieldAsInt(data["conf"]["ratio"]);
    ddResolution = JsonReader::getFieldAsInt(data["conf"]["resolution"]);
    fullscreen = JsonReader::getFieldAsBool(data["conf"]["fullscreen"]);
    _viewport = JsonReader::getFieldAsIVec2(data["conf"]["viewport"]);
    if (_viewport.x <= 0 || _viewport.y <= 0)
    {
        _viewport = { 1280, 720 };
    }
    RenderAbst::instance()->viewport = _viewport;
    BE::WindowAbst::instance()->setFullscreen(fullscreen);
    glm::ivec2 res = resolutions.at(std::string(resVec[ddRatio][ddResolution]));
    BE::WindowAbst::instance()->resizeWindow(res);
}

void
BE::DImGuiHelperFunc::ConfigWindow::Draw(const char* title, bool* p_opened)
{
    ImGui::SetNextWindowSize(ImVec2(300, 60), ImGuiSetCond_FirstUseEver);
    ImGui::Begin(title, p_opened);
    {
        static int viewport[2];
        viewport[0] = _viewport[0];
        viewport[1] = _viewport[1];
        if (ImGui::InputInt2("Viewport", viewport))
        {
            _viewport[0] = viewport[0];
            _viewport[1] = viewport[1];
        }
        ImGui::Checkbox("Fullscreen", &fullscreen);
        static const char* ratio[] = { "3:2", "4:3", "5:3", "5:4", "8:5", "16:9", "17:9", "21:9" };
        if (ImGui::Combo("Ratio", &ddRatio, ratio, ((int)(sizeof(ratio) / sizeof(*ratio)))))
        {
            ddResolution = 0;
        }

        ImGui::Combo("Resolution", &ddResolution, resVec[ddRatio].data(), static_cast<int>(resVec[ddRatio].size()));

        if (ImGui::Button("Apply"))
        {
            RenderAbst::instance()->viewport.x = viewport[0];
            RenderAbst::instance()->viewport.y = viewport[1];
            BE::WindowAbst::instance()->setFullscreen(fullscreen);
            glm::ivec2 res = resolutions.at(std::string(resVec[ddRatio][ddResolution]));
            BE::WindowAbst::instance()->resizeWindow(res);

            Json::Value data;
            JsonWriter::addValue(data["conf"]["ratio"], ddRatio);
            JsonWriter::addValue(data["conf"]["resolution"], ddResolution);
            JsonWriter::addValue(data["conf"]["fullscreen"], fullscreen);
            JsonWriter::addVec2(data["conf"]["viewport"], _viewport);
            JsonWriter::write(data, "engine.conf");
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset"))
        {
            ddRatio = 5;
            ddResolution = 2;
            _viewport = { 1280, 720 };
            fullscreen = false;

            Json::Value data;
            JsonWriter::addValue(data["conf"]["ratio"], ddRatio);
            JsonWriter::addValue(data["conf"]["resolution"], ddResolution);
            JsonWriter::addValue(data["conf"]["fullscreen"], fullscreen);
            JsonWriter::addVec2(data["conf"]["viewport"], _viewport);
            JsonWriter::write(data, "engine.conf");
        }
    }
    ImGui::End();
}

void BE::DImGuiHelperFunc::PhysicsWindow::Draw(const char * title, bool * p_opened)
{
    ImGui::SetNextWindowSize(ImVec2(300, 60), ImGuiSetCond_FirstUseEver);
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 60), ImVec2(300, 60));
    ImGui::Begin(title, p_opened);

    ImGui::Checkbox("Enable Circle Collider Debug", &Core::Physics::instance()->drawCircleColliders);

    ImGui::End();
}
