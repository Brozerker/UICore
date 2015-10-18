/*!
 * \file Models.cpp
 *
 * \author Sam Rivera
 * \date 9/27/2015
 *
 * 
 */
#include "Models.h"
#include "Textures.h"
#include "Vertex.h"

using namespace GFXCore;
using std::vector;

int Models::nIdGenerator = -1;

Models::Models()
{
}


Models::~Models()
{
}

bool GFXCore::Models::init(const int startNumModels /*= 10*/)
{
	modelList.reserve(startNumModels);

	return true;
}

int GFXCore::Models::createBoxMesh(IDirect3DDevice9* device, const float width, const float height, const float depth)
{
	XModelData mesh;
	memset(&mesh, NULL, sizeof(XModelData));

	HR(D3DXCreateBox(device, width, height, depth, &mesh.pMesh, &mesh.pAdjacency));

	DWORD* adj = new DWORD[mesh.pMesh->GetNumFaces() * 3];

	HR(mesh.pMesh->GenerateAdjacency(1e-6f, adj));
	HR(mesh.pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_ATTRSORT, adj, NULL, NULL, NULL));

 	if (adj) {
 		delete[] adj;
 		adj = NULL;
 	}

	D3DMATERIAL9 mat;
	mat.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Emissive = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Power = 1.0f;

	mesh.materialList.push_back(mat);

	modelList.push_back(mesh);

	return ++nIdGenerator;
}

int GFXCore::Models::createCylinderMesh(IDirect3DDevice9* device, const float radZNeg, const float radZPos, const float lenght, const unsigned int slices, const unsigned int stacks)
{
	XModelData mesh;
	memset(&mesh, NULL, sizeof(XModelData));

	HR(D3DXCreateCylinder(device, radZNeg, radZPos, lenght, slices, stacks, &mesh.pMesh, &mesh.pAdjacency));

	DWORD* adj = new DWORD[mesh.pMesh->GetNumFaces() * 3];

	HR(mesh.pMesh->GenerateAdjacency(1e-6f, adj));
	HR(mesh.pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_ATTRSORT, adj, NULL, NULL, NULL));

	if (adj) {
		delete[] adj;
		adj = NULL;
	}

	D3DMATERIAL9 mat;
	mat.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Emissive = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Power = 1.0f;

	mesh.materialList.push_back(mat);

	modelList.push_back(mesh);

	return ++nIdGenerator;
}

int GFXCore::Models::createPolyMesh(IDirect3DDevice9* device, const float lenght, const unsigned int sides)
{
	XModelData mesh;
	memset(&mesh, NULL, sizeof(XModelData));

	HR(D3DXCreatePolygon(device, lenght, sides, &mesh.pMesh, &mesh.pAdjacency));

	DWORD* adj = new DWORD[mesh.pMesh->GetNumFaces() * 3];

	HR(mesh.pMesh->GenerateAdjacency(1e-6f, adj));
	HR(mesh.pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_ATTRSORT, adj, NULL, NULL, NULL));

	if (adj) {
		delete[] adj;
		adj = NULL;
	}

	D3DMATERIAL9 mat;
	mat.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Emissive = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Power = 1.0f;

	mesh.materialList.push_back(mat);

	modelList.push_back(mesh);

	return ++nIdGenerator;
}

int GFXCore::Models::createSphereMesh(IDirect3DDevice9* device, const float radius, const unsigned int slices, const unsigned int stacks)
{
	XModelData mesh;
	memset(&mesh, NULL, sizeof(XModelData));

	HR(D3DXCreateSphere(device, radius, slices, stacks, &mesh.pMesh, &mesh.pAdjacency));

	DWORD* adj = new DWORD[mesh.pMesh->GetNumFaces() * 3];

	HR(mesh.pMesh->GenerateAdjacency(1e-6f, adj));
	HR(mesh.pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_ATTRSORT, adj, NULL, NULL, NULL));

	if (adj) {
		delete[] adj;
		adj = NULL;
	}

	D3DMATERIAL9 mat;
	mat.Ambient = { 0.0f, 1.0f, 0.0f, 1.0f };
	mat.Diffuse = { 0.0f, 1.0f, 0.0f, 1.0f };
	mat.Emissive = { 0.0f, 1.0f, 0.0f, 1.0f };
	mat.Specular = { 0.0f, 1.0f, 0.0f, 1.0f };
	mat.Power = 100.0f;

	mesh.materialList.push_back(mat);

	modelList.push_back(mesh);

	return ++nIdGenerator;
}

int GFXCore::Models::createTeapotMesh(IDirect3DDevice9* device)
{
	XModelData mesh;
	memset(&mesh, NULL, sizeof(XModelData));

	HR(D3DXCreateTeapot(device, &mesh.pMesh, &mesh.pAdjacency));

	DWORD* adj = new DWORD[mesh.pMesh->GetNumFaces() * 3];

	HR(mesh.pMesh->GenerateAdjacency(1e-6f, adj));
	HR(mesh.pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_ATTRSORT, adj, NULL, NULL, NULL));

	if (adj) {
		delete[] adj;
		adj = NULL;
	}

	D3DMATERIAL9 mat;
	mat.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Emissive = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Power = 1.0f;

	mesh.materialList.push_back(mat);

	modelList.push_back(mesh);

	return ++nIdGenerator;
}

int GFXCore::Models::createTorusMesh(IDirect3DDevice9* device, const float innRadius, const float outRadius, const unsigned int sides, const unsigned int rings)
{
	XModelData mesh;
	memset(&mesh, NULL, sizeof(XModelData));

	HR(D3DXCreateTorus(device, innRadius, outRadius, sides, rings, &mesh.pMesh, &mesh.pAdjacency));

	DWORD* adj = new DWORD[mesh.pMesh->GetNumFaces() * 3];

	HR(mesh.pMesh->GenerateAdjacency(1e-6f, adj));
	HR(mesh.pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_ATTRSORT, adj, NULL, NULL, NULL));

	if (adj) {
		delete[] adj;
		adj = NULL;
	}

	D3DMATERIAL9 mat;
	mat.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Emissive = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	mat.Power = 1.0f;

	mesh.materialList.push_back(mat);

	modelList.push_back(mesh);

	return ++nIdGenerator;
}

int Models::loadModel(IDirect3DDevice9* device, const wchar_t* fileName,  
								Textures& textures,
								const D3DXVECTOR3& initPos, 
								const D3DXVECTOR3& initRot, 
								const D3DXVECTOR3& initScale, 
								DWORD options)
{
	for (unsigned int i = 0; i < modelList.size(); ++i) 
		if (0 == wcscmp(fileName, modelList[i].strFileName))
			return i;

	XModelData modelData;
	memset(&modelData, NULL, sizeof(XModelData));
	wcscpy_s(modelData.strFileName, MAX_FILE_NAME, fileName);

	if (FAILED(D3DXLoadMeshFromX(modelData.strFileName, options, device, &modelData.pAdjacency,
													  &modelData.pMaterials, &modelData.pEffectInstances,
													  &modelData.dwNumMaterials, &modelData.pMesh))) {

		ErrorMsg(L"Load Mesh failure - Models::loadModel().", fileName);

		return -1;

	}

	D3DXMATERIAL* modelMats = (D3DXMATERIAL*)modelData.pMaterials->GetBufferPointer();
	if (NULL == modelMats)
		return -1;

 	modelData.materialList.reserve(modelData.dwNumMaterials);
 	modelData.textureList.reserve(modelData.dwNumMaterials);

	for (DWORD i = 0; i < modelData.dwNumMaterials; ++i) {
		modelData.materialList.push_back(modelMats[i].MatD3D);
		modelData.materialList[i].Ambient = modelData.materialList[i].Diffuse;

		if (modelMats[i].pTextureFilename) {
			int len = 0;
			wchar_t wstr[MAX_FILE_NAME] = L"";
			// TODO: change this to actual directory when all cores combined
			char append[MAX_FILE_NAME] = "..\\GraphicsTesting\\Assets\\";
			strcat_s(append, modelMats[i].pTextureFilename);
			size_t inputBuff;
			mbstowcs_s(&inputBuff, wstr, append, MAX_FILE_NAME);
			int texId = textures.loadTexture(device, wstr);
			modelData.textureList.push_back(texId);
		}
	}

	DWORD* adj = new DWORD[modelData.pMesh->GetNumFaces() * 3];
	if (NULL == adj) {
		ErrorMsg(L"Out of Memory", L"Models::init()");
		return -1;
	}
	
	HR(modelData.pMesh->GenerateAdjacency(1e-6f, adj));
	HR(modelData.pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_ATTRSORT, adj, NULL, NULL, NULL));

	delete[] adj;
	adj = NULL;

	D3DXMatrixIdentity(&modelData.translationMat);
	D3DXMatrixIdentity(&modelData.rotationMat);
	D3DXMatrixIdentity(&modelData.scalingMat);
	D3DXMatrixIdentity(&modelData.worldTranformMat);

	D3DXMatrixTranslation(&modelData.translationMat, initPos.x, initPos.y, initPos.z);
	D3DXMatrixRotationYawPitchRoll(&modelData.rotationMat, initRot.x, initRot.y, initRot.z);
	D3DXMatrixScaling(&modelData.scalingMat, initScale.x, initScale.y, initScale.z);

	D3DXMatrixMultiply(&modelData.scalingMat, &modelData.scalingMat, &modelData.rotationMat);
	D3DXMatrixMultiply(&modelData.worldTranformMat, &modelData.scalingMat, &modelData.translationMat);
	// TODO: add functionality to be able to set a particular shader to the model
	modelList.push_back(modelData);
	return ++nIdGenerator;
}

void Models::update(const int id, const D3DXVECTOR3& position, 
							 const bool rotChange, const bool scaleChange,
							 const D3DXVECTOR3& rotation, 
							 const D3DXVECTOR3& scaling)
{
#if defined (_DEBUG) | defined(DEBUG)
	CHECK_OUT_OF_BOUNDS(id, (int)modelList.size());
#endif

	setTranslation(id, position);
	if (rotChange)
		setRotation(id, rotation);
	if (scaleChange)
		setScaling(id, scaling);

	D3DXMatrixMultiply(&modelList[id].scalingMat, &modelList[id].scalingMat, &modelList[id].rotationMat);
	D3DXMatrixMultiply(&modelList[id].worldTranformMat, &modelList[id].scalingMat, &modelList[id].translationMat);
}

void Models::render(IDirect3DDevice9* device, Textures& textures, const int id)
{
#if defined (_DEBUG) | defined(DEBUG)
	CHECK_OUT_OF_BOUNDS(id, (int)modelList.size());
#endif

	HR(device->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));
	HR(device->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
	HR(device->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR));
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_AMBIENT, /*modelList[id].materialList[0].Ambient.a*/D3DCOLOR_ARGB(255, 255, 255, 255));
	device->SetTransform(D3DTS_WORLD, &modelList[id].worldTranformMat);
// 	if (modelList[id]->materialList[0])
	device->SetMaterial(&modelList[id].materialList[0]);
	if (modelList[id].textureList.size())
		device->SetTexture(0, textures.getTexture(modelList[id].textureList[0]));
	modelList[id].pMesh->DrawSubset(0);
}
 
void Models::shutdown()
{
	for (unsigned int i = 0; i < modelList.size(); ++i) {
		if (modelList[i].pAdjacency)
			ReleaseCom(modelList[i].pAdjacency);
		if (modelList[i].pEffectInstances)
			ReleaseCom(modelList[i].pEffectInstances);
		if (modelList[i].pMaterials)
			ReleaseCom(modelList[i].pMaterials);
		if (modelList[i].pMesh)
			ReleaseCom(modelList[i].pMesh);

		modelList[i].materialList.clear();
		modelList[i].materialList.resize(0);

		modelList[i].textureList.clear();
		modelList[i].textureList.resize(0);
	}
}

