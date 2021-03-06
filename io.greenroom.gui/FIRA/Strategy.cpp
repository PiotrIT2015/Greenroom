// Strategy.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Strategy.h"

#include <math.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
	DWORD  ul_reason_for_call, 
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


class Order{
public: Order(double val, int num){
		value = val;
		number = num;
	}
public: Order(){
	}
public: int number;
public: double value;
};
const double PI = 3.1415923;

int sqrState = -1;
int dest[4][2] = { {0,0},{0,-20},{20,-20},{20,0} };
Order rands[5];
Order opponentInfo[5];
int whichTeam = -2;
char myMessage[200]; //big enough???
bool myball = false;
bool returnerStatus = false;
bool attackMode = false;
int nearestPlayer = -1;
double smallestR =9999.0;

void PredictBall ( Environment *env );
void Goalie1 ( Robot *robot, Environment *env );
void NearBound2 ( Robot *robot, double vl, double vr, Environment *env );
void Attack2 ( Robot *robot, Environment *env );
void Defend ( Robot *robot, Environment *env, double low, double high );

void SortT( Order tab[], int size );

void Defend ( Environment *env );
void MoveToOpp ( Environment *env );
void DefendAttac ( Environment *env );
void Attack ( Environment *env );

//nie wiedziałem ile ogólnie jest robotów

void Arduino(Robot *robot, Environment *env);




// by moon at 9/2/2002
void MoonAttack (Robot *robot, Environment *env );
void doSquare( Robot *robot, double xTopLeft, double yTopLeft );
// just for testing to check whether the &env->opponent works or not
void MoonFollowOpponent (  Robot *robot, OpponentRobot *opponent );


void Velocity ( Robot *robot, int vl, int vr );
void Angle ( Robot *robot, int desired_angle);
void Position( Robot *robot, double x, double y );

extern "C" STRATEGY_API void Create ( Environment *env )
{

	// allocate user data and assign to env->userData
	// eg. env->userData = ( void * ) new MyVariables ();
}

extern "C" STRATEGY_API void Destroy ( Environment *env )
{
	// free any user data created in Create ( Environment * )

	// eg. if ( env->userData != NULL ) delete ( MyVariables * ) env->userData;
}

// Ta metoda koduje ogólny schemat poruszania robotów

extern "C" STRATEGY_API void Strategy ( Environment *env )
{
	if(whichTeam<-1){
		if(env->home[0].pos.x < (FRIGHTX - FLEFTX)/2)
			whichTeam=-1;// moj team po lewej
		else
			whichTeam=1;// moj team po prawej
	}
	double lastDiff = 0.0;
	double diff =0.0;

	myball = false;
	nearestPlayer = -1;
	smallestR =9999.0;




	if(whichTeam == -1 ?(env->currentBall.pos.x >= (FRIGHTX - FLEFTX)/2) : (env->currentBall.pos.x <= (FRIGHTX - FLEFTX)/2))
	{//piłka po stronie przeciwnika

		//w ktora strone toczy sie pilka
		if(whichTeam == -1)
			diff = env->currentBall.pos.x - GLEFT;
		else
			diff = GRIGHT - env->currentBall.pos.x;

		if(diff - lastDiff > 0){//do przodu
			Attack(env);
		}else{//do tylu

			DefendAttac(env);
		}
		//doSquare (&env->home [4], (FRIGHTX - FLEFTX)/2,(FTOP - FBOT)/2 );
	}else{
		//pilka po mojej stronie

		// czy moj zawodnik ma pilke
		if(myball){//tak
			MoveToOpp(env);
		}else{//nie
			Defend(env);
		}
	}
	
	lastDiff = diff;

}
void SortT( Order tab[], int size )
{
	Order swap;
	for( int i = 0; i < size; i++ )
	{
		for( int j = 0; j < size - 1; j++ )
		{
			if( tab[ j ].value > tab[ j + 1 ].value ){

				swap  = tab[ j ];
				tab[ j ]   = tab[ j + 1 ];
				tab[ j + 1 ] = swap;
			}

		}
	}
}

//kolejne cztery metody kodują zachowanie w poszczególnych formacjach

void Defend ( Environment *env ){

	Bot( &env->home [0], env );

}
void MoveToOpp ( Environment *env ){

	Bot( &env->home [0], env );

}
void DefendAttac ( Environment *env ){

	Bot( &env->home [0], env );

}
void Attack ( Environment *env ){

	Bot( &env->home [0], env );

}

void Bot(Robot * robot, Environment * env)
{

	PredictBall(env);
	Position(robot, whichTeam == 1 ? GLEFT + 4 : GRIGHT - 4, env->predictedBall.pos.y);

}











//Reszta metod koduje specyfike poszczególnych ruchów i zachowań których jest 9




void MoonAttack ( Robot *robot, Environment *env )
{

	PredictBall ( env );
	Position(robot, env->predictedBall.pos.x, env->predictedBall.pos.y);
	
}

void MoonFollowOpponent ( Robot *robot, OpponentRobot *opponent )
{
	Position(robot, opponent->pos.x, opponent->pos.y);
}

bool closeTo(Robot *robot, double xPos, double yPos) {

	if ((fabs(robot->pos.x-xPos)<1) && (fabs(robot->pos.y-yPos)<1))
	{
		return true;
	}
	else {
		return false;
	}

}
void doSquare( Robot *robot, double xTopLeft, double yTopLeft ) {
	if (sqrState<0 || sqrState>3)
		sqrState=0;
	if (closeTo(robot,xTopLeft+dest[sqrState][0], yTopLeft+dest[sqrState][1]) )
		sqrState+=1;
	else
		Position(robot, xTopLeft+dest[sqrState][0], yTopLeft+dest[sqrState][1]);
}

void Velocity ( Robot *robot, int vl, int vr )
{
	robot->velocityLeft = vl*2;
	robot->velocityRight = vr*2;
}

// robot soccer system p329
void Angle ( Robot *robot, int desired_angle)
{
	int theta_e, vl, vr;
	theta_e = desired_angle - (int)robot->rotation;

	while (theta_e > 180) theta_e -= 360;
	while (theta_e < -180) theta_e += 360;

	if (theta_e < -90) theta_e += 180;

	else if (theta_e > 90) theta_e -= 180;

	if (abs(theta_e) > 50) 
	{
		vl = (int)(-9./90.0 * (double) theta_e);
		vr = (int)(9./90.0 * (double)theta_e);
	}
	else if (abs(theta_e) > 20)
	{
		vl = (int)(-11.0/90.0 * (double)theta_e);
		vr = (int)(11.0/90.0 * (double)theta_e);
	}
	Velocity (robot, vl, vr);
}

void Position( Robot *robot, double x, double y )
{
	int desired_angle = 0, theta_e = 0, d_angle = 0, vl, vr, vc = 70;

	double dx, dy, d_e, Ka = 10.0/90.0;
	dx = x - robot->pos.x;
	dy = y - robot->pos.y;

	d_e = sqrt(dx * dx + dy * dy);
	if (dx == 0 && dy == 0)
		desired_angle = 90;
	else
		desired_angle = (int)(180. / PI * atan2((double)(dy), (double)(dx)));
	theta_e = desired_angle - (int)robot->rotation;

	while (theta_e > 180) theta_e -= 360;
	while (theta_e < -180) theta_e += 360;

	if (d_e > 100.) 
		Ka = 17. / 90.;
	else if (d_e > 50)
		Ka = 19. / 90.;
	else if (d_e > 30)
		Ka = 21. / 90.;
	else if (d_e > 20)
		Ka = 23. / 90.;
	else 
		Ka = 25. / 90.;

	if (theta_e > 95 || theta_e < -95)
	{
		theta_e += 180;

		if (theta_e > 180) 
			theta_e -= 360;
		if (theta_e > 80)
			theta_e = 80;
		if (theta_e < -80)
			theta_e = -80;
		if (d_e < 5.0 && abs(theta_e) < 40)
			Ka = 0.1;
		vr = (int)(-vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) + Ka * theta_e);
		vl = (int)(-vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) - Ka * theta_e);
	}

	else if (theta_e < 85 && theta_e > -85)
	{
		if (d_e < 5.0 && abs(theta_e) < 40)
			Ka = 0.1;
		vr = (int)( vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) + Ka * theta_e);
		vl = (int)( vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) - Ka * theta_e);
	}

	else
	{
		vr = (int)(+.17 * theta_e);
		vl = (int)(-.17 * theta_e);
	}

	Velocity(robot, vl, vr);
}


void PredictBall ( Environment *env )
{
	double dx = env->currentBall.pos.x - env->lastBall.pos.x;
	double dy = env->currentBall.pos.y - env->lastBall.pos.y;
	env->predictedBall.pos.x = env->currentBall.pos.x + dx;
	env->predictedBall.pos.y = env->currentBall.pos.y + dy;

}

void Goalie1 ( Robot *robot, Environment *env )
{
	double velocityLeft = 0, velocityRight = 0;

	double Tx = env->goalBounds.right - env->currentBall.pos.x;
	double Ty = env->fieldBounds.top - env->currentBall.pos.y;

	double Ax = env->goalBounds.right - robot->pos.x;
	double Ay = env->fieldBounds.top - robot->pos.y;

	if ( Ay > Ty + 0.9 && Ay > 27 )
	{
		velocityLeft = -100;
		velocityRight = -100;
	}

	if ( Ay > Ty - 0.9 && Ay < 43 )
	{
		velocityLeft = 100;
		velocityRight = 100;
	}

	if ( Ay < 27 )
	{
		velocityLeft = 100;
		velocityRight = 100;
	}

	if ( Ay > 43 )
	{
		velocityLeft = -100;
		velocityRight = -100;
	}

	double Tr = robot->rotation;
	if ( Tr < 0.001 )
		Tr = Tr + 360;
	if ( Tr > 360.001 )
		Tr = Tr - 360;
	if ( Tr > 270.5 )
		velocityRight = velocityRight + fabs ( Tr - 270 );
	else if ( Tr < 269.5 )
		velocityLeft = velocityLeft + fabs ( Tr - 270 );

	robot->velocityLeft = velocityLeft;
	robot->velocityRight = velocityRight;
}



void Attack2 ( Robot *robot, Environment *env )
{
	Vector3D t = env->currentBall.pos;
	double r = robot->rotation;
	if ( r < 0 ) r += 360;
	if ( r > 360 ) r -= 360;
	double vl = 0, vr = 0;

	if ( t.y > env->fieldBounds.top - 2.5 ) t.y = env->fieldBounds.top - 2.5;
	if ( t.y < env->fieldBounds.bottom + 2.5 ) t.y = env->fieldBounds.bottom + 2.5;
	if ( t.x > env->fieldBounds.right - 3 ) t.x = env->fieldBounds.right - 3;
	if ( t.x < env->fieldBounds.left + 3 ) t.x = env->fieldBounds.left + 3;

	double dx = robot->pos.x - t.x;
	double dy = robot->pos.y - t.y;

	double dxAdjusted = dx;
	double angleToPoint = 0;

	if ( fabs ( robot->pos.y - t.y ) > 7 || t.x > robot->pos.x )
		dxAdjusted -= 5;

	if ( dxAdjusted == 0 )
	{
		if ( dy > 0 )
			angleToPoint = 270;
		else
			angleToPoint = 90;
	}
	else if ( dy == 0 )
	{
		if ( dxAdjusted > 0 )
			angleToPoint = 360;
		else
			angleToPoint = 180;

	}
	else
		angleToPoint = atan ( fabs ( dy / dx ) ) * 180.0 / PI;

	if ( dxAdjusted > 0 )
	{
		if ( dy > 0 )
			angleToPoint -= 180;
		else if ( dy < 0 )
			angleToPoint = 180 - angleToPoint;
	}
	if ( dxAdjusted < 0 )
	{
		if ( dy > 0 )
			angleToPoint = - angleToPoint;
		else if ( dy < 0 )
			angleToPoint = 90 - angleToPoint;
	}

	if ( angleToPoint < 0 ) angleToPoint = angleToPoint + 360;
	if ( angleToPoint > 360 ) angleToPoint = angleToPoint - 360;
	if ( angleToPoint > 360 ) angleToPoint = angleToPoint - 360;

	double c = r;

	double angleDiff = fabs ( r - angleToPoint );

	if ( angleDiff < 40 )
	{
		vl = 100;
		vr = 100;
		if ( c > angleToPoint )
			vl -= 10;
		if ( c < angleToPoint )
			vr -= 10;
	}
	else
	{
		if ( r > angleToPoint )
		{
			if ( angleDiff > 180 )
				vl += 360 - angleDiff;
			else
				vr += angleDiff;
		}
		if ( r < angleToPoint )
		{
			if ( angleDiff > 180 )
				vr += 360 - angleDiff;
			else
				vl += angleDiff;
		}
	}

	NearBound2 ( robot, vl, vr, env );
}

void NearBound2 ( Robot *robot, double vl, double vr, Environment *env )
{
	//Vector3D t = env->currentBall.pos;

	Vector3D a = robot->pos;
	double r = robot->rotation;

	if ( a.y > env->fieldBounds.top - 15 && r > 45 && r < 130 )
	{
		if ( vl > 0 )
			vl /= 3;
		if ( vr > 0 )
			vr /= 3;
	}

	if ( a.y < env->fieldBounds.bottom + 15 && r < -45 && r > -130 )
	{
		if ( vl > 0 ) vl /= 3;
		if ( vr > 0 ) vr /= 3;
	}

	if ( a.x > env->fieldBounds.right - 10 )
	{
		if ( vl > 0 )
			vl /= 2;
		if ( vr > 0 )
			vr /= 2;
	}

	if ( a.x < env->fieldBounds.left + 10 )
	{
		if ( vl > 0 )
			vl /= 2;
		if ( vr > 0 )
			vr /= 2;
	}

	robot->velocityLeft = vl;
	robot->velocityRight = vr;
}

void Defend ( Robot *robot, Environment *env, double low, double high )
{
	double vl = 0, vr = 0;
	Vector3D z = env->currentBall.pos;

	double Tx = env->goalBounds.right - z.x;
	double Ty = env->fieldBounds.top - z.y;
	Vector3D a = robot->pos;
	a.x = env->goalBounds.right - a.x;
	a.y = env->fieldBounds.top - a.y;

	if ( a.y > Ty + 0.9 && a.y > low )
	{
		vl = -100;
		vr = -100;
	}
	if ( a.y < Ty - 0.9 && a.y < high )
	{
		vl = 100;
		vr = 100;
	}
	if ( a.y < low )
	{
		vl = 100;
		vr = 100;
	}
	if ( a.y > high )
	{
		vl = -100;
		vr = -100;
	}

	double Tr = robot->rotation;

	if ( Tr < 0.001 )
		Tr += 360;
	if ( Tr > 360.001 )
		Tr -= 360;
	if ( Tr > 270.5 )
		vr += fabs ( Tr - 270 );
	else if ( Tr < 269.5 )
		vl += fabs ( Tr - 270 );

	NearBound2 ( robot, vl ,vr, env );
}
