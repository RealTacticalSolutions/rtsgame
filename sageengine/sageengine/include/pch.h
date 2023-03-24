#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <chrono>
#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include <set>
#include <limits>
#include <algorithm>
#include <fstream>
#include <array>
#include <string>
#include <map>


#include "messageObject.h"
#include "waypoints.h"
#include "vertex.h"
#include "mesh.h"
#include "renderobject.h"
#include "blueprint.h"
#include "buffermanager.h"
#include "properties.h"
#include "collisionType.h"
#include "gameObject.h"
#include "shapetool.h"
#include "intersection.h"
#include "camera.h"
#include "gamemath.h"
#include "scene.h"
#include "window.h"
#include "renderer.h"
#include "grid.h"
#include "application.h"
#include "inputsystem.h"

