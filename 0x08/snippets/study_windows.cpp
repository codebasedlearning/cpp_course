// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class window {
public:
    window(unsigned long res_id) : visible_(false), res_id_(res_id) {
        cout << " a| -> ctor::window, id=" << res_id_ << endl;
    }
    
    void hide() { visible_=false; }
    void show() { visible_=true; }
    
    virtual void draw() = 0;

    virtual ~window() { 
        cout << " b| -> dtor::window, id=" << res_id_ << endl;
    }

protected:
    bool visible_;
    unsigned long res_id_;
};

class button : public window {
public:
    button(unsigned long res_id) : window(res_id) {}

    virtual void draw() { 
        cout << " c| ---> button draw, id=" << res_id_ << endl;
    } 
};

class checkbox : public window {
public:
    checkbox(unsigned long res_id) : window(res_id) {}

    virtual void draw() { 
        cout << " d| ---> checkbox draw, id=" << res_id_ << endl;
    } 
};

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    // create instances, draw etc. [...]

    return EXIT_SUCCESS;
}
