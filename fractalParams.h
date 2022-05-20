#ifndef FRACTALPARAMS_H
#define FRACTALPARAMS_H

#include <QVector2D>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
struct FractalParams
{
    enum TYPE {JULIA, MANDELBROT, NEWTON};
    TYPE type = MANDELBROT;
    bool grid = false;
    QVector2D m_c0; // relevant only for JULIA
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
struct CartesianGridView
{
    QVector2D m_center{0.0f, 0.0f};
    float     m_distPerPixel = 3.0f / 1920;
};

#endif // FRACTALPARAMS_H
