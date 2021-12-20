#include "World.hpp"

World::World(){
    camera_ptr = NULL;
    sampler_ptr = NULL;
	grid_ptr = NULL;
    std::vector<Geometry *> geometry;
}

World::~World(){   
    
}

void World::add_geometry(Geometry *geom_ptr){
    geometry.push_back(geom_ptr);
}

void World::add_light(Light* light_ptr){
    lights.push_back(light_ptr);
}

void World::set_camera(Camera *c_ptr){
    camera_ptr = c_ptr;
}

void World::set_acceleration(Acceleration *g_ptr){
	grid_ptr = g_ptr;
}

ShadeInfo World::hit_objects(const Ray &ray){
    ShadeInfo sf(*this);
    float t = kHugeValue;
    for (const auto &g: geometry){
        if (g->hit(ray, t, sf) & (sf.t > t)) //if the ray hits the object
        {
            // update the following values of shadeinfo:
            sf.hit=true;
            sf.t=t;
            sf.material_ptr=g->get_material();
            sf.ray=ray;
        }
    }
    sf.normal.normalize();
    sf.ray.d.normalize();
    return sf;
}

void World::set_tracer(Tracer *t_ptr){
    tracer_ptr = t_ptr;
}

void World::load_OBJ(const char* file_name){
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
			// std::cout << temp_point.to_string() << '\n';
			
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
	std::cout << "Num of vertices " << vertex_positions.size()<< '\n';
	std::cout << "Num of vertex positions " << vertex_position_indicies.size() << '\n';

	Triangle* triangle_ptr;
	Point3D v0,v1,v2;
	//Load in all indices
	for (auto it = vertex_position_indicies.begin(); it != (vertex_position_indicies.end()-3); it+=3) {
		std::cout<<"it: "<< *it << std::endl;
		v0 = vertex_positions.at(*it-1);
		v1 = vertex_positions.at(*(it+1)-1);
		v2 = vertex_positions.at(*(it+2)-1);
 		triangle_ptr = new Triangle(v0, v1, v2);
		triangle_ptr->set_material(new Cosine(blue));
        add_geometry(triangle_ptr);
		// grid_ptr->add_object(triangle_ptr);
	}
	// grid_ptr->setup_cells(); // must be called after all adding all triangles
	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";
}
