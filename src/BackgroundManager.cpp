#include "BackgroundManager.h"
#include "tools.h"

int BackgroundManager::m_minDepth = 0;
int BackgroundManager::m_maxDepth = 0;
std::map<int,std::vector<BackgroundDoodad*>> BackgroundManager::m_aBackground;

BackgroundManager::BackgroundManager()
{}

BackgroundManager::~BackgroundManager()
{}

void BackgroundManager::clear()
{
    for(std::map<int,std::vector<BackgroundDoodad*>>::iterator itDepth=m_aBackground.begin(); itDepth!=m_aBackground.end(); ++itDepth)
    {
    	std::vector<BackgroundDoodad*>& aBackground = itDepth->second;
    	for(std::vector<BackgroundDoodad*>::iterator itBackground=aBackground.begin(); itBackground!=aBackground.end(); )
		{
            BackgroundDoodad *tmp = *itBackground;
            aBackground.erase(itBackground);
			delete tmp;
		}
    }
}

void BackgroundManager::reset()
{
    m_minDepth = 0;
    m_maxDepth = 0;
}

void BackgroundManager::insertBackgroundDoodad(int depth, BackgroundDoodad* background)
{
    background->setDepth(depth);
    m_aBackground[depth].push_back(background);
    m_minDepth = MY_MIN(m_minDepth, depth);
    m_maxDepth = MY_MAX(m_maxDepth, depth);
}

void BackgroundManager::update(float dt)
{
    for(std::map<int,std::vector<BackgroundDoodad*>>::iterator itDepth=m_aBackground.begin(); itDepth!=m_aBackground.end(); ++itDepth)
    {
    	std::vector<BackgroundDoodad*> aBackground = itDepth->second;
    	for(std::vector<BackgroundDoodad*>::iterator itBackground=aBackground.begin(); itBackground!=aBackground.end(); )
		{
			(*itBackground)->update(dt);
			if((*itBackground)->isPendingDestruction())
			{
				BackgroundDoodad* tmp = *itBackground;
				aBackground.erase(itBackground);
				delete tmp;
			}
			else
				++itBackground;
		}
    }
}

void BackgroundManager::render(sf::RenderWindow& window)
{
    sf::View characterView = window.getView();
    for(std::map<int,std::vector<BackgroundDoodad*>>::iterator itDepth=m_aBackground.begin(); itDepth!=m_aBackground.end(); ++itDepth)
	{
	    int depth = itDepth->first;
        std::vector<BackgroundDoodad*> aBackground = itDepth->second;
    	for(std::vector<BackgroundDoodad*>::iterator itBackground=aBackground.begin(); itBackground!=aBackground.end(); ++itBackground)
		{
            sf::View depthView = characterView;
			if(depth < 0)
			{
				depthView.setCenter(characterView.getCenter().x * 0.5 * (m_minDepth-depth)/m_minDepth, characterView.getCenter().y * 0.5 * (m_minDepth-depth)/m_minDepth);
			}
            window.setView(depthView);
			(*itBackground)->render(window);
		}
	}
	window.setView(characterView);
}
