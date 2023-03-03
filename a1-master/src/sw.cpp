#include "sw.hpp"

#include <iostream>
#include <vector>

// Framebuffer --for clock
const int frameWidth = 400;
const int frameHeight = 400;

const int displayScale = 1; // display scaled version of framebuffer so you can see the pixels

// // // Framebuffer --e5
// const int frameWidth = 640;
// const int frameHeight = 480;

 //const int displayScale = 1; // display scaled version of framebuffer so you can see the pixels


bool z_buffer_on=false;
std::vector<std::vector<float>> z_buffer(640, std::vector<float>(480,1000000));

SDL_Surface* framebuffer = NULL;

glm::vec4 glouniformcolor;
glm::mat4 glouniformtrans;

bool useglouniformtrans=false;
bool useglouniformcolor=false;

//your resposiblity to telll e5 or not
//perpective-backchodi
bool ise5=false;

// SDL parameters

SDL_Window* window = NULL;
SDL_Surface *windowSurface = NULL;
bool quit = false;

namespace COL781 {
	namespace Software {


		// Forward declarations

		template <> float Attribs::get(int index) const;
		template <> glm::vec2 Attribs::get(int index) const;
		template <> glm::vec3 Attribs::get(int index) const;
		template <> glm::vec4 Attribs::get(int index) const;

		template <> void Attribs::set(int index, float value);
		template <> void Attribs::set(int index, glm::vec2 value);
		template <> void Attribs::set(int index, glm::vec3 value);
		template <> void Attribs::set(int index, glm::vec4 value);

//---------------------to complete the sw.cpp------------------------------------------------------------------


			GLenum glCheckError_(const char *file, int line) {
			GLenum errorCode;
			while ((errorCode = glGetError()) != GL_NO_ERROR) {
				std::string error;
				switch (errorCode) {
				case GL_INVALID_ENUM:
					error = "INVALID_ENUM";
					break;
				case GL_INVALID_VALUE:
					error = "INVALID_VALUE";
					break;
				case GL_INVALID_OPERATION:
					error = "INVALID_OPERATION";
					break;
				case GL_STACK_OVERFLOW:
					error = "STACK_OVERFLOW";
					break;
				case GL_STACK_UNDERFLOW:
					error = "STACK_UNDERFLOW";
					break;
				case GL_OUT_OF_MEMORY:
					error = "OUT_OF_MEMORY";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					error = "INVALID_FRAMEBUFFER_OPERATION";
					break;
				}
				std::cout << error << " | " << file << " (" << line << ")" << std::endl;
			}
			return errorCode;
		}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

		bool Rasterizer::initialize(const std::string &title, int width, int height, int spp) {
			if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
				return false;
			}
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, spp);
			window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
			if (!window) {
				std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
				return false;
			}
			if (!SDL_GL_CreateContext(window)) {
				std::cerr << "Could not create OpenGL context: " << SDL_GetError() << std::endl;
				return false;
			}
			GLenum glewStatus = glewInit();
			if (glewStatus != GLEW_OK) {
				std::cerr << "Could not initialize GLEW: " << glewGetErrorString(glewStatus) << std::endl;
				return false;
			}
			quit = false;

			windowSurface = SDL_GetWindowSurface(window);
            framebuffer = SDL_CreateRGBSurface(0, frameWidth, frameHeight, 32, 0, 0, 0, 0);
			glCheckError();
			return true;
		}

		bool Rasterizer::shouldQuit() {
			//glCheckError();
			return quit;
		}


		ShaderProgram Rasterizer::createShaderProgram(const VertexShader &vs, const FragmentShader &fs) {
			
			//GLuint myprogram= glCreateProgram();
			//ShaderProgram program = glCreateProgram();
			ShaderProgram program ;
			
			program.vs=vs;
			program.fs=fs;

			//glAttachShader(program, vs);
			//glAttachShader(program, fs);
			//glLinkProgram(program);
			
			//GLint linkStatus;
			//glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
			// if (linkStatus != GL_TRUE) {
			// 	std::cout << "Error linking shaders:" << std::endl;
			// 	GLint maxLength = 0;
			// 	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			// 	std::vector<GLchar> infoLog(maxLength);
			// 	glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);
			// 	std::cout << &infoLog[0] << std::endl;
			// 	glDeleteProgram(program);
			// 	glDeleteShader(vs);
			// 	glDeleteShader(fs);
			// 	return 0;
			// }
			//glCheckError();
			return program;
		}


		Object Rasterizer::createObject() {
			Object object;
			//glGenVertexArrays(1, &object.vao);
			//glCheckError();
			return object;
		}



		// void setAttribs(Object &object, int attribIndex, int n, int d, const float* data) {
			
		// 	//GLuint vbo;

		// 	//glm:: vec4 verices = data;

		// 	//std::cout<<data<<std::endl;
		// 	for(int i=0; i<n; i++){
		// 		object.attributeValues[i][0]=data;
		// 	}

		// 	// glGenBuffers(1, &vbo);
		// 	// glBindVertexArray(object.vao);
		// 	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// 	// glBufferData(GL_ARRAY_BUFFER, n*d*sizeof(float), data, GL_STATIC_DRAW);
		// 	// glVertexAttribPointer(attribIndex, d, GL_FLOAT, GL_FALSE, d*sizeof(float), NULL);
		// 	// glEnableVertexAttribArray(attribIndex);
		// 	// glCheckError();
		// }


// template <> void Rasterizer::setVertexAttribs(Object &object, int attribIndex, int n, const float* data) {
// 			setAttribs(object, attribIndex, n, 1, data);
// 		}

// 		template <> void Rasterizer::setVertexAttribs(Object &object, int attribIndex, int n, const float* data) {
// 			setAttribs(object, attribIndex, n, 1, data);
// 		}

// 		template <> void Rasterizer::setVertexAttribs(Object &object, int attribIndex, int n, const glm::vec2* data) {
// 			setAttribs(object, attribIndex, n, 2, (float*)data);
// 		}

// 		template <> void Rasterizer::setVertexAttribs(Object &object, int attribIndex, int n, const glm::vec3* data) {
// 			setAttribs(object, attribIndex, n, 3, (float*)data);
// 		}









		template <> void Rasterizer::setVertexAttribs(Object &object, int attribIndex, int n, const glm::vec4 *data) {
			
			std::vector<float> temp={0,0,0,0};

			object.attributeDims={};
			object.attributeDims.push_back(n);


			if(attribIndex==0){

				object.useuniformcolor=true;

			

				object.attributeValues={};
				for(int i=0; i<n; i++){

					for(int j=0; j<4; j++){
						//std::cout<<data[i][j]<<std::endl;
						temp[j]=data[i][j];
					}
					object.attributeValues.push_back(temp);
				}

			}else{

				useglouniformcolor=false;

				object.color={};
				for(int i=0; i<n; i++){

					for(int j=0; j<4; j++){
						//std::cout<<data[i][j]<<std::endl;
						temp[j]=data[i][j];
					}
					object.color.push_back(temp);
				}


			}
     
	


		}


		


		void Rasterizer::setTriangleIndices(Object &object, int n, glm::ivec3* indices) {
			
			
			object.attributeDims.push_back(n);
			glm::ivec3* love=indices;

			//std::cout<<love[0][0]<<std::endl;
			object.indices={};

			glm::ivec3 temp={0,0,0};

			for(int i=0; i<n; i++){
				
				for(int j=0; j<3; j++){
					//std::cout<<love[i][j]<<std::endl;
					temp[j]=love[i][j];
				}
				object.indices.push_back(temp);
			}
	

			//std::vector<glm::ivec3> indices1 = love;
			//object.indices= indices1;
		// 	GLuint ebo;
		// 	glGenBuffers(1, &ebo);
		// 	glBindVertexArray(object.vao);
		// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*n*sizeof(int), (float*)indices, GL_STATIC_DRAW);
		// 	object.nTris = n;
		// 	glCheckError();
		// 
		}


		    // clear the framebuffer with some color
		void clearFrameBuffer(glm::vec4 color) {        
			// set the pixels in the frambuffer 


			Uint32 *pixels = (Uint32*)framebuffer->pixels;
			SDL_PixelFormat *format = framebuffer->format;        
			Uint32 rgba = SDL_MapRGBA(format, color[0]*255, color[1]*255, color[2]*255, 1);
			for(int i=0; i<frameWidth; i++) {
				for(int j=0; j<frameHeight; j++) {
					pixels[i + frameWidth*j] = rgba; // set new color
				}
			}        
		}

		void Rasterizer::clear(glm::vec4 color) {

			clearFrameBuffer(color);
			//glClearColor(color[0], color[1], color[2], color[3]);
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//glCheckError();
			 // Update screen to apply the changes
            //SDL_BlitScaled(framebuffer, NULL, windowSurface, NULL);
            //SDL_UpdateWindowSurface(window);
		}

		void Rasterizer::useShaderProgram(const ShaderProgram &program) {
			//glUseProgram(program);
			//glCheckError();
		}

		template <> void Rasterizer::setUniform(ShaderProgram &program, const std::string &name, glm::vec4 value) {
		  
			program.uniforms.color[name] = value;
			glouniformcolor=value;	
			useglouniformcolor=true;
		
			
		}
		template <> void Rasterizer::setUniform(ShaderProgram &program, const std::string &name, glm::mat4 value) {
		  
			program.uniforms.trasform[name] = value;	
			glouniformtrans=value;
			useglouniformtrans=true;
			
		}




    // check if framebuffer coordinates (i, j) are inside the triangle  
    bool insideTriangle(glm::vec4 *vertices, float x, float y) {       

        //to go from NDC(ON PAPER COORDINATE) to screen coordinate(pixel position)--conversion                     
        float xa = (vertices[0][0] + 1.0f)*0.5*frameWidth, ya = (1.0f-vertices[0][1])*0.5*frameHeight;
        float xb = (vertices[1][0] + 1.0f)*0.5*frameWidth, yb = (1.0f-vertices[1][1])*0.5*frameHeight;
        float xc = (vertices[2][0] + 1.0f)*0.5*frameWidth, yc = (1.0f-vertices[2][1])*0.5*frameHeight;
        
        // float ab = (ya-yb)*x + (xb-xa)*y + xa*yb - xb*ya;
        // float cab = (ya-yb)*x + (xb-xa)*y + xa*yb - xb*ya;

        float bc = (yb-yc)*x + (xc-xb)*y + xb*yc - xc*yb;
        float abc = (yb-yc)*xa + (xc-xb)*ya + xb*yc - xc*yb;
        
        float ca = (yc-ya)*x + (xa-xc)*y + xc*ya - xa*yc;
        float bca = (yc-ya)*xb + (xa-xc)*yb + xc*ya - xa*yc;

        float alpha = bc/abc, beta = ca/bca, gamma = 1-alpha-beta;                
        return alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1;
    }


	    // check if framebuffer coordinates (i, j) are inside the triangle  
    std::vector<float> insideTriangle1(glm::vec4 *vertices, float x, float y) {       

        //to go from NDC(ON PAPER COORDINATE) to screen coordinate(pixel position)--conversion                     
        float xa = (vertices[0][0] + 1.0f)*0.5*frameWidth, ya = (1.0f-vertices[0][1])*0.5*frameHeight;
        float xb = (vertices[1][0] + 1.0f)*0.5*frameWidth, yb = (1.0f-vertices[1][1])*0.5*frameHeight;
        float xc = (vertices[2][0] + 1.0f)*0.5*frameWidth, yc = (1.0f-vertices[2][1])*0.5*frameHeight;
        
        // float ab = (ya-yb)*x + (xb-xa)*y + xa*yb - xb*ya;
        // float cab = (ya-yb)*x + (xb-xa)*y + xa*yb - xb*ya;

        float bc = (yb-yc)*x + (xc-xb)*y + xb*yc - xc*yb;
        float abc = (yb-yc)*xa + (xc-xb)*ya + xb*yc - xc*yb;
        
        float ca = (yc-ya)*x + (xa-xc)*y + xc*ya - xa*yc;
        float bca = (yc-ya)*xb + (xa-xc)*yb + xc*ya - xa*yc;

        float alpha = bc/abc, beta = ca/bca, gamma = 1-alpha-beta;                
        if(alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1){
			return {alpha, beta, gamma};
		}

		return {};
    }

		    // rasterize single triangle onto framebuffer from NDC
    // assuming coordinates are in anticlockwise order
    //brute force method to  resterize triangle
    //part1-1
    void rasterizeSingleTriangle(glm::vec4 *vertices, glm::vec4 color , glm::vec4 *tempcolor ) {        
        Uint32 *pixels = (Uint32*)framebuffer->pixels;
        SDL_PixelFormat *format = framebuffer->format;

		color=glouniformcolor;

        Uint32 triangleColor = SDL_MapRGBA(format, color[0]*255, color[1]*255, color[2]*255, 1);
        Uint32 bgColor  = SDL_MapRGBA(format, 255, 255, 255, 1); 

		//std::cout<<useuniformcolor<<std::endl;
		std::vector<float> interpole;   

        float x,y;    
        for(int i=0; i<frameWidth; i++) {
            for(int j=0; j<frameHeight; j++) {        
            
				
                x=i+0.5;
                y=j+0.5;

                if(insideTriangle(vertices,x,y)){

					interpole=insideTriangle1(vertices,x,y);
					float height_of_sample= vertices[0][2]*interpole[0]+vertices[1][2]*interpole[1]+vertices[2][2]*interpole[2];

					if(useglouniformcolor==false){

						
						 float r=tempcolor[0][0]*interpole[0] + tempcolor[1][0]*interpole[1] +tempcolor[2][0]*interpole[2];
						 float g=tempcolor[0][1]*interpole[0] + tempcolor[1][1]*interpole[1] +tempcolor[2][1]*interpole[2];
						 float b=tempcolor[0][2]*interpole[0] + tempcolor[1][2]*interpole[1] +tempcolor[2][2]*interpole[2];

						//  float r=(tempcolor[0][0]*interpole[0])*vertices[0][2] + (tempcolor[1][0]*interpole[1])*vertices[1][2] +(tempcolor[2][0]*interpole[2])*vertices[2][2];
						//  float g=(tempcolor[0][1]*interpole[0])*vertices[0][2] + (tempcolor[1][1]*interpole[1])*vertices[1][2] +(tempcolor[2][1]*interpole[2])*vertices[2][2];
						//  float b=(tempcolor[0][2]*interpole[0])*vertices[0][2] + (tempcolor[1][2]*interpole[1])*vertices[1][2] +(tempcolor[2][2]*interpole[2])*vertices[2][2];


						if(ise5){
							//e5
							r=(tempcolor[0][0]*interpole[0])*(1/vertices[0][2]) + (tempcolor[1][0]*interpole[1])*(1/vertices[1][2]) +(tempcolor[2][0]*interpole[2])*(1/vertices[2][2]);
							g=(tempcolor[0][1]*interpole[0])*(1/vertices[0][2]) + (tempcolor[1][1]*interpole[1])*(1/vertices[1][2]) +(tempcolor[2][1]*interpole[2])*(1/vertices[2][2]);
							b=(tempcolor[0][2]*interpole[0])*(1/vertices[0][2]) + (tempcolor[1][2]*interpole[1])*(1/vertices[1][2]) +(tempcolor[2][2]*interpole[2])*(1/vertices[2][2]);

							
							//1/z interpolation
							float z=1/((1/vertices[0][2])*interpole[0] +(1/vertices[1][2])*interpole[1] + (1/vertices[2][2])*interpole[2]);

							r=r*z;
							g=g*z;
							b=b*z;
						}

						

						triangleColor= SDL_MapRGBA(format,r*255,g*255,b*255,1);
					}

					if( z_buffer_on==true ){
						
						if(z_buffer[i][j]>height_of_sample){
						
                   			 pixels[i + j*frameWidth]=triangleColor;
							 z_buffer[i][j]=height_of_sample;
						}
					}else{

						pixels[i + j*frameWidth]=triangleColor;
					}
					
                }
                        
                
            }
        }        
    }
    
    //part1-2
    void rasterizeMultipleTriangle(glm::vec4 *vertices, glm::vec4 color, glm::vec4 *mycolor , glm::ivec3 *indices, int noofindices) {        
       
         int a,b,c;
          glm::vec4 tempvertices[]={ glm::vec4(-0.4, -0.8, 0.0, 1.0),
         glm::vec4( 0.8,  0.8, 0.0, 1.0),
        glm::vec4(-0.4, -0.4, 0.0, 1.0)};
        //int noofindices=sizeof(indices)/4;

		glm::vec4 tempcolor[]={

				glm::vec4(-0.8,  0.0, 0.0, 1.0),
			glm::vec4(-0.4, -0.8, 0.0, 1.0),
			glm::vec4( 0.8,  0.8, 0.0, 1.0)
		};


       // std::cout<<noofindices<<std::endl;
        for(int i=0; i<noofindices; i++){

            a=indices[i][0];
            b=indices[i][1];
            c=indices[i][2];

            tempvertices[0]=vertices[a];
            tempvertices[1]=vertices[b];
            tempvertices[2]=vertices[c];

			tempcolor[0]=mycolor[a];

			tempcolor[1]=mycolor[b];

			tempcolor[2]=mycolor[c];
			


            rasterizeSingleTriangle(tempvertices, color,tempcolor);
           
        }


    }

	  void drawrectangle(int x, int y, int width, int height){

        int x1=x;
        int x2=x+width;
        int y1=y;
        int y2= y+height;

        glm::vec4 color(0.00, 0.00, 0.00, 1.0);

        Uint32 *pixels = (Uint32*)framebuffer->pixels;
        SDL_PixelFormat *format = framebuffer->format;
        Uint32 triangleColor = SDL_MapRGBA(format, color[0]*255, color[1]*255, color[2]*255, 1);
        

        for(int i=x1; i<=x2; i++){

            for(int j=y1; j<=y2; j++){
                pixels[i + j*frameWidth]=triangleColor;
            }
        }


    }

    void drawclock(){

        //12
        drawrectangle(190,10,5,20);
        drawrectangle(210,10,5,20);
        drawrectangle(205,10,5,5);
        drawrectangle(215,25,5,5);


        //3
        drawrectangle(0+380,0+180,10,5);
        drawrectangle(0+380,10+180,10,5);
        drawrectangle(0+380,20+180,10,5);
        drawrectangle(10+380,0+180,5,25);

        //6
        drawrectangle(370-180,185+180,5,25);
        drawrectangle(370-180,205+180,10,5);
        drawrectangle(380-180,195+180,5,15);
        drawrectangle(370-180,195+180,10,5);

        
        //9
        drawrectangle(0+10,0+180,5,15);
        drawrectangle(5+10,0+180,10,5);
        drawrectangle(5+10,10+180,10,5);
        drawrectangle(15+10,0+180,5,25);

    }


		void Rasterizer::drawObject(const Object &object) {

		glm::vec4 vertices[] = {
		glm::vec4(-0.8,  0.0, 0.0, 1.0),
        glm::vec4(-0.4, -0.8, 0.0, 1.0),
        glm::vec4( 0.8,  0.8, 0.0, 1.0),
        glm::vec4(-0.4, -0.4, 0.0, 1.0)
    };

			glm::vec4 tempvertices[] = {
		glm::vec4(-0.8,  0.0, 0.0, 1.0),
        glm::vec4(-0.4, -0.8, 0.0, 1.0),
        glm::vec4( 0.8,  0.8, 0.0, 1.0),
        glm::vec4(-0.4, -0.4, 0.0, 1.0)
    };


	glm::ivec3 indices[] = {
		glm::ivec3(0, 1, 3),
		glm::ivec3(1, 2, 3)
	};


	 glm::vec4 mycolor[]={	
		
		glm::vec4(-0.8,  0.0, 0.0, 1.0),
        glm::vec4(-0.4, -0.8, 0.0, 1.0),
        glm::vec4( 0.8,  0.8, 0.0, 1.0),
        glm::vec4(-0.4, -0.4, 0.0, 1.0)
		
		};


		// 	glm::vec4 tempmycolor[]={	
		
		// glm::vec4(-0.8,  0.0, 0.0, 1.0),
        // glm::vec4(-0.4, -0.8, 0.0, 1.0),
        // glm::vec4( 0.8,  0.8, 0.0, 1.0),
        // glm::vec4(-0.4, -0.4, 0.0, 1.0)
		
		// };
			
				

		
		   //std::cout<<"hi riya i love u"<<std::endl;
		  
		   
		   int n=object.attributeDims[0];
		   int m=object.attributeDims[1];

		   //std::cout<<n<<" "<<m<<std::endl;

			
		 	// glm::vec4 vertices[n]={};
			// glm::vec4 tempvertices[n]={};
			// glm::ivec3 indices[m]={};
			// glm::vec4 mycolor[n]={};
			
		


				
			for(int i=0; i<n; i++){

				for(int j=0; j<4; j++){
					//std::cout<<data[i][j]<<std::endl;
					vertices[i][j]=object.attributeValues[i][j];
				}
				
			}

			

				
			for(int i=0; i<m; i++){

				for(int j=0; j<3; j++){
					//std::cout<<data[i][j]<<std::endl;
					indices[i][j]=object.indices[i][j];
				}
				
			}

			//bool useuniformcolor=true;


			if(useglouniformcolor==false){

			   for(int i=0; i<n; i++){

				   for(int j=0; j<4; j++){
					//std::cout<<data[i][j]<<std::endl;
					  mycolor[i][j]=object.color[i][j];
				}
				
				}

				//useuniformcolor=false;
			}
						

			glm::vec4 color={0.0, 0.6, 0.0, 1.0};


			

			if(useglouniformtrans==true){

				for(int i=0; i<4; i++){
					for(int j=0; j<4; j++){
						glouniformtrans[i][j]= 0.5*glouniformtrans[i][j];
					}
				}

				for(int i=0; i<4; i++){

					tempvertices[i]=glouniformtrans*vertices[i];
					
				}
				

				//if e5 is true we will do perspective backchodi
				if(ise5==true){
					for(int i=0; i<4; i++){
						tempvertices[i][0]= tempvertices[i][0]/tempvertices[i][2];
						tempvertices[i][1]= tempvertices[i][1]/tempvertices[i][2];
					}

				}

			 rasterizeMultipleTriangle(tempvertices,color, mycolor, indices, m);
			}else{

				
			 rasterizeMultipleTriangle(vertices,color, mycolor, indices, m);
			}
		    

			


				// glBindVertexArray(object.vao);
				// glDrawElements(GL_TRIANGLES, 3*object.nTris, GL_UNSIGNED_INT, 0);
				// glCheckError();
		
		
		}





		//call this function after updating framebuffer to apply changes to screen
		void updateScreen() { 
			SDL_BlitScaled(framebuffer, NULL, windowSurface, NULL);
			SDL_UpdateWindowSurface(window);
		}

		void Rasterizer::show() {

			//uncomment this for part2-ii -clock
			drawclock();
			//for clokc change frame to 400 x 400

            SDL_BlitScaled(framebuffer, NULL, windowSurface, NULL);
			SDL_UpdateWindowSurface(window);


			z_buffer=std::vector<std::vector<float>>(frameWidth, std::vector<float>(frameHeight,100000));

			 //SDL_GL_SwapWindow(window);
			 SDL_Event e;
			 while (SDL_PollEvent(&e) != 0) {
			 	if(e.type == SDL_QUIT) {
			 		quit = true;
			 	}
			 }

			//glCheckError();

		}

		    //handle events 
		void handleEvents() {        
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}
		}


		
		void terminate() {
			// Free resources and close SDL
			SDL_FreeSurface(framebuffer);
			SDL_DestroyWindow(window);
			SDL_Quit();
    	}
		void Rasterizer::deleteShaderProgram(ShaderProgram &program) {

			terminate();
			// glDeleteProgram(program);
			// glCheckError();
		}

		void Rasterizer::enableDepthTest() {
			
			z_buffer_on=true;
		
			//glEnable(GL_DEPTH_TEST);
		    //glDepthFunc(GL_LESS);   
			//glCheckError();
		}

		VertexShader Rasterizer::vsColorTransform() {
		
				"#version 330 core\n"
				"layout(location = 0) in vec4 vertex;\n"
				"layout(location = 1) in vec4 vColor;\n"
				"uniform mat4 transform;\n"
				"out vec4 color;\n"
				"void main() {\n"
				"	gl_Position = transform * vertex;\n"
				"	color = vColor;\n"
				"}\n";
			return vsIdentity();
		}

//---------to be added by me----------------------------------------------------------------------------------

		// Built-in shaders

		VertexShader Rasterizer::vsIdentity() {
			return [](const Uniforms &uniforms, const Attribs &in, Attribs &out) {
				glm::vec4 vertex = in.get<glm::vec4>(0);
				return vertex;
			};
		}

		VertexShader Rasterizer::vsTransform() {
			return [](const Uniforms &uniforms, const Attribs &in, Attribs &out) {
				glm::vec4 vertex = in.get<glm::vec4>(0);
				glm::mat4 transform = uniforms.get<glm::mat4>("transform");
				return transform * vertex;
			};
		}

		VertexShader Rasterizer::vsColor() {
			return [](const Uniforms &uniforms, const Attribs &in, Attribs &out) {
				glm::vec4 vertex = in.get<glm::vec4>(0);
				glm::vec4 color = in.get<glm::vec4>(1);
				out.set<glm::vec4>(0, color);
				return vertex;
			};
		}

		FragmentShader Rasterizer::fsConstant() {
			return [](const Uniforms &uniforms, const Attribs &in) {
				glm::vec4 color = uniforms.get<glm::vec4>("color");
				return color;
			};
		}

		FragmentShader Rasterizer::fsIdentity() {
			return [](const Uniforms &uniforms, const Attribs &in) {
				glm::vec4 color = in.get<glm::vec4>(0);
				return color;
			};
		}

		// Implementation of Attribs and Uniforms classes

		void checkDimension(int index, int actual, int requested) {
			if (actual != requested) {
				std::cout << "Warning: attribute " << index << " has dimension " << actual << " but accessed as dimension " << requested << std::endl;
			}
		}

		template <> float Attribs::get(int index) const {
			checkDimension(index, dims[index], 1);
			return values[index].x;
		}

		template <> glm::vec2 Attribs::get(int index) const {
			checkDimension(index, dims[index], 2);
			return glm::vec2(values[index].x, values[index].y);
		}

		template <> glm::vec3 Attribs::get(int index) const {
			checkDimension(index, dims[index], 3);
			return glm::vec3(values[index].x, values[index].y, values[index].z);
		}

		template <> glm::vec4 Attribs::get(int index) const {
			checkDimension(index, dims[index], 4);
			return values[index];
		}

		void expand(std::vector<int> &dims, std::vector<glm::vec4> &values, int index) {
			if (dims.size() < index+1)
				dims.resize(index+1);
			if (values.size() < index+1)
				values.resize(index+1);
		}

		template <> void Attribs::set(int index, float value) {
			expand(dims, values, index);
			dims[index] = 1;
			values[index].x = value;
		}

		template <> void Attribs::set(int index, glm::vec2 value) {
			expand(dims, values, index);
			dims[index] = 2;
			values[index].x = value.x;
			values[index].y = value.y;
		}

		template <> void Attribs::set(int index, glm::vec3 value) {
			expand(dims, values, index);
			dims[index] = 3;
			values[index].x = value.x;
			values[index].y = value.y;
			values[index].z = value.z;
		}

		template <> void Attribs::set(int index, glm::vec4 value) {
			expand(dims, values, index);
			dims[index] = 4;
			values[index] = value;
		}

		template <typename T> T Uniforms::get(const std::string &name) const {
			return *(T*)values.at(name);
		}

		template <typename T> void Uniforms::set(const std::string &name, T value) {
			auto it = values.find(name);
			if (it != values.end()) {
				delete it->second;
			}
			values[name] = (void*)(new T(value));
		}

	}
}
