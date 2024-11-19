/* --- Track.h --- */

/* ------------------------------------------
Author: User
Date: 11/19/2024
------------------------------------------ */

#ifndef TRACK_H
#define TRACK_H

#include <vector>

class ControlPoint;
class ShaderProgram;

class Track {
public:
    Track();
    ~Track();

    void Render(ShaderProgram* program);

private:
    std::vector<ControlPoint> m_points;
    
};

#endif // TRACK_H
