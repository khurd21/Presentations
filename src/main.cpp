#include <presentations/MainWindow.hpp>
#include <presentations/ThemeManager.hpp>

#include <QApplication>

int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents);

    QApplication app(argc, argv);
    presentations::ThemeManager::instance();
    presentations::MainWindow window;
    window.show();
    return QApplication::exec();
}