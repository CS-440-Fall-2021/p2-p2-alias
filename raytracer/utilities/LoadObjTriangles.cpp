
#include "Vector3D.hpp"
#include "../geometry/Triangle.hpp"
#include <vector>
#include <iostream>
// #include <stdio.h>
#include <fstream>
#include <string>
#include<sstream>

//Reference: https://github.com/Headturna/OpenGL-C---Tutorials/blob/master/OBJLoader.h
std::vector<Triangle> loadOBJ(const char* file_name)
{
	//Vertex portions
	std::vector<Point3D> vertex_positions;

	//Face vectors
	std::vector<int> vertex_position_indicies;

	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	int temp_index = 0;

	Point3D temp_point;

	//File open error check
	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	//Read one line at a time
	while (std::getline(in_file, line))
	{
		//Get the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;

	
		if (prefix == "v") //Vertex position
		{
			ss >> temp_point.x >> temp_point.y >> temp_point.z;
			//DEBUG
			std::cout << temp_point.to_string() << '\n';

			vertex_positions.push_back(temp_point);
		}

		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> temp_index)
			{
				//Push only the vertex index ignore the texture and normal indices
				if (counter == 0)
					vertex_position_indicies.push_back(temp_index);

				//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
					counter = 0;
			}	
		}
	}

	//DEBUG
	std::cout << "Num of vertices" << vertex_positions.size()<< '\n';
	std::cout << "Num of vertex positions" << vertex_position_indicies.size() << '\n';

	//Triangle array
	std::vector<Triangle*> triangles;
	Triangle* triangle_ptr;
	Point3D v0,v1,v2;
	//Load in all indices
	for (size_t i = 0; i < triangles.size(); ++i)
	{
		v0 = vertex_positions[vertex_position_indicies[i]-1];
		v1 = vertex_positions[vertex_position_indicies[i+1]-1];
		v2 = vertex_positions[vertex_position_indicies[i+2]-1];
 		triangle_ptr = new Triangle(v0, v1, v2);
		triangles.push_back(triangle_ptr);
		
	}

	//DEBUG
	std::cout << "Num of triangles: " << triangles.size() << "\n";

	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";
	return triangles;
}