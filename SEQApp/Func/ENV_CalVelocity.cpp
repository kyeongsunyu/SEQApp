#include "..\pch.h"
#include "..\SeqMain\CLASS_Main.h"
#include "..\SeqMain\DEFINE_GVX.h"


/************************************************************************/
/*                                                                      */
/*            |                                                         */
/*        V  -|-------/|-------------------------|\                     */
/*            |      / |                         | \                    */
/*            |     /  |                         |  \                   */
/*            |    /   |                         |   \                  */
/*            |   /    |                         |    \                 */
/*            |  /     |                         |     \                */
/*            | /      |                         |      \ |             */
/*            |/-------|-------------------------|-------\|----         */
/*            |        |                         |        |             */
/*            |<------>|<----------------------->|<------>|             */
/*            |   ta                                 ta   |             */
/*            |<----------------------------------------->|             */
/*                                tm                                    */
/*					   1                                                */
/*        이동거리 S=(---*ta*V*2)  + (tm-2*ta)*V                        */
/*                     2                                                */
/*                                                                      */
/*                    S                          S                      */
/*        ta = tm - (---) =>(1),     tm = ta + (---) =>(2)              */
/*                    V                          V                      */
/*                                                                      */
/*                                                                      */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
void CSeqMain::Make_Parameter1(CAjinMotor* Axis)
{
	double	temp_accel_time;	// unit : sec
	double	temp_speed;			// unit : mm/sec
	double	g_accel = 1.0;
	long	MAXSPEED;
	int		machinespeed = MachineSpeed;

	/*if ((Axis == MTStageX || Axis == MTStageY|| Axis == MTStageZ))  {
		g_accel = 0.5;
	}*/
	
	if (!Axis->bCamType) {
		MAXSPEED = (long)(MAX_SPEED * (Axis->SpeedDevide / 100.) * (machinespeed / 100.));

		temp_speed = (Axis->Speed / Axis->MMI_PulseRate) * (Axis->SpeedDevide / 100.) * (machinespeed / 100.);

		temp_accel_time = temp_speed / (g_accel * 9800.0);
		
		Axis->Accel = (int)(temp_speed / temp_accel_time);	// unit : mm^2/sec
		Axis->MovingDistance = abs(Axis->NxtArrpos - Axis->CurArrpos) / Axis->MMI_PulseRate;	// unit : mm

		if ((temp_speed * temp_accel_time) > Axis->MovingDistance) {	// »ï°¢ ±¸µ¿ÀÌ¶ó¸é 
			Axis->Speed = (int)(sqrt((double)(Axis->Accel * abs(Axis->MovingDistance))));
		}
		else {
			Axis->Speed = (int)(temp_speed);
		}

		if (Axis->Speed < 5) {
			Axis->Speed = 10 * Axis->MMI_PulseRate;	// unit : pps
			Axis->Accel = Axis->Speed * 2;
			Axis->Decel = Axis->Accel;
		}
		else {
			Axis->Speed = Axis->Speed * Axis->MMI_PulseRate;	// unit : pps
			Axis->Accel = Axis->Speed * 10;// Axis->MMI_PulseRate;
			Axis->Decel = Axis->Accel;
		}
	}
	else {
		Axis->Speed = Axis->Speed * 400;	// unit : pps
		Axis->Accel = Axis->Speed * 5;
		Axis->Decel = (int)(Axis->Accel * 0.5);
	}

	if (Axis->Speed < (int)(5 * Axis->MMI_PulseRate)) {
		Axis->Speed = Axis->SpeedArray[Axis->NxtPos];
		Axis->Accel = Axis->Speed * 10;
		Axis->Decel = Axis->Accel;
	}
}
//////////////////////////////////////////////////////////////////////////


