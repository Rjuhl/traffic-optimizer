#include "viewer.h"
#include "App.h"

int main() {
    App* app = new App();
    int ret = app->run();
    delete app;
    return ret;
}