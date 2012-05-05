#pragma once

#include <memory>
#include <vector>
#include <SFML/System.hpp>

using std::vector;
using std::shared_ptr;
using sf::Vector2i;

#define PtrType(T) typedef shared_ptr<T> T ## Ptr

namespace Voronoi {
    class HalfEdge;
    class Site;
    class Diagram;

    PtrType(Site);
    PtrType(HalfEdge);

    class HalfEdge {
    public:
        SitePtr from;
        SitePtr to;

        HalfEdgePtr next;
        HalfEdgePtr prev;
        HalfEdgePtr twin;

        HalfEdge();
        HalfEdge(SitePtr _from, SitePtr _to);
        HalfEdge(SitePtr _from, SitePtr _to, HalfEdgePtr _twin);
    };

    class Site {
    public:
        vector<HalfEdgePtr> incidentEdges;
        Vector2i position;

        Site();
        Site(Vector2i _position);
        Site(int x, int y);
    };
    inline bool operator==(const Site& lhs, const Site& rhs){return lhs.position.x == rhs.position.x; }
    inline bool operator!=(const Site& lhs, const Site& rhs){return !operator==(lhs,rhs);}
    inline bool operator< (const Site& lhs, const Site& rhs){return lhs.position.x < rhs.position.x; }
    inline bool operator> (const Site& lhs, const Site& rhs){return  operator< (rhs,lhs);}
    inline bool operator<=(const Site& lhs, const Site& rhs){return !operator> (lhs,rhs);}
    inline bool operator>=(const Site& lhs, const Site& rhs){return !operator< (lhs,rhs);}

    inline bool operator==(const SitePtr& lhs, const SitePtr& rhs){return lhs->position.x == rhs->position.x; }
    inline bool operator!=(const SitePtr& lhs, const SitePtr& rhs){return !operator==(lhs,rhs);}
    inline bool operator< (const SitePtr& lhs, const SitePtr& rhs){return lhs->position.x < rhs->position.x; }
    inline bool operator> (const SitePtr& lhs, const SitePtr& rhs){return  operator< (rhs,lhs);}
    inline bool operator<=(const SitePtr& lhs, const SitePtr& rhs){return !operator> (lhs,rhs);}
    inline bool operator>=(const SitePtr& lhs, const SitePtr& rhs){return !operator< (lhs,rhs);}

    class Diagram {
    public:
        vector<SitePtr> sites;

        void addSite(SitePtr site);

        void generate();

    };

    class SiteEvent {
    public:
        Vector2i posiiton;
    };

    class VertexEvent {
    public:
        Vector2i positon;
    };

    class Beachline {
    public:
        Beachline* next;
        Beachline* prev;
        SitePtr site;

        Beachline(SitePtr _site=nullptr, Beachline* _prev=nullptr, Beachline* _next=nullptr);

        void insert(SitePtr insertedSite);
        void remove();
    };

}





