#include "menumodel.h"

menumodel::menumodel() : QAbstractItemModel()
{
    //_items << "a" << "b" <<"c" << "d";
    _roles.insert(555, "text");
}
