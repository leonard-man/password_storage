#ifndef MESSAGEPARSINGRESULT_H
#define MESSAGEPARSINGRESULT_H

#include <cstdlib>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

// this class encapsulates the result of received message parsing activity
// it does not contain parsed message, it is only encapsulating error messages
// or success message
class MessageParsingResult
{
    public:
        MessageParsingResult();
        virtual ~MessageParsingResult();
        string get_parsing_result_message();
        void set_parsing_result_message(string result_message);
    protected:
    private:
        string parsing_result_message;
};

#endif // MESSAGEPARSINGRESULT_H
