#include <QApplication>
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("Rolling Shelter");
    window.resize(800, 600);

    QLabel *placeholder = new QLabel("Rolling Shelter - work in progress");
    placeholder->setAlignment(Qt::AlignCenter);
    window.setCentralWidget(placeholder);

    window.show();

    return app.exec();
}
