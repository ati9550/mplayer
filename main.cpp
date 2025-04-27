#include "backend/back_main.h"
#include "frontend/front_main.h"
#include "global.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    global::window = &window;

    Backend backend;
    global::backend = &backend;

    frontend::init();

    return app.exec();
}
