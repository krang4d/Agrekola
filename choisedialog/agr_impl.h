#ifndef AGR_IMPL_H
#define AGR_IMPL_H
#include "ko_impl.h"

class QString;

class Agr_impl : public Ko_impl
{
public:
    virtual void btp1Come(double) = 0;
    virtual void btp2Come(double) = 0;
    virtual void btp3Come(double) = 0;
    virtual void btp4Come(double) = 0;

    virtual void otp1Come(double) = 0;
    virtual void otp2Come(double) = 0;
    virtual void otp3Come(double) = 0;
    virtual void otp4Come(double) = 0;
};

#endif // AGR_IMPL_H
