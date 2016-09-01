template <typename T>
VisitorDoodad<T>::VisitorDoodad(T* doodad)
: Visitor()
, m_doodad(doodad)
{}

template <typename T>
VisitorDoodad<T>::VisitorDoodad()
: VisitorDoodad(nullptr)
{}

template <typename T>
VisitorDoodad<T>::~VisitorDoodad()
{}
