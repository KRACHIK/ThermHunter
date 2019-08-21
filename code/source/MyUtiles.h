#ifndef C_MYUTILES_H
#define C_MYUTILES_H 

#include <iostream>
#include <string>

class c_MyUtiles
{

public:
	c_MyUtiles();
	~c_MyUtiles();

	std::string ToHEX(float Arr[], size_t size);

	std::string IntToHEX(int);

	std::string FloatToHEX(float);
private:

};

std::string  getMeDirectory();

std::string getFindFileToken(std::string fileName, std::string findToken);

void Log(const char *fmt, ...);
void LogFile(const char *fmt, ...);

class c_MyBackGraundMessageBox // not used
{
public:

	c_MyBackGraundMessageBox(std::string msg, std::string msg2);
private:
	void MyMsgBox();
	std::string m_msg;
	std::string m_msg2;
};

class CPoint3D
{
public:
	CPoint3D() {};

	CPoint3D(float x, float y, float z)
		:
		m_X(x)
		, m_Y(y)
		, m_Z(z)
	{
	}

	void Set(float x, float y, float z)
	{
		m_X = x;
		m_Y = y;
		m_Z = z;
	}

	void AddOffset(float x, float y, float z)
	{
		m_X += x;
		m_Y += y;
		m_Z += z;
	}


	void Set(
		/* x */ float* A1,
		/* y */ float* A2,
		/* z */ float* A3
	)
	{
		m_X = *A1;
		m_Y = *A2;
		m_Z = *A3;
	}

	void Get(
		/* x */ float* A1,
		/* y */ float* A2,
		/* z */ float* A3
	)
	{
		*A1 = m_X;
		*A2 = m_Y;
		*A3 = m_Z;
	}



	void Set(CPoint3D point3D)
	{
		m_X = point3D.m_X;
		m_Y = point3D.m_Y;
		m_Z = point3D.m_Z;
	}


	CPoint3D Get() { return *this; }

	float GetX() const { return m_X; }
	float GetY() const { return m_Y; }
	float GetZ() const { return m_Z; }


	std::string GetDbgStr() const
	{
		std::string Log = "[" + std::to_string(m_X) + "," + std::to_string(m_Y) + "," + std::to_string(m_Z) + "]";
		return Log;
	}

private:
	float m_X = 0.0f;
	float m_Y = 0.0f;
	float m_Z = 0.0f;

};


class CMath
{
public:
	/*static float GetDistance(CPoint3D A, CPoint3D B)
	{
		float  Distance =
			sqrt(pow((A.GetX() - B.GetX()), 2.0))
			+ sqrt(pow((A.GetY() - B.GetY()), 2.0))
			+ sqrt(pow((A.GetZ() - B.GetZ()), 2.0));

		return Distance;
	}*/

	static float GetDistance2D(CPoint3D A, CPoint3D B)
	{
		float Ax_sqare = A.GetX() * A.GetX();
		float Bx_sqare = B.GetX() * B.GetX();

		float Ay_sqare = A.GetY() * A.GetY();
		float By_sqare = B.GetY() * B.GetY();

		float x_dif = abs(Ax_sqare - Bx_sqare);
		float y_dif = abs(Ay_sqare - By_sqare);

		float sum= x_dif + y_dif; 

		float  fDistance = sqrt(sum);
		 
		Log("[CMath::GetDistance2D] Ax_sqare %f, Bx_sqare %f, Ay_sqare %f, By_sqare	%f, x_dif %f, y_dif %f, sum %f, fDistance %f "
			, Ax_sqare
			, Bx_sqare
			, Ay_sqare
			, By_sqare
			, x_dif
			, y_dif
			, sum
			, fDistance
		);


			float  Distance = sqrt(
			(A.GetX()*A.GetX()) - (B.GetX()*B.GetX())
				+
				(A.GetY()*A.GetY()) - (B.GetY()*B.GetY())
			);


		return fDistance;
	}


};






#endif  








