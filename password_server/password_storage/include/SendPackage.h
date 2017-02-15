#ifndef SENDPACKAGE_H
#define SENDPACKAGE_H

#include <string>

using namespace std;

class SendPackage
{
    public:
        SendPackage();
        virtual ~SendPackage();
        void set_is_sent(bool val);
        string get_payload();
        void set_payload(string val);
        bool is_sent();
        int get_payload_length();
    protected:
    private:
        string payload;
        bool sent;
};

#endif // SENDPACKAGE_H
