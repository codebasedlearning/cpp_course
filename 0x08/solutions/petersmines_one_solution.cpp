// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Peters Mines solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iomanip>

using std::cout, std::endl;
using std::string, std::string_view;

class vehicle_base {
public:
    size_t seats_;

    vehicle_base(size_t seats) : seats_{seats} {
        cout << "ctor vehicle_base: seats=" << seats << endl;
    }

    ~vehicle_base() {
        cout << "dtor vehicle_base" << endl;
    }
};

class vehicle {
public:
    size_t max_speed_;

    vehicle(size_t max_speed) : max_speed_{max_speed} {
        cout << "ctor vehicle: max_speed=" << max_speed << endl;
    }
    ~vehicle() {
        cout << "dtor vehicle" << endl;
    }
};

class car : public virtual vehicle_base, public vehicle {
public:
    size_t wheels_;

    car(size_t seats, size_t max_speed, size_t wheels)
            : vehicle_base(seats), vehicle(max_speed), wheels_{wheels} {
        cout << "ctor car: seats=" << seats
             << ", max_speed=" << max_speed << ", wheels=" << wheels
             << endl;
    }
    ~car() {
        cout << "dtor car" << endl;
    }
};

class boat : public virtual vehicle_base, public vehicle {
public:
    boat(size_t seats, size_t max_speed)
            : vehicle_base(seats),
              vehicle(max_speed) {
        cout << "ctor boat: seats=" << seats
             << ", max_speed=" << max_speed
             << endl;
    }
    ~boat() {
        cout << "dtor boat" << endl;
    }
};

class amphibie : public car, public boat {
public:
    amphibie(size_t seats, size_t max_speed_car, size_t max_speed_boat,
             size_t wheels)
            : vehicle_base(seats), car(seats, max_speed_car, wheels),
              boat(seats, max_speed_boat) {
        std::cout << "ctor amphibie: seats=" << seats
                  << ", max_speed_car=" << max_speed_car
                  << ", max_speed_boat=" << max_speed_boat
                  << ", wheels=" << wheels
                  << endl;
    }
    ~amphibie() {
        cout << "dtor amphibie" << endl;
    }
};

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    amphibie amph{4, 120, 15, 4};

    cout << " 1| amph.seats=" << amph.seats_ << endl;
    cout << " 2| amph.wheels=" << amph.wheels_ << endl;
    cout << " 3| amph.boat::max_speed=" << amph.boat::max_speed_ << endl;
    cout << " 4| amph.car::max_speed=" << amph.car::max_speed_ << endl;

    return EXIT_SUCCESS;
}
