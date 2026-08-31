#pragma once

#include "state_provider.hpp"
#include "time_provider.hpp"

#include "utils/player.hpp"
#include "models/skybox.h"
#include "models/cursor.h"
#include "models/block_cursor.h"
#include "voxel/voxel.h"

class Input;

class Scene
    : public TimeProvider
    , public StateProvider {
public:
    void init();
    void update(const Input* input);
    glm::mat4 getView();
    std::vector<IRenderable*> getRenderables();

private:
    void updatePlayer(const Input* input);
    void updateMoon();

    std::vector<IRenderable*> m_renderables{};

    Skybox m_skybox{};
    Voxel m_moon{};
    Voxel m_planet{};
	BlockCursor m_block_cursor{};
    Cursor m_cursor{};
    std::vector<Voxel*> m_voxels{};
    
    Player m_player{};
    glm::mat4 m_view = glm::mat4(1.0f);
};
