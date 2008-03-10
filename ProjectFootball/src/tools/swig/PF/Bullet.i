%module BULLET

%{
#include "../bullet/LinearMath/btVector3.h"
#include "../bullet/LinearMath/btQuadWord.h"
#include "../bullet/LinearMath/btScalar.h"
%}

%{
typedef float btScalar;
%}

typedef float btScalar;

class btVector3
{
public:
    btVector3();
    btVector3(const btScalar& x, const btScalar& y, const btScalar& z);
    const btScalar& x() const;
    const btScalar& y() const;
    const btScalar& z() const;
    btScalar dot(const btVector3& v) const;
    btScalar length2() const;
    btScalar length() const;
    btScalar distance(const btVector3& v) const;
};

%extend btVector3
{
    btVector3 operator-(const btVector3& v) {
        return btVector3(self->x() - v.x(), self->y() - v.y(), self->z() - v.z());
    }

    btVector3 operator+(const btVector3& v) {
        return btVector3(self->x() + v.x(), self->y() + v.y(), self->z() + v.z());
    }
};