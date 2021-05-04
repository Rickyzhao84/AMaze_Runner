#include <core/location.h>

namespace visualizer_app {

    Location::Location(size_t row, size_t column) {
        x_coord_ = row;
        y_coord_ = column;
    }

    Location::Location() {
        x_coord_ = 0;
        y_coord_ = 0;
    }

    const size_t Location::GetYCoord() const {
        return y_coord_;
    }

    void Location::SetYCoord(const size_t &yCoord) {
        y_coord_ = yCoord;
    }

    const size_t Location::GetXCoord() const {
        return x_coord_;
    }

    void Location::SetXCoord(const size_t &xCoord) {
        x_coord_ = xCoord;
    }
}
