//
// Created by 06jcu on 8/12/2023.
//

#include "core.h"

std::vector<std::shared_ptr<GameObject>> Core::game_objects;
std::vector<Rectangle> Core::colliders;
std::shared_ptr<Camera2D> Core::current_camera;
