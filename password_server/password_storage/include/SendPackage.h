#ifndef SENDPACKAGE_H
#define SENDPACKAGE_H

#include <string>

using namespace std;

class SendPackage
{
    public:
        SendPackage();
        virtual ~SendPackage();
        bool GetIsSent() { return IsSent; }
        void SetIsSent(bool val) { IsSent = val; }
        string Getpayload() { return payload; }
        void Setpayload(string val) { payload = val; }
        bool IsSent;
        string payload;
    protected:
    private:

};

#endif // SENDPACKAGE_H
