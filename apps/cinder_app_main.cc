#include <visualizer/visualizer_app.h>

using visualizer_app::visualizer::VisualizerApp;

void prepareSettings(VisualizerApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(VisualizerApp, ci::app::RendererGl, prepareSettings);

