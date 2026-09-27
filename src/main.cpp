#include <QApplication>

#include "ui/MainWindow.h"

int main(int argc, char *argv[])
{
    // Nécessaire car resources.qrc est compilé dans rolling_shelter_ui, une
    // bibliothèque STATIQUE : sans cet appel explicite, le linker exclut le
    // code d'enregistrement des ressources (rien ne le référence autrement),
    // et QPixmap(":/...") échoue silencieusement à l'exécution.
    // L'argument correspond au nom du fichier .qrc, sans extension.
    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
