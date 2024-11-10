
#include <QApplication>

#include "jsondbms.h"
#include "Controller.h"
#include "model.h"
#include "View.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    JsonDBMS* d = new JsonDBMS("save.json");
    Model m(d);
    View v;
    Controller c;
    c.setModel(&m);
    c.setView(&v);
    v.setController(&c);
    v.show();
    return a.exec();
}
