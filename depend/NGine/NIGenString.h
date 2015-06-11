#pragma once

//Interface for Classes capable of generating String Information
class NIGenString{

public:
    //Generate String
    virtual std::string genString(void) const = 0;

    //Virtual Dtor
    virtual ~NIGenString(void){ }
};
