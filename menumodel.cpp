#include "menumodel.h"

menumodel* backmodel;
menumodel* forwardmodel;

menumodel::menumodel(QString name) : QAbstractItemModel()
{
    //_items << "a" << "b" <<"c" << "d";
    _roles.insert(555, "text");
    _name = name;
}
