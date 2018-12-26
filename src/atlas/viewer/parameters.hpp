#pragma once
#ifndef ATLAS_VIEWER_PARAMETERS_HPP
#define ATLAS_VIEWER_PARAMETERS_HPP

#include <string>

namespace atlas::viewer
{
    // stores global application parameters.
    struct Parameters
    {
        std::string shaderDirectory;
        std::string cacheDirectory;
        int verbosity;
    };
}

#endif // ATLAS_VIEWER_PARAMETERS_HPP