#include "SendPackage.h"

SendPackage::SendPackage()
{

}

SendPackage::~SendPackage()
{

}

void SendPackage::set_is_sent(bool val)
{
    sent = val;
}

string SendPackage::get_payload()
{
    return payload;
}

void SendPackage::set_payload(string val)
{
    payload.clear();
    payload = val;
}

bool SendPackage::is_sent()
{
    return sent;
}

int SendPackage::get_payload_length()
{
    return payload.size();
}
