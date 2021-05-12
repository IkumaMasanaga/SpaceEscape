#include "matrix.h"

namespace t2k {

	Matrix& Matrix::operator = (DirectX::XMMATRIX& other) {
		DirectX::XMStoreFloat4x4(this, other);
		return *this;
	}

	Matrix Matrix::operator * (const Matrix& other) const {
		Matrix m1 = *this;
		Matrix m2 = other;
		return DirectX::XMMatrixMultiply(m1, m2);
	}

	Matrix& Matrix::operator *= (const Matrix& other) {
		Matrix m = other;
		*this = *this * m;
		return *this;
	}

	Vector3 Matrix::getRelativePosition(const Vector3& relative_position, const float angle) {
		Matrix m = Matrix::createTranslation(relative_position.x, relative_position.y, relative_position.z) * Matrix::createRotationAxis(Vector3(0, 0, 1), angle);
		return t2k::Vector3(m._41, m._42, m._43);
	}

}