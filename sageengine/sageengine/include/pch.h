#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

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
#include <unordered_map>

#include "vertex.h"
#include "mesh.h"
#include "renderobject.h"
#include "blueprint.h"
#include "buffermanager.h"
#include "properties.h"
#include "gameObject.h"
#include "shapetool.h"
#include "camera.h"
#include "gamemath.h"
#include "scene.h"
#include "window.h"
#include "renderer.h"
#include "application.h"
#include "inputsystem.h"


