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

#endif // FRACTALPARAMS_H
