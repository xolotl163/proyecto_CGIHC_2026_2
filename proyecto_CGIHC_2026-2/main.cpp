/*----------------------------------------------------------------------------------------------------------*/
/*---------------- Proyecto Computación Grafica e Interaccion Humano computadora  --------------------------*/
/*---------------- Integrantes del equipo:                                        --------------------------*/
/*---------------- Chavez madrid Ismael Angel                                     --------------------------*/
/*---------------- Hernández Jiménez Efrén Antonio                                --------------------------*/
/*---------------- Garcia Cardenas Fabian                                         --------------------------*/
/*---------------- Padilla Cazares Jesus Alejandro                                --------------------------*/
/*------------------------------------------- 2026-2 -------------------------------------------------------*/

// Librarys and headers
#include <Windows.h>
#include <glad/glad.h>
#include <glfw3.h>						//main
#include <stdlib.h>		
#include <glm/glm.hpp>					//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>					//Texture
#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>
#include <mmsystem.h>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <vector>
#include <algorithm>
#include <numeric>

//definciones
#define PI 3.1415926

//Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

/* handmade prototype functions */


// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor* monitors;

//Buffers
GLuint VBO[3], VAO[3], EBO[3];

//Camera
Camera camera(glm::vec3(0.0f, 200.0f, 300.0f));
float MovementSpeed = 100.0f;
GLfloat lastX = SCR_WIDTH / 2.0f,
		lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//Timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//seccion 1
void getResolution(void);
void myData(void);	// De la practica 4
void LoadTextures(void); // De la práctica 6
unsigned int generateTextures(char*, bool, bool); // De la práctica 6

//For Keyboard
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rotX = 0.0f;

//Texture
unsigned int t_smile;
unsigned int t_toalla;
unsigned int t_unam;
unsigned int t_white;
unsigned int t_ladrillos;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

//// Light
glm::vec3 lightColor = glm::vec3(0.7f);
glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);

// posiciones
float	movAuto_x = 0.0f,
movAuto_z = 0.0f,
orienta = 90.0f;
bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false;

//otros datos para  otras animaciones
glm::vec3 circleCenter = glm::vec3(-550.0f, 0.0f, 100.0f);
float circleRadius = 100.0f;
float leoRadiusAdvance = 0.0f;
float limitA = (1.0f / 2.0f) * PI;
float limitB = (3.0f / 2.0f) * PI;
bool inMovementLeo = false;

//positions for the animated models
glm::vec3 initialPos = glm::vec3(-535.0f, 0.0f, 140.0f);
glm::vec3 angryPos = glm::vec3(-680.0f, 0.0f, -285.0f);
glm::vec3 pointingPos = glm::vec3(0.0f, 20.0f, 400.0f);
glm::vec3 talkingAdamPos = glm::vec3(-350.0f, 20.0f, 350.0f);
glm::vec3 talkingBoyPos = glm::vec3(-350.0f, 20.0f, 300.0f);
glm::vec3 talkingPhoneBoyPos = glm::vec3(-800.0f, 0.0f, -235.0f);
glm::vec3 talkingPhoneGirlPos = glm::vec3(-750.0f, 0.0f, 400.0f);
glm::vec3 walkingBrianPos = glm::vec3(-400.0f, 0.0f, 170.0f);
glm::vec3 walkingBrian00Pos = glm::vec3(400.0f, 0.0f, 450.0f);
glm::vec3 walkingKatePos = glm::vec3(-650.0f, 0.0f, -400.0f);
glm::vec3 walkingKate00Pos = glm::vec3(300.0f, 0.0f, -400.0f);
glm::vec3 walkingKate01Pos = glm::vec3(75.0f, 20.0f, 350.0f);
glm::vec3 startingPointLeonardPos = glm::vec3(-1000.0f, 20.0f, 100.0f);
glm::vec3 walkingLeonardPos = startingPointLeonardPos;
glm::vec3 walkingLeoPos = glm::vec3( circleCenter.x, circleCenter.y, circleCenter.z + (-1*circleRadius));
glm::vec3 orignaLeoPos = walkingLeoPos;
glm::vec3 walkingLeo00Pos = glm::vec3(-200.0f, 0.0f, -200.0);

//escala spara los modelos animados
glm::vec3 sittingLouiseScale = glm::vec3(1.4f);
glm::vec3 talkingEveScale = glm::vec3(1.7f);
glm::vec3 talkingWorkerScale = glm::vec3(1.4f);
glm::vec3 angryScale = glm::vec3(1.45f);
glm::vec3 pointingScale = glm::vec3(0.65f);
glm::vec3 talkingAdamScale = glm::vec3(1.4f);
glm::vec3 talkingBoyScale = glm::vec3(1.4f);
glm::vec3 talkingPhoneBoyScale = glm::vec3(1.4f);
glm::vec3 talkingPhoneGirlScale = glm::vec3(1.4f);
glm::vec3 walkingBrianScale = glm::vec3(1.4f);
glm::vec3 walkingKateScale = glm::vec3(1.4f);
glm::vec3 walkingLeonardScale = glm::vec3(1.4f);

//rotaciones para los modelos animados
float angryRot00 = rand() % 360;
float angryRot01 = rand() % 360;
float angryRot02 = rand() % 360;
float walkingBrianRot = rand() % 360;
float walkingLeonardRot = 90.0f;
float startingWalkingLeonardRot = 90.0f;
float walkingLeoRot = -90.0f;
float currentLeoRot = glm::radians(walkingLeoRot);

//estados para las animciones de caminar
int walkingBrian_currentState = 0;
int walkingBrian00_currentState = 0;
int walkingKate_currentState = 0;
int walkingKate00_currentState = 0;
int walkingKate01_currentState = 0;
int walkingLeonard_currentState = 0;
int walkingLeo_currentState = 0;
int walkingLeo00_currentState = 0;

//datos para las animaciones de los perosnajes
float currentStateTime_walkingBrian = 0.0f;
float currentStateTime_walkingKate = 0.0f;
float currentStateTime_walkingKate00 = 0.0f;
float currentStateTime_walkingKate01 = 0.0f;
float currentStateTime_walkingLeo = 0.0f;
float currentStateTime_walkingLeo00 = 0.0f;
float currentStateTime_walkingBrian00 = 0.0f;
float new_x = 0.0f;
float new_z = 0.0f;
float theta = limitA;

/* Keyframes(Manipulación y dibujo) _> inicia */
float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f,
		rotRodIzq = 0.0f,
		giroMonito = 0.0f;

float	incX = 0.0f,
		incY = 0.0f,
		incZ = 0.0f,
		rotRodIzqInc = 0.0f,
		giroMonitoInc = 0.0f;

#define MAX_FRAMES 9
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float giroMonito;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir número en caso de tener Key guardados
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotRodIzqInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}
/* Keyframes(Manipulación y dibujo) -> termina */

/* Para cargag de texturas -> inicia */

//this function load a texture from a file and generate an OpenGL texture object, returning the ID of the texture
unsigned int generateTextures(const char* filename, bool alfa, bool isPrimitive)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	
	if(isPrimitive)
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	else
		stbi_set_flip_vertically_on_load(false); // tell stb_image.h to flip loaded texture's on the y-axis.


	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

// This function load all the textures we are going to use 
// and save their ID in a variable to use them later when drawing
void LoadTextures()
{

	t_smile = generateTextures("Texturas/awesomeface.png", 1, true);
	t_toalla = generateTextures("Texturas/toalla.tga", 0, true);
	t_unam = generateTextures("Texturas/escudo_unam.jpg", 0, true);
	t_ladrillos = generateTextures("Texturas/bricks.jpg", 0, true);
	//This must be the last
	t_white = generateTextures("Texturas/white.jpg", 0, false);
}
/* Para cargag de texturas -> inicia */

/* Animación por keyframes (funciones) -> inicia */
void animate(void) 
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotRodIzq += rotRodIzqInc;
			giroMonito += giroMonitoInc;

			i_curr_steps++;
		}
	}

	//Vehículo
	if (animacion)
	{
		movAuto_x += 3.0f;
	}
}
/* Animación por keyframes (funciones) -> termina */

//función suelta -> solamente obtiene la resolución de la pantalla para crear la ventana a esa medida
void getResolution() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

//datos
void myData() {

	//datos para dibujar un cuadrado con textura, se pueden modificar para crear otras figuras
	float vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	float verticesPiso[] = {
		// positions          // texture coords
		 10.5f,  10.5f, 0.0f,   4.0f, 4.0f, // top right
		 10.5f, -10.5f, 0.0f,   4.0f, 0.0f, // bottom right
		-10.5f, -10.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-10.5f,  10.5f, 0.0f,   0.0f, 4.0f  // top left 
	};
	unsigned int indicesPiso[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(3, VAO);
	glGenBuffers(3, VBO);
	glGenBuffers(3, EBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para Piso
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPiso), verticesPiso, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesPiso), indicesPiso, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int main() {

	srand(time(NULL)); // Inicializa la semilla para la generación de números aleatorios

	// glfw: initialize and configure
	glfwInit();

	// glfw window creation
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	//creación de la ventana, se le asigna el título del proyecto
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Proyecto CGIHC 2026-2", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//inicialización de la ventana, se asigna el contexto, se asignan las funciones de callback para el mouse, el scroll y el teclado
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*configure global opengl state*/
	
	//Se utilizan las funciones creadas para cargar las texturas y los datos de los vértices
	// se habilita el depth test para que se dibujen correctamente los objetos en 3D
	LoadTextures();
	myData();
	glEnable(GL_DEPTH_TEST);

	//se construyen y se compilan los shaders, se asignan a variables para usarlos después
	//los shaders iniciales son para dibujar primitivas, modelos estáticos, el skybox y modelos animados respectivamente
	// por lo que primero se cargan y se toman de forma general para después asignar cada uno a su función correspondiente
	Shader myShader("shaders/shader_texture_color.vs", "shaders/shader_texture_color.fs"); //To use with primitives
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights_mod.fs");	//To use with static models
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");	//To use with skybox
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");	//To use with animated models 
	
	//creación de skybox, se le asignan las texturas correspondientes a cada cara del cubo
	vector<std::string> faces{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};
	Skybox skybox = Skybox(faces);

	// Skybox Shader configuration 
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	/*Creation and Load of models for the scene, the parameters are the path to the.obj file of each model */
	Model piso("resources/objects/piso/piso.obj");
	
	//modelos estaticos
	Model suelo("resources/objects/static models/banqueta/banqueta.obj");
	Model techo("resources/objects/static models/banqueta/techo.obj");
	Model techo01("resources/objects/static models/banqueta/techo.obj");
	Model techo02("resources/objects/static models/banqueta/techo.obj");
	Model outside_suelo("resources/objects/static models/banqueta/outside_banqueta.obj");
	Model columna_circulo("resources/objects/static models/columna_circulo/columna_circulo.obj");
	Model columna_circulo00("resources/objects/static models/columna_circulo/columna_circulo.obj");
	Model columna_circulo01("resources/objects/static models/columna_circulo/columna_circulo.obj");
	Model columna_circulo02("resources/objects/static models/columna_circulo/columna_circulo.obj");
	Model columna_circulo03("resources/objects/static models/columna_circulo/columna_circulo.obj");
	Model columna_ovalo("resources/objects/static models/columna_ovalo/columna_ovalo.obj");
	Model columna_ovalo01("resources/objects/static models/columna_ovalo/columna_ovalo.obj");
	Model columna_ovalo02("resources/objects/static models/columna_ovalo/columna_ovalo.obj");
	Model columna_ovalo03("resources/objects/static models/columna_ovalo/columna_ovalo.obj");
	Model columna_ovalo04("resources/objects/static models/columna_ovalo/columna_ovalo.obj");
	Model columna_ovalo05("resources/objects/static models/columna_ovalo/columna_ovalo.obj");
	Model banca("resources/objects/static models/Bench/Bench_4.obj");
	Model banca00("resources/objects/static models/Bench/Bench_4.obj");
	Model banca01("resources/objects/static models/Bench/Bench_4.obj");
	Model banca02("resources/objects/static models/Bench/Bench_4.obj");
	Model banca03("resources/objects/static models/Bench/Bench_4.obj");
	Model banca04("resources/objects/static models/Bench/Bench_4.obj");
	Model banca05("resources/objects/static models/Bench/Bench_4.obj");
	Model escaleras("resources/objects/static models/stairs/escaleras_002.obj");
	Model lampara("resources/objects/static models/street_lamp/objLamp.obj");
	Model banqueta00("resources/objects/static models/banqueta/banqueta00.obj"); //sostiene las escaleras
	Model banqueta01("resources/objects/static models/banqueta/banqueta00.obj"); //suelo del lado derecho del escenario
	Model banqueta02("resources/objects/static models/banqueta/banqueta00.obj"); //suelo del lado derecho del escenario
	Model reja("resources/objects/static models/reja/reja.obj");
	Model reja00("resources/objects/static models/reja/reja.obj");
	Model reja01("resources/objects/static models/reja/reja.obj");
	Model reja02("resources/objects/static models/reja/reja.obj");
	Model reja03("resources/objects/static models/reja/reja.obj");
	Model reja04("resources/objects/static models/reja/reja.obj");
	Model reja05("resources/objects/static models/reja/reja.obj");
	Model reja06("resources/objects/static models/reja/reja.obj");
	Model reja07("resources/objects/static models/reja/reja.obj");
	Model reja08("resources/objects/static models/reja/reja.obj");
	Model reja09("resources/objects/static models/reja/reja.obj");
	Model reja10("resources/objects/static models/reja/reja.obj");
	Model reja11("resources/objects/static models/reja/reja.obj");
	Model muro00("resources/objects/static models/banqueta/wall.obj");
	Model muro01("resources/objects/static models/banqueta/wall.obj");
	Model muro02("resources/objects/static models/banqueta/wall.obj");
	Model muro03("resources/objects/static models/banqueta/wall.obj");
	Model muro04("resources/objects/static models/banqueta/wall.obj");
	Model muro05("resources/objects/static models/banqueta/wall.obj");
	Model muro06("resources/objects/static models/banqueta/wall.obj");
	Model ventana("resources/objects/static models/ventana/ventana.obj");
	Model ventana00("resources/objects/static models/ventana/ventana.obj");
	Model ventana01("resources/objects/static models/ventana/ventana.obj");
	Model ventana02("resources/objects/static models/ventana/ventana.obj");
	Model stand01("resources/objects/static models/stand01/stand00.obj");

	//modelos animados
	ModelAnim personaje01("resources/objects/Personaje1/Arm.dae");
	personaje01.initShaders(animShader.ID);

	ModelAnim angry("resources/objects/animated models/Angry/Angry00.dae");
	angry.initShaders(animShader.ID);

	ModelAnim pointing("resources/objects/animated models/Pointing Remy/Pointing00.dae");
	pointing.initShaders(animShader.ID);
	
	ModelAnim sittingLouise("resources/objects/animated models/Sitting Louise/Sitting00.dae");
	sittingLouise.initShaders(animShader.ID);
	
	ModelAnim talkingAdam("resources/objects/animated models/Talking Adam/Talking00.dae");
	talkingAdam.initShaders(animShader.ID);

	ModelAnim talkingEve("resources/objects/animated models/Talking Eve/Talking00.dae");
	talkingEve.initShaders(animShader.ID);

	ModelAnim talkingBoy("resources/objects/animated models/TalkingBoy/Talking00.dae");
	talkingBoy.initShaders(animShader.ID);
	
	ModelAnim talkingPhoneBoy("resources/objects/animated models/TalkingPhoneBoy/TalkingPhoneBoy.dae");
	talkingPhoneBoy.initShaders(animShader.ID);
	
	ModelAnim talkingPhoneGirl("resources/objects/animated models/TalkingPhoneGirl/TalkingPhone.dae");
	talkingPhoneGirl.initShaders(animShader.ID);
	
	ModelAnim talkingWorker("resources/objects/animated models/TalkingWorker/Talking00.dae");
	talkingWorker.initShaders(animShader.ID);
	
	ModelAnim walkingKratos("resources/objects/animated models/Walking Brian/Walking00.dae");
	walkingKratos.initShaders(animShader.ID);
	ModelAnim idleKratos("resources/objects/animated models/idle_00/idle_00_.dae");
	idleKratos.initShaders(animShader.ID);

	ModelAnim walkingKate("resources/objects/animated models/Walking Kate/Walking00.dae");
	walkingKate.initShaders(animShader.ID);
	ModelAnim idleKate("resources/objects/animated models/TalkingPhoneKate/TalkingPhoneKate.dae");
	idleKate.initShaders(animShader.ID);

	ModelAnim walkingLeonard("resources/objects/animated models/Walking Leonard/Walking00.dae");
	walkingLeonard.initShaders(animShader.ID);
	ModelAnim talkingLeo("resources/objects/animated models/TalkingPhoneLeo/TalkingLeo.dae");
	talkingLeo.initShaders(animShader.ID);

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;
	}

	// create transformations and Projection
	glm::mat4 modelOp = glm::mat4(1.0f);		// Initialize Matrix, Use this matrix for individual models
	glm::mat4 viewOp = glm::mat4(1.0f);		    // Use this matrix for ALL models
	glm::mat4 projectionOp = glm::mat4(1.0f);	// This matrix is for Projection

	/* render loop -> start*/
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		lastFrame = SDL_GetTicks();

		// input -> checks if any relevant keys are pressed/released this frame and reacts accordingly
		//my_input(window);
		animate();

		/*Render starts*/

		// the background color is set to black and the color and depth buffers are cleared
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		//Setup shader for static models
		staticShader.use();

		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", ambientColor);
		staticShader.setVec3("dirLight.diffuse", diffuseColor);
		staticShader.setVec3("dirLight.specular", glm::vec3(0.6f, 0.6f, 0.6f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setVec3("spotLight[0].position", glm::vec3(0.0f, 20.0f, 10.0f));
		staticShader.setVec3("spotLight[0].direction", glm::vec3(0.0f, -1.0f, 0.0f));
		staticShader.setVec3("spotLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(10.0f)));
		staticShader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(60.0f)));
		staticShader.setFloat("spotLight[0].constant", 1.0f);
		staticShader.setFloat("spotLight[0].linear", 0.0009f);
		staticShader.setFloat("spotLight[0].quadratic", 0.0005f);

		staticShader.setFloat("material_shininess", 32.0f);

		//glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);

		// view/projection transformations 
		// this projections is for the camera
		projectionOp = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		viewOp = camera.GetViewMatrix();
		staticShader.setMat4("projection", projectionOp);
		staticShader.setMat4("view", viewOp);

		//Setup shader for primitives
		myShader.use();

		// view/projection transformations
		// this projections is for the camera
		viewOp = camera.GetViewMatrix();
		
		// pass them to the shaders
		myShader.setMat4("view", viewOp);
		
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		myShader.setMat4("projection", projectionOp);
		
		// draw skybox
		skyboxShader.use();
		skybox.Draw(skyboxShader, viewOp, projectionOp, camera);

		/*Sección de modelos animados -> starts*/
		
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projectionOp);
		animShader.setMat4("view", viewOp);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		//sitting louise -- inicia
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-525.0f, 1.0f, -350.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, sittingLouiseScale);
		animShader.setMat4("model", modelOp);
		sittingLouise.Draw(animShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-630.0f, 1.0f, 475.0f));
		modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, sittingLouiseScale);
		animShader.setMat4("model", modelOp);
		sittingLouise.Draw(animShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-650.0f, 1.0f, -480.0f));
		modelOp = glm::scale(modelOp, sittingLouiseScale);
		animShader.setMat4("model", modelOp);
		sittingLouise.Draw(animShader);
		//sitting louise -- termina

		//Parejas hablando -- inicia
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-800.0f, 0.0f, -350.0f));
		modelOp = glm::scale(modelOp, talkingWorkerScale);
		animShader.setMat4("model", modelOp);
		talkingWorker.Draw(animShader);
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-800.0f, 0.0f, -300.0f));
		modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, talkingWorkerScale);
		animShader.setMat4("model", modelOp);
		talkingWorker.Draw(animShader);
		//Parejas hablando -- termina

		//angry -- inicia
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-700.0f, 0.0f, -150.0f));
		modelOp = glm::scale(modelOp, angryScale);
		modelOp = glm::rotate(modelOp, glm::radians(angryRot01), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", modelOp);
		angry.Draw(animShader);
		
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-800.0f, 0.0f, 250.5f));
		modelOp = glm::scale(modelOp, angryScale);
		modelOp = glm::rotate(modelOp, glm::radians(angryRot02), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", modelOp);
		angry.Draw(animShader);
		//angry -- termina

		//pointing -- inicia
		modelOp = glm::translate(glm::mat4(1.0f), pointingPos);
		modelOp = glm::scale(modelOp, pointingScale);
		animShader.setMat4("model", modelOp);
		pointing.Draw(animShader);
		//pointing -- termina

		//parejas hablando adentro -- inicia
		modelOp = glm::translate(glm::mat4(1.0f), talkingAdamPos);
		modelOp = glm::scale(modelOp, talkingAdamScale);
		modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", modelOp);
		talkingAdam.Draw(animShader);

		modelOp = glm::translate(glm::mat4(1.0f), talkingBoyPos);
		modelOp = glm::scale(modelOp, talkingBoyScale);
		animShader.setMat4("model", modelOp);
		talkingBoy.Draw(animShader);

		modelOp = glm::translate(glm::mat4(1.0f), talkingPhoneGirlPos);
		modelOp = glm::scale(modelOp, talkingPhoneGirlScale);
		animShader.setMat4("model", modelOp);
		talkingPhoneGirl.Draw(animShader);
		//parejas hablando adentro -- termina

		//walking Brian -- inicia
		switch(walkingBrian_currentState){
			case 0:
				currentStateTime_walkingBrian += deltaTime;
				if ( currentStateTime_walkingBrian <= 10000) {
					modelOp = glm::translate(glm::mat4(1.0f), walkingBrianPos);
					modelOp = glm::scale(modelOp, walkingBrianScale);
					modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
					animShader.setMat4("model", modelOp);
					idleKratos.Draw(animShader);
				} else {
					currentStateTime_walkingBrian = 0;
					walkingBrian_currentState = 1;
				}
				break;
			case 1:
				if ( walkingBrianPos.x <= 430 ) {
					walkingBrianPos.x += 5.0f;
				} else {
					walkingBrian_currentState = 2;
				}
				modelOp = glm::translate(glm::mat4(1.0f), walkingBrianPos);
				modelOp = glm::scale(modelOp, walkingBrianScale);
				modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				walkingKratos.Draw(animShader);
				break;
			case 2:
				currentStateTime_walkingBrian += deltaTime;
				if (currentStateTime_walkingBrian <= 10000) {
					modelOp = glm::translate(glm::mat4(1.0f), walkingBrianPos);
					modelOp = glm::scale(modelOp, walkingBrianScale);
					modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
					animShader.setMat4("model", modelOp);
					idleKratos.Draw(animShader);
				}
				else {
					currentStateTime_walkingBrian = 0;
					walkingBrian_currentState = 3;
				}
				break;
			case 3:
				if (walkingBrianPos.x >= -420.0f) {
					walkingBrianPos.x -= 5.0f;
				}
				else {
					walkingBrian_currentState = 0;
				}
				modelOp = glm::translate(glm::mat4(1.0f), walkingBrianPos);
				modelOp = glm::scale(modelOp, walkingBrianScale);
				modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				walkingKratos.Draw(animShader);
				break;
			default:
				modelOp = glm::translate(glm::mat4(1.0f), walkingBrianPos);
				modelOp = glm::scale(modelOp, walkingBrianScale);
				modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				personaje01.Draw(animShader);
				break;
		}
		//walking Brian -- termina

		//walking Brian 00 -- inicia
		switch (walkingBrian00_currentState) {
		case 0:
			currentStateTime_walkingBrian00 += deltaTime;
			if (currentStateTime_walkingBrian00 <= 10000) {
				modelOp = glm::translate(glm::mat4(1.0f), walkingBrian00Pos);
				modelOp = glm::scale(modelOp, walkingBrianScale);
				modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				idleKratos.Draw(animShader);
			}
			else {
				currentStateTime_walkingBrian00 = 0;
				walkingBrian00_currentState = 1;
			}
			break;
		case 1:
			if (walkingBrian00Pos.z >= -50) {
				walkingBrian00Pos.z -= 5.0f;
			}
			else {
				walkingBrian00_currentState = 2;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingBrian00Pos);
			modelOp = glm::scale(modelOp, walkingBrianScale);
			modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingKratos.Draw(animShader);
			break;
		case 2:
			currentStateTime_walkingBrian00 += deltaTime;
			if (currentStateTime_walkingBrian00 <= 10000) {
				modelOp = glm::translate(glm::mat4(1.0f), walkingBrian00Pos);
				modelOp = glm::scale(modelOp, walkingBrianScale);
				modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				idleKratos.Draw(animShader);
			}
			else {
				currentStateTime_walkingBrian00 = 0;
				walkingBrian00_currentState = 3;
			}
			break;
		case 3:
			if (walkingBrian00Pos.z <= 450.0f) {
				walkingBrian00Pos.z += 5.0f;
			}
			else {
				walkingBrian00_currentState = 0;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingBrian00Pos);
			modelOp = glm::scale(modelOp, walkingBrianScale);
			modelOp = glm::rotate(modelOp, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingKratos.Draw(animShader);
			break;
		default:
			modelOp = glm::translate(glm::mat4(1.0f), walkingBrianPos);
			modelOp = glm::scale(modelOp, walkingBrianScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			personaje01.Draw(animShader);
			break;
		}
		//walking Brian00 -- termina

		//walking kate -- inicia
		switch (walkingKate_currentState) {
		case 0:
			currentStateTime_walkingKate += deltaTime;
			if (currentStateTime_walkingKate <= 15500) {
				modelOp = glm::translate(glm::mat4(1.0f), walkingKatePos);
				modelOp = glm::scale(modelOp, walkingKateScale);
				modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				idleKate.Draw(animShader);
			}
			else {
				currentStateTime_walkingKate = 0;
				walkingKate_currentState = 1;
			}
			break;
		case 1:
			if (walkingKatePos.z <= 400.0f) {
				walkingKatePos.z += 5.0f;
			}
			else {
				walkingKate_currentState = 2;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingKatePos);
			modelOp = glm::scale(modelOp, walkingKateScale);
			modelOp = glm::rotate(modelOp, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingKate.Draw(animShader);
			break;
		case 2:
			currentStateTime_walkingKate += deltaTime;
			if (currentStateTime_walkingKate <= 15750) {
				modelOp = glm::translate(glm::mat4(1.0f), walkingKatePos);
				modelOp = glm::scale(modelOp, walkingKateScale);
				modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				idleKate.Draw(animShader);
			}
			else {
				currentStateTime_walkingKate = 0;
				walkingKate_currentState = 3;
			}
			break;
		case 3:
			if (walkingKatePos.z >= -400.0f) {
				walkingKatePos.z -= 5.0f;
			}else {
				walkingKate_currentState = 0;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingKatePos);
			modelOp = glm::scale(modelOp, walkingKateScale);
			modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingKate.Draw(animShader);
			break;
		default:
			modelOp = glm::translate(glm::mat4(1.0f), walkingBrianPos);
			modelOp = glm::scale(modelOp, walkingBrianScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			personaje01.Draw(animShader);
			break;
		}
		//walking kate -- termina

		//walking kate 00 -- inicia
		switch (walkingKate00_currentState) {
		case 0:
			currentStateTime_walkingKate00 += deltaTime;
			if (currentStateTime_walkingKate00 <= 15500) {
				modelOp = glm::translate(glm::mat4(1.0f), walkingKate00Pos);
				modelOp = glm::scale(modelOp, walkingKateScale);
				modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				idleKate.Draw(animShader);
			}
			else {
				currentStateTime_walkingKate00 = 0;
				walkingKate00_currentState = 1;
			}
			break;
		case 1:
			if (walkingKate00Pos.z <= 230.0f) {
				walkingKate00Pos.z += 5.0f;
			}
			else {
				walkingKate00_currentState = 2;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingKate00Pos);
			modelOp = glm::scale(modelOp, walkingKateScale);
			modelOp = glm::rotate(modelOp, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingKate.Draw(animShader);
			break;
		case 2:
			currentStateTime_walkingKate00 += deltaTime;
			if (currentStateTime_walkingKate00 <= 15750) {
				modelOp = glm::translate(glm::mat4(1.0f), walkingKate00Pos);
				modelOp = glm::scale(modelOp, walkingKateScale);
				modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				idleKate.Draw(animShader);
			}
			else {
				currentStateTime_walkingKate00 = 0;
				walkingKate00_currentState = 3;
			}
			break;
		case 3:
			if (walkingKate00Pos.z >= -400.0f) {
				walkingKate00Pos.z -= 5.0f;
			}
			else {
				walkingKate00_currentState = 0;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingKate00Pos);
			modelOp = glm::scale(modelOp, walkingKateScale);
			modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingKate.Draw(animShader);
			break;
		default:
			modelOp = glm::translate(glm::mat4(1.0f), walkingBrianPos);
			modelOp = glm::scale(modelOp, walkingBrianScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			personaje01.Draw(animShader);
			break;
		}
		//walking kate 00 -- termina

		//walking kate 01 -- inicia
		switch (walkingKate01_currentState) {
		case 0:
			currentStateTime_walkingKate01 += deltaTime;
			if (currentStateTime_walkingKate01 <= 15500) {
				modelOp = glm::translate(glm::mat4(1.0f), walkingKate01Pos);
				modelOp = glm::scale(modelOp, walkingKateScale);
				modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				idleKate.Draw(animShader);
			}
			else {
				currentStateTime_walkingKate01 = 0;
				walkingKate01_currentState = 1;
			}
			break;
		case 1:
			if (walkingKate01Pos.x >= -250.0f) {
				walkingKate01Pos.x -= 5.0f;
			}
			else {
				walkingKate01_currentState = 2;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingKate01Pos);
			modelOp = glm::scale(modelOp, walkingKateScale);
			modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingKate.Draw(animShader);
			break;
		case 2:
			currentStateTime_walkingKate01 += deltaTime;
			if (currentStateTime_walkingKate01 <= 15750) {
				modelOp = glm::translate(glm::mat4(1.0f), walkingKate01Pos);
				modelOp = glm::scale(modelOp, walkingKateScale);
				modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				animShader.setMat4("model", modelOp);
				idleKate.Draw(animShader);
			}
			else {
				currentStateTime_walkingKate01 = 0;
				walkingKate01_currentState = 3;
			}
			break;
		case 3:
			if (walkingKate01Pos.x <= 75.0f) {
				walkingKate01Pos.x += 5.0f;
			}
			else {
				walkingKate01_currentState = 0;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingKate01Pos);
			modelOp = glm::scale(modelOp, walkingKateScale);
			modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingKate.Draw(animShader);
			break;
		default:
			modelOp = glm::translate(glm::mat4(1.0f), walkingBrianPos);
			modelOp = glm::scale(modelOp, walkingBrianScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingBrianRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			personaje01.Draw(animShader);
			break;
		}
		//walking kate 01 -- termina

		//walking leonard -- inicia
		switch (walkingLeonard_currentState) {
		case 0:
			if (walkingLeonardPos.x <= 0.0f) { 
				walkingLeonardPos.x += 5.0f;
			}
			else {
				walkingLeonard_currentState = 1;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeonardPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeonardRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		case 1:
			if (walkingLeonardRot <= 180.0f) {
				walkingLeonardRot += 5.0f;
			}
			else {
				walkingLeonard_currentState = 2;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeonardPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeonardRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		case 2:
			if (walkingLeonardPos.z >= -165.0f) {
				walkingLeonardPos.z -= 5.0f;
			}
			else {
				walkingLeonard_currentState = 3;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeonardPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeonardRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		case 3:
			if (walkingLeonardPos.y <= 135.0f) {
				walkingLeonardPos.z -= 5.0f;
				walkingLeonardPos.y += 2.5f;
			}
			else {
				walkingLeonard_currentState = 4;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeonardPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeonardRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		case 4:
			if (walkingLeonardRot >= 90.0f) {
				walkingLeonardRot -= 5.0f;
			}
			else {
				walkingLeonard_currentState = 5;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeonardPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeonardRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		case 5:
			if (walkingLeonardPos.x <= 110.0f) {
				walkingLeonardPos.x += 5.0f;
			}
			else {
				walkingLeonard_currentState = 6;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeonardPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeonardRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		case 6:
			if (walkingLeonardRot >= 0.0f) {
				walkingLeonardRot -= 5.0f;
			}
			else {
				walkingLeonard_currentState = 7;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeonardPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeonardRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		case 7:
			if (walkingLeonardPos.y <= 270.0f) {
				walkingLeonardPos.z += 5.0f;
				walkingLeonardPos.y += 2.5f;
			}
			else {
				walkingLeonardPos = startingPointLeonardPos;
				walkingLeonardRot = startingWalkingLeonardRot;
				walkingLeonard_currentState = 0;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeonardPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeonardRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		default:
			modelOp = glm::translate(glm::mat4(1.0f), initialPos);
			modelOp = glm::scale(modelOp, walkingBrianScale);
			modelOp = glm::rotate(modelOp, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			personaje01.Draw(animShader);
			break;
		}
		//walking leonard -- termina

		//walking leo --inicia
		switch (walkingLeo_currentState) {
		case 0:
			if (currentStateTime_walkingLeo <= 25000) {
				currentStateTime_walkingLeo += deltaTime;
			}
			else {
				currentStateTime_walkingLeo = 0;
				walkingLeo_currentState = 1;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeoPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeoRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			talkingLeo.Draw(animShader);
			break;
		case 1:
			if ( theta <= limitB ) {
				theta += 0.025;
				new_x = circleCenter.x + circleRadius * cos(theta);
				new_z = circleCenter.z - circleRadius * sin(theta);
				walkingLeoPos.x = new_x;
				walkingLeoPos.z = new_z;
			}
			else {
				walkingLeo_currentState = 2;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeoPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, 2*glm::radians(walkingLeoRot)+theta, glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		case 2:
			if (currentStateTime_walkingLeo <= 25000) {
				currentStateTime_walkingLeo += deltaTime;
			}
			else {
				currentStateTime_walkingLeo = 0;
				walkingLeo_currentState = 3;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeoPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeoRot), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			talkingLeo.Draw(animShader);
			break;
		case 3:
			if (theta >= limitA) {
				theta -= 0.025;
				new_x = circleCenter.x + circleRadius * cos(theta);
				new_z = circleCenter.z - circleRadius * sin(theta);
				walkingLeoPos.x = new_x;
				walkingLeoPos.z = new_z;
			}
			else {
				walkingLeo_currentState = 0;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeoPos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, glm::radians(currentLeoRot) + theta, glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		default:
			modelOp = glm::translate(glm::mat4(1.0f), initialPos);
			modelOp = glm::scale(modelOp, walkingBrianScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeoRot+0.5f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			personaje01.Draw(animShader);
			break;
		}
		//walking leo -- termina

		//walking leo 00 -- inicia
		switch (walkingLeo00_currentState) {
		case 0:
			if (currentStateTime_walkingLeo00 <= 25000) {
				currentStateTime_walkingLeo00 += deltaTime;
			}
			else {
				currentStateTime_walkingLeo00 = 0;
				walkingLeo00_currentState = 1;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeo00Pos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			talkingLeo.Draw(animShader);
			break;
		case 1:
			if ( walkingLeo00Pos.z >= -450.0f ) {
				walkingLeo00Pos.z -= 5.0f;
			}
			else {
				walkingLeo00_currentState = 2;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeo00Pos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		case 2:
			if (currentStateTime_walkingLeo00 <= 25000) {
				currentStateTime_walkingLeo00 += deltaTime;
			}
			else {
				currentStateTime_walkingLeo00 = 0;
				walkingLeo00_currentState = 3;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeo00Pos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			talkingLeo.Draw(animShader);
			break;
		case 3:
			if ( walkingLeo00Pos.z <= -200.0f ) {
				walkingLeo00Pos.z += 5.0f;
			}
			else {
				walkingLeo00_currentState = 0;
			}
			modelOp = glm::translate(glm::mat4(1.0f), walkingLeo00Pos);
			modelOp = glm::scale(modelOp, walkingLeonardScale);
			modelOp = glm::rotate(modelOp, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			walkingLeonard.Draw(animShader);
			break;
		default:
			modelOp = glm::translate(glm::mat4(1.0f), initialPos);
			modelOp = glm::scale(modelOp, walkingBrianScale);
			modelOp = glm::rotate(modelOp, glm::radians(walkingLeoRot + 0.5f), glm::vec3(0.0f, 1.0f, 0.0f));
			animShader.setMat4("model", modelOp);
			personaje01.Draw(animShader);
			break;
		}
		//walking leo 00 -- termina
		/*Sección de modelos animados -> ends*/

		/*Primtivas del escenario -> start*/
		myShader.use();
		glBindVertexArray(0);
		/*Primtivas del escenario -> ends*/

		/*sección de Modelos estaticos -> starts*/
		staticShader.use();
		staticShader.setMat4("projection", projectionOp);
		staticShader.setMat4("view", viewOp);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(50.0f, 1.0f, 50.0f));
		staticShader.setMat4("model", modelOp);
		suelo.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 245.0f, 400.0f));
		modelOp = glm::scale(modelOp, glm::vec3(50.0f, 1.0f, 50.0f));
		staticShader.setMat4("model", modelOp);
		techo.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-310.0f, 245.0f, -300.0f));
		modelOp = glm::scale(modelOp, glm::vec3(20.0f, 1.0f, 20.0f));
		staticShader.setMat4("model", modelOp);
		techo01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(375.0f, 245.0f, -300.0f));
		modelOp = glm::scale(modelOp, glm::vec3(12.0f, 1.0f, 20.0f));
		staticShader.setMat4("model", modelOp);
		techo02.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-700.0f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(20.0f, 1.0f, 50.0f));
		staticShader.setMat4("model", modelOp);
		outside_suelo.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.0f, -200.0f));
		modelOp = glm::scale(modelOp, glm::vec3(10.0f));
		staticShader.setMat4("model", modelOp);
		banqueta00.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-170.0f, 0.0f, 370.0f));
		modelOp = glm::scale(modelOp, glm::vec3(32.5f, 10.0f, 12.5f));
		staticShader.setMat4("model", modelOp);
		banqueta01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-170.0f, 0.0f, 600.0f));
		modelOp = glm::scale(modelOp, glm::vec3(32.5f, 10.0f, 12.5f));
		staticShader.setMat4("model", modelOp);
		banqueta02.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 1.0f, 200.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 6.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 1.0f, 290.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 6.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja00.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 1.0f, 380.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 6.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 6.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja02.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 1.0f, -90.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 6.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja03.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 180.0f, 500.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 1.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja04.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 180.0f, 410.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 1.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja05.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 180.0f, 320.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 1.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja06.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 180.0f, 230.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 1.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja07.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 180.0f, 140.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 1.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja08.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 180.0f, 50.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 1.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja09.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 180.0f, -40.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 1.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja10.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 180.0f, -130.0f));
		modelOp = glm::scale(modelOp, glm::vec3(5.0f, 1.0f, 5.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		reja11.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-490.0f, 100.0f, -420.0f));
		modelOp = glm::scale(modelOp, glm::vec3(15.0f, 15.0f, 20.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		muro00.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 100.0f, -500.0f));
		modelOp = glm::scale(modelOp, glm::vec3(50.0f, 15.0f, 20.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		muro01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-300.0f, 100.0f, 500.0f));
		modelOp = glm::scale(modelOp, glm::vec3(20.0f, 15.0f, 20.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		muro02.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(490.0f, 100.0f, -350.0f));
		modelOp = glm::scale(modelOp, glm::vec3(25.0f, 15.0f, 20.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		muro03.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-490.0f, 240.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(20.0f, 3.0f, 51.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		muro04.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-50.0f, 47.5f, 730.0f));
		modelOp = glm::scale(modelOp, glm::vec3(20.0f, 20.0f, 20.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		muro05.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-225.0f, 47.5f, 702.0f));
		modelOp = glm::scale(modelOp, glm::vec3(20.0f, 20.0f, 20.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		muro06.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-450.0f, 0.0f, -80.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.75f, 7.5f, 1.75f));
		staticShader.setMat4("model", modelOp);
		columna_circulo.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-450.0f, 0.0f, 270.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.75f, 7.5f, 1.75f));
		staticShader.setMat4("model", modelOp);
		columna_circulo00.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-450.0f, 0.0f, 450.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.75f, 7.5f, 1.75f));
		staticShader.setMat4("model", modelOp);
		columna_circulo01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0f, 0.0f, 450.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.75f, 7.5f, 1.75f));
		staticShader.setMat4("model", modelOp);
		columna_circulo02.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 0.0f, 450.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.75f, 7.5f, 1.75f));
		staticShader.setMat4("model", modelOp);
		columna_circulo03.Draw(staticShader);
		
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0f, 0.0f, 290.0f));
		modelOp = glm::scale(modelOp, glm::vec3(10.0f, 30.0f, 10.0f));
		staticShader.setMat4("model", modelOp);
		columna_ovalo.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3( 50.0f, 0.0f, 290.0f));
		modelOp = glm::scale(modelOp, glm::vec3(10.0f, 30.0f, 10.0f));
		staticShader.setMat4("model", modelOp);
		columna_ovalo02.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3( 475.0f, 0.0f, 290.0f));
		modelOp = glm::scale(modelOp, glm::vec3(10.0f, 30.0f, 10.0f));
		staticShader.setMat4("model", modelOp);
		columna_ovalo03.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(475.0f, 0.0f, -80.0f));
		modelOp = glm::scale(modelOp, glm::vec3(10.0f, 30.0f, 10.0f));
		staticShader.setMat4("model", modelOp);
		columna_ovalo01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0f, 0.0f, -50.0f));
		modelOp = glm::scale(modelOp, glm::vec3(10.0f, 30.0f, 10.0f));
		staticShader.setMat4("model", modelOp);
		columna_ovalo04.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 0.0f, -50.0f));
		modelOp = glm::scale(modelOp, glm::vec3(10.0f, 30.0f, 10.0f));
		staticShader.setMat4("model", modelOp);
		columna_ovalo05.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-525.0f, 1.0f, -135.0f));
		modelOp = glm::scale(modelOp, glm::vec3(50.0f, 50.0f, 50.0f));
		staticShader.setMat4("model", modelOp);
		banca.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-525.0f, 1.0f, -350.0f));
		modelOp = glm::scale(modelOp, glm::vec3(50.0f, 50.0f, 50.0f));
		staticShader.setMat4("model", modelOp);
		banca00.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-650.0f, 1.0f, -480.0f));
		modelOp = glm::scale(modelOp, glm::vec3(50.0f, 50.0f, 50.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		banca01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-800.0f, 1.0f, -480.0f));
		modelOp = glm::scale(modelOp, glm::vec3(50.0f, 50.0f, 50.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		banca02.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-525.0f, 1.0f, 300.0f));
		modelOp = glm::scale(modelOp, glm::vec3(50.0f, 50.0f, 50.0f));
		staticShader.setMat4("model", modelOp);
		banca03.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-630.0f, 1.0f, 475.0f));
		modelOp = glm::scale(modelOp, glm::vec3(50.0f, 50.0f, 50.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		banca04.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-850.0f, 1.0f, 475.0f));
		modelOp = glm::scale(modelOp, glm::vec3(50.0f, 50.0f, 50.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		banca05.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-560.0f, 0.0f, -460.0f));
		modelOp = glm::scale(modelOp, glm::vec3(7.5f, 20.0f, 7.5f));
		staticShader.setMat4("model", modelOp);
		lampara.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-750.0f, 0.0f, 475.0f));
		modelOp = glm::scale(modelOp, glm::vec3(7.5f, 20.0f, 7.5f));
		modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		lampara.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 0.0f, -175.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.75f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		stand01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 0.0f, -300.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.75f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		stand01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 0.0f, -415.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.75f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		stand01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 0.0f, 400.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.75f));
		modelOp = glm::rotate(modelOp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		stand01.Draw(staticShader);
	
		//aqui se colocan los modelos estaticos que tengan algun tipo de transparencia -> inicia
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 20.0f, -200.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.5f));
		staticShader.setMat4("model", modelOp);
		escaleras.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-300.0f, 100.0f, 475.0f));
		modelOp = glm::scale(modelOp, glm::vec3(10.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		ventana.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-50.0f, 10.0f, 485.0f));
		modelOp = glm::scale(modelOp, glm::vec3(10.0f, 23.5f, 7.5f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		ventana00.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(75.0f, 10.0f, 485.0f));
		modelOp = glm::scale(modelOp, glm::vec3(15.0f, 23.5f, 7.5f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		ventana01.Draw(staticShader);

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(150.0f, 10.0f, 610.0f));
		modelOp = glm::scale(modelOp, glm::vec3(7.5f, 23.5f, 25.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", modelOp);
		ventana02.Draw(staticShader);

		glDisable(GL_BLEND);
		//modelos estaticos con transparencia -> termina

		/*sección de Modelos estaticos -> ends*/

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glDeleteVertexArrays(3, VAO);
	glDeleteBuffers(3, VBO);
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos) 
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

/*handmade functions definition*/


/* Este codigo es para dibujar un cuadrado con textura, se puede modificar para crear otras figuras y colocar otras texturas
		 * Se mantiene aquí como ejemplo de dibujo de un plano con textura
		glBindVertexArray(VAO[2]);
		modelOp = glm::scale(glm::mat4(1.0f), glm::vec3(40.0f, 2.0f, 40.0f));
		modelOp = glm::translate(modelOp, glm::vec3(0.0f, -1.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, t_ladrillos);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		*/