#ifndef Pathfinding_hpp
#define Pathfinding_hpp

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

float stepsize = 16.0f;

namespace std {
    template < >
    struct hash < Point > {
        size_t operator()(const Point& p) const {
            return hash < float >()(p.x) ^ hash < float >()(p.y);
        }
    };
}

float heuristic(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

std::vector < Point > getNeighbors(GameObject* object, const Point& p) {
    std::vector < Point > neighbors;

    
    if (fabs(p.x - object->position.x) < 512.0f && fabs(p.y - object->position.y) < 512.0f) {

        if(!collisionPrediction(object, p, -stepsize, 0))
            neighbors.emplace_back(p.x - stepsize, p.y);

        if (!collisionPrediction(object, p, stepsize, 0))
            neighbors.emplace_back(p.x + stepsize, p.y);

        if (!collisionPrediction(object, p, 0, -stepsize))
            neighbors.emplace_back(p.x, p.y - stepsize);

        if (!collisionPrediction(object, p, 0, stepsize))
            neighbors.emplace_back(p.x, p.y + stepsize);

    }
 
    return neighbors;
}

std::vector < Point > aStar(GameObject* object, const Point& goal) {
    const Point& start = Point(object->position.x, object->position.y);
    std::priority_queue < std::pair < float, Point >, std::vector < std::pair < float, Point >>, std::greater < >> openSet;
    std::unordered_map < Point, Point > cameFrom;
    std::unordered_map < Point, int > costSoFar;
    sf::Time starttime = currentTime;

    openSet.emplace(0, start);
    cameFrom[start] = start;
    costSoFar[start] = 0;

    while (!openSet.empty()) {
        Point current = openSet.top().second;
        openSet.pop();

        if ((timeClock.getElapsedTime() - starttime).asSeconds() > 0.1f) { // HERE LIMITING
            return { };
        }


        if (current == goal) {
            std::vector < Point > path;
            while (current != start) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }
        else if (fabs(current.x - goal.x) < stepsize && fabs(current.y - goal.y) < stepsize)
        {
            Point next = Point(goal.x, goal.y);
            float newCost = costSoFar[current] + 1;
            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                costSoFar[next] = newCost;
                float priority = newCost + heuristic(next, goal);
                openSet.emplace(priority, next);
                cameFrom[next] = current;
            }
        }
        else {
            for (const Point& next : getNeighbors(object, current)) {
                float newCost = costSoFar[current] + 1;
                if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                    costSoFar[next] = newCost;
                    float priority = newCost + heuristic(next, goal);
                    openSet.emplace(priority, next);
                    cameFrom[next] = current;
                }
            }
        }

        
    }

    return { }; // No path found
}

#endif