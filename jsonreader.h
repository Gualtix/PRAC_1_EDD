#ifndef JSONREADER_H
#define JSONREADER_H

//#include "doublelist.h"
//#include "simplelist.h"
#include "dc_list.h"
#include "simplelist.h"

class JsonReader
{
public:
    static void fillListFromFile(DC_List *list, QByteArray json);
    static void fillListFromFile(SimpleList *list, QByteArray json);

};

#endif // JSONREADER_H
