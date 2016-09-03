#ifndef VISITORDOODAD_H
#define VISITORDOODAD_H

#include "Doodad.h"
#include "Visitor.h"

template <typename T=Doodad>
class VisitorDoodad : public Visitor
{
    public:
        virtual ~VisitorDoodad(void);

    protected:
        T* m_doodad;

        VisitorDoodad(T* doodad);
        VisitorDoodad(void);
};

#include "../src/VisitorDoodad.tpp"

#endif // VISITORDOODAD_H
