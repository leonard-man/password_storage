#ifndef RECEIVEPACKAGE_H
#define RECEIVEPACKAGE_H

#include <string>

using namespace std;

class ReceivePackage
{
    public:
        ReceivePackage();
        virtual ~ReceivePackage();
        bool GetIsRead() { return IsRead; }
        void SetIsRead(bool val) { IsRead = val; }
        std::string GetPayload() { return payload; }
        void SetPayload(std::string val) { payload = val; }
        bool IsRead;
    protected:
    private:
        std::string payload;
};

#endif // RECEIVEPACKAGE_H
