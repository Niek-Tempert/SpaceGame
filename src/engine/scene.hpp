#pragma once

#include <providers/input_provider.hpp>
#include <providers/time_provider.hpp>
#include <primitives/skybox.hpp>
#include <primitives/crossair.hpp>
#include <primitives/block_select.hpp>
#include <voxel/voxel.h>

#include "player.hpp"

class Input;
class Engine;

class Scene
    : public TimeProvider
    , public InputProvider {
public:
    Scene(const InputProvider& input, const TimeProvider& time);
	void update();
	glm::mat4 getView();
    std::vector<IRenderable*> getRenderables();

private:
    void updatePlayer();
    void updateMoon();
    void makeUI();

    std::vector<IRenderable*> m_renderables{};

    Skybox m_skybox;
    Voxel m_moon;
    Voxel m_planet;
	BlockSelect m_blockSelect;
    Crossair m_crossair;
    std::vector<Voxel*> m_voxels;
    
    Player m_player;
    glm::mat4 m_view;
    f32 m_moonSpeed;
};
