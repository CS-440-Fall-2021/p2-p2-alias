#include "Image.hpp"
#include "RGBColor.hpp"
#include <iostream>

Image::Image(int hres, int vres)
{
    this->hres = hres;
    this->vres = vres;

    colors = new RGBColor*[hres];
    for(int i = 0; i < hres; i++)
        colors[i] = new RGBColor[vres];
}

Image::Image(const ViewPlane &vp)
{
    hres = vp.hres;
    vres = vp.vres;
    colors = new RGBColor*[hres];
    for (int i = 0; i < hres; i++)  {
        colors[i] = new RGBColor[vres];
    }
}


Image::~Image()
{
    
    for(int i = 0; i < hres; i++)
        delete[] colors[i];
    delete[] colors;
}

void Image::set_pixel(int x, int y, const RGBColor &color)
{  //all r g b values are set for the pixel
    
    colors[y][x].r = (int) (color.r * 255);
    colors[y][x].g = (int) (color.g * 255);
    colors[y][x].b = (int) (color.b * 255);
}

void Image::write_ppm(std::string path) const
{
    const char *p = path.c_str();
    FILE *pFile;
    pFile = fopen(p, "w"); //opens or creates file
    if (pFile != NULL)
    {   //initial info for ppm file
        fputs("P3 \n", pFile);
        fputs((std::to_string(hres)+ " ").c_str(), pFile);
        fputs((std::to_string(vres)+ "\n").c_str() , pFile);
        fputs("255 \n", pFile);

        //stores the info of the pixel color in the ppm file
        for(int i=0; i<hres;i++)
        {
            for (int j=0; j<vres;j++)
            {
               fputs(colors[i][j].to_string().c_str(), pFile);
            }
        }
        fclose(pFile);
    }
};