template <typename T>
ListDoodad<T>::ListDoodad()
{}

template <typename T>
ListDoodad<T>::~ListDoodad()
{}

template <typename T>
unsigned int ListDoodad<T>::size()
{
	return m_doodads.size();
}

template <typename T>
T& ListDoodad<T>::getDoodad(int i)
{
    return m_doodads.at(i);
}

template <typename T>
std::vector<T>& ListDoodad<T>::getList()
{
    return m_doodads;
}

template <typename T>
void ListDoodad<T>::insereDoodad(T doodad)
{
	m_doodads.push_back(doodad);
}

template <typename T>
void ListDoodad<T>::collision(Doodad& doodad)
{
    for(unsigned int i=0; i<m_doodads.size(); i++)
		m_doodads.at(i).collision(doodad);
}

template <typename T>
void ListDoodad<T>::collisionVector(std::vector<Doodad>& doodads)
{
    for(unsigned int i=0; i<m_doodads.size(); i++)
        collision(doodads.at(i));
}

template <typename T>
void ListDoodad<T>::collisionList(ListDoodad<Doodad>& doodads)
{
    for(unsigned int i=0; i<m_doodads.size(); i++)
        doodads.collision(m_doodads.at(i));
}

template <typename T>
EstheticEffect* ListDoodad<T>::popEstheticEffect()
{
    for(typename std::vector<T>::iterator it=m_doodads.begin(); it!=m_doodads.end(); ++it)
    {
        EstheticEffect* ee = it->popEstheticEffect();
        if(nullptr != ee)
            return ee;
    }
    return nullptr;
}

template <typename T>
void ListDoodad<T>::update(float dt)
{
    for(typename std::vector<T>::iterator it=m_doodads.begin(); it!=m_doodads.end(); )
    {
        it->update(dt);
        if(it->isPendingDestruction())
            m_doodads.erase(it);
        else
            ++it;
    }
}

template <typename T>
void ListDoodad<T>::render(sf::RenderWindow& window)
{
    for(typename std::vector<T>::iterator it=m_doodads.begin(); it!=m_doodads.end(); ++it)
        it->render(window);
}
