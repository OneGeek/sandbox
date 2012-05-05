
#include <vector>
#include <algorithm>
#include <memory>

#include <stdio.h>

#include "voronoi.h"
#include "constants.h"
#include "vectorUtil.h"
#include "rawbinarytree.h"


using namespace Voronoi;
using namespace std;

// HalfEdge
HalfEdge::HalfEdge(){}

HalfEdge::HalfEdge(SitePtr _from, SitePtr _to)
:from(_from), to(_to),twin(new HalfEdge(_to, _from, HalfEdgePtr(this)))
{}


HalfEdge::HalfEdge(SitePtr _from, SitePtr _to, HalfEdgePtr _twin)
:from(_from), to(_to),twin(_twin)
{}

// Site
Site::Site(Vector2i _position)
:position(_position)
{}

Site::Site(){}

Site::Site(int x, int y)
:position(Vector2i(x,y))
{}

// Diagram
void Diagram::addSite(SitePtr site)
{
    sites.push_back(site);
}

void Diagram::generate()
{
    Beachline beachline;
    vector<SitePtr> sitesLeft = sites;

    for (int sweepY=0; sweepY<WINDOW_HEIGHT; sweepY++)
    {

        // Out of the sites we haven't integrated into the diagram yet, find those that
        // just crossed the sweepline
        vector<SitePtr> sitesFound;
        for (auto iter=sitesLeft.begin(); iter != sitesLeft.end(); iter++)
        {
            auto site = *iter;

            // Site event
            if (site->position.y <= sweepY) {
                sitesFound.push_back(site);
            }
        }

        // If we found sites, remove them from the 'left to find' list
        if (!sitesFound.empty())
        {
            printf("Found site(s) at %d\t%d sites left\n", sweepY, sitesLeft.size());

            for (auto iter=sitesFound.begin(); iter != sitesFound.end(); iter++)
            {
                auto site = *iter;
                if (beachline.site == nullptr) {
                    beachline.site = site;

                }else {
                    beachline.insert(site);
                }
                remove(site, sitesLeft);
            }
        }
    }


}

Beachline::Beachline(SitePtr _site, Beachline* _prev, Beachline* _next)
:next(_prev), prev(_next), site(_site){}


void Beachline::insert(SitePtr insertedSite) {
    prev = new Beachline(site, prev, this);
    next = new Beachline(site, this, next);
    site = insertedSite;
}

void Beachline::remove() {
    if (prev) {
        prev->next = next;
    }

    if (next) {
        next->prev = prev;
    }
}


