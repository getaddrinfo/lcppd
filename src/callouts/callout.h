#ifndef _CALLOUT_H
#define _CALLOUT_H

#include <string>

class ICallout
{
public:
    std::string m_identifier;
    std::string m_canoical;

    virtual void spawn();
    virtual void onTick();
    virtual void destroy();
};

#endif _CALLOUT_H