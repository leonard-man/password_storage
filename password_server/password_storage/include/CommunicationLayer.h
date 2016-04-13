#ifndef COMMUNICATIONLAYER_H
#define COMMUNICATIONLAYER_H

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/* object for socket communication - do research on interface and communication protocol <XML ans candidate?> */
class CommunicationLayer
{
    public:
        CommunicationLayer();
        virtual ~CommunicationLayer();
    protected:
    private:
};

#endif // COMMUNICATIONLAYER_H
