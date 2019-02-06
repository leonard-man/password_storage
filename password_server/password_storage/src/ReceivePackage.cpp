#include "ReceivePackage.h"

ReceivePackage::ReceivePackage()
{
    std::cout << "ReceivePackage created.\n";
}

ReceivePackage::~ReceivePackage()
{
    std::cout << "ReceivePackage destroyed.\n";
}

void ReceivePackage::set_is_read(bool val)
{
    read = val;
}

std::string ReceivePackage::get_payload()
{
    return payload;
}

void ReceivePackage::set_payload(std::string val)
{
    payload = val;
}

bool ReceivePackage::is_read()
{
    return read;
}

int ReceivePackage::get_payload_length()
{
    return payload.size();
}
