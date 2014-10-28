raytracer
=========

Computer Graphics I project 3 - Raytracer in C++ and OpenGL

This is a very simple and stupid raytracer. Given a scene with objects, it casts rays through each pixel of the screen region and follows its path.
At each intersection with an object in the scene, it decomposes the ray into a refracted and a reflected ray, recursively tracing their path too.
At each intersection the light level and type of the components is the aggregated, until a value for the pixel is computed.
