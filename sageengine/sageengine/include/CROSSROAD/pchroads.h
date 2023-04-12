#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <glm/glm.hpp>

#include "trafficStatusObject.h"
#include "messageObject.h"
#include"./JSON/json.hpp"
#include "client.h"
#include "server.h"
#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib

#include "trafficlight.h"
extern std::mutex g_mutex;
extern bool g_serverReady;
extern std::condition_variable g_conditionVariable;
extern bool server_running;
extern bool client_running;
extern bool messagereadable;






