#include "World.hpp"
#include "../BRDF/Lambertian.hpp"
#include "../materials/Matte.hpp"

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
    double t = kHugeValue;
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
	std::ifstream in_file = std::ifstream(file_name);
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
		// std::cout<<"it: "<< *it << std::endl;
		v0 = vertex_positions.at(*it-1);
		v1 = vertex_positions.at(*(it+1)-1);
		v2 = vertex_positions.at(*(it+2)-1);
 		triangle_ptr = new Triangle(v0, v1, v2, Vector3D((v1 - v0) ^ (v2 - v0)));
		Lambertian *amb = new Lambertian(0.3, white);
		Lambertian *diff = new Lambertian(1.0, white);
		triangle_ptr->set_material(new Matte(amb, diff));
        // add_geometry(triangle_ptr);
		grid_ptr->add_object(triangle_ptr);
	}
	grid_ptr->setup_cells(); // must be called after all adding all triangles
	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";
}


void World::load_scene(std::string filename, bool load_colors)
{
    std::ifstream infile(filename);

    int n_points, n_faces;
    double x, y, z, nx, ny, nz, s, t,red, green, blue, alpha;
    std::string data;

    std::getline(infile, data);         // ply
    std::getline(infile, data);         // format ascii 1.0
    std::getline(infile, data);         // comment Created by Blender 3.0.0 - www.blender.org
    infile >> data >> data >> n_points; // element vertex N_POINTS
    std::getline(infile, data);         // \n
    std::getline(infile, data);         // property double x
    std::getline(infile, data);         // property double y
    std::getline(infile, data);         // property double z
    std::getline(infile, data);         // property double nx
    std::getline(infile, data);         // property double ny
    std::getline(infile, data);         // property double nz
    std::getline(infile, data);         // property double s
    std::getline(infile, data);         // property double t
    std::getline(infile, data);         // property uchar red
    std::getline(infile, data);         // property uchar green
    std::getline(infile, data);         // property uchar blue
    std::getline(infile, data);         // property uchar alpha
    infile >> data >> data >> n_faces;  // element face N_FACES
    std::getline(infile, data);         // \n
    std::getline(infile, data);         // property list uchar uint vertex_indices
    std::getline(infile, data);         // end_header

    Point3D *points = new Point3D[n_points];
    RGBColor *colors = new RGBColor[n_points];
    Vector3D *normals = new Vector3D[n_points];

    std::cout << "N_POINTS: " << n_points << std::endl;
    std::cout << "N_FACES: " << n_faces << std::endl;

    // reading the vertices
    for (int i = 0; i < n_points; i++)
    {
        infile >> x >> y >> z >> nx >> ny >> nz >> s >> t >> red >> green >> blue >> alpha;

        points[i] = Point3D(x, y, z);

        normals[i] = Vector3D(nx, ny, nz);
        normals[i].normalize();

        // assigning vertex colors
        if (load_colors)
        {
            colors[i] = RGBColor(red / (double)256.0, green / (double)256.0, blue / (double)256.0); // actual color from ply file
        }
        else
        {
            colors[i] = RGBColor(1.0); // white color
        }
    }

    int n, a, b, c;
    RGBColor face_color;
    Triangle *triangle_ptr;

    // reading the faces
    for (int i = 0; i < n_faces; i++)
    {
        infile >> n >> a >> b >> c;

        face_color = RGBColor(colors[a] / (double)3.0) + (colors[b] / (double)3.0) + (colors[c] / (double)3.0);

        triangle_ptr = new Triangle(points[a], points[b], points[c], normals[a], normals[b], normals[c]);
		Lambertian *amb = new Lambertian(1.0, face_color);
		Lambertian *diff = new Lambertian(1.0, face_color);
        triangle_ptr->set_material(new Matte(amb, diff));

        grid_ptr->add_object(triangle_ptr);
    }
    std::cout << "loaded\n";
    infile.close();
}