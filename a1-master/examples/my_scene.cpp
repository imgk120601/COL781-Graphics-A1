#include "../src/a1.hpp"
#include <glm/gtc/matrix_transform.hpp>
// Program with perspective correct interpolation of vertex attributes.

namespace R = COL781::Software;
//namespace R = COL781::Hardware;
using namespace glm;
int main() {
	R::Rasterizer r;
	int width = 640, height = 480;
    if (!r.initialize("my_scene", width, height))
        return EXIT_FAILURE;

    R::ShaderProgram program = r.createShaderProgram(
        r.vsColorTransform(),
        r.fsIdentity()
    );
    vec4 vertices[] = {
        vec4( -0.75,  -0.25, 0.0, 1.0),
        vec4(  -0.5,  0.5, 0.0, 1.0),
		vec4( 0.0,   -0.25, 0.0, 1.0)
    };

	ivec3 triangles[] = {
		ivec3(0, 1, 2)
	};
	
    R::Object shape = r.createObject();
	r.setVertexAttribs(shape, 0, 3, vertices);

	r.setTriangleIndices(shape, 1, triangles);

    vec4 vertices1[] = {
        vec4( -1.0,  -1.0, 0.0, 1.0),
        vec4(  -0.5,  0.0, 0.0, 1.0),
		vec4( 0.0,   -1.0, 0.0, 1.0)
    };



   glm::mat4 trans = glm::mat4(1.0f);
trans = glm::translate(trans, glm::vec3(0.5f, 0.0f, 0.1f));

     for(int i=0; i<3; i++){
         vertices1[i]=trans*vertices[i];
     }



    //mountain-2
     R::Object shape1 = r.createObject();
	 r.setVertexAttribs(shape1, 0, 3, vertices1);

	 r.setTriangleIndices(shape1, 1, triangles);



    //grass
    vec4 vertices2[] = {
        vec4( -1.0,  -1.0, 0.0, 1.0),
        vec4(  1.0,  -1.0, 0.0, 1.0),
		vec4( 1.0,   -0.25, 0.0, 1.0),
        vec4( -1.0,  -0.25, 0.0, 1.0)

    };

	ivec3 triangles1[] = {
		ivec3(0, 1, 2),
        ivec3(0,2,3)
	};
	
    R::Object shape2 = r.createObject();
	r.setVertexAttribs(shape2, 0, 4, vertices2);

	r.setTriangleIndices(shape2, 2, triangles1);


    //sun
    vec4 vertices3[] = {
        vec4( -0.4,  -0.2, 0.5, 1.0),
        vec4(  0.0,  -0.2, 0.5, 1.0),
		vec4( 0.0,   0.2, 0.5, 1.0),
        vec4( -0.4,  0.2, 0.5, 1.0)
    };

    vec4 tempvertices3[] = {
         vec4( -0.4,  -0.2, 0.5, 1.0),
        vec4(  0.0,  -0.2, 0.5, 1.0),
		vec4( 0.0,   0.2, 0.5, 1.0),
        vec4( -0.4,  0.2, 0.5, 1.0)
    };


    glm::mat4 trans_sun = glm::mat4(1.0f);
    trans_sun = glm::translate(trans_sun, glm::vec3(0.0f, 0.01f, 0.0f));
	
	
    R::Object shape3 = r.createObject();
	r.setVertexAttribs(shape3, 0, 4, vertices3);

	r.setTriangleIndices(shape3, 2, triangles1);

  
    vec4 sky_color={0.0 ,0.0 ,0.0, 1.0};

    r.enableDepthTest();
    // The transformation matrix.
    //mat4 model = mat4(1.0f);
 	//mat4 view = translate(mat4(1.0f), vec3(0.0f, 0.0f, -2.0f)); 
   // mat4 projection = perspective(radians(60.0f), (float)width/(float)height, 0.1f, 100.0f);
    //float speed = 90.0f; // degrees per second
     

     std::vector<std::vector<float>> my_color={
        {39,33,78},
        {255,107,62},
        {247,193,106},
        {255,239,122},
        {181,214,224}

     };


    float crntTime=0;
   float prevTime=SDL_GetTicks64();

   int count=1;

   int count2=1;

    while (!r.shouldQuit()) {
        //float time = SDL_GetTicks64()*1e-3;
        //r.clear(vec4(0.23, 0.73, 1.0, 1.0));
        r.clear(sky_color);

        r.useShaderProgram(program);
        //model = rotate(mat4(1.0f), radians(speed * time), vec3(1.0f,0.0f,0.0f));
        //r.setUniform(program, "transform", projection * view * model);
        
        r.setUniform<vec4>(program, "color", vec4(0.70, 0.40, 0.20, 1.0));
		r.drawObject(shape);


         
         r.setUniform<vec4>(program, "color", vec4(0.80, 0.40, 0.20, 1.0));
		 r.drawObject(shape1);

        
        //grass
       r.setUniform<vec4>(program, "color", vec4(0.27, 0.85, 0.16, 1.0));
		 r.drawObject(shape2);


         //sun
        for(int i=0; i<4; i++){
            tempvertices3[i]=trans_sun*tempvertices3[i];
        }

        r.setVertexAttribs(shape3, 0, 4, tempvertices3);

	     r.setTriangleIndices(shape3, 2, triangles1);


       r.setUniform<vec4>(program, "color", vec4(1.0, 0.60, 0.20, 1.0));
		 r.drawObject(shape3);


          
        r.show();

         //    // Simple timer
       prevTime = SDL_GetTicks64();
       crntTime = SDL_GetTicks64();
		
		while (crntTime - prevTime <= 1000 )
		{
            crntTime = SDL_GetTicks64();   
		}

        count2++;
        
        if(count2==10){
            count2=0;
            if(count<4){
                count++;
            }

            sky_color={my_color[count][0]/255 , my_color[count][1]/255 ,my_color[count][2]/255 ,1.0 };

            
        }
        
       
    }
    r.deleteShaderProgram(program);
    return EXIT_SUCCESS;
}
