#include "viewer.hpp"

#include "atlas/renderer/instance.hpp"
#include <chrono>
#include <iostream>

using namespace atlas::viewer;
using namespace atlas::renderer;

spdlog::level::level_enum selectLogLevel(int verbosity)
{
    assert(verbosity >= 0);

    if (verbosity == 0)
    {
        return spdlog::level::warn;
    }
    else if (verbosity == 1)
    {
        return spdlog::level::info;
    }
    else if (verbosity == 2)
    {
        return spdlog::level::debug;
    }
    else
    {
        return spdlog::level::trace;
    }
}

Viewer::Viewer(Parameters params) :
    _parameters(params)
{
    _log = spdlog::stdout_color_mt(APP_NAME);
    spdlog::set_level(selectLogLevel(params.verbosity));
    _log->info("initialize");

    _log->info("shader directory...{0}", params.shaderDirectory);

    if (glfwInit() != GLFW_TRUE)
    {
        std::runtime_error("could not initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    _window = glfwCreateWindow(800, 600, APP_NAME, nullptr, nullptr);

    _log->debug("create window");

    Instance::initialize(_window, params.shaderDirectory);

    _scene = std::make_unique<scene::Scene>("main");

    _scene->getLayer("grid")->setActive(false);

    _sessionStart = std::chrono::steady_clock::now();
}

void Viewer::update()
{
    auto frameStart = std::chrono::steady_clock::now();

    glfwPollEvents();

    // TODO framerate limiting
    std::this_thread::sleep_for(std::chrono::milliseconds(16));

    auto now = std::chrono::steady_clock::now();
    time.elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _sessionStart);
    time.deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - frameStart);
    time.frame++;

    _scene->render(time);
}

void Viewer::run()
{
    while (!glfwWindowShouldClose(_window))
    {
        update();
    }
}

Viewer::~Viewer()
{
    _scene = nullptr;

    Instance::terminate();

    glfwDestroyWindow(_window);

    _log->info("exit");
}