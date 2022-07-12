#pragma once

#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <memory>
#include "types.h"

#define no_error NULL

class errors : public std::enable_shared_from_this<errors> {
    errors() = default;

  private:
    errors(str);
    str m;

  public:
    static s_ptr<errors> new_error(str);
    str msg();
    const char* cmsg();
};

typedef s_ptr<errors> error;

#endif
