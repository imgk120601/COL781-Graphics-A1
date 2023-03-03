#include "../src/a1.hpp"

// namespace R = COL781::Software;
//namespace R = COL781::Hardware;
namespace R = COL781::Software;
using namespace glm;

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <map>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <math.h>

#include <glm/geometric.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>



int main() {
	R::Rasterizer r;
    if (!r.initialize("Example 1", 640, 480))
        return EXIT_FAILURE;
    R::ShaderProgram program = r.createShaderProgram(
        r.vsIdentity(),
        r.fsConstant()
    );
glm::vec4 color(1.00, 0.00, 0.00, 1.0);
    glm::vec4 color1(0.00, 1.00, 0.00, 1.0);
 glm::vec4 color2(0.00, 0.00, 1.00, 1.0);
  glm::vec4 color3(1.00, 1.00, 1.00, 1.0);

    glm::vec4 vertices[] = {
        glm::vec4(0.01,0,0,0),
        glm::vec4(0.01,1.0,0,0),
        
        glm::vec4(-0.01,1.0,0,0),
        glm::vec4(-0.01,1.0,0,0)

};

    glm::vec4 vertices1[] = {
   glm::vec4(0.01,0,0,0),
        glm::vec4(0.01,1.0,0,0),
        
        glm::vec4(-0.01,1.0,0,0),
        glm::vec4(-0.01,1.0,0,0)

};

    glm::vec4 vertices2[] = {
     glm::vec4(0.02,0,0,0),
        glm::vec4(0.02,0.5,0,0),
        
        glm::vec4(-0.02,0.5,0,0),
        glm::vec4(-0.02,0,0,0)

};


    glm::ivec3 indices[] = {
        glm::ivec3(0, 1, 2),
        glm::ivec3(0,2,3)
    };

	glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 model1 = glm::mat4(1.0f);
    glm::mat4 model2 = glm::mat4(1.0f);
    glm::mat4 tempmodel= glm::mat4(1.0f);

    glm::vec4 tempvertices[] = {
      glm::vec4(0.01,0,0,0),
        glm::vec4(0.01,1.0,0,0),
        
        glm::vec4(-0.01,1.0,0,0),
        glm::vec4(-0.01,0.0,0,0)
};

    glm::vec4 tempvertices1[] = {
  glm::vec4(0.01,0,0,0),
        glm::vec4(0.01,1.0,0,0),
        
        glm::vec4(-0.01,1.0,0,0),
        glm::vec4(-0.01,0.0,0,0)

};
    glm::vec4 tempvertices2[] = {
     glm::vec4(0.02,0,0,0),
        glm::vec4(0.02,0.5,0,0),
        
        glm::vec4(-0.02,0.5,0,0),
        glm::vec4(-0.02,0,0,0)

};



    float crntTime=0;
   float prevTime=SDL_GetTicks64();
   float rotation = 0.0f;

      float rotationhr=0.0f;
    float rotationmin=0.0f;
    float rotationsec=0.0f;
   
    int second=0;
    int min=0;
    int hr=0;










	R::Object a1 = r.createObject();
	 r.setVertexAttribs(a1, 0, 4, vertices);
	r.setTriangleIndices(a1, 2, indices);

     r.setUniform(program, "color", vec4(0.9, 0.6, 0.0, 1.0));
    r.drawObject(a1);

    R::Object a2 = r.createObject();
	 r.setVertexAttribs(a2, 0, 4, vertices1);
	r.setTriangleIndices(a2, 2, indices);

     r.setUniform(program, "color", vec4(0.9, 0.0, 0.3, 1.0));
    r.drawObject(a2);
    
    R::Object a3 = r.createObject();
	 r.setVertexAttribs(a3, 0, 4, vertices2);
	r.setTriangleIndices(a3, 2, indices);

     r.setUniform(program, "color", vec4(0.0, 0.6, 0.3, 1.0));
    r.drawObject(a3);
    


    
       while (!r.shouldQuit()) {


            //    // Simple timer
            prevTime = SDL_GetTicks64();
            crntTime = SDL_GetTicks64();
                
            while (crntTime - prevTime <= 1000 )
            {
                crntTime = SDL_GetTicks64();   
            }

            second++;

            rotationsec = 0.0174532925*second*6*59;
        
        
            r.clear(vec4(1.0, 1.0, 1.0, 1.0));
            r.useShaderProgram(program);


            model = glm::rotate(tempmodel, glm::radians(-rotationsec), glm::vec3(0.0f, 0.0f, 1.0f));

            for(int i=0; i<3; i++){
                tempvertices[i]=model*vertices[i];
            }

            


            //r.rasterizeMultipleTriangle(tempvertices,color,indices);
            R::Object a1 = r.createObject();
	        r.setVertexAttribs(a1, 0, 4, tempvertices);
	        r.setTriangleIndices(a1, 2, indices);

             r.setUniform(program, "color", vec4(0.9, 0.6, 0.0, 1.0));

            r.drawObject(a1);

        

           if(second==58){
               min++;
               rotationmin = 0.0174532925*min*6*59;
                model1 = glm::rotate(tempmodel, glm::radians(-rotationmin), glm::vec3(0.0f, 0.0f, 1.0f));

                for(int i=0; i<3; i++){
                    tempvertices1[i]=model1*vertices1[i];
                }

                second=0;
                //rotationsec=0;

           }
            if(min==58){
                hr++;
               rotationhr =  0.0174532925*hr*6*59;
                model2 = glm::rotate(tempmodel, glm::radians(-rotationhr), glm::vec3(0.0f, 0.0f, 1.0f));

                for(int i=0; i<3; i++){
                    tempvertices2[i]=model2*vertices2[i];
                }

                min=0;
                //rotationmin=0;
           }

            R::Object a2 = r.createObject();
	        r.setVertexAttribs(a2, 0, 4, tempvertices1);
	        r.setTriangleIndices(a2, 2, indices);

             r.setUniform(program, "color", vec4(0.9, 0.0, 0.3, 1.0));
            r.drawObject(a2);

            //r.rasterizeMultipleTriangle(tempvertices1,color1,indices);


            R::Object a3 = r.createObject();
	        r.setVertexAttribs(a3, 0, 4, tempvertices2);
	        r.setTriangleIndices(a3, 2, indices);


             r.setUniform(program, "color", vec4(0.0, 0.6, 0.3, 1.0));
            r.drawObject(a3);
            //r.rasterizeMultipleTriangle(tempvertices2,color2,indices);

           // drawclock();

            //pipe->updateScreen();

    
	    	//r.drawObject(tickmark);
            r.show();
      }
     r.deleteShaderProgram(program);
    return EXIT_SUCCESS;
}
