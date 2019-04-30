#pragma once

#include "vector"
#include <iostream>
#include <math.h>
#include <limits>
#include "linalg.h"

namespace raytracer
{

    struct Ray
    {
        Ray(linalg::vec<float, 3> p_start, linalg::vec<float, 3> p_dir, bool n = true) : start(p_start), dir(p_dir) {
            if (n) {
                dir = normalize(p_dir);
            }
            
        }
        Ray() {}

        linalg::vec<float, 3> start;
        linalg::vec<float, 3> dir;

        linalg::vec<float, 3> ray_pos(float t) const {
            float x = start[0] + (dir[0] * t);
            float y = start[1] + (dir[1] * t);
            float z = start[2] + (dir[2] * t);

            return linalg::vec<float, 3>(x,y,z);
        }
    };
    

    struct Color
    {
        Color(float r, float g, float b, float ai) : a(ai) {
            rgb = linalg::vec<float, 3>(r,g,b);
        }
        Color(float r, float g, float b) : a(1) {
            rgb = linalg::vec<float, 3>(r,g,b);
        }
        Color(linalg::vec<float, 3> c) : rgb(c), a(1) {}
        Color() {}

        linalg::vec<float, 3> rgb;
        float a = 1;

        char r() {
            return ((char) (255 * std::max(0.f, std::min(1.f, rgb[0]))));
        }

        char g() {
            return ((char) (255 * std::max(0.f, std::min(1.f, rgb[1]))));
        }

        char b() {
            return ((char) (255 * std::max(0.f, std::min(1.f, rgb[2]))));
        }

        std::string print() {
            return std::to_string((int)(rgb[0] * 255.0)) + " " + 
                std::to_string((int)(rgb[1] * 255.0)) + " " + 
                std::to_string((int)(rgb[2]*255.0)) + " ";
        }
    };

    struct Material
    {
        Material(Color p_diffuseColor, linalg::vec<float, 4> a, float s, float r) : 
            diffuseColor(p_diffuseColor),
            albedo(a),
            specularExponent(s),
            refraction(r) {
        }
        Material() {}

        Color diffuseColor;
        linalg::vec<float, 4> albedo;
        float specularExponent = 1;
        float refraction = 0;
    };

    struct Sphere
    {
        Sphere(float x,float y,float z,float r) : radius(r) {
            center = linalg::vec<float, 3>(x, y, z);
        }
        Sphere(float x,float y,float z,float r, Material mat) : radius(r), material(mat) {
            center = linalg::vec<float, 3>(x, y, z);
        }
        Sphere() {}
        linalg::vec<float, 3> center;
        float radius = 1;
        Material material;
    };

    struct Point_light
    {
        Point_light(linalg::vec<float, 3> p, float i) : pos(p), intensity(i) {}

        linalg::vec<float, 3> pos;
        float intensity = 1;
    };

    struct Camera
    {
        Camera() {}

        linalg::vec<float, 3> pos;
        linalg::vec<float, 3> dir;
        float fov;
    };
}
