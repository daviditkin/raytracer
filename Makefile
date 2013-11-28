all:
	clang++ Vector.cpp Matrix.cpp Sphere.cpp Scene.cpp Main.cpp -o lab3 -lglut -lGL -lGLU -fpermissive -O
