#include "DatabaseLayer.h"

DatabaseLayer::DatabaseLayer()
{
    //ctor
}

DatabaseLayer::~DatabaseLayer()
{
    //dtor
}

vector<PasswordEntry> DatabaseLayer::get_all_password_entries()
{
    //return vector<dynamic_cast<PasswordEntry*>(nullptr)>;
}

PasswordEntry* DatabaseLayer::get_password_entry(unsigned int id)
{
    return nullptr;
}

bool DatabaseLayer::insert_password_entry(PasswordEntry& password_entry)
{
    return false;
}

PasswordEntry* DatabaseLayer::change_password_entry(PasswordEntry& new_password_entry)
{
    return nullptr;
}

bool DatabaseLayer::delete_password_entry(PasswordEntry& password_entry)
{
    return false;
}
