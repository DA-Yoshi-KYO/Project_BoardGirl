/// @file RendererComponent.h
/// @brief �����_���[�p�̒���R���|�[�l���g�N���X

#pragma once

#include "Component.h"
#include "Defines.h"

class CRendererComponent : public CComponent
{
public:
	using CComponent::CComponent;

	// �e��p�����[�^�̐ݒ�
	/// <summary>
	/// �����_���[�̓����p�����[�^��ݒ�
	/// </summary>
	/// <param name="inParam">�ݒ肷�郌���_���[�̃p�����[�^</param>
	void SetRendererParam(const RendererParam inParam);
	/// <summary>
	/// �\�����郍�[�J�����W��ݒ�
	/// </summary>
	/// <param name="inPos">�ݒ肷����W�̒l(DirectX::XMFLOAT3)</param>
	void SetPos(DirectX::XMFLOAT3 inPos);
	/// <summary>
	/// �\������2D���W��ݒ�
	/// </summary>
	/// <param name="inPos">�ݒ肷����W�̒l(DirectX::XMFLOAT2)</param>
	void SetPos(DirectX::XMFLOAT2 inPos);
	/// <summary>
	/// �\�����郍�[�J���T�C�Y��ݒ�
	/// </summary>
	/// <param name="inSize">�ݒ肷��T�C�Y�̒l(DirectX::XMFLOAT3)</param>
	void SetSize(DirectX::XMFLOAT3 inSize);
	/// <summary>
	/// �\������2D�T�C�Y��ݒ�
	/// </summary>
	/// <param name="inSize">�ݒ肷��T�C�Y�̒l(DirectX::XMFLOAT2)</param>
	void SetSize(DirectX::XMFLOAT2 inSize);
	/// <summary>
	/// �\�����郍�[�J����]��ݒ�
	/// </summary>
	/// <param name="inRotation">�ݒ肷���]�̒l(DirectX::XMFLOAT3)</param>
	void SetRotation(DirectX::XMFLOAT3 inRotation);
	/// <summary>
	/// �\������2D��]��ݒ�
	/// </summary>
	/// <param name="inRotation">�ݒ肷���]�̒l(DirectX::XMFLOAT2)</param>
	void SetRotation(float inRotation);
	/// <summary>
	/// �\������F��ݒ�
	/// </summary>
	/// <param name="inColor">�ݒ肷��F�̒l(DirectX::XMFLOAT4)</param>
	void SetColor(DirectX::XMFLOAT4 inColor);
	/// <summary>
	/// UV���W�̈ʒu��ݒ�
	/// </summary>
	/// <param name="inUVPos">�ݒ肷��UV���W�̈ʒu(DirectX::XMFLOAT2)</param>
	void SetUVPos(DirectX::XMFLOAT2 inUVPos);
	/// <summary>
	/// UV���W�̃T�C�Y��ݒ�
	/// </summary>
	/// <param name="inUVSize">�ݒ肷��UV���W�̃T�C�Y(DirectX::XMFLOAT2)</param>
	void SetUVSize(DirectX::XMFLOAT2 inUVSize);

protected:
	RendererParam m_tParam;	// �����_���[�̓����p�����[�^

};