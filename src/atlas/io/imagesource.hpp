#pragma once
#ifndef ATLAS_IO_IMAGESOURCE_HPP
#define ATLAS_IO_IMAGESOURCE_HPP

#include <future>
#include "request.hpp"
#include "response.hpp"
#include "atlas/core/region.hpp"
#include "atlas/core/image.hpp"

namespace atlas::io
{
    using namespace atlas::core;

    // Base class for all image sources.
    class ImageSource
    {
    public:
        virtual ~ImageSource() {}

        // asynchronously fetches the given region in the data source.
        virtual std::future<Response<Image>> get(Request<Region>);

        // returns the region covered by the data source.
        virtual Region region() const noexcept = 0;

    protected:
        virtual Response<Image> readRegion(Request<Region>) = 0;
    };
}

#endif // ATLAS_IO_IMAGESOURCE_HPP