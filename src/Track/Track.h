/* --- Track.h --- */

/* ------------------------------------------
Author: User
Date: 11/19/2024
------------------------------------------ */

#ifndef TRACK_H
#define TRACK_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "DataStructure.h"

class ControlPoint;
class ShaderProgram;

class Track
{
public:
    Track();
    ~Track();

    void Render(ShaderProgram *program);

    void setTrackMode(const TrackMode &newTrackMode);
    void setNewTension(const float &tension);

    void createNewPoint();

private:
    struct TrackNode
    {
        glm::vec3 position;
        glm::vec3 rotation;
    };

    struct TrackObject
    {
        GLuint VAO;
        GLuint VBO;
        glm::mat4 model;
    };

    std::vector<TrackNode> m_nodes;
    std::vector<ControlPoint> m_controlPoints;
    TrackObject m_trackObject;
    TrackMode trackMode;
    float m_tension;

private:
    void updateTrack();
    void createLinearTrack();
    void createBezierTrack();
    void createBSplineTrack();
    void createCarinalTrack();
    void createTrackObject();

    void computeBSplineBasis(TrackNode &B0, TrackNode &B1, TrackNode &B2, TrackNode &B3);
    void computeCarinalBasis(TrackNode &B0, TrackNode &B1, TrackNode &B2, TrackNode &B3);
    void createPartBazier(TrackNode &startNode, TrackNode &ctrl0, TrackNode &ctrl1, TrackNode &endNode);
};

#endif // TRACK_H
