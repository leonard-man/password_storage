#ifndef RECEIVEPACKAGE_H
#define RECEIVEPACKAGE_H

#include <string>

using namespace std;

class ReceivePackage
{
    public:
        ReceivePackage();
        virtual ~ReceivePackage();
        void set_is_read(bool val);
        std::string get_payload();
        void set_payload(std::string val);
        bool is_read();
        int get_payload_length();
    protected:
    private:
        std::string payload;
        bool read;
};

#endif // RECEIVEPACKAGE_H
