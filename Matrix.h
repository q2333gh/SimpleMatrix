//
// Created by Liu Qi sheng on 2018/4/3.
// This program provides the encapsulation of the matrix and its operations
// Maintainer email=liuqisheng_ws@163.com
//
#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <typeinfo>

template<class T>
class Matrix {
 private:
  int cols;//����
  int rows;//����
  int size;//�����С
  T *data;//Ԫ������
  bool is_singular = false;//�Ƿ�����
 public:
  Matrix();//Ĭ�Ϲ��캯��
  Matrix(int rows_, int cols_, T val);//���������������,Ԫ�����ֵval
  Matrix(int row_cols_, T val); //����ԽǷ���,�Խ�Ԫ��ֵval
  Matrix(int rows_, int cols_, const std::vector<T> &Array, bool isRowFirst = true);//��һά���鹹�����Ĭ�����к��д洢
  Matrix(int rows_, int cols_, const std::vector<std::vector<T>> &Array);//�ö�ά���鹹�����
  Matrix(const Matrix &matrix);                     //���Ѵ��ڵľ�����������
  int getCols() const { return cols; };                //��ȡ����
  int getRows() const { return rows; };                //��ȡ����
  int getSize() const { return rows * cols; };         //��ȡ�����С
  bool isSingular() {
	inverse();
	return is_singular;
  };//�жϾ����Ƿ�����

  T &operator()(int row, int col);                    //���Ų��������أ����ڻ�ȡ�����row�е�col��Ԫ��

  bool LUP_Descomposition(Matrix<double> &A, Matrix<double> &L, Matrix<double> &U, Matrix<double> &P);//LUP�ֽ�
  Matrix<double> LUP_Solve(Matrix<double> &L, Matrix<double> &U, Matrix<double> &P, Matrix<double> &b);//LUP������Է���
  Matrix<T> transpose();                                //����ת��
  Matrix<double> inverse();                                  //LU�ֽ��������
  Matrix<T> &operator=(const Matrix &matrix);            //����ĸ�ֵ����������
  Matrix<T> &operator+=(const Matrix &matrix);          //����ļӷ�����������
  Matrix<T> &operator+=(T val);                //���������ļӷ�����������
  Matrix<T> &operator-=(const Matrix &matrix);          //����ļ�������������
  Matrix<T> &operator-=(T val);                //���������ļ�������������
  Matrix<T> &operator*=(const Matrix &matrix);          //����ĳ˷�����������
  Matrix<T> &operator*=(T val);                //���������ĳ˷�����������
  Matrix<T> &operator/=(const Matrix &matrix);          //�������Ԫ�س�������������
  Matrix<T> &operator/=(T val);                //���������ĳ�������������

  ~Matrix() { delete[]data; };
 public:
  template<class ElemType>
  friend Matrix<ElemType> operator+(const Matrix<ElemType> &matrix1, const Matrix<ElemType> &matrix2);//���������ӷ�+����������
  template<class ElemType>
  friend Matrix<ElemType> operator-(const Matrix<ElemType> &matrix1, const Matrix<ElemType> &matrix2);//������������-����������
  template<class ElemType>
  friend Matrix<ElemType> operator*(const Matrix<ElemType> &matrix1, const Matrix<ElemType> &matrix2);//���������˷�*����������
  template<class ElemType>
  friend Matrix<ElemType> operator/(const Matrix<ElemType> &matrix1, const Matrix<ElemType> &matrix2);//�����������Ԫ�س���/����������
  template<class ElemType>
  friend Matrix<ElemType> operator+(const Matrix<ElemType> &matrix, const ElemType val);      //���������ӷ�+���������أ�1��
  template<class ElemType>
  friend Matrix<ElemType> operator+(const ElemType val, const Matrix<ElemType> &matrix);      //���������ӷ�+���������أ�2��
  template<class ElemType>
  friend Matrix<ElemType> operator-(const Matrix<ElemType> &matrix, const ElemType val);      //������������-���������أ�1��
  template<class ElemType>
  friend Matrix<ElemType> operator-(const ElemType val, const Matrix<ElemType> &matrix);      //������������-���������أ�2��
  template<class ElemType>
  friend Matrix<ElemType> operator*(const Matrix<ElemType> &matrix, const ElemType val);      //���������˷�*���������أ�1��
  template<class ElemType>
  friend Matrix<ElemType> operator*(const ElemType val, const Matrix<ElemType> &matrix);      //���������˷�*���������أ�2��
  template<class ElemType>
  friend Matrix<ElemType> operator/(const Matrix<ElemType> &matrix, const ElemType val);      //������������/���������أ�1��
  template<class ElemType>
  friend Matrix<ElemType> operator/(const ElemType val, const Matrix<ElemType> &matrix);      //������������/���������أ�2��
  template<class ElemType>
  friend std::ostream &operator<<(std::ostream &os, const Matrix<ElemType> &matrix); //��������������
};

//Ĭ�Ϲ��캯��
template<class T>
Matrix<T>::Matrix() {
  cols = 0;
  rows = 0;
  size = 0;
  data = nullptr;
}
//���캯���������й���
template<class T>
Matrix<T>::Matrix(int rows_, int cols_, T val) {
  cols = cols_;
  rows = rows_;
  size = cols * rows;
  data = new T[size];
  for (int i = 0; i < size; i++)
	data[i] = val;
}

//���캯�������ɶԽ���,���к���ʽ�洢  
template<class T>
Matrix<T>::Matrix(int row_cols_, T val) {
  cols = rows = row_cols_;
  size = cols * rows;
  data = new T[size];
  for (int i = 0; i < cols; i++) {
	for (int j = 0; j < rows; j++) {
	  data[i * rows + j] = (j == i ? val : 0);
	}
  }
}
//���캯������һά����  
template<class T>
Matrix<T>::Matrix(int rows_, int cols_, const std::vector<T> &Array, bool isRowFirst) {
  cols = cols_;
  rows = rows_;
  size = cols * rows;
  data = new T[size];
  if (size != Array.size()) {
	std::cerr << "vector size is not equal with the matrix!" << std::endl;
	return;
  }
  if (isRowFirst == false) {
	for (int i = 0; i < size; i++) {
	  data[i] = Array[i];
	}
  } else {
	for (int i = 0; i < rows; i++)
	  for (int j = 0; j < cols; j++) {
		data[j * rows + i] = Array[i * cols + j];
	  }
  }
}
//���캯�����ɶ�ά���� 
template<class T>
Matrix<T>::Matrix(int rows_, int cols_, const std::vector<std::vector<T>> &Array) {
  cols = cols_;
  rows = rows_;
  size = cols * rows;
  data = new T[size];
  for (int i = 0; i < cols; i++)
	for (int j = 0; j < rows; j++)
	  data[i * rows + j] = Array[j][i];
}
//���캯�������๹��  
template<class T>
Matrix<T>::Matrix(const Matrix &matrix) {
  cols = matrix.cols;
  rows = matrix.rows;
  size = cols * rows;
  data = new T[size];
  for (int i = 0; i < size; i++)
	data[i] = matrix.data[i];
}

//----------------------------------------------------------------------------------- 
template<class T>
T &Matrix<T>::operator()(int row, int col) {
  return data[col * rows + row];
}

//�������  
template<class ElemType>
std::ostream &operator<<(std::ostream &os, const Matrix<ElemType> &matrix) {
  for (int i = 0; i < matrix.rows; i++) {
	for (int j = 0; j < matrix.cols; j++) {
	  os << matrix.data[j * matrix.rows + i];
	  if (j != matrix.cols - 1)
		os << ",";
	}
	os << ";" << std::endl;
  }
  return os;
}
//����ת��
template<class T>
Matrix<T> Matrix<T>::transpose() {
  Matrix<T> res(cols, rows, 0);
  for (int i = 0; i < cols; i++)
	for (int j = 0; j < rows; j++)
	  res(i, j) = data[i * rows + j];
  return res;
}
//������ = ����
template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix &matrix) {
  //һ��Ҫ������ʱ���󣬷�ֹͬһ����ֵ�����·����ڴ��ͬʱ���Ѿ����˾���ı䣡������������
  if (this == &matrix) {
	return *this;
  }
  cols = matrix.cols;
  rows = matrix.rows;
  size = cols * rows;
  delete[] data;
  data = new T[size];
  for (int i = 0; i < size; i++)
	data[i] = matrix.data[i];
  return *this;
}

//������ += ����(�����)  
template<class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix &matrix) {
  if (cols != matrix.cols || rows != matrix.rows) {
	std::cerr << "Error:The number of rows or columns is not equal(matrix::operator+=)" << std::endl;
	return *this;
  } else if (typeid(matrix.data).name() != typeid(data).name()) {
	std::cerr << "Error:Different types of matrix data(matrix::operator+=)" << std::endl;
	return *this;
  } else {
	for (int i = 0; i < size; i++)
	  data[i] += matrix.data[i];
	return *this;
  }
}
//������ +�� ����(����)  
template<class T>
Matrix<T> &Matrix<T>::operator+=(T val) {
  for (int i = 0; i < this->size; i++)
	this->data[i] += val;
  return *this;
}

//������ -= ����(�����)
template<class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix &matrix) {
  if (cols != matrix.cols || rows != matrix.rows) {
	std::cerr << "Error:The number of rows or columns is not equal(matrix::operator-=)" << std::endl;
	return *this;
  } else if (typeid(matrix.data).name() != typeid(data).name()) {
	std::cerr << "Error:Different types of matrix data(matrix::operator-=)" << std::endl;
	return *this;
  } else {
	for (int i = 0; i < size; i++)
	  data[i] -= matrix.data[i];
	return *this;
  }
}
//������ -= ����(����)  
template<class T>
Matrix<T> &Matrix<T>::operator-=(T val) {
  for (int i = 0; i < this->size; i++)
	this->data[i] -= val;
  return *this;
}

//������ *= ����(�����)  
template<class T>
Matrix<T> &Matrix<T>::operator*=(const Matrix &matrix) {
  if (cols != matrix.rows) {
	std::cerr
		<< "Error:The cols of matrix1 is not equal to the rows of matrix2, and can not be multiplied.(matrix::operator*=)"
		<< std::endl;
	return *this;
  } else if (typeid(matrix.data).name() != typeid(data).name()) {
	std::cerr << "Error:Different types of matrix data(matrix::operator*=)" << std::endl;
	return *this;
  } else {
	int res_size = rows * matrix.cols;
	T *res_data = new T[res_size];
	for (int i = 0; i < rows; i++)
	  for (int j = 0; j < matrix.cols; j++) {
		T temp = 0.0;
		for (int k = 0; k < cols; k++) {
		  temp += data[k * rows + i] * matrix.data[j * matrix.rows + k];
		  res_data[j * rows + i] = temp;
		}
	  }
	cols = matrix.cols;
	size = res_size;
	delete[] data;
	data = new T[size];
	for (int i = 0; i < size; i++)
	  data[i] = res_data[i];
	delete[] res_data;
	return *this;
  }
}

//������ *= ����(����)  
template<class T>
Matrix<T> &Matrix<T>::operator*=(T val) {
  for (int i = 0; i < this->size; i++)
	this->data[i] *= val;
  return *this;
}

//������ /= ����(������Ԫ�س�)  
template<class T>
Matrix<T> &Matrix<T>::operator/=(const Matrix &matrix) {
  if (cols != matrix.cols || rows != matrix.rows) {
	std::cerr << "Error:The number of rows or columns is not equal(matrix::operator/=)" << std::endl;
	return *this;
  } else if (typeid(matrix.data).name() != typeid(data).name()) {
	std::cerr << "Error:Different types of matrix data(matrix::operator/=)" << std::endl;
	return *this;
  } else {
	for (int i = 0; i < size; i++)
	  data[i] /= matrix.data[i];
	return *this;
  }
}
//������ /= ����(����)  
template<class T>
Matrix<T> &Matrix<T>::operator/=(T val) {
  for (int i = 0; i < this->size; i++)
	this->data[i] /= val;
  return *this;
}

//������ + ����(�����)  
template<class ElemType>
Matrix<ElemType> operator+(const Matrix<ElemType> &matrix1, const Matrix<ElemType> &matrix2) {
  Matrix<ElemType> res(matrix1);
  if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows) {
	std::cerr << "Error:The number of rows or columns is not equal(matrix::operator+)" << std::endl;
  } else if (typeid(matrix1.data).name() != typeid(matrix2.data).name()) {
	std::cerr << "Error:Different types of matrix data(matrix::operator+)" << std::endl;
  } else {
	for (int i = 0; i < matrix1.size; i++)
	  res.data[i] = matrix1.data[i] + matrix2.data[i];
  }
  return res;
}

//������ - ����(�����)  
template<class ElemType>
Matrix<ElemType> operator-(const Matrix<ElemType> &matrix1, const Matrix<ElemType> &matrix2) {
  Matrix<ElemType> res(matrix1);
  if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows) {
	std::cerr << "Error:The number of rows or columns is not equal(matrix::operator-)" << std::endl;
  } else if (typeid(matrix1.data).name() != typeid(matrix2.data).name()) {
	std::cerr << "Error:Different types of matrix data(matrix::operator-)" << std::endl;
  } else {
	for (int i = 0; i < matrix1.size; i++)
	  res.data[i] = matrix1.data[i] - matrix2.data[i];
  }
  return res;
}

//������ * ����(�����)  
template<class ElemType>
Matrix<ElemType> operator*(const Matrix<ElemType> &matrix1, const Matrix<ElemType> &matrix2) {
  Matrix<ElemType> res(matrix1.rows, matrix2.cols);
  if (matrix1.cols != matrix2.rows) {
	std::cerr
		<< "Error:The cols of matrix1 is not equal to the rows of matrix2, and can not be multiplied.(matrix::operator*)"
		<< std::endl;
	return res;
  } else if (typeid(matrix1.data).name() != typeid(matrix2.data).name()) {
	std::cerr << "Error:Different types of matrix data(matrix::operator*)" << std::endl;
	return res;
  } else {
	for (int i = 0; i < matrix1.rows; i++)
	  for (int j = 0; j < matrix2.cols; j++) {
		ElemType temp = 0.0;
		for (int k = 0; k < matrix1.cols; k++) {
		  temp += matrix1.data[k * matrix1.rows + i] * matrix2.data[j * matrix2.rows + k];
		  res.data[j * matrix1.rows + i] = temp;
		}
	  }
	return res;
  }
}

//������ / ����(������Ԫ�س�)  
template<class ElemType>
Matrix<ElemType> operator/(const Matrix<ElemType> &matrix1, const Matrix<ElemType> &matrix2) {
  Matrix<ElemType> res(matrix1);
  if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows) {
	std::cerr << "Error:The number of rows or columns is not equal(matrix::operator/)" << std::endl;
  } else if (typeid(matrix1.data).name() != typeid(matrix2.data).name()) {
	std::cerr << "Error:Different types of matrix data(matrix::operator/)" << std::endl;
  } else {
	for (int i = 0; i < matrix1.size; i++)
	  res.data[i] = matrix1.data[i] / matrix2.data[i];
  }
  return res;
}

//������ + ����(����1)  
template<class ElemType>
Matrix<ElemType> operator+(const Matrix<ElemType> &matrix, const ElemType val) {
  for (int i = 0; i < matrix.size; i++)
	matrix.data[i] += val;
  return matrix;
}
//������ + ����(����2)
template<class ElemType>
Matrix<ElemType> operator+(const ElemType val, const Matrix<ElemType> &matrix) {
  for (int i = 0; i < matrix.size; i++)
	matrix.data[i] += val;
  return matrix;
}
//������ - ����(����1)  
template<class ElemType>
Matrix<ElemType> operator-(const Matrix<ElemType> &matrix, const ElemType val) {
  for (int i = 0; i < matrix.size; i++)
	matrix.data[i] -= val;
  return matrix;
}
//������ - ����(����2)
template<class ElemType>
Matrix<ElemType> operator-(const ElemType val, const Matrix<ElemType> &matrix) {
  for (int i = 0; i < matrix.size; i++)
	matrix.data[i] = val - matrix.data[i];
  return matrix;
}
//������ * ����(����1)  
template<class ElemType>
Matrix<ElemType> operator*(const Matrix<ElemType> &matrix, const ElemType val) {
  for (int i = 0; i < matrix.size; i++)
	matrix.data[i] *= val;
  return matrix;
}
//������ * ����(����2)
template<class ElemType>
Matrix<ElemType> operator*(const ElemType val, const Matrix<ElemType> &matrix) {
  for (int i = 0; i < matrix.size; i++)
	matrix.data[i] *= val;
  return matrix;
}
//������ / ����(����1)  
template<class ElemType>
Matrix<ElemType> operator/(const Matrix<ElemType> &matrix, const ElemType val) {
  for (int i = 0; i < matrix.size; i++)
	matrix.data[i] /= val;
  return matrix;
}
//������ / ����(����2)
template<class ElemType>
Matrix<ElemType> operator/(const ElemType val, const Matrix<ElemType> &matrix) {
  for (int i = 0; i < matrix.size; i++)
	matrix.data[i] = val / matrix.data[i];
  return matrix;
}

//LUP�ֽ�
template<class T>
bool Matrix<T>::LUP_Descomposition(Matrix<double> &A, Matrix<double> &L, Matrix<double> &U, Matrix<double> &P) {
  int N = P.getSize();
  int row = 0;
  for (int i = 0; i < N; i++) {
	P(0, i) = i;
  }
  for (int i = 0; i < N - 1; i++) {
	double p = 0.0;
	for (int j = i; j < N; j++) {
	  if (fabs(A(j, i)) > p) {
		p = fabs(A(j, i));
		row = j;
	  }
	}
	if (0 == p) {
	  std::cerr << "Error:Matrix singularity and the inverse matrix is incalculable" << std::endl;
	  return false;
	}

	//����P[i]��P[row]
	double tmp = P(0, i);
	P(0, i) = P(0, row);
	P(0, row) = tmp;

	double tmp2 = 0;
	for (int j = 0; j < N; j++) {
	  //����A[i][j]�� A[row][j]
	  tmp2 = A(i, j);
	  A(i, j) = A(row, j);
	  A(row, j) = tmp2;
	}

	//����ͬLU�ֽ�
	double u = A(i, i), l = 0;
	for (int j = i + 1; j < N; j++) {
	  l = A(j, i) / u;
	  A(j, i) = l;
	  for (int k = i + 1; k < N; k++) {
		A(j, k) = A(j, k) - A(i, k) * l;
	  }
	}
  }

  //����L��U
  for (int i = 0; i < N; i++) {
	for (int j = 0; j <= i; j++) {
	  if (i != j) {
		L(i, j) = A(i, j);
	  } else {
		L(i, j) = 1;
	  }
	}
	for (int k = i; k < N; k++) {
	  U(i, k) = A(i, k);
	}
  }
  return true;
}
//LUP������Է���
template<class T>
Matrix<double> Matrix<T>::LUP_Solve(Matrix<double> &L, Matrix<double> &U, Matrix<double> &P, Matrix<double> &b) {
  int N = P.getSize();
  Matrix<double> x(1, N, 0.0);
  Matrix<double> y(1, N, 0.0);
  //�����滻
  for (int i = 0; i < N; i++) {
	y(0, i) = b(0, P(0, i));
	for (int j = 0; j < i; j++) {
	  y(0, i) = y(0, i) - L(i, j) * y(0, j);
	}
  }
  //�����滻
  for (int i = N - 1; i >= 0; i--) {
	x(0, i) = y(0, i);
	for (int j = N - 1; j > i; j--) {
	  x(0, i) = x(0, i) - U(i, j) * x(0, j);
	}
	x(0, i) /= U(i, i);
  }
  return x;
}
//LU�ֽ��������
template<class T>
Matrix<double> Matrix<T>::inverse() {
  int N = rows;
  Matrix<double> A_mirror(N, N, 0.0);
  for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	  A_mirror(i, j) = data[j * rows + i];
  Matrix<double> A_inv(N, N, 0.0);
  Matrix<double> A_inv_each(1, N, 0.0);
  Matrix<double> b(1, N, 0.0);
  Matrix<double> L(N, N, 0.0);
  Matrix<double> U(N, N, 0.0);
  Matrix<double> P(1, N, 0.0);
  if (LUP_Descomposition(A_mirror, L, U, P) == false) {
	A_inv.is_singular = true;
	return A_inv;
  }
  for (int i = 0; i < N; i++) {
	//���쵥λ���ÿһ��
	for (int i = 0; i < N; i++) {
	  b(0, i) = 0;
	}
	b(0, i) = 1;
	A_inv_each = LUP_Solve(L, U, P, b);
	for (int j = 0; j < N; j++)A_inv(j, i) = A_inv_each(0, j);
  }
  return A_inv;
}



