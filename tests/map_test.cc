#include <catch2/catch.hpp>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <visualizer/visualizer_app.h>
#include <core/Location.h>
#include <visualizer/visualizer_app.h>

TEST_CASE("Map generates a different starting point each game") {
    visualizer_app::visualizer::VisualizerApp();
    
}

TEST_CASE("Map generates a different ending point each game") {
    
}