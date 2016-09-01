#ifndef VISITORDOODAD_H
#define VISITORDOODAD_H

#include "Doodad.h"
#include "Visitor.h"

template <typename T=Doodad>
class VisitorDoodad : public Visitor
{
    public:
        virtual ~VisitorDoodad();

    protected:
        T* m_doodad;

        VisitorDoodad(T* doodad);
        VisitorDoodad();
};

#include "../src/VisitorDoodad.tpp"

#endif // VISITORDOODAD_H
