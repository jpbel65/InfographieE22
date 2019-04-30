#pragma once

#include <fstream>
#include <cmath>
#include "structs.h"
#include "linalg.h"
#include "string"
#include "ofMain.h"

namespace raytracer {
    linalg::vec<float, 3> time(linalg::vec<float, 3> v, float f) {
        return linalg::vec<float, 3>(v[0] * f, v[1] * f, v[2] * f);
    }

    linalg::vec<float, 3> reflection(const linalg::vec<float, 3> &I, const linalg::vec<float, 3> &normal) {
        return I - time(time(normal,2), dot(I,normal));
    }

    linalg::vec<float, 3> refraction(const linalg::vec<float, 3> &I, const linalg::vec<float, 3> &normal, const float &refraction) {
        float cosi = - std::max(-1.f, std::min(1.f, dot(I, normal)));
        float etai = 1, etat = refraction;
        linalg::vec<float, 3> n = normal;
        if (cosi < 0) {
            cosi = -cosi;
            std::swap(etai,etat);
            n = -normal;
        }

        float eta =etai / etat;
        float k = 1 - eta*eta*(1-cosi*cosi);
        
        return k < 0 ? linalg::vec<float, 3>(0,0,0) : time(I, eta) + time(n, eta * cosi - sqrtf(k));
    }

    bool intersect(const raytracer::Sphere &sphere,const raytracer::Ray &ray, float &t0) {
        linalg::vec<float, 3> L = sphere.center - ray.start;
        float tca = dot(L,ray.dir);
        float d2 = dot(L,L) - tca*tca;
        if (d2 > sphere.radius*sphere.radius) return false;
        float thc = sqrtf(sphere.radius*sphere.radius - d2);
        t0       = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0) t0 = t1;

        if (t0 < 0) return false;
        return true;
    }

    raytracer::Color cast_ray(const std::vector<raytracer::Sphere> &spheres, const raytracer::Ray &ray, const std::vector<raytracer::Point_light> &lights, const raytracer::Color &ambiant_color, size_t depth = 0) {
        using namespace std;
        raytracer::Color color(ambiant_color);
        float dist = std::numeric_limits<float>::max();

        if (depth <= 8) {
            for(auto&& sphere : spheres)
            {
                float dist_i;
                if (intersect(sphere, ray, dist_i)) {
                    if (dist_i < dist) {
                        dist = dist_i;
                        float diffuse_intensity = 0;
                        float specular_intensity = 0;
                        linalg::vec<float, 3> normal = normalize(ray.ray_pos(dist) - sphere.center);

                        // -------------------------------
                        // Reflection
                        // -------------------------------
                        linalg::vec<float, 3> reflection_dir = reflection(ray.dir, normal);
                        linalg::vec<float, 3> reflection_orig = dot(reflection_dir,normal) < 0 ? 
                            ray.ray_pos(dist) - time(normal, 1e-3) : ray.ray_pos(dist) + time(normal, 1e-3);
                        raytracer::Ray reflection_ray(reflection_orig, reflection_dir);
                        linalg::vec<float, 3> reflection_color = cast_ray(spheres, reflection_ray, lights, ambiant_color, depth + 1).rgb;

                        // -------------------------------
                        // Refraction
                        // -------------------------------
                        linalg::vec<float, 3> refraction_dir = refraction(ray.dir, normal, sphere.material.refraction);
                        linalg::vec<float, 3> refraction_orig = dot(refraction_dir,normal) < 0 ? 
                            ray.ray_pos(dist) - time(normal, 1e-3) : ray.ray_pos(dist) + time(normal, 1e-3);
                        raytracer::Ray refraction_ray(refraction_orig, refraction_dir);
                        linalg::vec<float, 3> refraction_color = cast_ray(spheres, refraction_ray, lights, ambiant_color, depth + 1).rgb;

                        // -------------------------------
                        // Ombrage
                        // -------------------------------
                        for(auto&& light : lights)
                        {
                            linalg::vec<float, 3> light_dir = normalize(light.pos - ray.ray_pos(dist));
                            float light_dist = length(light.pos - ray.ray_pos(dist));
                            linalg::vec<float, 3> shadow_orig = dot(light_dir, normal) < 0 ? 
                                ray.ray_pos(dist) - time(normal, 1e-3) : ray.ray_pos(dist) + time(normal, 1e-3);
                            float shadow_dist;
                            raytracer::Ray shadow_ray(shadow_orig, normalize(light.pos - shadow_orig));
                            bool shadow = false;
                            for(auto&& sphere2 : spheres)
                            {
                                if (intersect(sphere2, shadow_ray, shadow_dist) && shadow_dist < light_dist) {
                                    shadow = true;
                                }
                            }
                            if (!shadow) {
                                diffuse_intensity += light.intensity * std::max(0.f, dot(light_dir, normal));
                                specular_intensity += pow(std::max(0.f, dot(-reflection(-light_dir, normal), ray.dir)), sphere.material.specularExponent) * light.intensity;
                            }
                        }
                        
                        // -------------------------------
                        // Couleur retournée
                        // -------------------------------
                        color.rgb = time(time(sphere.material.diffuseColor.rgb,diffuse_intensity), sphere.material.albedo[0]) +
                                    time(time(linalg::vec<float, 3>(1,1,1), specular_intensity), sphere.material.albedo[1]) +
                                    time(reflection_color, sphere.material.albedo[2]) +
                                    time(refraction_color, sphere.material.albedo[3]);
                    }
                    
                }
            }
        }

        return color;
    }

    void render(const std::vector<raytracer::Sphere> &spheres, const std::vector<raytracer::Point_light> &lights, const raytracer::Color &ambiant_color, unsigned int width, unsigned int height) {
        ofPixels pixels;
        pixels.allocate(width, height, OF_IMAGE_COLOR);
        linalg::vec<float, 3> pos(0,0,0);
        const int fov = M_PI/2.;

        std::vector<raytracer::Color> framebuffer(width*height);

        // ----------------------------------------
        // Remplissage du framebuffer (paralellisé)
        // ----------------------------------------
        // #pragma omp parallel for
        for (size_t j = 0; j<height; j++) {
            for (size_t i = 0; i<width; i++) {
                float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
                float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
                linalg::vec<float, 3> dir(x,y, -1);
                raytracer::Ray ray(pos, dir);
                framebuffer[i+j*width] = cast_ray(spheres, ray, lights, ambiant_color);
            }
        }

        // ----------------------------------------
        // Écriture du fichier
        // ----------------------------------------
        std::ofstream ofs;
        ofs.open(ofToDataPath("raytrace.ppm"));
        ofs << "P6\n" << width << " " << height << "\n255\n";
        for (size_t i = 0; i < height*width; ++i) {
            raytracer::Color &c = framebuffer[i];
            float max = std::max(c.rgb[0], std::max(c.rgb[1], c.rgb[2]));
            if (max>1) c.rgb = time(c.rgb,(1.f/max));
            pixels.setColor(framebuffer[i].rgb[0], framebuffer[i].rgb[1], framebuffer[i].rgb[2]);
            for (size_t j = 0; j<3; j++) {
                ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i].rgb[j])));
            }
        }
        ofs.close();
        // return pixels;
    }
}
