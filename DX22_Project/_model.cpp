#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void Model::MakeMesh(const void* ptr)
{
	// ���O����
	aiVector3D zero3(0.0f, 0.0f, 0.0f);
	aiColor4D one4(1.0f, 1.0f, 1.0f, 1.0f);
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);
	float xFlip = m_loadFlip == Flip::XFlip ? -1.0f : 1.0f;
	float zFlip = (m_loadFlip == Flip::ZFlip || m_loadFlip == Flip::ZFlipUseAnime) ? -1.0f : 1.0f;
	int idx1 = (m_loadFlip == Flip::XFlip || m_loadFlip == Flip::ZFlip) ? 2 : 1;
	int idx2 = (m_loadFlip == Flip::XFlip || m_loadFlip == Flip::ZFlip) ? 1 : 2;

	// ���b�V���̍쐬
	m_meshes.resize(pScene->mNumMeshes);
	for (unsigned int i = 0; i < m_meshes.size(); ++i)
	{
		aiMesh* assimpMesh = pScene->mMeshes[i];
		Mesh& mesh = m_meshes[i];

		// �m�[�h�K�w���̒T��
		mesh.nodeIndex = FindNode(assimpMesh->mName.data);
		if (mesh.nodeIndex == NODE_NONE) { continue; }

		// ���_�������ݐ�̗̈��p��
		mesh.vertices.resize(assimpMesh->mNumVertices);

		// ���_�f�[�^�̏�������
		for (unsigned int j = 0; j < mesh.vertices.size(); ++j) {
			// ���f���f�[�^����l�̎擾
			aiVector3D pos		= assimpMesh->mVertices[j];
			aiVector3D normal	= assimpMesh->HasNormals() ? assimpMesh->mNormals[j] : zero3;
			aiVector3D uv		= assimpMesh->HasTextureCoords(0) ?
				assimpMesh->mTextureCoords[0][j] : zero3;
			aiColor4D color		= assimpMesh->HasVertexColors(0) ? assimpMesh->mColors[0][j] : one4;
			// �l��ݒ�
			mesh.vertices[j] = {
				DirectX::XMFLOAT3(pos.x * m_loadScale * xFlip, pos.y * m_loadScale, pos.z * m_loadScale * zFlip),
				DirectX::XMFLOAT3(normal.x, normal.y, normal.z),
				DirectX::XMFLOAT2(uv.x, uv.y),
				DirectX::XMFLOAT4(color.r, color.g, color.b, color.a)
			};
		}

		// �{�[������
		MakeVertexWeight(pScene, i);

		// �C���f�b�N�X�̏������ݐ�̗p��
		// mNumFaces�̓|���S���̐���\��(�P�|���S����3�C���f�b�N�X
		mesh.indices.resize(assimpMesh->mNumFaces * 3);

		// �C���f�b�N�X�̏�������
		for (unsigned int j = 0; j < assimpMesh->mNumFaces; ++j) {
			// ���f���f�[�^����l�̎擾
			aiFace face = assimpMesh->mFaces[j];

			// �l�̐ݒ�
			int idx = j * 3;
			mesh.indices[idx + 0] = face.mIndices[0];
			mesh.indices[idx + 1] = face.mIndices[idx1];
			mesh.indices[idx + 2] = face.mIndices[idx2];
		}

		// �}�e���A���̊��蓖��
		mesh.materialID = assimpMesh->mMaterialIndex;

		// ���b�V�������ɒ��_�o�b�t�@�쐬
		MeshBuffer::Description desc = {};
		desc.pVtx		= mesh.vertices.data();
		desc.vtxSize	= sizeof(Vertex);
		desc.vtxCount	= mesh.vertices.size();
		desc.pIdx		= mesh.indices.data();
		desc.idxSize	= sizeof(unsigned long);
		desc.idxCount	= mesh.indices.size();
		desc.topology	= D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		mesh.pMesh = new MeshBuffer();
		mesh.pMesh->Create(desc);
	}
}

void Model::MakeMaterial(const void* ptr, std::string directory)
{
	// ���O����
	aiColor3D color(0.0f, 0.0f, 0.0f);
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);
	float shininess;

	// �}�e���A���̍쐬
	m_materials.resize(pScene->mNumMaterials);
	for (unsigned int i = 0; i < m_materials.size(); ++i)
	{
		aiMaterial* assimpMaterial = pScene->mMaterials[i];
		Material& material = m_materials[i];

		//--- �e��}�e���A���p�����[�^�[�̓ǂݎ��
		// �g�U���̓ǂݎ��
		if (assimpMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
			material.diffuse = DirectX::XMFLOAT4(color.r, color.g, color.b, 1.0f);
		else
			material.diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		// �����̓ǂݎ��
		if (assimpMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
			material.ambient = DirectX::XMFLOAT4(color.r, color.g, color.b, 1.0f);
		else
			material.ambient = DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		// ���ˌ��̓ǂݎ��
		if (assimpMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
			material.specular = DirectX::XMFLOAT4(color.r, color.g, color.b, 0.0f);
		else
			material.specular = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		// ���ˌ��̋�����ǂݎ��
		if (assimpMaterial->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
			material.specular.w = shininess;

		// �e�N�X�`���ǂݍ��ݏ���
		HRESULT hr;
		aiString path;

		// �e�N�X�`���̃p�X����ǂݍ���
		material.pTexture = nullptr;
		if (assimpMaterial->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) != AI_SUCCESS) {
			continue;
		}

		// �e�N�X�`���̈�m��
		material.pTexture = new Texture;

		// ���̂܂ܓǂݍ���
		hr = material.pTexture->Create(path.C_Str());
		if (SUCCEEDED(hr)) { continue; }

		// �f�B���N�g���ƘA�����ĒT��
		hr = material.pTexture->Create((directory + path.C_Str()).c_str());
		if (SUCCEEDED(hr)) { continue; }

		// ���f���Ɠ����K�w��T��
		// �p�X����t�@�C�����̂ݎ擾
		std::string fullPath = path.C_Str();
		std::string baseDir = GetDirectory(fullPath.c_str());
		std::string fileName = fullPath.substr(baseDir.size());

		// �e�N�X�`���̓Ǎ�
		hr = material.pTexture->Create((directory + fileName).c_str());
		if (SUCCEEDED(hr)) { continue; }

		// �e�N�X�`����������Ȃ�����
		delete material.pTexture;
		material.pTexture = nullptr;
		SetErrorMessage("Not find texture. [" + fullPath + "]");
	}
}