all:
	clang++ Vector.cpp Matrix.cpp Coefficient.cpp Intensity.cpp Light.cpp Sphere.cpp Rect.cpp Scene.cpp Main.cpp -o lab3 -lglut -lGL -lGLU -fpermissive -O
