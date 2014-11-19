#include "tree.h"
#include "node.h"
#include <stdlib.h> 
#include <time.h>

#define MAGIC_CONST 1

char VertexShaderName[] = "Vertex.vert";
char FragmentShaderName[] = "Fragment.frag";

void Tree::init() {
	srand(MAGIC_CONST);
	root = new Node(this, -1, MAX_STEP, false, ROOT_TRANS_X, ROOT_TRANS_Y, ROOT_TRANS_Z);
	
	useTexture = true;
	phi = theta = 0;
	radius = 10;

	eye = glm::vec3(0, 0, radius);
	cen = glm::vec3(0, 0, 0);
	up =  glm::vec3(0, 1, 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	//initialize shader program
	shaderProgram.init(VertexShaderName,FragmentShaderName);
	//use this shader program
	glUseProgram(shaderProgram.programObject);

	//create new branch
	pBranch = new Branch();
	//fill in data
	pBranch->initData();

	//initialize opengl buffers and variables inside of object
	pBranch->initGLBuffers(shaderProgram.programObject,"pos","nor","tex");
	//create new leaf
	pLeaf = new Leaf();
	//fill in data
	pLeaf->initData();
	//initialize opengl buffers and variables inside of object
	pLeaf->initGLBuffers(shaderProgram.programObject,"pos","nor","tex");
	initTexture();
}

void Tree::initTexture()
{
    //generate as many textures as you need
	glGenTextures(1,&texId[0]);
	
    //enable texturing and zero slot
	glActiveTexture(GL_TEXTURE0);
    //bind texId to 0 unit
	glBindTexture(GL_TEXTURE_2D,texId[0]);

	//don't use alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	// Set nearest filtering mode for texture minification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//TODO: load texture from file 
	GLubyte imgData[2*2*3] = {
		//row1: yellow,orange
		255,255,0, 255,128,0,
		//row2: green, dark green
		0,255,0, 0,64,0
	};  

	//set Texture Data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2,2, 0, GL_RGB, GL_UNSIGNED_BYTE, &imgData[0]);
}

void Tree::drawNode(Node &node) {

  //Draw triangle with shaders (in screen coordinates)
  //need to set uniform in modelViewMatrix

	glUseProgram(shaderProgram.programObject);

  //we will need this uniform locations to connect them to our variables
	int locMV = glGetUniformLocation(shaderProgram.programObject,"modelViewMatrix");
	int locN = glGetUniformLocation(shaderProgram.programObject,"normalMatrix");
	int locP = glGetUniformLocation(shaderProgram.programObject,"modelViewProjectionMatrix");
	int texLoc = glGetUniformLocation(shaderProgram.programObject,"textureSampler");
	int locFlag = glGetUniformLocation(shaderProgram.programObject,"useTexture");
  //if there is some problem
	if (locMV<0 || locN<0 || locP<0 || texLoc <0 || locFlag<0)
	{
	  //not all uniforms were allocated - show blue screen.
	  //check your variables properly. May be there is unused?
		glClearColor(0,0,1,1);
		glClear(GL_COLOR_BUFFER_BIT);
	  //end frame visualization
		glutSwapBuffers();
		return;
	}

	glm::mat4x4 viewMatrix = glm::lookAt(eye,cen,up);

	glm::mat4x4 modelViewMatrix;
	glm::mat4x4 modelViewProjectionMatrix;
	glm::mat4x4 normalMatrix;

	glm::mat4x4 modelMatrix = glm::mat4();

	modelMatrix = glm::translate(modelMatrix,glm::vec3(node.x, node.y, node.z));
 	modelMatrix = glm::rotate(modelMatrix, node.phi, glm::vec3(0.0f, 0.0f, 1.0f));
 	modelMatrix = glm::rotate(modelMatrix, node.theta, glm::vec3(1.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix,glm::vec3(node.scale_x, node.scale_y, node.scale_z));


  //modelViewMatrix consists of viewMatrix and modelMatrix
	modelViewMatrix = viewMatrix*modelMatrix;
  //calculate normal matrix 
	normalMatrix = glm::inverseTranspose(modelViewMatrix);
  //finally calculate modelViewProjectionMatrix
	modelViewProjectionMatrix = projectionMatrix*modelViewMatrix;

  //bind texture
	glBindTexture(GL_TEXTURE_2D,texId[0]);

  //pass variables to the shaders
	glUniformMatrix4fv(locMV,1,0,glm::value_ptr(modelViewMatrix));
	glUniformMatrix4fv(locN,1,0,glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(locP,1,0,glm::value_ptr(modelViewProjectionMatrix));
	glUniform1ui(texLoc,0);
	glUniform1i(locFlag,useTexture);

	if (node.isLeaf) {
		pLeaf->draw();
	}
	else {
		pBranch->draw();
	}
}

void Tree::reshape(int width, int height)
{
  windowWidth = width;
  windowHeight = height;
  //set viewport to match window size
  glViewport(0, 0, width, height);
  
  float fieldOfView = 45.0f;
  float aspectRatio = float(width)/float(height);
  float zNear = 0.1f;
  float zFar = 100.0f;
  //set projection matrix
  projectionMatrix = glm::perspective(fieldOfView,aspectRatio,zNear,zFar);
}