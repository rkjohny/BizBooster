#ifndef _DO_CONNETCOR_H
#define _DO_CONNETCOR_H

#include <string>

namespace Dbo {
class Connector {

protected:
    Connector();

    Connector(const Connector &);

    virtual ~Connector();

public:
    static Connector *NewInstance(std::string db_name);

    virtual void Close() = 0;
};
}

#endif
