
#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

#ifdef _MSC_VER
#pragma warning(disable: 4100) // Disable warning 'unreferenced formal parameter'
#endif // _MSC_VER



#ifdef _MSC_VER
#pragma warning(default: 4100) // Enable warning 'unreferenced formal parameter'
#endif // _MSC_VER

#include <fstream>

//PR”BA TEKSTUR NR 56
#define BITMAP_ID 0x4D42
// Opis tekstury
BITMAPINFOHEADER	bitmapInfoHeader;	// nag≥Ûwek obrazu
unsigned char* bitmapData;				// dane tekstury
unsigned int		texture[10];		// obiekt tekstury




//to map image filenames to textureIds
#include <string.h>
#include <map>


#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>
//#include "UTFConverter.h"


//static std::string modelpath = "C:/Users/Miko≥aj/Desktop/PROJEKT WALL-E/SimpleTexturedOpenGL/objekty/tank.obj";
static std::string modelpath = "cube.obj";
static std::string modelpath2 = "ak.obj";
static std::string modelpath3 = "mapapg2.obj";
static std::string modelpath4 = "drzewo.obj";
static std::string modelpath5 = "liscie.obj";
static std::string modelpath6 = "KociaLapkapd.obj";




HGLRC       hRC=nullptr;            // Permanent Rendering Context
HDC         hDC=nullptr;            // Private GDI Device Context
HWND        g_hWnd=nullptr;         // Holds Window Handle
HINSTANCE   g_hInstance=nullptr;    // Holds The Instance Of The Application

bool		keys[256];			// Array used for Keyboard Routine;
bool		active=TRUE;		// Window Active Flag Set To TRUE by Default
bool		fullscreen=FALSE;	// full-screen Flag Set To full-screen By Default

GLfloat		xrot;
GLfloat		yrot;
GLfloat		zrot;
#define GL_PI 3.14
//globalne
float kolorGasienicy = 0.0f;
float oko1 = 13;
float obr = 0;
float Xpos = 0, Zpos = 0, Ypos = 0;
float kat = 0;
float Xkam = 0, Ykam = -5, Zkam = 0;
GLfloat xRot = 15.0f;
GLfloat yRot = 0.0f;
int bob = 0;
float idle = 0;
float szyjaObr = 0;
int szyjaR = 0;
float dlonObr = 0;
float dlonObr2 = 0;

float obrotSrubek = 0;


float ramieZ = 0;
float ramieY = 0;

float katRamion = 0;

float przedluzenie = 0;
float pochylenie = 0;

int kroki = 0;
int podnoszenie = 0;
int opuszczanie = 0;
int wpychanie = 0;
int nies = 0;

float katp;
float opad = 0.45;

float nachylenieX = 0, nachylenieZ = 0;
float predkosc = 0;
//float predkoscObrotu = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
GLboolean abortGLInit(const char*);

const char* windowTitle = "Projekt WALL∑E";

float catX = -20, catY = 0,catZ = -50, minCatY;

bool kamera = false;
float wysokosc[200];

#define STB_IMAGE_IMPLEMENTATION
#include "contrib/stb/stb_image.h"

float wys1[500][500];
float wys2[500][500];
float wys3[500][500];
float wys4[500][500];

int w, h;
stbi_uc* mapa = stbi_load("mapapg.png", &w, &h, NULL, 1);
stbi_uc* mapalg = stbi_load("mapalg.png", &w, &h, NULL, 1);
stbi_uc* mapald = stbi_load("mapald.png", &w, &h, NULL, 1);
stbi_uc* mapapd = stbi_load("mapapd.png", &w, &h, NULL, 1);




// the global Assimp scene object
const aiScene* g_scene = nullptr;
const aiScene* g_scene2 = nullptr;
const aiScene* g_scene3 = nullptr;
const aiScene* g_scene4 = nullptr;
const aiScene* g_scene5 = nullptr;
const aiScene* g_scene6 = nullptr;
GLuint scene_list = 0;
aiVector3D scene_min, scene_max, scene_center;

// images / texture
std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds
GLuint*		textureIds;							// pointer to texture Array

// Create an instance of the Importer class
Assimp::Importer importer;
Assimp::Importer importer2;
Assimp::Importer importer3;
Assimp::Importer importer4;
Assimp::Importer importer5;
Assimp::Importer importer6;


bool Import3DFromFile( const std::string& pFile)
{
	// Check if file exists
	std::ifstream fin(pFile.c_str());
	if(!fin.fail())
	{
		fin.close();
	}
	else
	{
		//MessageBox(nullptr, UTFConverter("Couldn't open file: " + pFile).c_wstr() , TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		//( importer.GetErrorString());
		return false;
	}

	g_scene = importer.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality);

	// If the import failed, report it
	if(!g_scene)
	{
		//logInfo( importer.GetErrorString());
		return false;
	}

	// Now we can access the file's contents.
	//logInfo("Import of scene " + pFile + " succeeded.");

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}
//2 model
bool Import3DFromFile2(const std::string& pFile)
{
	g_scene2 = importer2.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality);
	if (!g_scene2)
		return false;
	return true;
}
bool Import3DFromFile3(const std::string& pFile)
{
	g_scene3 = importer3.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality);
	if (!g_scene3)
		return false;
	return true;
}
bool Import3DFromFile4(const std::string& pFile)
{
	g_scene4 = importer4.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality);
	if (!g_scene4)
		return false;
	return true;
}
bool Import3DFromFile5(const std::string& pFile)
{
	g_scene5 = importer5.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality);
	if (!g_scene4)
		return false;
	return true;
}
bool Import3DFromFile6(const std::string& pFile)
{
	g_scene6 = importer6.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality);
	if (!g_scene4)
		return false;
	return true;
}

//PR”BA TEKSTUR NR 56
// // LoadBitmapFile
// opis: ≥aduje mapÍ bitowπ z pliku i zwraca jej adres.
//       Wype≥nia strukturÍ nag≥Ûwka.
//	 Nie obs≥uguje map 8-bitowych.
unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader)
{
	FILE* filePtr;							// wskaünik pozycji pliku
	BITMAPFILEHEADER	bitmapFileHeader;		// nag≥Ûwek pliku
	unsigned char* bitmapImage;			// dane obrazu
	int					imageIdx = 0;		// licznik pikseli
	unsigned char		tempRGB;				// zmienna zamiany sk≥adowych

	// otwiera plik w trybie "read binary"
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// wczytuje nag≥Ûwek pliku
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// sprawdza, czy jest to plik formatu BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// wczytuje nag≥Ûwek obrazu
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// ustawia wskaünik pozycji pliku na poczπtku danych obrazu
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// przydziela pamiÍÊ buforowi obrazu
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// sprawdza, czy uda≥o siÍ przydzieliÊ pamiÍÊ
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// wczytuje dane obrazu
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// sprawdza, czy dane zosta≥y wczytane
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// zamienia miejscami sk≥adowe R i B 
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// zamyka plik i zwraca wskaünik bufora zawierajπcego wczytany obraz
	fclose(filePtr);
	return bitmapImage;
}
//




// Resize And Initialize The GL Window
void ReSizeGLScene(GLsizei width, GLsizei height)
{
    // Prevent A Divide By Zero By
	if (height==0)
	{
        // Making Height Equal One
        height=1;
	}

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();							// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,1.0f,1500.0f);

	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	glLoadIdentity();							// Reset The Modelview Matrix
}


std::string getBasePath(const std::string& path)
{
	size_t pos = path.find_last_of("\\/");
	return (std::string::npos == pos) ? "" : path.substr(0, pos + 1);
}

void freeTextureIds()
{
	textureIdMap.clear(); //no need to delete pointers in it manually here. (Pointers point to textureIds deleted in next step)

	if (textureIds)
	{
		delete[] textureIds;
		textureIds = nullptr;
	}
}

int LoadGLTextures(const aiScene* scene)
{
	freeTextureIds();

	//ILboolean success;

	/* Before calling ilInit() version should be checked. */
	/*if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		/// wrong DevIL version ///
		std::string err_msg = "Wrong DevIL version. Old devil.dll in system32/SysWow64?";
		char* cErr_msg = (char *) err_msg.c_str();
		abortGLInit(cErr_msg);
		return -1;
	}*/

	//ilInit(); /* Initialization of DevIL */

    if (scene->HasTextures()) return 1;
        //abortGLInit("Support for meshes with embedded textures is not implemented");

	/* getTexture Filenames and Numb of Textures */
	for (unsigned int m=0; m<scene->mNumMaterials; m++)
	{
		int texIndex = 0;
		aiReturn texFound = AI_SUCCESS;

		aiString path;	// filename

		while (texFound == AI_SUCCESS)
		{
			texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
			textureIdMap[path.data] = nullptr; //fill map with textures, pointers still NULL yet
			texIndex++;
		}
	}

	const size_t numTextures = textureIdMap.size();


	/* array with DevIL image IDs */
	//ILuint* imageIds = NULL;
//	imageIds = new ILuint[numTextures];

	/* generate DevIL Image IDs */
//	ilGenImages(numTextures, imageIds); /* Generation of numTextures image names */

	/* create and fill array with GL texture ids */
	textureIds = new GLuint[numTextures];
	glGenTextures(static_cast<GLsizei>(numTextures), textureIds); /* Texture name generation */

	/* get iterator */
	std::map<std::string, GLuint*>::iterator itr = textureIdMap.begin();

	std::string basepath = getBasePath(modelpath);
	for (size_t i=0; i<numTextures; i++)
	{

		//save IL image ID
		std::string filename = (*itr).first;  // get filename
		(*itr).second =  &textureIds[i];	  // save texture id for filename in map
		itr++;								  // next texture


		//ilBindImage(imageIds[i]); /* Binding of DevIL image name */
		std::string fileloc = basepath + filename;	/* Loading of image */
		//success = ilLoadImage(fileloc.c_str());
        int x, y, n;
        unsigned char *data = stbi_load(fileloc.c_str(), &x, &y, &n, STBI_rgb_alpha);

		if (nullptr != data )
		{
            // Convert every colour component into unsigned byte.If your image contains
            // alpha channel you can replace IL_RGB with IL_RGBA
            //success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
			/*if (!success)
			{
				abortGLInit("Couldn't convert image");
				return -1;
			}*/
            // Binding of texture name
            //glBindTexture(GL_TEXTURE_2D, textureIds[i]);
			// redefine standard texture values
            // We will use linear interpolation for magnification filter
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            // We will use linear interpolation for minifying filter
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            // Texture specification
            glTexImage2D(GL_TEXTURE_2D, 0, n, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);// Texture specification.

            // we also want to be able to deal with odd texture dimensions
            glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
            glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
            glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
            glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
            stbi_image_free(data);
        }
		else
		{
			/* Error occurred */
			//MessageBox(nullptr, UTFConverter("Couldn't load Image: " + fileloc).c_wstr(), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		}
	}
    // Because we have already copied image data into texture data  we can release memory used by image.
//	ilDeleteImages(numTextures, imageIds);

	// Cleanup
	//delete [] imageIds;
	//imageIds = NULL;

	return TRUE;
}



GLfloat LightAmbient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat LightDiffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 5.0f, 5.0f, 0.0f };

// All Setup For OpenGL goes here
int InitGL()
{
	//for (int i = 0; i < 200; i++)
	//{
	//	if (i < 100)
	//		wysokosc[i] = 0;
	//	else
	//		wysokosc[i] = (i - 100) * tan(GL_PI / 12);
	//}

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
			wys1[i][j] = mapalg[w * i + j] -80.0f ;
	}
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
			wys2[i][j] = mapa[w * i + j] - 80.0f;
	}
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
			wys3[i][j] = mapald[w * i + j] - 80.0f;
	}
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
			wys4[i][j] = mapapd[w * i + j] - 80.0f;
	}
	if (!LoadGLTextures(g_scene))
	{
		return FALSE;
	}

	//PR”BA TEKSTUR NR 56
	glGenTextures(10, &texture[0]);                  // tworzy obiekt tekstury			

		// ≥aduje pierwszy obraz tekstury:
	bitmapData = LoadBitmapFile("Bok.bmp", &bitmapInfoHeader);

	glBindTexture(GL_TEXTURE_2D, texture[0]);       // aktywuje obiekt tekstury

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// tworzy obraz tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

	if (bitmapData)
		free(bitmapData);

	// ≥aduje drugi obraz tekstury:
	bitmapData = LoadBitmapFile("mapka1.bmp", &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[1]);       // aktywuje obiekt tekstury

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// tworzy obraz tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

	if (bitmapData)
		free(bitmapData);
		

		// ≥aduje pierwszy obraz tekstury:
	bitmapData = LoadBitmapFile("cat.bmp", &bitmapInfoHeader);

	glBindTexture(GL_TEXTURE_2D, texture[2]);       // aktywuje obiekt tekstury

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// tworzy obraz tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

	if (bitmapData)
		free(bitmapData);

	bitmapData = LoadBitmapFile("woda.bmp", &bitmapInfoHeader);

	glBindTexture(GL_TEXTURE_2D, texture[3]);       // aktywuje obiekt tekstury

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// tworzy obraz tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

	if (bitmapData)
		free(bitmapData);

	bitmapData = LoadBitmapFile("drzewo.bmp", &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[4]);       // aktywuje obiekt tekstury

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// tworzy obraz tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

	if (bitmapData)
		free(bitmapData);

	bitmapData = LoadBitmapFile("liscie.bmp", &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[5]);       // aktywuje obiekt tekstury

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// tworzy obraz tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

	if (bitmapData)
		free(bitmapData);

	bitmapData = LoadBitmapFile("paseczki.bmp", &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[6]);       // aktywuje obiekt tekstury

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// tworzy obraz tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

	if (bitmapData)
		free(bitmapData);

	bitmapData = LoadBitmapFile("Panel.bmp", &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[7]);       // aktywuje obiekt tekstury

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// tworzy obraz tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

	if (bitmapData)
		free(bitmapData);

	bitmapData = LoadBitmapFile("trasz.bmp", &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, texture[8]);       // aktywuje obiekt tekstury

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// tworzy obraz tekstury
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);

	if (bitmapData)
		free(bitmapData);

	// ustalenie sposobu mieszania tekstury z t≥em
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	//






	//glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);		 // Enables Smooth Shading
	glClearColor(0.45f, 0.7f, 1.0f, 0.0f);
	glClearDepth(1.0f);				// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation


	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);    // Uses default lighting parameters
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_NORMALIZE);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);

	//
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	return TRUE;					// Initialization Went OK
}


// Can't send color down as a pointer to aiColor4D because AI colors are ABGR.
void Color4f(const aiColor4D *color)
{
	glColor4f(color->r, color->g, color->b, color->a);
}

void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void color4_to_float4(const aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void apply_material(const aiMaterial *mtl)
{
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	aiColor4D diffuse;
	aiColor4D specular;
	aiColor4D ambient;
	aiColor4D emission;
	ai_real shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;	// changed: to unsigned

	int texIndex = 0;
	aiString texPath;	//contains filename of texture

	if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
	{
		//bind texture
		unsigned int texId = *textureIdMap[texPath.data];
		glBindTexture(GL_TEXTURE_2D, texId);
	}

	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	max = 1;
	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
	if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	//if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
	//	glEnable(GL_CULL_FACE);
	//else
	//	glDisable(GL_CULL_FACE);
}


void recursive_render (const struct aiScene *sc, const struct aiNode* nd, float scale, int teren)
{
	unsigned int i;
	unsigned int n=0, t;
	aiMatrix4x4 m = nd->mTransformation;
	aiMatrix4x4 m2;
	aiMatrix4x4::Scaling(aiVector3D(scale, scale, scale), m2);
	m = m * m2;
	m.Transpose();
	glPushMatrix();
	glMultMatrixf((float*)&m);
	for (; n < nd->mNumMeshes; ++n)
	{
		const struct aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumFaces; ++t) 
		{
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;
			switch(face->mNumIndices)
			{
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}
			glBegin(face_mode);
			for(i = 0; i < face->mNumIndices; i++)
			{
				int vertexIndex = face->mIndices[i];
				if(mesh->HasTextureCoords(0))		
					glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y);
					glNormal3fv(&mesh->mNormals[vertexIndex].x);
					if (mesh->mVertices[vertexIndex].y > 15.0f && teren)
						glColor4f(0.42, 0.61, 0.345,1.0f);
					else if ((mesh->mVertices[vertexIndex].y < 15.0f && mesh->mVertices[vertexIndex].y > -2.0f)&& teren)
						glColor4f(0.34, 0.49, 0.27,1.0f);
					else if ( mesh->mVertices[vertexIndex].y < -2.0f && teren)
						glColor4f(0.27, 0.39, 0.22, 1.0f);
					glVertex3fv(&mesh->mVertices[vertexIndex].x);
			}
			glEnd();
		}
	}
	for (n = 0; n < nd->mNumChildren; ++n)
		recursive_render(sc, nd->mChildren[n], scale, teren);
	
	glPopMatrix();
}


void drawAiScene(const aiScene* scene, double skala, int teren)
{
	recursive_render(scene, scene->mRootNode, skala, teren);
}


void walec(double r, double h, float iks, float igrek, float zet,float szaro)
{
	double x, y, alpha, PI = 3.14;
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(-1, 0, 0);
	glColor3d(szaro, szaro, szaro);
	glVertex3d(0 + iks, 0 + igrek, 0 + zet);
	for (alpha = 0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(0 + iks, y + igrek, x + zet);
	}
	glEnd();
	
	glBegin(GL_QUAD_STRIP);
	for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 8.0)
	{
		glNormal3f(0, sin(alpha), cos(alpha));
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(0 + iks, y + igrek, x + zet);
		glVertex3d(h + iks, y + igrek, x + zet);
	}
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	
	glVertex3d(h + iks, 0 + igrek, 0 + zet);
	for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 8.0)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(h + iks, y + igrek, x + zet);
	}
	glEnd();
}

void podloze(float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_POLYGON);
	glNormal3d(0, 1, 0);
	glVertex3f(-100, 0, 100);
	glVertex3f(100, 0, 100);
	glVertex3f(100, 0, -100);
	glVertex3f(-100, 0, -100);



	glEnd();
}

// WALLE START

void tyl()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glColor3f(0.9f, 0.7f, 0.3f);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); // W≥πcz teksturowanie

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(0.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2d(0.0, 1.0); glVertex3f(0, 10, 0);
	glTexCoord2d(1.0, 0.0); glVertex3f(10, 0, 0);
	glTexCoord2d(1.0, 1.0); glVertex3f(10, 10, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0, 5, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 8.5, 1.5);
	glVertex3f(0, 4.5, 2);
	glVertex3f(0, 1, 1.5);
	glVertex3f(0, 0, 0);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1, 5, 0);
	glVertex3f(1, 10, 0);
	glVertex3f(1, 8.5, 1.5);
	glVertex3f(1, 4.5, 2);
	glVertex3f(1, 1, 1.5);
	glVertex3f(1, 0, 0);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 10, 0);
	glVertex3f(1, 10, 0);
	glVertex3f(0, 8.5, 1.5);
	glVertex3f(1, 8.5, 1.5);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0, 4.5, 2);
	glVertex3f(1, 4.5, 2);
	glVertex3f(0, 1, 1.5);
	glVertex3f(1, 1, 1.5);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	/*glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 10, 0);
	glVertex3f(1, 10, 0);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0, 8.5, 1.5);
	glVertex3f(1, 8.5, 1.5);
	glVertex3f(0, 4.5, 2);
	glVertex3f(1, 4.5, 2);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 1, 1.5);
	glVertex3f(1, 1, 1.5);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);*/

	glEnd();

	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(9, 5, 0);
	glVertex3f(9, 10, 0);
	glVertex3f(9, 8.5, 1.5);
	glVertex3f(9, 4.5, 2);
	glVertex3f(9, 1, 1.5);
	glVertex3f(9, 0, 0);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(10, 5, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(10, 8.5, 1.5);
	glVertex3f(10, 4.5, 2);
	glVertex3f(10, 1, 1.5);
	glVertex3f(10, 0, 0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(9, 10, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(9, 8.5, 1.5);
	glVertex3f(10, 8.5, 1.5);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(9, 4.5, 2);
	glVertex3f(10, 4.5, 2);
	glVertex3f(9, 1, 1.5);
	glVertex3f(10, 1, 1.5);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(9, 0, 0);
	glVertex3f(10, 0, 0);
	glEnd();

	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1, 10, 0);
	glVertex3f(9, 10, 0);
	glVertex3f(1, 8.5, 1.5);
	glVertex3f(9, 8.5, 1.5);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glEnd();

	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(4.5, 2, 1);
	glVertex3f(5.5, 2, 1);
	glVertex3f(4.5, 8, 1);
	glVertex3f(5.5, 8, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(4.5, 2, 0);
	glVertex3f(4.5, 2, 1);
	glVertex3f(4.5, 8, 0);
	glVertex3f(4.5, 8, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(5.5, 2, 0);
	glVertex3f(5.5, 2, 1);
	glVertex3f(5.5, 8, 0);
	glVertex3f(5.5, 8, 1);
	glEnd();

	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(4.5, 2, 0);
	glVertex3f(4.5, 2, 1);
	glVertex3f(5.5, 2, 0);
	glVertex3f(5.5, 2, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(4.5, 8, 0);
	glVertex3f(4.5, 8, 1);
	glVertex3f(5.5, 8, 0);
	glVertex3f(5.5, 8, 1);
	glEnd();



	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(3, 2, 1);
	glVertex3f(4, 2, 1);
	glVertex3f(3, 8, 1);
	glVertex3f(4, 8, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(3, 2, 0);
	glVertex3f(3, 2, 1);
	glVertex3f(3, 8, 0);
	glVertex3f(3, 8, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(4, 2, 0);
	glVertex3f(4, 2, 1);
	glVertex3f(4, 8, 0);
	glVertex3f(4, 8, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(3, 2, 0);
	glVertex3f(3, 2, 1);
	glVertex3f(4, 2, 0);
	glVertex3f(4, 2, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(3, 8, 0);
	glVertex3f(3, 8, 1);
	glVertex3f(4, 8, 0);
	glVertex3f(4, 8, 1);
	glEnd();












	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(6, 2, 1);
	glVertex3f(7, 2, 1);
	glVertex3f(6, 8, 1);
	glVertex3f(7, 8, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(6, 2, 0);
	glVertex3f(6, 2, 1);
	glVertex3f(6, 8, 0);
	glVertex3f(6, 8, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(7, 2, 0);
	glVertex3f(7, 2, 1);
	glVertex3f(7, 8, 0);
	glVertex3f(7, 8, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(6, 2, 0);
	glVertex3f(6, 2, 1);
	glVertex3f(7, 2, 0);
	glVertex3f(7, 2, 1);
	glEnd();
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(6, 8, 0);
	glVertex3f(6, 8, 1);
	glVertex3f(7, 8, 0);
	glVertex3f(7, 8, 1);
	glEnd();

	
}
void boki()
{
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glColor3f(0.9f, 0.7f, 0.3f);
	glColor3f(1,1,1);
	glBegin(GL_TRIANGLE_STRIP);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2d(1.0, 1.0); glVertex3f(0, 10, 0);
	glTexCoord2d(0.0, 0.0); glVertex3f(0, 0, -9);
	glTexCoord2d(0.0, 1.0);  glVertex3f(0, 10, -9);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0, 0.0); glVertex3f(10, 0, 0);
	glTexCoord2d(1.0, 1.0); glVertex3f(10, 10, 0);
	glTexCoord2d(0.0, 0.0); glVertex3f(10, 0, -9);
	glTexCoord2d(0.0, 1.0); glVertex3f(10, 10, -9);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5, 1.5, -1);
	glVertex3f(-0.5, 5.5, -1);
	glVertex3f(-0.5, 1.5, -7.5);
	glVertex3f(-0.5, 7.5, -7.5);
	glEnd();

	//glColor3f(1.0f, 0.5f, 0.5f);
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 1.5, -1);
	glVertex3f(-0.5, 1.5, -1);
	glVertex3f(0, 5.5, -1);
	glVertex3f(-0.5, 5.5, -1);
	glEnd();
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0, 1.5, -7.5);
	glVertex3f(-0.5, 1.5, -7.5);
	glVertex3f(0, 7.5, -7.5);
	glVertex3f(-0.5, 7.5, -7.5);
	glEnd();
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 5.5, -1);
	glVertex3f(-0.5, 5.5, -1);
	glVertex3f(0, 7.5, -7.5);
	glVertex3f(-0.5, 7.5, -7.5);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0, 1.5, -1);
	glVertex3f(-0.5, 1.5, -1);
	glVertex3f(0, 1.5, -7.5);
	glVertex3f(-0.5, 1.5, -7.5);
	glEnd();


	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(10.5, 1.5, -1);
	glVertex3f(10.5, 5.5, -1);
	glVertex3f(10.5, 1.5, -7.5);
	glVertex3f(10.5, 7.5, -7.5);
	glEnd();

	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(10, 1.5, -1);
	glVertex3f(10.5, 1.5, -1);
	glVertex3f(10, 5.5, -1);
	glVertex3f(10.5, 5.5, -1);
	glEnd();
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(10, 1.5, -7.5);
	glVertex3f(10.5, 1.5, -7.5);
	glVertex3f(10, 7.5, -7.5);
	glVertex3f(10.5, 7.5, -7.5);
	glEnd();
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(10, 5.5, -1);
	glVertex3f(10.5, 5.5, -1);
	glVertex3f(10, 7.5, -7.5);
	glVertex3f(10.5, 7.5, -7.5);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(10, 1.5, -1);
	glVertex3f(10.5, 1.5, -1);
	glVertex3f(10, 1.5, -7.5);
	glVertex3f(10.5, 1.5, -7.5);
	glEnd();

	walec(0.75, 0.5, -0.5, 7, -2, 0.4);
	walec(0.75, 0.5, 10, 7, -2, 0.4);

	
}
void przod(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.8f, 0.6f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0, 8, -9);
	glVertex3f(0, 10, -9);
	glVertex3f(10, 8, -9);
	glVertex3f(10, 10, -9);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glColor3f(1,1,1);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2d(0.0, 0.0); glVertex3f(1.5, 8, -10);
	glTexCoord2d(0.0, 1.0); glVertex3f(1.5, 10, -10);
	glTexCoord2d(2, 0.0); glVertex3f(8.5, 8, -10);
	glTexCoord2d(2, 1.0); glVertex3f(8.5, 10, -10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	
	
	


	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.5, 8, -10);
	glVertex3f(1.5, 10, -10);
	glVertex3f(1.5, 8, -9);
	glVertex3f(1.5, 10, -9);
	glEnd();
	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(8.5, 8, -10);
	glVertex3f(8.5, 10, -10);
	glVertex3f(8.5, 8, -9);
	glVertex3f(8.5, 10, -9);
	glEnd();
	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(1.5, 8, -9);
	glVertex3f(1.5, 8, -10);
	glVertex3f(8.5, 8, -9);
	glVertex3f(8.5, 8, -10);
	glEnd();
}
void dach(void)
{
	

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.9f, 0.7f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, -1, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(0, 10, -10);
	glVertex3f(10, 10, -10);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexCoord2d(0.0, 1.0); glVertex3f(0, 10.5, 0);
	glTexCoord2d(1.0, 1.0); glVertex3f(10, 10.5, 0);
	glTexCoord2d(0.0, 0.0); glVertex3f(0, 10.5, -10);
	glTexCoord2d(1.0, 0.0); glVertex3f(10, 10.5, -10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glColor3f(0.9f, 0.7f, 0.3f);
	
	



	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 10.5, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(10, 10.5, 0);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0, 10, -10);
	glVertex3f(0, 10.5, -10);
	glVertex3f(10, 10, -10);
	glVertex3f(10, 10.5, -10);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 10.5, 0);
	glVertex3f(0, 10, -10);
	glVertex3f(0, 10.5, -10);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(10, 10, 0);
	glVertex3f(10, 10.5, 0);
	glVertex3f(10, 10, -10);
	glVertex3f(10, 10.5, -10);
	glEnd();



	//poczatek szyi
	walec(0.5, 0.25, 4.25, 10.65, -3, 0.4);
	walec(0.5, 0.25, 5.5, 10.65, -3, 0.4);

	
}
void podloga(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(0, 0, -9);
	glVertex3f(10, 0, -9);
	glEnd();
}
void brzusio(void)
{
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.9f, 0.7f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 0.0f,1.0f);
	glVertex3f(0, 0, -9);
	glVertex3f(0, 8, -9);
	glVertex3f(10, 0, -9);
	glVertex3f(10, 8, -9);
	glEnd();
	
	
	
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,1,1);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2d(0.0, 0.0); glVertex3f(0, 0, -10);
	glTexCoord2d(0.0, 1.0); glVertex3f(0, 8, -10);
	glTexCoord2d(1.0, 0.0); glVertex3f(10, 0, -10);
	glTexCoord2d(1.0, 1.0); glVertex3f(10, 8, -10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.9f, 0.7f, 0.3f);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0, 0, -9);
	glVertex3f(0, 8, -9);
	glVertex3f(0, 0, -10);
	glVertex3f(0, 8, -10);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(10, 0, -9);
	glVertex3f(10, 8, -9);
	glVertex3f(10, 0, -10);
	glVertex3f(10, 8, -10);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0, 0, -9);
	glVertex3f(0, 0, -10);
	glVertex3f(10, 0, -9);
	glVertex3f(10, 0, -10);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 8, -9);
	glVertex3f(0, 8, -10);
	glVertex3f(10, 8, -9);
	glVertex3f(10, 8, -10);
	glEnd();
	
}

void szyja()
{
	glPushMatrix();
	glTranslatef(5, 11, -3);
	glRotatef(30, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	walec(0.5, 2, 0, 0, 0, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.25, 12.15, -5);
	walec(0.5, 1.5, 0, 0, 0, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 12.15, -5);
	glRotatef(120, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	walec(0.5, 2, 0, 0, 0, 0.4);
	glPopMatrix();
}

void szyja2()
{
	glPushMatrix();
	glTranslatef(5, 13.5, -4);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	walec(0.25, 2, 0, 0, 0, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 15.5, -3.5);
	glRotatef(90, 0, 1, 0);
	walec(0.35, 3, 0, 0, 0, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 15.5, -5);
	walec(0.35, 5, 0, 0, 0, 0.4);
	glPopMatrix();
}

void oczko1(float iks, float igrek, float zet)
{
	glPushMatrix();
	glTranslatef(iks, igrek, zet);
	glRotatef(180, 0, 1, 0);


	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	walec(0.85, 2, -0.35, 0.2, 0.7, 0.4);
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	glVertex3f(3.25 / 2, 3.5 / 2, 0);
	glVertex3f(4 / 2, 3.3 / 2, 0);
	glVertex3f(4.5 / 2, 2.9 / 2, 0);
	glVertex3f(4.65 / 2, 2.4 / 2, 0);
	glVertex3f(4.4 / 2, -0.2 / 2, 0);
	glVertex3f(3.3 / 2, -1.6 / 2, 0);
	glVertex3f(2 / 2, -3.0f / 2, 0);
	glVertex3f(-0.3 / 2, -3.75 / 2, 0);
	glVertex3f(-2.2 / 2, -3.25 / 2, 0);
	glVertex3f(-4.2 / 2, -1.1 / 2, 0);
	glVertex3f(-4.2 / 2, 1.1 / 2, 0);
	glVertex3f(-3.75 / 2, 1.9 / 2, 0);
	glVertex3f(-3 / 2, 2.3 / 2, 0);
	glVertex3f(3.25 / 2, 3.5 / 2, 0);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(-1, 1, 0);
	glVertex3f(3.25 / 2, 3.5 / 2, 0);
	glVertex3f(3.25 / 2, 3.5 / 2, -3.5);
	glVertex3f(4 / 2, 3.3 / 2, 0);
	glVertex3f(4 / 2, 3.3 / 2, -3.5);
	glVertex3f(4.5 / 2, 2.9 / 2, 0);
	glVertex3f(4.5 / 2, 2.9 / 2, -3.5);
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(-1, 0, 0);
	glVertex3f(4.65 / 2, 2.4 / 2, 0);
	glVertex3f(4.65 / 2, 2.4 / 2, -3.5);
	glVertex3f(4.4 / 2, -0.2 / 2, 0);
	glVertex3f(4.4 / 2, -0.2 / 2, -3.5);
	glVertex3f(3.3 / 2, -1.6 / 2, 0);
	glVertex3f(3.3 / 2, -1.6 / 2, -3.5);

	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0, -1, 0);
	glVertex3f(2 / 2, -3.0f / 2, 0);
	glVertex3f(2 / 2, -3.0f / 2, -3.5);
	glVertex3f(-0.3 / 2, -3.75 / 2, 0);
	glVertex3f(-0.3 / 2, -3.75 / 2, -3.5);
	glVertex3f(-2.2 / 2, -3.25 / 2, 0);
	glVertex3f(-2.2 / 2, -3.25 / 2, -3.5);

	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(1, 1, 0);
	glVertex3f(-4.2 / 2, -1.1 / 2, 0);
	glVertex3f(-4.2 / 2, -1.1 / 2, -3.5);
	glVertex3f(-4.2 / 2, 1.1 / 2, 0);
	glVertex3f(-4.2 / 2, 1.1 / 2, -3.5);
	glVertex3f(-3.75 / 2, 1.9 / 2, 0);
	glVertex3f(-3.75 / 2, 1.9 / 2, -3.5);

	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0, 1, 0);
	glVertex3f(-3 / 2, 2.3 / 2, 0);
	glVertex3f(-3 / 2, 2.3 / 2, -3.5);

	glVertex3f(3.25 / 2, 3.5 / 2, 0);
	glVertex3f(3.25 / 2, 3.5 / 2, -3.5);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, -3.5);
	glVertex3f(3.25 / 2, 3.5 / 2, -3.5);
	glVertex3f(4 / 2, 3.3 / 2, -3.5);
	glVertex3f(4.5 / 2, 2.9 / 2, -3.5);
	glVertex3f(4.65 / 2, 2.4 / 2, -3.5);
	glVertex3f(4.4 / 2, -0.2 / 2, -3.5);
	glVertex3f(3.3 / 2, -1.6 / 2, -3.5);
	glVertex3f(2 / 2, -3.0f / 2, -3.5);
	glVertex3f(-0.3 / 2, -3.75 / 2, -3.5);
	glVertex3f(-2.2 / 2, -3.25 / 2, -3.5);
	glVertex3f(-4.2 / 2, -1.1 / 2, -3.5);
	glVertex3f(-4.2 / 2, 1.1 / 2, -3.5);
	glVertex3f(-3.75 / 2, 1.9 / 2, -3.5);
	glVertex3f(-3 / 2, 2.3 / 2, -3.5);
	glVertex3f(3.25 / 2, 3.5 / 2, -3.5);
	glEnd();



	glColor3f(0.25, 0.25, 0.25);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, -7);

	glVertex3f(1.3, 1.4, -7);
	glVertex3f(1.5, 1.25, -7);

	glVertex3f(1.9, -0.45, -7);
	glVertex3f(1.7, -0.7, -7);

	glVertex3f(-0.9, -1.3, -7);
	glVertex3f(-1.2, -1, -7);

	glVertex3f(-1.55, 0.55, -7);
	glVertex3f(-1.45, 0.8, -7);

	glVertex3f(1.3, 1.4, -7);
	glEnd();
	glColor3f(0.25, 0.25, 0.25);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1, 0, 0);
	glVertex3f(1.3, 1.4, -7);
	glVertex3f(1.3, 1.4, -3.5);
	glVertex3f(1.5, 1.25, -7);
	glVertex3f(1.5, 1.25, -3.5);
	glVertex3f(1.9, -0.45, -7);
	glVertex3f(1.9, -0.45, -3.5);
	glVertex3f(1.7, -0.7, -7);
	glVertex3f(1.7, -0.7, -3.5);
	glNormal3f(0, -1, 0);
	glVertex3f(-0.9, -1.3, -7);
	glVertex3f(-0.9, -1.3, -3.5);
	glNormal3f(1, 0, 0);
	glVertex3f(-1.2, -1, -7);
	glVertex3f(-1.2, -1, -3.5);
	glVertex3f(-1.55, 0.55, -7);
	glVertex3f(-1.55, 0.55, -3.5);
	glNormal3f(0, 1, 0);
	glVertex3f(-1.45, 0.8, -7);
	glVertex3f(-1.45, 0.8, -3.5);
	glVertex3f(1.3, 1.4, -7);
	glVertex3f(1.3, 1.4, -3.5);
	glEnd();


	glPopMatrix();
}


void pudelko()
{
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.25, 0);
	glVertex3f(3, 0, 0);
	glVertex3f(3, 0.25, 0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, -1.5);
	glVertex3f(0, 0.25, -1.5);
	glVertex3f(3, 0, -1.5);
	glVertex3f(3, 0.25, -1.5);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.25, 0);
	glVertex3f(0, 0, -1.5);
	glVertex3f(0, 0.25, -1.5);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1, 0, 0);
	glVertex3f(3, 0, 0);
	glVertex3f(3, 0.25, 0);
	glVertex3f(3, 0, -1.5);
	glVertex3f(3, 0.25, -1.5);
	glEnd();

	
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, -1, 0);
	glTexCoord2d(0.0, 1.0); glVertex3f(0, 0, 0);
	glTexCoord2d(0.0, 0.0); glVertex3f(0, 0, -1.5);
	glTexCoord2d(1.0, 1.0); glVertex3f(3, 0, 0);
	glTexCoord2d(1.0, 0.0); glVertex3f(3, 0, -1.5);
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 1, 0);
	glVertex3f(0, 0.25, 0);
	glVertex3f(0, 0.25, -1.5);
	glVertex3f(3, 0.25, 0);
	glVertex3f(3, 0.25, -1.5);
	glEnd();

	
	
	
	
	glDisable(GL_TEXTURE_2D);
}

void gasienica()
{

	glColor3f(0.25, 0.25, 0.25);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(1, 0, 0);
	glVertex3f(-1, -4, -5);
	glVertex3f(-1, -4, -9.5);
	glVertex3f(-1, -2.2, -10.05);
	glVertex3f(-1, -1.5, -9.6);
	glVertex3f(-1, 3.5, -4.25);
	glVertex3f(-1, 3.5, -4);
	glVertex3f(-1, 2.5, -2.5);
	glVertex3f(-1, 0, -0.5);
	glVertex3f(-1, -1, 0.35);
	glVertex3f(-1, -2.5, 0.55);
	glVertex3f(-1, -4, 0);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1.5, -4, -5);
	glVertex3f(-1.5, -4, -9.5);
	glVertex3f(-1.5, -2.2, -10.05);
	glVertex3f(-1.5, -1.5, -9.6);
	glVertex3f(-1.5, 3.5, -4.25);
	glVertex3f(-1.5, 3.5, -4);
	glVertex3f(-1.5, 2.5, -2.5);
	glVertex3f(-1.5, 0, -0.5);
	glVertex3f(-1.5, -1, 0.35);
	glVertex3f(-1.5, -2.5, 0.55);
	glVertex3f(-1.5, -4, 0);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 1, 0);
	glVertex3f(-1, -4, -5);
	glVertex3f(-1.5, -4, -5);
	glVertex3f(-1, -4, -9.5);
	glVertex3f(-1.5, -4, -9.5);
	glVertex3f(-1, -2.2, -10.05);
	glVertex3f(-1.5, -2.2, -10.05);
	glVertex3f(-1, -1.5, -9.6);
	glVertex3f(-1.5, -1.5, -9.6);
	glVertex3f(-1, 3.5, -4.25);
	glVertex3f(-1.5, 3.5, -4.25);
	glVertex3f(-1, 3.5, -4);
	glVertex3f(-1.5, 3.5, -4);
	glVertex3f(-1, 2.5, -2.5);
	glVertex3f(-1.5, 2.5, -2.5);
	glVertex3f(-1, 0, -0.5);
	glVertex3f(-1.5, 0, -0.5);
	glVertex3f(-1, -1, 0.35);
	glVertex3f(-1.5, -1, 0.35);
	glVertex3f(-1, -2.5, 0.55);
	glVertex3f(-1.5, -2.5, 0.55);
	glVertex3f(-1, -4, 0);
	glVertex3f(-1.5, -4, 0);
	glEnd();



	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(1, 0, 0);
	glVertex3f(-2.5, -4, -5);
	glVertex3f(-2.5, -4, -9.5);
	glVertex3f(-2.5, -2.2, -10.05);
	glVertex3f(-2.5, -1.5, -9.6);
	glVertex3f(-2.5, 3.5, -4.25);
	glVertex3f(-2.5, 3.5, -4);
	glVertex3f(-2.5, 2.5, -2.5);
	glVertex3f(-2.5, 0, -0.5);
	glVertex3f(-2.5, -1, 0.35);
	glVertex3f(-2.5, -2.5, 0.55);
	glVertex3f(-2.5, -4, 0);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(-1, 0, 0);
	glVertex3f(-3, -4, -5);
	glVertex3f(-3, -4, -9.5);
	glVertex3f(-3, -2.2, -10.05);
	glVertex3f(-3, -1.5, -9.6);
	glVertex3f(-3, 3.5, -4.25);
	glVertex3f(-3, 3.5, -4);
	glVertex3f(-3, 2.5, -2.5);
	glVertex3f(-3, 0, -0.5);
	glVertex3f(-3, -1, 0.35);
	glVertex3f(-3, -2.5, 0.55);
	glVertex3f(-3, -4, 0);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 1, 0);
	glVertex3f(-2.5, -4, -5);
	glVertex3f(-3, -4, -5);
	glVertex3f(-2.5, -4, -9.5);
	glVertex3f(-3, -4, -9.5);
	glVertex3f(-2.5, -2.2, -10.05);
	glVertex3f(-3, -2.2, -10.05);
	glVertex3f(-2.5, -1.5, -9.6);
	glVertex3f(-3, -1.5, -9.6);
	glVertex3f(-2.5, 3.5, -4.25);
	glVertex3f(-3, 3.5, -4.25);
	glVertex3f(-2.5, 3.5, -4);
	glVertex3f(-3, 3.5, -4);
	glVertex3f(-2.5, 2.5, -2.5);
	glVertex3f(-3, 2.5, -2.5);
	glVertex3f(-2.5, 0, -0.5);
	glVertex3f(-3, 0, -0.5);
	glVertex3f(-2.5, -1, 0.35);
	glVertex3f(-3, -1, 0.35);
	glVertex3f(-2.5, -2.5, 0.55);
	glVertex3f(-3, -2.5, 0.55);
	glVertex3f(-2.5, -4, 0);
	glVertex3f(-3, -4, 0);
	glEnd();




	glPushMatrix();
	glTranslatef(-3.5, -4, 0);
	glRotatef(-10, 1, 0, 0);
	glColor3f(0.1 + kolorGasienicy, 0.1 + kolorGasienicy, 0.1 + kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -4.25, -1.6);
	glColor3f(0.3 - kolorGasienicy, 0.3 - kolorGasienicy, 0.3 - kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -4.25, -3.2);
	glColor3f(0.1 + kolorGasienicy, 0.1 + kolorGasienicy, 0.1 + kolorGasienicy);
	pudelko();
	glPopMatrix();
	glColor3f(0.3 - kolorGasienicy, 0.3 - kolorGasienicy, 0.3 - kolorGasienicy);
	glPushMatrix();
	glTranslatef(-3.5, -4.25, -4.8);

	pudelko();
	glPopMatrix();
	glColor3f(0.3 - kolorGasienicy, 0.3 - kolorGasienicy, 0.3 - kolorGasienicy);
	glPushMatrix();

	glTranslatef(-3.5, -4.25, -6.4);
	glColor3f(0.1 + kolorGasienicy, 0.1 + kolorGasienicy, 0.1 + kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -4.25, -8);
	glRotatef(7, 1, 0, 0);
	glColor3f(0.3 - kolorGasienicy, 0.3 - kolorGasienicy, 0.3 - kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -3.95, -9.7);
	glRotatef(65, 1, 0, 0);
	glColor3f(0.1 + kolorGasienicy, 0.1 + kolorGasienicy, 0.1 + kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -2.3, -10.2);
	glRotatef(120, 1, 0, 0);
	glColor3f(0.3 - kolorGasienicy, 0.3 - kolorGasienicy, 0.3 - kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -0.9, -9.25);
	glRotatef(135, 1, 0, 0);
	glColor3f(0.1 + kolorGasienicy, 0.1 + kolorGasienicy, 0.1 + kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 0.35, -8);
	glRotatef(135, 1, 0, 0);
	glColor3f(0.3 - kolorGasienicy, 0.3 - kolorGasienicy, 0.3 - kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 1.6, -6.75);
	glRotatef(140, 1, 0, 0);
	glColor3f(0.1 + kolorGasienicy, 0.1 + kolorGasienicy, 0.1 + kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 2.7, -5.5);
	glRotatef(145, 1, 0, 0);
	glColor3f(0.3 - kolorGasienicy, 0.3 - kolorGasienicy, 0.3 - kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 3.6, -3.9);
	glRotatef(210, 1, 0, 0);
	glColor3f(0.1 + kolorGasienicy, 0.1 + kolorGasienicy, 0.1 + kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 2.7, -2.45);
	glRotatef(225, 1, 0, 0);
	glColor3f(0.3 - kolorGasienicy, 0.3 - kolorGasienicy, 0.3 - kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 1.5, -1.25);
	glRotatef(230, 1, 0, 0);
	glColor3f(0.1 + kolorGasienicy, 0.1 + kolorGasienicy, 0.1 + kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, 0.25, -0.15);
	glRotatef(245, 1, 0, 0);
	glColor3f(0.3 - kolorGasienicy, 0.3 - kolorGasienicy, 0.3 - kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -1.2, 0.5);
	glRotatef(260, 1, 0, 0);
	glColor3f(0.1 + kolorGasienicy, 0.1 + kolorGasienicy, 0.1 + kolorGasienicy);
	pudelko();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5, -2.5, 0.75);
	glRotatef(295, 1, 0, 0);
	glColor3f(0.3 - kolorGasienicy, 0.3 - kolorGasienicy, 0.3 - kolorGasienicy);
	pudelko();
	glPopMatrix();
}

void kola()
{
	//duze
	glPushMatrix();
	glTranslatef(-3.5, -1.55, -2.25);
	glRotatef(-obrotSrubek, 1, 0, 0);
	glTranslatef(3.5, 1.55, 2.25);
		glPushMatrix();
			glTranslatef(-3.5, -1.55, -2.25);
			walec(2.5, 3, 0, 0, 0, 0.4);

			glPushMatrix();
				glTranslatef(-0.125, 2, 0);
				walec(0.25, 3.25, 0, 0, 0, 0.35);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, -2, 0);
				walec(0.25, 3.25, 0, 0, 0, 0.35);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, 0, 2);
				walec(0.25, 3.25, 0, 0, 0, 0.35);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, 0, -2);
				walec(0.25, 3.25, 0, 0, 0, 0.35);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, 1.4, 1.4);
				walec(0.25, 3.25, 0, 0, 0, 0.35);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, -1.4, -1.4);
				walec(0.25, 3.25, 0, 0, 0, 0.35);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, 1.4, -1.4);
				walec(0.25, 3.25, 0, 0, 0, 0.35);
			glPopMatrix();


			glPushMatrix();
				glTranslatef(-0.125, -1.4, 1.4);
				walec(0.25, 3.25, 0, 0, 0, 0.35);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	



	//mniejsze
	glPushMatrix();
	glTranslatef(-3.5, -2.5, -8.25);
	glRotatef(-obrotSrubek, 1, 0, 0);
	glTranslatef(3.5, 2.5, 8.25);
		glPushMatrix();
		glTranslatef(-3.5, -2.5, -8.25);
		walec(1.5, 3, 0, 0, 0, 0.5);
			glPushMatrix();
				glTranslatef(-0.125, 1, 0);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, -1, 0);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, 0, 1);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, 0, -1);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();


	
	//najmniejsze dolne
	glPushMatrix();
	glTranslatef(-3.5, 0.25, -6.25);
	glRotatef(-obrotSrubek, 1, 0, 0);
	glTranslatef(3.5, -0.25, 6.25);
		glPushMatrix();
		glTranslatef(-3.5, 0.25, -6.25);
		walec(1, 3, 0, 0, 0, 0.4);
			glPushMatrix();
				glTranslatef(-0.125, 0.5, 0);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, -0.5, 0);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, 0, 0.5);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, 0, -0.5);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();





	//najmniejsze gorne
	glPushMatrix();
	glTranslatef(-3.5, 2.25, -4);
	glRotatef(-obrotSrubek, 1, 0, 0);
	glTranslatef(3.5, -2.25, 4);
		glPushMatrix();
		glTranslatef(-3.5, 2.25, -4);
		walec(1, 3, 0, 0, 0, 0.5);
			glPushMatrix();
				glTranslatef(-0.125, 0.5, 0);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, -0.5, 0);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, 0, 0.5);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.125, 0, -0.5);
				walec(0.25, 3.25, 0, 0, 0, 0.45);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();



}
//11.04
void polwalca(double r, double h, float iks, float igrek, float zet, float szaro)
{
	double x, y, alpha, PI = 3.14;
	glBegin(GL_TRIANGLE_FAN);
	//glColor3d(szaro, szaro, szaro);
	glColor3f(0.8f, 0.6f, 0.2f);
	glVertex3d(0 + iks, 0 + igrek, 0 + zet);
	for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(0 + iks, y + igrek, x + zet);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (alpha = 0.0; alpha <= PI; alpha += PI / 8.0)
	{
		glNormal3f(0, sin(alpha), cos(alpha));
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(0 + iks, y + igrek, x + zet);
		glVertex3d(h + iks, y + igrek, x + zet);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(h + iks, 0 + igrek, 0 + zet);
	for (alpha = 0; alpha <= PI; alpha += PI / 8.0)
	{
		x = r * sin(alpha);
		y = r * cos(alpha);
		glVertex3d(h + iks, y + igrek, x + zet);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
	//glColor3f(0.9f, 0.7f, 0.3f);
	glColor3f(1,1,1);
	glBegin(GL_TRIANGLE_STRIP);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glNormal3f(0, 0, -1);
	glTexCoord2d(1, 1.0); glVertex3f(0, r, 0);
	glTexCoord2d(1, 0.0); glVertex3f(0, -r, 0);
	glTexCoord2d(0.0, 1.0);  glVertex3f(h, r, 0);
	glTexCoord2d(0.0, 0.0);  glVertex3f(h, -r, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	
	
	
}

void palec()
{
	glColor3f(0.45, 0.45, 0.45);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, 1);
	glVertex3f(-2, 9.5, -15);
	glVertex3f(-2, 9.25, -15);
	glVertex3f(-0.75, 9.5, -15);
	glVertex3f(-0.75, 9.25, -15);
	glEnd();
	glColor3f(0.45, 0.45, 0.45);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, -1);
	glVertex3f(-2, 9.5, -17);
	glVertex3f(-2, 9.25, -17);
	glVertex3f(-0.75, 9.5, -17);
	glVertex3f(-0.75, 9.25, -17);
	glEnd();
	glColor3f(0.45, 0.45, 0.45);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1, 0, 0);
	glVertex3f(-2, 9.5, -15);
	glVertex3f(-2, 9.5, -17);
	glVertex3f(-2, 9.25, -15);
	glVertex3f(-2, 9.25, -17);
	glEnd();
	glColor3f(0.45, 0.45, 0.45);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1, 0, 0);
	glVertex3f(-0.75, 9.5, -15);
	glVertex3f(-0.75, 9.5, -17);
	glVertex3f(-0.75, 9.25, -15);
	glVertex3f(-0.75, 9.25, -17);
	glEnd();
	glColor3f(0.45, 0.45, 0.45);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 1, 0);
	glVertex3f(-2, 9.5, -15);
	glVertex3f(-2, 9.5, -17);
	glVertex3f(-0.75, 9.5, -15);
	glVertex3f(-0.75, 9.5, -17);
	glEnd();
	glColor3f(0.45, 0.45, 0.45);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, -1, 0);
	glVertex3f(-2, 9.25, -15);
	glVertex3f(-2, 9.25, -17);
	glVertex3f(-2, 9.25, -15);
	glVertex3f(-2, 9.25, -17);
	glEnd();
}

void ramiona()
{
	glPushMatrix();
	//glTranslatef(0, -5.75, -5.75);
	glTranslatef(-1.25, 9-ramieY, -2.8-ramieZ);
	glRotatef(katRamion, 1, 0, 0);
	glTranslatef(1.25, -9, 2.8);

		glPushMatrix();
		glTranslatef(-1.25, 8, -2.5);
		glRotatef(90, 0, 0, 1);
		walec(0.6, 2.5, 0, 0, 0, 0.7);
		glPopMatrix();

		glColor3f(0.4, 0.4, 0.4);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3f(0, -1, 0);
		glVertex3f(-1.25, 9, -2.8);
		glVertex3f(0, 9, -2.8);
		glVertex3f(-1.25, 9, -2.2);
		glVertex3f(0, 9, -2.2);
		glEnd();
		glColor3f(0.4, 0.4, 0.4);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3f(0, 1, 0);
		glVertex3f(-1.25, 9.5, -2.8);
		glVertex3f(0, 9.5, -2.8);
		glVertex3f(-1.25, 9.5, -2.2);
		glVertex3f(0, 9.5, -2.2);
		glEnd();
		glColor3f(0.4, 0.4, 0.4);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3f(0, 0, -1);
		glVertex3f(-1.25, 9.5, -2.8);
		glVertex3f(-1.25, 9, -2.8);
		glVertex3f(0, 9.5, -2.8);
		glVertex3f(0, 9, -2.8);
		glEnd();
		glColor3f(0.4, 0.4, 0.4);
		glBegin(GL_TRIANGLE_STRIP);
		glNormal3f(0, 0, 1);
		glVertex3f(-1.25, 9.5, -2.2);
		glVertex3f(-1.25, 9, -2.2);
		glVertex3f(0, 9.5, -2.2);
		glVertex3f(0, 9, -2.2);
		glEnd();

		glPushMatrix();
		glTranslatef(-1.85, 9.25, -2.5);
		glRotatef(90, 0, 0, 1);
		glRotatef(90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		polwalca(1.25, 7, 0, 0, 0, 0.8);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-1.25, 9.25, -9.5);
		glRotatef(90, 0, 1, 0);
		walec(0.6, 1, 0, 0, 0, 0.6);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, -przedluzenie);
			glPushMatrix();
			glTranslatef(-1.25, 9.25, -2.5);
			glRotatef(90, 0, 1, 0);
			walec(0.5, 11, 0, 0, 0, 0.7);
			glPopMatrix();
		
			glPushMatrix();
			glTranslatef(-1.25, 9.25, -13);
			glRotatef(90, 0, 1, 0);
			walec(0.4, 1.5, 0, 0, 0, 0.6);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.75-0.5, 8.8+0.45, -14.5);
			glRotatef(dlonObr, 0, 0, 1);
			glRotatef(dlonObr2, -1, 0, 0);
			glTranslatef(0.75+0.5, -8.8-0.45, 14.5);

			//AK
			//glPushMatrix();
			//glTranslatef(7, 9, -21);
			////glRotatef(90, 1, 0, 0);
			//glRotatef(180, 0, 1, 0);
			//glRotatef(-90, 0, 0, 1);
			//glColor3f(0.4, 0.4, 0.4);
			//drawAiScene(g_scene2, 1.5);
			//glPopMatrix();
			
				glColor3f(0.25, 0.25, 0.25);
				glBegin(GL_TRIANGLE_STRIP);
				glNormal3f(0, 0, 1);
				glVertex3f(-1.75, 9.7, -14.5);
				glVertex3f(-1.75, 8.8, -14.5);
				glVertex3f(-0.75, 9.7, -14.5);
				glVertex3f(-0.75, 8.8, -14.5);
				glEnd();
				glColor3f(0.25, 0.25, 0.25);
				glBegin(GL_TRIANGLE_STRIP);
				glNormal3f(0, 0, -1);
				glVertex3f(-1.75, 9.7, -15.5);
				glVertex3f(-1.75, 8.8, -15.5);
				glVertex3f(-0.75, 9.7, -15.5);
				glVertex3f(-0.75, 8.8, -15.5);
				glEnd();
				glColor3f(0.25, 0.25, 0.25);
				glBegin(GL_TRIANGLE_STRIP);
				glNormal3f(-1, 0, 0);
				glVertex3f(-1.75, 9.7, -14.5);
				glVertex3f(-1.75, 9.7, -15.5);
				glVertex3f(-1.75, 8.8, -14.5);
				glVertex3f(-1.75, 8.8, -15.5);
				glEnd();
				glColor3f(0.25, 0.25, 0.25);
				glBegin(GL_TRIANGLE_STRIP);
				glNormal3f(1, 0, 0);
				glVertex3f(-0.75, 9.7, -14.5);
				glVertex3f(-0.75, 9.7, -15.5);
				glVertex3f(-0.75, 8.8, -14.5);
				glVertex3f(-0.75, 8.8, -15.5);
				glEnd();
				glColor3f(0.25, 0.25, 0.25);
				glBegin(GL_TRIANGLE_STRIP);
				glNormal3f(0, 1, 0);
				glVertex3f(-1.75, 9.7, -14.5);
				glVertex3f(-1.75, 9.7, -15.5);
				glVertex3f(-0.75, 9.7, -14.5);
				glVertex3f(-0.75, 9.7, -15.5);
				glEnd();
				glColor3f(0.25, 0.25, 0.25);
				glBegin(GL_TRIANGLE_STRIP);
				glNormal3f(0, -1, 0);
				glVertex3f(-1.75, 8.8, -14.5);
				glVertex3f(-1.75, 8.8, -15.5);
				glVertex3f(-0.75, 8.8, -14.5);
				glVertex3f(-0.75, 8.8, -15.5);
				glEnd();


				glPushMatrix();
				glTranslatef(-0.6, 0, 0);
				palec();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(-1.2, 9.5, -17);
				//glTranslatef(0.6, 0, -9.5);

				glRotatef(-30, 1, 0, 0);
				glScalef(1, 1, 0.5);
				glTranslatef(2, -9.5, 15);
				palec();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.8, 0, 0);
				palec();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(-2.6, 9.5, -17);
				glRotatef(-30, 1, 0, 0);
				glScalef(1, 1, 0.5);
				glTranslatef(2, -9.5, 15);
				palec();
				glPopMatrix();
				glPushMatrix();

				glTranslatef(-2, 9.25, -15.5);
				glRotatef(-30, 1, 0, 0);
				glScalef(1, 1, 0.5);
				glTranslatef(2, -9.5, 15);
				palec();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
//WALLE KONIEC

void pudlo()
{
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 30, 0);
	glVertex3f(30, 0, 0);
	glVertex3f(30, 30, 0);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, -30);
	glVertex3f(0, 30, -30);
	glVertex3f(30, 0, -30);
	glVertex3f(30, 30, -30);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(-1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 30, 0);
	glVertex3f(0, 0, -30);
	glVertex3f(0, 30, -30);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(1, 0, 0);
	glVertex3f(30, 0, 0);
	glVertex3f(30, 30, 0);
	glVertex3f(30, 0, -30);
	glVertex3f(30, 30, -30);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -30);
	glVertex3f(30, 0, 0);
	glVertex3f(30, 0, -30);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 1, 0);
	glVertex3f(0, 30, 0);
	glVertex3f(0, 30, -30);
	glVertex3f(30, 30, 0);
	glVertex3f(30, 30, -30);
	glEnd();
}




float odleglosc(float aX, float bX, float aZ, float bZ)
{
	return sqrt(pow((aX-bX),2)+pow(aZ-bZ,2));
}


bool kolizja(float zmianaX, float zmianaZ)
{
	if (Xpos > 0 && Zpos < 0)
	{
		if (odleglosc(Xpos + zmianaX, 260, Zpos + zmianaZ, -300) < (5 * sqrt(2) + 75))
			return true;
	}
	if (Xpos < 0 && Zpos > 0)
	{
		if (odleglosc(Xpos + zmianaX, -150, Zpos + zmianaZ, 150) < (5 * sqrt(2) + 12))
			return true;
	}
	if (odleglosc(Xpos + zmianaX, 0, Zpos + zmianaZ, -100) < (5*sqrt(2) + 10))
		return true;

	return false;
}

void pochylenie15stopni()
{
	if (Zpos < -100)
	{
		//if (nachylenie < 15)
		//nachylenie++;
		katp = kat;
		if (katp < 0)
			katp = 360 + katp;
		if (katp >= 0 && katp < 6)
		{
			nachylenieX = 15;
			nachylenieZ = 0;
		}
		if (katp >= 6 && katp < 12)
		{
			nachylenieX = 14;
			nachylenieZ = 1;
		}
		if (katp >= 12 && katp < 18)
		{
			nachylenieX = 13;
			nachylenieZ = 2;
		}
		if (katp >= 18 && katp < 24)
		{
			nachylenieX = 12;
			nachylenieZ = 3;
		}
		if (katp >= 24 && katp < 30)
		{
			nachylenieX = 11;
			nachylenieZ = 4;
		}
		if (katp >= 30 && katp < 36)
		{
			nachylenieX = 10;
			nachylenieZ = 5;
		}
		if (katp >= 36 && katp < 42)
		{
			nachylenieX = 9;
			nachylenieZ = 6;
		}
		if (katp >= 42 && katp < 48)
		{
			nachylenieX = 8;
			nachylenieZ = 7;
		}
		if (katp >= 48 && katp < 54)
		{
			nachylenieX = 7;
			nachylenieZ = 8;
		}
		if (katp >= 54 && katp < 60)
		{
			nachylenieX = 6;
			nachylenieZ = 9;
		}
		if (katp >= 60 && katp < 66)
		{
			nachylenieX = 5;
			nachylenieZ = 10;
		}
		if (katp >= 66 && katp < 72)
		{
			nachylenieX = 4;
			nachylenieZ = 11;
		}
		if (katp >= 72 && katp < 78)
		{
			nachylenieX = 3;
			nachylenieZ = 12;
		}
		if (katp >= 78 && katp < 84)
		{
			nachylenieX = 2;
			nachylenieZ = 13;
		}
		if (katp >= 84 && katp < 90)
		{
			nachylenieX = 1;
			nachylenieZ = 14;
		}
		if (katp >= 90 && katp < 96)
		{
			nachylenieX = 0;
			nachylenieZ = 15;
		}
		if (katp >= 96 && katp < 102)
		{
			nachylenieX = -1;
			nachylenieZ = 14;
		}
		if (katp >= 102 && katp < 108)
		{
			nachylenieX = -2;
			nachylenieZ = 13;
		}
		if (katp >= 108 && katp < 114)
		{
			nachylenieX = -3;
			nachylenieZ = 12;
		}
		if (katp >= 114 && katp < 120)
		{
			nachylenieX = -4;
			nachylenieZ = 11;
		}
		if (katp >= 120 && katp < 126)
		{
			nachylenieX = -5;
			nachylenieZ = 10;
		}
		if (katp >= 126 && katp < 132)
		{
			nachylenieX = -6;
			nachylenieZ = 9;
		}
		if (katp >= 132 && katp < 138)
		{
			nachylenieX = -7;
			nachylenieZ = 8;
		}
		if (katp >= 138 && katp < 144)
		{
			nachylenieX = -8;
			nachylenieZ = 7;
		}
		if (katp >= 144 && katp < 150)
		{
			nachylenieX = -9;
			nachylenieZ = 6;
		}
		if (katp >= 150 && katp < 156)
		{
			nachylenieX = -10;
			nachylenieZ = 5;
		}
		if (katp >= 156 && katp < 162)
		{
			nachylenieX = -11;
			nachylenieZ = 4;
		}
		if (katp >= 162 && katp < 168)
		{
			nachylenieX = -12;
			nachylenieZ = 3;
		}
		if (katp >= 168 && katp < 174)
		{
			nachylenieX = -13;
			nachylenieZ = 2;
		}
		if (katp >= 174 && katp < 180)
		{
			nachylenieX = -14;
			nachylenieZ = 1;
		}
		if (katp >= 180 && katp < 186)
		{
			nachylenieX = -15;
			nachylenieZ = 0;
		}
		if (katp >= 186 && katp < 192)//
		{
			nachylenieX = -14;
			nachylenieZ = -1;
		}
		if (katp >= 192 && katp < 198)
		{
			nachylenieX = -13;
			nachylenieZ = -2;
		}
		if (katp >= 198 && katp < 204)
		{
			nachylenieX = -12;
			nachylenieZ = -3;
		}
		if (katp >= 204 && katp < 210)
		{
			nachylenieX = -11;
			nachylenieZ = -4;
		}
		if (katp >= 210 && katp < 216)
		{
			nachylenieX = -10;
			nachylenieZ = -5;
		}
		if (katp >= 216 && katp < 222)
		{
			nachylenieX = -9;
			nachylenieZ = -6;
		}
		if (katp >= 222 && katp < 228)
		{
			nachylenieX = -8;
			nachylenieZ = -7;
		}
		if (katp >= 228 && katp < 234)
		{
			nachylenieX = -7;
			nachylenieZ = -8;
		}
		if (katp >= 234 && katp < 240)
		{
			nachylenieX = -6;
			nachylenieZ = -9;
		}
		if (katp >= 240 && katp < 246)
		{
			nachylenieX = -5;
			nachylenieZ = -10;
		}
		if (katp >= 246 && katp < 252)
		{
			nachylenieX = -4;
			nachylenieZ = -11;
		}
		if (katp >= 252 && katp < 258)
		{
			nachylenieX = -3;
			nachylenieZ = -12;
		}
		if (katp >= 258 && katp < 264)
		{
			nachylenieX = -2;
			nachylenieZ = -13;
		}
		if (katp >= 264 && katp < 270)
		{
			nachylenieX = -1;
			nachylenieZ = -14;
		}
		if (katp >= 270 && katp < 276)
		{
			nachylenieX = 0;
			nachylenieZ = -15;
		}
		if (katp >= 276 && katp < 282)
		{
			nachylenieX = 1;
			nachylenieZ = -14;
		}
		if (katp >= 282 && katp < 288)
		{
			nachylenieX = 2;
			nachylenieZ = -14;
		}
		if (katp >= 288 && katp < 294)
		{
			nachylenieX = 3;
			nachylenieZ = -13;
		}
		if (katp >= 294 && katp < 300)
		{
			nachylenieX = 4;
			nachylenieZ = -11;
		}
		if (katp >= 300 && katp < 306)
		{
			nachylenieX = 5;
			nachylenieZ = -10;
		}
		if (katp >= 306 && katp < 312)
		{
			nachylenieX = 6;
			nachylenieZ = -9;
		}
		if (katp >= 312 && katp < 318)
		{
			nachylenieX = 7;
			nachylenieZ = -8;
		}
		if (katp >= 318 && katp < 324)
		{
			nachylenieX = 8;
			nachylenieZ = -7;
		}
		if (katp >= 324 && katp < 330)
		{
			nachylenieX = 9;
			nachylenieZ = -6;
		}
		if (katp >= 330 && katp < 336)
		{
			nachylenieX = 10;
			nachylenieZ = -5;
		}
		if (katp >= 336 && katp < 342)
		{
			nachylenieX = 11;
			nachylenieZ = -4;
		}
		if (katp >= 342 && katp < 348)
		{
			nachylenieX = 12;
			nachylenieZ = -3;
		}
		if (katp >= 348 && katp < 354)
		{
			nachylenieX = 13;
			nachylenieZ = -2;
		}
		if (katp >= 354 && katp < 360)
		{
			nachylenieX = 14;
			nachylenieZ = -1;
		}
		if (katp >= 360)
		{
			nachylenieX = 15;
			nachylenieZ = 0;
		}

	}
	else
	{
		if (nachylenieX < 0)
			nachylenieX++;
		else
		{
			if (nachylenieX > 0)
				nachylenieX--;
		}
		if (nachylenieZ < 0)
			nachylenieZ++;
		else
		{
			if (nachylenieZ > 0)
				nachylenieZ--;
		}
	}
}


void otoczenie()
{
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-500, 0, -500);
	glVertex3f(-500, 50, -500);
	glVertex3f(500, 0, -500);
	glVertex3f(500, 50, -500);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-500, 0, 500);
	glVertex3f(-500, 50, 500);
	glVertex3f(500, 0, 500);
	glVertex3f(500, 50, 500);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-500, 0, -500);
	glVertex3f(-500, 50, -500);
	glVertex3f(-500, 0, 500);
	glVertex3f(-500, 50, 500);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(500, 0, -500);
	glVertex3f(500, 50, -500);
	glVertex3f(500, 0, 500);
	glVertex3f(500, 50, 500);
	glEnd();
	glColor3f(0.1, 0.2, 0.1);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-500, 0, -500);
	glVertex3f(500, 0, -500);
	glVertex3f(-500, 0, 500);
	glVertex3f(500, 0, 500);
	glEnd();
}

void drzewo(float skala, float obrotDrzewa, float iks, float igrek, float zet)
{
	glPushMatrix();
	glTranslatef(iks, igrek, zet);
	glRotatef(obrotDrzewa, 0, 1, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glColor3f(0.6, 0.4, 0.2);
	drawAiScene(g_scene4, skala,0);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glColor3f(0.1, 0.7, 0.1);
	drawAiScene(g_scene5, skala,0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

//RenderScene
int DrawGLScene()				//Here's where we do all the drawing
{
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();				// Reset MV Matrix


	glTranslatef(0.0f, 0, -40.0f);	// Move 40 Units And Into The Screen

	

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(10, 10, 0);
	glEnd();


	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);
	
	glColor3f(0.3, 0.3, 0.3);
	drawAiScene(g_scene);

	//xrot+=0.3f;
	//yrot+=0.2f;
	//zrot+=0.4f;
	*/


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state and do the rotations
	glPushMatrix();
	if (kamera)
	{
		glRotatef(30, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glTranslatef(0, -100, 0);
	}
	else
		gluLookAt(50 * sin(-yRot / 20.0f) + Xpos, 50 + Ypos, 50 * cos(-yRot / 20.0f) + Zpos, Xpos, Ypos + 30, Zpos, 0, 1, 0);
	
	
	
	
	
	//szescian();

	
	//podloze(0.3f, 0.2f, 0.2f);
	
	//otoczenie();

	//glColor4f(0.6, 0.4, 0.1,1);

	//PR”BA TEKSTUR NR 56
	glPushMatrix();
	glTranslatef(0, 30, 0);
	glEnable(GL_TEXTURE_2D); // W≥πcz teksturowanie

	//glBindTexture(GL_TEXTURE_2D, texture[2]);
	//glBegin(GL_TRIANGLE_STRIP);
	//glNormal3d(0, 0, 1);
	//glColor3f(1, 1, 1);
	///*glTexCoord2d(1.0, 1.0); glVertex3d(25, 25, 25);
	//glTexCoord2d(0.0, 1.0); glVertex3d(-25, 25, 25);
	//glTexCoord2d(0.0, 0.0); glVertex3d(-25, -25, 25);
	//glTexCoord2d(1.0, 0.0); glVertex3d(25, -25, 25);*/
	//glTexCoord2d(0.0, 0.0); glVertex3d(-25, -25, 25);
	//glTexCoord2d(0.0, 1.0); glVertex3d(-25, 25, 25);
	//glTexCoord2d(1.0, 0.0); glVertex3d(25, -25, 25);
	//glTexCoord2d(1.0, 1.0); glVertex3d(25, 25, 25);
	//glEnd();
	/*glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);
	glTexCoord2d(1.0, 1.0); glVertex3d(25, 25, 25);
	glTexCoord2d(0.0, 1.0); glVertex3d(25, -25, 25);
	glTexCoord2d(0.0, 0.0); glVertex3d(25, -25, -25);
	glTexCoord2d(1.0, 0.0); glVertex3d(25, 25, -25);
	glEnd();*/

	
	glPopMatrix();
	//



	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_TRIANGLE_STRIP);
	glColor4f(0.8, 0.8, 1,1);
	glTexCoord2d(1.0, 1.0); glVertex3f(-300, -30 + idle, -300);
	glTexCoord2d(0.0, 1.0); glVertex3f(-100, -30 + idle, -300);
	glTexCoord2d(0.0, 0.0); glVertex3f(-300, -30 + idle, -100);
	glTexCoord2d(1.0, 0.0); glVertex3f(-100, -30+idle, -100);
	glEnd();
	glDisable(GL_TEXTURE_2D); // Wy≥πcz teksturowanie

	glColor3f(0.1, 0.4, 0.1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	drawAiScene(g_scene3, 2.25,1);
	glDisable(GL_TEXTURE_2D);
	//drawAiScene(g_scene3, 2.25);


	drzewo(3, 0, 260, 30, -300);
	drzewo(2.5, 45, -300, -5, 200);
	drzewo(2.2, 120, -210, -5, 150);
	drzewo(2.8, -15, -150, -5, 150);

	

	//glPushMatrix();
	//glTranslatef(0, 0, -100);
	//glRotatef(15, 1, 0, 0);
	//podloze(0.2, 0.4, 0.2);
	//glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.5, 0.3);
	glTranslatef(0, 0, -100);
	glRotatef(90, 0, 0, 1);
	walec(10, 25, 0, 0, 0,0.3);
	glPopMatrix();

	

	/*glPushMatrix();
	glColor3f(0.7, 0.5, 0.6);
	glTranslatef(260, 0, -300);
	glRotatef(90, 0, 0, 1);
	walec(80, 90, 0, 0, 0, 0.3);
	glPopMatrix();*/

	glPushMatrix();
	if (nies)
	{
		catX = Xpos;
		catY = Ypos+5;
		catZ = Zpos;
	}
	else
	{
		if (wpychanie)
		{
			if (abs(Xpos - catX) > 0)
			{
				if (Xpos > catX)
					catX++;
				else
					catX--;

			}
			if (abs(Zpos - catZ) > 0)
			{
				if (Zpos > catZ)
					catZ++;
				else
					catZ--;
			}
			if (catY < 5)
				catY++;
		}
		if (catX < 0 && catZ < 0)
			minCatY = wys1[(int)-catX][(int)-catZ];
		else
			if (catX > 0 && catZ < 0)
				minCatY = wys2[(int)catX][(int)-catZ];
			else
				if (Xpos < 0 && Zpos > 0)
					minCatY = wys3[(int)-catX][(int)catZ];
				else
					if (Xpos > 0 && Zpos > 0)
						minCatY = wys4[(int)catX][(int)catZ];
	}
	
	glTranslatef(catX, catY, catZ);
	if(nies)
		glRotatef(kat, 0, 1, 0);
	glScalef(0.018, 0.018, 0.018);
	
	//glRotatef(315, 0, 1, 0);

	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glEnable(GL_TEXTURE_2D);
	drawAiScene(g_scene,1,0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	


	glPushMatrix();

	//poruszanie ca≥ym robotem

		//Ypos = wysokosc[abs((int)Zpos)];
	if (Xpos < 0 && Zpos < 0)
		Ypos = wys1[(int)-Xpos][(int)-Zpos];
	else
		if (Xpos > 0 && Zpos < 0)
			Ypos = wys2[(int)Xpos][(int)-Zpos];
	else
		if (Xpos < 0 && Zpos > 0)
			Ypos = wys3[(int)-Xpos][(int)Zpos];
	else
		if (Xpos > 0 && Zpos > 0)
			Ypos = wys4[(int)Xpos][(int)Zpos];
		
	glTranslatef(Xpos, Ypos, Zpos);//3. a na koniec wraca na polozenie jakie ma byc
	glRotatef(kat, 0, 1, 0);//2. potem obraca wokol osi Y
	glRotatef(pochylenie, 1, 0, 0);
	glTranslatef(-5, 0, 5); //1. najpierw idzie na srodek 


	glPushMatrix();
	glTranslatef(0, 4.25, 0);
	kola();
	gasienica();

	glPushMatrix();
	glTranslatef(10, 0, 0);
	glScalef(-1, 1, 1);
	kola();
	gasienica();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, idle, 0);
	glRotatef(pochylenie, 1, 0, 0);
	glPopMatrix();
	
	podloga();
	
	ramiona();

	glPushMatrix();
	glTranslatef(1.25, -8, 2.5);
	glScalef(-1, 1, 1);
	glTranslatef(-8.75, 8, -2.5);
	ramiona();

	tyl();
	boki();
	dach();
	przod();

	glPushMatrix();
	glTranslatef(0, 0, -9);
	glRotatef(obr, 1.0f, 0.0f, 0.0f);
	glTranslatef(0, 0, 9); 
	brzusio();
	glPopMatrix();

	szyja();
	glPushMatrix();
	glTranslatef(5, 13.5, -4);
	glRotatef(szyjaObr, 0, 1, 0);
	glTranslatef(-5, -13.5, 4);
		szyja2();
		glPushMatrix();
		glTranslatef(7.75, 15.5, -10);
		glRotatef(oko1, 0.0f, 0.0f, 1.0f);
		glTranslatef(-7.75, -15.5, 10);
		oczko1(7.75, 15.5, -10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(2.25, 15.5, -10);
		glScalef(-1, 1, 1);
		glRotatef(oko1, 0.0f, 0.0f, 1.0f);
		glTranslatef(-2.25, -15.5, 10);
		oczko1(2.25, 15.5, -10);
		glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();//
	//KONIEC
	glPopMatrix();

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	// Flush drawing commands
	glFlush();



	Sleep(1);
	return TRUE;					
}


void KillGLWindow()			// Properly Kill The Window
{
	if (fullscreen)					// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(nullptr, 0);	// If So Switch Back To The Desktop
		ShowCursor(TRUE);					// Show Mouse Pointer
	}

	if (hRC)					// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(nullptr, nullptr))	// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(nullptr, TEXT("Release Of DC And RC Failed."), TEXT("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))			// Are We Able To Delete The RC?
		{
			MessageBox(nullptr, TEXT("Release Rendering Context Failed."), TEXT("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		}
		hRC = nullptr;
	}

	if (hDC)
	{
		if (!ReleaseDC(g_hWnd, hDC)) // Are We able to Release The DC?
			MessageBox(nullptr, TEXT("Release Device Context Failed."), TEXT("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		hDC = nullptr;
	}

	if (g_hWnd)
	{
		if (!DestroyWindow(g_hWnd)) // Are We Able To Destroy The Window
			MessageBox(nullptr, TEXT("Could Not Release hWnd."), TEXT("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		g_hWnd = nullptr;
	}

	if (g_hInstance)
	{
		if (!UnregisterClass(TEXT("OpenGL"), g_hInstance)) // Are We Able To Unregister Class
			MessageBox(nullptr, TEXT("Could Not Unregister Class."), TEXT("SHUTDOWN ERROR"), MB_OK | MB_ICONINFORMATION);
		g_hInstance = nullptr;
	}
}

GLboolean abortGLInit(const char* abortMessage)
{
	KillGLWindow();									// Reset Display
	//MessageBox(nullptr, UTFConverter(abortMessage).c_wstr(), TEXT("ERROR"), MB_OK|MB_ICONEXCLAMATION);
	return FALSE;									// quit and return False
}

BOOL CreateGLWindow(const char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;		// Hold the result after searching for a match
	WNDCLASS	wc;					// Window Class Structure
	DWORD		dwExStyle;			// Window Extended Style
	DWORD		dwStyle;			// Window Style
	RECT		WindowRect;			// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left		= (long)0;
	WindowRect.right	= (long)width;
	WindowRect.top		= (long)0;
	WindowRect.bottom	= (long)height;

	fullscreen = fullscreenflag;

	g_hInstance = GetModuleHandle(nullptr);	// Grab An Instance For Our Window
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw On Move, And Own DC For Window
	wc.lpfnWndProc	= (WNDPROC) WndProc;		// WndProc handles Messages
	wc.cbClsExtra	= 0;	// No Extra Window Data
	wc.cbWndExtra	= 0;	// No Extra Window Data
	wc.hInstance	= g_hInstance;
	wc.hIcon		= LoadIcon(nullptr, IDI_WINLOGO);	// Load The Default Icon
	wc.hCursor		= LoadCursor(nullptr, IDC_ARROW);	// Load the default arrow
	wc.hbrBackground= nullptr;						// No Background required for OpenGL
	wc.lpszMenuName	= nullptr;						// No Menu
	wc.lpszClassName= TEXT("OpenGL");		        // Class Name

	if (!RegisterClass(&wc))
	{
		MessageBox(nullptr, TEXT("Failed to register the window class"), TEXT("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;		//exit and return false
	}

	if (fullscreen)		// attempt fullscreen mode
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Make Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of the devmode structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// bits per pixel
		dmScreenSettings.dmFields		= DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode and Get Results. NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			//// If The Mode Fails, Offer Two Options.  Quit Or Run In A Window.
			//if (MessageBox(nullptr,TEXT("The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?"),TEXT("NeHe GL"),MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			//{
			//	fullscreen = FALSE;		// Select Windowed Mode (Fullscreen = FALSE)
			//}
			//else
			//{
			//	//Popup Messagebox: Closing
			//	MessageBox(nullptr, TEXT("Program will close now."), TEXT("ERROR"), MB_OK|MB_ICONSTOP);
			//	return FALSE; //exit, return false
			//}
		}
	}

	if (fullscreen)		// when mode really succeeded
	{
		dwExStyle=WS_EX_APPWINDOW;		// Window Extended Style
		dwStyle=WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window extended style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	if (nullptr == (g_hWnd=CreateWindowEx(dwExStyle,			// Extended Style For The Window
								TEXT("OpenGL"),						// Class Name
								title,							// Window Title
								WS_CLIPSIBLINGS |				// Required Window Style
								WS_CLIPCHILDREN |				// Required Window Style
								dwStyle,						// Selected WIndow Style
								0, 0,							// Window Position
								WindowRect.right-WindowRect.left, // Calc adjusted Window Width
								WindowRect.bottom-WindowRect.top, // Calc adjustes Window Height
								nullptr,						// No Parent Window
								nullptr,						// No Menu
								g_hInstance,					// Instance
								nullptr )))						// Don't pass anything To WM_CREATE
	{
		abortGLInit("Window Creation Error.");
		return FALSE;
	}

	static	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,												// Version Number
		PFD_DRAW_TO_WINDOW |							// Format Must Support Window
		PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,								// Must Support Double Buffering
		PFD_TYPE_RGBA,									// Request An RGBA Format
		BYTE(bits),											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,								// Color Bits Ignored
		0,												// No Alpha Buffer
		0,												// Shift Bit Ignored
		0,												// No Accumulation Buffer
		0, 0, 0, 0,										// Accumulation Bits Ignored
		16,												// 16Bit Z-Buffer (Depth Buffer)
		0,												// No Stencil Buffer
		0,												// No Auxiliary Buffer
		PFD_MAIN_PLANE,									// Main Drawing Layer
		0,												// Reserved
		0, 0, 0											// Layer Masks Ignored
	};

	if (nullptr == (hDC=GetDC(g_hWnd)))					// Did we get the Device Context?
	{
		abortGLInit("Can't Create A GL Device Context.");
		return FALSE;
	}

	if (0 == (PixelFormat=ChoosePixelFormat(hDC, &pfd))) // Did We Find a matching pixel Format?
	{
		abortGLInit("Can't Find Suitable PixelFormat");
		return FALSE;
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		abortGLInit("Can't Set The PixelFormat");
		return FALSE;
	}

	if (nullptr == (hRC=wglCreateContext(hDC)))
	{
		abortGLInit("Can't Create A GL Rendering Context.");
		return FALSE;
	}

	if (!(wglMakeCurrent(hDC,hRC)))						// Try to activate the rendering context
	{
		abortGLInit("Can't Activate The Rendering Context");
		return FALSE;
	}

	//// *** everything okay ***

	ShowWindow(g_hWnd, SW_SHOW);	// Show The Window
	SetForegroundWindow(g_hWnd);	// Slightly Higher Prio
	SetFocus(g_hWnd);				// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);	// Set Up Our Perspective GL Screen

	if (!InitGL())
	{
		abortGLInit("Initialization failed");
		return FALSE;
	}

	return TRUE;
}

void cleanup()
{
	if (g_hWnd)
		KillGLWindow();
}

LRESULT CALLBACK WndProc(HWND hWnd,				// Handles for this Window
						 UINT uMsg,				// Message for this Window
						 WPARAM wParam,			// additional message Info
						 LPARAM lParam)			// additional message Info
{
	SetTimer(hWnd, 1, 1, NULL);//w milisekundach
	SetTimer(hWnd, 2, 100, NULL);//w milisekundach
	SetTimer(hWnd, 3, 10, NULL);//w milisekundach










	switch (uMsg)				// check for Window Messages
	{
		case WM_ACTIVATE:				// Watch For Window Activate Message
			{
				if (!HIWORD(wParam))	// Check Minimization State
				{
					active=TRUE;
				}
				else
				{
					active=FALSE;
				}

				return 0;				// return To The Message Loop
			}

		case WM_SYSCOMMAND:			// Interrupt System Commands
			{
				switch (wParam)
				{
					case SC_SCREENSAVE:		// Screen-saver trying to start
					case SC_MONITORPOWER:	// Monitor trying to enter power-safe
					return 0;
				}
				break;
			}

		case WM_CLOSE:			// close message received?
			{
				PostQuitMessage(0);	// Send WM_QUIT quit message
				return 0;			// Jump Back
			}

		case WM_KEYDOWN:		// Is a key pressed?
			{
				keys[wParam] = TRUE;	// If so, Mark it as true
				return 0;
			}

		case WM_KEYUP:			// Has Key Been released?
			{
				keys[wParam] = FALSE;	// If so, Mark It As FALSE
				return 0;
			}

		case WM_SIZE:			// Resize The OpenGL Window
			{
				ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));	// LoWord-Width, HiWord-Height
				return 0;
			}
		case WM_TIMER:
		{
			switch (wParam)
		case 1:
			{
				if (!bob)
				{
					idle += 0.01;
					if (idle > 0.1)
						bob = 1;
				}
				if (bob)
				{
					idle -= 0.01;
					if (idle < -0.1)
						bob = 0;
				}
				if (!keys[VK_NUMPAD8] && predkosc > 0.0f)
				{
					predkosc -= 0.1;
					obrotSrubek += predkosc*10;
					if (!kolizja(-predkosc * sin(kat * GL_PI / 180.0f), -predkosc * cos(kat * GL_PI / 180.0f)))
					{
						Xpos += -predkosc * sin(kat * GL_PI / 180.0f);
						Zpos += -predkosc * cos(kat * GL_PI / 180.0f);
					}
					
					kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;
					pochylenie-=0.125f;
				}
				else
				if (pochylenie < 0)
					pochylenie+=0.125f;

		    /*if (!keys[VK_NUMPAD4] && predkoscObrotu > 0.0f)
				{
					predkoscObrotu -= 0.125;
					kat += predkoscObrotu;
					obrotSrubek += predkoscObrotu * 10;
					kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;

				}
				if (!keys[VK_NUMPAD6] && predkoscObrotu > 0.0f)
				{
					predkoscObrotu -= 0.125;
					kat -= predkoscObrotu;
					obrotSrubek += predkoscObrotu * 10;
					kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;
				}*/
				if (keys[VK_NUMPAD5])
				{
					kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;
				}
			}
		case 2:
		{
			if (!szyjaR)
			{
				szyjaObr += 0.1;
				if (szyjaObr > 5)
					szyjaR = 1;
			}
			if (szyjaR)
			{
				szyjaObr -= 0.1;
				if (szyjaObr < -5)
					szyjaR = 0;
			}
			
		}
		case 3:
		{
			if (podnoszenie)
			{
				if (kroki < 25)
				{
					if (obr > -110)
						obr -= 3;
					if (ramieZ < 5.75)
					{
						ramieZ += 0.25;
						if (pochylenie > -5)
							pochylenie -= 0.2;
					}
					kroki++;
				}
				if (kroki >= 25 && kroki < 50)
				{
					if (obr > -110)
						obr -= 3;
					if (ramieY < 5.75)
						ramieY += 0.25;
					if (katRamion > -25)
						katRamion -= 1;
					if (przedluzenie < 7)
						przedluzenie += 0.5;
					if (dlonObr < 90)
						dlonObr += 10;
					if (dlonObr2 < 75)
						dlonObr2 += 3.5;
					kroki++;
				}
				if (kroki >= 50 && kroki < 100)
				{
					
					if (pochylenie < 0)
						pochylenie += 0.2;
					if (przedluzenie > 0)
						przedluzenie -= 0.5;
					if (katRamion > -45)
						katRamion -= 1;
					if (ramieY > 0)
						ramieY -= 0.25;
					else
					{
						
						if (ramieZ > 0)
							ramieZ -= 0.25;
						if(ramieZ < 4)
							wpychanie = 1;
					}
					kroki++;
				}
				if (kroki >= 100 && kroki < 110)
				{
					wpychanie = 0;
					/*if (dlonObr > 0)
						dlonObr -= 10;*/
					if (dlonObr2 > 0)
						dlonObr2 -= 10;
					if (obr < 0)
						obr += 3;
					kroki++;
				}
				if (kroki >= 110 && kroki < 150)
				{
					if (dlonObr > 0)
						dlonObr -= 10;
					if (obr < 0)
						obr += 3;
					if (katRamion < 0)
						katRamion += 2.5;
					kroki++;
				}
				if (kroki == 150)
				{
					kroki = 0;
					podnoszenie = 0;
					nies = 1;
				}

			}
			if (opuszczanie)
			{
				if (kroki < 25)
				{
					if (obr > -110)
						obr -= 3;
					if (pochylenie > -5)
						pochylenie -= 0.2;
					kroki++;
				}
				if (kroki >= 25 && kroki < 70)
				{
					nies = 0;
					if (obr > -110)
						obr -= 3;
					catX += -(2+predkosc) * sin(kat * GL_PI / 180.0f);
					catZ += -(2+predkosc) * cos(kat * GL_PI / 180.0f);
					kroki++;
					opad += 0.015;
				}
				if (kroki >= 70 && kroki < 125)
				{
					if (obr < 0)
						obr += 3;
					kroki++;
				}
				if (kroki == 125)
				{
					opuszczanie = 0;
					kroki = 0;
				}
			}
			if (catY > minCatY)
				catY-=opad;
		}
		}
	}

	// Pass All unhandled Messaged To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE /*hInstance*/,     // The instance
				   HINSTANCE /*hPrevInstance*/,  // Previous instance
				   LPSTR /*lpCmdLine*/,          // Command Line Parameters
				   int /*nShowCmd*/ )            // Window Show State
{
	MSG msg = {};
	BOOL done=FALSE;
	//irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	//engine->play2D("C:/Users/Miko≥aj/Desktop/materia≥y na grafikÍ/assimp/SimpleTexturedOpenGL/objekty/walle.wav", false);
	//createAILogger();
	//logInfo("App fired!");

	// Check the command line for an override file path.
	//int argc;
	//LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	//if (argv != nullptr && argc > 1)
	//{
	//	std::wstring modelpathW(argv[1]);
	//	modelpath = modelpathW;
	//}
	if (!mapa)
		return 0;


	if (!Import3DFromFile(modelpath))
	{
		cleanup();
		return 0;
	}
	if (!Import3DFromFile2(modelpath2))
	{
		cleanup();
		return 0;
	}
	if (!Import3DFromFile3(modelpath3))
	{
		cleanup();
		return 0;
	}
	if (!Import3DFromFile4(modelpath4))
	{
		cleanup();
		return 0;
	}
	if (!Import3DFromFile5(modelpath5))
	{
		cleanup();
		return 0;
	}
	/*if (!Import3DFromFile6(modelpath6))
	{
		cleanup();
		return 0;
	}*/
	//logInfo("=============== Post Import ====================");

	/*if (MessageBox(nullptr, TEXT("Would You Like To Run In Fullscreen Mode?"), TEXT("Start Fullscreen?"), MB_YESNO|MB_ICONEXCLAMATION)==IDNO)
	{
		fullscreen=FALSE;
	}*/

	if (!CreateGLWindow(windowTitle, 1280, 720, 16, fullscreen))
	{
		cleanup();
		return 0;
	}

	while(!done)	// Game Loop
	{
		//SetWaitableTimer(timer,1000)
		if (PeekMessage(&msg, nullptr, 0,0, PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				done=TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// Draw The Scene. Watch For ESC Key And Quit Messaged From DrawGLScene()
			if (active)
			{
				if (keys[VK_ESCAPE])
				{
					done=TRUE;
				}
				else
				{
					DrawGLScene();
					SwapBuffers(hDC);
				}
				if (keys[VK_UP])
					xRot -= 1.0f;

				if (keys[VK_DOWN])
					xRot += 1.0f;

				if (keys [VK_LEFT])
					yRot -= 1.0f;
				if (keys [VK_RIGHT])
					yRot += 1.0f;
				
				
				if (GetAsyncKeyState(0x57) && GetAsyncKeyState(0x41))
				{
					obrotSrubek += 10;
				
					Xpos += -1.0f * sin(kat * GL_PI / 180.0f);
					Zpos += -1.0f * cos(kat * GL_PI / 180.0f);
					kat += 1;
					/*kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;*/
					
			
				}
				if (GetAsyncKeyState(0x57) && GetAsyncKeyState(0x44))
				{

					obrotSrubek += 10;
					
					Xpos += -1.0f * sin(kat * GL_PI / 180.0f);
					Zpos += -1.0f * cos(kat * GL_PI / 180.0f);
					kat -= 1;
					/*kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;*/
				}
				if (GetAsyncKeyState(0x57) && !GetAsyncKeyState(0x44)&& !GetAsyncKeyState(0x41))
				{

					obrotSrubek += 10;
					
					//Xpos += 3;
				
						Xpos += -1.0f * sin(kat * GL_PI / 180.0f);
						Zpos += -1.0f * cos(kat * GL_PI / 180.0f);
						kolorGasienicy += 0.2f;
						if (kolorGasienicy > 0.2f)
							kolorGasienicy = 0.0f;
					
					

				}


				if (GetAsyncKeyState(0x53) && GetAsyncKeyState(0x41))
				{
					obrotSrubek -= 10;

					Xpos -= -1.0f * sin(kat * GL_PI / 180.0f);
					Zpos -= -1.0f * cos(kat * GL_PI / 180.0f);
					kat += 1;
					/*kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;*/
				}
				if (GetAsyncKeyState(0x53) && GetAsyncKeyState(0x44))
				{
					obrotSrubek -= 10;

					Xpos -= -1.0f * sin(kat * GL_PI / 180.0f);
					Zpos -= -1.0f * cos(kat * GL_PI / 180.0f);
					kat -= 1;
					/*kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;*/
				}
				if (GetAsyncKeyState(0x53) && !GetAsyncKeyState(0x44) && !GetAsyncKeyState(0x41))
				{
					obrotSrubek -= 10;

					//Xpos += 3;
					Xpos -= -1.0f * sin(kat * GL_PI / 180.0f);
					Zpos -= -1.0f * cos(kat * GL_PI / 180.0f);
					kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;

				}

				if (keys[0x41])//A
				{
					obrotSrubek += 10;

					kat += 1;
					kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;
				}
				if (keys[0x44])//D
				{
					obrotSrubek += 10;

					kat -= 1;
					kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;
				}
				if (keys[0x4F])//O opusc klape
				{
					if(obr>-110)
					obr -= 3;
				}
				if (keys[0x50])//P podnies klape
				{
					if(obr<0)
					obr += 3;
				}
				if (keys[0x4B])//K opusc oczka
				{
					if (oko1 > 0)
						oko1 -= 1;
				}
				if (keys[0x4C])//L podnies oczka
				{
					if (oko1 < 13)
						oko1 += 1;
				}
				if (keys[0x52])//R wydluz ramie
				{
					if (przedluzenie < 7)
						przedluzenie += 0.5;
					if (dlonObr < 90)
						dlonObr += 10;
					if (dlonObr2 < 75)
						dlonObr2 += 5;
				}
				if (keys[0x54])//T skroc ramie
				{
					if (przedluzenie > 0)
						przedluzenie -= 0.5;
					if (dlonObr > 0)
						dlonObr -= 10;
					if (dlonObr2 > 0)
						dlonObr2 -= 5;
				}
				if (keys[0x46])//F ramie w dol
				{
					if (ramieZ < 5.75)
					{
						ramieZ += 0.25;
					}
					else
					{
						if (ramieY < 5.75)
						{
							ramieY += 0.25;
						}
					}

				}
				if (keys[0x47])//G ramie w gore
				{
					if (ramieY > 0)
					{
						ramieY -= 0.25;
					}
					else
					{
						if (ramieZ > 0)
						{
							ramieZ -= 0.25;
						}
					}

				}
				if (keys[0x43])//C podnies ramie
				{
					if(katRamion < 90)
						katRamion += 2.5;
				}
				if (keys[0x56])//V opusc ramie
				{
					if (katRamion > -25)
						katRamion -= 2.5;
				}
				if (keys[0x58])//X podnies
				{
					podnoszenie = 1;
					
				}
				if (keys[0x42])//B opusc
				{
					if (nies)
					{
						opuszczanie = 1;
						opad = 0.45;
					}
				}
				if (keys[0x5A])//Z "animacja"
				{
					if (kroki < 25)
					{
						if (obr > -110)
							obr -= 3;
						if (ramieZ < 5.75)
						{
							ramieZ += 0.25;
							if (pochylenie > -5)
								pochylenie -= 0.2;
						}
						kroki++;
					}
					if (kroki >= 25 && kroki < 50)
					{
						if (obr > -110)
							obr -= 3;
						if (ramieY < 5.75)
							ramieY += 0.25;
						if (katRamion > -25)
							katRamion -= 1;
						if (przedluzenie < 7)
							przedluzenie += 0.5;
						if (dlonObr < 90)
							dlonObr += 10;
						if (dlonObr2 < 75)
							dlonObr2 += 3.5;
						kroki++;
					}
					if (kroki >= 50 && kroki < 100)
					{
						if (pochylenie < 0)
							pochylenie += 0.2;
						if (przedluzenie > 0)
							przedluzenie -= 0.5;
						if (katRamion > -45)
							katRamion -= 1;
						if (ramieY > 0)
							ramieY -= 0.25;
						else
						{
							if (ramieZ > 0)
								ramieZ -= 0.25;
						}
						kroki++;
					}
					if (kroki >= 100 && kroki < 110)
					{
						/*if (dlonObr > 0)
							dlonObr -= 10;*/
						if (dlonObr2 > 0)
							dlonObr2 -= 10;
						if (obr < 0)
							obr += 3;
						kroki++;
					}
					if (kroki >= 110 && kroki < 150)
					{
						if (dlonObr > 0)
							dlonObr -= 10;
						if (obr < 0)
							obr += 3;
						if (katRamion < 0)
							katRamion += 2.5;
						kroki++;
					}
					if (kroki == 150)
					{
						kroki = 0;
					}
				}
				if (keys[VK_NUMPAD8])
				{
					if(pochylenie <1)
					pochylenie += 0.125f;
					if (predkosc < 1.3)
						predkosc += 0.1;
					obrotSrubek += predkosc * 10;
					if (!kolizja(-predkosc * sin(kat * GL_PI / 180.0f), -predkosc * cos(kat * GL_PI / 180.0f)))
					{
						Xpos += -predkosc * sin(kat * GL_PI / 180.0f);
						Zpos += -predkosc * cos(kat * GL_PI / 180.0f);
					}
					kolorGasienicy += 0.2f;
					if (kolorGasienicy > 0.2f)
						kolorGasienicy = 0.0f;
				}
				if (keys[VK_NUMPAD5])
				{
					obrotSrubek -= 0.25 * 10;
					if (!kolizja(0.25 * sin(kat * GL_PI / 180.0f), 0.25 * cos(kat * GL_PI / 180.0f)))
					{
						Xpos -= -0.25 * sin(kat * GL_PI / 180.0f);
						Zpos -= -0.25 * cos(kat * GL_PI / 180.0f);
					}
				}
				if (keys[VK_NUMPAD4])
				{
					obrotSrubek += 5;
					kat += 1;
					if (!keys[VK_NUMPAD8] && !keys[VK_NUMPAD5])
					{
						kolorGasienicy += 0.2f;
						if (kolorGasienicy > 0.2f)
							kolorGasienicy = 0.0f;
					}
				}
				if (keys[VK_NUMPAD6])
				{
					obrotSrubek += 5;
					kat -= 1;
					if(!keys[VK_NUMPAD8] && !keys[VK_NUMPAD5])
					{
						kolorGasienicy += 0.2f;
						if (kolorGasienicy > 0.2f)
							kolorGasienicy = 0.0f;
					}
				}
				if (keys[VK_NUMPAD0])
				{
					keys[VK_NUMPAD0] = false;
					kamera = !kamera;
				}
					

				

				xRot = (const int)xRot % 360;
				yRot = (const int)yRot % 360;
				obrotSrubek = (const int)obrotSrubek % 360;
				kat = (const int)kat % 360;
			}

			//if (keys[VK_F1])
			//{
			//	keys[VK_F1]=FALSE;
			//	KillGLWindow();
			//	//fullscreen=!fullscreen;
			//	if (!CreateGLWindow(windowTitle, 640, 480, 16, fullscreen))
			//	{
			//		cleanup();
			//		return 0;
			//	}
			//}
		}
	}

	// *** cleanup ***
	//engine->drop();
	cleanup();
	return static_cast<int>(msg.wParam);
}