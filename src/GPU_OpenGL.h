/*
    Copyright 2016-2023 melonDS team

    This file is part of melonDS.

    melonDS is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    melonDS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with melonDS. If not, see http://www.gnu.org/licenses/.
*/

#pragma once

#include "OpenGLSupport.h"

#include <array>
#include <optional>

namespace melonDS
{
class GPU;
struct RenderSettings;
class GLRenderer;
class Renderer3D;
class GLCompositor
{
public:
    static std::optional<GLCompositor> New() noexcept;
    GLCompositor(const GLCompositor&) = delete;
    GLCompositor& operator=(const GLCompositor&) = delete;
    GLCompositor(GLCompositor&&) noexcept;
    GLCompositor& operator=(GLCompositor&&) noexcept;
    ~GLCompositor();

    void SetGameScene(int gameScene) noexcept;
    void SetAspectRatio(float aspectRatio) noexcept;
    void SetScaleFactor(int scale) noexcept;
    void SetShowMap(bool showMap) noexcept;
    void SetShowTarget(bool showTarget) noexcept;
    void SetShowMissionGauge(bool showMissionGauge) noexcept;
    [[nodiscard]] int GetGameScene() const noexcept { return GameScene; }
    [[nodiscard]] float GetAspectRatio() const noexcept { return AspectRatio; }
    [[nodiscard]] int GetScaleFactor() const noexcept { return Scale; }
    [[nodiscard]] bool GetShowMap() const noexcept { return ShowMap; }
    [[nodiscard]] bool GetShowTarget() const noexcept { return ShowTarget; }
    [[nodiscard]] bool GetShowMissionGauge() const noexcept { return ShowMissionGauge; }

    void Stop(const GPU& gpu) noexcept;
    void RenderFrame(const GPU& gpu, Renderer3D& renderer) noexcept;
    void BindOutputTexture(int buf);
private:
    GLCompositor(GLuint CompShader) noexcept;
    int Scale = 0;
    int ScreenH = 0, ScreenW = 0;
    int GameScene = 0;
    float AspectRatio = 0;
    bool ShowMap = false;
    bool ShowTarget = false;
    bool ShowMissionGauge = false;

    GLuint CompShader {};
    GLuint CompScaleLoc = 0;
    GLuint Comp3DXPosLoc = 0;
    GLuint CompGameSceneLoc = 0;
    GLuint CompAspectRatioLoc = 0;
    GLuint CompShowMapLoc = 0;
    GLuint CompShowTargetLoc = 0;
    GLuint CompShowMissionGaugeLoc = 0;

    GLuint CompVertexBufferID = 0;
    GLuint CompVertexArrayID = 0;

    struct CompVertex
    {
        std::array<float, 2> Position {};
        std::array<float, 2> Texcoord {};
    };
    std::array<CompVertex, 2*3*2> CompVertices {};

    GLuint CompScreenInputTex = 0;
    std::array<GLuint, 2> CompScreenOutputTex {};
    std::array<GLuint, 2> CompScreenOutputFB {};
};

}
