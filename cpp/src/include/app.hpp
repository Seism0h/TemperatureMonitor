#ifndef APP_H
#define APP_H

#include "systemManager.hpp"

// Base class for applications
class app { 
protected:
    systemManager& sysManager;

public:
    app(systemManager& sysManager) : sysManager(sysManager) {}
    virtual ~app() = default;
// Every application must implement these methods
    virtual void init() = 0;   
    virtual void cyclic() = 0;
    virtual void terminate() = 0;
};

#endif // APP_H