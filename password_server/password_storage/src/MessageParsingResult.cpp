#include "MessageParsingResult.h"

MessageParsingResult::MessageParsingResult()
{
    //ctor
}

MessageParsingResult::~MessageParsingResult()
{
    //dtor
}

string MessageParsingResult::get_parsing_result_message()
{
    return parsing_result_message;
}

void MessageParsingResult::set_parsing_result_message(string result_message)
{
    parsing_result_message = result_message;
}
