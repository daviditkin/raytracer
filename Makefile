all:
	clang++ Vector.cpp Cone.cpp Cylinder.cpp Coefficient.cpp Intensity.cpp Light.cpp Sphere.cpp Rect.cpp Scene.cpp Main.cpp -o lab3 -lglut -lGL -lGLU -fpermissive -O
