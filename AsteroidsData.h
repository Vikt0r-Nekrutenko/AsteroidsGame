#ifndef ASTEROIDSDATA_H
#define ASTEROIDSDATA_H

#include "SpaceObjectsData.h"

class AsteroidsData : public SpaceObjectsData
{
public:
    void destroy(size_t indx) override;
};

#endif // ASTEROIDSDATA_H
